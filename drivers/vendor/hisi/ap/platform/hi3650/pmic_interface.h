/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmic_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-12 09:24:57
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月12日
    作    者   : x00212999
    修改内容   : 从《nManager_PMIC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __PMIC_INTERFACE_H__
#define __PMIC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/5) PMU_CTRL
 ****************************************************************************/
/* 寄存器说明：版本寄存器0。
   位域定义UNION结构:  PMIC_VERSION0_UNION */
#define PMIC_VERSION0_ADDR(base)                  ((base) + (0x000))

/* 寄存器说明：版本寄存器1。
   位域定义UNION结构:  PMIC_VERSION1_UNION */
#define PMIC_VERSION1_ADDR(base)                  ((base) + (0x001))

/* 寄存器说明：版本寄存器2。
   位域定义UNION结构:  PMIC_VERSION2_UNION */
#define PMIC_VERSION2_ADDR(base)                  ((base) + (0x002))

/* 寄存器说明：版本寄存器3。
   位域定义UNION结构:  PMIC_VERSION3_UNION */
#define PMIC_VERSION3_ADDR(base)                  ((base) + (0x003))

/* 寄存器说明：版本寄存器4。
   位域定义UNION结构:  PMIC_VERSION4_UNION */
#define PMIC_VERSION4_ADDR(base)                  ((base) + (0x004))

/* 寄存器说明：版本寄存器5。
   位域定义UNION结构:  PMIC_VERSION5_UNION */
#define PMIC_VERSION5_ADDR(base)                  ((base) + (0x005))

/* 寄存器说明：状态标志寄存器0。
   位域定义UNION结构:  PMIC_STATUS0_UNION */
#define PMIC_STATUS0_ADDR(base)                   ((base) + (0x006))

/* 寄存器说明：状态标志寄存器1。
   位域定义UNION结构:  PMIC_STATUS1_UNION */
#define PMIC_STATUS1_ADDR(base)                   ((base) + (0x007))

/* 寄存器说明：数模接口保留寄存器0。
   位域定义UNION结构:  PMIC_D2A_RES0_UNION */
#define PMIC_D2A_RES0_ADDR(base)                  ((base) + (0x008))

/* 寄存器说明：数模接口保留寄存器1。
   位域定义UNION结构:  PMIC_D2A_RES1_UNION */
#define PMIC_D2A_RES1_ADDR(base)                  ((base) + (0x009))

/* 寄存器说明：xo_cali_thresold[15:8]映射寄存器
   位域定义UNION结构:  PMIC_D2A_RES2_UNION */
#define PMIC_D2A_RES2_ADDR(base)                  ((base) + (0x00A))

/* 寄存器说明：数模接口保留寄存器3。
   位域定义UNION结构:  PMIC_A2D_RES0_UNION */
#define PMIC_A2D_RES0_ADDR(base)                  ((base) + (0x00B))

/* 寄存器说明：数模接口保留寄存器4。
   位域定义UNION结构:  PMIC_A2D_RES1_UNION */
#define PMIC_A2D_RES1_ADDR(base)                  ((base) + (0x00C))

/* 寄存器说明：BUCK0控制寄存器0。
   位域定义UNION结构:  PMIC_BUCK0_CTRL0_UNION */
#define PMIC_BUCK0_CTRL0_ADDR(base)               ((base) + (0x00D))

/* 寄存器说明：BUCK0控制寄存器1。
   位域定义UNION结构:  PMIC_BUCK0_CTRL1_UNION */
#define PMIC_BUCK0_CTRL1_ADDR(base)               ((base) + (0x00E))

/* 寄存器说明：BUCK0控制寄存器2。
   位域定义UNION结构:  PMIC_BUCK0_CTRL2_UNION */
#define PMIC_BUCK0_CTRL2_ADDR(base)               ((base) + (0x00F))

/* 寄存器说明：BUCK0控制寄存器3。
   位域定义UNION结构:  PMIC_BUCK0_CTRL3_UNION */
#define PMIC_BUCK0_CTRL3_ADDR(base)               ((base) + (0x010))

/* 寄存器说明：BUCK0控制寄存器4。
   位域定义UNION结构:  PMIC_BUCK0_CTRL4_UNION */
#define PMIC_BUCK0_CTRL4_ADDR(base)               ((base) + (0x011))

/* 寄存器说明：BUCK0控制寄存器5。
   位域定义UNION结构:  PMIC_BUCK0_CTRL5_UNION */
#define PMIC_BUCK0_CTRL5_ADDR(base)               ((base) + (0x012))

/* 寄存器说明：BUCK0控制寄存器6。
   位域定义UNION结构:  PMIC_BUCK0_CTRL6_UNION */
#define PMIC_BUCK0_CTRL6_ADDR(base)               ((base) + (0x013))

/* 寄存器说明：BUCK0控制寄存器7。
   位域定义UNION结构:  PMIC_BUCK0_CTRL7_UNION */
#define PMIC_BUCK0_CTRL7_ADDR(base)               ((base) + (0x014))

/* 寄存器说明：BUCK0控制寄存器8。
   位域定义UNION结构:  PMIC_BUCK0_CTRL8_UNION */
#define PMIC_BUCK0_CTRL8_ADDR(base)               ((base) + (0x015))

/* 寄存器说明：BUCK0控制寄存器9。
   位域定义UNION结构:  PMIC_BUCK0_CTRL9_UNION */
#define PMIC_BUCK0_CTRL9_ADDR(base)               ((base) + (0x016))

/* 寄存器说明：BUCK0控制寄存器10。
   位域定义UNION结构:  PMIC_BUCK0_CTRL10_UNION */
#define PMIC_BUCK0_CTRL10_ADDR(base)              ((base) + (0x017))

/* 寄存器说明：BUCK0控制寄存器11。
   位域定义UNION结构:  PMIC_BUCK0_CTRL11_UNION */
#define PMIC_BUCK0_CTRL11_ADDR(base)              ((base) + (0x018))

/* 寄存器说明：BUCK1控制寄存器0。
   位域定义UNION结构:  PMIC_BUCK1_CTRL0_UNION */
#define PMIC_BUCK1_CTRL0_ADDR(base)               ((base) + (0x019))

/* 寄存器说明：BUCK1控制寄存器1。
   位域定义UNION结构:  PMIC_BUCK1_CTRL1_UNION */
#define PMIC_BUCK1_CTRL1_ADDR(base)               ((base) + (0x01A))

/* 寄存器说明：BUCK1控制寄存器2。
   位域定义UNION结构:  PMIC_BUCK1_CTRL2_UNION */
#define PMIC_BUCK1_CTRL2_ADDR(base)               ((base) + (0x01B))

/* 寄存器说明：BUCK1控制寄存器3。
   位域定义UNION结构:  PMIC_BUCK1_CTRL3_UNION */
#define PMIC_BUCK1_CTRL3_ADDR(base)               ((base) + (0x01C))

/* 寄存器说明：BUCK1控制寄存器4。
   位域定义UNION结构:  PMIC_BUCK1_CTRL4_UNION */
#define PMIC_BUCK1_CTRL4_ADDR(base)               ((base) + (0x01D))

/* 寄存器说明：BUCK1控制寄存器5。
   位域定义UNION结构:  PMIC_BUCK1_CTRL5_UNION */
#define PMIC_BUCK1_CTRL5_ADDR(base)               ((base) + (0x01E))

/* 寄存器说明：BUCK1控制寄存器6。
   位域定义UNION结构:  PMIC_BUCK1_CTRL6_UNION */
#define PMIC_BUCK1_CTRL6_ADDR(base)               ((base) + (0x01F))

/* 寄存器说明：BUCK1控制寄存器7。
   位域定义UNION结构:  PMIC_BUCK1_CTRL7_UNION */
#define PMIC_BUCK1_CTRL7_ADDR(base)               ((base) + (0x020))

/* 寄存器说明：BUCK1控制寄存器8。
   位域定义UNION结构:  PMIC_BUCK1_CTRL8_UNION */
#define PMIC_BUCK1_CTRL8_ADDR(base)               ((base) + (0x021))

/* 寄存器说明：BUCK1控制寄存器9。
   位域定义UNION结构:  PMIC_BUCK1_CTRL9_UNION */
#define PMIC_BUCK1_CTRL9_ADDR(base)               ((base) + (0x022))

/* 寄存器说明：BUCK1控制寄存器10。
   位域定义UNION结构:  PMIC_BUCK1_CTRL10_UNION */
#define PMIC_BUCK1_CTRL10_ADDR(base)              ((base) + (0x023))

/* 寄存器说明：BUCK1控制寄存器11。
   位域定义UNION结构:  PMIC_BUCK1_CTRL11_UNION */
#define PMIC_BUCK1_CTRL11_ADDR(base)              ((base) + (0x024))

/* 寄存器说明：BUCK2控制寄存器0。
   位域定义UNION结构:  PMIC_BUCK2_CTRL0_UNION */
#define PMIC_BUCK2_CTRL0_ADDR(base)               ((base) + (0x025))

/* 寄存器说明：BUCK2控制寄存器1。
   位域定义UNION结构:  PMIC_BUCK2_CTRL1_UNION */
#define PMIC_BUCK2_CTRL1_ADDR(base)               ((base) + (0x026))

/* 寄存器说明：BUCK2控制寄存器2。
   位域定义UNION结构:  PMIC_BUCK2_CTRL2_UNION */
#define PMIC_BUCK2_CTRL2_ADDR(base)               ((base) + (0x027))

/* 寄存器说明：BUCK2控制寄存器3。
   位域定义UNION结构:  PMIC_BUCK2_CTRL3_UNION */
#define PMIC_BUCK2_CTRL3_ADDR(base)               ((base) + (0x028))

/* 寄存器说明：BUCK2控制寄存器4。
   位域定义UNION结构:  PMIC_BUCK2_CTRL4_UNION */
#define PMIC_BUCK2_CTRL4_ADDR(base)               ((base) + (0x029))

/* 寄存器说明：BUCK2控制寄存器5。
   位域定义UNION结构:  PMIC_BUCK2_CTRL5_UNION */
#define PMIC_BUCK2_CTRL5_ADDR(base)               ((base) + (0x02A))

/* 寄存器说明：BUCK2控制寄存器6。
   位域定义UNION结构:  PMIC_BUCK2_CTRL6_UNION */
#define PMIC_BUCK2_CTRL6_ADDR(base)               ((base) + (0x02B))

/* 寄存器说明：BUCK2控制寄存器7。
   位域定义UNION结构:  PMIC_BUCK2_CTRL7_UNION */
#define PMIC_BUCK2_CTRL7_ADDR(base)               ((base) + (0x02C))

/* 寄存器说明：BUCK2控制寄存器8。
   位域定义UNION结构:  PMIC_BUCK2_CTRL8_UNION */
#define PMIC_BUCK2_CTRL8_ADDR(base)               ((base) + (0x02D))

/* 寄存器说明：BUCK2控制寄存器9。
   位域定义UNION结构:  PMIC_BUCK2_CTRL9_UNION */
#define PMIC_BUCK2_CTRL9_ADDR(base)               ((base) + (0x02E))

/* 寄存器说明：BUCK2控制寄存器10。
   位域定义UNION结构:  PMIC_BUCK2_CTRL10_UNION */
#define PMIC_BUCK2_CTRL10_ADDR(base)              ((base) + (0x02F))

/* 寄存器说明：BUCK2控制寄存器11。
   位域定义UNION结构:  PMIC_BUCK2_CTRL11_UNION */
#define PMIC_BUCK2_CTRL11_ADDR(base)              ((base) + (0x030))

/* 寄存器说明：BUCK3控制寄存器0。
   位域定义UNION结构:  PMIC_BUCK3_CTRL0_UNION */
#define PMIC_BUCK3_CTRL0_ADDR(base)               ((base) + (0x031))

/* 寄存器说明：BUCK3控制寄存器1。
   位域定义UNION结构:  PMIC_BUCK3_CTRL1_UNION */
#define PMIC_BUCK3_CTRL1_ADDR(base)               ((base) + (0x032))

/* 寄存器说明：BUCK3控制寄存器2。
   位域定义UNION结构:  PMIC_BUCK3_CTRL2_UNION */
#define PMIC_BUCK3_CTRL2_ADDR(base)               ((base) + (0x033))

/* 寄存器说明：BUCK3控制寄存器3。
   位域定义UNION结构:  PMIC_BUCK3_CTRL3_UNION */
#define PMIC_BUCK3_CTRL3_ADDR(base)               ((base) + (0x034))

/* 寄存器说明：BUCK3控制寄存器4。
   位域定义UNION结构:  PMIC_BUCK3_CTRL4_UNION */
#define PMIC_BUCK3_CTRL4_ADDR(base)               ((base) + (0x035))

/* 寄存器说明：BUCK3控制寄存器5。
   位域定义UNION结构:  PMIC_BUCK3_CTRL5_UNION */
#define PMIC_BUCK3_CTRL5_ADDR(base)               ((base) + (0x036))

/* 寄存器说明：BUCK3控制寄存器6。
   位域定义UNION结构:  PMIC_BUCK3_CTRL6_UNION */
#define PMIC_BUCK3_CTRL6_ADDR(base)               ((base) + (0x037))

/* 寄存器说明：BUCK3控制寄存器7。
   位域定义UNION结构:  PMIC_BUCK3_CTRL7_UNION */
#define PMIC_BUCK3_CTRL7_ADDR(base)               ((base) + (0x038))

/* 寄存器说明：BUCK3控制寄存器8。
   位域定义UNION结构:  PMIC_BUCK3_CTRL8_UNION */
#define PMIC_BUCK3_CTRL8_ADDR(base)               ((base) + (0x039))

/* 寄存器说明：BUCK3控制寄存器9。
   位域定义UNION结构:  PMIC_BUCK3_CTRL9_UNION */
#define PMIC_BUCK3_CTRL9_ADDR(base)               ((base) + (0x03A))

/* 寄存器说明：BUCK3控制寄存器10。
   位域定义UNION结构:  PMIC_BUCK3_CTRL10_UNION */
#define PMIC_BUCK3_CTRL10_ADDR(base)              ((base) + (0x03B))

/* 寄存器说明：BUCK3控制寄存器11。
   位域定义UNION结构:  PMIC_BUCK3_CTRL11_UNION */
#define PMIC_BUCK3_CTRL11_ADDR(base)              ((base) + (0x03C))

/* 寄存器说明：BUCK4控制寄存器0。
   位域定义UNION结构:  PMIC_BUCK4_CTRL0_UNION */
#define PMIC_BUCK4_CTRL0_ADDR(base)               ((base) + (0x03D))

/* 寄存器说明：BUCK4控制寄存器1。
   位域定义UNION结构:  PMIC_BUCK4_CTRL1_UNION */
#define PMIC_BUCK4_CTRL1_ADDR(base)               ((base) + (0x03E))

/* 寄存器说明：BUCK4控制寄存器2。
   位域定义UNION结构:  PMIC_BUCK4_CTRL2_UNION */
#define PMIC_BUCK4_CTRL2_ADDR(base)               ((base) + (0x03F))

/* 寄存器说明：BUCK4控制寄存器3。
   位域定义UNION结构:  PMIC_BUCK4_CTRL3_UNION */
#define PMIC_BUCK4_CTRL3_ADDR(base)               ((base) + (0x040))

/* 寄存器说明：BUCK4控制寄存器4。
   位域定义UNION结构:  PMIC_BUCK4_CTRL4_UNION */
#define PMIC_BUCK4_CTRL4_ADDR(base)               ((base) + (0x041))

/* 寄存器说明：BUCK4控制寄存器5。
   位域定义UNION结构:  PMIC_BUCK4_CTRL5_UNION */
#define PMIC_BUCK4_CTRL5_ADDR(base)               ((base) + (0x042))

/* 寄存器说明：BUCK4控制寄存器6。
   位域定义UNION结构:  PMIC_BUCK4_CTRL6_UNION */
#define PMIC_BUCK4_CTRL6_ADDR(base)               ((base) + (0x043))

/* 寄存器说明：BUCK4控制寄存器7。
   位域定义UNION结构:  PMIC_BUCK4_CTRL7_UNION */
#define PMIC_BUCK4_CTRL7_ADDR(base)               ((base) + (0x044))

/* 寄存器说明：BUCK4控制寄存器8。
   位域定义UNION结构:  PMIC_BUCK4_CTRL8_UNION */
#define PMIC_BUCK4_CTRL8_ADDR(base)               ((base) + (0x045))

/* 寄存器说明：BUCK4控制寄存器9。
   位域定义UNION结构:  PMIC_BUCK4_CTRL9_UNION */
#define PMIC_BUCK4_CTRL9_ADDR(base)               ((base) + (0x046))

/* 寄存器说明：BUCK4控制寄存器10。
   位域定义UNION结构:  PMIC_BUCK4_CTRL10_UNION */
#define PMIC_BUCK4_CTRL10_ADDR(base)              ((base) + (0x047))

/* 寄存器说明：BUCK4控制寄存器11。
   位域定义UNION结构:  PMIC_BUCK4_CTRL11_UNION */
#define PMIC_BUCK4_CTRL11_ADDR(base)              ((base) + (0x048))

/* 寄存器说明：LDO0_2/LDO1控制寄存器。
   位域定义UNION结构:  PMIC_LDO_1_CTRL_UNION */
#define PMIC_LDO_1_CTRL_ADDR(base)                ((base) + (0x049))

/* 寄存器说明：LDO2/LDO3控制寄存器。
   位域定义UNION结构:  PMIC_LD2_3_CTRL_UNION */
#define PMIC_LD2_3_CTRL_ADDR(base)                ((base) + (0x04A))

/* 寄存器说明：LDO4/LDO5控制寄存器。
   位域定义UNION结构:  PMIC_LDO4_5_CTRL_UNION */
#define PMIC_LDO4_5_CTRL_ADDR(base)               ((base) + (0x04B))

/* 寄存器说明：LDO7/LDO8控制寄存器。
   位域定义UNION结构:  PMIC_LDO7_8_CTRL_UNION */
#define PMIC_LDO7_8_CTRL_ADDR(base)               ((base) + (0x04C))

/* 寄存器说明：LDO9/LDO10控制寄存器。
   位域定义UNION结构:  PMIC_LDO9_10_CTRL_UNION */
#define PMIC_LDO9_10_CTRL_ADDR(base)              ((base) + (0x04D))

/* 寄存器说明：LDO11/LDO12控制寄存器。
   位域定义UNION结构:  PMIC_LD11_12_CTRL_UNION */
#define PMIC_LD11_12_CTRL_ADDR(base)              ((base) + (0x04E))

/* 寄存器说明：LDO13/LDO14控制寄存器。
   位域定义UNION结构:  PMIC_LDO13_14_CTRL_UNION */
#define PMIC_LDO13_14_CTRL_ADDR(base)             ((base) + (0x04F))

/* 寄存器说明：LDO15/LDO16控制寄存器。
   位域定义UNION结构:  PMIC_LDO15_16_CTRL_UNION */
#define PMIC_LDO15_16_CTRL_ADDR(base)             ((base) + (0x050))

/* 寄存器说明：LDO17/LDO19控制寄存器。
   位域定义UNION结构:  PMIC_LDO17_19_CTRL_UNION */
#define PMIC_LDO17_19_CTRL_ADDR(base)             ((base) + (0x051))

/* 寄存器说明：LDO20/LDO21控制寄存器。
   位域定义UNION结构:  PMIC_LDO20_21_CTRL_UNION */
#define PMIC_LDO20_21_CTRL_ADDR(base)             ((base) + (0x052))

/* 寄存器说明：LDO22/LDO23控制寄存器。
   位域定义UNION结构:  PMIC_LDO22_23_CTRL_UNION */
#define PMIC_LDO22_23_CTRL_ADDR(base)             ((base) + (0x053))

/* 寄存器说明：LDO24/LDO25控制寄存器。
   位域定义UNION结构:  PMIC_LDO24_25_CTRL_UNION */
#define PMIC_LDO24_25_CTRL_ADDR(base)             ((base) + (0x054))

/* 寄存器说明：LDO26/LDO27控制寄存器。
   位域定义UNION结构:  PMIC_LDO26_27_CTRL_UNION */
#define PMIC_LDO26_27_CTRL_ADDR(base)             ((base) + (0x055))

/* 寄存器说明：LDO28/LDO29控制寄存器。
   位域定义UNION结构:  PMIC_LDO28_29_CTRL_UNION */
#define PMIC_LDO28_29_CTRL_ADDR(base)             ((base) + (0x056))

/* 寄存器说明：LDO30/LDO31控制寄存器。
   位域定义UNION结构:  PMIC_LDO30_31_CTRL_UNION */
#define PMIC_LDO30_31_CTRL_ADDR(base)             ((base) + (0x057))

/* 寄存器说明：LDO32控制寄存器。
   位域定义UNION结构:  PMIC_LDO32_CTRL_UNION */
#define PMIC_LDO32_CTRL_ADDR(base)                ((base) + (0x058))

/* 寄存器说明：LDO0_1开关使能寄存器。
   位域定义UNION结构:  PMIC_LDO0_1_ONOFF_UNION */
#define PMIC_LDO0_1_ONOFF_ADDR(base)              ((base) + (0x059))

/* 寄存器说明：LDO0_2开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO0_2_ONOFF_ECO_UNION */
#define PMIC_LDO0_2_ONOFF_ECO_ADDR(base)          ((base) + (0x05A))

/* 寄存器说明：LDO0_2调压寄存器。
   位域定义UNION结构:  PMIC_LDO0_2_VSET_UNION */
#define PMIC_LDO0_2_VSET_ADDR(base)               ((base) + (0x05B))

/* 寄存器说明：LDO1开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO1_ONOFF_ECO_UNION */
#define PMIC_LDO1_ONOFF_ECO_ADDR(base)            ((base) + (0x05C))

/* 寄存器说明：LDO1调压寄存器。
   位域定义UNION结构:  PMIC_LDO1_VSET_UNION */
#define PMIC_LDO1_VSET_ADDR(base)                 ((base) + (0x05D))

/* 寄存器说明：LDO2开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO2_ONOFF_ECO_UNION */
#define PMIC_LDO2_ONOFF_ECO_ADDR(base)            ((base) + (0x05E))

/* 寄存器说明：LDO2调压寄存器。
   位域定义UNION结构:  PMIC_LDO2_VSET_UNION */
#define PMIC_LDO2_VSET_ADDR(base)                 ((base) + (0x05F))

/* 寄存器说明：LDO3开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO3_ONOFF_ECO_UNION */
#define PMIC_LDO3_ONOFF_ECO_ADDR(base)            ((base) + (0x060))

/* 寄存器说明：LDO3调压寄存器。
   位域定义UNION结构:  PMIC_LDO3_VSET_UNION */
#define PMIC_LDO3_VSET_ADDR(base)                 ((base) + (0x061))

/* 寄存器说明：LDO4开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO4_ONOFF_ECO_UNION */
#define PMIC_LDO4_ONOFF_ECO_ADDR(base)            ((base) + (0x062))

/* 寄存器说明：LDO4调压寄存器。
   位域定义UNION结构:  PMIC_LDO4_VSET_UNION */
#define PMIC_LDO4_VSET_ADDR(base)                 ((base) + (0x063))

/* 寄存器说明：LDO5开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO5_ONOFF_ECO_UNION */
#define PMIC_LDO5_ONOFF_ECO_ADDR(base)            ((base) + (0x064))

/* 寄存器说明：LDO5调压寄存器。
   位域定义UNION结构:  PMIC_LDO5_VSET_UNION */
#define PMIC_LDO5_VSET_ADDR(base)                 ((base) + (0x065))

/* 寄存器说明：LDO7开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO7_ONOFF_ECO_UNION */
#define PMIC_LDO7_ONOFF_ECO_ADDR(base)            ((base) + (0x066))

/* 寄存器说明：LDO7调压寄存器。
   位域定义UNION结构:  PMIC_LDO7_VSET_UNION */
#define PMIC_LDO7_VSET_ADDR(base)                 ((base) + (0x067))

/* 寄存器说明：LDO8开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO8_ONOFF_ECO_UNION */
#define PMIC_LDO8_ONOFF_ECO_ADDR(base)            ((base) + (0x068))

/* 寄存器说明：LDO8调压寄存器。
   位域定义UNION结构:  PMIC_LDO8_VSET_UNION */
#define PMIC_LDO8_VSET_ADDR(base)                 ((base) + (0x069))

/* 寄存器说明：LDO9开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO9_ONOFF_ECO_UNION */
#define PMIC_LDO9_ONOFF_ECO_ADDR(base)            ((base) + (0x06A))

/* 寄存器说明：LDO9调压寄存器。
   位域定义UNION结构:  PMIC_LDO9_VSET_UNION */
#define PMIC_LDO9_VSET_ADDR(base)                 ((base) + (0x06B))

/* 寄存器说明：LDO10开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO10_ONOFF_ECO_UNION */
#define PMIC_LDO10_ONOFF_ECO_ADDR(base)           ((base) + (0x06C))

/* 寄存器说明：LDO10调压寄存器。
   位域定义UNION结构:  PMIC_LDO10_VSET_UNION */
#define PMIC_LDO10_VSET_ADDR(base)                ((base) + (0x06D))

/* 寄存器说明：LDO11开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO11_ONOFF_ECO_UNION */
#define PMIC_LDO11_ONOFF_ECO_ADDR(base)           ((base) + (0x06E))

/* 寄存器说明：LDO11调压寄存器。
   位域定义UNION结构:  PMIC_LDO11_VSET_UNION */
#define PMIC_LDO11_VSET_ADDR(base)                ((base) + (0x06F))

/* 寄存器说明：LDO12开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO12_ONOFF_ECO_UNION */
#define PMIC_LDO12_ONOFF_ECO_ADDR(base)           ((base) + (0x070))

/* 寄存器说明：LDO12调压寄存器。
   位域定义UNION结构:  PMIC_LDO12_VSET_UNION */
#define PMIC_LDO12_VSET_ADDR(base)                ((base) + (0x071))

/* 寄存器说明：LDO13开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO13_ONOFF_ECO_UNION */
#define PMIC_LDO13_ONOFF_ECO_ADDR(base)           ((base) + (0x072))

/* 寄存器说明：LDO13调压寄存器。
   位域定义UNION结构:  PMIC_LDO13_VSET_UNION */
#define PMIC_LDO13_VSET_ADDR(base)                ((base) + (0x073))

/* 寄存器说明：LDO14开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO14_ONOFF_ECO_UNION */
#define PMIC_LDO14_ONOFF_ECO_ADDR(base)           ((base) + (0x074))

/* 寄存器说明：LDO14调压寄存器。
   位域定义UNION结构:  PMIC_LDO14_VSET_UNION */
#define PMIC_LDO14_VSET_ADDR(base)                ((base) + (0x075))

/* 寄存器说明：LDO15开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO15_ONOFF_ECO_UNION */
#define PMIC_LDO15_ONOFF_ECO_ADDR(base)           ((base) + (0x076))

/* 寄存器说明：LDO15调压寄存器。
   位域定义UNION结构:  PMIC_LDO15_VSET_UNION */
#define PMIC_LDO15_VSET_ADDR(base)                ((base) + (0x077))

/* 寄存器说明：LDO16开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO16_ONOFF_ECO_UNION */
#define PMIC_LDO16_ONOFF_ECO_ADDR(base)           ((base) + (0x078))

/* 寄存器说明：LDO16调压寄存器。
   位域定义UNION结构:  PMIC_LDO16_VSET_UNION */
#define PMIC_LDO16_VSET_ADDR(base)                ((base) + (0x079))

/* 寄存器说明：LDO17开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO17_ONOFF_ECO_UNION */
#define PMIC_LDO17_ONOFF_ECO_ADDR(base)           ((base) + (0x07A))

/* 寄存器说明：LDO17调压寄存器。
   位域定义UNION结构:  PMIC_LDO17_VSET_UNION */
#define PMIC_LDO17_VSET_ADDR(base)                ((base) + (0x07B))

/* 寄存器说明：LDO19开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO19_ONOFF_ECO_UNION */
#define PMIC_LDO19_ONOFF_ECO_ADDR(base)           ((base) + (0x07C))

/* 寄存器说明：LDO19调压寄存器。
   位域定义UNION结构:  PMIC_LDO19_VSET1_UNION */
#define PMIC_LDO19_VSET1_ADDR(base)               ((base) + (0x07D))

/* 寄存器说明：LDO20开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO20_ONOFF_ECO_UNION */
#define PMIC_LDO20_ONOFF_ECO_ADDR(base)           ((base) + (0x07E))

/* 寄存器说明：LDO20调压寄存器。
   位域定义UNION结构:  PMIC_LDO20_VSET_UNION */
#define PMIC_LDO20_VSET_ADDR(base)                ((base) + (0x07F))

/* 寄存器说明：LDO21开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO21_ONOFF_ECO_UNION */
#define PMIC_LDO21_ONOFF_ECO_ADDR(base)           ((base) + (0x080))

/* 寄存器说明：LDO21调压寄存器。
   位域定义UNION结构:  PMIC_LDO21_VSET_UNION */
#define PMIC_LDO21_VSET_ADDR(base)                ((base) + (0x081))

/* 寄存器说明：LDO22开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO22_ONOFF_ECO_UNION */
#define PMIC_LDO22_ONOFF_ECO_ADDR(base)           ((base) + (0x082))

/* 寄存器说明：LDO22调压寄存器。
   位域定义UNION结构:  PMIC_LDO22_VSET_UNION */
#define PMIC_LDO22_VSET_ADDR(base)                ((base) + (0x083))

/* 寄存器说明：LDO23开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO23_ONOFF_ECO_UNION */
#define PMIC_LDO23_ONOFF_ECO_ADDR(base)           ((base) + (0x084))

/* 寄存器说明：LDO23调压寄存器。
   位域定义UNION结构:  PMIC_LDO23_VSET_UNION */
#define PMIC_LDO23_VSET_ADDR(base)                ((base) + (0x085))

/* 寄存器说明：LDO24开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO24_ONOFF_ECO_UNION */
#define PMIC_LDO24_ONOFF_ECO_ADDR(base)           ((base) + (0x086))

/* 寄存器说明：LDO24调压寄存器。
   位域定义UNION结构:  PMIC_LDO24_VSET_UNION */
#define PMIC_LDO24_VSET_ADDR(base)                ((base) + (0x087))

/* 寄存器说明：LDO25开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO25_ONOFF_ECO_UNION */
#define PMIC_LDO25_ONOFF_ECO_ADDR(base)           ((base) + (0x088))

/* 寄存器说明：LDO25调压寄存器。
   位域定义UNION结构:  PMIC_LDO25_VSET_UNION */
#define PMIC_LDO25_VSET_ADDR(base)                ((base) + (0x089))

/* 寄存器说明：LDO26开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO26_ONOFF_ECO_UNION */
#define PMIC_LDO26_ONOFF_ECO_ADDR(base)           ((base) + (0x08A))

/* 寄存器说明：LDO26调压寄存器。
   位域定义UNION结构:  PMIC_LDO26_VSET_UNION */
#define PMIC_LDO26_VSET_ADDR(base)                ((base) + (0x08B))

/* 寄存器说明：LDO27开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO27_ONOFF_ECO_UNION */
#define PMIC_LDO27_ONOFF_ECO_ADDR(base)           ((base) + (0x08C))

/* 寄存器说明：LDO27调压寄存器。
   位域定义UNION结构:  PMIC_LDO27_VSET_UNION */
#define PMIC_LDO27_VSET_ADDR(base)                ((base) + (0x08D))

/* 寄存器说明：LDO28开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO28_ONOFF_ECO_UNION */
#define PMIC_LDO28_ONOFF_ECO_ADDR(base)           ((base) + (0x08E))

/* 寄存器说明：LDO28调压寄存器。
   位域定义UNION结构:  PMIC_LDO28_VSET_UNION */
#define PMIC_LDO28_VSET_ADDR(base)                ((base) + (0x08F))

/* 寄存器说明：LDO29开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO29_ONOFF_ECO_UNION */
#define PMIC_LDO29_ONOFF_ECO_ADDR(base)           ((base) + (0x090))

/* 寄存器说明：LDO29调压寄存器。
   位域定义UNION结构:  PMIC_LDO29_VSET_UNION */
#define PMIC_LDO29_VSET_ADDR(base)                ((base) + (0x091))

/* 寄存器说明：LDO开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO30_ONOFF_ECO_UNION */
#define PMIC_LDO30_ONOFF_ECO_ADDR(base)           ((base) + (0x092))

/* 寄存器说明：LDO30调压寄存器。
   位域定义UNION结构:  PMIC_LDO30_VSET_UNION */
#define PMIC_LDO30_VSET_ADDR(base)                ((base) + (0x093))

/* 寄存器说明：LDO31开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO31_ONOFF_ECO_UNION */
#define PMIC_LDO31_ONOFF_ECO_ADDR(base)           ((base) + (0x094))

/* 寄存器说明：LDO31调压寄存器。
   位域定义UNION结构:  PMIC_LDO31_VSET_UNION */
#define PMIC_LDO31_VSET_ADDR(base)                ((base) + (0x095))

/* 寄存器说明：LDO32开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO32_ONOFF_ECO_UNION */
#define PMIC_LDO32_ONOFF_ECO_ADDR(base)           ((base) + (0x096))

/* 寄存器说明：LDO32调压寄存器。
   位域定义UNION结构:  PMIC_LDO32_VSET_UNION */
#define PMIC_LDO32_VSET_ADDR(base)                ((base) + (0x097))

/* 寄存器说明：BUCK0开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_BUCK0_ONOFF_ECO_UNION */
#define PMIC_BUCK0_ONOFF_ECO_ADDR(base)           ((base) + (0x098))

/* 寄存器说明：BUCK0调压寄存器。
   位域定义UNION结构:  PMIC_BUCK0_VSET_UNION */
#define PMIC_BUCK0_VSET_ADDR(base)                ((base) + (0x099))

/* 寄存器说明：BUCK1开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_BUCK1_ONOFF_ECO_UNION */
#define PMIC_BUCK1_ONOFF_ECO_ADDR(base)           ((base) + (0x09A))

/* 寄存器说明：BUCK1调压寄存器。
   位域定义UNION结构:  PMIC_BUCK1_VSET_UNION */
#define PMIC_BUCK1_VSET_ADDR(base)                ((base) + (0x09B))

/* 寄存器说明：BUCK2开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_BUCK2_ONOFF_ECO_UNION */
#define PMIC_BUCK2_ONOFF_ECO_ADDR(base)           ((base) + (0x09C))

/* 寄存器说明：BUCK2调压寄存器。
   位域定义UNION结构:  PMIC_BUCK2_VSET_UNION */
#define PMIC_BUCK2_VSET_ADDR(base)                ((base) + (0x09D))

/* 寄存器说明：BUCK3开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_BUCK3_ONOFF_ECO_UNION */
#define PMIC_BUCK3_ONOFF_ECO_ADDR(base)           ((base) + (0x09E))

/* 寄存器说明：BUCK3调压寄存器。
   位域定义UNION结构:  PMIC_BUCK3_VSET_UNION */
#define PMIC_BUCK3_VSET_ADDR(base)                ((base) + (0x09F))

/* 寄存器说明：BUCK4开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_BUCK4_ONOFF_ECO_UNION */
#define PMIC_BUCK4_ONOFF_ECO_ADDR(base)           ((base) + (0x0A0))

/* 寄存器说明：BUCK4调压控制寄存器。
   位域定义UNION结构:  PMIC_BUCK4_VSET_UNION */
#define PMIC_BUCK4_VSET_ADDR(base)                ((base) + (0x0A1))

/* 寄存器说明：LDO_PMUA ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO_PMUA_ECO_UNION */
#define PMIC_LDO_PMUA_ECO_ADDR(base)              ((base) + (0x0A2))

/* 寄存器说明：LDO_PMUA调压寄存器。
   位域定义UNION结构:  PMIC_LDO_PMUA_VSET_UNION */
#define PMIC_LDO_PMUA_VSET_ADDR(base)             ((base) + (0x0A3))

/* 寄存器说明：BST使能控制寄存器。
   位域定义UNION结构:  PMIC_BST_MODE_EN_UNION */
#define PMIC_BST_MODE_EN_ADDR(base)               ((base) + (0x0A4))

/* 寄存器说明：NOPWRT控制寄存器。
   位域定义UNION结构:  PMIC_NOPWR_CTRL_UNION */
#define PMIC_NOPWR_CTRL_ADDR(base)                ((base) + (0x0A5))

/* 寄存器说明：classd控制寄存器0。
   位域定义UNION结构:  PMIC_CLASSD_CTRL0_UNION */
#define PMIC_CLASSD_CTRL0_ADDR(base)              ((base) + (0x0A6))

/* 寄存器说明：classd控制寄存器1。
   位域定义UNION结构:  PMIC_CLASSD_CTRL1_UNION */
#define PMIC_CLASSD_CTRL1_ADDR(base)              ((base) + (0x0A7))

/* 寄存器说明：classd控制寄存器2。
   位域定义UNION结构:  PMIC_CLASSD_CTRL2_UNION */
#define PMIC_CLASSD_CTRL2_ADDR(base)              ((base) + (0x0A8))

/* 寄存器说明：classd控制寄存器3。
   位域定义UNION结构:  PMIC_CLASSD_CTRL3_UNION */
#define PMIC_CLASSD_CTRL3_ADDR(base)              ((base) + (0x0A9))

/* 寄存器说明：电压温度控制寄存器。
   位域定义UNION结构:  PMIC_TH_CTRL_UNION */
#define PMIC_TH_CTRL_ADDR(base)                   ((base) + (0x0AA))

/* 寄存器说明：bg测试寄存器。
   位域定义UNION结构:  PMIC_BG_TEST_UNION */
#define PMIC_BG_TEST_ADDR(base)                   ((base) + (0x0AB))

/* 寄存器说明：DR345闪烁模式使能和模式寄存器。
   位域定义UNION结构:  PMIC_DR_EN_MODE_345_UNION */
#define PMIC_DR_EN_MODE_345_ADDR(base)            ((base) + (0x0AC))

/* 寄存器说明：DR12闪烁模式使能和模式寄存器。
   位域定义UNION结构:  PMIC_DR_EN_MODE_12_UNION */
#define PMIC_DR_EN_MODE_12_ADDR(base)             ((base) + (0x0AD))

/* 寄存器说明：DR12闪烁模式周期调节0寄存器。
   位域定义UNION结构:  PMIC_FLASH_PERIOD_DR12_UNION */
#define PMIC_FLASH_PERIOD_DR12_ADDR(base)         ((base) + (0x0AE))

/* 寄存器说明：DR12闪烁模式点亮时间调节0寄存器。
   位域定义UNION结构:  PMIC_FLASH_ON_DR12_UNION */
#define PMIC_FLASH_ON_DR12_ADDR(base)             ((base) + (0x0AF))

/* 寄存器说明：DR345闪烁模式周期调节1寄存器。
   位域定义UNION结构:  PMIC_FLASH_PERIOD_DR345_UNION */
#define PMIC_FLASH_PERIOD_DR345_ADDR(base)        ((base) + (0x0B0))

/* 寄存器说明：DR345闪烁模式点亮时间调节1寄存器。
   位域定义UNION结构:  PMIC_FLASH_ON_DR345_UNION */
#define PMIC_FLASH_ON_DR345_ADDR(base)            ((base) + (0x0B1))

/* 寄存器说明：DR灯模式选择寄存器。
   位域定义UNION结构:  PMIC_DR_MODE_SEL_UNION */
#define PMIC_DR_MODE_SEL_ADDR(base)               ((base) + (0x0B2))

/* 寄存器说明：DR1/2呼吸模式控制寄存器。
   位域定义UNION结构:  PMIC_DR_BRE_CTRL_UNION */
#define PMIC_DR_BRE_CTRL_ADDR(base)               ((base) + (0x0B3))

/* 寄存器说明：DR1和DR2常亮常暗时间配置寄存器。
   位域定义UNION结构:  PMIC_DR12_TIM_CONF0_UNION */
#define PMIC_DR12_TIM_CONF0_ADDR(base)            ((base) + (0x0B4))

/* 寄存器说明：DR1和DR2渐亮渐暗时间配置寄存器。
   位域定义UNION结构:  PMIC_DR12_TIM_CONF1_UNION */
#define PMIC_DR12_TIM_CONF1_ADDR(base)            ((base) + (0x0B5))

/* 寄存器说明：DR1电流选择寄存器。
   位域定义UNION结构:  PMIC_DR1_ISET_UNION */
#define PMIC_DR1_ISET_ADDR(base)                  ((base) + (0x0B6))

/* 寄存器说明：DR2电流选择寄存器。
   位域定义UNION结构:  PMIC_DR2_ISET_UNION */
#define PMIC_DR2_ISET_ADDR(base)                  ((base) + (0x0B7))

/* 寄存器说明：DR3/4/5控制寄存器。
   位域定义UNION结构:  PMIC_DR_LED_CTRL_UNION */
#define PMIC_DR_LED_CTRL_ADDR(base)               ((base) + (0x0B8))

/* 寄存器说明：DR3/4/5输出控制寄存器。
   位域定义UNION结构:  PMIC_DR_OUT_CTRL_UNION */
#define PMIC_DR_OUT_CTRL_ADDR(base)               ((base) + (0x0B9))

/* 寄存器说明：DR3电流选择寄存器。
   位域定义UNION结构:  PMIC_DR3_ISET_UNION */
#define PMIC_DR3_ISET_ADDR(base)                  ((base) + (0x0BA))

/* 寄存器说明：DR3启动延时配置寄存器。
   位域定义UNION结构:  PMIC_DR3_START_DEL_UNION */
#define PMIC_DR3_START_DEL_ADDR(base)             ((base) + (0x0BB))

/* 寄存器说明：DR4电流选择寄存器。
   位域定义UNION结构:  PMIC_DR4_ISET_UNION */
#define PMIC_DR4_ISET_ADDR(base)                  ((base) + (0x0BC))

/* 寄存器说明：DR4启动延时配置寄存器。
   位域定义UNION结构:  PMIC_DR4_START_DEL_UNION */
#define PMIC_DR4_START_DEL_ADDR(base)             ((base) + (0x0BD))

/* 寄存器说明：DR5电流选择寄存器。
   位域定义UNION结构:  PMIC_DR5_ISET_UNION */
#define PMIC_DR5_ISET_ADDR(base)                  ((base) + (0x0BE))

/* 寄存器说明：DR5启动延时配置寄存器。
   位域定义UNION结构:  PMIC_DR5_START_DEL_UNION */
#define PMIC_DR5_START_DEL_ADDR(base)             ((base) + (0x0BF))

/* 寄存器说明：DR345常亮常暗时间配置寄存器。
   位域定义UNION结构:  PMIC_DR334_TIM_CONF0_UNION */
#define PMIC_DR334_TIM_CONF0_ADDR(base)           ((base) + (0x0C0))

/* 寄存器说明：DR345渐亮渐暗时间配置寄存器。
   位域定义UNION结构:  PMIC_DR345_TIM_CONF1_UNION */
#define PMIC_DR345_TIM_CONF1_ADDR(base)           ((base) + (0x0C1))

/* 寄存器说明：IN端低压阈值调整寄存器0。
   位域定义UNION结构:  PMIC_VSYS_LOW_SET0_UNION */
#define PMIC_VSYS_LOW_SET0_ADDR(base)             ((base) + (0x0C2))

/* 寄存器说明：IN端低压阈值调整寄存器1。
   位域定义UNION结构:  PMIC_VSYS_LOW_SET1_UNION */
#define PMIC_VSYS_LOW_SET1_ADDR(base)             ((base) + (0x0C3))

/* 寄存器说明：系统控制预留寄存器。
   位域定义UNION结构:  PMIC_SYS_CTRL_RESERVE_UNION */
#define PMIC_SYS_CTRL_RESERVE_ADDR(base)          ((base) + (0x0C4))

/* 寄存器说明：硬线屏蔽控制寄存器0。
   位域定义UNION结构:  PMIC_HARDWIRE_CTRL0_UNION */
#define PMIC_HARDWIRE_CTRL0_ADDR(base)            ((base) + (0x0C5))

/* 寄存器说明：硬线屏蔽控制寄存器1。
   位域定义UNION结构:  PMIC_HARDWIRE_CTRL1_UNION */
#define PMIC_HARDWIRE_CTRL1_ADDR(base)            ((base) + (0x0C6))

/* 寄存器说明：peri硬线控制寄存器0。
   位域定义UNION结构:  PMIC_PERI_CTRL0_UNION */
#define PMIC_PERI_CTRL0_ADDR(base)                ((base) + (0x0C7))

/* 寄存器说明：peri硬线控制寄存器1。
   位域定义UNION结构:  PMIC_PERI_CTRL1_UNION */
#define PMIC_PERI_CTRL1_ADDR(base)                ((base) + (0x0C8))

/* 寄存器说明：peri硬线调压寄存器。
   位域定义UNION结构:  PMIC_PERI_VSET_CTRL_UNION */
#define PMIC_PERI_VSET_CTRL_ADDR(base)            ((base) + (0x0C9))

/* 寄存器说明：peri硬线时间间隔控制寄存器。
   位域定义UNION结构:  PMIC_PERI_TIME__CTRL_UNION */
#define PMIC_PERI_TIME__CTRL_ADDR(base)           ((base) + (0x0CA))

/* 寄存器说明：热复位下电控制寄存器。
   位域定义UNION结构:  PMIC_HRESET_PWRDOWN_CTRL_UNION */
#define PMIC_HRESET_PWRDOWN_CTRL_ADDR(base)       ((base) + (0x0CB))

/* 寄存器说明：32kHz时钟输出使能控制寄存器。
   位域定义UNION结构:  PMIC_OSC32K_ONOFF_CTRL_UNION */
#define PMIC_OSC32K_ONOFF_CTRL_ADDR(base)         ((base) + (0x0CC))

/* 寄存器说明：OCP和SPC滤波时间控制寄存器。
   位域定义UNION结构:  PMIC_OCP_DEB_CTRL_UNION */
#define PMIC_OCP_DEB_CTRL_ADDR(base)              ((base) + (0x0CD))

/* 寄存器说明：OCP和DOCP滤波开关寄存器。
   位域定义UNION结构:  PMIC_OCP_SCP_ONOFF_UNION */
#define PMIC_OCP_SCP_ONOFF_ADDR(base)             ((base) + (0x0CE))

/* 寄存器说明：欠压告警和欠压关机滤波时间选择寄存器。
   位域定义UNION结构:  PMIC_UV_VSYS_DEB_CTRL_UNION */
#define PMIC_UV_VSYS_DEB_CTRL_ADDR(base)          ((base) + (0x0CF))

/* 寄存器说明：BUCK0/1/2/3 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_BUCK0_3_OCP_CTRL_UNION */
#define PMIC_BUCK0_3_OCP_CTRL_ADDR(base)          ((base) + (0x0D0))

/* 寄存器说明：BUCK4/LDO0/1/2 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_BUCK4_LDO0_1_OCP_CTRL_UNION */
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ADDR(base)     ((base) + (0x0D1))

/* 寄存器说明：LCO3/4/5/7 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO3_7_OCP_CTRL_UNION */
#define PMIC_LDO3_7_OCP_CTRL_ADDR(base)           ((base) + (0x0D2))

/* 寄存器说明：LDO8/9/10/11 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO8_11_OCP_CTRL_UNION */
#define PMIC_LDO8_11_OCP_CTRL_ADDR(base)          ((base) + (0x0D3))

/* 寄存器说明：LDO12/13/14/15 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO12_15_OCP_CTRL_UNION */
#define PMIC_LDO12_15_OCP_CTRL_ADDR(base)         ((base) + (0x0D4))

/* 寄存器说明：LDO16/17/19/20 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO16_20_OCP_CTRL_UNION */
#define PMIC_LDO16_20_OCP_CTRL_ADDR(base)         ((base) + (0x0D5))

/* 寄存器说明：LDO21/22/23/24 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO21_24_OCP_CTRL_UNION */
#define PMIC_LDO21_24_OCP_CTRL_ADDR(base)         ((base) + (0x0D6))

/* 寄存器说明：LDO25/26/27/28 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO25_28_OCP_CTRL_UNION */
#define PMIC_LDO25_28_OCP_CTRL_ADDR(base)         ((base) + (0x0D7))

/* 寄存器说明：LDO29/30/31/32 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO29_32_OCP_CTRL_UNION */
#define PMIC_LDO29_32_OCP_CTRL_ADDR(base)         ((base) + (0x0D8))

/* 寄存器说明：CLASS/BUCK0 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_CLASS_BUCK0_SCP_CTRL_UNION */
#define PMIC_CLASS_BUCK0_SCP_CTRL_ADDR(base)      ((base) + (0x0D9))

/* 寄存器说明：BUCK1/2/3/4 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_BUCK1_4_SCP_CTRL_UNION */
#define PMIC_BUCK1_4_SCP_CTRL_ADDR(base)          ((base) + (0x0DA))

/* 寄存器说明：系统控制寄存器0。
   位域定义UNION结构:  PMIC_SYS_CTRL0_UNION */
#define PMIC_SYS_CTRL0_ADDR(base)                 ((base) + (0x0DB))

/* 寄存器说明：系统控制寄存器1。
   位域定义UNION结构:  PMIC_SYS_CTRL1_UNION */
#define PMIC_SYS_CTRL1_ADDR(base)                 ((base) + (0x0DC))

/* 寄存器说明：库仑计ECO使能控制寄存器。
   位域定义UNION结构:  PMIC_COUL_ECO_MASK_UNION */
#define PMIC_COUL_ECO_MASK_ADDR(base)             ((base) + (0x0DD))

/* 寄存器说明：SIM控制寄存器。
   位域定义UNION结构:  PMIC_SIM_CTRL_UNION */
#define PMIC_SIM_CTRL_ADDR(base)                  ((base) + (0x0DE))

/* 寄存器说明：SIM滤波控制寄存器。
   位域定义UNION结构:  PMIC_SIM_DEB_CTRL_UNION */
#define PMIC_SIM_DEB_CTRL_ADDR(base)              ((base) + (0x0DF))

/* 寄存器说明：DAC IBIAS配置寄存器。
   位域定义UNION结构:  PMIC_AUX_IBIAS_CFG_UNION */
#define PMIC_AUX_IBIAS_CFG_ADDR(base)             ((base) + (0x0E0))

/* 寄存器说明：IRQ_MASK0控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_0_UNION */
#define PMIC_IRQ_MASK_0_ADDR(base)                ((base) + (0x0E1))

/* 寄存器说明：IRQ_MASK1控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_1_UNION */
#define PMIC_IRQ_MASK_1_ADDR(base)                ((base) + (0x0E2))

/* 寄存器说明：IRQ_MASK2控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_2_UNION */
#define PMIC_IRQ_MASK_2_ADDR(base)                ((base) + (0x0E3))

/* 寄存器说明：IRQ_MASK3控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_3_UNION */
#define PMIC_IRQ_MASK_3_ADDR(base)                ((base) + (0x0E4))

/* 寄存器说明：IRQ_MASK4控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_4_UNION */
#define PMIC_IRQ_MASK_4_ADDR(base)                ((base) + (0x0E5))

/* 寄存器说明：IRQ_MASK5控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_5_UNION */
#define PMIC_IRQ_MASK_5_ADDR(base)                ((base) + (0x0E6))

/* 寄存器说明：IRQ_MASK6控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_6_UNION */
#define PMIC_IRQ_MASK_6_ADDR(base)                ((base) + (0x0E7))

/* 寄存器说明：IRQ_MASK7控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_7_UNION */
#define PMIC_IRQ_MASK_7_ADDR(base)                ((base) + (0x0E8))

/* 寄存器说明：IRQ_MASK8控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_8_UNION */
#define PMIC_IRQ_MASK_8_ADDR(base)                ((base) + (0x0E9))

/* 寄存器说明：IRQ_MASK9控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_9_UNION */
#define PMIC_IRQ_MASK_9_ADDR(base)                ((base) + (0x0EA))

/* 寄存器说明：OTP0回读寄存器0。
   位域定义UNION结构:  PMIC_OTP0_0_UNION */
#define PMIC_OTP0_0_ADDR(base)                    ((base) + (0x0EB))

/* 寄存器说明：OTP0回读寄存器1。
   位域定义UNION结构:  PMIC_OTP0_1_UNION */
#define PMIC_OTP0_1_ADDR(base)                    ((base) + (0x0EC))

/* 寄存器说明：OTP0回读寄存器2。
   位域定义UNION结构:  PMIC_OTP0_2_UNION */
#define PMIC_OTP0_2_ADDR(base)                    ((base) + (0x0ED))

/* 寄存器说明：OTP0回读寄存器3。
   位域定义UNION结构:  PMIC_OTP0_3_UNION */
#define PMIC_OTP0_3_ADDR(base)                    ((base) + (0x0EE))

/* 寄存器说明：OTP0控制寄存器0。
   位域定义UNION结构:  PMIC_OTP0_CTRL_0_UNION */
#define PMIC_OTP0_CTRL_0_ADDR(base)               ((base) + (0x0EF))

/* 寄存器说明：OTP0控制寄存器1。
   位域定义UNION结构:  PMIC_OTP0_CTRL_1_UNION */
#define PMIC_OTP0_CTRL_1_ADDR(base)               ((base) + (0x0F0))

/* 寄存器说明：OTP0写操作数据寄存器。
   位域定义UNION结构:  PMIC_OTP0_WDATA_UNION */
#define PMIC_OTP0_WDATA_ADDR(base)                ((base) + (0x0F1))

/* 寄存器说明：OTP0或操作寄存器0
   位域定义UNION结构:  PMIC_OTP0_0_W_UNION */
#define PMIC_OTP0_0_W_ADDR(base)                  ((base) + (0x0F2))

/* 寄存器说明：OTP0或操作寄存器1
   位域定义UNION结构:  PMIC_OTP0_1_W_UNION */
#define PMIC_OTP0_1_W_ADDR(base)                  ((base) + (0x0F3))

/* 寄存器说明：OTP0或操作寄存器2
   位域定义UNION结构:  PMIC_OTP0_2_W_UNION */
#define PMIC_OTP0_2_W_ADDR(base)                  ((base) + (0x0F4))

/* 寄存器说明：OTP0或操作寄存器3
   位域定义UNION结构:  PMIC_OTP0_3_W_UNION */
#define PMIC_OTP0_3_W_ADDR(base)                  ((base) + (0x0F5))

/* 寄存器说明：OTP1回读寄存器0。
   位域定义UNION结构:  PMIC_OTP1_0_UNION */
#define PMIC_OTP1_0_ADDR(base)                    ((base) + (0x0F6))

/* 寄存器说明：OTP1回读寄存器1。
   位域定义UNION结构:  PMIC_OTP1_1_UNION */
#define PMIC_OTP1_1_ADDR(base)                    ((base) + (0x0F7))

/* 寄存器说明：OTP1回读寄存器2。
   位域定义UNION结构:  PMIC_OTP1_2_UNION */
#define PMIC_OTP1_2_ADDR(base)                    ((base) + (0x0F8))

/* 寄存器说明：OTP1回读寄存器3。
   位域定义UNION结构:  PMIC_OTP1_3_UNION */
#define PMIC_OTP1_3_ADDR(base)                    ((base) + (0x0F9))

/* 寄存器说明：OTP1控制寄存器0。
   位域定义UNION结构:  PMIC_OTP1_CTRL_0_UNION */
#define PMIC_OTP1_CTRL_0_ADDR(base)               ((base) + (0x0FA))

/* 寄存器说明：OTP1控制寄存器1。
   位域定义UNION结构:  PMIC_OTP1_CTRL_1_UNION */
#define PMIC_OTP1_CTRL_1_ADDR(base)               ((base) + (0x0FB))

/* 寄存器说明：OTP0写操作数据寄存器。
   位域定义UNION结构:  PMIC_OTP1_WDATA_UNION */
#define PMIC_OTP1_WDATA_ADDR(base)                ((base) + (0x0FC))

/* 寄存器说明：OTP1或操作寄存器0。
   位域定义UNION结构:  PMIC_OTP1_0_W_UNION */
#define PMIC_OTP1_0_W_ADDR(base)                  ((base) + (0x0FD))

/* 寄存器说明：OTP1或操作寄存器1。
   位域定义UNION结构:  PMIC_OTP1_1_W_UNION */
#define PMIC_OTP1_1_W_ADDR(base)                  ((base) + (0x0FE))

/* 寄存器说明：OTP1或操作寄存器2。
   位域定义UNION结构:  PMIC_OTP1_2_W_UNION */
#define PMIC_OTP1_2_W_ADDR(base)                  ((base) + (0x0FF))

/* 寄存器说明：OTP1或操作寄存器3。
   位域定义UNION结构:  PMIC_OTP1_3_W_UNION */
#define PMIC_OTP1_3_W_ADDR(base)                  ((base) + (0x100))

/* 寄存器说明：RESETIN_N复位信息寄存器0。
   位域定义UNION结构:  PMIC_HRST_REG0_UNION */
#define PMIC_HRST_REG0_ADDR(base)                 ((base) + (0x101))

/* 寄存器说明：RESETIN_N复位信息寄存器1。
   位域定义UNION结构:  PMIC_HRST_REG1_UNION */
#define PMIC_HRST_REG1_ADDR(base)                 ((base) + (0x102))

/* 寄存器说明：RESETIN_N复位信息寄存器2。
   位域定义UNION结构:  PMIC_HRST_REG2_UNION */
#define PMIC_HRST_REG2_ADDR(base)                 ((base) + (0x103))

/* 寄存器说明：SOFT复位信息寄存器。
   位域定义UNION结构:  PMIC_SOFT_RST_REG_UNION */
#define PMIC_SOFT_RST_REG_ADDR(base)              ((base) + (0x104))

/* 寄存器说明：时钟控制寄存器0。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL0_UNION */
#define PMIC_CLK_TOP_CTRL0_ADDR(base)             ((base) + (0x105))

/* 寄存器说明：时钟控制寄存器1。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL1_UNION */
#define PMIC_CLK_TOP_CTRL1_ADDR(base)             ((base) + (0x106))

/* 寄存器说明：时钟控制寄存器2。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL2_UNION */
#define PMIC_CLK_TOP_CTRL2_ADDR(base)             ((base) + (0x107))

/* 寄存器说明：时钟控制寄存器3。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL3_UNION */
#define PMIC_CLK_TOP_CTRL3_ADDR(base)             ((base) + (0x108))

/* 寄存器说明：时钟控制寄存器4。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL4_UNION */
#define PMIC_CLK_TOP_CTRL4_ADDR(base)             ((base) + (0x109))

/* 寄存器说明：时钟控制寄存器5。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL5_UNION */
#define PMIC_CLK_TOP_CTRL5_ADDR(base)             ((base) + (0x10A))

/* 寄存器说明：时钟控制寄存器6。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL6_UNION */
#define PMIC_CLK_TOP_CTRL6_ADDR(base)             ((base) + (0x10B))

/* 寄存器说明：时钟控制寄存器7。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL7_UNION */
#define PMIC_CLK_TOP_CTRL7_ADDR(base)             ((base) + (0x10C))

/* 寄存器说明：256K RC控制寄存器0。
   位域定义UNION结构:  PMIC_CLK_256K_CTRL0_UNION */
#define PMIC_CLK_256K_CTRL0_ADDR(base)            ((base) + (0x10D))

/* 寄存器说明：256K RC控制寄存器1。
   位域定义UNION结构:  PMIC_CLK_256K_CTRL1_UNION */
#define PMIC_CLK_256K_CTRL1_ADDR(base)            ((base) + (0x10E))

/* 寄存器说明：时钟控制预留寄存器0。
   位域定义UNION结构:  PMIC_CLK_TOP_RESERVE0_UNION */
#define PMIC_CLK_TOP_RESERVE0_ADDR(base)          ((base) + (0x10F))

/* 寄存器说明：时钟控制预留寄存器1。
   位域定义UNION结构:  PMIC_CLK_TOP_RESERVE1_UNION */
#define PMIC_CLK_TOP_RESERVE1_ADDR(base)          ((base) + (0x110))

/* 寄存器说明：数字系统debug预留寄存器0。
   位域定义UNION结构:  PMIC_SYS_DEBUG0_UNION */
#define PMIC_SYS_DEBUG0_ADDR(base)                ((base) + (0x111))

/* 寄存器说明：数字系统debug预留寄存器1。
   位域定义UNION结构:  PMIC_SYS_DEBUG1_UNION */
#define PMIC_SYS_DEBUG1_ADDR(base)                ((base) + (0x112))

/* 寄存器说明：DAC0 din高位映射寄存器。
   位域定义UNION结构:  PMIC_DAC0_DIN_MSB_UNION */
#define PMIC_DAC0_DIN_MSB_ADDR(base)              ((base) + (0x113))

/* 寄存器说明：DAC0 din低位映射寄存器。
   位域定义UNION结构:  PMIC_DAC0_DIN_LSB_UNION */
#define PMIC_DAC0_DIN_LSB_ADDR(base)              ((base) + (0x114))

/* 寄存器说明：DAC1 din高位映射寄存器。
   位域定义UNION结构:  PMIC_DAC1_DIN_MSB_UNION */
#define PMIC_DAC1_DIN_MSB_ADDR(base)              ((base) + (0x115))

/* 寄存器说明：DAC1 din低位映射寄存器。
   位域定义UNION结构:  PMIC_DAC1_DIN_LSB_UNION */
#define PMIC_DAC1_DIN_LSB_ADDR(base)              ((base) + (0x116))

/* 寄存器说明：xo_core_en,xo_ldo_en,eco_in_n寄存器写屏蔽控制寄存器。
   位域定义UNION结构:  PMIC_CORE_LDO_ECO_LOCK_UNION */
#define PMIC_CORE_LDO_ECO_LOCK_ADDR(base)         ((base) + (0x117))



/****************************************************************************
                     (2/5) PMU_IRQ
 ****************************************************************************/
/* 寄存器说明：BUKC0-4，LDO0-2 OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP0_UNION */
#define PMIC_NP_OCP0_ADDR(base)                   ((base) + (0x11A))

/* 寄存器说明：LDO3-11 OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP1_UNION */
#define PMIC_NP_OCP1_ADDR(base)                   ((base) + (0x11B))

/* 寄存器说明：LDO12-20 OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP2_UNION */
#define PMIC_NP_OCP2_ADDR(base)                   ((base) + (0x11C))

/* 寄存器说明：LDO21-28 OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP3_UNION */
#define PMIC_NP_OCP3_ADDR(base)                   ((base) + (0x11D))

/* 寄存器说明：LDO29-32 CLASSD OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP4_UNION */
#define PMIC_NP_OCP4_ADDR(base)                   ((base) + (0x11E))

/* 寄存器说明：BUCK0-4 SCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_SCP_UNION */
#define PMIC_NP_SCP_ADDR(base)                    ((base) + (0x11F))

/* 寄存器说明：中断寄存器0。
   位域定义UNION结构:  PMIC_IRQ0_UNION */
#define PMIC_IRQ0_ADDR(base)                      ((base) + (0x120))

/* 寄存器说明：中断寄存器1。
   位域定义UNION结构:  PMIC_IRQ1_UNION */
#define PMIC_IRQ1_ADDR(base)                      ((base) + (0x121))

/* 寄存器说明：中断寄存器2。
   位域定义UNION结构:  PMIC_IRQ2_UNION */
#define PMIC_IRQ2_ADDR(base)                      ((base) + (0x122))

/* 寄存器说明：中断寄存器3。
   位域定义UNION结构:  PMIC_IRQ3_UNION */
#define PMIC_IRQ3_ADDR(base)                      ((base) + (0x123))

/* 寄存器说明：OCP中断寄存器0。
   位域定义UNION结构:  PMIC_OCP_IRQ0_UNION */
#define PMIC_OCP_IRQ0_ADDR(base)                  ((base) + (0x124))

/* 寄存器说明：OCP中断寄存器1。
   位域定义UNION结构:  PMIC_OCP_IRQ1_UNION */
#define PMIC_OCP_IRQ1_ADDR(base)                  ((base) + (0x125))

/* 寄存器说明：OCP中断寄存器3。
   位域定义UNION结构:  PMIC_OCP_IRQ2_UNION */
#define PMIC_OCP_IRQ2_ADDR(base)                  ((base) + (0x126))

/* 寄存器说明：OCP中断寄存器4。
   位域定义UNION结构:  PMIC_OCP_IRQ3_UNION */
#define PMIC_OCP_IRQ3_ADDR(base)                  ((base) + (0x127))

/* 寄存器说明：OCP中断寄存器5。
   位域定义UNION结构:  PMIC_OCP_IRQ4_UNION */
#define PMIC_OCP_IRQ4_ADDR(base)                  ((base) + (0x128))

/* 寄存器说明：OCP中断寄存器6。
   位域定义UNION结构:  PMIC_OCP_IRQ5_UNION */
#define PMIC_OCP_IRQ5_ADDR(base)                  ((base) + (0x129))

/* 寄存器说明：事件记录寄存器0。
   位域定义UNION结构:  PMIC_NP_RECORD0_UNION */
#define PMIC_NP_RECORD0_ADDR(base)                ((base) + (0x12A))

/* 寄存器说明：事件记录寄存器1。
   位域定义UNION结构:  PMIC_NP_RECORD1_UNION */
#define PMIC_NP_RECORD1_ADDR(base)                ((base) + (0x12B))



/****************************************************************************
                     (3/5) PMU_RTC
 ****************************************************************************/
/* 寄存器说明：RTC当前时间寄存器bit[7:0]。
   位域定义UNION结构:  PMIC_RTCDR0_UNION */
#define PMIC_RTCDR0_ADDR(base)                    ((base) + (0x12C))

/* 寄存器说明：RTC当前时间寄存器bit[15:8]。
   位域定义UNION结构:  PMIC_RTCDR1_UNION */
#define PMIC_RTCDR1_ADDR(base)                    ((base) + (0x12D))

/* 寄存器说明：RTC当前时间寄存器bit[23:16]。
   位域定义UNION结构:  PMIC_RTCDR2_UNION */
#define PMIC_RTCDR2_ADDR(base)                    ((base) + (0x12E))

/* 寄存器说明：RTC当前时间寄存器bit[31:24]。
   位域定义UNION结构:  PMIC_RTCDR3_UNION */
#define PMIC_RTCDR3_ADDR(base)                    ((base) + (0x12F))

/* 寄存器说明：RTC比较寄存器bit[7:0]。
   位域定义UNION结构:  PMIC_RTCMR0_UNION */
#define PMIC_RTCMR0_ADDR(base)                    ((base) + (0x130))

/* 寄存器说明：RTC比较寄存器bit[15:8]。
   位域定义UNION结构:  PMIC_RTCMR1_UNION */
#define PMIC_RTCMR1_ADDR(base)                    ((base) + (0x131))

/* 寄存器说明：RTC比较寄存器bit[23:16]。
   位域定义UNION结构:  PMIC_RTCMR2_UNION */
#define PMIC_RTCMR2_ADDR(base)                    ((base) + (0x132))

/* 寄存器说明：RTC比较寄存器bit[31:24]。
   位域定义UNION结构:  PMIC_RTCMR3_UNION */
#define PMIC_RTCMR3_ADDR(base)                    ((base) + (0x133))

/* 寄存器说明：RTC加载寄存器bit[7:0]。
   位域定义UNION结构:  PMIC_RTCLR0_UNION */
#define PMIC_RTCLR0_ADDR(base)                    ((base) + (0x134))

/* 寄存器说明：RTC加载寄存器bit[15:8]。
   位域定义UNION结构:  PMIC_RTCLR1_UNION */
#define PMIC_RTCLR1_ADDR(base)                    ((base) + (0x135))

/* 寄存器说明：RTC加载寄存器bit[23:16]。
   位域定义UNION结构:  PMIC_RTCLR2_UNION */
#define PMIC_RTCLR2_ADDR(base)                    ((base) + (0x136))

/* 寄存器说明：RTC加载寄存器bit[31:24]。
   位域定义UNION结构:  PMIC_RTCLR3_UNION */
#define PMIC_RTCLR3_ADDR(base)                    ((base) + (0x137))

/* 寄存器说明：RTC控制寄存器。
   位域定义UNION结构:  PMIC_RTCCTRL_UNION */
#define PMIC_RTCCTRL_ADDR(base)                   ((base) + (0x138))

/* 寄存器说明：XO_THRESOLD[7:0]寄存器。
   位域定义UNION结构:  PMIC_XO_THRESOLD0_UNION */
#define PMIC_XO_THRESOLD0_ADDR(base)              ((base) + (0x139))

/* 寄存器说明：XO_THRESOLD[15:8]寄存器。
   位域定义UNION结构:  PMIC_XO_THRESOLD1_UNION */
#define PMIC_XO_THRESOLD1_ADDR(base)              ((base) + (0x13A))

/* 寄存器说明：CRC_VALUE[7:0]寄存器。
   位域定义UNION结构:  PMIC_CRC_VAULE0_UNION */
#define PMIC_CRC_VAULE0_ADDR(base)                ((base) + (0x13B))

/* 寄存器说明：CRC_VALUE[15:8]寄存器。
   位域定义UNION结构:  PMIC_CRC_VAULE1_UNION */
#define PMIC_CRC_VAULE1_ADDR(base)                ((base) + (0x13C))

/* 寄存器说明：CRC_VALUE[20:16]寄存器。
   位域定义UNION结构:  PMIC_CRC_VAULE2_UNION */
#define PMIC_CRC_VAULE2_ADDR(base)                ((base) + (0x13D))

/* 寄存器说明：RTC上电拍照[7:0]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRUP_TIMER0_UNION */
#define PMIC_RTC_PWRUP_TIMER0_ADDR(base)          ((base) + (0x13E))

/* 寄存器说明：RTC上电拍照[15:8]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRUP_TIMER1_UNION */
#define PMIC_RTC_PWRUP_TIMER1_ADDR(base)          ((base) + (0x13F))

/* 寄存器说明：RTC上电拍照[23:16]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRUP_TIMER2_UNION */
#define PMIC_RTC_PWRUP_TIMER2_ADDR(base)          ((base) + (0x140))

/* 寄存器说明：RTC上电拍照[31:24]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRUP_TIMER3_UNION */
#define PMIC_RTC_PWRUP_TIMER3_ADDR(base)          ((base) + (0x141))

/* 寄存器说明：RTC下电拍照[7:0]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRDOWN_TIMER0_UNION */
#define PMIC_RTC_PWRDOWN_TIMER0_ADDR(base)        ((base) + (0x142))

/* 寄存器说明：RTC下电拍照[15:8]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRDOWN_TIMER1_UNION */
#define PMIC_RTC_PWRDOWN_TIMER1_ADDR(base)        ((base) + (0x143))

/* 寄存器说明：RTC下电拍照[23:16]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRDOWN_TIMER2_UNION */
#define PMIC_RTC_PWRDOWN_TIMER2_ADDR(base)        ((base) + (0x144))

/* 寄存器说明：RTC下电拍照[31:24]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRDOWN_TIMER3_UNION */
#define PMIC_RTC_PWRDOWN_TIMER3_ADDR(base)        ((base) + (0x145))



/****************************************************************************
                     (4/5) PMU_COUL
 ****************************************************************************/
/* 寄存器说明：库仑计中断寄存器。
   位域定义UNION结构:  PMIC_COUL_IRQ_UNION */
#define PMIC_COUL_IRQ_ADDR(base)                  ((base) + (0x14B))

/* 寄存器说明：库仑计中断屏蔽寄存器。
   位域定义UNION结构:  PMIC_COUL_IRQ_MASK_UNION */
#define PMIC_COUL_IRQ_MASK_ADDR(base)             ((base) + (0x14C))

/* 寄存器说明：当前电流[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT_0_UNION */
#define PMIC_CURRENT_0_ADDR(base)                 ((base) + (0x14D))

/* 寄存器说明：当前电流[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT_1_UNION */
#define PMIC_CURRENT_1_ADDR(base)                 ((base) + (0x14E))

/* 寄存器说明：当前电压[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT_0_UNION */
#define PMIC_V_OUT_0_ADDR(base)                   ((base) + (0x14F))

/* 寄存器说明：当前电压[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT_1_UNION */
#define PMIC_V_OUT_1_ADDR(base)                   ((base) + (0x150))

/* 寄存器说明：库仑计控制寄存器。
   位域定义UNION结构:  PMIC_CLJ_CTRL_REG_UNION */
#define PMIC_CLJ_CTRL_REG_ADDR(base)              ((base) + (0x151))

/* 寄存器说明：ECO_REFLASH工作时间寄存器。
   位域定义UNION结构:  PMIC_ECO_REFALSH_TIME_UNION */
#define PMIC_ECO_REFALSH_TIME_ADDR(base)          ((base) + (0x152))

/* 寄存器说明：cl_out[7:0]寄存器。
   位域定义UNION结构:  PMIC_CL_OUT0_UNION */
#define PMIC_CL_OUT0_ADDR(base)                   ((base) + (0x153))

/* 寄存器说明：cl_out[15:8]寄存器。
   位域定义UNION结构:  PMIC_CL_OUT1_UNION */
#define PMIC_CL_OUT1_ADDR(base)                   ((base) + (0x154))

/* 寄存器说明：cl_out[23:16]寄存器。
   位域定义UNION结构:  PMIC_CL_OUT2_UNION */
#define PMIC_CL_OUT2_ADDR(base)                   ((base) + (0x155))

/* 寄存器说明：cl_out[31:24]寄存器。
   位域定义UNION结构:  PMIC_CL_OUT3_UNION */
#define PMIC_CL_OUT3_ADDR(base)                   ((base) + (0x156))

/* 寄存器说明：cl_in[7:0]寄存器。
   位域定义UNION结构:  PMIC_CL_IN0_UNION */
#define PMIC_CL_IN0_ADDR(base)                    ((base) + (0x157))

/* 寄存器说明：cl_in[15:8]寄存器。
   位域定义UNION结构:  PMIC_CL_IN1_UNION */
#define PMIC_CL_IN1_ADDR(base)                    ((base) + (0x158))

/* 寄存器说明：cl_in[23:16]寄存器。
   位域定义UNION结构:  PMIC_CL_IN2_UNION */
#define PMIC_CL_IN2_ADDR(base)                    ((base) + (0x159))

/* 寄存器说明：cl_in[31:24]寄存器。
   位域定义UNION结构:  PMIC_CL_IN3_UNION */
#define PMIC_CL_IN3_ADDR(base)                    ((base) + (0x15A))

/* 寄存器说明：chg_timer[7:0]寄存器。
   位域定义UNION结构:  PMIC_CHG_TIMER0_UNION */
#define PMIC_CHG_TIMER0_ADDR(base)                ((base) + (0x15B))

/* 寄存器说明：chg_timer[15:8]寄存器。
   位域定义UNION结构:  PMIC_CHG_TIMER1_UNION */
#define PMIC_CHG_TIMER1_ADDR(base)                ((base) + (0x15C))

/* 寄存器说明：chg_timer[23:16]寄存器。
   位域定义UNION结构:  PMIC_CHG_TIMER2_UNION */
#define PMIC_CHG_TIMER2_ADDR(base)                ((base) + (0x15D))

/* 寄存器说明：chg_timer[31:24]寄存器。
   位域定义UNION结构:  PMIC_CHG_TIMER3_UNION */
#define PMIC_CHG_TIMER3_ADDR(base)                ((base) + (0x15E))

/* 寄存器说明：load_timer[7:0]寄存器。
   位域定义UNION结构:  PMIC_LOAD_TIMER0_UNION */
#define PMIC_LOAD_TIMER0_ADDR(base)               ((base) + (0x15F))

/* 寄存器说明：load_timer[15:8]寄存器。
   位域定义UNION结构:  PMIC_LOAD_TIMER1_UNION */
#define PMIC_LOAD_TIMER1_ADDR(base)               ((base) + (0x160))

/* 寄存器说明：load_timer[23:16]寄存器。
   位域定义UNION结构:  PMIC_LOAD_TIMER2_UNION */
#define PMIC_LOAD_TIMER2_ADDR(base)               ((base) + (0x161))

/* 寄存器说明：load_timer[31:24]寄存器。
   位域定义UNION结构:  PMIC_LOAD_TIMER3_UNION */
#define PMIC_LOAD_TIMER3_ADDR(base)               ((base) + (0x162))

/* 寄存器说明：cl_int[7:0]寄存器。
   位域定义UNION结构:  PMIC_CL_INT0_UNION */
#define PMIC_CL_INT0_ADDR(base)                   ((base) + (0x163))

/* 寄存器说明：cl_int[15:8]寄存器。
   位域定义UNION结构:  PMIC_CL_INT1_UNION */
#define PMIC_CL_INT1_ADDR(base)                   ((base) + (0x164))

/* 寄存器说明：cl_int[23:16]寄存器。
   位域定义UNION结构:  PMIC_CL_INT2_UNION */
#define PMIC_CL_INT2_ADDR(base)                   ((base) + (0x165))

/* 寄存器说明：cl_int[31:24]寄存器。
   位域定义UNION结构:  PMIC_CL_INT3_UNION */
#define PMIC_CL_INT3_ADDR(base)                   ((base) + (0x166))

/* 寄存器说明：v_int[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_INT0_UNION */
#define PMIC_V_INT0_ADDR(base)                    ((base) + (0x167))

/* 寄存器说明：v_int[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_INT1_UNION */
#define PMIC_V_INT1_ADDR(base)                    ((base) + (0x168))

/* 寄存器说明：offset_current[7:0]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_CURRENT0_UNION */
#define PMIC_OFFSET_CURRENT0_ADDR(base)           ((base) + (0x169))

/* 寄存器说明：offset_current[15:8]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_CURRENT1_UNION */
#define PMIC_OFFSET_CURRENT1_ADDR(base)           ((base) + (0x16A))

/* 寄存器说明：offset_voltage[7:0]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_VOLTAGE0_UNION */
#define PMIC_OFFSET_VOLTAGE0_ADDR(base)           ((base) + (0x16B))

/* 寄存器说明：offset_voltage[15:8]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_VOLTAGE1_UNION */
#define PMIC_OFFSET_VOLTAGE1_ADDR(base)           ((base) + (0x16C))

/* 寄存器说明：v_ocv_data[7:0]寄存器。
   位域定义UNION结构:  PMIC_OCV_VOLTAGE0_UNION */
#define PMIC_OCV_VOLTAGE0_ADDR(base)              ((base) + (0x16D))

/* 寄存器说明：v_ocv_data[15:8]寄存器。
   位域定义UNION结构:  PMIC_OCV_VOLTAGE1_UNION */
#define PMIC_OCV_VOLTAGE1_ADDR(base)              ((base) + (0x16E))

/* 寄存器说明：i_ocv_data[7:0]寄存器。
   位域定义UNION结构:  PMIC_OCV_CURRENT0_UNION */
#define PMIC_OCV_CURRENT0_ADDR(base)              ((base) + (0x16F))

/* 寄存器说明：i_ocv_data[15:8]寄存器。
   位域定义UNION结构:  PMIC_OCV_CURRENT1_UNION */
#define PMIC_OCV_CURRENT1_ADDR(base)              ((base) + (0x170))

/* 寄存器说明：eco_out_clin[7:0]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLIN_0_UNION */
#define PMIC_ECO_OUT_CLIN_0_ADDR(base)            ((base) + (0x171))

/* 寄存器说明：eco_out_clin[15:8]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLIN_1_UNION */
#define PMIC_ECO_OUT_CLIN_1_ADDR(base)            ((base) + (0x172))

/* 寄存器说明：eco_out_clin[23:16]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLIN_2_UNION */
#define PMIC_ECO_OUT_CLIN_2_ADDR(base)            ((base) + (0x173))

/* 寄存器说明：eco_out_clin[31:24]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLIN_3_UNION */
#define PMIC_ECO_OUT_CLIN_3_ADDR(base)            ((base) + (0x174))

/* 寄存器说明：eco_out_clout[7:0]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLOUT_0_UNION */
#define PMIC_ECO_OUT_CLOUT_0_ADDR(base)           ((base) + (0x175))

/* 寄存器说明：eco_out_clout[15:8]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLOUT_1_UNION */
#define PMIC_ECO_OUT_CLOUT_1_ADDR(base)           ((base) + (0x176))

/* 寄存器说明：eco_out_clout[23:16]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLOUT_2_UNION */
#define PMIC_ECO_OUT_CLOUT_2_ADDR(base)           ((base) + (0x177))

/* 寄存器说明：eco_out_clout[31:24]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLOUT_3_UNION */
#define PMIC_ECO_OUT_CLOUT_3_ADDR(base)           ((base) + (0x178))

/* 寄存器说明：v_out_pre0[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE0_UNION */
#define PMIC_V_OUT0_PRE0_ADDR(base)               ((base) + (0x179))

/* 寄存器说明：v_out_pre0[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE0_UNION */
#define PMIC_V_OUT1_PRE0_ADDR(base)               ((base) + (0x17A))

/* 寄存器说明：v_out_pre1[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE1_UNION */
#define PMIC_V_OUT0_PRE1_ADDR(base)               ((base) + (0x17B))

/* 寄存器说明：v_out_pre1[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE1_UNION */
#define PMIC_V_OUT1_PRE1_ADDR(base)               ((base) + (0x17C))

/* 寄存器说明：v_out_pre2[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE2_UNION */
#define PMIC_V_OUT0_PRE2_ADDR(base)               ((base) + (0x17D))

/* 寄存器说明：v_out_pre2[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE2_UNION */
#define PMIC_V_OUT1_PRE2_ADDR(base)               ((base) + (0x17E))

/* 寄存器说明：v_out_pre3[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE3_UNION */
#define PMIC_V_OUT0_PRE3_ADDR(base)               ((base) + (0x17F))

/* 寄存器说明：v_out_pre3[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE3_UNION */
#define PMIC_V_OUT1_PRE3_ADDR(base)               ((base) + (0x180))

/* 寄存器说明：v_out_pre4[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE4_UNION */
#define PMIC_V_OUT0_PRE4_ADDR(base)               ((base) + (0x181))

/* 寄存器说明：v_out_pre4[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE4_UNION */
#define PMIC_V_OUT1_PRE4_ADDR(base)               ((base) + (0x182))

/* 寄存器说明：v_out_pre5[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE5_UNION */
#define PMIC_V_OUT0_PRE5_ADDR(base)               ((base) + (0x183))

/* 寄存器说明：v_out_pre5[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE5_UNION */
#define PMIC_V_OUT1_PRE5_ADDR(base)               ((base) + (0x184))

/* 寄存器说明：v_out_pre6[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE6_UNION */
#define PMIC_V_OUT0_PRE6_ADDR(base)               ((base) + (0x185))

/* 寄存器说明：v_out_pre6[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE6_UNION */
#define PMIC_V_OUT1_PRE6_ADDR(base)               ((base) + (0x186))

/* 寄存器说明：v_out_pre7[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE7_UNION */
#define PMIC_V_OUT0_PRE7_ADDR(base)               ((base) + (0x187))

/* 寄存器说明：v_out_pre7[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE7_UNION */
#define PMIC_V_OUT1_PRE7_ADDR(base)               ((base) + (0x188))

/* 寄存器说明：v_out_pre8[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE8_UNION */
#define PMIC_V_OUT0_PRE8_ADDR(base)               ((base) + (0x189))

/* 寄存器说明：v_out_pre8[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE8_UNION */
#define PMIC_V_OUT1_PRE8_ADDR(base)               ((base) + (0x18A))

/* 寄存器说明：v_out_pre9[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE9_UNION */
#define PMIC_V_OUT0_PRE9_ADDR(base)               ((base) + (0x18B))

/* 寄存器说明：v_out_pre9[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE9_UNION */
#define PMIC_V_OUT1_PRE9_ADDR(base)               ((base) + (0x18C))

/* 寄存器说明：current_pre0[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE0_UNION */
#define PMIC_CURRENT0_PRE0_ADDR(base)             ((base) + (0x18D))

/* 寄存器说明：current_pre0[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE0_UNION */
#define PMIC_CURRENT1_PRE0_ADDR(base)             ((base) + (0x18E))

/* 寄存器说明：current_pre1[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE1_UNION */
#define PMIC_CURRENT0_PRE1_ADDR(base)             ((base) + (0x18F))

/* 寄存器说明：current_pre1[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE1_UNION */
#define PMIC_CURRENT1_PRE1_ADDR(base)             ((base) + (0x190))

/* 寄存器说明：current_pre2[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE2_UNION */
#define PMIC_CURRENT0_PRE2_ADDR(base)             ((base) + (0x191))

/* 寄存器说明：current_pre2[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE2_UNION */
#define PMIC_CURRENT1_PRE2_ADDR(base)             ((base) + (0x192))

/* 寄存器说明：current_pre3[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE3_UNION */
#define PMIC_CURRENT0_PRE3_ADDR(base)             ((base) + (0x193))

/* 寄存器说明：current_pre3[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE3_UNION */
#define PMIC_CURRENT1_PRE3_ADDR(base)             ((base) + (0x194))

/* 寄存器说明：current_pre4[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE4_UNION */
#define PMIC_CURRENT0_PRE4_ADDR(base)             ((base) + (0x195))

/* 寄存器说明：current_pre4[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE4_UNION */
#define PMIC_CURRENT1_PRE4_ADDR(base)             ((base) + (0x196))

/* 寄存器说明：current_pre5[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE5_UNION */
#define PMIC_CURRENT0_PRE5_ADDR(base)             ((base) + (0x197))

/* 寄存器说明：current_pre5[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE5_UNION */
#define PMIC_CURRENT1_PRE5_ADDR(base)             ((base) + (0x198))

/* 寄存器说明：current_pre6[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE6_UNION */
#define PMIC_CURRENT0_PRE6_ADDR(base)             ((base) + (0x199))

/* 寄存器说明：current_pre6[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE6_UNION */
#define PMIC_CURRENT1_PRE6_ADDR(base)             ((base) + (0x19A))

/* 寄存器说明：current_pre7[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE7_UNION */
#define PMIC_CURRENT0_PRE7_ADDR(base)             ((base) + (0x19B))

/* 寄存器说明：current_pre7[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE7_UNION */
#define PMIC_CURRENT1_PRE7_ADDR(base)             ((base) + (0x19C))

/* 寄存器说明：current_pre8[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE8_UNION */
#define PMIC_CURRENT0_PRE8_ADDR(base)             ((base) + (0x19D))

/* 寄存器说明：current_pre8[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE8_UNION */
#define PMIC_CURRENT1_PRE8_ADDR(base)             ((base) + (0x19E))

/* 寄存器说明：current_pre9[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE9_UNION */
#define PMIC_CURRENT0_PRE9_ADDR(base)             ((base) + (0x19F))

/* 寄存器说明：current_pre9[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE9_UNION */
#define PMIC_CURRENT1_PRE9_ADDR(base)             ((base) + (0x1A0))

/* 寄存器说明：电流偏置调整[7:0]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_CURRENT_MOD_0_UNION */
#define PMIC_OFFSET_CURRENT_MOD_0_ADDR(base)      ((base) + (0x1A1))

/* 寄存器说明：电流偏置调整[15:8]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_CURRENT_MOD_1_UNION */
#define PMIC_OFFSET_CURRENT_MOD_1_ADDR(base)      ((base) + (0x1A2))

/* 寄存器说明：电压偏置调整[7:0]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_VOLTAGE_MOD_0_UNION */
#define PMIC_OFFSET_VOLTAGE_MOD_0_ADDR(base)      ((base) + (0x1A3))

/* 寄存器说明：电压偏置调整[15:8]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_VOLTAGE_MOD_1_UNION */
#define PMIC_OFFSET_VOLTAGE_MOD_1_ADDR(base)      ((base) + (0x1A4))

/* 寄存器说明：库仑计保留1寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED1_UNION */
#define PMIC_CLJ_RESERVED1_ADDR(base)             ((base) + (0x1A5))

/* 寄存器说明：库仑计保留2寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED2_UNION */
#define PMIC_CLJ_RESERVED2_ADDR(base)             ((base) + (0x1A6))

/* 寄存器说明：库仑计保留3寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED3_UNION */
#define PMIC_CLJ_RESERVED3_ADDR(base)             ((base) + (0x1A7))

/* 寄存器说明：库仑计保留4寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED4_UNION */
#define PMIC_CLJ_RESERVED4_ADDR(base)             ((base) + (0x1A8))

/* 寄存器说明：库仑计保留5寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED5_UNION */
#define PMIC_CLJ_RESERVED5_ADDR(base)             ((base) + (0x1A9))

/* 寄存器说明：库仑计保留6寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED6_UNION */
#define PMIC_CLJ_RESERVED6_ADDR(base)             ((base) + (0x1AA))

/* 寄存器说明：库仑计保留7寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED7_UNION */
#define PMIC_CLJ_RESERVED7_ADDR(base)             ((base) + (0x1AB))

/* 寄存器说明：PMU软复位寄存器。
   位域定义UNION结构:  PMIC_PMU_SOFT_RST_UNION */
#define PMIC_PMU_SOFT_RST_ADDR(base)              ((base) + (0x1AC))

/* 寄存器说明：库仑计DEBUG专用1寄存器。
   位域定义UNION结构:  PMIC_CLJ_DEBUG_UNION */
#define PMIC_CLJ_DEBUG_ADDR(base)                 ((base) + (0x1AD))

/* 寄存器说明：库仑计DEBUG专用2寄存器。
   位域定义UNION结构:  PMIC_CLJ_DEBUG_2_UNION */
#define PMIC_CLJ_DEBUG_2_ADDR(base)               ((base) + (0x1AE))

/* 寄存器说明：库仑计DEBUG专用3寄存器。
   位域定义UNION结构:  PMIC_STATE_TEST_UNION */
#define PMIC_STATE_TEST_ADDR(base)                ((base) + (0x1AF))

/* 寄存器说明：库仑计数模接口预留寄存器。
   位域定义UNION结构:  PMIC_COUL_RESERVE_UNION */
#define PMIC_COUL_RESERVE_ADDR(base)              ((base) + (0x1B0))

/* 寄存器说明：软件预留寄存器0。
   位域定义UNION结构:  PMIC_SOFT_RESERE0_UNION */
#define PMIC_SOFT_RESERE0_ADDR(base)              ((base) + (0x1B1))

/* 寄存器说明：软件预留寄存器1。
   位域定义UNION结构:  PMIC_SOFT_RESERE1_UNION */
#define PMIC_SOFT_RESERE1_ADDR(base)              ((base) + (0x1B2))

/* 寄存器说明：软件预留寄存器2。
   位域定义UNION结构:  PMIC_SOFT_RESERE2_UNION */
#define PMIC_SOFT_RESERE2_ADDR(base)              ((base) + (0x1B3))

/* 寄存器说明：软件预留寄存器3。
   位域定义UNION结构:  PMIC_SOFT_RESERE3_UNION */
#define PMIC_SOFT_RESERE3_ADDR(base)              ((base) + (0x1B4))

/* 寄存器说明：软件预留寄存器4。
   位域定义UNION结构:  PMIC_SOFT_RESERE4_UNION */
#define PMIC_SOFT_RESERE4_ADDR(base)              ((base) + (0x1B5))

/* 寄存器说明：软件预留寄存器5。
   位域定义UNION结构:  PMIC_SOFT_RESERE5_UNION */
#define PMIC_SOFT_RESERE5_ADDR(base)              ((base) + (0x1B6))

/* 寄存器说明：软件预留寄存器6。
   位域定义UNION结构:  PMIC_SOFT_RESERE6_UNION */
#define PMIC_SOFT_RESERE6_ADDR(base)              ((base) + (0x1B7))

/* 寄存器说明：软件预留寄存器7。
   位域定义UNION结构:  PMIC_SOFT_RESERE7_UNION */
#define PMIC_SOFT_RESERE7_ADDR(base)              ((base) + (0x1B8))



/****************************************************************************
                     (5/5) HKADC
 ****************************************************************************/
/* 寄存器说明：ADC控制寄存器。
   位域定义UNION结构:  PMIC_ADC_CTRL_UNION */
#define PMIC_ADC_CTRL_ADDR(base)                  ((base) + (0x00))

/* 寄存器说明：ADC转换开始寄存器。
   位域定义UNION结构:  PMIC_ADC_START_UNION */
#define PMIC_ADC_START_ADDR(base)                 ((base) + (0x01))

/* 寄存器说明：ADC转换状态指示寄存器。
   位域定义UNION结构:  PMIC_CONV_STATUS_UNION */
#define PMIC_CONV_STATUS_ADDR(base)               ((base) + (0x02))

/* 寄存器说明：ADC结果高位寄存器。
   位域定义UNION结构:  PMIC_ADC_DATA1_UNION */
#define PMIC_ADC_DATA1_ADDR(base)                 ((base) + (0x03))

/* 寄存器说明：ADC结果低位寄存器。
   位域定义UNION结构:  PMIC_ADC_DATA0_UNION */
#define PMIC_ADC_DATA0_ADDR(base)                 ((base) + (0x04))

/* 寄存器说明：ADC转换使能寄存器。
   位域定义UNION结构:  PMIC_ADC_CONV_UNION */
#define PMIC_ADC_CONV_ADDR(base)                  ((base) + (0x05))

/* 寄存器说明：ADCibas电流配置寄存器。
   位域定义UNION结构:  PMIC_ADC_CURRENT_UNION */
#define PMIC_ADC_CURRENT_ADDR(base)               ((base) + (0x06))

/* 寄存器说明：ADC校准配置控制寄存器。
   位域定义UNION结构:  PMIC_ADC_CALI_CTRL_UNION */
#define PMIC_ADC_CALI_CTRL_ADDR(base)             ((base) + (0x07))

/* 寄存器说明：ADC校准值寄存器。
   位域定义UNION结构:  PMIC_ADC_CALI_VALUE_UNION */
#define PMIC_ADC_CALI_VALUE_ADDR(base)            ((base) + (0x08))

/* 寄存器说明：ADC校准配置值寄存器。
   位域定义UNION结构:  PMIC_ADC_CALI_CFG_UNION */
#define PMIC_ADC_CALI_CFG_ADDR(base)              ((base) + (0x09))

/* 寄存器说明：HKADC预留寄存器。
   位域定义UNION结构:  PMIC_ADC_RSV0_UNION */
#define PMIC_ADC_RSV0_ADDR(base)                  ((base) + (0x0A))

/* 寄存器说明：HKADC预留寄存器。
   位域定义UNION结构:  PMIC_ADC_RSV1_UNION */
#define PMIC_ADC_RSV1_ADDR(base)                  ((base) + (0x0B))





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
                     (1/5) PMU_CTRL
 ****************************************************************************/
/*****************************************************************************
 结构名    : PMIC_VERSION0_UNION
 结构说明  : VERSION0 寄存器结构定义。地址偏移量:0x000，初值:0x36，宽度:8
 寄存器说明: 版本寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num0 : 8;  /* bit[0-7]: ASIC码36表示项目编号6。 */
    } reg;
} PMIC_VERSION0_UNION;
#endif
#define PMIC_VERSION0_project_num0_START  (0)
#define PMIC_VERSION0_project_num0_END    (7)


/*****************************************************************************
 结构名    : PMIC_VERSION1_UNION
 结构说明  : VERSION1 寄存器结构定义。地址偏移量:0x001，初值:0x34，宽度:8
 寄存器说明: 版本寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num1 : 8;  /* bit[0-7]: ASIC码34表示项目编号4。 */
    } reg;
} PMIC_VERSION1_UNION;
#endif
#define PMIC_VERSION1_project_num1_START  (0)
#define PMIC_VERSION1_project_num1_END    (7)


/*****************************************************************************
 结构名    : PMIC_VERSION2_UNION
 结构说明  : VERSION2 寄存器结构定义。地址偏移量:0x002，初值:0x32，宽度:8
 寄存器说明: 版本寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num2 : 8;  /* bit[0-7]: ASIC码32表示项目编号2。 */
    } reg;
} PMIC_VERSION2_UNION;
#endif
#define PMIC_VERSION2_project_num2_START  (0)
#define PMIC_VERSION2_project_num2_END    (7)


/*****************************************************************************
 结构名    : PMIC_VERSION3_UNION
 结构说明  : VERSION3 寄存器结构定义。地址偏移量:0x003，初值:0x31，宽度:8
 寄存器说明: 版本寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num3 : 8;  /* bit[0-7]: ASIC码31表示项目编号1。 */
    } reg;
} PMIC_VERSION3_UNION;
#endif
#define PMIC_VERSION3_project_num3_START  (0)
#define PMIC_VERSION3_project_num3_END    (7)


/*****************************************************************************
 结构名    : PMIC_VERSION4_UNION
 结构说明  : VERSION4 寄存器结构定义。地址偏移量:0x004，初值:0x05，宽度:8
 寄存器说明: 版本寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  version0 : 8;  /* bit[0-7]: 表示版本为V510的5。 */
    } reg;
} PMIC_VERSION4_UNION;
#endif
#define PMIC_VERSION4_version0_START  (0)
#define PMIC_VERSION4_version0_END    (7)


/*****************************************************************************
 结构名    : PMIC_VERSION5_UNION
 结构说明  : VERSION5 寄存器结构定义。地址偏移量:0x005，初值:0x00，宽度:8
 寄存器说明: 版本寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id : 8;  /* bit[0-7]: 表示版本为V510的10。 */
    } reg;
} PMIC_VERSION5_UNION;
#endif
#define PMIC_VERSION5_chip_id_START  (0)
#define PMIC_VERSION5_chip_id_END    (7)


/*****************************************************************************
 结构名    : PMIC_STATUS0_UNION
 结构说明  : STATUS0 寄存器结构定义。地址偏移量:0x006，初值:0x00，宽度:8
 寄存器说明: 状态标志寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_ov_d200ur        : 1;  /* bit[0]: 过压状态指示位(上升沿去抖200us)。
                                                              0：VSYS电压小于6V；
                                                              1：VSYS电压大于6V。 */
        unsigned char  vsys_uv_d10mr         : 1;  /* bit[1]: 低电压告警状态指示位(上升沿去抖10ms，时间可配)。
                                                              0：VSYS电压大于3.65V(可寄存器配置为其他电压档位)；
                                                              1：VSYS电压小于3.65V(可寄存器配置为其他电压档位)。 */
        unsigned char  vsys_pwroff_abs       : 1;  /* bit[2]: 绝对关机电压状态位指示位（没有同步）。
                                                              0：VSYS电压大于2.3V；
                                                              1：VSYS电压小于2.3V。 */
        unsigned char  vsys_pwroff_deb_d80mr : 1;  /* bit[3]: 去抖关机电压状态指示位（上升沿去抖80ms，时间可配）。
                                                              0：VSYS大于2.6V(可寄存器配置为3.0V)；
                                                              1：VSYS小于2.6V(可寄存器配置为3.0V)。
                                                              配置寄存器在非下电区。 */
        unsigned char  vsys_pwron_d60ur      : 1;  /* bit[4]: 开机电压状态指示位（上升沿去抖60us）。
                                                              0：VSYS大于2.8V(可寄存器配置为3.2V)；
                                                              1：VSYS小于2.8V(可寄存器配置为3.2V)。
                                                              配置寄存器在非下电区。 */
        unsigned char  thsd_otmp140_d1mr     : 1;  /* bit[5]: 过温状态位(上升沿去抖1ms)。
                                                              0：温度小于140℃；
                                                              1： 温度大于140℃。 */
        unsigned char  thsd_otmp125_d1mr     : 1;  /* bit[6]: 过温状态指示位(上升沿去抖1ms)。
                                                              0：温度小于设置值；
                                                              1：温度大于设置值(非140关机门限)。
                                                              温度设置值参见TH_CTRL[thsd_tmp_set]，默认125℃。 */
        unsigned char  pwron_d20m            : 1;  /* bit[7]: 按键状态指示位(双沿去抖20ms)。
                                                              0：按键未被按下；
                                                              1：按键被按下。 */
    } reg;
} PMIC_STATUS0_UNION;
#endif
#define PMIC_STATUS0_vsys_ov_d200ur_START         (0)
#define PMIC_STATUS0_vsys_ov_d200ur_END           (0)
#define PMIC_STATUS0_vsys_uv_d10mr_START          (1)
#define PMIC_STATUS0_vsys_uv_d10mr_END            (1)
#define PMIC_STATUS0_vsys_pwroff_abs_START        (2)
#define PMIC_STATUS0_vsys_pwroff_abs_END          (2)
#define PMIC_STATUS0_vsys_pwroff_deb_d80mr_START  (3)
#define PMIC_STATUS0_vsys_pwroff_deb_d80mr_END    (3)
#define PMIC_STATUS0_vsys_pwron_d60ur_START       (4)
#define PMIC_STATUS0_vsys_pwron_d60ur_END         (4)
#define PMIC_STATUS0_thsd_otmp140_d1mr_START      (5)
#define PMIC_STATUS0_thsd_otmp140_d1mr_END        (5)
#define PMIC_STATUS0_thsd_otmp125_d1mr_START      (6)
#define PMIC_STATUS0_thsd_otmp125_d1mr_END        (6)
#define PMIC_STATUS0_pwron_d20m_START             (7)
#define PMIC_STATUS0_pwron_d20m_END               (7)


/*****************************************************************************
 结构名    : PMIC_STATUS1_UNION
 结构说明  : STATUS1 寄存器结构定义。地址偏移量:0x007，初值:0x00，宽度:8
 寄存器说明: 状态标志寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dcxo_clk_sel         : 1;  /* bit[0]: DCXO模式当前工作时钟源。
                                                             0：32K RC；
                                                             1：19.2MHz 586分频时钟。 */
        unsigned char  tcxo_clk_sel         : 1;  /* bit[1]: TCXO模式当前工作时钟源。
                                                             0：32K RC；
                                                             1：32K Crystal OSC。 */
        unsigned char  xo32k_mode_otp       : 1;  /* bit[2]: XO 32K来源 
                                                             0：无32K晶体；
                                                             1：有32K晶体。 */
        unsigned char  buck1_vol_sel        : 1;  /* bit[3]: BUCK1的开机电压选择信号。
                                                             0：1.2V；
                                                             1：1.1V。 */
        unsigned char  sim0_hpd_d540u       : 1;  /* bit[4]: SIM0_HPD状态指示位(双沿去抖540us，时间可配)。
                                                             0：SIM0_HPD输入低电平；
                                                             1：SIM0_HPD输入高电平。 */
        unsigned char  sim1_hpd_d540u       : 1;  /* bit[5]: SIM1_HPD状态指示位(双沿去抖540us，时间可配)。
                                                             0：SIM1_HPD输入低电平；
                                                             1：SIM1_HPD输入高电平。 */
        unsigned char  alarm_on             : 1;  /* bit[6]: 闹钟状态指示位。
                                                             0：闹钟无效；
                                                             1： 闹钟有效，持续1s高电平。 */
        unsigned char  vbus_det_insert_d20m : 1;  /* bit[7]: USB状态指示位(双沿去抖20ms)。
                                                             0：USB处于拔出状态；
                                                             1：USB处于插入状态。 */
    } reg;
} PMIC_STATUS1_UNION;
#endif
#define PMIC_STATUS1_dcxo_clk_sel_START          (0)
#define PMIC_STATUS1_dcxo_clk_sel_END            (0)
#define PMIC_STATUS1_tcxo_clk_sel_START          (1)
#define PMIC_STATUS1_tcxo_clk_sel_END            (1)
#define PMIC_STATUS1_xo32k_mode_otp_START        (2)
#define PMIC_STATUS1_xo32k_mode_otp_END          (2)
#define PMIC_STATUS1_buck1_vol_sel_START         (3)
#define PMIC_STATUS1_buck1_vol_sel_END           (3)
#define PMIC_STATUS1_sim0_hpd_d540u_START        (4)
#define PMIC_STATUS1_sim0_hpd_d540u_END          (4)
#define PMIC_STATUS1_sim1_hpd_d540u_START        (5)
#define PMIC_STATUS1_sim1_hpd_d540u_END          (5)
#define PMIC_STATUS1_alarm_on_START              (6)
#define PMIC_STATUS1_alarm_on_END                (6)
#define PMIC_STATUS1_vbus_det_insert_d20m_START  (7)
#define PMIC_STATUS1_vbus_det_insert_d20m_END    (7)


/*****************************************************************************
 结构名    : PMIC_D2A_RES0_UNION
 结构说明  : D2A_RES0 寄存器结构定义。地址偏移量:0x008，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_0_3 : 4;  /* bit[0-3]: xo_cali_thresold[3:0]映射寄存器 */
        unsigned char  d2a_reserve0         : 4;  /* bit[4-7]: 数字到模拟的保留信号。 */
    } reg;
} PMIC_D2A_RES0_UNION;
#endif
#define PMIC_D2A_RES0_xo_cali_thresold_0_3_START  (0)
#define PMIC_D2A_RES0_xo_cali_thresold_0_3_END    (3)
#define PMIC_D2A_RES0_d2a_reserve0_START          (4)
#define PMIC_D2A_RES0_d2a_reserve0_END            (7)


/*****************************************************************************
 结构名    : PMIC_D2A_RES1_UNION
 结构说明  : D2A_RES1 寄存器结构定义。地址偏移量:0x009，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_4_7 : 4;  /* bit[0-3]: xo_cali_thresold[7:4]映射寄存器 */
        unsigned char  d2a_reserve1         : 4;  /* bit[4-7]: 数字到模拟的保留信号。 */
    } reg;
} PMIC_D2A_RES1_UNION;
#endif
#define PMIC_D2A_RES1_xo_cali_thresold_4_7_START  (0)
#define PMIC_D2A_RES1_xo_cali_thresold_4_7_END    (3)
#define PMIC_D2A_RES1_d2a_reserve1_START          (4)
#define PMIC_D2A_RES1_d2a_reserve1_END            (7)


/*****************************************************************************
 结构名    : PMIC_D2A_RES2_UNION
 结构说明  : D2A_RES2 寄存器结构定义。地址偏移量:0x00A，初值:0x00，宽度:8
 寄存器说明: xo_cali_thresold[15:8]映射寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_8_15 : 8;  /* bit[0-7]: xo_cali_thresold[15:8]映射寄存器 */
    } reg;
} PMIC_D2A_RES2_UNION;
#endif
#define PMIC_D2A_RES2_xo_cali_thresold_8_15_START  (0)
#define PMIC_D2A_RES2_xo_cali_thresold_8_15_END    (7)


/*****************************************************************************
 结构名    : PMIC_A2D_RES0_UNION
 结构说明  : A2D_RES0 寄存器结构定义。地址偏移量:0x00B，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_19m2_sel     : 1;  /* bit[0]  : XO 19.2M来源。
                                                          0：38.4M晶体；
                                                          1：19.2M晶振。 */
        unsigned char  xo_19m2_abnor_n : 1;  /* bit[1]  : XO 19.2M时钟异常指示信号。
                                                          0：19.2M异常(19.2M时钟消失)；
                                                          1: 19.2M时钟正常。 */
        unsigned char  a2d_reserve0    : 6;  /* bit[2-7]: 模拟到数字的保留信号。 */
    } reg;
} PMIC_A2D_RES0_UNION;
#endif
#define PMIC_A2D_RES0_xo_19m2_sel_START      (0)
#define PMIC_A2D_RES0_xo_19m2_sel_END        (0)
#define PMIC_A2D_RES0_xo_19m2_abnor_n_START  (1)
#define PMIC_A2D_RES0_xo_19m2_abnor_n_END    (1)
#define PMIC_A2D_RES0_a2d_reserve0_START     (2)
#define PMIC_A2D_RES0_a2d_reserve0_END       (7)


/*****************************************************************************
 结构名    : PMIC_A2D_RES1_UNION
 结构说明  : A2D_RES1 寄存器结构定义。地址偏移量:0x00C，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  a2d_reserve1 : 8;  /* bit[0-7]: 模拟到数字的保留信号。 */
    } reg;
} PMIC_A2D_RES1_UNION;
#endif
#define PMIC_A2D_RES1_a2d_reserve1_START  (0)
#define PMIC_A2D_RES1_a2d_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL0_UNION
 结构说明  : BUCK0_CTRL0 寄存器结构定义。地址偏移量:0x00D，初值:0x83，宽度:8
 寄存器说明: BUCK0控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_adj_clx : 4;  /* bit[0-3]: bit[3]：发生DMD时，关闭部分功率管。
                                                        0：不关闭；
                                                        1：关闭。
                                                        bit[2：0]：LX反馈滤波电容调节。
                                                        000：10pF；
                                                        001：20pF；
                                                        010：30pF；
                                                        011：40pF；
                                                        100：30pF；
                                                        101：40pF；
                                                        110：50pF；
                                                        111：60pF。 */
        unsigned char  buck0_adj_rlx : 4;  /* bit[4-7]: BUCK0 LX反馈滤波电阻调节。
                                                        0000：3.4MΩ；
                                                        0001：3.2MΩ；
                                                        0010：2.8MΩ；
                                                        0011：2.6MΩ；
                                                        0100：2.4MΩ；
                                                        0101：2.2MΩ；
                                                        0110：2.0MΩ；
                                                        0111：1.8MΩ；
                                                        1000：1.6MΩ；
                                                        1001：1.4MΩ；
                                                        1010：1.2MΩ；
                                                        1011：1.0MΩ；
                                                        1100：0.8MΩ；
                                                        1101：0.6MΩ；
                                                        1110：0.4MΩ；
                                                        1111：0.2MΩ。 */
    } reg;
} PMIC_BUCK0_CTRL0_UNION;
#endif
#define PMIC_BUCK0_CTRL0_buck0_adj_clx_START  (0)
#define PMIC_BUCK0_CTRL0_buck0_adj_clx_END    (3)
#define PMIC_BUCK0_CTRL0_buck0_adj_rlx_START  (4)
#define PMIC_BUCK0_CTRL0_buck0_adj_rlx_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL1_UNION
 结构说明  : BUCK0_CTRL1 寄存器结构定义。地址偏移量:0x00E，初值:0x40，宽度:8
 寄存器说明: BUCK0控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ng_dt_sel : 1;  /* bit[0]  : BUCK0 P管到N管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck0_pg_dt_sel : 1;  /* bit[1]  : BUCK0 N管到P管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck0_sft_sel   : 1;  /* bit[2]  : BUCK0软启动方式选择。
                                                          0：软启动时间为200μs左右；
                                                          1：软启动时间为100μs左右。 */
        unsigned char  reserved        : 1;  /* bit[3]  : 保留。 */
        unsigned char  buck0_dt_sel    : 2;  /* bit[4-5]: 死区时间调节。
                                                          0：不额外延迟5ns；
                                                          1：额外延迟5ns。 */
        unsigned char  buck0_ocp_sel   : 2;  /* bit[6-7]: BUCK0 OCP点调整。
                                                          00：3.24A；
                                                          01：3.69A；
                                                          10：4.13A；
                                                          11：4.57A。 */
    } reg;
} PMIC_BUCK0_CTRL1_UNION;
#endif
#define PMIC_BUCK0_CTRL1_buck0_ng_dt_sel_START  (0)
#define PMIC_BUCK0_CTRL1_buck0_ng_dt_sel_END    (0)
#define PMIC_BUCK0_CTRL1_buck0_pg_dt_sel_START  (1)
#define PMIC_BUCK0_CTRL1_buck0_pg_dt_sel_END    (1)
#define PMIC_BUCK0_CTRL1_buck0_sft_sel_START    (2)
#define PMIC_BUCK0_CTRL1_buck0_sft_sel_END      (2)
#define PMIC_BUCK0_CTRL1_buck0_dt_sel_START     (4)
#define PMIC_BUCK0_CTRL1_buck0_dt_sel_END       (5)
#define PMIC_BUCK0_CTRL1_buck0_ocp_sel_START    (6)
#define PMIC_BUCK0_CTRL1_buck0_ocp_sel_END      (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL2_UNION
 结构说明  : BUCK0_CTRL2 寄存器结构定义。地址偏移量:0x00F，初值:0x3C，宽度:8
 寄存器说明: BUCK0控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ng_n_sel : 2;  /* bit[0-1]: BUCK0 N power管驱动对应NMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
        unsigned char  buck0_ng_p_sel : 2;  /* bit[2-3]: BUCK0 N power管驱动对应PMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck0_pg_n_sel : 2;  /* bit[4-5]: BUCK0 P power管驱动对应NMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck0_pg_p_sel : 2;  /* bit[6-7]: BUCK0 P power管驱动对应PMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
    } reg;
} PMIC_BUCK0_CTRL2_UNION;
#endif
#define PMIC_BUCK0_CTRL2_buck0_ng_n_sel_START  (0)
#define PMIC_BUCK0_CTRL2_buck0_ng_n_sel_END    (1)
#define PMIC_BUCK0_CTRL2_buck0_ng_p_sel_START  (2)
#define PMIC_BUCK0_CTRL2_buck0_ng_p_sel_END    (3)
#define PMIC_BUCK0_CTRL2_buck0_pg_n_sel_START  (4)
#define PMIC_BUCK0_CTRL2_buck0_pg_n_sel_END    (5)
#define PMIC_BUCK0_CTRL2_buck0_pg_p_sel_START  (6)
#define PMIC_BUCK0_CTRL2_buck0_pg_p_sel_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL3_UNION
 结构说明  : BUCK0_CTRL3 寄存器结构定义。地址偏移量:0x010，初值:0x20，宽度:8
 寄存器说明: BUCK0控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reg_r  : 2;  /* bit[0-1]: BUCK0内部regulator电阻，用于调节regulator带宽。
                                                       00：2.8kHz；
                                                       01：45kHz；
                                                       10：85kHz；
                                                       11：152kHz。 */
        unsigned char  reserved     : 2;  /* bit[2-3]: 保留。 */
        unsigned char  buck0_reg_en : 1;  /* bit[4]  : BUCK0内部精度调整器使能信号。
                                                       0：使能；
                                                       1：不使能。 */
        unsigned char  buck0_dbias  : 2;  /* bit[5-6]: BUCK0比较器偏置电流调节。
                                                       00：2uA；
                                                       01：1uA；
                                                       10：4uA；
                                                       11：3uA。 */
        unsigned char  buck0_ocp_d  : 1;  /* bit[7]  : BUCK0 内部OCP环路屏蔽信号。
                                                       0：不屏蔽；
                                                       1：屏蔽。 */
    } reg;
} PMIC_BUCK0_CTRL3_UNION;
#endif
#define PMIC_BUCK0_CTRL3_buck0_reg_r_START   (0)
#define PMIC_BUCK0_CTRL3_buck0_reg_r_END     (1)
#define PMIC_BUCK0_CTRL3_buck0_reg_en_START  (4)
#define PMIC_BUCK0_CTRL3_buck0_reg_en_END    (4)
#define PMIC_BUCK0_CTRL3_buck0_dbias_START   (5)
#define PMIC_BUCK0_CTRL3_buck0_dbias_END     (6)
#define PMIC_BUCK0_CTRL3_buck0_ocp_d_START   (7)
#define PMIC_BUCK0_CTRL3_buck0_ocp_d_END     (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL4_UNION
 结构说明  : BUCK0_CTRL4 寄存器结构定义。地址偏移量:0x011，初值:0x20，宽度:8
 寄存器说明: BUCK0控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_short_pdp : 1;  /* bit[0]  : 短路保护屏蔽寄存器。
                                                          0：使能短路保护，0.4V门限；
                                                          1：不使能短路保护，0V门限。 */
        unsigned char  buck0_reg_ss_d  : 1;  /* bit[1]  : BUCK0软启动时内部regulator状态。
                                                          0：正常状态；
                                                          1：单位增益反馈。 */
        unsigned char  buck0_regop_c   : 1;  /* bit[2]  : BUCK0内部regulator OP输出电容，用于调节OP的slew-rate。
                                                          0：slew-rate慢；
                                                          1：slew-rate快。 */
        unsigned char  buck0_reg_idr   : 2;  /* bit[3-4]: BUCK0内部regulator电流，用于调节regulator调整精度范围。
                                                          00：4uA；
                                                          01：6uA；
                                                          10：8uA；
                                                          11：10uA。 */
        unsigned char  buck0_reg_dr    : 3;  /* bit[5-7]: BUCK0内部regulator电阻，用于调节regulator调整精度范围。
                                                          000：+/-6mV；
                                                          001：+/-12mV；
                                                          010：+/-18mV；
                                                          011：+/-24mV；
                                                          100：+/-30mV；
                                                          101：+/-36mV；
                                                          110：+/-42mV；
                                                          111：+/-48mV。 */
    } reg;
} PMIC_BUCK0_CTRL4_UNION;
#endif
#define PMIC_BUCK0_CTRL4_buck0_short_pdp_START  (0)
#define PMIC_BUCK0_CTRL4_buck0_short_pdp_END    (0)
#define PMIC_BUCK0_CTRL4_buck0_reg_ss_d_START   (1)
#define PMIC_BUCK0_CTRL4_buck0_reg_ss_d_END     (1)
#define PMIC_BUCK0_CTRL4_buck0_regop_c_START    (2)
#define PMIC_BUCK0_CTRL4_buck0_regop_c_END      (2)
#define PMIC_BUCK0_CTRL4_buck0_reg_idr_START    (3)
#define PMIC_BUCK0_CTRL4_buck0_reg_idr_END      (4)
#define PMIC_BUCK0_CTRL4_buck0_reg_dr_START     (5)
#define PMIC_BUCK0_CTRL4_buck0_reg_dr_END       (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL5_UNION
 结构说明  : BUCK0_CTRL5 寄存器结构定义。地址偏移量:0x012，初值:0x04，宽度:8
 寄存器说明: BUCK0控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ton      : 2;  /* bit[0-1]: BUCK0最小导通时间。
                                                         00：100ns；
                                                         01：200ns；
                                                         10：300ns；
                                                         11：400ns。 */
        unsigned char  buck0_nmos_off : 1;  /* bit[2]  : BUCK0用于关闭NMOS power管。
                                                         0：强制关闭；
                                                         1：不强制关闭。 */
        unsigned char  buck0_reg_c    : 1;  /* bit[3]  : BUCK0内部regulator电容，用于调节regulator带宽。
                                                         0：电容小；
                                                         1：电容大。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK0_CTRL5_UNION;
#endif
#define PMIC_BUCK0_CTRL5_buck0_ton_START       (0)
#define PMIC_BUCK0_CTRL5_buck0_ton_END         (1)
#define PMIC_BUCK0_CTRL5_buck0_nmos_off_START  (2)
#define PMIC_BUCK0_CTRL5_buck0_nmos_off_END    (2)
#define PMIC_BUCK0_CTRL5_buck0_reg_c_START     (3)
#define PMIC_BUCK0_CTRL5_buck0_reg_c_END       (3)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL6_UNION
 结构说明  : BUCK0_CTRL6 寄存器结构定义。地址偏移量:0x013，初值:0x41，宽度:8
 寄存器说明: BUCK0控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_shield_i    : 2;  /* bit[0-1]: DMD屏蔽信号对应电流调节。
                                                            00：0.84A；
                                                            01：1.25A；
                                                            10：1.66A；
                                                            11：2.07A。 */
        unsigned char  buck0_new_dmd_sel : 5;  /* bit[2-6]: bit[6] DMD偏置电流选择。
                                                            0：2uA；
                                                            1：1uA。
                                                            bit[5] DMD方式选择。
                                                            0：老DMD；
                                                            1：新DMD。
                                                            bit[4：2] 新DMD结构DMD电流调节。
                                                            000：28mA；
                                                            001：-75mA；
                                                            010：-40mA；
                                                            011：-12mA；
                                                            100：70mA；
                                                            101：120mA；
                                                            110：162mA；
                                                            111：205mA。 */
        unsigned char  reserved          : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_BUCK0_CTRL6_UNION;
#endif
#define PMIC_BUCK0_CTRL6_buck0_shield_i_START     (0)
#define PMIC_BUCK0_CTRL6_buck0_shield_i_END       (1)
#define PMIC_BUCK0_CTRL6_buck0_new_dmd_sel_START  (2)
#define PMIC_BUCK0_CTRL6_buck0_new_dmd_sel_END    (6)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL7_UNION
 结构说明  : BUCK0_CTRL7 寄存器结构定义。地址偏移量:0x014，初值:0x1B，宽度:8
 寄存器说明: BUCK0控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_dmd_sel : 3;  /* bit[0-2]: BUCK0 老DMD结构DMD电流调节。
                                                        000：-45mA；
                                                        001：-5mA；
                                                        010：27mA；
                                                        011：70mA；
                                                        100：105mA；
                                                        101：144mA；
                                                        110：185mA；
                                                        111：228mA。 */
        unsigned char  buck0_mos_sel : 2;  /* bit[3-4]: BUCK0 比较器内部电流调节。
                                                        00：增加0uA；
                                                        01：增加1uA；
                                                        10：增加2uA；
                                                        11：增加3uA。 */
        unsigned char  reserved      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_BUCK0_CTRL7_UNION;
#endif
#define PMIC_BUCK0_CTRL7_buck0_dmd_sel_START  (0)
#define PMIC_BUCK0_CTRL7_buck0_dmd_sel_END    (2)
#define PMIC_BUCK0_CTRL7_buck0_mos_sel_START  (3)
#define PMIC_BUCK0_CTRL7_buck0_mos_sel_END    (4)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL8_UNION
 结构说明  : BUCK0_CTRL8 寄存器结构定义。地址偏移量:0x015，初值:0x00，宽度:8
 寄存器说明: BUCK0控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reserve0 : 8;  /* bit[0-7]: BUCK0备用寄存器。 */
    } reg;
} PMIC_BUCK0_CTRL8_UNION;
#endif
#define PMIC_BUCK0_CTRL8_buck0_reserve0_START  (0)
#define PMIC_BUCK0_CTRL8_buck0_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL9_UNION
 结构说明  : BUCK0_CTRL9 寄存器结构定义。地址偏移量:0x016，初值:0x00，宽度:8
 寄存器说明: BUCK0控制寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reserve1 : 8;  /* bit[0-7]: BUCK0备用寄存器。 */
    } reg;
} PMIC_BUCK0_CTRL9_UNION;
#endif
#define PMIC_BUCK0_CTRL9_buck0_reserve1_START  (0)
#define PMIC_BUCK0_CTRL9_buck0_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL10_UNION
 结构说明  : BUCK0_CTRL10 寄存器结构定义。地址偏移量:0x017，初值:0x00，宽度:8
 寄存器说明: BUCK0控制寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reserve2 : 8;  /* bit[0-7]: BUCK0备用寄存器。 */
    } reg;
} PMIC_BUCK0_CTRL10_UNION;
#endif
#define PMIC_BUCK0_CTRL10_buck0_reserve2_START  (0)
#define PMIC_BUCK0_CTRL10_buck0_reserve2_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL11_UNION
 结构说明  : BUCK0_CTRL11 寄存器结构定义。地址偏移量:0x018，初值:0x00，宽度:8
 寄存器说明: BUCK0控制寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_pdn_lx_det     : 1;  /* bit[0]: BUCK0 比较器增强迟滞选择。
                                                             0：不增加迟滞量；
                                                             1：增加迟滞量。 */
        unsigned char  buck0_eco_dmd        : 1;  /* bit[1]: 在正常模式下强制NMOS管关闭。
                                                             0：不强制；
                                                             1：强制。 */
        unsigned char  buck0_dmd_shield_n   : 1;  /* bit[2]: 大电流下DMD屏蔽信号。
                                                             0：屏蔽；
                                                             1：不屏蔽。 */
        unsigned char  buck0_ocp_delay_sel  : 1;  /* bit[3]: OCP屏蔽时间延长15ns信号。
                                                             0：不延长；
                                                             1：延长。 */
        unsigned char  buck0_dmd_clamp      : 1;  /* bit[4]: 老DMD嵌位使能信号。
                                                             0：加上；
                                                             1：不加上。 */
        unsigned char  buck0_en_regop_clamp : 1;  /* bit[5]: regulator 嵌位电路使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned char  buck0_en_ss_sel      : 1;  /* bit[6]: 选择软起完成信号。
                                                             0：模拟给出；
                                                             1：数字给出。 */
        unsigned char  reserved             : 1;  /* bit[7]: 保留。 */
    } reg;
} PMIC_BUCK0_CTRL11_UNION;
#endif
#define PMIC_BUCK0_CTRL11_buck0_pdn_lx_det_START      (0)
#define PMIC_BUCK0_CTRL11_buck0_pdn_lx_det_END        (0)
#define PMIC_BUCK0_CTRL11_buck0_eco_dmd_START         (1)
#define PMIC_BUCK0_CTRL11_buck0_eco_dmd_END           (1)
#define PMIC_BUCK0_CTRL11_buck0_dmd_shield_n_START    (2)
#define PMIC_BUCK0_CTRL11_buck0_dmd_shield_n_END      (2)
#define PMIC_BUCK0_CTRL11_buck0_ocp_delay_sel_START   (3)
#define PMIC_BUCK0_CTRL11_buck0_ocp_delay_sel_END     (3)
#define PMIC_BUCK0_CTRL11_buck0_dmd_clamp_START       (4)
#define PMIC_BUCK0_CTRL11_buck0_dmd_clamp_END         (4)
#define PMIC_BUCK0_CTRL11_buck0_en_regop_clamp_START  (5)
#define PMIC_BUCK0_CTRL11_buck0_en_regop_clamp_END    (5)
#define PMIC_BUCK0_CTRL11_buck0_en_ss_sel_START       (6)
#define PMIC_BUCK0_CTRL11_buck0_en_ss_sel_END         (6)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL0_UNION
 结构说明  : BUCK1_CTRL0 寄存器结构定义。地址偏移量:0x019，初值:0x83，宽度:8
 寄存器说明: BUCK1控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_adj_clx : 4;  /* bit[0-3]: bit[3]：发生DMD时，关闭部分功率管。
                                                        0：不关闭；
                                                        1：关闭。
                                                        bit[2:0]：LX反馈滤波电容调节。
                                                        000：10pF；
                                                        001：20pF；
                                                        010：30pF；
                                                        011：40pF；
                                                        100：30pF；
                                                        101：40pF；
                                                        110：50pF；
                                                        111：60pF。 */
        unsigned char  buck1_adj_rlx : 4;  /* bit[4-7]: BUCK1 LX反馈滤波电阻调节。
                                                        0000：3.4MΩ；
                                                        0001：3.2MΩ；
                                                        0010：2.8MΩ；
                                                        0011：2.6MΩ；
                                                        0100：2.4MΩ；
                                                        0101：2.2MΩ；
                                                        0110：2.0MΩ；
                                                        0111：1.8MΩ；
                                                        1000：1.6MΩ；
                                                        1001：1.4MΩ；
                                                        1010：1.2MΩ；
                                                        1011：1.0MΩ；
                                                        1100：0.8MΩ；
                                                        1101：0.6MΩ；
                                                        1110：0.4MΩ；
                                                        1111：0.2MΩ。 */
    } reg;
} PMIC_BUCK1_CTRL0_UNION;
#endif
#define PMIC_BUCK1_CTRL0_buck1_adj_clx_START  (0)
#define PMIC_BUCK1_CTRL0_buck1_adj_clx_END    (3)
#define PMIC_BUCK1_CTRL0_buck1_adj_rlx_START  (4)
#define PMIC_BUCK1_CTRL0_buck1_adj_rlx_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL1_UNION
 结构说明  : BUCK1_CTRL1 寄存器结构定义。地址偏移量:0x01A，初值:0x40，宽度:8
 寄存器说明: BUCK1控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ng_dt_sel : 1;  /* bit[0]  : BUCK1 P管到N管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck1_pg_dt_sel : 1;  /* bit[1]  : BUCK1 N管到P管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck1_sft_sel   : 1;  /* bit[2]  : BUCK1软启动方式选择。
                                                          0：软启动时间为200μs左右；
                                                          1：软启动时间为100μs左右。 */
        unsigned char  reserved        : 1;  /* bit[3]  : 保留。 */
        unsigned char  buck1_dt_sel    : 2;  /* bit[4-5]: 死区时间调节。
                                                          0：不额外延迟5ns；
                                                          1：额外延迟5ns。 */
        unsigned char  buck1_ocp_sel   : 2;  /* bit[6-7]: BUCK1 OCP点调整。
                                                          00：3.70A；
                                                          01：4.14A；
                                                          10：4.59A；
                                                          11：5.03A。 */
    } reg;
} PMIC_BUCK1_CTRL1_UNION;
#endif
#define PMIC_BUCK1_CTRL1_buck1_ng_dt_sel_START  (0)
#define PMIC_BUCK1_CTRL1_buck1_ng_dt_sel_END    (0)
#define PMIC_BUCK1_CTRL1_buck1_pg_dt_sel_START  (1)
#define PMIC_BUCK1_CTRL1_buck1_pg_dt_sel_END    (1)
#define PMIC_BUCK1_CTRL1_buck1_sft_sel_START    (2)
#define PMIC_BUCK1_CTRL1_buck1_sft_sel_END      (2)
#define PMIC_BUCK1_CTRL1_buck1_dt_sel_START     (4)
#define PMIC_BUCK1_CTRL1_buck1_dt_sel_END       (5)
#define PMIC_BUCK1_CTRL1_buck1_ocp_sel_START    (6)
#define PMIC_BUCK1_CTRL1_buck1_ocp_sel_END      (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL2_UNION
 结构说明  : BUCK1_CTRL2 寄存器结构定义。地址偏移量:0x01B，初值:0x3C，宽度:8
 寄存器说明: BUCK1控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ng_n_sel : 2;  /* bit[0-1]: BUCK1 N power管驱动对应NMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
        unsigned char  buck1_ng_p_sel : 2;  /* bit[2-3]: BUCK1 N power管驱动对应PMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck1_pg_n_sel : 2;  /* bit[4-5]: BUCK1 P power管驱动对应NMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck1_pg_p_sel : 2;  /* bit[6-7]: BUCK1 P power管驱动对应PMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
    } reg;
} PMIC_BUCK1_CTRL2_UNION;
#endif
#define PMIC_BUCK1_CTRL2_buck1_ng_n_sel_START  (0)
#define PMIC_BUCK1_CTRL2_buck1_ng_n_sel_END    (1)
#define PMIC_BUCK1_CTRL2_buck1_ng_p_sel_START  (2)
#define PMIC_BUCK1_CTRL2_buck1_ng_p_sel_END    (3)
#define PMIC_BUCK1_CTRL2_buck1_pg_n_sel_START  (4)
#define PMIC_BUCK1_CTRL2_buck1_pg_n_sel_END    (5)
#define PMIC_BUCK1_CTRL2_buck1_pg_p_sel_START  (6)
#define PMIC_BUCK1_CTRL2_buck1_pg_p_sel_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL3_UNION
 结构说明  : BUCK1_CTRL3 寄存器结构定义。地址偏移量:0x01C，初值:0x20，宽度:8
 寄存器说明: BUCK1控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reg_r  : 2;  /* bit[0-1]: BUCK1内部regulator电阻，用于调节regulator带宽。
                                                       00：2.8kHz；
                                                       01：45kHz；
                                                       10：85kHz；
                                                       11：152kHz。 */
        unsigned char  reserved     : 2;  /* bit[2-3]: 保留。 */
        unsigned char  buck1_reg_en : 1;  /* bit[4]  : BUCK1内部精度调整器使能信号。
                                                       0：使能；
                                                       1：不使能。 */
        unsigned char  buck1_dbias  : 2;  /* bit[5-6]: BUCK1比较器偏置电流调节。
                                                       00：2uA；
                                                       01：1uA；
                                                       10：4uA；
                                                       11：3uA。 */
        unsigned char  buck1_ocp_d  : 1;  /* bit[7]  : BUCK1 内部OCP环路屏蔽信号。
                                                       0：不屏蔽；
                                                       1：屏蔽。 */
    } reg;
} PMIC_BUCK1_CTRL3_UNION;
#endif
#define PMIC_BUCK1_CTRL3_buck1_reg_r_START   (0)
#define PMIC_BUCK1_CTRL3_buck1_reg_r_END     (1)
#define PMIC_BUCK1_CTRL3_buck1_reg_en_START  (4)
#define PMIC_BUCK1_CTRL3_buck1_reg_en_END    (4)
#define PMIC_BUCK1_CTRL3_buck1_dbias_START   (5)
#define PMIC_BUCK1_CTRL3_buck1_dbias_END     (6)
#define PMIC_BUCK1_CTRL3_buck1_ocp_d_START   (7)
#define PMIC_BUCK1_CTRL3_buck1_ocp_d_END     (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL4_UNION
 结构说明  : BUCK1_CTRL4 寄存器结构定义。地址偏移量:0x01D，初值:0x20，宽度:8
 寄存器说明: BUCK1控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_short_pdp : 1;  /* bit[0]  : 短路保护屏蔽寄存器。
                                                          0：使能短路保护，0.4V门限；
                                                          1：不使能短路保护，0V门限。 */
        unsigned char  buck1_reg_ss_d  : 1;  /* bit[1]  : BUCK1软启动时内部regulator状态。
                                                          0：正常状态；
                                                          1：单位增益反馈。 */
        unsigned char  buck1_regop_c   : 1;  /* bit[2]  : BUCK1内部regulator OP输出电容，用于调节OP的slew-rate。
                                                          0：slew-rate慢；
                                                          1：slew-rate快。 */
        unsigned char  buck1_reg_idr   : 2;  /* bit[3-4]: BUCK1内部regulator电流，用于调节regulator调整精度范围。
                                                          00：4uA；
                                                          01：6uA；
                                                          10：8uA；
                                                          11：10uA。 */
        unsigned char  buck1_reg_dr    : 3;  /* bit[5-7]: BUCK1内部regulator电阻，用于调节regulator调整精度范围。
                                                          000：+/-6mV；
                                                          001：+/-12mV；
                                                          010：+/-18mV；
                                                          011：+/-24mV；
                                                          100：+/-30mV；
                                                          101：+/-36mV；
                                                          110：+/-42mV；
                                                          111：+/-48mV。 */
    } reg;
} PMIC_BUCK1_CTRL4_UNION;
#endif
#define PMIC_BUCK1_CTRL4_buck1_short_pdp_START  (0)
#define PMIC_BUCK1_CTRL4_buck1_short_pdp_END    (0)
#define PMIC_BUCK1_CTRL4_buck1_reg_ss_d_START   (1)
#define PMIC_BUCK1_CTRL4_buck1_reg_ss_d_END     (1)
#define PMIC_BUCK1_CTRL4_buck1_regop_c_START    (2)
#define PMIC_BUCK1_CTRL4_buck1_regop_c_END      (2)
#define PMIC_BUCK1_CTRL4_buck1_reg_idr_START    (3)
#define PMIC_BUCK1_CTRL4_buck1_reg_idr_END      (4)
#define PMIC_BUCK1_CTRL4_buck1_reg_dr_START     (5)
#define PMIC_BUCK1_CTRL4_buck1_reg_dr_END       (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL5_UNION
 结构说明  : BUCK1_CTRL5 寄存器结构定义。地址偏移量:0x01E，初值:0x04，宽度:8
 寄存器说明: BUCK1控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ton      : 2;  /* bit[0-1]: BUCK1最小导通时间。
                                                         00：100ns；
                                                         01：200ns；
                                                         10：300ns；
                                                         11：400ns。 */
        unsigned char  buck1_nmos_off : 1;  /* bit[2]  : BUCK1用于关闭NMOS power管。
                                                         0：强制关闭；
                                                         1：不强制关闭。 */
        unsigned char  buck1_reg_c    : 1;  /* bit[3]  : BUCK1内部regulator电容，用于调节regulator带宽。
                                                         0：电容小；
                                                         1：电容大。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK1_CTRL5_UNION;
#endif
#define PMIC_BUCK1_CTRL5_buck1_ton_START       (0)
#define PMIC_BUCK1_CTRL5_buck1_ton_END         (1)
#define PMIC_BUCK1_CTRL5_buck1_nmos_off_START  (2)
#define PMIC_BUCK1_CTRL5_buck1_nmos_off_END    (2)
#define PMIC_BUCK1_CTRL5_buck1_reg_c_START     (3)
#define PMIC_BUCK1_CTRL5_buck1_reg_c_END       (3)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL6_UNION
 结构说明  : BUCK1_CTRL6 寄存器结构定义。地址偏移量:0x01F，初值:0x41，宽度:8
 寄存器说明: BUCK1控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_shield_i    : 2;  /* bit[0-1]: DMD屏蔽信号对应电流调节。
                                                            00：0.84A；
                                                            01：1.25A；
                                                            10：1.66A；
                                                            11：2.07A。 */
        unsigned char  buck1_new_dmd_sel : 5;  /* bit[2-6]: bit[6] DMD偏置电流选择。
                                                            0：2uA；
                                                            1：1uA。
                                                            bit[3] DMD方式选择。
                                                            0：老DMD；
                                                            1：新DMD。
                                                            bit[4:2] 新DMD结构DMD电流调节。
                                                            000：28mA；
                                                            001：-70mA；
                                                            010：-40mA；
                                                            011：-12mA；
                                                            100：70mA；
                                                            101：120mA；
                                                            110：162mA；
                                                            111：205mA。 */
        unsigned char  reserved          : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_BUCK1_CTRL6_UNION;
#endif
#define PMIC_BUCK1_CTRL6_buck1_shield_i_START     (0)
#define PMIC_BUCK1_CTRL6_buck1_shield_i_END       (1)
#define PMIC_BUCK1_CTRL6_buck1_new_dmd_sel_START  (2)
#define PMIC_BUCK1_CTRL6_buck1_new_dmd_sel_END    (6)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL7_UNION
 结构说明  : BUCK1_CTRL7 寄存器结构定义。地址偏移量:0x020，初值:0x1B，宽度:8
 寄存器说明: BUCK1控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_dmd_sel : 3;  /* bit[0-2]: BUCK1 老DMD结构DMD电流调节。
                                                        000：-60mA；
                                                        001：-24mA；
                                                        010：12mA；
                                                        011：50mA；
                                                        100：92mA；
                                                        101：132mA；
                                                        110：173mA；
                                                        111：214mA。 */
        unsigned char  buck1_mos_sel : 2;  /* bit[3-4]: BUCK1 比较器内部电流调节。
                                                        00：增加0uA；
                                                        01：增加1uA；
                                                        10：增加2uA；
                                                        11：增加3uA。 */
        unsigned char  reserved      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_BUCK1_CTRL7_UNION;
#endif
#define PMIC_BUCK1_CTRL7_buck1_dmd_sel_START  (0)
#define PMIC_BUCK1_CTRL7_buck1_dmd_sel_END    (2)
#define PMIC_BUCK1_CTRL7_buck1_mos_sel_START  (3)
#define PMIC_BUCK1_CTRL7_buck1_mos_sel_END    (4)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL8_UNION
 结构说明  : BUCK1_CTRL8 寄存器结构定义。地址偏移量:0x021，初值:0x00，宽度:8
 寄存器说明: BUCK1控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reserve0 : 8;  /* bit[0-7]: BUCK1备用寄存器。 */
    } reg;
} PMIC_BUCK1_CTRL8_UNION;
#endif
#define PMIC_BUCK1_CTRL8_buck1_reserve0_START  (0)
#define PMIC_BUCK1_CTRL8_buck1_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL9_UNION
 结构说明  : BUCK1_CTRL9 寄存器结构定义。地址偏移量:0x022，初值:0x00，宽度:8
 寄存器说明: BUCK1控制寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reserve1 : 8;  /* bit[0-7]: BUCK1备用寄存器。 */
    } reg;
} PMIC_BUCK1_CTRL9_UNION;
#endif
#define PMIC_BUCK1_CTRL9_buck1_reserve1_START  (0)
#define PMIC_BUCK1_CTRL9_buck1_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL10_UNION
 结构说明  : BUCK1_CTRL10 寄存器结构定义。地址偏移量:0x023，初值:0x00，宽度:8
 寄存器说明: BUCK1控制寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reserve2 : 8;  /* bit[0-7]: BUCK1备用寄存器。 */
    } reg;
} PMIC_BUCK1_CTRL10_UNION;
#endif
#define PMIC_BUCK1_CTRL10_buck1_reserve2_START  (0)
#define PMIC_BUCK1_CTRL10_buck1_reserve2_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL11_UNION
 结构说明  : BUCK1_CTRL11 寄存器结构定义。地址偏移量:0x024，初值:0x00，宽度:8
 寄存器说明: BUCK1控制寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_pdn_lx_det     : 1;  /* bit[0]: BUCK1 比较器增强迟滞选择。
                                                             0：不增加迟滞量；
                                                             1：增加迟滞量。 */
        unsigned char  buck1_eco_dmd        : 1;  /* bit[1]: 在正常模式下强制NMOS管关闭。
                                                             0：不强制；
                                                             1：强制。 */
        unsigned char  buck1_dmd_shield_n   : 1;  /* bit[2]: 大电流下DMD屏蔽信号。
                                                             0：屏蔽；
                                                             1：不屏蔽。 */
        unsigned char  buck1_ocp_delay_sel  : 1;  /* bit[3]: OCP屏蔽时间延长15ns信号。
                                                             0：不延长；
                                                             1：延长。 */
        unsigned char  buck1_dmd_clamp      : 1;  /* bit[4]: 老DMD嵌位使能信号。
                                                             0：加上；
                                                             1：不加上。 */
        unsigned char  buck1_en_regop_clamp : 1;  /* bit[5]: regulator 嵌位电路使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned char  buck1_en_ss_sel      : 1;  /* bit[6]: 选择软起完成信号。
                                                             0：模拟给出；
                                                             1：数字给出。 */
        unsigned char  reserved             : 1;  /* bit[7]: 保留。 */
    } reg;
} PMIC_BUCK1_CTRL11_UNION;
#endif
#define PMIC_BUCK1_CTRL11_buck1_pdn_lx_det_START      (0)
#define PMIC_BUCK1_CTRL11_buck1_pdn_lx_det_END        (0)
#define PMIC_BUCK1_CTRL11_buck1_eco_dmd_START         (1)
#define PMIC_BUCK1_CTRL11_buck1_eco_dmd_END           (1)
#define PMIC_BUCK1_CTRL11_buck1_dmd_shield_n_START    (2)
#define PMIC_BUCK1_CTRL11_buck1_dmd_shield_n_END      (2)
#define PMIC_BUCK1_CTRL11_buck1_ocp_delay_sel_START   (3)
#define PMIC_BUCK1_CTRL11_buck1_ocp_delay_sel_END     (3)
#define PMIC_BUCK1_CTRL11_buck1_dmd_clamp_START       (4)
#define PMIC_BUCK1_CTRL11_buck1_dmd_clamp_END         (4)
#define PMIC_BUCK1_CTRL11_buck1_en_regop_clamp_START  (5)
#define PMIC_BUCK1_CTRL11_buck1_en_regop_clamp_END    (5)
#define PMIC_BUCK1_CTRL11_buck1_en_ss_sel_START       (6)
#define PMIC_BUCK1_CTRL11_buck1_en_ss_sel_END         (6)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL0_UNION
 结构说明  : BUCK2_CTRL0 寄存器结构定义。地址偏移量:0x025，初值:0x83，宽度:8
 寄存器说明: BUCK2控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_adj_clx : 4;  /* bit[0-3]: bit[3]：发生DMD时，关闭部分功率管。
                                                        0：不关闭；
                                                        1：关闭。
                                                        bit[2:0]：LX反馈滤波电容调节。
                                                        000：10pF；
                                                        001：20pF；
                                                        010：30pF；
                                                        011：40pF；
                                                        100：30pF；
                                                        101：40pF；
                                                        110：50pF；
                                                        111：60pF。 */
        unsigned char  buck2_adj_rlx : 4;  /* bit[4-7]: BUCK2 LX反馈滤波电阻调节。
                                                        0000：3.4MΩ；
                                                        0001：3.2MΩ；
                                                        0010：2.8MΩ；
                                                        0011：2.6MΩ；
                                                        0100：2.4MΩ；
                                                        0101：2.2MΩ；
                                                        0110：2.0MΩ；
                                                        0111：1.8MΩ；
                                                        1000：1.6MΩ；
                                                        1001：1.4MΩ；
                                                        1010：1.2MΩ；
                                                        1011：1.0MΩ；
                                                        1100：0.8MΩ；
                                                        1101：0.6MΩ；
                                                        1110：0.4MΩ；
                                                        1111：0.2MΩ。 */
    } reg;
} PMIC_BUCK2_CTRL0_UNION;
#endif
#define PMIC_BUCK2_CTRL0_buck2_adj_clx_START  (0)
#define PMIC_BUCK2_CTRL0_buck2_adj_clx_END    (3)
#define PMIC_BUCK2_CTRL0_buck2_adj_rlx_START  (4)
#define PMIC_BUCK2_CTRL0_buck2_adj_rlx_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL1_UNION
 结构说明  : BUCK2_CTRL1 寄存器结构定义。地址偏移量:0x026，初值:0x40，宽度:8
 寄存器说明: BUCK2控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ng_dt_sel : 1;  /* bit[0]  : BUCK2 P管到N管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck2_pg_dt_sel : 1;  /* bit[1]  : BUCK2 N管到P管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck2_sft_sel   : 1;  /* bit[2]  : BUCK2软启动方式选择。
                                                          0：软启动时间为200μs左右；
                                                          1：软启动时间为100μs左右。 */
        unsigned char  reserved        : 1;  /* bit[3]  : 保留。 */
        unsigned char  buck2_dt_sel    : 2;  /* bit[4-5]: 死区时间调节。
                                                          0：不额外延迟5ns；
                                                          1：额外延迟5ns。 */
        unsigned char  buck2_ocp_sel   : 2;  /* bit[6-7]: BUCK2 OCP点调整。
                                                          00：3.24A；
                                                          01：3.69A；
                                                          10：4.13A；
                                                          11：4.57A。 */
    } reg;
} PMIC_BUCK2_CTRL1_UNION;
#endif
#define PMIC_BUCK2_CTRL1_buck2_ng_dt_sel_START  (0)
#define PMIC_BUCK2_CTRL1_buck2_ng_dt_sel_END    (0)
#define PMIC_BUCK2_CTRL1_buck2_pg_dt_sel_START  (1)
#define PMIC_BUCK2_CTRL1_buck2_pg_dt_sel_END    (1)
#define PMIC_BUCK2_CTRL1_buck2_sft_sel_START    (2)
#define PMIC_BUCK2_CTRL1_buck2_sft_sel_END      (2)
#define PMIC_BUCK2_CTRL1_buck2_dt_sel_START     (4)
#define PMIC_BUCK2_CTRL1_buck2_dt_sel_END       (5)
#define PMIC_BUCK2_CTRL1_buck2_ocp_sel_START    (6)
#define PMIC_BUCK2_CTRL1_buck2_ocp_sel_END      (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL2_UNION
 结构说明  : BUCK2_CTRL2 寄存器结构定义。地址偏移量:0x027，初值:0x3C，宽度:8
 寄存器说明: BUCK2控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ng_n_sel : 2;  /* bit[0-1]: BUCK2 N power管驱动对应NMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
        unsigned char  buck2_ng_p_sel : 2;  /* bit[2-3]: BUCK2 N power管驱动对应PMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck2_pg_n_sel : 2;  /* bit[4-5]: BUCK2 P power管驱动对应NMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck2_pg_p_sel : 2;  /* bit[6-7]: BUCK2 P power管驱动对应PMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
    } reg;
} PMIC_BUCK2_CTRL2_UNION;
#endif
#define PMIC_BUCK2_CTRL2_buck2_ng_n_sel_START  (0)
#define PMIC_BUCK2_CTRL2_buck2_ng_n_sel_END    (1)
#define PMIC_BUCK2_CTRL2_buck2_ng_p_sel_START  (2)
#define PMIC_BUCK2_CTRL2_buck2_ng_p_sel_END    (3)
#define PMIC_BUCK2_CTRL2_buck2_pg_n_sel_START  (4)
#define PMIC_BUCK2_CTRL2_buck2_pg_n_sel_END    (5)
#define PMIC_BUCK2_CTRL2_buck2_pg_p_sel_START  (6)
#define PMIC_BUCK2_CTRL2_buck2_pg_p_sel_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL3_UNION
 结构说明  : BUCK2_CTRL3 寄存器结构定义。地址偏移量:0x028，初值:0x20，宽度:8
 寄存器说明: BUCK2控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reg_r  : 2;  /* bit[0-1]: BUCK2内部regulator电阻，用于调节regulator带宽。
                                                       00：2.8kHz；
                                                       01：45kHz；
                                                       10：85kHz；
                                                       11：152kHz。 */
        unsigned char  reserved     : 2;  /* bit[2-3]: 保留。 */
        unsigned char  buck2_reg_en : 1;  /* bit[4]  : BUCK2内部精度调整器使能信号。
                                                       0：使能；
                                                       1：不使能。 */
        unsigned char  buck2_dbias  : 2;  /* bit[5-6]: BUCK2比较器偏置电流调节。
                                                       00：2uA；
                                                       01：1uA；
                                                       10：4uA；
                                                       11：3uA。 */
        unsigned char  buck2_ocp_d  : 1;  /* bit[7]  : BUCK2 内部OCP环路屏蔽信号。
                                                       0：不屏蔽；
                                                       1：屏蔽。 */
    } reg;
} PMIC_BUCK2_CTRL3_UNION;
#endif
#define PMIC_BUCK2_CTRL3_buck2_reg_r_START   (0)
#define PMIC_BUCK2_CTRL3_buck2_reg_r_END     (1)
#define PMIC_BUCK2_CTRL3_buck2_reg_en_START  (4)
#define PMIC_BUCK2_CTRL3_buck2_reg_en_END    (4)
#define PMIC_BUCK2_CTRL3_buck2_dbias_START   (5)
#define PMIC_BUCK2_CTRL3_buck2_dbias_END     (6)
#define PMIC_BUCK2_CTRL3_buck2_ocp_d_START   (7)
#define PMIC_BUCK2_CTRL3_buck2_ocp_d_END     (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL4_UNION
 结构说明  : BUCK2_CTRL4 寄存器结构定义。地址偏移量:0x029，初值:0x20，宽度:8
 寄存器说明: BUCK2控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_short_pdp : 1;  /* bit[0]  : 短路保护屏蔽寄存器。
                                                          0：使能短路保护，0.4V门限；
                                                          1：不使能短路保护，0V门限。 */
        unsigned char  buck2_reg_ss_d  : 1;  /* bit[1]  : BUCK2软启动时内部regulator状态。
                                                          0：正常状态；
                                                          1：单位增益反馈。 */
        unsigned char  buck2_regop_c   : 1;  /* bit[2]  : BUCK2内部regulator OP输出电容，用于调节OP的slew-rate。
                                                          0：slew-rate慢；
                                                          1：slew-rate快。 */
        unsigned char  buck2_reg_idr   : 2;  /* bit[3-4]: BUCK2内部regulator电流，用于调节regulator调整精度范围。
                                                          00：4uA；
                                                          01：6uA；
                                                          10：8uA；
                                                          11：10uA。 */
        unsigned char  buck2_reg_dr    : 3;  /* bit[5-7]: BUCK2内部regulator电阻，用于调节regulator调整精度范围。
                                                          000：+/-6mV；
                                                          001：+/-12mV；
                                                          010：+/-18mV；
                                                          011：+/-24mV；
                                                          100：+/-30mV；
                                                          101：+/-36mV；
                                                          110：+/-42mV；
                                                          111：+/-48mV。 */
    } reg;
} PMIC_BUCK2_CTRL4_UNION;
#endif
#define PMIC_BUCK2_CTRL4_buck2_short_pdp_START  (0)
#define PMIC_BUCK2_CTRL4_buck2_short_pdp_END    (0)
#define PMIC_BUCK2_CTRL4_buck2_reg_ss_d_START   (1)
#define PMIC_BUCK2_CTRL4_buck2_reg_ss_d_END     (1)
#define PMIC_BUCK2_CTRL4_buck2_regop_c_START    (2)
#define PMIC_BUCK2_CTRL4_buck2_regop_c_END      (2)
#define PMIC_BUCK2_CTRL4_buck2_reg_idr_START    (3)
#define PMIC_BUCK2_CTRL4_buck2_reg_idr_END      (4)
#define PMIC_BUCK2_CTRL4_buck2_reg_dr_START     (5)
#define PMIC_BUCK2_CTRL4_buck2_reg_dr_END       (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL5_UNION
 结构说明  : BUCK2_CTRL5 寄存器结构定义。地址偏移量:0x02A，初值:0x04，宽度:8
 寄存器说明: BUCK2控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ton      : 2;  /* bit[0-1]: BUCK2最小导通时间。
                                                         00：100ns；
                                                         01：200ns；
                                                         10：300ns；
                                                         11：400ns。 */
        unsigned char  buck2_nmos_off : 1;  /* bit[2]  : BUCK2用于关闭NMOS power管。
                                                         0：强制关闭；
                                                         1：不强制关闭。 */
        unsigned char  buck2_reg_c    : 1;  /* bit[3]  : BUCK2内部regulator电容，用于调节regulator带宽。
                                                         0：电容小；
                                                         1：电容大。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK2_CTRL5_UNION;
#endif
#define PMIC_BUCK2_CTRL5_buck2_ton_START       (0)
#define PMIC_BUCK2_CTRL5_buck2_ton_END         (1)
#define PMIC_BUCK2_CTRL5_buck2_nmos_off_START  (2)
#define PMIC_BUCK2_CTRL5_buck2_nmos_off_END    (2)
#define PMIC_BUCK2_CTRL5_buck2_reg_c_START     (3)
#define PMIC_BUCK2_CTRL5_buck2_reg_c_END       (3)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL6_UNION
 结构说明  : BUCK2_CTRL6 寄存器结构定义。地址偏移量:0x02B，初值:0x41，宽度:8
 寄存器说明: BUCK2控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_shield_i    : 2;  /* bit[0-1]: DMD屏蔽信号对应电流调节。
                                                            00：0.84A；
                                                            01：1.25A；
                                                            10：1.66A；
                                                            11：2.07A。 */
        unsigned char  buck2_new_dmd_sel : 5;  /* bit[2-6]: bit[6] DMD偏置电流选择。
                                                            0：2uA；
                                                            1：1uA。
                                                            bit[5] DMD方式选择。
                                                            0：老DMD；
                                                            1：新DMD。
                                                            bit[4:2] 新DMD结构DMD电流调节。
                                                            000：-60mA；
                                                            001：-24mA；
                                                            010：12mA；
                                                            011：50mA；
                                                            100：92mA；
                                                            101：132mA；
                                                            110：173mA；
                                                            111：214mA。 */
        unsigned char  reserved          : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_BUCK2_CTRL6_UNION;
#endif
#define PMIC_BUCK2_CTRL6_buck2_shield_i_START     (0)
#define PMIC_BUCK2_CTRL6_buck2_shield_i_END       (1)
#define PMIC_BUCK2_CTRL6_buck2_new_dmd_sel_START  (2)
#define PMIC_BUCK2_CTRL6_buck2_new_dmd_sel_END    (6)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL7_UNION
 结构说明  : BUCK2_CTRL7 寄存器结构定义。地址偏移量:0x02C，初值:0x1B，宽度:8
 寄存器说明: BUCK2控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_dmd_sel : 3;  /* bit[0-2]: BUCK2 老DMD结构DMD电流调节。
                                                        000：-80mA；
                                                        001：-45mA；
                                                        010：-10mA；
                                                        011：27mA；
                                                        100：70mA；
                                                        101：111mA；
                                                        110：150mA；
                                                        111：182mA。 */
        unsigned char  buck2_mos_sel : 2;  /* bit[3-4]: BUCK2 比较器内部电流调节。
                                                        00：增加0uA；
                                                        01：增加1uA；
                                                        10：增加2uA；
                                                        11：增加3uA。 */
        unsigned char  reserved      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_BUCK2_CTRL7_UNION;
#endif
#define PMIC_BUCK2_CTRL7_buck2_dmd_sel_START  (0)
#define PMIC_BUCK2_CTRL7_buck2_dmd_sel_END    (2)
#define PMIC_BUCK2_CTRL7_buck2_mos_sel_START  (3)
#define PMIC_BUCK2_CTRL7_buck2_mos_sel_END    (4)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL8_UNION
 结构说明  : BUCK2_CTRL8 寄存器结构定义。地址偏移量:0x02D，初值:0x00，宽度:8
 寄存器说明: BUCK2控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reserve0 : 8;  /* bit[0-7]: BUCK2备用寄存器。 */
    } reg;
} PMIC_BUCK2_CTRL8_UNION;
#endif
#define PMIC_BUCK2_CTRL8_buck2_reserve0_START  (0)
#define PMIC_BUCK2_CTRL8_buck2_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL9_UNION
 结构说明  : BUCK2_CTRL9 寄存器结构定义。地址偏移量:0x02E，初值:0x00，宽度:8
 寄存器说明: BUCK2控制寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reserve1 : 8;  /* bit[0-7]: BUCK2备用寄存器。 */
    } reg;
} PMIC_BUCK2_CTRL9_UNION;
#endif
#define PMIC_BUCK2_CTRL9_buck2_reserve1_START  (0)
#define PMIC_BUCK2_CTRL9_buck2_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL10_UNION
 结构说明  : BUCK2_CTRL10 寄存器结构定义。地址偏移量:0x02F，初值:0x00，宽度:8
 寄存器说明: BUCK2控制寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reserve2 : 8;  /* bit[0-7]: BUCK2备用寄存器。 */
    } reg;
} PMIC_BUCK2_CTRL10_UNION;
#endif
#define PMIC_BUCK2_CTRL10_buck2_reserve2_START  (0)
#define PMIC_BUCK2_CTRL10_buck2_reserve2_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL11_UNION
 结构说明  : BUCK2_CTRL11 寄存器结构定义。地址偏移量:0x030，初值:0x00，宽度:8
 寄存器说明: BUCK2控制寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_pdn_lx_det     : 1;  /* bit[0]: BUCK1 比较器增强迟滞选择。
                                                             0：不增加迟滞量；
                                                             1：增加迟滞量。 */
        unsigned char  buck2_eco_dmd        : 1;  /* bit[1]: 在正常模式下强制NMOS管关闭。
                                                             0：不强制；
                                                             1：强制。 */
        unsigned char  buck2_dmd_shield_n   : 1;  /* bit[2]: 大电流下DMD屏蔽信号。
                                                             0：屏蔽；
                                                             1：不屏蔽。 */
        unsigned char  buck2_ocp_delay_sel  : 1;  /* bit[3]: OCP屏蔽时间延长15ns信号。
                                                             0：不延长；
                                                             1：延长。 */
        unsigned char  buck2_dmd_clamp      : 1;  /* bit[4]: 老DMD嵌位使能信号。
                                                             0：加上；
                                                             1：不加上。 */
        unsigned char  buck2_en_regop_clamp : 1;  /* bit[5]: regulator 嵌位电路使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned char  buck2_en_ss_sel      : 1;  /* bit[6]: 选择软起完成信号。
                                                             0：模拟给出；
                                                             1：数字给出。 */
        unsigned char  reserved             : 1;  /* bit[7]: 保留。 */
    } reg;
} PMIC_BUCK2_CTRL11_UNION;
#endif
#define PMIC_BUCK2_CTRL11_buck2_pdn_lx_det_START      (0)
#define PMIC_BUCK2_CTRL11_buck2_pdn_lx_det_END        (0)
#define PMIC_BUCK2_CTRL11_buck2_eco_dmd_START         (1)
#define PMIC_BUCK2_CTRL11_buck2_eco_dmd_END           (1)
#define PMIC_BUCK2_CTRL11_buck2_dmd_shield_n_START    (2)
#define PMIC_BUCK2_CTRL11_buck2_dmd_shield_n_END      (2)
#define PMIC_BUCK2_CTRL11_buck2_ocp_delay_sel_START   (3)
#define PMIC_BUCK2_CTRL11_buck2_ocp_delay_sel_END     (3)
#define PMIC_BUCK2_CTRL11_buck2_dmd_clamp_START       (4)
#define PMIC_BUCK2_CTRL11_buck2_dmd_clamp_END         (4)
#define PMIC_BUCK2_CTRL11_buck2_en_regop_clamp_START  (5)
#define PMIC_BUCK2_CTRL11_buck2_en_regop_clamp_END    (5)
#define PMIC_BUCK2_CTRL11_buck2_en_ss_sel_START       (6)
#define PMIC_BUCK2_CTRL11_buck2_en_ss_sel_END         (6)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL0_UNION
 结构说明  : BUCK3_CTRL0 寄存器结构定义。地址偏移量:0x031，初值:0x83，宽度:8
 寄存器说明: BUCK3控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_adj_clx : 4;  /* bit[0-3]: bit[3]：发生DMD时关闭部分功率管。
                                                        0：不关闭；
                                                        1：关闭。
                                                        bit[2:0]：LX反馈滤波电容调节。
                                                        000：10pF；
                                                        001：20pF；
                                                        010：30pF；
                                                        011：40pF；
                                                        100：30pF；
                                                        101：40pF；
                                                        110：50pF；
                                                        111：60pF。 */
        unsigned char  buck3_adj_rlx : 4;  /* bit[4-7]: BUCK3 LX反馈滤波电阻调节。
                                                        0000：3.4MΩ；
                                                        0001：3.2MΩ；
                                                        0010：2.8MΩ；
                                                        0011：2.6MΩ；
                                                        0100：2.4MΩ；
                                                        0101：2.2MΩ；
                                                        0110：2.0MΩ；
                                                        0111：1.8MΩ；
                                                        1000：1.6MΩ；
                                                        1001：1.4MΩ；
                                                        1010：1.2MΩ；
                                                        1011：1.0MΩ；
                                                        1100：0.8MΩ；
                                                        1101：0.6MΩ；
                                                        1110：0.4MΩ；
                                                        1111：0.2MΩ。 */
    } reg;
} PMIC_BUCK3_CTRL0_UNION;
#endif
#define PMIC_BUCK3_CTRL0_buck3_adj_clx_START  (0)
#define PMIC_BUCK3_CTRL0_buck3_adj_clx_END    (3)
#define PMIC_BUCK3_CTRL0_buck3_adj_rlx_START  (4)
#define PMIC_BUCK3_CTRL0_buck3_adj_rlx_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL1_UNION
 结构说明  : BUCK3_CTRL1 寄存器结构定义。地址偏移量:0x032，初值:0x40，宽度:8
 寄存器说明: BUCK3控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ng_dt_sel : 1;  /* bit[0]  : BUCK3 P管到N管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck3_pg_dt_sel : 1;  /* bit[1]  : BUCK3 N管到P管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck3_sft_sel   : 1;  /* bit[2]  : BUCK3软启动方式选择。
                                                          0：软启动时间为200us左右；
                                                          1：软启动时间为100us左右。 */
        unsigned char  reserved        : 1;  /* bit[3]  : 保留。 */
        unsigned char  buck3_dt_sel    : 2;  /* bit[4-5]: 死区时间调节。
                                                          0：不额外延迟5ns；
                                                          1：额外延迟5ns。 */
        unsigned char  buck3_ocp_sel   : 2;  /* bit[6-7]: BUCK3 OCP点调整。
                                                          00：3.24A；
                                                          01：3.69A；
                                                          10：4.13A；
                                                          11：4.57A。 */
    } reg;
} PMIC_BUCK3_CTRL1_UNION;
#endif
#define PMIC_BUCK3_CTRL1_buck3_ng_dt_sel_START  (0)
#define PMIC_BUCK3_CTRL1_buck3_ng_dt_sel_END    (0)
#define PMIC_BUCK3_CTRL1_buck3_pg_dt_sel_START  (1)
#define PMIC_BUCK3_CTRL1_buck3_pg_dt_sel_END    (1)
#define PMIC_BUCK3_CTRL1_buck3_sft_sel_START    (2)
#define PMIC_BUCK3_CTRL1_buck3_sft_sel_END      (2)
#define PMIC_BUCK3_CTRL1_buck3_dt_sel_START     (4)
#define PMIC_BUCK3_CTRL1_buck3_dt_sel_END       (5)
#define PMIC_BUCK3_CTRL1_buck3_ocp_sel_START    (6)
#define PMIC_BUCK3_CTRL1_buck3_ocp_sel_END      (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL2_UNION
 结构说明  : BUCK3_CTRL2 寄存器结构定义。地址偏移量:0x033，初值:0x3C，宽度:8
 寄存器说明: BUCK3控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ng_n_sel : 2;  /* bit[0-1]: BUCK3 N power管驱动对应NMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
        unsigned char  buck3_ng_p_sel : 2;  /* bit[2-3]: BUCK3 N power管驱动对应PMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck3_pg_n_sel : 2;  /* bit[4-5]: BUCK3 P power管驱动对应NMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck3_pg_p_sel : 2;  /* bit[6-7]: BUCK3 P power管驱动对应PMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
    } reg;
} PMIC_BUCK3_CTRL2_UNION;
#endif
#define PMIC_BUCK3_CTRL2_buck3_ng_n_sel_START  (0)
#define PMIC_BUCK3_CTRL2_buck3_ng_n_sel_END    (1)
#define PMIC_BUCK3_CTRL2_buck3_ng_p_sel_START  (2)
#define PMIC_BUCK3_CTRL2_buck3_ng_p_sel_END    (3)
#define PMIC_BUCK3_CTRL2_buck3_pg_n_sel_START  (4)
#define PMIC_BUCK3_CTRL2_buck3_pg_n_sel_END    (5)
#define PMIC_BUCK3_CTRL2_buck3_pg_p_sel_START  (6)
#define PMIC_BUCK3_CTRL2_buck3_pg_p_sel_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL3_UNION
 结构说明  : BUCK3_CTRL3 寄存器结构定义。地址偏移量:0x034，初值:0x20，宽度:8
 寄存器说明: BUCK3控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reg_r  : 2;  /* bit[0-1]: BUCK3内部regulator电阻，用于调节regulator带宽。
                                                       00：2.8kHz；
                                                       01：45kHz；
                                                       10：85kHz；
                                                       11：152kHz。 */
        unsigned char  reserved     : 2;  /* bit[2-3]: 保留。 */
        unsigned char  buck3_reg_en : 1;  /* bit[4]  : BUCK3内部精度调整器使能信号。
                                                       0：使能；
                                                       1：不使能。 */
        unsigned char  buck3_dbias  : 2;  /* bit[5-6]: BUCK3 比较器偏置电流调节。
                                                       00：2uA；
                                                       01：1uA；
                                                       10：4uA；
                                                       11：3uA。 */
        unsigned char  buck3_ocp_d  : 1;  /* bit[7]  : BUCK3 内部OCP环路屏蔽信号。
                                                       0：不屏蔽；
                                                       1：屏蔽。 */
    } reg;
} PMIC_BUCK3_CTRL3_UNION;
#endif
#define PMIC_BUCK3_CTRL3_buck3_reg_r_START   (0)
#define PMIC_BUCK3_CTRL3_buck3_reg_r_END     (1)
#define PMIC_BUCK3_CTRL3_buck3_reg_en_START  (4)
#define PMIC_BUCK3_CTRL3_buck3_reg_en_END    (4)
#define PMIC_BUCK3_CTRL3_buck3_dbias_START   (5)
#define PMIC_BUCK3_CTRL3_buck3_dbias_END     (6)
#define PMIC_BUCK3_CTRL3_buck3_ocp_d_START   (7)
#define PMIC_BUCK3_CTRL3_buck3_ocp_d_END     (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL4_UNION
 结构说明  : BUCK3_CTRL4 寄存器结构定义。地址偏移量:0x035，初值:0x20，宽度:8
 寄存器说明: BUCK3控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_short_pdp : 1;  /* bit[0]  : 短路保护屏蔽寄存器。
                                                          0：使能短路保护，0.4V门限；
                                                          1：不使能短路保护，0V门限。 */
        unsigned char  buck3_reg_ss_d  : 1;  /* bit[1]  : BUCK3软启动时内部regulator状态。
                                                          0：正常状态；
                                                          1：单位增益反馈。 */
        unsigned char  buck3_regop_c   : 1;  /* bit[2]  : BUCK3内部regulator OP输出电容，用于调节OP的slew-rate。
                                                          0：slew-rate慢；
                                                          1：slew-rate快。 */
        unsigned char  buck3_reg_idr   : 2;  /* bit[3-4]: BUCK3内部regulator电流，用于调节regulator调整精度范围。
                                                          00：4uA；
                                                          01：6uA；
                                                          10：8uA；
                                                          11：10uA。 */
        unsigned char  buck3_reg_dr    : 3;  /* bit[5-7]: BUCK3内部regulator电阻，用于调节regulator调整精度范围。
                                                          000：+/-6mV；
                                                          001：+/-12mV；
                                                          010：+/-18mV；
                                                          011：+/-24mV；
                                                          100：+/-30mV；
                                                          101：+/-36mV；
                                                          110：+/-42mV；
                                                          111：+/-48mV。 */
    } reg;
} PMIC_BUCK3_CTRL4_UNION;
#endif
#define PMIC_BUCK3_CTRL4_buck3_short_pdp_START  (0)
#define PMIC_BUCK3_CTRL4_buck3_short_pdp_END    (0)
#define PMIC_BUCK3_CTRL4_buck3_reg_ss_d_START   (1)
#define PMIC_BUCK3_CTRL4_buck3_reg_ss_d_END     (1)
#define PMIC_BUCK3_CTRL4_buck3_regop_c_START    (2)
#define PMIC_BUCK3_CTRL4_buck3_regop_c_END      (2)
#define PMIC_BUCK3_CTRL4_buck3_reg_idr_START    (3)
#define PMIC_BUCK3_CTRL4_buck3_reg_idr_END      (4)
#define PMIC_BUCK3_CTRL4_buck3_reg_dr_START     (5)
#define PMIC_BUCK3_CTRL4_buck3_reg_dr_END       (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL5_UNION
 结构说明  : BUCK3_CTRL5 寄存器结构定义。地址偏移量:0x036，初值:0x04，宽度:8
 寄存器说明: BUCK3控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ton      : 2;  /* bit[0-1]: BUCK3最小导通时间。
                                                         00：100ns；
                                                         01：200ns；
                                                         10：300ns；
                                                         11：400ns。 */
        unsigned char  buck3_nmos_off : 1;  /* bit[2]  : BUCK3用于关闭NMOS power管。
                                                         0：强制关闭；
                                                         1：不强制关闭。 */
        unsigned char  buck3_reg_c    : 1;  /* bit[3]  : BUCK3内部regulator电容，用于调节regulator带宽。
                                                         0：电容小；
                                                         1：电容大。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK3_CTRL5_UNION;
#endif
#define PMIC_BUCK3_CTRL5_buck3_ton_START       (0)
#define PMIC_BUCK3_CTRL5_buck3_ton_END         (1)
#define PMIC_BUCK3_CTRL5_buck3_nmos_off_START  (2)
#define PMIC_BUCK3_CTRL5_buck3_nmos_off_END    (2)
#define PMIC_BUCK3_CTRL5_buck3_reg_c_START     (3)
#define PMIC_BUCK3_CTRL5_buck3_reg_c_END       (3)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL6_UNION
 结构说明  : BUCK3_CTRL6 寄存器结构定义。地址偏移量:0x037，初值:0x41，宽度:8
 寄存器说明: BUCK3控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_shield_i    : 2;  /* bit[0-1]: DMD屏蔽信号对应电流调节。
                                                            00：0.84A；
                                                            01：1.25A；
                                                            10：1.66A；
                                                            11：2.07A。 */
        unsigned char  buck3_new_dmd_sel : 5;  /* bit[2-6]: bit[6]：DMD偏置电流选择。
                                                            0：2uA；
                                                            1：1uA。
                                                            bit[5]：DMD方式选择。
                                                            0：老DMD；
                                                            1：新DMD。
                                                            Bit[4:2]：新DMD结构DMD电流调节。
                                                            000：38mA；
                                                            001：-92mA；
                                                            010：-45mA；
                                                            011：3mA；
                                                            100：82mA；
                                                            101：130mA；
                                                            110：173mA；
                                                            111：219mA。 */
        unsigned char  reserved          : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_BUCK3_CTRL6_UNION;
#endif
#define PMIC_BUCK3_CTRL6_buck3_shield_i_START     (0)
#define PMIC_BUCK3_CTRL6_buck3_shield_i_END       (1)
#define PMIC_BUCK3_CTRL6_buck3_new_dmd_sel_START  (2)
#define PMIC_BUCK3_CTRL6_buck3_new_dmd_sel_END    (6)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL7_UNION
 结构说明  : BUCK3_CTRL7 寄存器结构定义。地址偏移量:0x038，初值:0x1B，宽度:8
 寄存器说明: BUCK3控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_dmd_sel : 3;  /* bit[0-2]: BUCK3 老DMD结构DMD电流调节。
                                                        000：-74mA；
                                                        001：-35mA；
                                                        010：-3mA；
                                                        011：35mA；
                                                        100：78mA；
                                                        101：122mA；
                                                        110：167mA；
                                                        111：210mA。 */
        unsigned char  buck3_mos_sel : 2;  /* bit[3-4]: BUCK3 比较器内部电流调节。
                                                        00：增加0uA；
                                                        01：增加1uA；
                                                        10：增加2uA；
                                                        11：增加3uA。 */
        unsigned char  reserved      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_BUCK3_CTRL7_UNION;
#endif
#define PMIC_BUCK3_CTRL7_buck3_dmd_sel_START  (0)
#define PMIC_BUCK3_CTRL7_buck3_dmd_sel_END    (2)
#define PMIC_BUCK3_CTRL7_buck3_mos_sel_START  (3)
#define PMIC_BUCK3_CTRL7_buck3_mos_sel_END    (4)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL8_UNION
 结构说明  : BUCK3_CTRL8 寄存器结构定义。地址偏移量:0x039，初值:0x00，宽度:8
 寄存器说明: BUCK3控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reserve0 : 8;  /* bit[0-7]: BUCK3备用寄存器。 */
    } reg;
} PMIC_BUCK3_CTRL8_UNION;
#endif
#define PMIC_BUCK3_CTRL8_buck3_reserve0_START  (0)
#define PMIC_BUCK3_CTRL8_buck3_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL9_UNION
 结构说明  : BUCK3_CTRL9 寄存器结构定义。地址偏移量:0x03A，初值:0x00，宽度:8
 寄存器说明: BUCK3控制寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reserve1 : 8;  /* bit[0-7]: BUCK3备用寄存器。 */
    } reg;
} PMIC_BUCK3_CTRL9_UNION;
#endif
#define PMIC_BUCK3_CTRL9_buck3_reserve1_START  (0)
#define PMIC_BUCK3_CTRL9_buck3_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL10_UNION
 结构说明  : BUCK3_CTRL10 寄存器结构定义。地址偏移量:0x03B，初值:0x00，宽度:8
 寄存器说明: BUCK3控制寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reserve2 : 8;  /* bit[0-7]: BUCK3备用寄存器。 */
    } reg;
} PMIC_BUCK3_CTRL10_UNION;
#endif
#define PMIC_BUCK3_CTRL10_buck3_reserve2_START  (0)
#define PMIC_BUCK3_CTRL10_buck3_reserve2_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL11_UNION
 结构说明  : BUCK3_CTRL11 寄存器结构定义。地址偏移量:0x03C，初值:0x00，宽度:8
 寄存器说明: BUCK3控制寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_pdn_lx_det     : 1;  /* bit[0]: BUCK3 比较器增强迟滞选择。
                                                             0：不增加迟滞量；
                                                             1：增加迟滞量。 */
        unsigned char  buck3_eco_dmd        : 1;  /* bit[1]: 在正常模式下强制NMOS管关闭。
                                                             0：不强制；
                                                             1：强制。 */
        unsigned char  buck3_dmd_shield_n   : 1;  /* bit[2]: 大电流下DMD屏蔽信号。
                                                             0：屏蔽；
                                                             1：不屏蔽。 */
        unsigned char  buck3_ocp_delay_sel  : 1;  /* bit[3]: OCP屏蔽时间延长15ns信号。
                                                             0：不延长；
                                                             1：延长。 */
        unsigned char  buck3_dmd_clamp      : 1;  /* bit[4]: 老DMD嵌位使能信号。
                                                             0：加上；
                                                             1：不加上。 */
        unsigned char  buck3_en_regop_clamp : 1;  /* bit[5]: regulator 嵌位电路使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned char  buck3_en_ss_sel      : 1;  /* bit[6]: 选择软起完成信号。
                                                             0：模拟给出；
                                                             1：数字给出。 */
        unsigned char  reserved             : 1;  /* bit[7]: 保留。 */
    } reg;
} PMIC_BUCK3_CTRL11_UNION;
#endif
#define PMIC_BUCK3_CTRL11_buck3_pdn_lx_det_START      (0)
#define PMIC_BUCK3_CTRL11_buck3_pdn_lx_det_END        (0)
#define PMIC_BUCK3_CTRL11_buck3_eco_dmd_START         (1)
#define PMIC_BUCK3_CTRL11_buck3_eco_dmd_END           (1)
#define PMIC_BUCK3_CTRL11_buck3_dmd_shield_n_START    (2)
#define PMIC_BUCK3_CTRL11_buck3_dmd_shield_n_END      (2)
#define PMIC_BUCK3_CTRL11_buck3_ocp_delay_sel_START   (3)
#define PMIC_BUCK3_CTRL11_buck3_ocp_delay_sel_END     (3)
#define PMIC_BUCK3_CTRL11_buck3_dmd_clamp_START       (4)
#define PMIC_BUCK3_CTRL11_buck3_dmd_clamp_END         (4)
#define PMIC_BUCK3_CTRL11_buck3_en_regop_clamp_START  (5)
#define PMIC_BUCK3_CTRL11_buck3_en_regop_clamp_END    (5)
#define PMIC_BUCK3_CTRL11_buck3_en_ss_sel_START       (6)
#define PMIC_BUCK3_CTRL11_buck3_en_ss_sel_END         (6)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL0_UNION
 结构说明  : BUCK4_CTRL0 寄存器结构定义。地址偏移量:0x03D，初值:0x83，宽度:8
 寄存器说明: BUCK4控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_adj_clx : 4;  /* bit[0-3]: bit[3]：发生DMD时关闭部分功率管。
                                                        0：不关闭；
                                                        1：关闭。
                                                        bit[2:0]：LX反馈滤波电容调节。
                                                        000：10pF；
                                                        001：20pF；
                                                        010：30pF；
                                                        011：40pF；
                                                        100：30pF；
                                                        101：40pF；
                                                        110：50pF；
                                                        111：60pF。 */
        unsigned char  buck4_adj_rlx : 4;  /* bit[4-7]: BUCK4 LX反馈滤波电阻调节。
                                                        0000：3.4MΩ；
                                                        0001：3.2MΩ；
                                                        0010：2.8MΩ；
                                                        0011：2.6MΩ；
                                                        0100：2.4MΩ；
                                                        0101：2.2MΩ；
                                                        0110：2.0MΩ；
                                                        0111：1.8MΩ；
                                                        1000：1.6MΩ；
                                                        1001：1.4MΩ；
                                                        1010：1.2MΩ；
                                                        1011：1.0MΩ；
                                                        1100：0.8MΩ；
                                                        1101：0.6MΩ；
                                                        1110：0.4MΩ；
                                                        1111：0.2MΩ。 */
    } reg;
} PMIC_BUCK4_CTRL0_UNION;
#endif
#define PMIC_BUCK4_CTRL0_buck4_adj_clx_START  (0)
#define PMIC_BUCK4_CTRL0_buck4_adj_clx_END    (3)
#define PMIC_BUCK4_CTRL0_buck4_adj_rlx_START  (4)
#define PMIC_BUCK4_CTRL0_buck4_adj_rlx_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL1_UNION
 结构说明  : BUCK4_CTRL1 寄存器结构定义。地址偏移量:0x03E，初值:0x40，宽度:8
 寄存器说明: BUCK4控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_ng_dt_sel : 1;  /* bit[0]  : BUCK4 P管到N管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck4_pg_dt_sel : 1;  /* bit[1]  : BUCK4 N管到P管死区模式选择。
                                                          0：不并入新死区控制模式；
                                                          1：并入新死区控制模式。 */
        unsigned char  buck4_sft_sel   : 1;  /* bit[2]  : BUCK4软启动方式选择。
                                                          0：软启动时间为200us左右；
                                                          1：软启动时间为100us左右。 */
        unsigned char  reserved        : 1;  /* bit[3]  : 保留。 */
        unsigned char  buck4_dt_sel    : 2;  /* bit[4-5]: 死区时间调节。
                                                          0：不额外延迟5ns；
                                                          1：额外延迟5ns。 */
        unsigned char  buck4_ocp_sel   : 2;  /* bit[6-7]: BUCK4 OCP点调整。
                                                          00：3.24A；
                                                          01：3.69A；
                                                          10：4.13A；
                                                          11：4.57A。 */
    } reg;
} PMIC_BUCK4_CTRL1_UNION;
#endif
#define PMIC_BUCK4_CTRL1_buck4_ng_dt_sel_START  (0)
#define PMIC_BUCK4_CTRL1_buck4_ng_dt_sel_END    (0)
#define PMIC_BUCK4_CTRL1_buck4_pg_dt_sel_START  (1)
#define PMIC_BUCK4_CTRL1_buck4_pg_dt_sel_END    (1)
#define PMIC_BUCK4_CTRL1_buck4_sft_sel_START    (2)
#define PMIC_BUCK4_CTRL1_buck4_sft_sel_END      (2)
#define PMIC_BUCK4_CTRL1_buck4_dt_sel_START     (4)
#define PMIC_BUCK4_CTRL1_buck4_dt_sel_END       (5)
#define PMIC_BUCK4_CTRL1_buck4_ocp_sel_START    (6)
#define PMIC_BUCK4_CTRL1_buck4_ocp_sel_END      (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL2_UNION
 结构说明  : BUCK4_CTRL2 寄存器结构定义。地址偏移量:0x03F，初值:0x3C，宽度:8
 寄存器说明: BUCK4控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_ng_n_sel : 2;  /* bit[0-1]: BUCK4 N power管驱动对应NMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
        unsigned char  buck4_ng_p_sel : 2;  /* bit[2-3]: BUCK4 N power管驱动对应PMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck4_pg_n_sel : 2;  /* bit[4-5]: BUCK4 P power管驱动对应NMOS驱动能力调节。
                                                         00：4倍驱动；
                                                         01：3倍驱动；
                                                         10：2倍驱动；
                                                         11：1倍驱动。 */
        unsigned char  buck4_pg_p_sel : 2;  /* bit[6-7]: BUCK4 P power管驱动对应PMOS驱动能力调节。
                                                         00：1倍驱动；
                                                         01：2倍驱动；
                                                         10：3倍驱动；
                                                         11：4倍驱动。 */
    } reg;
} PMIC_BUCK4_CTRL2_UNION;
#endif
#define PMIC_BUCK4_CTRL2_buck4_ng_n_sel_START  (0)
#define PMIC_BUCK4_CTRL2_buck4_ng_n_sel_END    (1)
#define PMIC_BUCK4_CTRL2_buck4_ng_p_sel_START  (2)
#define PMIC_BUCK4_CTRL2_buck4_ng_p_sel_END    (3)
#define PMIC_BUCK4_CTRL2_buck4_pg_n_sel_START  (4)
#define PMIC_BUCK4_CTRL2_buck4_pg_n_sel_END    (5)
#define PMIC_BUCK4_CTRL2_buck4_pg_p_sel_START  (6)
#define PMIC_BUCK4_CTRL2_buck4_pg_p_sel_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL3_UNION
 结构说明  : BUCK4_CTRL3 寄存器结构定义。地址偏移量:0x040，初值:0x20，宽度:8
 寄存器说明: BUCK4控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_reg_r  : 2;  /* bit[0-1]: BUCK4内部regulator电阻，用于调节regulator带宽。
                                                       00：2.8kHz；
                                                       01：45kHz；
                                                       10：85kHz；
                                                       11：152kHz。 */
        unsigned char  reserved     : 2;  /* bit[2-3]: 保留。 */
        unsigned char  buck4_reg_en : 1;  /* bit[4]  : BUCK4内部精度调整器使能信号。
                                                       0：使能；
                                                       1：不使能。 */
        unsigned char  buck4_dbias  : 2;  /* bit[5-6]: BUCK4 比较器偏置电流调节。
                                                       00：2uA；
                                                       01：1uA；
                                                       10：4uA；
                                                       11：3uA。 */
        unsigned char  buck4_ocp_d  : 1;  /* bit[7]  : BUCK4 内部OCP环路屏蔽信号。
                                                       0：不屏蔽；
                                                       1：屏蔽。 */
    } reg;
} PMIC_BUCK4_CTRL3_UNION;
#endif
#define PMIC_BUCK4_CTRL3_buck4_reg_r_START   (0)
#define PMIC_BUCK4_CTRL3_buck4_reg_r_END     (1)
#define PMIC_BUCK4_CTRL3_buck4_reg_en_START  (4)
#define PMIC_BUCK4_CTRL3_buck4_reg_en_END    (4)
#define PMIC_BUCK4_CTRL3_buck4_dbias_START   (5)
#define PMIC_BUCK4_CTRL3_buck4_dbias_END     (6)
#define PMIC_BUCK4_CTRL3_buck4_ocp_d_START   (7)
#define PMIC_BUCK4_CTRL3_buck4_ocp_d_END     (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL4_UNION
 结构说明  : BUCK4_CTRL4 寄存器结构定义。地址偏移量:0x041，初值:0x20，宽度:8
 寄存器说明: BUCK4控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_short_pdp : 1;  /* bit[0]  : 短路保护屏蔽寄存器。
                                                          0：使能短路保护，0.4V门限；
                                                          1：不使能短路保护，0V门限。 */
        unsigned char  buck4_reg_ss_d  : 1;  /* bit[1]  : BUCK4软启动时内部regulator状态。
                                                          0：正常状态；
                                                          1：单位增益反馈。 */
        unsigned char  buck4_regop_c   : 1;  /* bit[2]  : BUCK4内部regulator OP输出电容，用于调节OP的slew-rate。
                                                          0：slew-rate慢；
                                                          1：slew-rate快。 */
        unsigned char  buck4_reg_idr   : 2;  /* bit[3-4]: BUCK4内部regulator电流，用于调节regulator调整精度范围。
                                                          00：4uA；
                                                          01：6uA；
                                                          10：8uA；
                                                          11：10uA。 */
        unsigned char  buck4_reg_dr    : 3;  /* bit[5-7]: BUCK4内部regulator电阻，用于调节regulator调整精度范围。
                                                          000：+/-6mV；
                                                          001：+/-12mV；
                                                          010：+/-18mV；
                                                          011：+/-24mV；
                                                          100：+/-30mV；
                                                          101：+/-36mV；
                                                          110：+/-42mV；
                                                          111：+/-48mV。 */
    } reg;
} PMIC_BUCK4_CTRL4_UNION;
#endif
#define PMIC_BUCK4_CTRL4_buck4_short_pdp_START  (0)
#define PMIC_BUCK4_CTRL4_buck4_short_pdp_END    (0)
#define PMIC_BUCK4_CTRL4_buck4_reg_ss_d_START   (1)
#define PMIC_BUCK4_CTRL4_buck4_reg_ss_d_END     (1)
#define PMIC_BUCK4_CTRL4_buck4_regop_c_START    (2)
#define PMIC_BUCK4_CTRL4_buck4_regop_c_END      (2)
#define PMIC_BUCK4_CTRL4_buck4_reg_idr_START    (3)
#define PMIC_BUCK4_CTRL4_buck4_reg_idr_END      (4)
#define PMIC_BUCK4_CTRL4_buck4_reg_dr_START     (5)
#define PMIC_BUCK4_CTRL4_buck4_reg_dr_END       (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL5_UNION
 结构说明  : BUCK4_CTRL5 寄存器结构定义。地址偏移量:0x042，初值:0x04，宽度:8
 寄存器说明: BUCK4控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_ton      : 2;  /* bit[0-1]: BUCK4最小导通时间。
                                                         00：100ns；
                                                         01：200ns；
                                                         10：300ns；
                                                         11：400ns。 */
        unsigned char  buck4_nmos_off : 1;  /* bit[2]  : BUCK4用于关闭NMOS power管。
                                                         0：强制关闭；
                                                         1：不强制关闭。 */
        unsigned char  buck4_reg_c    : 1;  /* bit[3]  : BUCK4内部regulator电容，用于调节regulator带宽。
                                                         0：电容小；
                                                         1：电容大。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK4_CTRL5_UNION;
#endif
#define PMIC_BUCK4_CTRL5_buck4_ton_START       (0)
#define PMIC_BUCK4_CTRL5_buck4_ton_END         (1)
#define PMIC_BUCK4_CTRL5_buck4_nmos_off_START  (2)
#define PMIC_BUCK4_CTRL5_buck4_nmos_off_END    (2)
#define PMIC_BUCK4_CTRL5_buck4_reg_c_START     (3)
#define PMIC_BUCK4_CTRL5_buck4_reg_c_END       (3)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL6_UNION
 结构说明  : BUCK4_CTRL6 寄存器结构定义。地址偏移量:0x043，初值:0x41，宽度:8
 寄存器说明: BUCK4控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_shield_i    : 2;  /* bit[0-1]: DMD屏蔽信号对应电流调节。
                                                            00：0.84A；
                                                            01：1.25A；
                                                            10：1.66A；
                                                            11：2.07A。 */
        unsigned char  buck4_new_dmd_sel : 5;  /* bit[2-6]: bit[6]：DMD偏置电流选择。
                                                            0：2uA；
                                                            1：1uA。
                                                            bit[5]：DMD方式选择。
                                                            0：老DMD；
                                                            1：新DMD。
                                                            Bit[4:2]：新DMD结构DMD电流调节。
                                                            000：28mA；
                                                            001：-75mA；
                                                            010：-40mA；
                                                            011：-12mA；
                                                            100：70mA；
                                                            101：120mA；
                                                            110：162mA；
                                                            111：205mA。 */
        unsigned char  reserved          : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_BUCK4_CTRL6_UNION;
#endif
#define PMIC_BUCK4_CTRL6_buck4_shield_i_START     (0)
#define PMIC_BUCK4_CTRL6_buck4_shield_i_END       (1)
#define PMIC_BUCK4_CTRL6_buck4_new_dmd_sel_START  (2)
#define PMIC_BUCK4_CTRL6_buck4_new_dmd_sel_END    (6)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL7_UNION
 结构说明  : BUCK4_CTRL7 寄存器结构定义。地址偏移量:0x044，初值:0x1B，宽度:8
 寄存器说明: BUCK4控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_dmd_sel : 3;  /* bit[0-2]: BUCK4 老DMD结构DMD电流调节。
                                                        000：-45mA；
                                                        001：-5mA；
                                                        010：27mA；
                                                        011：70mA；
                                                        100：105mA；
                                                        101：144mA；
                                                        110：185mA；
                                                        111：228mA。 */
        unsigned char  buck4_mos_sel : 2;  /* bit[3-4]: BUCK4 比较器内部电流调节。
                                                        00：增加0uA；
                                                        01：增加1uA；
                                                        10：增加2uA；
                                                        11：增加3uA。 */
        unsigned char  reserved      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_BUCK4_CTRL7_UNION;
#endif
#define PMIC_BUCK4_CTRL7_buck4_dmd_sel_START  (0)
#define PMIC_BUCK4_CTRL7_buck4_dmd_sel_END    (2)
#define PMIC_BUCK4_CTRL7_buck4_mos_sel_START  (3)
#define PMIC_BUCK4_CTRL7_buck4_mos_sel_END    (4)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL8_UNION
 结构说明  : BUCK4_CTRL8 寄存器结构定义。地址偏移量:0x045，初值:0x00，宽度:8
 寄存器说明: BUCK4控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_reserve0 : 8;  /* bit[0-7]: BUCK4备用寄存器。 */
    } reg;
} PMIC_BUCK4_CTRL8_UNION;
#endif
#define PMIC_BUCK4_CTRL8_buck4_reserve0_START  (0)
#define PMIC_BUCK4_CTRL8_buck4_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL9_UNION
 结构说明  : BUCK4_CTRL9 寄存器结构定义。地址偏移量:0x046，初值:0x00，宽度:8
 寄存器说明: BUCK4控制寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_reserve1 : 8;  /* bit[0-7]: BUCK4备用寄存器。 */
    } reg;
} PMIC_BUCK4_CTRL9_UNION;
#endif
#define PMIC_BUCK4_CTRL9_buck4_reserve1_START  (0)
#define PMIC_BUCK4_CTRL9_buck4_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL10_UNION
 结构说明  : BUCK4_CTRL10 寄存器结构定义。地址偏移量:0x047，初值:0x00，宽度:8
 寄存器说明: BUCK4控制寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_reserve2 : 8;  /* bit[0-7]: BUCK4备用寄存器。 */
    } reg;
} PMIC_BUCK4_CTRL10_UNION;
#endif
#define PMIC_BUCK4_CTRL10_buck4_reserve2_START  (0)
#define PMIC_BUCK4_CTRL10_buck4_reserve2_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_CTRL11_UNION
 结构说明  : BUCK4_CTRL11 寄存器结构定义。地址偏移量:0x048，初值:0x00，宽度:8
 寄存器说明: BUCK4控制寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_pdn_lx_det     : 1;  /* bit[0]: BUCK3 比较器增强迟滞选择。
                                                             0：不增加迟滞量；
                                                             1：增加迟滞量。 */
        unsigned char  buck4_eco_dmd        : 1;  /* bit[1]: 在正常模式下强制NMOS管关闭。
                                                             0：不强制；
                                                             1：强制。 */
        unsigned char  buck4_dmd_shield_n   : 1;  /* bit[2]: 大电流下DMD屏蔽信号。
                                                             0：屏蔽；
                                                             1：不屏蔽。 */
        unsigned char  buck4_ocp_delay_sel  : 1;  /* bit[3]: OCP屏蔽时间延长15ns信号。
                                                             0：不延长；
                                                             1：延长。 */
        unsigned char  buck4_dmd_clamp      : 1;  /* bit[4]: 老DMD嵌位使能信号。
                                                             0：加上；
                                                             1：不加上。 */
        unsigned char  buck4_en_regop_clamp : 1;  /* bit[5]: regulator 嵌位电路使能。
                                                             0：不使能；
                                                             1：使能。 */
        unsigned char  buck4_en_ss_sel      : 1;  /* bit[6]: 选择软起完成信号。
                                                             0：模拟给出；
                                                             1：数字给出。 */
        unsigned char  reserved             : 1;  /* bit[7]: 保留。 */
    } reg;
} PMIC_BUCK4_CTRL11_UNION;
#endif
#define PMIC_BUCK4_CTRL11_buck4_pdn_lx_det_START      (0)
#define PMIC_BUCK4_CTRL11_buck4_pdn_lx_det_END        (0)
#define PMIC_BUCK4_CTRL11_buck4_eco_dmd_START         (1)
#define PMIC_BUCK4_CTRL11_buck4_eco_dmd_END           (1)
#define PMIC_BUCK4_CTRL11_buck4_dmd_shield_n_START    (2)
#define PMIC_BUCK4_CTRL11_buck4_dmd_shield_n_END      (2)
#define PMIC_BUCK4_CTRL11_buck4_ocp_delay_sel_START   (3)
#define PMIC_BUCK4_CTRL11_buck4_ocp_delay_sel_END     (3)
#define PMIC_BUCK4_CTRL11_buck4_dmd_clamp_START       (4)
#define PMIC_BUCK4_CTRL11_buck4_dmd_clamp_END         (4)
#define PMIC_BUCK4_CTRL11_buck4_en_regop_clamp_START  (5)
#define PMIC_BUCK4_CTRL11_buck4_en_regop_clamp_END    (5)
#define PMIC_BUCK4_CTRL11_buck4_en_ss_sel_START       (6)
#define PMIC_BUCK4_CTRL11_buck4_en_ss_sel_END         (6)


/*****************************************************************************
 结构名    : PMIC_LDO_1_CTRL_UNION
 结构说明  : LDO_1_CTRL 寄存器结构定义。地址偏移量:0x049，初值:0x11，宽度:8
 寄存器说明: LDO0_2/LDO1控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_vrset     : 3;  /* bit[0-2]: LDO1负载调整率补偿调整。
                                                         000：不补偿；
                                                         001：补偿5mV；
                                                         010：补偿10mV；
                                                         011：补偿15mV；
                                                         100：补偿20mV；
                                                         101：补偿25mV；
                                                         110：补偿30mV；
                                                         111：补偿35mV。 */
        unsigned char  ldo1_ocp_enn   : 1;  /* bit[3]  : LDO1限流模式选择信号。
                                                         0：表示告警限流；
                                                         1：表示告警不限流。 */
        unsigned char  ldo0_2_vrset   : 3;  /* bit[4-6]: LDO0负载调整率补偿调整。
                                                         000：不补偿；
                                                         001：补偿5mV；
                                                         010：补偿10mV；
                                                         011：补偿15mV；
                                                         100：补偿20mV；
                                                         101：补偿25mV；
                                                         110：补偿30mV；
                                                         111：补偿35mV。 */
        unsigned char  ldo0_2_ocp_enn : 1;  /* bit[7]  : LDO0限流模式选择信号。
                                                         0：表示告警限流；
                                                         1：表示告警不限流。 */
    } reg;
} PMIC_LDO_1_CTRL_UNION;
#endif
#define PMIC_LDO_1_CTRL_ldo1_vrset_START      (0)
#define PMIC_LDO_1_CTRL_ldo1_vrset_END        (2)
#define PMIC_LDO_1_CTRL_ldo1_ocp_enn_START    (3)
#define PMIC_LDO_1_CTRL_ldo1_ocp_enn_END      (3)
#define PMIC_LDO_1_CTRL_ldo0_2_vrset_START    (4)
#define PMIC_LDO_1_CTRL_ldo0_2_vrset_END      (6)
#define PMIC_LDO_1_CTRL_ldo0_2_ocp_enn_START  (7)
#define PMIC_LDO_1_CTRL_ldo0_2_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LD2_3_CTRL_UNION
 结构说明  : LD2_3_CTRL 寄存器结构定义。地址偏移量:0x04A，初值:0x11，宽度:8
 寄存器说明: LDO2/LDO3控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_vrset   : 3;  /* bit[0-2]: LDO3负载调整率补偿调整。
                                                       000：不补偿；
                                                       001：补偿5mV；
                                                       010：补偿10mV；
                                                       011：补偿15mV；
                                                       100：补偿20mV；
                                                       101：补偿25mV；
                                                       110：补偿30mV；
                                                       111：补偿35mV。 */
        unsigned char  ldo3_ocp_enn : 1;  /* bit[3]  : LDO3限流模式选择信号。
                                                       0：表示告警限流；
                                                       1：表示告警不限流。 */
        unsigned char  ldo2_vrset   : 3;  /* bit[4-6]: LDO2负载调整率补偿调整。
                                                       000：不补偿；
                                                       001：补偿5mV；
                                                       010：补偿10mV；
                                                       011：补偿15mV；
                                                       100：补偿20mV；
                                                       101：补偿25mV；
                                                       110：补偿30mV；
                                                       111：补偿35mV。 */
        unsigned char  ldo2_ocp_enn : 1;  /* bit[7]  : LDO2限流模式选择信号。
                                                       0：表示告警限流；
                                                       1：表示告警不限流。 */
    } reg;
} PMIC_LD2_3_CTRL_UNION;
#endif
#define PMIC_LD2_3_CTRL_ldo3_vrset_START    (0)
#define PMIC_LD2_3_CTRL_ldo3_vrset_END      (2)
#define PMIC_LD2_3_CTRL_ldo3_ocp_enn_START  (3)
#define PMIC_LD2_3_CTRL_ldo3_ocp_enn_END    (3)
#define PMIC_LD2_3_CTRL_ldo2_vrset_START    (4)
#define PMIC_LD2_3_CTRL_ldo2_vrset_END      (6)
#define PMIC_LD2_3_CTRL_ldo2_ocp_enn_START  (7)
#define PMIC_LD2_3_CTRL_ldo2_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO4_5_CTRL_UNION
 结构说明  : LDO4_5_CTRL 寄存器结构定义。地址偏移量:0x04B，初值:0x11，宽度:8
 寄存器说明: LDO4/LDO5控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo5_vrset   : 3;  /* bit[0-2]: LDO5负载调整率补偿调整。
                                                       000：不补偿；
                                                       001：补偿5mV；
                                                       010：补偿10mV；
                                                       011：补偿15mV；
                                                       100：补偿20mV；
                                                       101：补偿25mV；
                                                       110：补偿30mV；
                                                       111：补偿35mV。 */
        unsigned char  ldo5_ocp_enn : 1;  /* bit[3]  : LDO5限流模式选择信号。
                                                       0：表示告警限流；
                                                       1：表示告警不限流。 */
        unsigned char  ldo4_vrset   : 3;  /* bit[4-6]: LDO4负载调整率补偿调整。
                                                       000：不补偿；
                                                       001：补偿5mV；
                                                       010：补偿10mV；
                                                       011：补偿15mV；
                                                       100：补偿20mV；
                                                       101：补偿25mV；
                                                       110：补偿30mV；
                                                       111：补偿35mV。 */
        unsigned char  ldo4_ocp_enn : 1;  /* bit[7]  : LDO4限流模式选择信号。
                                                       0：表示告警限流；
                                                       1：表示告警不限流。 */
    } reg;
} PMIC_LDO4_5_CTRL_UNION;
#endif
#define PMIC_LDO4_5_CTRL_ldo5_vrset_START    (0)
#define PMIC_LDO4_5_CTRL_ldo5_vrset_END      (2)
#define PMIC_LDO4_5_CTRL_ldo5_ocp_enn_START  (3)
#define PMIC_LDO4_5_CTRL_ldo5_ocp_enn_END    (3)
#define PMIC_LDO4_5_CTRL_ldo4_vrset_START    (4)
#define PMIC_LDO4_5_CTRL_ldo4_vrset_END      (6)
#define PMIC_LDO4_5_CTRL_ldo4_ocp_enn_START  (7)
#define PMIC_LDO4_5_CTRL_ldo4_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO7_8_CTRL_UNION
 结构说明  : LDO7_8_CTRL 寄存器结构定义。地址偏移量:0x04C，初值:0x11，宽度:8
 寄存器说明: LDO7/LDO8控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo8_vrset   : 3;  /* bit[0-2]: LDO8负载调整率补偿调整。
                                                       000：不补偿；
                                                       001：补偿5mV；
                                                       010：补偿10mV；
                                                       011：补偿15mV；
                                                       100：补偿20mV；
                                                       101：补偿25mV；
                                                       110：补偿30mV；
                                                       111：补偿35mV。 */
        unsigned char  ldo8_ocp_enn : 1;  /* bit[3]  : LDO8限流模式选择信号。
                                                       0：表示告警限流；
                                                       1：表示告警不限流。 */
        unsigned char  ldo7_vrset   : 3;  /* bit[4-6]: LDO7负载调整率补偿调整。
                                                       000：不补偿；
                                                       001：补偿5mV；
                                                       010：补偿10mV；
                                                       011：补偿15mV；
                                                       100：补偿20mV；
                                                       101：补偿25mV；
                                                       110：补偿30mV；
                                                       111：补偿35mV。 */
        unsigned char  ldo7_ocp_enn : 1;  /* bit[7]  : LDO7限流模式选择信号。
                                                       0：表示告警限流；
                                                       1：表示告警不限流。 */
    } reg;
} PMIC_LDO7_8_CTRL_UNION;
#endif
#define PMIC_LDO7_8_CTRL_ldo8_vrset_START    (0)
#define PMIC_LDO7_8_CTRL_ldo8_vrset_END      (2)
#define PMIC_LDO7_8_CTRL_ldo8_ocp_enn_START  (3)
#define PMIC_LDO7_8_CTRL_ldo8_ocp_enn_END    (3)
#define PMIC_LDO7_8_CTRL_ldo7_vrset_START    (4)
#define PMIC_LDO7_8_CTRL_ldo7_vrset_END      (6)
#define PMIC_LDO7_8_CTRL_ldo7_ocp_enn_START  (7)
#define PMIC_LDO7_8_CTRL_ldo7_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO9_10_CTRL_UNION
 结构说明  : LDO9_10_CTRL 寄存器结构定义。地址偏移量:0x04D，初值:0x11，宽度:8
 寄存器说明: LDO9/LDO10控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo10_vrset   : 3;  /* bit[0-2]: LDO10负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo10_ocp_enn : 1;  /* bit[3]  : LDO10限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo9_vrset    : 3;  /* bit[4-6]: LDO9负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo9_ocp_enn  : 1;  /* bit[7]  : LDO9限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO9_10_CTRL_UNION;
#endif
#define PMIC_LDO9_10_CTRL_ldo10_vrset_START    (0)
#define PMIC_LDO9_10_CTRL_ldo10_vrset_END      (2)
#define PMIC_LDO9_10_CTRL_ldo10_ocp_enn_START  (3)
#define PMIC_LDO9_10_CTRL_ldo10_ocp_enn_END    (3)
#define PMIC_LDO9_10_CTRL_ldo9_vrset_START     (4)
#define PMIC_LDO9_10_CTRL_ldo9_vrset_END       (6)
#define PMIC_LDO9_10_CTRL_ldo9_ocp_enn_START   (7)
#define PMIC_LDO9_10_CTRL_ldo9_ocp_enn_END     (7)


/*****************************************************************************
 结构名    : PMIC_LD11_12_CTRL_UNION
 结构说明  : LD11_12_CTRL 寄存器结构定义。地址偏移量:0x04E，初值:0x11，宽度:8
 寄存器说明: LDO11/LDO12控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo12_vrset   : 3;  /* bit[0-2]: LDO12负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo12_ocp_enn : 1;  /* bit[3]  : LDO12限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo11_vrset   : 3;  /* bit[4-6]: LDO11负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo11_ocp_enn : 1;  /* bit[7]  : LDO11限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LD11_12_CTRL_UNION;
#endif
#define PMIC_LD11_12_CTRL_ldo12_vrset_START    (0)
#define PMIC_LD11_12_CTRL_ldo12_vrset_END      (2)
#define PMIC_LD11_12_CTRL_ldo12_ocp_enn_START  (3)
#define PMIC_LD11_12_CTRL_ldo12_ocp_enn_END    (3)
#define PMIC_LD11_12_CTRL_ldo11_vrset_START    (4)
#define PMIC_LD11_12_CTRL_ldo11_vrset_END      (6)
#define PMIC_LD11_12_CTRL_ldo11_ocp_enn_START  (7)
#define PMIC_LD11_12_CTRL_ldo11_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO13_14_CTRL_UNION
 结构说明  : LDO13_14_CTRL 寄存器结构定义。地址偏移量:0x04F，初值:0x11，宽度:8
 寄存器说明: LDO13/LDO14控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo14_vrset   : 3;  /* bit[0-2]: LDO14负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo14_ocp_enn : 1;  /* bit[3]  : LDO14限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo13_vrset   : 3;  /* bit[4-6]: LDO13负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo13_ocp_enn : 1;  /* bit[7]  : LDO13限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO13_14_CTRL_UNION;
#endif
#define PMIC_LDO13_14_CTRL_ldo14_vrset_START    (0)
#define PMIC_LDO13_14_CTRL_ldo14_vrset_END      (2)
#define PMIC_LDO13_14_CTRL_ldo14_ocp_enn_START  (3)
#define PMIC_LDO13_14_CTRL_ldo14_ocp_enn_END    (3)
#define PMIC_LDO13_14_CTRL_ldo13_vrset_START    (4)
#define PMIC_LDO13_14_CTRL_ldo13_vrset_END      (6)
#define PMIC_LDO13_14_CTRL_ldo13_ocp_enn_START  (7)
#define PMIC_LDO13_14_CTRL_ldo13_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO15_16_CTRL_UNION
 结构说明  : LDO15_16_CTRL 寄存器结构定义。地址偏移量:0x050，初值:0x11，宽度:8
 寄存器说明: LDO15/LDO16控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo16_vrset   : 3;  /* bit[0-2]: LDO16负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo16_ocp_enn : 1;  /* bit[3]  : LDO16限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo15_vrset   : 3;  /* bit[4-6]: LDO15负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo15_ocp_enn : 1;  /* bit[7]  : LDO15限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO15_16_CTRL_UNION;
#endif
#define PMIC_LDO15_16_CTRL_ldo16_vrset_START    (0)
#define PMIC_LDO15_16_CTRL_ldo16_vrset_END      (2)
#define PMIC_LDO15_16_CTRL_ldo16_ocp_enn_START  (3)
#define PMIC_LDO15_16_CTRL_ldo16_ocp_enn_END    (3)
#define PMIC_LDO15_16_CTRL_ldo15_vrset_START    (4)
#define PMIC_LDO15_16_CTRL_ldo15_vrset_END      (6)
#define PMIC_LDO15_16_CTRL_ldo15_ocp_enn_START  (7)
#define PMIC_LDO15_16_CTRL_ldo15_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO17_19_CTRL_UNION
 结构说明  : LDO17_19_CTRL 寄存器结构定义。地址偏移量:0x051，初值:0x11，宽度:8
 寄存器说明: LDO17/LDO19控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo19_vrset   : 3;  /* bit[0-2]: LDO19负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo19_ocp_enn : 1;  /* bit[3]  : LDO19限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo17_vrset   : 3;  /* bit[4-6]: LDO17负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo17_ocp_enn : 1;  /* bit[7]  : LDO17限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO17_19_CTRL_UNION;
#endif
#define PMIC_LDO17_19_CTRL_ldo19_vrset_START    (0)
#define PMIC_LDO17_19_CTRL_ldo19_vrset_END      (2)
#define PMIC_LDO17_19_CTRL_ldo19_ocp_enn_START  (3)
#define PMIC_LDO17_19_CTRL_ldo19_ocp_enn_END    (3)
#define PMIC_LDO17_19_CTRL_ldo17_vrset_START    (4)
#define PMIC_LDO17_19_CTRL_ldo17_vrset_END      (6)
#define PMIC_LDO17_19_CTRL_ldo17_ocp_enn_START  (7)
#define PMIC_LDO17_19_CTRL_ldo17_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO20_21_CTRL_UNION
 结构说明  : LDO20_21_CTRL 寄存器结构定义。地址偏移量:0x052，初值:0x11，宽度:8
 寄存器说明: LDO20/LDO21控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo21_vrset   : 3;  /* bit[0-2]: LDO21负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo21_ocp_enn : 1;  /* bit[3]  : LDO21限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo20_vrset   : 3;  /* bit[4-6]: LDO20负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo20_ocp_enn : 1;  /* bit[7]  : LDO20限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO20_21_CTRL_UNION;
#endif
#define PMIC_LDO20_21_CTRL_ldo21_vrset_START    (0)
#define PMIC_LDO20_21_CTRL_ldo21_vrset_END      (2)
#define PMIC_LDO20_21_CTRL_ldo21_ocp_enn_START  (3)
#define PMIC_LDO20_21_CTRL_ldo21_ocp_enn_END    (3)
#define PMIC_LDO20_21_CTRL_ldo20_vrset_START    (4)
#define PMIC_LDO20_21_CTRL_ldo20_vrset_END      (6)
#define PMIC_LDO20_21_CTRL_ldo20_ocp_enn_START  (7)
#define PMIC_LDO20_21_CTRL_ldo20_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO22_23_CTRL_UNION
 结构说明  : LDO22_23_CTRL 寄存器结构定义。地址偏移量:0x053，初值:0x11，宽度:8
 寄存器说明: LDO22/LDO23控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo23_vrset   : 3;  /* bit[0-2]: LDO23负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo23_ocp_enn : 1;  /* bit[3]  : LDO23限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo22_vrset   : 3;  /* bit[4-6]: LDO22负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo22_ocp_enn : 1;  /* bit[7]  : LDO22限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO22_23_CTRL_UNION;
#endif
#define PMIC_LDO22_23_CTRL_ldo23_vrset_START    (0)
#define PMIC_LDO22_23_CTRL_ldo23_vrset_END      (2)
#define PMIC_LDO22_23_CTRL_ldo23_ocp_enn_START  (3)
#define PMIC_LDO22_23_CTRL_ldo23_ocp_enn_END    (3)
#define PMIC_LDO22_23_CTRL_ldo22_vrset_START    (4)
#define PMIC_LDO22_23_CTRL_ldo22_vrset_END      (6)
#define PMIC_LDO22_23_CTRL_ldo22_ocp_enn_START  (7)
#define PMIC_LDO22_23_CTRL_ldo22_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO24_25_CTRL_UNION
 结构说明  : LDO24_25_CTRL 寄存器结构定义。地址偏移量:0x054，初值:0x11，宽度:8
 寄存器说明: LDO24/LDO25控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo25_vrset   : 3;  /* bit[0-2]: LDO25负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo25_ocp_enn : 1;  /* bit[3]  : LDO25限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo24_vrset   : 3;  /* bit[4-6]: LDO24负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo24_ocp_enn : 1;  /* bit[7]  : LDO24限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO24_25_CTRL_UNION;
#endif
#define PMIC_LDO24_25_CTRL_ldo25_vrset_START    (0)
#define PMIC_LDO24_25_CTRL_ldo25_vrset_END      (2)
#define PMIC_LDO24_25_CTRL_ldo25_ocp_enn_START  (3)
#define PMIC_LDO24_25_CTRL_ldo25_ocp_enn_END    (3)
#define PMIC_LDO24_25_CTRL_ldo24_vrset_START    (4)
#define PMIC_LDO24_25_CTRL_ldo24_vrset_END      (6)
#define PMIC_LDO24_25_CTRL_ldo24_ocp_enn_START  (7)
#define PMIC_LDO24_25_CTRL_ldo24_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO26_27_CTRL_UNION
 结构说明  : LDO26_27_CTRL 寄存器结构定义。地址偏移量:0x055，初值:0x11，宽度:8
 寄存器说明: LDO26/LDO27控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo27_vrset   : 3;  /* bit[0-2]: LDO27负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo27_ocp_enn : 1;  /* bit[3]  : LDO27限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo26_vrset   : 3;  /* bit[4-6]: LDO26负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo26_ocp_enn : 1;  /* bit[7]  : LDO26限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO26_27_CTRL_UNION;
#endif
#define PMIC_LDO26_27_CTRL_ldo27_vrset_START    (0)
#define PMIC_LDO26_27_CTRL_ldo27_vrset_END      (2)
#define PMIC_LDO26_27_CTRL_ldo27_ocp_enn_START  (3)
#define PMIC_LDO26_27_CTRL_ldo27_ocp_enn_END    (3)
#define PMIC_LDO26_27_CTRL_ldo26_vrset_START    (4)
#define PMIC_LDO26_27_CTRL_ldo26_vrset_END      (6)
#define PMIC_LDO26_27_CTRL_ldo26_ocp_enn_START  (7)
#define PMIC_LDO26_27_CTRL_ldo26_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO28_29_CTRL_UNION
 结构说明  : LDO28_29_CTRL 寄存器结构定义。地址偏移量:0x056，初值:0x11，宽度:8
 寄存器说明: LDO28/LDO29控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo29_vrset   : 3;  /* bit[0-2]: LDO29负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo29_ocp_enn : 1;  /* bit[3]  : LDO29限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo28_vrset   : 3;  /* bit[4-6]: LDO28负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo28_ocp_enn : 1;  /* bit[7]  : LDO28限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO28_29_CTRL_UNION;
#endif
#define PMIC_LDO28_29_CTRL_ldo29_vrset_START    (0)
#define PMIC_LDO28_29_CTRL_ldo29_vrset_END      (2)
#define PMIC_LDO28_29_CTRL_ldo29_ocp_enn_START  (3)
#define PMIC_LDO28_29_CTRL_ldo29_ocp_enn_END    (3)
#define PMIC_LDO28_29_CTRL_ldo28_vrset_START    (4)
#define PMIC_LDO28_29_CTRL_ldo28_vrset_END      (6)
#define PMIC_LDO28_29_CTRL_ldo28_ocp_enn_START  (7)
#define PMIC_LDO28_29_CTRL_ldo28_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO30_31_CTRL_UNION
 结构说明  : LDO30_31_CTRL 寄存器结构定义。地址偏移量:0x057，初值:0x11，宽度:8
 寄存器说明: LDO30/LDO31控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo31_vrset   : 3;  /* bit[0-2]: LDO31负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo31_ocp_enn : 1;  /* bit[3]  : LDO31限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo30_vrset   : 3;  /* bit[4-6]: LDO30负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo30_ocp_enn : 1;  /* bit[7]  : LDO30限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO30_31_CTRL_UNION;
#endif
#define PMIC_LDO30_31_CTRL_ldo31_vrset_START    (0)
#define PMIC_LDO30_31_CTRL_ldo31_vrset_END      (2)
#define PMIC_LDO30_31_CTRL_ldo31_ocp_enn_START  (3)
#define PMIC_LDO30_31_CTRL_ldo31_ocp_enn_END    (3)
#define PMIC_LDO30_31_CTRL_ldo30_vrset_START    (4)
#define PMIC_LDO30_31_CTRL_ldo30_vrset_END      (6)
#define PMIC_LDO30_31_CTRL_ldo30_ocp_enn_START  (7)
#define PMIC_LDO30_31_CTRL_ldo30_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO32_CTRL_UNION
 结构说明  : LDO32_CTRL 寄存器结构定义。地址偏移量:0x058，初值:0x01，宽度:8
 寄存器说明: LDO32控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo32_vrset   : 3;  /* bit[0-2]: LDO32负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo32_ocp_enn : 1;  /* bit[3]  : LDO32限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  reserved      : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO32_CTRL_UNION;
#endif
#define PMIC_LDO32_CTRL_ldo32_vrset_START    (0)
#define PMIC_LDO32_CTRL_ldo32_vrset_END      (2)
#define PMIC_LDO32_CTRL_ldo32_ocp_enn_START  (3)
#define PMIC_LDO32_CTRL_ldo32_ocp_enn_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO0_1_ONOFF_UNION
 结构说明  : LDO0_1_ONOFF 寄存器结构定义。地址偏移量:0x059，初值:0x00，宽度:8
 寄存器说明: LDO0_1开关使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0    : 4;  /* bit[0-3]: 保留。 */
        unsigned char  reg_ldo0_1_en : 1;  /* bit[4]  : LDO0_1使能信号。
                                                        0：关闭；
                                                        1：使能。 */
        unsigned char  reserved_1    : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO0_1_ONOFF_UNION;
#endif
#define PMIC_LDO0_1_ONOFF_reg_ldo0_1_en_START  (4)
#define PMIC_LDO0_1_ONOFF_reg_ldo0_1_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO0_2_ONOFF_ECO_UNION
 结构说明  : LDO0_2_ONOFF_ECO 寄存器结构定义。地址偏移量:0x05A，初值:0x02，宽度:8
 寄存器说明: LDO0_2开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo0_2_eco_en : 1;  /* bit[0]  : LDO0_2进入低功耗ECO模式控制信号。
                                                            0：normal模式；
                                                            1：ECO模式。 */
        unsigned char  reg_ldo0_2_en     : 1;  /* bit[1]  : LDO0_2使能信号。
                                                            0：关闭；
                                                            1：使能。 */
        unsigned char  reserved          : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO0_2_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_eco_en_START  (0)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_eco_en_END    (0)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_en_START      (1)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO0_2_VSET_UNION
 结构说明  : LDO0_2_VSET 寄存器结构定义。地址偏移量:0x05B，初值:0x55，宽度:8
 寄存器说明: LDO0_2调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo0_2_vset     : 3;  /* bit[0-2]: LDO0_2输出电压设置。
                                                          000：0.600V；
                                                          001：0.650V；
                                                          010：0.700V；
                                                          011：0.750V；
                                                          100：0.775V；
                                                          101：0.800V；
                                                          110：0.825V；
                                                          111：0.850V。 */
        unsigned char  reserved_0      : 1;  /* bit[3]  : 保留 */
        unsigned char  ldo0_2_vset_adj : 3;  /* bit[4-6]: LDO0_2输出电压值在PERI_EN有效时可配置成不同档位的值。
                                                          000：0.600V；
                                                          001：0.650V；
                                                          010：0.700V；
                                                          011：0.750V；
                                                          100：0.775V；
                                                          101：0.800V；
                                                          110：0.825V；
                                                          111：0.850V。 */
        unsigned char  reserved_1      : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_LDO0_2_VSET_UNION;
#endif
#define PMIC_LDO0_2_VSET_ldo0_2_vset_START      (0)
#define PMIC_LDO0_2_VSET_ldo0_2_vset_END        (2)
#define PMIC_LDO0_2_VSET_ldo0_2_vset_adj_START  (4)
#define PMIC_LDO0_2_VSET_ldo0_2_vset_adj_END    (6)


/*****************************************************************************
 结构名    : PMIC_LDO1_ONOFF_ECO_UNION
 结构说明  : LDO1_ONOFF_ECO 寄存器结构定义。地址偏移量:0x05C，初值:0x00，宽度:8
 寄存器说明: LDO1开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo1_eco_en : 1;  /* bit[0]  : LDO1进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reg_ldo1_en     : 1;  /* bit[1]  : LDO1使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO1_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_eco_en_START  (0)
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_eco_en_END    (0)
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_en_START      (1)
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO1_VSET_UNION
 结构说明  : LDO1_VSET 寄存器结构定义。地址偏移量:0x05D，初值:0x00，宽度:8
 寄存器说明: LDO1调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_vset : 4;  /* bit[0-3]: LDO1输出电压设置，默认电压1.0V。
                                                    0000：1.00V；
                                                    0001：1.05V；
                                                    0010：1.10V；
                                                    0011：1.15V；
                                                    0100：1.20V；
                                                    0101：1.25V；
                                                    0110：1.26V；
                                                    0111：1.27V；
                                                    1000：1.28V；
                                                    1001：1.29V；
                                                    1010：1.30V；
                                                    1011：1.31V；
                                                    1100：1.32V；
                                                    1101：1.33V；
                                                    1110：1.34V；
                                                    1111：1.50V。 */
        unsigned char  reserved  : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO1_VSET_UNION;
#endif
#define PMIC_LDO1_VSET_ldo1_vset_START  (0)
#define PMIC_LDO1_VSET_ldo1_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO2_ONOFF_ECO_UNION
 结构说明  : LDO2_ONOFF_ECO 寄存器结构定义。地址偏移量:0x05E，初值:0x02，宽度:8
 寄存器说明: LDO2开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo2_eco_en : 1;  /* bit[0]  : LDO2进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reg_ldo2_en     : 1;  /* bit[1]  : LDO2使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO2_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_eco_en_START  (0)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_eco_en_END    (0)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_en_START      (1)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO2_VSET_UNION
 结构说明  : LDO2_VSET 寄存器结构定义。地址偏移量:0x05F，初值:0x33，宽度:8
 寄存器说明: LDO2调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_vset     : 3;  /* bit[0-2]: LDO2输出电压设置。
                                                        000：1.700V；
                                                        001：1.750V；
                                                        010：1.775V；
                                                        011：1.800V；
                                                        100：1.825V；
                                                        101：1.850V；
                                                        110：1.875V；
                                                        111：1.900V。 */
        unsigned char  reserved_0    : 1;  /* bit[3]  : 保留。 */
        unsigned char  ldo2_vset_adj : 3;  /* bit[4-6]: LDO2输出电压值在PERI_EN有效时可配置成不同档位的值。
                                                        000：1.700V；
                                                        001：1.750V；
                                                        010：1.775V；
                                                        011：1.800V；
                                                        100：1.825V；
                                                        101：1.850V；
                                                        110：1.875V；
                                                        111：1.900V。 */
        unsigned char  reserved_1    : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_LDO2_VSET_UNION;
#endif
#define PMIC_LDO2_VSET_ldo2_vset_START      (0)
#define PMIC_LDO2_VSET_ldo2_vset_END        (2)
#define PMIC_LDO2_VSET_ldo2_vset_adj_START  (4)
#define PMIC_LDO2_VSET_ldo2_vset_adj_END    (6)


/*****************************************************************************
 结构名    : PMIC_LDO3_ONOFF_ECO_UNION
 结构说明  : LDO3_ONOFF_ECO 寄存器结构定义。地址偏移量:0x060，初值:0x00，宽度:8
 寄存器说明: LDO3开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo3_eco_en : 1;  /* bit[0]  : LDO3进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reg_ldo3_en     : 1;  /* bit[1]  : LDO3使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO3_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_eco_en_START  (0)
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_eco_en_END    (0)
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_en_START      (1)
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO3_VSET_UNION
 结构说明  : LDO3_VSET 寄存器结构定义。地址偏移量:0x061，初值:0x00，宽度:8
 寄存器说明: LDO3调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_vset : 4;  /* bit[0-3]: LDO3输出电压设置。
                                                    0000：1.800V；
                                                    0001：1.825V；
                                                    0010：1.850V；
                                                    0011：1.875V；
                                                    0100：1.900V；
                                                    0101：1.925V；
                                                    0110：1.950V；
                                                    0111：1.975V。
                                                    1000：2.000V；
                                                    1001：2.025V；
                                                    1010：2.050V；
                                                    1011：2.075V；
                                                    1100：2.100V；
                                                    1101：2.125V；
                                                    1110：2.150V；
                                                    1111：2.200V。 */
        unsigned char  reserved  : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO3_VSET_UNION;
#endif
#define PMIC_LDO3_VSET_ldo3_vset_START  (0)
#define PMIC_LDO3_VSET_ldo3_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO4_ONOFF_ECO_UNION
 结构说明  : LDO4_ONOFF_ECO 寄存器结构定义。地址偏移量:0x062，初值:0x00，宽度:8
 寄存器说明: LDO4开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo4_eco_en : 1;  /* bit[0]  : LDO4进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reg_ldo4_en     : 1;  /* bit[1]  : LDO4使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO4_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_eco_en_START  (0)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_eco_en_END    (0)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_en_START      (1)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO4_VSET_UNION
 结构说明  : LDO4_VSET 寄存器结构定义。地址偏移量:0x063，初值:0x00，宽度:8
 寄存器说明: LDO4调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo4_vset : 3;  /* bit[0-2]: LDO4输出电压设置。
                                                    000：1.700V；
                                                    001：1.750V；
                                                    010：1.775V；
                                                    011：1.800V；
                                                    100：1.825V；
                                                    101：1.850V；
                                                    110：1.875V；
                                                    111：1.900V。 */
        unsigned char  reserved  : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO4_VSET_UNION;
#endif
#define PMIC_LDO4_VSET_ldo4_vset_START  (0)
#define PMIC_LDO4_VSET_ldo4_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO5_ONOFF_ECO_UNION
 结构说明  : LDO5_ONOFF_ECO 寄存器结构定义。地址偏移量:0x064，初值:0x02，宽度:8
 寄存器说明: LDO5开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo5_eco_en : 1;  /* bit[0]  : LDO5进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reg_ldo5_en     : 1;  /* bit[1]  : LDO5使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO5_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_eco_en_START  (0)
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_eco_en_END    (0)
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_en_START      (1)
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO5_VSET_UNION
 结构说明  : LDO5_VSET 寄存器结构定义。地址偏移量:0x065，初值:0x03，宽度:8
 寄存器说明: LDO5调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo5_vset : 3;  /* bit[0-2]: LDO5输出电压设置。
                                                    000：1.7V；
                                                    001：1.75V；
                                                    010：1.775V；
                                                    011：1.8V；
                                                    100：1.825V；
                                                    101：1.85V；
                                                    110：1.9V；
                                                    111：1.95V。 */
        unsigned char  reserved  : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO5_VSET_UNION;
#endif
#define PMIC_LDO5_VSET_ldo5_vset_START  (0)
#define PMIC_LDO5_VSET_ldo5_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO7_ONOFF_ECO_UNION
 结构说明  : LDO7_ONOFF_ECO 寄存器结构定义。地址偏移量:0x066，初值:0x02，宽度:8
 寄存器说明: LDO7开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo7_eco_en : 1;  /* bit[0]  : LDO7进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reg_ldo7_en     : 1;  /* bit[1]  : LDO7使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO7_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_eco_en_START  (0)
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_eco_en_END    (0)
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_en_START      (1)
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO7_VSET_UNION
 结构说明  : LDO7_VSET 寄存器结构定义。地址偏移量:0x067，初值:0x03，宽度:8
 寄存器说明: LDO7调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo7_vset : 3;  /* bit[0-2]: LDO7输出电压设置。
                                                    000：1.7V；
                                                    001：1.75V；
                                                    010：1.775V；
                                                    011：1.8V；
                                                    100：1.825V；
                                                    101：1.85V；
                                                    110：1.9V；
                                                    111：1.95V。 */
        unsigned char  reserved  : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO7_VSET_UNION;
#endif
#define PMIC_LDO7_VSET_ldo7_vset_START  (0)
#define PMIC_LDO7_VSET_ldo7_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO8_ONOFF_ECO_UNION
 结构说明  : LDO8_ONOFF_ECO 寄存器结构定义。地址偏移量:0x068，初值:0x02，宽度:8
 寄存器说明: LDO8开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo8_eco_en : 1;  /* bit[0]  : LDO8进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reg_ldo8_en     : 1;  /* bit[1]  : LDO8使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO8_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_eco_en_START  (0)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_eco_en_END    (0)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_en_START      (1)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO8_VSET_UNION
 结构说明  : LDO8_VSET 寄存器结构定义。地址偏移量:0x069，初值:0x03，宽度:8
 寄存器说明: LDO8调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo8_vset : 4;  /* bit[0-3]: LDO8输出电压设置，ldo8_vset[3]不使用。
                                                    000：1.7V；
                                                    001：1.75V；
                                                    010：1.775V；
                                                    011：1.8V；
                                                    100：1.825V；
                                                    101：1.850V；
                                                    110：1.900V；
                                                    111：1.950V。 */
        unsigned char  reserved  : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO8_VSET_UNION;
#endif
#define PMIC_LDO8_VSET_ldo8_vset_START  (0)
#define PMIC_LDO8_VSET_ldo8_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO9_ONOFF_ECO_UNION
 结构说明  : LDO9_ONOFF_ECO 寄存器结构定义。地址偏移量:0x06A，初值:0x00，宽度:8
 寄存器说明: LDO9开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo9_eco_en : 1;  /* bit[0]  : LDO9进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reg_ldo9_en     : 1;  /* bit[1]  : LDO9使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO9_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_eco_en_START  (0)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_eco_en_END    (0)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_en_START      (1)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO9_VSET_UNION
 结构说明  : LDO9_VSET 寄存器结构定义。地址偏移量:0x06B，初值:0x00，宽度:8
 寄存器说明: LDO9调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo9_vset : 3;  /* bit[0-2]: LDO9输出电压设置。
                                                    000：1.75V；
                                                    001：1.8V；
                                                    010：1.825V；
                                                    011：2.8V；
                                                    100：2.85V；
                                                    101：2.95V；
                                                    110：3.0V；
                                                    111：3.3V。 */
        unsigned char  reserved  : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO9_VSET_UNION;
#endif
#define PMIC_LDO9_VSET_ldo9_vset_START  (0)
#define PMIC_LDO9_VSET_ldo9_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO10_ONOFF_ECO_UNION
 结构说明  : LDO10_ONOFF_ECO 寄存器结构定义。地址偏移量:0x06C，初值:0x02，宽度:8
 寄存器说明: LDO10开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo10_eco_en : 1;  /* bit[0]  : LDO10进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo10_en     : 1;  /* bit[1]  : LDO10使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO10_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_eco_en_START  (0)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_eco_en_END    (0)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_en_START      (1)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO10_VSET_UNION
 结构说明  : LDO10_VSET 寄存器结构定义。地址偏移量:0x06D，初值:0x02，宽度:8
 寄存器说明: LDO10调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo10_vset : 3;  /* bit[0-2]: LDO10输出电压设置。
                                                     000：3.1V；
                                                     001：3.15V；
                                                     010：3.2V；
                                                     011：3.3V；
                                                     其他：3.3V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO10_VSET_UNION;
#endif
#define PMIC_LDO10_VSET_ldo10_vset_START  (0)
#define PMIC_LDO10_VSET_ldo10_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO11_ONOFF_ECO_UNION
 结构说明  : LDO11_ONOFF_ECO 寄存器结构定义。地址偏移量:0x06E，初值:0x00，宽度:8
 寄存器说明: LDO11开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo11_eco_en : 1;  /* bit[0]  : LDO11进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo11_en     : 1;  /* bit[1]  : LDO11使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO11_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_eco_en_START  (0)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_eco_en_END    (0)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_en_START      (1)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO11_VSET_UNION
 结构说明  : LDO11_VSET 寄存器结构定义。地址偏移量:0x06F，初值:0x00，宽度:8
 寄存器说明: LDO11调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo11_vset : 3;  /* bit[0-2]: LDO11输出电压设置。
                                                     000：1.75V；
                                                     001：1.8V；
                                                     010：1.825V；
                                                     011：2.8V；
                                                     100：2.85V；
                                                     101：2.95V；
                                                     110：3.0V；
                                                     111：3.3V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO11_VSET_UNION;
#endif
#define PMIC_LDO11_VSET_ldo11_vset_START  (0)
#define PMIC_LDO11_VSET_ldo11_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO12_ONOFF_ECO_UNION
 结构说明  : LDO12_ONOFF_ECO 寄存器结构定义。地址偏移量:0x070，初值:0x00，宽度:8
 寄存器说明: LDO12开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo12_eco_en : 1;  /* bit[0]  : LDO12进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo12_en     : 1;  /* bit[1]  : LDO12使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO12_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_eco_en_START  (0)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_eco_en_END    (0)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_en_START      (1)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO12_VSET_UNION
 结构说明  : LDO12_VSET 寄存器结构定义。地址偏移量:0x071，初值:0x00，宽度:8
 寄存器说明: LDO12调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo12_vset : 3;  /* bit[0-2]: LDO12输出电压设置。
                                                     000：1.75V；
                                                     001：1.8V；
                                                     010：1.825V；
                                                     011：2.8V；
                                                     100：2.85V；
                                                     101：2.95V；
                                                     110：3.0V；
                                                     111：3.3V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO12_VSET_UNION;
#endif
#define PMIC_LDO12_VSET_ldo12_vset_START  (0)
#define PMIC_LDO12_VSET_ldo12_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO13_ONOFF_ECO_UNION
 结构说明  : LDO13_ONOFF_ECO 寄存器结构定义。地址偏移量:0x072，初值:0x00，宽度:8
 寄存器说明: LDO13开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo13_eco_en : 1;  /* bit[0]  : LDO13进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo13_en     : 1;  /* bit[1]  : LDO13使能信号(默认不开启，可通过OTP配置默认开启（默认值为1）)。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO13_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_eco_en_START  (0)
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_eco_en_END    (0)
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_en_START      (1)
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO13_VSET_UNION
 结构说明  : LDO13_VSET 寄存器结构定义。地址偏移量:0x073，初值:0x04，宽度:8
 寄存器说明: LDO13调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo13_vset : 3;  /* bit[0-2]: LDO13输出电压设置。
                                                     000：1.75V；
                                                     001：1.8V；
                                                     010：1.825V；
                                                     011：2.8V；
                                                     100：2.85V；
                                                     101：2.95V；
                                                     110：3.0V；
                                                     111：3.3V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO13_VSET_UNION;
#endif
#define PMIC_LDO13_VSET_ldo13_vset_START  (0)
#define PMIC_LDO13_VSET_ldo13_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO14_ONOFF_ECO_UNION
 结构说明  : LDO14_ONOFF_ECO 寄存器结构定义。地址偏移量:0x074，初值:0x00，宽度:8
 寄存器说明: LDO14开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo14_eco_en : 1;  /* bit[0]  : LDO14进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo14_en     : 1;  /* bit[1]  : LDO14使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO14_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_eco_en_START  (0)
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_eco_en_END    (0)
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_en_START      (1)
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO14_VSET_UNION
 结构说明  : LDO14_VSET 寄存器结构定义。地址偏移量:0x075，初值:0x00，宽度:8
 寄存器说明: LDO14调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo14_vset : 3;  /* bit[0-2]: LDO14输出电压设置。
                                                     000：1.75V；
                                                     001：1.8V；
                                                     010：1.825V；
                                                     011：2.8V；
                                                     100：2.85V；
                                                     101：2.95V；
                                                     110：3.0V；
                                                     111：3.3V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO14_VSET_UNION;
#endif
#define PMIC_LDO14_VSET_ldo14_vset_START  (0)
#define PMIC_LDO14_VSET_ldo14_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO15_ONOFF_ECO_UNION
 结构说明  : LDO15_ONOFF_ECO 寄存器结构定义。地址偏移量:0x076，初值:0x02，宽度:8
 寄存器说明: LDO15开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo15_eco_en : 1;  /* bit[0]  : LDO15进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo15_en     : 1;  /* bit[1]  : LDO15使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO15_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_eco_en_START  (0)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_eco_en_END    (0)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_en_START      (1)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO15_VSET_UNION
 结构说明  : LDO15_VSET 寄存器结构定义。地址偏移量:0x077，初值:0x07，宽度:8
 寄存器说明: LDO15调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo15_vset : 3;  /* bit[0-2]: LDO15输出电压设置。
                                                     000：1.75V；
                                                     001：1.8V；
                                                     010：2.4V；
                                                     011：2.6V；
                                                     100：2.7V；
                                                     101：2.85V；
                                                     110：2.95V；
                                                     111：3.0V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO15_VSET_UNION;
#endif
#define PMIC_LDO15_VSET_ldo15_vset_START  (0)
#define PMIC_LDO15_VSET_ldo15_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO16_ONOFF_ECO_UNION
 结构说明  : LDO16_ONOFF_ECO 寄存器结构定义。地址偏移量:0x078，初值:0x00，宽度:8
 寄存器说明: LDO16开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo16_eco_en : 1;  /* bit[0]  : LDO16进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo16_en     : 1;  /* bit[1]  : LDO16使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO16_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_eco_en_START  (0)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_eco_en_END    (0)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_en_START      (1)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO16_VSET_UNION
 结构说明  : LDO16_VSET 寄存器结构定义。地址偏移量:0x079，初值:0x00，宽度:8
 寄存器说明: LDO16调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo16_vset : 3;  /* bit[0-2]: LDO16输出电压设置。
                                                     000：1.75V；
                                                     001：1.8V；
                                                     010：2.4V；
                                                     011：2.6V；
                                                     100：2.7V；
                                                     101：2.85V；
                                                     110：2.95V；
                                                     111：3.0V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO16_VSET_UNION;
#endif
#define PMIC_LDO16_VSET_ldo16_vset_START  (0)
#define PMIC_LDO16_VSET_ldo16_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO17_ONOFF_ECO_UNION
 结构说明  : LDO17_ONOFF_ECO 寄存器结构定义。地址偏移量:0x07A，初值:0x00，宽度:8
 寄存器说明: LDO17开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo17_eco_en : 1;  /* bit[0]  : LDO17进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo17_en     : 1;  /* bit[1]  : LDO17使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO17_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_eco_en_START  (0)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_eco_en_END    (0)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_en_START      (1)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO17_VSET_UNION
 结构说明  : LDO17_VSET 寄存器结构定义。地址偏移量:0x07B，初值:0x00，宽度:8
 寄存器说明: LDO17调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo17_vset : 3;  /* bit[0-2]: LDO17输出电压设置。
                                                     000：2.6V；
                                                     001：2.7V；
                                                     010：2.8V；
                                                     011：2.85V；
                                                     100：3.0V；
                                                     101：3.1V；
                                                     110：3.2V；
                                                     111：3.3V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO17_VSET_UNION;
#endif
#define PMIC_LDO17_VSET_ldo17_vset_START  (0)
#define PMIC_LDO17_VSET_ldo17_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO19_ONOFF_ECO_UNION
 结构说明  : LDO19_ONOFF_ECO 寄存器结构定义。地址偏移量:0x07C，初值:0x00，宽度:8
 寄存器说明: LDO19开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo19_eco_en : 1;  /* bit[0]  : LDO19进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo19_en     : 1;  /* bit[1]  : LDO19使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO19_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_eco_en_START  (0)
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_eco_en_END    (0)
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_en_START      (1)
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO19_VSET1_UNION
 结构说明  : LDO19_VSET1 寄存器结构定义。地址偏移量:0x07D，初值:0x00，宽度:8
 寄存器说明: LDO19调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo19_vset : 3;  /* bit[0-2]: LDO19输出电压设置。
                                                     000：1.8V；
                                                     001：2.6V；
                                                     010：2.7V；
                                                     011：2.75V；
                                                     100：2.8V；
                                                     101：2.85V；
                                                     110：2.9V；
                                                     111：3.0V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO19_VSET1_UNION;
#endif
#define PMIC_LDO19_VSET1_ldo19_vset_START  (0)
#define PMIC_LDO19_VSET1_ldo19_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO20_ONOFF_ECO_UNION
 结构说明  : LDO20_ONOFF_ECO 寄存器结构定义。地址偏移量:0x07E，初值:0x00，宽度:8
 寄存器说明: LDO20开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo20_eco_en : 1;  /* bit[0]  : LDO20进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo20_en     : 1;  /* bit[1]  : LDO20使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO20_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_eco_en_START  (0)
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_eco_en_END    (0)
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_en_START      (1)
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO20_VSET_UNION
 结构说明  : LDO20_VSET 寄存器结构定义。地址偏移量:0x07F，初值:0x00，宽度:8
 寄存器说明: LDO20调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo20_vset : 4;  /* bit[0-3]: LDO20输出电压设置。
                                                     0000：0.80V；
                                                     0001：0.85V；
                                                     0010：0.90V；
                                                     0011：0.95V；
                                                     0100：1.00V；
                                                     0101：1.05V；
                                                     0110：1.10V；
                                                     0111：1.20V；
                                                     1000：1.25V；
                                                     1001：1.26V；
                                                     1010：1.27V；
                                                     1011：1.28V；
                                                     1100：1.29V；
                                                     1101：1.30V；
                                                     1110：1.31V；
                                                     1111：1.32V。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO20_VSET_UNION;
#endif
#define PMIC_LDO20_VSET_ldo20_vset_START  (0)
#define PMIC_LDO20_VSET_ldo20_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO21_ONOFF_ECO_UNION
 结构说明  : LDO21_ONOFF_ECO 寄存器结构定义。地址偏移量:0x080，初值:0x00，宽度:8
 寄存器说明: LDO21开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo21_eco_en : 1;  /* bit[0]  : LDO21进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo21_en     : 1;  /* bit[1]  : LDO21使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO21_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_eco_en_START  (0)
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_eco_en_END    (0)
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_en_START      (1)
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO21_VSET_UNION
 结构说明  : LDO21_VSET 寄存器结构定义。地址偏移量:0x081，初值:0x00，宽度:8
 寄存器说明: LDO21调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo21_vset : 3;  /* bit[0-2]: LDO21输出电压设置。
                                                     000：1.700V；
                                                     001：1.750V；
                                                     010：1.775V；
                                                     011：1.800V；
                                                     100：1.825V；
                                                     101：1.850V；
                                                     110：1.875V；
                                                     111：1.900V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO21_VSET_UNION;
#endif
#define PMIC_LDO21_VSET_ldo21_vset_START  (0)
#define PMIC_LDO21_VSET_ldo21_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO22_ONOFF_ECO_UNION
 结构说明  : LDO22_ONOFF_ECO 寄存器结构定义。地址偏移量:0x082，初值:0x00，宽度:8
 寄存器说明: LDO22开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo22_eco_en : 1;  /* bit[0]  : LDO22进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo22_en     : 1;  /* bit[1]  : LDO22使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO22_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_eco_en_START  (0)
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_eco_en_END    (0)
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_en_START      (1)
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO22_VSET_UNION
 结构说明  : LDO22_VSET 寄存器结构定义。地址偏移量:0x083，初值:0x00，宽度:8
 寄存器说明: LDO22调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_vset : 4;  /* bit[0-3]: LDO22输出电压设置。
                                                     0000：1.0V；
                                                     0001：1.05V；
                                                     0010：1.10V；
                                                     0011：1.15V；
                                                     0100：1.20V；
                                                     0101：1.25V；
                                                     0110：1.26V；
                                                     0111：1.27V。
                                                     1000：1.28V；
                                                     1001：1.29V；
                                                     1010：1.30V；
                                                     1011：1.31V；
                                                     1100：1.32V；
                                                     1101：1.33V；
                                                     1110：1.34V；
                                                     1111：1.50V。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO22_VSET_UNION;
#endif
#define PMIC_LDO22_VSET_ldo22_vset_START  (0)
#define PMIC_LDO22_VSET_ldo22_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO23_ONOFF_ECO_UNION
 结构说明  : LDO23_ONOFF_ECO 寄存器结构定义。地址偏移量:0x084，初值:0x02，宽度:8
 寄存器说明: LDO23开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo23_eco_en : 1;  /* bit[0]  : LDO23进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo23_en     : 1;  /* bit[1]  : LDO23使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO23_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_eco_en_START  (0)
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_eco_en_END    (0)
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_en_START      (1)
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO23_VSET_UNION
 结构说明  : LDO23_VSET 寄存器结构定义。地址偏移量:0x085，初值:0x07，宽度:8
 寄存器说明: LDO23调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo23_vset : 3;  /* bit[0-2]: LDO23输出电压设置。
                                                     000：2.6V；
                                                     001：2.7V；
                                                     010：2.8V；
                                                     011：2.9V；
                                                     100：3.0V；
                                                     101：3.1V；
                                                     110：3.2V；
                                                     111：3.3V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO23_VSET_UNION;
#endif
#define PMIC_LDO23_VSET_ldo23_vset_START  (0)
#define PMIC_LDO23_VSET_ldo23_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO24_ONOFF_ECO_UNION
 结构说明  : LDO24_ONOFF_ECO 寄存器结构定义。地址偏移量:0x086，初值:0x02，宽度:8
 寄存器说明: LDO24开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo24_eco_en : 1;  /* bit[0]  : LDO24进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo24_en     : 1;  /* bit[1]  : LDO24使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO24_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_eco_en_START  (0)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_eco_en_END    (0)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_en_START      (1)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO24_VSET_UNION
 结构说明  : LDO24_VSET 寄存器结构定义。地址偏移量:0x087，初值:0x02，宽度:8
 寄存器说明: LDO24调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo24_vset : 3;  /* bit[0-2]: LDO24输出电压设置。
                                                     000：2.6V；
                                                     001：2.7V；
                                                     010：2.8V；
                                                     011：2.85V；
                                                     100：3.0V；
                                                     101：3.1V；
                                                     110：3.2V；
                                                     111：3.3V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO24_VSET_UNION;
#endif
#define PMIC_LDO24_VSET_ldo24_vset_START  (0)
#define PMIC_LDO24_VSET_ldo24_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO25_ONOFF_ECO_UNION
 结构说明  : LDO25_ONOFF_ECO 寄存器结构定义。地址偏移量:0x088，初值:0x00，宽度:8
 寄存器说明: LDO25开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo25_eco_en : 1;  /* bit[0]  : LDO25进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo25_en     : 1;  /* bit[1]  : LDO25使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO25_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_eco_en_START  (0)
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_eco_en_END    (0)
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_en_START      (1)
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO25_VSET_UNION
 结构说明  : LDO25_VSET 寄存器结构定义。地址偏移量:0x089，初值:0x00，宽度:8
 寄存器说明: LDO25调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo25_vset : 3;  /* bit[0-2]: LDO25输出电压设置。
                                                     000：1.5V；
                                                     001：1.8V；
                                                     010：2.4V；
                                                     011：2.5V；
                                                     100：2.6V；
                                                     101：2.7V；
                                                     110：2.85V；
                                                     111：3.0V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO25_VSET_UNION;
#endif
#define PMIC_LDO25_VSET_ldo25_vset_START  (0)
#define PMIC_LDO25_VSET_ldo25_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO26_ONOFF_ECO_UNION
 结构说明  : LDO26_ONOFF_ECO 寄存器结构定义。地址偏移量:0x08A，初值:0x02，宽度:8
 寄存器说明: LDO26开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo26_eco_en : 1;  /* bit[0]  : LDO26进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo26_en     : 1;  /* bit[1]  : LDO26使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO26_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_eco_en_START  (0)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_eco_en_END    (0)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_en_START      (1)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO26_VSET_UNION
 结构说明  : LDO26_VSET 寄存器结构定义。地址偏移量:0x08B，初值:0x06，宽度:8
 寄存器说明: LDO26调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo26_vset : 3;  /* bit[0-2]: LDO26输出电压设置。
                                                     000：1.500V；
                                                     001：1.550V；
                                                     010：1.600V；
                                                     011：1.650V；
                                                     100：1.700V；
                                                     101：1.750V；
                                                     110：1.800V；
                                                     111：1.850V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO26_VSET_UNION;
#endif
#define PMIC_LDO26_VSET_ldo26_vset_START  (0)
#define PMIC_LDO26_VSET_ldo26_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO27_ONOFF_ECO_UNION
 结构说明  : LDO27_ONOFF_ECO 寄存器结构定义。地址偏移量:0x08C，初值:0x02，宽度:8
 寄存器说明: LDO27开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo27_eco_en : 1;  /* bit[0]  : LDO27进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo27_en     : 1;  /* bit[1]  : LDO27使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO27_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_eco_en_START  (0)
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_eco_en_END    (0)
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_en_START      (1)
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO27_VSET_UNION
 结构说明  : LDO27_VSET 寄存器结构定义。地址偏移量:0x08D，初值:0x05，宽度:8
 寄存器说明: LDO27调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo27_vset : 4;  /* bit[0-3]: LDO27输出电压设置。
                                                     0000：2.200V；
                                                     0001：2.250V；
                                                     0010：2.300V；
                                                     0011：2.350V；
                                                     0100：2.375V；
                                                     0101：2.400V；
                                                     0110：2.425V；
                                                     0111：2.450V；
                                                     1000：2.475V；
                                                     1001：2.500V；
                                                     1010：2.550V；
                                                     1011：2.600V；
                                                     1100：2.650V；
                                                     1101：2.700V；
                                                     1110：2.800V；
                                                     1111：2.850V。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO27_VSET_UNION;
#endif
#define PMIC_LDO27_VSET_ldo27_vset_START  (0)
#define PMIC_LDO27_VSET_ldo27_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO28_ONOFF_ECO_UNION
 结构说明  : LDO28_ONOFF_ECO 寄存器结构定义。地址偏移量:0x08E，初值:0x00，宽度:8
 寄存器说明: LDO28开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo28_eco_en : 1;  /* bit[0]  : LDO28进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo28_en     : 1;  /* bit[1]  : LDO28使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO28_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_eco_en_START  (0)
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_eco_en_END    (0)
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_en_START      (1)
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO28_VSET_UNION
 结构说明  : LDO28_VSET 寄存器结构定义。地址偏移量:0x08F，初值:0x00，宽度:8
 寄存器说明: LDO28调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo28_vset : 3;  /* bit[0-2]: LDO28输出电压设置。
                                                     000：1.700V；
                                                     001：1.750V；
                                                     010：1.775V；
                                                     011：1.800V；
                                                     100：1.825V；
                                                     101：1.850V；
                                                     110：1.875V；
                                                     111：1.900V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO28_VSET_UNION;
#endif
#define PMIC_LDO28_VSET_ldo28_vset_START  (0)
#define PMIC_LDO28_VSET_ldo28_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO29_ONOFF_ECO_UNION
 结构说明  : LDO29_ONOFF_ECO 寄存器结构定义。地址偏移量:0x090，初值:0x02，宽度:8
 寄存器说明: LDO29开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo29_eco_en : 1;  /* bit[0]  : LDO29进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo29_en     : 1;  /* bit[1]  : LDO29使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO29_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_eco_en_START  (0)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_eco_en_END    (0)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_en_START      (1)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO29_VSET_UNION
 结构说明  : LDO29_VSET 寄存器结构定义。地址偏移量:0x091，初值:0x33，宽度:8
 寄存器说明: LDO29调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo29_vset     : 3;  /* bit[0-2]: LDO29输出电压设置。
                                                         000：1.000V；
                                                         001：1.050V；
                                                         010：1.100V；
                                                         011：1.200V；
                                                         100：1.250V；
                                                         101：1.300V；
                                                         110：1.500V；
                                                         111：1.550V。 */
        unsigned char  reserved_0     : 1;  /* bit[3]  : 保留。 */
        unsigned char  ldo29_vset_adj : 3;  /* bit[4-6]: LDO29输出目标电压在PERI_EN有效时可配置的档位。
                                                         000：1.000V；
                                                         001：1.050V；
                                                         010：1.100V；
                                                         011：1.200V；
                                                         100：1.250V；
                                                         101：1.300V；
                                                         110：1.500V；
                                                         111：1.550V。 */
        unsigned char  reserved_1     : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_LDO29_VSET_UNION;
#endif
#define PMIC_LDO29_VSET_ldo29_vset_START      (0)
#define PMIC_LDO29_VSET_ldo29_vset_END        (2)
#define PMIC_LDO29_VSET_ldo29_vset_adj_START  (4)
#define PMIC_LDO29_VSET_ldo29_vset_adj_END    (6)


/*****************************************************************************
 结构名    : PMIC_LDO30_ONOFF_ECO_UNION
 结构说明  : LDO30_ONOFF_ECO 寄存器结构定义。地址偏移量:0x092，初值:0x02，宽度:8
 寄存器说明: LDO开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo30_eco_en : 1;  /* bit[0]  : LDO30进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo30_en     : 1;  /* bit[1]  : LDO30使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO30_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO30_ONOFF_ECO_reg_ldo30_eco_en_START  (0)
#define PMIC_LDO30_ONOFF_ECO_reg_ldo30_eco_en_END    (0)
#define PMIC_LDO30_ONOFF_ECO_reg_ldo30_en_START      (1)
#define PMIC_LDO30_ONOFF_ECO_reg_ldo30_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO30_VSET_UNION
 结构说明  : LDO30_VSET 寄存器结构定义。地址偏移量:0x093，初值:0x05，宽度:8
 寄存器说明: LDO30调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo30_vset : 4;  /* bit[0-3]: LDO30输出电压设置。
                                                     0000：0.700V；
                                                     0001：0.725V；
                                                     0010：0.750V；
                                                     0011：0.775V；
                                                     0100：0.790V；
                                                     0101：0.800V；
                                                     0110：0.810V；
                                                     0111：0.825V；
                                                     1000：0.830V；
                                                     1001：0.850V；
                                                     1010：0.875V；
                                                     1011：0.900V；
                                                     1100：0.925V；
                                                     1101：0.950V；
                                                     1110：0.975V；
                                                     1111：1.000V。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO30_VSET_UNION;
#endif
#define PMIC_LDO30_VSET_ldo30_vset_START  (0)
#define PMIC_LDO30_VSET_ldo30_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO31_ONOFF_ECO_UNION
 结构说明  : LDO31_ONOFF_ECO 寄存器结构定义。地址偏移量:0x094，初值:0x00，宽度:8
 寄存器说明: LDO31开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo31_eco_en : 1;  /* bit[0]  : LDO31进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo31_en     : 1;  /* bit[1]  : LDO31使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO31_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_eco_en_START  (0)
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_eco_en_END    (0)
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_en_START      (1)
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO31_VSET_UNION
 结构说明  : LDO31_VSET 寄存器结构定义。地址偏移量:0x095，初值:0x00，宽度:8
 寄存器说明: LDO31调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo31_vset  : 3;  /* bit[0-2]: LDO31输出电压设置。
                                                      000：2.50V；
                                                      001：2.60V；
                                                      010：2.70V；
                                                      011：2.80V；
                                                      100：2.90V；
                                                      101：3.00V；
                                                      110：3.10V；
                                                      111：3.20V。 */
        unsigned char  ldo_reserve : 5;  /* bit[3-7]: ldo保留寄存器 */
    } reg;
} PMIC_LDO31_VSET_UNION;
#endif
#define PMIC_LDO31_VSET_ldo31_vset_START   (0)
#define PMIC_LDO31_VSET_ldo31_vset_END     (2)
#define PMIC_LDO31_VSET_ldo_reserve_START  (3)
#define PMIC_LDO31_VSET_ldo_reserve_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO32_ONOFF_ECO_UNION
 结构说明  : LDO32_ONOFF_ECO 寄存器结构定义。地址偏移量:0x096，初值:0x00，宽度:8
 寄存器说明: LDO32开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo32_eco_en : 1;  /* bit[0]  : LDO32进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reg_ldo32_en     : 1;  /* bit[1]  : LDO32使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO32_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_eco_en_START  (0)
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_eco_en_END    (0)
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_en_START      (1)
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_LDO32_VSET_UNION
 结构说明  : LDO32_VSET 寄存器结构定义。地址偏移量:0x097，初值:0x00，宽度:8
 寄存器说明: LDO32调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo32_vset : 4;  /* bit[0-3]: LDO32输出电压设置。
                                                     0000：0.80V；
                                                     0001：0.85V；
                                                     0010：0.90V；
                                                     0011：0.95V；
                                                     0100：1.00V；
                                                     0101：1.05V；
                                                     0110：1.10V；
                                                     0111：1.20V；
                                                     1000：1.25V；
                                                     1001：1.26V；
                                                     1010：1.27V；
                                                     1011：1.28V；
                                                     1100：1.29V；
                                                     1101：1.30V；
                                                     1110：1.31V；
                                                     1111：1.32V。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO32_VSET_UNION;
#endif
#define PMIC_LDO32_VSET_ldo32_vset_START  (0)
#define PMIC_LDO32_VSET_ldo32_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_BUCK0_ONOFF_ECO_UNION
 结构说明  : BUCK0_ONOFF_ECO 寄存器结构定义。地址偏移量:0x098，初值:0x02，宽度:8
 寄存器说明: BUCK0开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck0_eco_en : 1;  /* bit[0]  : BUCK0 eco模式选择。
                                                           0：正常；
                                                           1：ECO模式。 */
        unsigned char  reg_buck0_en     : 1;  /* bit[1]  : BUCK0使能信号。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_BUCK0_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_eco_en_START  (0)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_eco_en_END    (0)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_en_START      (1)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_BUCK0_VSET_UNION
 结构说明  : BUCK0_VSET 寄存器结构定义。地址偏移量:0x099，初值:0x05，宽度:8
 寄存器说明: BUCK0调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_vset : 4;  /* bit[0-3]: BUCK0输出电压调节。
                                                     0000：0.700V；
                                                     0001：0.725V；
                                                     0010：0.750V；
                                                     0011：0.775V；
                                                     0100：0.790V；
                                                     0101：0.800V；
                                                     0110：0.810V；
                                                     0111：0.825V；
                                                     1000：0.830V；
                                                     1001：0.850V；
                                                     1010：0.875V；
                                                     1011：0.900V；
                                                     1100：0.925V；
                                                     1101：0.950V；
                                                     1110：0.975V；
                                                     1111：1.000V。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留 */
    } reg;
} PMIC_BUCK0_VSET_UNION;
#endif
#define PMIC_BUCK0_VSET_buck0_vset_START  (0)
#define PMIC_BUCK0_VSET_buck0_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_BUCK1_ONOFF_ECO_UNION
 结构说明  : BUCK1_ONOFF_ECO 寄存器结构定义。地址偏移量:0x09A，初值:0x02，宽度:8
 寄存器说明: BUCK1开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck1_eco_en : 1;  /* bit[0]  : BUCK1 eco模式选择。
                                                           0：正常；
                                                           1：ECO模式。 */
        unsigned char  reg_buck1_en     : 1;  /* bit[1]  : BUCK1使能信号。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_BUCK1_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_eco_en_START  (0)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_eco_en_END    (0)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_en_START      (1)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_BUCK1_VSET_UNION
 结构说明  : BUCK1_VSET 寄存器结构定义。地址偏移量:0x09B，初值:0xBB，宽度:8
 寄存器说明: BUCK1调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_vset     : 4;  /* bit[0-3]: BUCK1输出电压调节，默认开机电压1.2V, buck1_vol_sel控制默认值：0：1.2V；1：1.1V。
                                                         0000：0.925V；
                                                         0001：0.950V；
                                                         0010：0.975V；
                                                         0011：1.000V；
                                                         0100：1.025V；
                                                         0101：1.050V；
                                                         0110：1.075V；
                                                         0111：1.100V；
                                                         1000：1.125V；
                                                         1001：1.150V；
                                                         1010：1.175V；
                                                         1011：1.200V；
                                                         1100：1.225V；
                                                         1101：1.250V；
                                                         1110：1.275V；
                                                         1111：1.300V。 */
        unsigned char  buck1_vset_adj : 4;  /* bit[4-7]: BUCK1输出电压值在PERI_EN有效时可配置成不同档位的值,buck1_vol_sel控制默认值：0：1.2V；1：1.1V。
                                                         0000：0.925V；
                                                         0001：0.950V；
                                                         0010：0.975V；
                                                         0011：1.000V；
                                                         0100：1.025V；
                                                         0101：1.050V；
                                                         0110：1.075V；
                                                         0111：1.100V；
                                                         1000：1.125V；
                                                         1001：1.150V；
                                                         1010：1.175V；
                                                         1011：1.200V；
                                                         1100：1.225V；
                                                         1101：1.250V；
                                                         1110：1.275V；
                                                         1111：1.300V。 */
    } reg;
} PMIC_BUCK1_VSET_UNION;
#endif
#define PMIC_BUCK1_VSET_buck1_vset_START      (0)
#define PMIC_BUCK1_VSET_buck1_vset_END        (3)
#define PMIC_BUCK1_VSET_buck1_vset_adj_START  (4)
#define PMIC_BUCK1_VSET_buck1_vset_adj_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_ONOFF_ECO_UNION
 结构说明  : BUCK2_ONOFF_ECO 寄存器结构定义。地址偏移量:0x09C，初值:0x02，宽度:8
 寄存器说明: BUCK2开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck2_eco_en : 1;  /* bit[0]  : BUCK2 eco模式选择。
                                                           0：正常；
                                                           1：ECO模式。 */
        unsigned char  reg_buck2_en     : 1;  /* bit[1]  : BUCK2使能信号。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_BUCK2_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_eco_en_START  (0)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_eco_en_END    (0)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_en_START      (1)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_BUCK2_VSET_UNION
 结构说明  : BUCK2_VSET 寄存器结构定义。地址偏移量:0x09D，初值:0x44，宽度:8
 寄存器说明: BUCK2调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_vset     : 4;  /* bit[0-3]: BUCK2输出电压调节。
                                                         0000：1.350V；
                                                         0001：1.375V；
                                                         0010：1.400V；
                                                         0011：1.425V；
                                                         0100：1.450V；
                                                         0101：1.475V；
                                                         0110：1.500V；
                                                         0111：1.525V；
                                                         1000：1.550V；
                                                         1001：1.575V；
                                                         1010：1.600V；
                                                         1011：1.625V；
                                                         1100：1.650V；
                                                         1101：1.675V；
                                                         1110：1.700V；
                                                         1111：1.725V。 */
        unsigned char  buck2_vset_adj : 4;  /* bit[4-7]: BUCK2输出目标电压在PERI_EN有效时可配置的档位。
                                                         0000：1.350V；
                                                         0001：1.375V；
                                                         0010：1.400V；
                                                         0011：1.425V；
                                                         0100：1.450V；
                                                         0101：1.475V；
                                                         0110：1.500V；
                                                         0111：1.525V；
                                                         1000：1.550V；
                                                         1001：1.575V；
                                                         1010：1.600V；
                                                         1011：1.625V；
                                                         1100：1.650V；
                                                         1101：1.675V；
                                                         1110：1.700V；
                                                         1111：1.725V。 */
    } reg;
} PMIC_BUCK2_VSET_UNION;
#endif
#define PMIC_BUCK2_VSET_buck2_vset_START      (0)
#define PMIC_BUCK2_VSET_buck2_vset_END        (3)
#define PMIC_BUCK2_VSET_buck2_vset_adj_START  (4)
#define PMIC_BUCK2_VSET_buck2_vset_adj_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_ONOFF_ECO_UNION
 结构说明  : BUCK3_ONOFF_ECO 寄存器结构定义。地址偏移量:0x09E，初值:0x02，宽度:8
 寄存器说明: BUCK3开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck3_eco_en : 1;  /* bit[0]  : BUCK3 eco模式选择。
                                                           0：正常；
                                                           1：ECO模式。 */
        unsigned char  reg_buck3_en     : 1;  /* bit[1]  : BUCK3使能信号。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_BUCK3_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_eco_en_START  (0)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_eco_en_END    (0)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_en_START      (1)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_BUCK3_VSET_UNION
 结构说明  : BUCK3_VSET 寄存器结构定义。地址偏移量:0x09F，初值:0x77，宽度:8
 寄存器说明: BUCK3调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_vset     : 4;  /* bit[0-3]: BUCK3输出电压调节。
                                                         1.8/1.85/1.9/1.95/2.0/2.05/2.1/2.15/2.2/2.25/2.3/2.35/2.4/2.45/2.5/2.55，默认电压2.15V
                                                         0000：1.800V；
                                                         0001：1.850V；
                                                         0010：1.900V；
                                                         0011：1.950V；
                                                         0100：2.000V；
                                                         0101：2.050V；
                                                         0110：2.100V；
                                                         0111：2.150V；
                                                         1000：2.200V；
                                                         1001：2.250V；
                                                         1010：2.300V；
                                                         1011：2.350V；
                                                         1100：2.400V；
                                                         1101：2.450V；
                                                         1110：2.500V；
                                                         1111：2.550V。 */
        unsigned char  buck3_vset_adj : 4;  /* bit[4-7]: BUCK3输出目标电压在PERI_EN有效时可配置的档位。
                                                         1.8/1.85/1.9/1.95/2.0/2.05/2.1/2.15/2.2/2.25/2.3/2.35/2.4/2.45/2.5/2.55，默认电压2.15V
                                                         0000：1.800V；
                                                         0001：1.850V；
                                                         0010：1.900V；
                                                         0011：1.950V；
                                                         0100：2.000V；
                                                         0101：2.050V；
                                                         0110：2.100V；
                                                         0111：2.150V；
                                                         1000：2.200V；
                                                         1001：2.250V；
                                                         1010：2.300V；
                                                         1011：2.350V；
                                                         1100：2.400V；
                                                         1101：2.450V；
                                                         1110：2.500V；
                                                         1111：2.550V。 */
    } reg;
} PMIC_BUCK3_VSET_UNION;
#endif
#define PMIC_BUCK3_VSET_buck3_vset_START      (0)
#define PMIC_BUCK3_VSET_buck3_vset_END        (3)
#define PMIC_BUCK3_VSET_buck3_vset_adj_START  (4)
#define PMIC_BUCK3_VSET_buck3_vset_adj_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_ONOFF_ECO_UNION
 结构说明  : BUCK4_ONOFF_ECO 寄存器结构定义。地址偏移量:0x0A0，初值:0x02，宽度:8
 寄存器说明: BUCK4开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck4_eco_en : 1;  /* bit[0]  : BUCK4 eco模式选择。
                                                           0：正常；
                                                           1：ECO模式。 */
        unsigned char  reg_buck4_en     : 1;  /* bit[1]  : BUCK4使能信号。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved         : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_BUCK4_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK4_ONOFF_ECO_reg_buck4_eco_en_START  (0)
#define PMIC_BUCK4_ONOFF_ECO_reg_buck4_eco_en_END    (0)
#define PMIC_BUCK4_ONOFF_ECO_reg_buck4_en_START      (1)
#define PMIC_BUCK4_ONOFF_ECO_reg_buck4_en_END        (1)


/*****************************************************************************
 结构名    : PMIC_BUCK4_VSET_UNION
 结构说明  : BUCK4_VSET 寄存器结构定义。地址偏移量:0x0A1，初值:0x05，宽度:8
 寄存器说明: BUCK4调压控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_vset : 4;  /* bit[0-3]: BUCK4输出电压调节。
                                                     0000：0.700V；
                                                     0001：0.725V；
                                                     0010：0.750V；
                                                     0011：0.775V；
                                                     0100：0.790V；
                                                     0101：0.800V；
                                                     0110：0.810V；
                                                     0111：0.825V；
                                                     1000：0.830V；
                                                     1001：0.850V；
                                                     1010：0.875V；
                                                     1011：0.900V；
                                                     1100：0.925V；
                                                     1101：0.950V；
                                                     1110：0.975V；
                                                     1111：1.000V。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK4_VSET_UNION;
#endif
#define PMIC_BUCK4_VSET_buck4_vset_START  (0)
#define PMIC_BUCK4_VSET_buck4_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO_PMUA_ECO_UNION
 结构说明  : LDO_PMUA_ECO 寄存器结构定义。地址偏移量:0x0A2，初值:0x00，宽度:8
 寄存器说明: LDO_PMUA ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  pmua_eco_en : 1;  /* bit[0]  : PMUA进入ECO模式控制信号。
                                                      0：0代表normal模式；
                                                      1：ECO模式。 */
        unsigned char  reserved    : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_LDO_PMUA_ECO_UNION;
#endif
#define PMIC_LDO_PMUA_ECO_pmua_eco_en_START  (0)
#define PMIC_LDO_PMUA_ECO_pmua_eco_en_END    (0)


/*****************************************************************************
 结构名    : PMIC_LDO_PMUA_VSET_UNION
 结构说明  : LDO_PMUA_VSET 寄存器结构定义。地址偏移量:0x0A3，初值:0x05，宽度:8
 寄存器说明: LDO_PMUA调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  pmua_vset : 3;  /* bit[0-2]: LDO_PMUA输出电压设置。
                                                    000：2.5；
                                                    001：2.6；
                                                    010：2.7；
                                                    011：2.8；
                                                    100：2.9；
                                                    101：3.0；
                                                    110：3.1；
                                                    111：3.2。 */
        unsigned char  reserved  : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO_PMUA_VSET_UNION;
#endif
#define PMIC_LDO_PMUA_VSET_pmua_vset_START  (0)
#define PMIC_LDO_PMUA_VSET_pmua_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_BST_MODE_EN_UNION
 结构说明  : BST_MODE_EN 寄存器结构定义。地址偏移量:0x0A4，初值:0x03，宽度:8
 寄存器说明: BST使能控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck_boost_en_d : 1;  /* bit[0]  : 外置BUCK_BOOST芯片的使能信号，通过模拟PMUD（1.8V） IO输出。
                                                              0：关闭；
                                                              1：开启。 */
        unsigned char  buck_boost_en_mode  : 1;  /* bit[1]  : BUCK_BOOST保持常开使能信号。
                                                              0：表示随上下电；
                                                              1：表示常开。 */
        unsigned char  reserved            : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_BST_MODE_EN_UNION;
#endif
#define PMIC_BST_MODE_EN_reg_buck_boost_en_d_START  (0)
#define PMIC_BST_MODE_EN_reg_buck_boost_en_d_END    (0)
#define PMIC_BST_MODE_EN_buck_boost_en_mode_START   (1)
#define PMIC_BST_MODE_EN_buck_boost_en_mode_END     (1)


/*****************************************************************************
 结构名    : PMIC_NOPWR_CTRL_UNION
 结构说明  : NOPWR_CTRL 寄存器结构定义。地址偏移量:0x0A5，初值:0x01，宽度:8
 寄存器说明: NOPWRT控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_chg_en   : 1;  /* bit[0]  : 备用电池充电使能。
                                                      0：不使能；
                                                      1：使能。 */
        unsigned char  np_chg_vset : 2;  /* bit[1-2]: 备用电池充电电压选择。
                                                      00：2.5V(默认值）；
                                                      01：3.0V；
                                                      1X：3.3V。
                                                      注意：Austin实际为2档调压（2.5V默认，3.0V）为了与smartstar兼容，这边寄存器留2位，实际使用时只用2档。 */
        unsigned char  reserved    : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_NOPWR_CTRL_UNION;
#endif
#define PMIC_NOPWR_CTRL_np_chg_en_START    (0)
#define PMIC_NOPWR_CTRL_np_chg_en_END      (0)
#define PMIC_NOPWR_CTRL_np_chg_vset_START  (1)
#define PMIC_NOPWR_CTRL_np_chg_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_CLASSD_CTRL0_UNION
 结构说明  : CLASSD_CTRL0 寄存器结构定义。地址偏移量:0x0A6，初值:0x00，宽度:8
 寄存器说明: classd控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_classd_en   : 1;  /* bit[0]  : classD使能控制。
                                                          1：开启；
                                                          0：关闭。 */
        unsigned char  classd_mute     : 1;  /* bit[1]  : classd_mute控制。 
                                                          0：正常工作；
                                                          1：Mute。 */
        unsigned char  classd_mute_sel : 1;  /* bit[2]  : classd_mute_sel控制。 
                                                          0：延时mute模式（mute时立即mute,解除mute时，延时8ms,检测输入过零再解除）； 
                                                          1：正常mute模式（无8ms延时）。 */
        unsigned char  classd_drv_en   : 1;  /* bit[3]  : 驱动电路使能。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  classd_i_ocp    : 2;  /* bit[4-5]: classD过流阈值调节。
                                                          00：1.2A；
                                                          01：1.59A；
                                                          10：2.0A；
                                                          11：2.39A。 */
        unsigned char  classd_gain     : 2;  /* bit[6-7]: classD增益控制。 
                                                          00：12db；
                                                          01：15db；
                                                          10：18db；
                                                          11：21db。 */
    } reg;
} PMIC_CLASSD_CTRL0_UNION;
#endif
#define PMIC_CLASSD_CTRL0_reg_classd_en_START    (0)
#define PMIC_CLASSD_CTRL0_reg_classd_en_END      (0)
#define PMIC_CLASSD_CTRL0_classd_mute_START      (1)
#define PMIC_CLASSD_CTRL0_classd_mute_END        (1)
#define PMIC_CLASSD_CTRL0_classd_mute_sel_START  (2)
#define PMIC_CLASSD_CTRL0_classd_mute_sel_END    (2)
#define PMIC_CLASSD_CTRL0_classd_drv_en_START    (3)
#define PMIC_CLASSD_CTRL0_classd_drv_en_END      (3)
#define PMIC_CLASSD_CTRL0_classd_i_ocp_START     (4)
#define PMIC_CLASSD_CTRL0_classd_i_ocp_END       (5)
#define PMIC_CLASSD_CTRL0_classd_gain_START      (6)
#define PMIC_CLASSD_CTRL0_classd_gain_END        (7)


/*****************************************************************************
 结构名    : PMIC_CLASSD_CTRL1_UNION
 结构说明  : CLASSD_CTRL1 寄存器结构定义。地址偏移量:0x0A7，初值:0x00，宽度:8
 寄存器说明: classd控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_i_pump : 2;  /* bit[0-1]: Ramp波中，pump电流控制。
                                                        00：6μA；
                                                        01：7μA；
                                                        10：7μA；
                                                        11：8μA。 */
        unsigned char  classd_i_ramp : 2;  /* bit[2-3]: Ramp波中，比较器电流控制。
                                                        00：1μA；
                                                        01：3μA；
                                                        10：4μA；
                                                        11：5μA。 */
        unsigned char  classd_p_sel  : 2;  /* bit[4-5]: 驱动级pmos控制。
                                                        00：开一路pmos；
                                                        01：开两路pmos；
                                                        10：开三路pmos；
                                                        11：开四路pmos。 */
        unsigned char  classd_n_sel  : 2;  /* bit[6-7]: 驱动级nmos控制。
                                                        00：开一路nmos；
                                                        01：开两路nmos；
                                                        10：开三路nmos；
                                                        11：开四路nmos。 */
    } reg;
} PMIC_CLASSD_CTRL1_UNION;
#endif
#define PMIC_CLASSD_CTRL1_classd_i_pump_START  (0)
#define PMIC_CLASSD_CTRL1_classd_i_pump_END    (1)
#define PMIC_CLASSD_CTRL1_classd_i_ramp_START  (2)
#define PMIC_CLASSD_CTRL1_classd_i_ramp_END    (3)
#define PMIC_CLASSD_CTRL1_classd_p_sel_START   (4)
#define PMIC_CLASSD_CTRL1_classd_p_sel_END     (5)
#define PMIC_CLASSD_CTRL1_classd_n_sel_START   (6)
#define PMIC_CLASSD_CTRL1_classd_n_sel_END     (7)


/*****************************************************************************
 结构名    : PMIC_CLASSD_CTRL2_UNION
 结构说明  : CLASSD_CTRL2 寄存器结构定义。地址偏移量:0x0A8，初值:0x00，宽度:8
 寄存器说明: classd控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_pls_byp  : 1;  /* bit[0]  : 最小脉宽门限。
                                                          0：正常工作；
                                                          1：bypass最小脉宽限制。 */
        unsigned char  classd_dt_sel   : 1;  /* bit[1]  : dead time控制。
                                                          0：2ns；
                                                          1：7ns。 */
        unsigned char  classd_fx_bps   : 1;  /* bit[2]  : 扩频模式控制。
                                                          0：开启扩频模式；
                                                          1：bypass扩频模式（固定频率）。 */
        unsigned char  classd_ocp_bps  : 1;  /* bit[3]  : 过流保护控制。
                                                          0：开启过流保护；
                                                          1：bypass过流保护电路（OCP信号不上报）。 */
        unsigned char  classd_reserve0 : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_CLASSD_CTRL2_UNION;
#endif
#define PMIC_CLASSD_CTRL2_classd_pls_byp_START   (0)
#define PMIC_CLASSD_CTRL2_classd_pls_byp_END     (0)
#define PMIC_CLASSD_CTRL2_classd_dt_sel_START    (1)
#define PMIC_CLASSD_CTRL2_classd_dt_sel_END      (1)
#define PMIC_CLASSD_CTRL2_classd_fx_bps_START    (2)
#define PMIC_CLASSD_CTRL2_classd_fx_bps_END      (2)
#define PMIC_CLASSD_CTRL2_classd_ocp_bps_START   (3)
#define PMIC_CLASSD_CTRL2_classd_ocp_bps_END     (3)
#define PMIC_CLASSD_CTRL2_classd_reserve0_START  (4)
#define PMIC_CLASSD_CTRL2_classd_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLASSD_CTRL3_UNION
 结构说明  : CLASSD_CTRL3 寄存器结构定义。地址偏移量:0x0A9，初值:0x00，宽度:8
 寄存器说明: classd控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_reserve1 : 8;  /* bit[0-7]: 保留。 */
    } reg;
} PMIC_CLASSD_CTRL3_UNION;
#endif
#define PMIC_CLASSD_CTRL3_classd_reserve1_START  (0)
#define PMIC_CLASSD_CTRL3_classd_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_TH_CTRL_UNION
 结构说明  : TH_CTRL 寄存器结构定义。地址偏移量:0x0AA，初值:0x32，宽度:8
 寄存器说明: 电压温度控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_eco_en   : 1;  /* bit[0]  : ref_top模式选择位。
                                                       0：ref_top正常工作；
                                                       1：ref_top进入eco模式。 */
        unsigned char  reg_thsd_en  : 1;  /* bit[1]  : THSD过温保护模块关闭开关控制位。
                                                       0：关闭THSD过温保护模块；
                                                       1：开启THSD过温保护模块。 */
        unsigned char  thsd_eco_en  : 1;  /* bit[2]  : THSD过温保护ECO模式开关控制位。
                                                       0：关闭THSD过温保护ECO模式；
                                                       1：开启THSD过温保护ECO模式。 */
        unsigned char  reserved_0   : 1;  /* bit[3]  : 保留。 */
        unsigned char  thsd_tmp_set : 2;  /* bit[4-5]: 温度保护模块报警温度设置。
                                                       00：95℃；
                                                       01：105℃；
                                                       10：115℃；
                                                       11：125℃。 */
        unsigned char  reserved_1   : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_TH_CTRL_UNION;
#endif
#define PMIC_TH_CTRL_ref_eco_en_START    (0)
#define PMIC_TH_CTRL_ref_eco_en_END      (0)
#define PMIC_TH_CTRL_reg_thsd_en_START   (1)
#define PMIC_TH_CTRL_reg_thsd_en_END     (1)
#define PMIC_TH_CTRL_thsd_eco_en_START   (2)
#define PMIC_TH_CTRL_thsd_eco_en_END     (2)
#define PMIC_TH_CTRL_thsd_tmp_set_START  (4)
#define PMIC_TH_CTRL_thsd_tmp_set_END    (5)


/*****************************************************************************
 结构名    : PMIC_BG_TEST_UNION
 结构说明  : BG_TEST 寄存器结构定义。地址偏移量:0x0AB，初值:0x00，宽度:8
 寄存器说明: bg测试寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_test : 8;  /* bit[0-7]: 基准测试模式预留。 */
    } reg;
} PMIC_BG_TEST_UNION;
#endif
#define PMIC_BG_TEST_ref_test_START  (0)
#define PMIC_BG_TEST_ref_test_END    (7)


/*****************************************************************************
 结构名    : PMIC_DR_EN_MODE_345_UNION
 结构说明  : DR_EN_MODE_345 寄存器结构定义。地址偏移量:0x0AC，初值:0x00，宽度:8
 寄存器说明: DR345闪烁模式使能和模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_dr3_int : 1;  /* bit[0]  : DR3工作在闪烁模式下（dr3_mode_sel=1）开关控制。
                                                     0：关闭DR3；
                                                     1：开启DR3。  */
        unsigned char  dr3_mode   : 1;  /* bit[1]  : DR3闪动模式开关控制。
                                                     0：关闭闪动模式(此时表现为持续输出)；
                                                     1：开启DR3闪动模式。  */
        unsigned char  en_dr4_int : 1;  /* bit[2]  : DR4工作在闪烁模式下（dr4_mode_sel=1）开关控制。
                                                     0：关闭DR4；
                                                     1：开启DR4。  */
        unsigned char  dr4_mode   : 1;  /* bit[3]  : DR4闪动模式开关控制。
                                                     0：关闭闪动模式(此时表现为持续输出)；
                                                     1：开启DR4闪动模式。  */
        unsigned char  en_dr5_int : 1;  /* bit[4]  : DR5工作在闪烁模式下（dr5_mode_sel=1）开关控制。
                                                     0：关闭DR5；
                                                     1：开启DR5。  */
        unsigned char  dr5_mode   : 1;  /* bit[5]  : DR5闪动模式开关控制。
                                                     0：关闭闪动模式(此时表现为持续输出)；
                                                     1：开启DR5闪动模式。  */
        unsigned char  reserved   : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_DR_EN_MODE_345_UNION;
#endif
#define PMIC_DR_EN_MODE_345_en_dr3_int_START  (0)
#define PMIC_DR_EN_MODE_345_en_dr3_int_END    (0)
#define PMIC_DR_EN_MODE_345_dr3_mode_START    (1)
#define PMIC_DR_EN_MODE_345_dr3_mode_END      (1)
#define PMIC_DR_EN_MODE_345_en_dr4_int_START  (2)
#define PMIC_DR_EN_MODE_345_en_dr4_int_END    (2)
#define PMIC_DR_EN_MODE_345_dr4_mode_START    (3)
#define PMIC_DR_EN_MODE_345_dr4_mode_END      (3)
#define PMIC_DR_EN_MODE_345_en_dr5_int_START  (4)
#define PMIC_DR_EN_MODE_345_en_dr5_int_END    (4)
#define PMIC_DR_EN_MODE_345_dr5_mode_START    (5)
#define PMIC_DR_EN_MODE_345_dr5_mode_END      (5)


/*****************************************************************************
 结构名    : PMIC_DR_EN_MODE_12_UNION
 结构说明  : DR_EN_MODE_12 寄存器结构定义。地址偏移量:0x0AD，初值:0x00，宽度:8
 寄存器说明: DR12闪烁模式使能和模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_dr1_int : 1;  /* bit[0]  : DR1工作在闪烁模式下（dr1_mode_sel=1）开关控制。
                                                     0：关闭DR1；
                                                     1：开启DR1 。  */
        unsigned char  dr1_mode   : 1;  /* bit[1]  : DR1闪动模式开关控制。
                                                     0：关闭闪动模式(此时表现为持续输出)；
                                                     1：开启DR1闪动模式。  */
        unsigned char  en_dr2_int : 1;  /* bit[2]  : DR2工作在闪烁模式下（dr2_mode_sel=1）开关控制。
                                                     0：关闭DR2；
                                                     1：开启DR2。  */
        unsigned char  dr2_mode   : 1;  /* bit[3]  : DR2闪动模式开关控制。
                                                     0：关闭闪动模式(此时表现为持续输出)；
                                                     1：开启DR2闪动模式。  */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_DR_EN_MODE_12_UNION;
#endif
#define PMIC_DR_EN_MODE_12_en_dr1_int_START  (0)
#define PMIC_DR_EN_MODE_12_en_dr1_int_END    (0)
#define PMIC_DR_EN_MODE_12_dr1_mode_START    (1)
#define PMIC_DR_EN_MODE_12_dr1_mode_END      (1)
#define PMIC_DR_EN_MODE_12_en_dr2_int_START  (2)
#define PMIC_DR_EN_MODE_12_en_dr2_int_END    (2)
#define PMIC_DR_EN_MODE_12_dr2_mode_START    (3)
#define PMIC_DR_EN_MODE_12_dr2_mode_END      (3)


/*****************************************************************************
 结构名    : PMIC_FLASH_PERIOD_DR12_UNION
 结构说明  : FLASH_PERIOD_DR12 寄存器结构定义。地址偏移量:0x0AE，初值:0x3F，宽度:8
 寄存器说明: DR12闪烁模式周期调节0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_period_dr12 : 8;  /* bit[0-7]: 闪烁周期T = 配置值 *31.25ms。 */
    } reg;
} PMIC_FLASH_PERIOD_DR12_UNION;
#endif
#define PMIC_FLASH_PERIOD_DR12_flash_period_dr12_START  (0)
#define PMIC_FLASH_PERIOD_DR12_flash_period_dr12_END    (7)


/*****************************************************************************
 结构名    : PMIC_FLASH_ON_DR12_UNION
 结构说明  : FLASH_ON_DR12 寄存器结构定义。地址偏移量:0x0AF，初值:0x1F，宽度:8
 寄存器说明: DR12闪烁模式点亮时间调节0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_on_dr12 : 8;  /* bit[0-7]: 点亮时间t =配置值 *7.8125ms。 */
    } reg;
} PMIC_FLASH_ON_DR12_UNION;
#endif
#define PMIC_FLASH_ON_DR12_flash_on_dr12_START  (0)
#define PMIC_FLASH_ON_DR12_flash_on_dr12_END    (7)


/*****************************************************************************
 结构名    : PMIC_FLASH_PERIOD_DR345_UNION
 结构说明  : FLASH_PERIOD_DR345 寄存器结构定义。地址偏移量:0x0B0，初值:0x3F，宽度:8
 寄存器说明: DR345闪烁模式周期调节1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_period_dr345 : 8;  /* bit[0-7]: 闪烁周期T = 配置值 *31.25ms。 */
    } reg;
} PMIC_FLASH_PERIOD_DR345_UNION;
#endif
#define PMIC_FLASH_PERIOD_DR345_flash_period_dr345_START  (0)
#define PMIC_FLASH_PERIOD_DR345_flash_period_dr345_END    (7)


/*****************************************************************************
 结构名    : PMIC_FLASH_ON_DR345_UNION
 结构说明  : FLASH_ON_DR345 寄存器结构定义。地址偏移量:0x0B1，初值:0x1F，宽度:8
 寄存器说明: DR345闪烁模式点亮时间调节1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_on_dr345 : 8;  /* bit[0-7]: 点亮时间t =配置值 *7.8125ms。 */
    } reg;
} PMIC_FLASH_ON_DR345_UNION;
#endif
#define PMIC_FLASH_ON_DR345_flash_on_dr345_START  (0)
#define PMIC_FLASH_ON_DR345_flash_on_dr345_END    (7)


/*****************************************************************************
 结构名    : PMIC_DR_MODE_SEL_UNION
 结构说明  : DR_MODE_SEL 寄存器结构定义。地址偏移量:0x0B2，初值:0x00，宽度:8
 寄存器说明: DR灯模式选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr1_mode_sel : 1;  /* bit[0]  : DR1工作模式选择。
                                                       0： DR1工作在呼吸功能模式；
                                                       1：DR1工作在闪烁模式。 */
        unsigned char  dr2_mode_sel : 1;  /* bit[1]  : DR2工作模式选择。
                                                       0： DR2工作在呼吸功能模式；
                                                       1：DR2工作在闪烁模式。 */
        unsigned char  dr3_mode_sel : 1;  /* bit[2]  : DR3工作模式选择。
                                                       0： DR3工作在呼吸功能模式；
                                                       1：DR3工作在闪烁模式。 */
        unsigned char  dr4_mode_sel : 1;  /* bit[3]  : DR4工作模式选择。
                                                       0： DR4工作在呼吸功能模式；
                                                       1：DR4工作在闪烁模式。 */
        unsigned char  dr5_mode_sel : 1;  /* bit[4]  : DR5工作模式选择。
                                                       0： DR5工作在呼吸功能模式；
                                                       1：DR5工作在闪烁模式。 */
        unsigned char  reserved     : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_DR_MODE_SEL_UNION;
#endif
#define PMIC_DR_MODE_SEL_dr1_mode_sel_START  (0)
#define PMIC_DR_MODE_SEL_dr1_mode_sel_END    (0)
#define PMIC_DR_MODE_SEL_dr2_mode_sel_START  (1)
#define PMIC_DR_MODE_SEL_dr2_mode_sel_END    (1)
#define PMIC_DR_MODE_SEL_dr3_mode_sel_START  (2)
#define PMIC_DR_MODE_SEL_dr3_mode_sel_END    (2)
#define PMIC_DR_MODE_SEL_dr4_mode_sel_START  (3)
#define PMIC_DR_MODE_SEL_dr4_mode_sel_END    (3)
#define PMIC_DR_MODE_SEL_dr5_mode_sel_START  (4)
#define PMIC_DR_MODE_SEL_dr5_mode_sel_END    (4)


/*****************************************************************************
 结构名    : PMIC_DR_BRE_CTRL_UNION
 结构说明  : DR_BRE_CTRL 寄存器结构定义。地址偏移量:0x0B3，初值:0x00，宽度:8
 寄存器说明: DR1/2呼吸模式控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_dr1_en   : 1;  /* bit[0]  : DR1工作在呼吸（dr1_mode_sel=0）模式使能。
                                                       0：dr1关闭 ； 
                                                       1：dr1使能。
                                                       dr1_flash_en = 1,呼吸 ；
                                                       dr1_flash_en = 0,常亮 。 */
        unsigned char  dr1_flash_en : 1;  /* bit[1]  : DR1呼吸使能。
                                                       0：不使能dr1呼吸模式；
                                                       1：使能dr1呼吸模式。 */
        unsigned char  reserved_0   : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_dr2_en   : 1;  /* bit[4]  : DR2工作在呼吸（dr2_mode_sel=0）模式使能。
                                                       0：dr2关闭 ； 
                                                       1：dr2使能。
                                                       dr2_flash_en = 1,呼吸 ；
                                                       dr2_flash_en = 0,常亮 。 */
        unsigned char  dr2_flash_en : 1;  /* bit[5]  : DR2呼吸使能。
                                                       0：不使能dr2呼吸模式。
                                                       1：使能dr2呼吸模式。 */
        unsigned char  reserved_1   : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_DR_BRE_CTRL_UNION;
#endif
#define PMIC_DR_BRE_CTRL_reg_dr1_en_START    (0)
#define PMIC_DR_BRE_CTRL_reg_dr1_en_END      (0)
#define PMIC_DR_BRE_CTRL_dr1_flash_en_START  (1)
#define PMIC_DR_BRE_CTRL_dr1_flash_en_END    (1)
#define PMIC_DR_BRE_CTRL_reg_dr2_en_START    (4)
#define PMIC_DR_BRE_CTRL_reg_dr2_en_END      (4)
#define PMIC_DR_BRE_CTRL_dr2_flash_en_START  (5)
#define PMIC_DR_BRE_CTRL_dr2_flash_en_END    (5)


/*****************************************************************************
 结构名    : PMIC_DR12_TIM_CONF0_UNION
 结构说明  : DR12_TIM_CONF0 寄存器结构定义。地址偏移量:0x0B4，初值:0x33，宽度:8
 寄存器说明: DR1和DR2常亮常暗时间配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr12_t_off : 3;  /* bit[0-2]: DR12呼吸模式下长暗时间。
                                                     000：1ms；
                                                     001：0.25s；
                                                     010：0.5s；
                                                     011：1s；
                                                     100：2s；
                                                     101：4s；
                                                     110：4s；
                                                     111：长暗。 */
        unsigned char  reserved_0 : 1;  /* bit[3]  : 保留。 */
        unsigned char  dr12_t_on  : 3;  /* bit[4-6]: DR12呼吸模式下长亮时间配置。
                                                     000：1ms；
                                                     001：0.25s；
                                                     010：0.5s；
                                                     011：1s；
                                                     100：2s；
                                                     101：4s；
                                                     110：4s；
                                                     111：长亮。 */
        unsigned char  reserved_1 : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_DR12_TIM_CONF0_UNION;
#endif
#define PMIC_DR12_TIM_CONF0_dr12_t_off_START  (0)
#define PMIC_DR12_TIM_CONF0_dr12_t_off_END    (2)
#define PMIC_DR12_TIM_CONF0_dr12_t_on_START   (4)
#define PMIC_DR12_TIM_CONF0_dr12_t_on_END     (6)


/*****************************************************************************
 结构名    : PMIC_DR12_TIM_CONF1_UNION
 结构说明  : DR12_TIM_CONF1 寄存器结构定义。地址偏移量:0x0B5，初值:0x33，宽度:8
 寄存器说明: DR1和DR2渐亮渐暗时间配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr12_t_rise : 3;  /* bit[0-2]: DR12呼吸模式下渐亮时间。
                                                      000：0s；
                                                      001：0.25s；
                                                      010：0.5s；
                                                      011：1s；
                                                      100：2s；
                                                      101：2.5s；
                                                      110：3s；
                                                      111：4s。 */
        unsigned char  reserved_0  : 1;  /* bit[3]  : 保留。 */
        unsigned char  dr12_t_fall : 3;  /* bit[4-6]: DR12呼吸模式下渐暗时间。
                                                      000：0s；
                                                      001：0.25s；
                                                      010：0.5s；
                                                      011：1s；
                                                      100：2s；
                                                      101：2.5s；
                                                      110：3s；
                                                      111：4s。 */
        unsigned char  reserved_1  : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_DR12_TIM_CONF1_UNION;
#endif
#define PMIC_DR12_TIM_CONF1_dr12_t_rise_START  (0)
#define PMIC_DR12_TIM_CONF1_dr12_t_rise_END    (2)
#define PMIC_DR12_TIM_CONF1_dr12_t_fall_START  (4)
#define PMIC_DR12_TIM_CONF1_dr12_t_fall_END    (6)


/*****************************************************************************
 结构名    : PMIC_DR1_ISET_UNION
 结构说明  : DR1_ISET 寄存器结构定义。地址偏移量:0x0B6，初值:0x00，宽度:8
 寄存器说明: DR1电流选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr1_iset : 3;  /* bit[0-2]: DR1电流调节。 000：3 mA；
                                                   001：6 mA；
                                                   010：9 mA；
                                                   011：12 mA；
                                                   100：15 mA；
                                                   101：18 mA；
                                                   110：21 mA；
                                                   111：24 mA。 */
        unsigned char  reserved : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_DR1_ISET_UNION;
#endif
#define PMIC_DR1_ISET_dr1_iset_START  (0)
#define PMIC_DR1_ISET_dr1_iset_END    (2)


/*****************************************************************************
 结构名    : PMIC_DR2_ISET_UNION
 结构说明  : DR2_ISET 寄存器结构定义。地址偏移量:0x0B7，初值:0x00，宽度:8
 寄存器说明: DR2电流选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr2_iset : 3;  /* bit[0-2]: DR2电流调节。 000：3 mA；
                                                   001：6 mA；
                                                   010：9 mA；
                                                   011：12 mA；
                                                   100：15 mA；
                                                   101：18 mA；
                                                   110：21 mA；
                                                   111：24 mA。 */
        unsigned char  reserved : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_DR2_ISET_UNION;
#endif
#define PMIC_DR2_ISET_dr2_iset_START  (0)
#define PMIC_DR2_ISET_dr2_iset_END    (2)


/*****************************************************************************
 结构名    : PMIC_DR_LED_CTRL_UNION
 结构说明  : DR_LED_CTRL 寄存器结构定义。地址偏移量:0x0B8，初值:0x00，宽度:8
 寄存器说明: DR3/4/5控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_dr3_en : 1;  /* bit[0]  : 呼吸模式下DR3使能。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned char  reg_dr4_en : 1;  /* bit[1]  : 呼吸模式下DR4使能。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned char  reg_dr5_en : 1;  /* bit[2]  : 呼吸模式下DR5使能。
                                                     0：不使能；
                                                     1：使能。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_DR_LED_CTRL_UNION;
#endif
#define PMIC_DR_LED_CTRL_reg_dr3_en_START  (0)
#define PMIC_DR_LED_CTRL_reg_dr3_en_END    (0)
#define PMIC_DR_LED_CTRL_reg_dr4_en_START  (1)
#define PMIC_DR_LED_CTRL_reg_dr4_en_END    (1)
#define PMIC_DR_LED_CTRL_reg_dr5_en_START  (2)
#define PMIC_DR_LED_CTRL_reg_dr5_en_END    (2)


/*****************************************************************************
 结构名    : PMIC_DR_OUT_CTRL_UNION
 结构说明  : DR_OUT_CTRL 寄存器结构定义。地址偏移量:0x0B9，初值:0x00，宽度:8
 寄存器说明: DR3/4/5输出控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr3_out_ctrl : 2;  /* bit[0-1]: DR3输出控制。
                                                       00：DR3的配置项输出到DR3管脚；
                                                       01：DR3与DR4相或后的配置项输出到DR3管脚；
                                                       10：DR3与DR4、DR5相或后的配置项输出到DR3管脚；
                                                       11：DR4与DR5相或后的配置项输出到DR3管脚。 */
        unsigned char  dr4_out_ctrl : 2;  /* bit[2-3]: DR4输出控制。
                                                       00：DR4的配置项输出到DR4管脚；
                                                       01：DR3与DR4相或后的配置项输出到DR4管脚；
                                                       10：DR3与DR4、DR5相或后的配置项输出到DR4管脚；
                                                       11：DR4与DR5相或后的配置项输出到DR4管脚。 */
        unsigned char  dr5_out_ctrl : 2;  /* bit[4-5]: DR5输出控制。
                                                       00：DR5的配置项输出到DR5管脚；
                                                       01：DR3与DR4相或后的配置项输出到DR5管脚；
                                                       10：DR3与DR4、DR5相或后的配置项输出到DR5管脚；
                                                       11：DR4与DR5相或后的配置项输出到DR5管脚。 */
        unsigned char  reserved     : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_DR_OUT_CTRL_UNION;
#endif
#define PMIC_DR_OUT_CTRL_dr3_out_ctrl_START  (0)
#define PMIC_DR_OUT_CTRL_dr3_out_ctrl_END    (1)
#define PMIC_DR_OUT_CTRL_dr4_out_ctrl_START  (2)
#define PMIC_DR_OUT_CTRL_dr4_out_ctrl_END    (3)
#define PMIC_DR_OUT_CTRL_dr5_out_ctrl_START  (4)
#define PMIC_DR_OUT_CTRL_dr5_out_ctrl_END    (5)


/*****************************************************************************
 结构名    : PMIC_DR3_ISET_UNION
 结构说明  : DR3_ISET 寄存器结构定义。地址偏移量:0x0BA，初值:0x00，宽度:8
 寄存器说明: DR3电流选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr3_iset : 3;  /* bit[0-2]: DR3输出电流调节（mA）。
                                                   0x0 ：1.0；
                                                   0x1 ：1.5；
                                                   0x2 ：2.0；
                                                   0x3 ：2.5；
                                                   0x4 ：3.0；
                                                   0x5 ：3.5；
                                                   0x6 ：4.0；
                                                   0x7 ：4.5。 */
        unsigned char  reserved : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_DR3_ISET_UNION;
#endif
#define PMIC_DR3_ISET_dr3_iset_START  (0)
#define PMIC_DR3_ISET_dr3_iset_END    (2)


/*****************************************************************************
 结构名    : PMIC_DR3_START_DEL_UNION
 结构说明  : DR3_START_DEL 寄存器结构定义。地址偏移量:0x0BB，初值:0x10，宽度:8
 寄存器说明: DR3启动延时配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr3_start_delay : 8;  /* bit[0-7]: DR3启动延时范围：0～32768 ms，step：125ms。 */
    } reg;
} PMIC_DR3_START_DEL_UNION;
#endif
#define PMIC_DR3_START_DEL_dr3_start_delay_START  (0)
#define PMIC_DR3_START_DEL_dr3_start_delay_END    (7)


/*****************************************************************************
 结构名    : PMIC_DR4_ISET_UNION
 结构说明  : DR4_ISET 寄存器结构定义。地址偏移量:0x0BC，初值:0x00，宽度:8
 寄存器说明: DR4电流选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr4_iset : 3;  /* bit[0-2]: DR4输出电流调节（mA）。
                                                   0x0 ：1.0；
                                                   0x1 ：1.5；
                                                   0x2 ：2.0；
                                                   0x3 ：2.5；
                                                   0x4 ：3.0；
                                                   0x5 ：3.5；
                                                   0x6 ：4.0；
                                                   0x7 ：4.5。 */
        unsigned char  reserved : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_DR4_ISET_UNION;
#endif
#define PMIC_DR4_ISET_dr4_iset_START  (0)
#define PMIC_DR4_ISET_dr4_iset_END    (2)


/*****************************************************************************
 结构名    : PMIC_DR4_START_DEL_UNION
 结构说明  : DR4_START_DEL 寄存器结构定义。地址偏移量:0x0BD，初值:0x10，宽度:8
 寄存器说明: DR4启动延时配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr4_start_delay : 8;  /* bit[0-7]: DR4启动延时范围：0～32768 ms，step：125ms。 */
    } reg;
} PMIC_DR4_START_DEL_UNION;
#endif
#define PMIC_DR4_START_DEL_dr4_start_delay_START  (0)
#define PMIC_DR4_START_DEL_dr4_start_delay_END    (7)


/*****************************************************************************
 结构名    : PMIC_DR5_ISET_UNION
 结构说明  : DR5_ISET 寄存器结构定义。地址偏移量:0x0BE，初值:0x00，宽度:8
 寄存器说明: DR5电流选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr5_iset : 3;  /* bit[0-2]: DR5输出电流调节（mA）。
                                                   0x0 ：1.0；
                                                   0x1 ：1.5；
                                                   0x2 ：2.0；
                                                   0x3 ：2.5；
                                                   0x4 ：3.0；
                                                   0x5 ：3.5；
                                                   0x6 ：4.0；
                                                   0x7 ：4.5。 */
        unsigned char  reserved : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_DR5_ISET_UNION;
#endif
#define PMIC_DR5_ISET_dr5_iset_START  (0)
#define PMIC_DR5_ISET_dr5_iset_END    (2)


/*****************************************************************************
 结构名    : PMIC_DR5_START_DEL_UNION
 结构说明  : DR5_START_DEL 寄存器结构定义。地址偏移量:0x0BF，初值:0x10，宽度:8
 寄存器说明: DR5启动延时配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr5_start_delay : 8;  /* bit[0-7]: DR5启动延时范围：0～32768 ms，step：125ms。 */
    } reg;
} PMIC_DR5_START_DEL_UNION;
#endif
#define PMIC_DR5_START_DEL_dr5_start_delay_START  (0)
#define PMIC_DR5_START_DEL_dr5_start_delay_END    (7)


/*****************************************************************************
 结构名    : PMIC_DR334_TIM_CONF0_UNION
 结构说明  : DR334_TIM_CONF0 寄存器结构定义。地址偏移量:0x0C0，初值:0x44，宽度:8
 寄存器说明: DR345常亮常暗时间配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr345_t_off : 4;  /* bit[0-3]: DR345常亮时间配置。
                                                      000：0s；
                                                      001：0.5s；
                                                      010：1s；
                                                      011：2s；
                                                      100：4s；
                                                      101：6s；
                                                      110：8s；
                                                      111：12s；
                                                      1000：14；
                                                      1001：16；
                                                      其他：常暗。 */
        unsigned char  dr345_t_on  : 4;  /* bit[4-7]: DR345常亮时间配置。
                                                      0000：0s；
                                                      0001：0.5s；
                                                      0010：1s；
                                                      0011：2s；
                                                      0100：4s；
                                                      0101：6s；
                                                      0110：8s；
                                                      0111：12s；
                                                      1000：14；
                                                      1001：16；
                                                      其他：常亮。 */
    } reg;
} PMIC_DR334_TIM_CONF0_UNION;
#endif
#define PMIC_DR334_TIM_CONF0_dr345_t_off_START  (0)
#define PMIC_DR334_TIM_CONF0_dr345_t_off_END    (3)
#define PMIC_DR334_TIM_CONF0_dr345_t_on_START   (4)
#define PMIC_DR334_TIM_CONF0_dr345_t_on_END     (7)


/*****************************************************************************
 结构名    : PMIC_DR345_TIM_CONF1_UNION
 结构说明  : DR345_TIM_CONF1 寄存器结构定义。地址偏移量:0x0C1，初值:0x33，宽度:8
 寄存器说明: DR345渐亮渐暗时间配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr345_t_rise : 3;  /* bit[0-2]: DR345渐暗时间配置。
                                                       000：0s；
                                                       001：0.25s；
                                                       010：0.5s；
                                                       011：1s；
                                                       100：2s；
                                                       101：2.5s；
                                                       110：3s；
                                                       111：4s。 */
        unsigned char  reserved_0   : 1;  /* bit[3]  : 保留。 */
        unsigned char  dr345_t_fall : 3;  /* bit[4-6]: DR345渐暗时间配置。
                                                       000：0s；
                                                       001：0.25s；
                                                       010：0.5s；
                                                       011：1s；
                                                       100：2s；
                                                       101：2.5s；
                                                       110：3s；
                                                       111：4s。 */
        unsigned char  reserved_1   : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_DR345_TIM_CONF1_UNION;
#endif
#define PMIC_DR345_TIM_CONF1_dr345_t_rise_START  (0)
#define PMIC_DR345_TIM_CONF1_dr345_t_rise_END    (2)
#define PMIC_DR345_TIM_CONF1_dr345_t_fall_START  (4)
#define PMIC_DR345_TIM_CONF1_dr345_t_fall_END    (6)


/*****************************************************************************
 结构名    : PMIC_VSYS_LOW_SET0_UNION
 结构说明  : VSYS_LOW_SET0 寄存器结构定义。地址偏移量:0x0C2，初值:0x1E，宽度:8
 寄存器说明: IN端低压阈值调整寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_uv_set         : 4;  /* bit[0-3]: vsys端输入低电压判断阈值电压调节，低于此电压上报中断。
                                                              0000： 2.60V；
                                                              0001： 2.70V；
                                                              0010：2.80V；
                                                              0011：2.90V；
                                                              0100：3.00V；
                                                              0101：3.10V；
                                                              0110：3.20V；
                                                              0111：3.30V；
                                                              1000：3.35V；
                                                              1001：3.40V；
                                                              1010：3.45V；
                                                              1011：3.50V；
                                                              1100：3.55V；
                                                              1101：3.60V；
                                                              1110：3.65V；
                                                              1111：3.70V。
                                                              滤波时间参见UV_VSYS__DEB_CTRL[vsys_uv_deb_sel]。 */
        unsigned char  vsys_pwroff_deb_set : 3;  /* bit[4-6]: 关机电压阈值调节，低于此电压PMU关机。
                                                              000： 2.5V；
                                                              001： 2.6V；
                                                              010： 2.7V；
                                                              011：2.8V；
                                                              100：2.9V；
                                                              101：3.0V；
                                                              110：3.1V；
                                                              111：3.2V。
                                                              滤波时间参见UV_VSYS_DEB_CTRL[vsys_pwroff_deb_sel]。 */
        unsigned char  vsys_pwroff_abs_set : 1;  /* bit[7]  : vsys端低电压判断阈值电压调整，低于此电压立刻关机，不滤波。
                                                              0：2.3V；
                                                              1：2.4V。 */
    } reg;
} PMIC_VSYS_LOW_SET0_UNION;
#endif
#define PMIC_VSYS_LOW_SET0_vsys_uv_set_START          (0)
#define PMIC_VSYS_LOW_SET0_vsys_uv_set_END            (3)
#define PMIC_VSYS_LOW_SET0_vsys_pwroff_deb_set_START  (4)
#define PMIC_VSYS_LOW_SET0_vsys_pwroff_deb_set_END    (6)
#define PMIC_VSYS_LOW_SET0_vsys_pwroff_abs_set_START  (7)
#define PMIC_VSYS_LOW_SET0_vsys_pwroff_abs_set_END    (7)


/*****************************************************************************
 结构名    : PMIC_VSYS_LOW_SET1_UNION
 结构说明  : VSYS_LOW_SET1 寄存器结构定义。地址偏移量:0x0C3，初值:0x02，宽度:8
 寄存器说明: IN端低压阈值调整寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_pwron_set : 3;  /* bit[0-2]: 开机电压阈值调节，高于此电压PMU开机。
                                                         000：2.6V；
                                                         001：2.7V；
                                                         010：2.8V；
                                                         011：2.9V；
                                                         100：3.0V；
                                                         101：3.1V；
                                                         110：3.2V；
                                                         111：3.3V。 */
        unsigned char  reserved_0     : 1;  /* bit[3]  : 保留。 */
        unsigned char  nfc_on_d2a     : 1;  /* bit[4]  : NFC_ON输出管脚，非掉电寄存器，放在PMUD域下面。
                                                         0：NFC_ON管脚输出0电平；
                                                         1：NFC_ON管脚输出1.8V。 */
        unsigned char  reserved_1     : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_VSYS_LOW_SET1_UNION;
#endif
#define PMIC_VSYS_LOW_SET1_vsys_pwron_set_START  (0)
#define PMIC_VSYS_LOW_SET1_vsys_pwron_set_END    (2)
#define PMIC_VSYS_LOW_SET1_nfc_on_d2a_START      (4)
#define PMIC_VSYS_LOW_SET1_nfc_on_d2a_END        (4)


/*****************************************************************************
 结构名    : PMIC_SYS_CTRL_RESERVE_UNION
 结构说明  : SYS_CTRL_RESERVE 寄存器结构定义。地址偏移量:0x0C4，初值:0x00，宽度:8
 寄存器说明: 系统控制预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_ctrl_reserve : 8;  /* bit[0-7]: 系统控制模块预留寄存器。 */
    } reg;
} PMIC_SYS_CTRL_RESERVE_UNION;
#endif
#define PMIC_SYS_CTRL_RESERVE_sys_ctrl_reserve_START  (0)
#define PMIC_SYS_CTRL_RESERVE_sys_ctrl_reserve_END    (7)


/*****************************************************************************
 结构名    : PMIC_HARDWIRE_CTRL0_UNION
 结构说明  : HARDWIRE_CTRL0 寄存器结构定义。地址偏移量:0x0C5，初值:0x3F，宽度:8
 寄存器说明: 硬线屏蔽控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_eco_in_hd_mask   : 1;  /* bit[0]  : 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对eco_in_n的拉低/拉高控制作用。
                                                               0：不屏蔽；
                                                               1：屏蔽。 */
        unsigned char  reg_xo_core_hd_mask  : 1;  /* bit[1]  : 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对xo_core_en的拉低/拉高控制作用。
                                                               0：不屏蔽；
                                                               1：屏蔽。 */
        unsigned char  reg_xo_ldo_hd_mask   : 1;  /* bit[2]  : 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对xo_ldo_en的拉低/拉高控制作用。
                                                               0：不屏蔽；
                                                               1：屏蔽。 */
        unsigned char  reg_sys_clk_hd_mask  : 1;  /* bit[3]  : 是否屏蔽硬线SYS_CLK_EN对sys_clk的开/关控制作用。
                                                               0：不屏蔽；
                                                               1：屏蔽。 */
        unsigned char  reg_abb_clk_hd_mask  : 1;  /* bit[4]  : 是否屏蔽硬线SYS_CLK_EN对abb_clk的开/关控制作用。
                                                               0：不屏蔽；
                                                               1：屏蔽。 */
        unsigned char  reg_wifi_clk_hd_mask : 1;  /* bit[5]  : 是否屏蔽硬线WIFIBT_CLK_EN对wifibt_clk的开/关控制作用。
                                                               0：不屏蔽；
                                                               1：屏蔽。 */
        unsigned char  reserved             : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_HARDWIRE_CTRL0_UNION;
#endif
#define PMIC_HARDWIRE_CTRL0_reg_eco_in_hd_mask_START    (0)
#define PMIC_HARDWIRE_CTRL0_reg_eco_in_hd_mask_END      (0)
#define PMIC_HARDWIRE_CTRL0_reg_xo_core_hd_mask_START   (1)
#define PMIC_HARDWIRE_CTRL0_reg_xo_core_hd_mask_END     (1)
#define PMIC_HARDWIRE_CTRL0_reg_xo_ldo_hd_mask_START    (2)
#define PMIC_HARDWIRE_CTRL0_reg_xo_ldo_hd_mask_END      (2)
#define PMIC_HARDWIRE_CTRL0_reg_sys_clk_hd_mask_START   (3)
#define PMIC_HARDWIRE_CTRL0_reg_sys_clk_hd_mask_END     (3)
#define PMIC_HARDWIRE_CTRL0_reg_abb_clk_hd_mask_START   (4)
#define PMIC_HARDWIRE_CTRL0_reg_abb_clk_hd_mask_END     (4)
#define PMIC_HARDWIRE_CTRL0_reg_wifi_clk_hd_mask_START  (5)
#define PMIC_HARDWIRE_CTRL0_reg_wifi_clk_hd_mask_END    (5)


/*****************************************************************************
 结构名    : PMIC_HARDWIRE_CTRL1_UNION
 结构说明  : HARDWIRE_CTRL1 寄存器结构定义。地址偏移量:0x0C6，初值:0x1F，宽度:8
 寄存器说明: 硬线屏蔽控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo27_hd_mask : 1;  /* bit[0]  : 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对ldo27的开/关控制作用。
                                                            0：不屏蔽；
                                                            1：屏蔽。 */
        unsigned char  reg_ldo26_hd_mask : 2;  /* bit[1-2]: 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对ld26的开/关及进/出eco控制作用。
                                                            00：保留；
                                                            01：屏蔽组合逻辑对ldo26的开/关控制，不屏蔽组合逻辑对LDO26的进/出eco控制（这种配置下，ldo26的使能寄存器必须为1，ldo26的eco使能寄存器必须为0，ldo26才可能受控于组合逻辑而进/出eco模式）；
                                                            10：不屏蔽组合逻辑对LDO26的开/关控制，屏蔽组合逻辑对ldo26的进/出eco控制（这种配置下，ldo26的使能寄存器必须为0，ldo26才有可能受控于组合逻辑而开/关）；
                                                            11：屏蔽组合逻辑对ldo26的开/关和进/出eco控制（这种配置下，ldo26的开/关只受控于自身使能寄存器，ldo26的进/出eco功能只受控于自身的eco使能寄存器，当然其使能寄存器必须为1才有可能真正进入eco模式）。 */
        unsigned char  reg_ldo14_hd_mask : 1;  /* bit[3]  : 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对ldo14的开/关控制作用。
                                                            0：不屏蔽；
                                                            1：屏蔽。 */
        unsigned char  reg_ldo13_hd_mask : 1;  /* bit[4]  : 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对ldo13的开/关控制作用。
                                                            0：不屏蔽；
                                                            1：屏蔽。 */
        unsigned char  reserved          : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_HARDWIRE_CTRL1_UNION;
#endif
#define PMIC_HARDWIRE_CTRL1_reg_ldo27_hd_mask_START  (0)
#define PMIC_HARDWIRE_CTRL1_reg_ldo27_hd_mask_END    (0)
#define PMIC_HARDWIRE_CTRL1_reg_ldo26_hd_mask_START  (1)
#define PMIC_HARDWIRE_CTRL1_reg_ldo26_hd_mask_END    (2)
#define PMIC_HARDWIRE_CTRL1_reg_ldo14_hd_mask_START  (3)
#define PMIC_HARDWIRE_CTRL1_reg_ldo14_hd_mask_END    (3)
#define PMIC_HARDWIRE_CTRL1_reg_ldo13_hd_mask_START  (4)
#define PMIC_HARDWIRE_CTRL1_reg_ldo13_hd_mask_END    (4)


/*****************************************************************************
 结构名    : PMIC_PERI_CTRL0_UNION
 结构说明  : PERI_CTRL0 寄存器结构定义。地址偏移量:0x0C7，初值:0x00，宽度:8
 寄存器说明: peri硬线控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo5_on    : 1;  /* bit[0]: LDO5是否受控于peri_en控制位。
                                                           0：不受peri_en控制而开/关；
                                                           1：受peri_en控制而开/关。 */
        unsigned char  peri_en_ldo2_eco   : 1;  /* bit[1]: LDO2是否受控于peri_en控制位。
                                                           0：不受peri_en控制而进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo0_2_eco : 1;  /* bit[2]: LDO0_2是否受控于peri_en控制位。
                                                           0：不受peri_en控制而进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_buck4_on   : 1;  /* bit[3]: BUCK4是否受控于peri_en控制位。
                                                           0：不受peri_en控制而开/关；
                                                           1：受peri_en控制而开/关。 */
        unsigned char  peri_en_buck3_eco  : 1;  /* bit[4]: BUCK3是否受控于peri_en控制位。
                                                           0：不受peri_en控制而进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_buck2_eco  : 1;  /* bit[5]: BUCK2是否受控于peri_en控制位。
                                                           0：不受peri_en控制而进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_buck1_eco  : 1;  /* bit[6]: BUCK1是否受控于peri_en控制位。
                                                           0：不受peri_en控制而进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_buck0_on   : 1;  /* bit[7]: BUCK0是否受控于peri_en控制位。
                                                           0：不受peri_en控制而开/关；
                                                           1：受peri_en控制而开/关。 */
    } reg;
} PMIC_PERI_CTRL0_UNION;
#endif
#define PMIC_PERI_CTRL0_peri_en_ldo5_on_START     (0)
#define PMIC_PERI_CTRL0_peri_en_ldo5_on_END       (0)
#define PMIC_PERI_CTRL0_peri_en_ldo2_eco_START    (1)
#define PMIC_PERI_CTRL0_peri_en_ldo2_eco_END      (1)
#define PMIC_PERI_CTRL0_peri_en_ldo0_2_eco_START  (2)
#define PMIC_PERI_CTRL0_peri_en_ldo0_2_eco_END    (2)
#define PMIC_PERI_CTRL0_peri_en_buck4_on_START    (3)
#define PMIC_PERI_CTRL0_peri_en_buck4_on_END      (3)
#define PMIC_PERI_CTRL0_peri_en_buck3_eco_START   (4)
#define PMIC_PERI_CTRL0_peri_en_buck3_eco_END     (4)
#define PMIC_PERI_CTRL0_peri_en_buck2_eco_START   (5)
#define PMIC_PERI_CTRL0_peri_en_buck2_eco_END     (5)
#define PMIC_PERI_CTRL0_peri_en_buck1_eco_START   (6)
#define PMIC_PERI_CTRL0_peri_en_buck1_eco_END     (6)
#define PMIC_PERI_CTRL0_peri_en_buck0_on_START    (7)
#define PMIC_PERI_CTRL0_peri_en_buck0_on_END      (7)


/*****************************************************************************
 结构名    : PMIC_PERI_CTRL1_UNION
 结构说明  : PERI_CTRL1 寄存器结构定义。地址偏移量:0x0C8，初值:0x00，宽度:8
 寄存器说明: peri硬线控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo30_on  : 1;  /* bit[0]: LDO30是否受控于peri_en控制位。
                                                          0：不受peri_en控制而开/关；
                                                          1：受peri_en控制而开/关。 */
        unsigned char  peri_en_ldo29_eco : 1;  /* bit[1]: LDO29是否受控于peri_en控制位。
                                                          0：不受peri_en控制而进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo23_on  : 1;  /* bit[2]: LDO23是否受控于peri_en控制位。
                                                          0：不受peri_en控制而开/关；
                                                          1：受peri_en控制而开/关。 */
        unsigned char  peri_en_ldo12_eco : 1;  /* bit[3]: LDO12是否受控于peri_en控制位。
                                                          0：不受peri_en控制而进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo11_eco : 1;  /* bit[4]: LDO11是否受控于peri_en控制位。
                                                          0：不受peri_en控制而进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo10_on  : 1;  /* bit[5]: LDO10是否受控于peri_en控制位。
                                                          0：不受peri_en控制而开/关；
                                                          1：受peri_en控制而开/关。 */
        unsigned char  peri_en_ldo8_on   : 1;  /* bit[6]: LDO8是否受控于peri_en控制位。
                                                          0：不受peri_en控制而开/关；
                                                          1：受peri_en控制而开/关。 */
        unsigned char  peri_en_ldo7_on   : 1;  /* bit[7]: LDO7是否受控于peri_en控制位。
                                                          0：不受peri_en控制而开/关；
                                                          1：受peri_en控制而开/关。 */
    } reg;
} PMIC_PERI_CTRL1_UNION;
#endif
#define PMIC_PERI_CTRL1_peri_en_ldo30_on_START   (0)
#define PMIC_PERI_CTRL1_peri_en_ldo30_on_END     (0)
#define PMIC_PERI_CTRL1_peri_en_ldo29_eco_START  (1)
#define PMIC_PERI_CTRL1_peri_en_ldo29_eco_END    (1)
#define PMIC_PERI_CTRL1_peri_en_ldo23_on_START   (2)
#define PMIC_PERI_CTRL1_peri_en_ldo23_on_END     (2)
#define PMIC_PERI_CTRL1_peri_en_ldo12_eco_START  (3)
#define PMIC_PERI_CTRL1_peri_en_ldo12_eco_END    (3)
#define PMIC_PERI_CTRL1_peri_en_ldo11_eco_START  (4)
#define PMIC_PERI_CTRL1_peri_en_ldo11_eco_END    (4)
#define PMIC_PERI_CTRL1_peri_en_ldo10_on_START   (5)
#define PMIC_PERI_CTRL1_peri_en_ldo10_on_END     (5)
#define PMIC_PERI_CTRL1_peri_en_ldo8_on_START    (6)
#define PMIC_PERI_CTRL1_peri_en_ldo8_on_END      (6)
#define PMIC_PERI_CTRL1_peri_en_ldo7_on_START    (7)
#define PMIC_PERI_CTRL1_peri_en_ldo7_on_END      (7)


/*****************************************************************************
 结构名    : PMIC_PERI_VSET_CTRL_UNION
 结构说明  : PERI_VSET_CTRL 寄存器结构定义。地址偏移量:0x0C9，初值:0x00，宽度:8
 寄存器说明: peri硬线调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_buck3_vset  : 1;  /* bit[0]  : BUCK3电压是否受控于peri_en控制位进入目标电压。
                                                              0：不受peri_en控制而进入；
                                                              1：受peri_en控制而进入。 */
        unsigned char  peri_en_buck2_vset  : 1;  /* bit[1]  : BUCK2电压是否受控于peri_en控制位进入目标电压。
                                                              0：不受peri_en控制而进入；
                                                              1：受peri_en控制而进入。 */
        unsigned char  peri_en_buck1_vset  : 1;  /* bit[2]  : BUCK1电压是否受控于peri_en控制位进入目标电压。
                                                              0：不受peri_en控制而进入；
                                                              1：受peri_en控制而进入。 */
        unsigned char  peri_en_ldo29_vset  : 1;  /* bit[3]  : LDO29电压是否受控于peri_en控制位进入目标电压。
                                                              0：不受peri_en控制而进入；
                                                              1：受peri_en控制而进入。 */
        unsigned char  peri_en_ldo2_vset   : 1;  /* bit[4]  : LDO2电压是否受控于peri_en控制位进入目标电压。
                                                              0：不受peri_en控制而进入；
                                                              1：受peri_en控制而进入。 */
        unsigned char  peri_en_ldo0_2_vset : 1;  /* bit[5]  : LDO0_2电压是否受控于peri_en控制位进入目标电压。
                                                              0：不受peri_en控制而进入；
                                                              1：受peri_en控制而进入。 */
        unsigned char  reserved            : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_PERI_VSET_CTRL_UNION;
#endif
#define PMIC_PERI_VSET_CTRL_peri_en_buck3_vset_START   (0)
#define PMIC_PERI_VSET_CTRL_peri_en_buck3_vset_END     (0)
#define PMIC_PERI_VSET_CTRL_peri_en_buck2_vset_START   (1)
#define PMIC_PERI_VSET_CTRL_peri_en_buck2_vset_END     (1)
#define PMIC_PERI_VSET_CTRL_peri_en_buck1_vset_START   (2)
#define PMIC_PERI_VSET_CTRL_peri_en_buck1_vset_END     (2)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo29_vset_START   (3)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo29_vset_END     (3)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo2_vset_START    (4)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo2_vset_END      (4)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo0_2_vset_START  (5)
#define PMIC_PERI_VSET_CTRL_peri_en_ldo0_2_vset_END    (5)


/*****************************************************************************
 结构名    : PMIC_PERI_TIME__CTRL_UNION
 结构说明  : PERI_TIME__CTRL 寄存器结构定义。地址偏移量:0x0CA，初值:0x00，宽度:8
 寄存器说明: peri硬线时间间隔控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0   : 1;  /* bit[0]  : 预留寄存器 */
        unsigned char  ldo8_on_sel  : 1;  /* bit[1]  : LDO5和LDO8上电间隔控制位。
                                                       0：peri_en拉高时LDO5和LDO8上电间隔为120us；
                                                       1：peri_en拉高时LDO5和LDO8上电间隔为60us。
                                                       LDO8和LDO10上电间隔控制位。
                                                       0：peri_en拉高时LDO8和LDO10上电间隔为120us；
                                                       1：peri_en拉高时LDO8和LDO10上电间隔为60us。 */
        unsigned char  ldo5_on_sel  : 1;  /* bit[2]  : LDO7和LDO5上电间隔控制位。
                                                       0：peri_en拉高时LDO7和LDO5上电间隔为120us；
                                                       1：peri_en拉高时LDO7和LDO5上电间隔为60us。 */
        unsigned char  ldo7_on_sel  : 1;  /* bit[3]  : BUCK4和LDO7上电间隔控制位。
                                                       0：peri_en拉高时BUCK4和LDO7上电间隔为240us；
                                                       1：peri_en拉高时BUCK4和LDO7上电间隔为120us。 */
        unsigned char  buck4_on_sel : 1;  /* bit[4]  : BUCK0和BUCK4上电间隔控制位。
                                                       0：peri_en拉高时BUCK0和BUCK4上电间隔为240us；
                                                       1：peri_en拉高时BUCK0和BUCK4上电间隔为120us。 */
        unsigned char  reserved_1   : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_PERI_TIME__CTRL_UNION;
#endif
#define PMIC_PERI_TIME__CTRL_ldo8_on_sel_START   (1)
#define PMIC_PERI_TIME__CTRL_ldo8_on_sel_END     (1)
#define PMIC_PERI_TIME__CTRL_ldo5_on_sel_START   (2)
#define PMIC_PERI_TIME__CTRL_ldo5_on_sel_END     (2)
#define PMIC_PERI_TIME__CTRL_ldo7_on_sel_START   (3)
#define PMIC_PERI_TIME__CTRL_ldo7_on_sel_END     (3)
#define PMIC_PERI_TIME__CTRL_buck4_on_sel_START  (4)
#define PMIC_PERI_TIME__CTRL_buck4_on_sel_END    (4)


/*****************************************************************************
 结构名    : PMIC_HRESET_PWRDOWN_CTRL_UNION
 结构说明  : HRESET_PWRDOWN_CTRL 寄存器结构定义。地址偏移量:0x0CB，初值:0x01，宽度:8
 寄存器说明: 热复位下电控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hreset_mode : 1;  /* bit[0]  : HRESET_N功能模式选择位。
                                                      0：hreset下电重启；
                                                      1：hreset热复位重启。 */
        unsigned char  reserved    : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_HRESET_PWRDOWN_CTRL_UNION;
#endif
#define PMIC_HRESET_PWRDOWN_CTRL_hreset_mode_START  (0)
#define PMIC_HRESET_PWRDOWN_CTRL_hreset_mode_END    (0)


/*****************************************************************************
 结构名    : PMIC_OSC32K_ONOFF_CTRL_UNION
 结构说明  : OSC32K_ONOFF_CTRL 寄存器结构定义。地址偏移量:0x0CC，初值:0x01，宽度:8
 寄存器说明: 32kHz时钟输出使能控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_32k_sys : 1;  /* bit[0]  : CLK32_SYS 输出使能位。
                                                     0：不输出；
                                                     1：32kHz时钟输出。 */
        unsigned char  en_32k_bt  : 1;  /* bit[1]  : CLK32_BT 输出使能位。
                                                     0：不输出；
                                                     1：32kHz时钟输出。 */
        unsigned char  en_32k_gps : 1;  /* bit[2]  : CLK32_GPS 输出使能位。
                                                     0：不输出；
                                                     1：32kHz时钟输出。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_OSC32K_ONOFF_CTRL_UNION;
#endif
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_sys_START  (0)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_sys_END    (0)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_bt_START   (1)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_bt_END     (1)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_gps_START  (2)
#define PMIC_OSC32K_ONOFF_CTRL_en_32k_gps_END    (2)


/*****************************************************************************
 结构名    : PMIC_OCP_DEB_CTRL_UNION
 结构说明  : OCP_DEB_CTRL 寄存器结构定义。地址偏移量:0x0CD，初值:0x02，宽度:8
 寄存器说明: OCP和SPC滤波时间控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  scp_ocp_deb_sel2 : 3;  /* bit[0-2]: LDO的OCP滤波时间。
                                                           000：150us（非绝对150us，可能是180us到210us等较小值）；
                                                           001：0.5ms；
                                                           010：1ms；
                                                           011：2ms；
                                                           100：4ms；
                                                           101：20ms；
                                                           110：40ms；
                                                           111：80ms。
                                                           注：LDO没有滤波使能，默认就使能滤波。 */
        unsigned char  reserved_0       : 1;  /* bit[3]  : 保留。 */
        unsigned char  scp_ocp_deb_sel1 : 3;  /* bit[4-6]: BUCK的OCP和SCP，classd的OCP，滤波时间选择。
                                                           000：60us（非绝对60us，可能是90us或120us等较小值）；
                                                           001：0.5ms；
                                                           010：1ms；
                                                           011：2ms；
                                                           100：4ms；
                                                           101：20ms；
                                                           110：40ms；
                                                           111：80ms。
                                                           注：classd没有滤波使能信号，因此默认为000情况下，则classd滤波60us，而BUCK 需要开启使能信号才有滤波，当不使能情况下，滤波为0us。 */
        unsigned char  reserved_1       : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_OCP_DEB_CTRL_UNION;
#endif
#define PMIC_OCP_DEB_CTRL_scp_ocp_deb_sel2_START  (0)
#define PMIC_OCP_DEB_CTRL_scp_ocp_deb_sel2_END    (2)
#define PMIC_OCP_DEB_CTRL_scp_ocp_deb_sel1_START  (4)
#define PMIC_OCP_DEB_CTRL_scp_ocp_deb_sel1_END    (6)


/*****************************************************************************
 结构名    : PMIC_OCP_SCP_ONOFF_UNION
 结构说明  : OCP_SCP_ONOFF 寄存器结构定义。地址偏移量:0x0CE，初值:0x03，宽度:8
 寄存器说明: OCP和DOCP滤波开关寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_buck_scp_deb : 1;  /* bit[0]  : BUCK scp滤波功能使能位。
                                                          0：BUCK scp 滤波不使能；
                                                          1：BUCK scp 滤波使能。 */
        unsigned char  en_buck_ocp_deb : 1;  /* bit[1]  : BUCK OCP滤波功能使能位。
                                                          0：BUCK OCP 滤波不使能；
                                                          1：BUCK OCP 滤波使能。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_OCP_SCP_ONOFF_UNION;
#endif
#define PMIC_OCP_SCP_ONOFF_en_buck_scp_deb_START  (0)
#define PMIC_OCP_SCP_ONOFF_en_buck_scp_deb_END    (0)
#define PMIC_OCP_SCP_ONOFF_en_buck_ocp_deb_START  (1)
#define PMIC_OCP_SCP_ONOFF_en_buck_ocp_deb_END    (1)


/*****************************************************************************
 结构名    : PMIC_UV_VSYS_DEB_CTRL_UNION
 结构说明  : UV_VSYS_DEB_CTRL 寄存器结构定义。地址偏移量:0x0CF，初值:0xA7，宽度:8
 寄存器说明: 欠压告警和欠压关机滤波时间选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_pwroff_deb_sel : 3;  /* bit[0-2]: vsys小于2.6V指示信号去抖时间。
                                                              000：0ms（非绝对0可能是30us或60us等较小值）；
                                                              001：0.45ms；
                                                              010：0.9ms；
                                                              011：1.8ms；
                                                              100：3.6ms；
                                                              101：20ms；
                                                              110：40ms；
                                                              111：80ms。 */
        unsigned char  reserved            : 1;  /* bit[3]  : 保留。 */
        unsigned char  vsys_uv_deb_sel     : 4;  /* bit[4-7]: vsys_uv滤波时间选择。
                                                              0000：0.25ms；
                                                              0001：0.5ms；
                                                              0010：1ms；
                                                              0011：2ms；
                                                              0100：3ms；
                                                              0101：4ms；
                                                              0110：5ms；
                                                              0111：6ms；
                                                              1000：7ms；
                                                              1001：8ms；
                                                              1010：10ms；
                                                              1011：20ms；
                                                              1100：30ms；
                                                              1101：40ms；
                                                              1110：60ms；
                                                              1111：80ms。 */
    } reg;
} PMIC_UV_VSYS_DEB_CTRL_UNION;
#endif
#define PMIC_UV_VSYS_DEB_CTRL_vsys_pwroff_deb_sel_START  (0)
#define PMIC_UV_VSYS_DEB_CTRL_vsys_pwroff_deb_sel_END    (2)
#define PMIC_UV_VSYS_DEB_CTRL_vsys_uv_deb_sel_START      (4)
#define PMIC_UV_VSYS_DEB_CTRL_vsys_uv_deb_sel_END        (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_3_OCP_CTRL_UNION
 结构说明  : BUCK0_3_OCP_CTRL 寄存器结构定义。地址偏移量:0x0D0，初值:0xFF，宽度:8
 寄存器说明: BUCK0/1/2/3 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ocp_auto_stop : 2;  /* bit[0-1]: BUCK3在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck2_ocp_auto_stop : 2;  /* bit[2-3]: BUCK2在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck1_ocp_auto_stop : 2;  /* bit[4-5]: BUCK1在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck0_ocp_auto_stop : 2;  /* bit[6-7]: BUCK0在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_BUCK0_3_OCP_CTRL_UNION;
#endif
#define PMIC_BUCK0_3_OCP_CTRL_buck3_ocp_auto_stop_START  (0)
#define PMIC_BUCK0_3_OCP_CTRL_buck3_ocp_auto_stop_END    (1)
#define PMIC_BUCK0_3_OCP_CTRL_buck2_ocp_auto_stop_START  (2)
#define PMIC_BUCK0_3_OCP_CTRL_buck2_ocp_auto_stop_END    (3)
#define PMIC_BUCK0_3_OCP_CTRL_buck1_ocp_auto_stop_START  (4)
#define PMIC_BUCK0_3_OCP_CTRL_buck1_ocp_auto_stop_END    (5)
#define PMIC_BUCK0_3_OCP_CTRL_buck0_ocp_auto_stop_START  (6)
#define PMIC_BUCK0_3_OCP_CTRL_buck0_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK4_LDO0_1_OCP_CTRL_UNION
 结构说明  : BUCK4_LDO0_1_OCP_CTRL 寄存器结构定义。地址偏移量:0x0D1，初值:0xF7，宽度:8
 寄存器说明: BUCK4/LDO0/1/2 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_ocp_auto_stop  : 2;  /* bit[0-1]: LDO2在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo1_ocp_auto_stop  : 2;  /* bit[2-3]: LDO1在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo0_ocp_auto_stop  : 2;  /* bit[4-5]: LDO0在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck4_ocp_auto_stop : 2;  /* bit[6-7]: BUCK4在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_BUCK4_LDO0_1_OCP_CTRL_UNION;
#endif
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo2_ocp_auto_stop_START   (0)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo2_ocp_auto_stop_END     (1)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo1_ocp_auto_stop_START   (2)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo1_ocp_auto_stop_END     (3)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo0_ocp_auto_stop_START   (4)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_ldo0_ocp_auto_stop_END     (5)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_buck4_ocp_auto_stop_START  (6)
#define PMIC_BUCK4_LDO0_1_OCP_CTRL_buck4_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO3_7_OCP_CTRL_UNION
 结构说明  : LDO3_7_OCP_CTRL 寄存器结构定义。地址偏移量:0x0D2，初值:0x5F，宽度:8
 寄存器说明: LCO3/4/5/7 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo7_ocp_auto_stop : 2;  /* bit[0-1]: LDO7在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo5_ocp_auto_stop : 2;  /* bit[2-3]: LDO5在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo4_ocp_auto_stop : 2;  /* bit[4-5]: LDO4在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo3_ocp_auto_stop : 2;  /* bit[6-7]: LDO3在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO3_7_OCP_CTRL_UNION;
#endif
#define PMIC_LDO3_7_OCP_CTRL_ldo7_ocp_auto_stop_START  (0)
#define PMIC_LDO3_7_OCP_CTRL_ldo7_ocp_auto_stop_END    (1)
#define PMIC_LDO3_7_OCP_CTRL_ldo5_ocp_auto_stop_START  (2)
#define PMIC_LDO3_7_OCP_CTRL_ldo5_ocp_auto_stop_END    (3)
#define PMIC_LDO3_7_OCP_CTRL_ldo4_ocp_auto_stop_START  (4)
#define PMIC_LDO3_7_OCP_CTRL_ldo4_ocp_auto_stop_END    (5)
#define PMIC_LDO3_7_OCP_CTRL_ldo3_ocp_auto_stop_START  (6)
#define PMIC_LDO3_7_OCP_CTRL_ldo3_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO8_11_OCP_CTRL_UNION
 结构说明  : LDO8_11_OCP_CTRL 寄存器结构定义。地址偏移量:0x0D3，初值:0x5D，宽度:8
 寄存器说明: LDO8/9/10/11 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo11_ocp_auto_stop : 2;  /* bit[0-1]: LDO11在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo10_ocp_auto_stop : 2;  /* bit[2-3]: LDO10在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo9_ocp_auto_stop  : 2;  /* bit[4-5]: LDO9在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo8_ocp_auto_stop  : 2;  /* bit[6-7]: LDO8在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO8_11_OCP_CTRL_UNION;
#endif
#define PMIC_LDO8_11_OCP_CTRL_ldo11_ocp_auto_stop_START  (0)
#define PMIC_LDO8_11_OCP_CTRL_ldo11_ocp_auto_stop_END    (1)
#define PMIC_LDO8_11_OCP_CTRL_ldo10_ocp_auto_stop_START  (2)
#define PMIC_LDO8_11_OCP_CTRL_ldo10_ocp_auto_stop_END    (3)
#define PMIC_LDO8_11_OCP_CTRL_ldo9_ocp_auto_stop_START   (4)
#define PMIC_LDO8_11_OCP_CTRL_ldo9_ocp_auto_stop_END     (5)
#define PMIC_LDO8_11_OCP_CTRL_ldo8_ocp_auto_stop_START   (6)
#define PMIC_LDO8_11_OCP_CTRL_ldo8_ocp_auto_stop_END     (7)


/*****************************************************************************
 结构名    : PMIC_LDO12_15_OCP_CTRL_UNION
 结构说明  : LDO12_15_OCP_CTRL 寄存器结构定义。地址偏移量:0x0D4，初值:0x55，宽度:8
 寄存器说明: LDO12/13/14/15 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo15_ocp_auto_stop : 2;  /* bit[0-1]: LDO15在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo14_ocp_auto_stop : 2;  /* bit[2-3]: LDO14在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo13_ocp_auto_stop : 2;  /* bit[4-5]: LDO13在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo12_ocp_auto_stop : 2;  /* bit[6-7]: LDO12在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO12_15_OCP_CTRL_UNION;
#endif
#define PMIC_LDO12_15_OCP_CTRL_ldo15_ocp_auto_stop_START  (0)
#define PMIC_LDO12_15_OCP_CTRL_ldo15_ocp_auto_stop_END    (1)
#define PMIC_LDO12_15_OCP_CTRL_ldo14_ocp_auto_stop_START  (2)
#define PMIC_LDO12_15_OCP_CTRL_ldo14_ocp_auto_stop_END    (3)
#define PMIC_LDO12_15_OCP_CTRL_ldo13_ocp_auto_stop_START  (4)
#define PMIC_LDO12_15_OCP_CTRL_ldo13_ocp_auto_stop_END    (5)
#define PMIC_LDO12_15_OCP_CTRL_ldo12_ocp_auto_stop_START  (6)
#define PMIC_LDO12_15_OCP_CTRL_ldo12_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO16_20_OCP_CTRL_UNION
 结构说明  : LDO16_20_OCP_CTRL 寄存器结构定义。地址偏移量:0x0D5，初值:0x55，宽度:8
 寄存器说明: LDO16/17/19/20 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo20_ocp_auto_stop : 2;  /* bit[0-1]: LDO20在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo19_ocp_auto_stop : 2;  /* bit[2-3]: LDO19在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo17_ocp_auto_stop : 2;  /* bit[4-5]: LDO17在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo16_ocp_auto_stop : 2;  /* bit[6-7]: LDO16在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO16_20_OCP_CTRL_UNION;
#endif
#define PMIC_LDO16_20_OCP_CTRL_ldo20_ocp_auto_stop_START  (0)
#define PMIC_LDO16_20_OCP_CTRL_ldo20_ocp_auto_stop_END    (1)
#define PMIC_LDO16_20_OCP_CTRL_ldo19_ocp_auto_stop_START  (2)
#define PMIC_LDO16_20_OCP_CTRL_ldo19_ocp_auto_stop_END    (3)
#define PMIC_LDO16_20_OCP_CTRL_ldo17_ocp_auto_stop_START  (4)
#define PMIC_LDO16_20_OCP_CTRL_ldo17_ocp_auto_stop_END    (5)
#define PMIC_LDO16_20_OCP_CTRL_ldo16_ocp_auto_stop_START  (6)
#define PMIC_LDO16_20_OCP_CTRL_ldo16_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO21_24_OCP_CTRL_UNION
 结构说明  : LDO21_24_OCP_CTRL 寄存器结构定义。地址偏移量:0x0D6，初值:0x5D，宽度:8
 寄存器说明: LDO21/22/23/24 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo24_ocp_auto_stop : 2;  /* bit[0-1]: LDO24在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo23_ocp_auto_stop : 2;  /* bit[2-3]: LDO23在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo22_ocp_auto_stop : 2;  /* bit[4-5]: LDO22在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo21_ocp_auto_stop : 2;  /* bit[6-7]: LDO21在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO21_24_OCP_CTRL_UNION;
#endif
#define PMIC_LDO21_24_OCP_CTRL_ldo24_ocp_auto_stop_START  (0)
#define PMIC_LDO21_24_OCP_CTRL_ldo24_ocp_auto_stop_END    (1)
#define PMIC_LDO21_24_OCP_CTRL_ldo23_ocp_auto_stop_START  (2)
#define PMIC_LDO21_24_OCP_CTRL_ldo23_ocp_auto_stop_END    (3)
#define PMIC_LDO21_24_OCP_CTRL_ldo22_ocp_auto_stop_START  (4)
#define PMIC_LDO21_24_OCP_CTRL_ldo22_ocp_auto_stop_END    (5)
#define PMIC_LDO21_24_OCP_CTRL_ldo21_ocp_auto_stop_START  (6)
#define PMIC_LDO21_24_OCP_CTRL_ldo21_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO25_28_OCP_CTRL_UNION
 结构说明  : LDO25_28_OCP_CTRL 寄存器结构定义。地址偏移量:0x0D7，初值:0x7D，宽度:8
 寄存器说明: LDO25/26/27/28 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo28_ocp_auto_stop : 2;  /* bit[0-1]: LDO28在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo27_ocp_auto_stop : 2;  /* bit[2-3]: LDO27在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo26_ocp_auto_stop : 2;  /* bit[4-5]: LDO26在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo25_ocp_auto_stop : 2;  /* bit[6-7]: LDO25在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO25_28_OCP_CTRL_UNION;
#endif
#define PMIC_LDO25_28_OCP_CTRL_ldo28_ocp_auto_stop_START  (0)
#define PMIC_LDO25_28_OCP_CTRL_ldo28_ocp_auto_stop_END    (1)
#define PMIC_LDO25_28_OCP_CTRL_ldo27_ocp_auto_stop_START  (2)
#define PMIC_LDO25_28_OCP_CTRL_ldo27_ocp_auto_stop_END    (3)
#define PMIC_LDO25_28_OCP_CTRL_ldo26_ocp_auto_stop_START  (4)
#define PMIC_LDO25_28_OCP_CTRL_ldo26_ocp_auto_stop_END    (5)
#define PMIC_LDO25_28_OCP_CTRL_ldo25_ocp_auto_stop_START  (6)
#define PMIC_LDO25_28_OCP_CTRL_ldo25_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO29_32_OCP_CTRL_UNION
 结构说明  : LDO29_32_OCP_CTRL 寄存器结构定义。地址偏移量:0x0D8，初值:0x75，宽度:8
 寄存器说明: LDO29/30/31/32 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo32_ocp_auto_stop : 2;  /* bit[0-1]: LDO32在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：不支持。 */
        unsigned char  ldo31_ocp_auto_stop : 2;  /* bit[2-3]: LDO31在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo30_ocp_auto_stop : 2;  /* bit[4-5]: LDO30在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo29_ocp_auto_stop : 2;  /* bit[6-7]: LDO29在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO29_32_OCP_CTRL_UNION;
#endif
#define PMIC_LDO29_32_OCP_CTRL_ldo32_ocp_auto_stop_START  (0)
#define PMIC_LDO29_32_OCP_CTRL_ldo32_ocp_auto_stop_END    (1)
#define PMIC_LDO29_32_OCP_CTRL_ldo31_ocp_auto_stop_START  (2)
#define PMIC_LDO29_32_OCP_CTRL_ldo31_ocp_auto_stop_END    (3)
#define PMIC_LDO29_32_OCP_CTRL_ldo30_ocp_auto_stop_START  (4)
#define PMIC_LDO29_32_OCP_CTRL_ldo30_ocp_auto_stop_END    (5)
#define PMIC_LDO29_32_OCP_CTRL_ldo29_ocp_auto_stop_START  (6)
#define PMIC_LDO29_32_OCP_CTRL_ldo29_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLASS_BUCK0_SCP_CTRL_UNION
 结构说明  : CLASS_BUCK0_SCP_CTRL 寄存器结构定义。地址偏移量:0x0D9，初值:0x0F，宽度:8
 寄存器说明: CLASS/BUCK0 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_scp_auto_stop  : 2;  /* bit[0-1]: BUCK0在发生SCP时是否自动关闭功能选择位。
                                                               X0： 仅上报中断，不自动关闭，PMU不下电；
                                                               01： 上报中断，自动关闭，PMU不下电；
                                                               11：上报中断，自动关闭，PMU下电。 */
        unsigned char  classd_ocp_auto_stop : 2;  /* bit[2-3]: class在发生OCP时是否自动关闭功能选择位。
                                                               X0： 仅上报中断，不自动关闭，PMU不下电；
                                                               01： 上报中断，自动关闭，PMU不下电；
                                                               11：上报中断，自动关闭，PMU下电。 */
        unsigned char  reserved             : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_CLASS_BUCK0_SCP_CTRL_UNION;
#endif
#define PMIC_CLASS_BUCK0_SCP_CTRL_buck0_scp_auto_stop_START   (0)
#define PMIC_CLASS_BUCK0_SCP_CTRL_buck0_scp_auto_stop_END     (1)
#define PMIC_CLASS_BUCK0_SCP_CTRL_classd_ocp_auto_stop_START  (2)
#define PMIC_CLASS_BUCK0_SCP_CTRL_classd_ocp_auto_stop_END    (3)


/*****************************************************************************
 结构名    : PMIC_BUCK1_4_SCP_CTRL_UNION
 结构说明  : BUCK1_4_SCP_CTRL 寄存器结构定义。地址偏移量:0x0DA，初值:0xFF，宽度:8
 寄存器说明: BUCK1/2/3/4 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_scp_auto_stop : 2;  /* bit[0-1]: BUCK4在发生SCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck3_scp_auto_stop : 2;  /* bit[2-3]: BUCK3在发生SCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck2_scp_auto_stop : 2;  /* bit[4-5]: BUCK2在发生SCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck1_scp_auto_stop : 2;  /* bit[6-7]: BUCK1在发生SCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_BUCK1_4_SCP_CTRL_UNION;
#endif
#define PMIC_BUCK1_4_SCP_CTRL_buck4_scp_auto_stop_START  (0)
#define PMIC_BUCK1_4_SCP_CTRL_buck4_scp_auto_stop_END    (1)
#define PMIC_BUCK1_4_SCP_CTRL_buck3_scp_auto_stop_START  (2)
#define PMIC_BUCK1_4_SCP_CTRL_buck3_scp_auto_stop_END    (3)
#define PMIC_BUCK1_4_SCP_CTRL_buck2_scp_auto_stop_START  (4)
#define PMIC_BUCK1_4_SCP_CTRL_buck2_scp_auto_stop_END    (5)
#define PMIC_BUCK1_4_SCP_CTRL_buck1_scp_auto_stop_START  (6)
#define PMIC_BUCK1_4_SCP_CTRL_buck1_scp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_SYS_CTRL0_UNION
 结构说明  : SYS_CTRL0 寄存器结构定义。地址偏移量:0x0DB，初值:0x00，宽度:8
 寄存器说明: 系统控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vsys_pwroff_abs_pd_mask : 1;  /* bit[0]  : vsys小于2.3v时是否自动关机控制位。
                                                                  0：自动关机(低于2.3v时间超过35us以上才能保证关机成功)；
                                                                  1：不自动关机。 */
        unsigned char  vsys_pwroff_deb_pd_mask : 1;  /* bit[1]  : vsys小于2.6v时是否自动关机控制位。
                                                                  0：自动关机；
                                                                  1：不自动关机。 */
        unsigned char  thsd_otmp140_pd_mask    : 1;  /* bit[2]  : 温度超过140度时是否自动关机控制位。
                                                                  0：自动关机；
                                                                  1：不自动关机。 */
        unsigned char  vsys_ov_pd_mask         : 1;  /* bit[3]  : vsys过压时是否自动关机控制位。
                                                                  0：自动关机；
                                                                  1：不自动关机。 */
        unsigned char  reserved                : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_SYS_CTRL0_UNION;
#endif
#define PMIC_SYS_CTRL0_vsys_pwroff_abs_pd_mask_START  (0)
#define PMIC_SYS_CTRL0_vsys_pwroff_abs_pd_mask_END    (0)
#define PMIC_SYS_CTRL0_vsys_pwroff_deb_pd_mask_START  (1)
#define PMIC_SYS_CTRL0_vsys_pwroff_deb_pd_mask_END    (1)
#define PMIC_SYS_CTRL0_thsd_otmp140_pd_mask_START     (2)
#define PMIC_SYS_CTRL0_thsd_otmp140_pd_mask_END       (2)
#define PMIC_SYS_CTRL0_vsys_ov_pd_mask_START          (3)
#define PMIC_SYS_CTRL0_vsys_ov_pd_mask_END            (3)


/*****************************************************************************
 结构名    : PMIC_SYS_CTRL1_UNION
 结构说明  : SYS_CTRL1 寄存器结构定义。地址偏移量:0x0DC，初值:0x00，宽度:8
 寄存器说明: 系统控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_smpl_open_en  : 1;  /* bit[0]  : SMPL功能使能位。
                                                           0：不支持电池掉出自重启；
                                                           1：支持电池掉出自重启。 */
        unsigned char  np_smpl_time_sel : 2;  /* bit[1-2]: 电池掉出再插入间隔重启时间选择。
                                                           00：0.5s；
                                                           01：1s；
                                                           10：1.5s；
                                                           11：2s。 */
        unsigned char  reserved_0       : 1;  /* bit[3]  : 保留。 */
        unsigned char  np_pwron_8s_sel  : 1;  /* bit[4]  : 开机状态下按下pwron_n长达8s关机或者重启选择。
                                                           0：长按键重启；
                                                           1：长按键关机。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_SYS_CTRL1_UNION;
#endif
#define PMIC_SYS_CTRL1_np_smpl_open_en_START   (0)
#define PMIC_SYS_CTRL1_np_smpl_open_en_END     (0)
#define PMIC_SYS_CTRL1_np_smpl_time_sel_START  (1)
#define PMIC_SYS_CTRL1_np_smpl_time_sel_END    (2)
#define PMIC_SYS_CTRL1_np_pwron_8s_sel_START   (4)
#define PMIC_SYS_CTRL1_np_pwron_8s_sel_END     (4)


/*****************************************************************************
 结构名    : PMIC_COUL_ECO_MASK_UNION
 结构说明  : COUL_ECO_MASK 寄存器结构定义。地址偏移量:0x0DD，初值:0x07，宽度:8
 寄存器说明: 库仑计ECO使能控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  coul_codec_clk_en_mask : 1;  /* bit[0]  : CODEC_CLK_EN控制库仑计进入ECO模式屏蔽位。
                                                                 0：不屏蔽；
                                                                 1：屏蔽。 */
        unsigned char  coul_wifi_clk_en_mask  : 1;  /* bit[1]  : WIFI_BT_CLK_EN控制库仑计进入ECO模式屏蔽位。
                                                                 0：不屏蔽；
                                                                 1：屏蔽。 */
        unsigned char  coul_sys_clk_en_mask   : 1;  /* bit[2]  : SYS_CLK_EN控制库仑计进入ECO模式屏蔽位。
                                                                 0：不屏蔽；
                                                                 1：屏蔽。 */
        unsigned char  reserved               : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_COUL_ECO_MASK_UNION;
#endif
#define PMIC_COUL_ECO_MASK_coul_codec_clk_en_mask_START  (0)
#define PMIC_COUL_ECO_MASK_coul_codec_clk_en_mask_END    (0)
#define PMIC_COUL_ECO_MASK_coul_wifi_clk_en_mask_START   (1)
#define PMIC_COUL_ECO_MASK_coul_wifi_clk_en_mask_END     (1)
#define PMIC_COUL_ECO_MASK_coul_sys_clk_en_mask_START    (2)
#define PMIC_COUL_ECO_MASK_coul_sys_clk_en_mask_END      (2)


/*****************************************************************************
 结构名    : PMIC_SIM_CTRL_UNION
 结构说明  : SIM_CTRL 寄存器结构定义。地址偏移量:0x0DE，初值:0x00，宽度:8
 寄存器说明: SIM控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sim0_hpd_r_pd_en : 1;  /* bit[0]: 发生sim0_hpd上升沿中断时是否关闭LDO11控制位。
                                                         0：不关闭LDO11；
                                                         1：关闭LDO11。 */
        unsigned char  sim0_hpd_f_pd_en : 1;  /* bit[1]: 发生sim0_hpd下降沿中断时是否关闭LDO11控制位。
                                                         0：不关闭LDO11；
                                                         1：关闭LDO11。 */
        unsigned char  sim0_hpd_h_pd_en : 1;  /* bit[2]: 发生sim0_hpd高电平中断时是否关闭LDO11控制位。
                                                         0：不关闭LDO11；
                                                         1：关闭LDO11。 */
        unsigned char  sim0_hpd_l_pd_en : 1;  /* bit[3]: 发生sim0_hpd低电平中断时是否关闭LDO11控制位。
                                                         0：不关闭LDO11；
                                                         1：关闭LDO11。 */
        unsigned char  sim1_hpd_r_pd_en : 1;  /* bit[4]: 发生sim1_hpd上升沿中断时是否关闭LDO12控制位。
                                                         0：不关闭LDO12；
                                                         1：关闭LDO12。 */
        unsigned char  sim1_hpd_f_pd_en : 1;  /* bit[5]: 发生sim1_hpd下降沿中断时是否关闭LDO12控制位。
                                                         0：不关闭LDO12；
                                                         1：关闭LDO12。 */
        unsigned char  sim1_hpd_h_pd_en : 1;  /* bit[6]: 发生sim1_hpd高电平中断时是否关闭LDO12控制位。
                                                         0：不关闭LDO12；
                                                         1：关闭LDO12。 */
        unsigned char  sim1_hpd_l_pd_en : 1;  /* bit[7]: 发生sim1_hpd低电平中断时是否关闭LDO12控制位。
                                                         0：不关闭LDO12；
                                                         1：关闭LDO12。 */
    } reg;
} PMIC_SIM_CTRL_UNION;
#endif
#define PMIC_SIM_CTRL_sim0_hpd_r_pd_en_START  (0)
#define PMIC_SIM_CTRL_sim0_hpd_r_pd_en_END    (0)
#define PMIC_SIM_CTRL_sim0_hpd_f_pd_en_START  (1)
#define PMIC_SIM_CTRL_sim0_hpd_f_pd_en_END    (1)
#define PMIC_SIM_CTRL_sim0_hpd_h_pd_en_START  (2)
#define PMIC_SIM_CTRL_sim0_hpd_h_pd_en_END    (2)
#define PMIC_SIM_CTRL_sim0_hpd_l_pd_en_START  (3)
#define PMIC_SIM_CTRL_sim0_hpd_l_pd_en_END    (3)
#define PMIC_SIM_CTRL_sim1_hpd_r_pd_en_START  (4)
#define PMIC_SIM_CTRL_sim1_hpd_r_pd_en_END    (4)
#define PMIC_SIM_CTRL_sim1_hpd_f_pd_en_START  (5)
#define PMIC_SIM_CTRL_sim1_hpd_f_pd_en_END    (5)
#define PMIC_SIM_CTRL_sim1_hpd_h_pd_en_START  (6)
#define PMIC_SIM_CTRL_sim1_hpd_h_pd_en_END    (6)
#define PMIC_SIM_CTRL_sim1_hpd_l_pd_en_START  (7)
#define PMIC_SIM_CTRL_sim1_hpd_l_pd_en_END    (7)


/*****************************************************************************
 结构名    : PMIC_SIM_DEB_CTRL_UNION
 结构说明  : SIM_DEB_CTRL 寄存器结构定义。地址偏移量:0x0DF，初值:0x27，宽度:8
 寄存器说明: SIM滤波控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sim_hpd_deb_sel : 5;  /* bit[0-4]: sim_hpd上下沿防抖（实际产生边沿中断的时间在这个基础上再加90us）。
                                                          0x0 ： 120us；0x1 ：180us；
                                                          0x2 ：240us；0x3 ： 300us；
                                                          0x4 ： 360us；0x5 ： 420us；
                                                          0x6 ： 480us；0x7 ： 540us；
                                                          0x8 ： 600us；0x9 ： 740us；
                                                          0xa ： 1ms；0xb ： 1.25ms；
                                                          0xc ： 1.5ms；0xd ： 1.75ms；
                                                          0xe ： 2ms；0xf ： 2.25ms；
                                                          0x10： 2.5ms；0x11： 2.75ms；
                                                          0x12： 3ms；0x13： 4ms；
                                                          0x14： 5ms；0x15： 6ms；
                                                          0x16： 7ms；0x17： 8ms；
                                                          0x18： 9ms；0x19： 10ms；
                                                          0x1a： 11ms；0x1b： 12ms；
                                                          0x1c： 13ms；0x1d： 14ms；
                                                          0x1e： 15ms；0x1f： 16ms。
                                                          （0x0-0x8会有60us左右的偏差，0x9-0x12会有250us左右的偏差，0x13-0x1f会有2ms左右的偏差） */
        unsigned char  sim_del_sel     : 3;  /* bit[5-7]: SIM0/1_HPD产生中断到自动关闭电源延迟时间选择。
                                                          000：60us；
                                                          001：120us；
                                                          010：180us；
                                                          011：240us；
                                                          100：360us；
                                                          101：480us；
                                                          110：540us；
                                                          111：600us。 */
    } reg;
} PMIC_SIM_DEB_CTRL_UNION;
#endif
#define PMIC_SIM_DEB_CTRL_sim_hpd_deb_sel_START  (0)
#define PMIC_SIM_DEB_CTRL_sim_hpd_deb_sel_END    (4)
#define PMIC_SIM_DEB_CTRL_sim_del_sel_START      (5)
#define PMIC_SIM_DEB_CTRL_sim_del_sel_END        (7)


/*****************************************************************************
 结构名    : PMIC_AUX_IBIAS_CFG_UNION
 结构说明  : AUX_IBIAS_CFG 寄存器结构定义。地址偏移量:0x0E0，初值:0x0A，宽度:8
 寄存器说明: DAC IBIAS配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  aux_offset_cfg : 2;  /* bit[0-1]: AUXDAC OFFSET调节。
                                                         00：+10mV；
                                                         01：0mV；
                                                         10：0mV；
                                                         11：-10mV。 */
        unsigned char  aux_ibias_cfg  : 2;  /* bit[2-3]: AUXDAC偏置电流调节。
                                                         00：2.5uA；
                                                         01：5.0uA；
                                                         10：5.0uA；
                                                         11：7.5uA。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_AUX_IBIAS_CFG_UNION;
#endif
#define PMIC_AUX_IBIAS_CFG_aux_offset_cfg_START  (0)
#define PMIC_AUX_IBIAS_CFG_aux_offset_cfg_END    (1)
#define PMIC_AUX_IBIAS_CFG_aux_ibias_cfg_START   (2)
#define PMIC_AUX_IBIAS_CFG_aux_ibias_cfg_END     (3)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_0_UNION
 结构说明  : IRQ_MASK_0 寄存器结构定义。地址偏移量:0x0E1，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK0控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_0 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：按键按下中断屏蔽；
                                                     bit[6]：按键释放中断屏蔽；
                                                     bit[5]：按键1s中断屏蔽；
                                                     bit[4]：按键6s中断屏蔽；
                                                     bit[3]：闹钟中断屏蔽；
                                                     bit[2]：vbus拔出中断屏蔽；
                                                     bit[1]：vbus插入中断屏蔽；
                                                     bit[0]：por中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_0_UNION;
#endif
#define PMIC_IRQ_MASK_0_irq_mask_0_START  (0)
#define PMIC_IRQ_MASK_0_irq_mask_0_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_1_UNION
 结构说明  : IRQ_MASK_1 寄存器结构定义。地址偏移量:0x0E2，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK1控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_1 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：过温125°中断屏蔽；
                                                     bit[6]：过温140°中断屏蔽；
                                                     bit[5]：去抖欠压关机中断屏蔽；
                                                     bit[4]：绝对欠压关机中断屏蔽；
                                                     bit[3]：欠压报警中断屏蔽；
                                                     bit[2]：过压报警中断屏蔽；
                                                     bit[1]：库仑计中断总屏蔽；
                                                     bit[0]：OCP中断总屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_1_UNION;
#endif
#define PMIC_IRQ_MASK_1_irq_mask_1_START  (0)
#define PMIC_IRQ_MASK_1_irq_mask_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_2_UNION
 结构说明  : IRQ_MASK_2 寄存器结构定义。地址偏移量:0x0E3，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK2控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_2 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7：1]：保留；
                                                     bit[0]：热复位中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_2_UNION;
#endif
#define PMIC_IRQ_MASK_2_irq_mask_2_START  (0)
#define PMIC_IRQ_MASK_2_irq_mask_2_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_3_UNION
 结构说明  : IRQ_MASK_3 寄存器结构定义。地址偏移量:0x0E4，初值:0xCC，宽度:8
 寄存器说明: IRQ_MASK3控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_3 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：sim_hpd1低电平中断屏蔽；
                                                     bit[6]：sim_hpd1高电平中断屏蔽；
                                                     bit[5]：sim_hpd1下降沿中断屏蔽；
                                                     bit[4]：sim_hpd1上升沿中断屏蔽；
                                                     bit[3]：sim_hpd0低电平中断屏蔽；
                                                     bit[2]：sim_hpd0高电平中断屏蔽；
                                                     bit[1]：sim_hpd0下降沿中断屏蔽；
                                                     bit[0]：sim_hpd0上升沿中断屏蔽；
                                                     bit[7]、bit[6]、bit[3]、bit[2]默认屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_3_UNION;
#endif
#define PMIC_IRQ_MASK_3_irq_mask_3_START  (0)
#define PMIC_IRQ_MASK_3_irq_mask_3_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_4_UNION
 结构说明  : IRQ_MASK_4 寄存器结构定义。地址偏移量:0x0E5，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK4控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_4 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：BUCK0输出过载中断屏蔽；
                                                     bit[6]：BUCK1输出过载中断屏蔽；
                                                     bit[5]：BUCK2输出过载中断屏蔽；
                                                     bit[4]：BUCK3输出过载中断屏蔽；
                                                     bit[3]：BUCK4输出过载中断屏蔽；
                                                     bit[2]：LDO0_2输出过载中断屏蔽；
                                                     bit[1]：LDO1输出过载中断屏蔽；
                                                     bit[0]：LDO2输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_4_UNION;
#endif
#define PMIC_IRQ_MASK_4_irq_mask_4_START  (0)
#define PMIC_IRQ_MASK_4_irq_mask_4_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_5_UNION
 结构说明  : IRQ_MASK_5 寄存器结构定义。地址偏移量:0x0E6，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK5控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_5 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：LDO3输出过载中断屏蔽；
                                                     bit[6]：LDO4输出过载中断屏蔽；
                                                     bit[5]：LDO5输出过载中断屏蔽；
                                                     bit[4]：LDO7输出过载中断屏蔽；
                                                     bit[3]：LDO8输出过载中断屏蔽；
                                                     bit[2]：LDO9输出过载中断屏蔽；
                                                     bit[1]：LDO10输出过载中断屏蔽；
                                                     bit[0]：LDO11输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_5_UNION;
#endif
#define PMIC_IRQ_MASK_5_irq_mask_5_START  (0)
#define PMIC_IRQ_MASK_5_irq_mask_5_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_6_UNION
 结构说明  : IRQ_MASK_6 寄存器结构定义。地址偏移量:0x0E7，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK6控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_6 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：LDO12输出过载中断屏蔽；
                                                     bit[6]：LDO13输出过载中断屏蔽；
                                                     bit[5]：LDO14输出过载中断屏蔽；
                                                     bit[4]：LDO15输出过载中断屏蔽；
                                                     bit[3]：LDO16输出过载中断屏蔽；
                                                     bit[2]：LDO17输出过载中断屏蔽；
                                                     bit[1]：LDO19输出过载中断屏蔽；
                                                     bit[0]：LDO20输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_6_UNION;
#endif
#define PMIC_IRQ_MASK_6_irq_mask_6_START  (0)
#define PMIC_IRQ_MASK_6_irq_mask_6_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_7_UNION
 结构说明  : IRQ_MASK_7 寄存器结构定义。地址偏移量:0x0E8，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK7控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_7 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：LDO21输出过载中断屏蔽；
                                                     bit[6]：LDO22输出过载中断屏蔽；
                                                     bit[5]：LDO23输出过载中断屏蔽；
                                                     bit[4]：LDO24输出过载中断屏蔽；
                                                     bit[3]：LDO25输出过载中断屏蔽；
                                                     bit[2]：LDO26输出过载中断屏蔽；
                                                     bit[1]：LDO27输出过载中断屏蔽；
                                                     bit[0]：LDO28输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_7_UNION;
#endif
#define PMIC_IRQ_MASK_7_irq_mask_7_START  (0)
#define PMIC_IRQ_MASK_7_irq_mask_7_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_8_UNION
 结构说明  : IRQ_MASK_8 寄存器结构定义。地址偏移量:0x0E9，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK8控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_8 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：LDO29输出过载中断屏蔽；
                                                     bit[6]：LDO30输出过载中断屏蔽；
                                                     bit[5]：LDO31输出过载中断屏蔽；
                                                     bit[4]：LDO32输出过载中断屏蔽；
                                                     bit[3：1]：保留；
                                                     bit[0]：class输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_8_UNION;
#endif
#define PMIC_IRQ_MASK_8_irq_mask_8_START  (0)
#define PMIC_IRQ_MASK_8_irq_mask_8_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_9_UNION
 结构说明  : IRQ_MASK_9 寄存器结构定义。地址偏移量:0x0EA，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK9控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_9 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7：5]：保留；
                                                     bit[4]：BUCK0输出短路中断屏蔽；
                                                     bit[3]：BUCK1输出短路中断屏蔽；
                                                     bit[2]：BUCK2输出短路中断屏蔽；
                                                     bit[1]：BUCK3输出短路中断屏蔽；
                                                     bit[0]：BUCK4输出短路中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_9_UNION;
#endif
#define PMIC_IRQ_MASK_9_irq_mask_9_START  (0)
#define PMIC_IRQ_MASK_9_irq_mask_9_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP0_0_UNION
 结构说明  : OTP0_0 寄存器结构定义。地址偏移量:0x0EB，初值:0x00，宽度:8
 寄存器说明: OTP0回读寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob0 : 8;  /* bit[0-7]: OTP0回读值bit[7:0]。 */
    } reg;
} PMIC_OTP0_0_UNION;
#endif
#define PMIC_OTP0_0_otp0_pdob0_START  (0)
#define PMIC_OTP0_0_otp0_pdob0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP0_1_UNION
 结构说明  : OTP0_1 寄存器结构定义。地址偏移量:0x0EC，初值:0x00，宽度:8
 寄存器说明: OTP0回读寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob1 : 8;  /* bit[0-7]: OTP0回读值bit[15:8]。 */
    } reg;
} PMIC_OTP0_1_UNION;
#endif
#define PMIC_OTP0_1_otp0_pdob1_START  (0)
#define PMIC_OTP0_1_otp0_pdob1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP0_2_UNION
 结构说明  : OTP0_2 寄存器结构定义。地址偏移量:0x0ED，初值:0x00，宽度:8
 寄存器说明: OTP0回读寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob2 : 8;  /* bit[0-7]: OTP0回读值bit[23:16]。 */
    } reg;
} PMIC_OTP0_2_UNION;
#endif
#define PMIC_OTP0_2_otp0_pdob2_START  (0)
#define PMIC_OTP0_2_otp0_pdob2_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP0_3_UNION
 结构说明  : OTP0_3 寄存器结构定义。地址偏移量:0x0EE，初值:0x00，宽度:8
 寄存器说明: OTP0回读寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob3 : 8;  /* bit[0-7]: OTP0回读值bit[31:24]。 */
    } reg;
} PMIC_OTP0_3_UNION;
#endif
#define PMIC_OTP0_3_otp0_pdob3_START  (0)
#define PMIC_OTP0_3_otp0_pdob3_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP0_CTRL_0_UNION
 结构说明  : OTP0_CTRL_0 寄存器结构定义。地址偏移量:0x0EF，初值:0x00，宽度:8
 寄存器说明: OTP0控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pwe_int   : 1;  /* bit[0]  : OTP0写控制信号。
                                                         0：拉低otp_pwe，结束写操作；
                                                         1：拉高otp_pwe，发起写操作。
                                                         需保证otp_pwe的高电平持续时间满足otp器件的要求。 */
        unsigned char  otp0_pwe_pulse : 1;  /* bit[1]  : OTP0写脉冲控制。
                                                         0：不发起脉冲；
                                                         1：发起一个310us的高电平脉冲。 */
        unsigned char  otp0_por_int   : 1;  /* bit[2]  : OTP0读控制信号。
                                                         0：拉低otp_por，结束读操作；
                                                         1：拉高otp_por，发起读操作。
                                                         需保证otp_por的高电平持续时间满足otp器件的要求。 */
        unsigned char  otp0_por_pulse : 1;  /* bit[3]  : OTP0初始化控制信号。
                                                         0： 不发起脉冲；
                                                         1：发起一个30us的por高电平脉冲。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_OTP0_CTRL_0_UNION;
#endif
#define PMIC_OTP0_CTRL_0_otp0_pwe_int_START    (0)
#define PMIC_OTP0_CTRL_0_otp0_pwe_int_END      (0)
#define PMIC_OTP0_CTRL_0_otp0_pwe_pulse_START  (1)
#define PMIC_OTP0_CTRL_0_otp0_pwe_pulse_END    (1)
#define PMIC_OTP0_CTRL_0_otp0_por_int_START    (2)
#define PMIC_OTP0_CTRL_0_otp0_por_int_END      (2)
#define PMIC_OTP0_CTRL_0_otp0_por_pulse_START  (3)
#define PMIC_OTP0_CTRL_0_otp0_por_pulse_END    (3)


/*****************************************************************************
 结构名    : PMIC_OTP0_CTRL_1_UNION
 结构说明  : OTP0_CTRL_1 寄存器结构定义。地址偏移量:0x0F0，初值:0x00，宽度:8
 寄存器说明: OTP0控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pa     : 2;  /* bit[0-1]: OTP0的地址信号。
                                                      00：选择otp0器件的bit[7:0]进行读/写操作；
                                                      01：选择otp0器件的bit[15:8]进行读/写操作；
                                                      10：选择otp0器件的bit[23:16]进行读/写操作；
                                                      11：选择otp0器件的bit[31:24]进行读/写操作。 */
        unsigned char  otp0_ptm    : 2;  /* bit[2-3]: OTP0测试模式使能信号。
                                                      00：用户模式；
                                                      01：margin-2读模式；
                                                      10：margin-1读模式；
                                                      11：未定义。 */
        unsigned char  otp01_pprog : 1;  /* bit[4]  : OTP01编程模式使能信号。
                                                      0：关闭otp编程；
                                                      1：使能otp编程。 */
        unsigned char  reserved    : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_OTP0_CTRL_1_UNION;
#endif
#define PMIC_OTP0_CTRL_1_otp0_pa_START      (0)
#define PMIC_OTP0_CTRL_1_otp0_pa_END        (1)
#define PMIC_OTP0_CTRL_1_otp0_ptm_START     (2)
#define PMIC_OTP0_CTRL_1_otp0_ptm_END       (3)
#define PMIC_OTP0_CTRL_1_otp01_pprog_START  (4)
#define PMIC_OTP0_CTRL_1_otp01_pprog_END    (4)


/*****************************************************************************
 结构名    : PMIC_OTP0_WDATA_UNION
 结构说明  : OTP0_WDATA 寄存器结构定义。地址偏移量:0x0F1，初值:0x00，宽度:8
 寄存器说明: OTP0写操作数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdin : 8;  /* bit[0-7]: OTP0的输入值寄存器。 */
    } reg;
} PMIC_OTP0_WDATA_UNION;
#endif
#define PMIC_OTP0_WDATA_otp0_pdin_START  (0)
#define PMIC_OTP0_WDATA_otp0_pdin_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP0_0_W_UNION
 结构说明  : OTP0_0_W 寄存器结构定义。地址偏移量:0x0F2，初值:0x00，宽度:8
 寄存器说明: OTP0或操作寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob0_w : 8;  /* bit[0-7]: 与OTP0_0相或后送给模拟。 */
    } reg;
} PMIC_OTP0_0_W_UNION;
#endif
#define PMIC_OTP0_0_W_otp0_pdob0_w_START  (0)
#define PMIC_OTP0_0_W_otp0_pdob0_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP0_1_W_UNION
 结构说明  : OTP0_1_W 寄存器结构定义。地址偏移量:0x0F3，初值:0x00，宽度:8
 寄存器说明: OTP0或操作寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob1_w : 8;  /* bit[0-7]: 与OTP0_1相或后送给模拟。 */
    } reg;
} PMIC_OTP0_1_W_UNION;
#endif
#define PMIC_OTP0_1_W_otp0_pdob1_w_START  (0)
#define PMIC_OTP0_1_W_otp0_pdob1_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP0_2_W_UNION
 结构说明  : OTP0_2_W 寄存器结构定义。地址偏移量:0x0F4，初值:0x00，宽度:8
 寄存器说明: OTP0或操作寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob2_w : 8;  /* bit[0-7]: 与OTP0_2相或后送给模拟。 */
    } reg;
} PMIC_OTP0_2_W_UNION;
#endif
#define PMIC_OTP0_2_W_otp0_pdob2_w_START  (0)
#define PMIC_OTP0_2_W_otp0_pdob2_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP0_3_W_UNION
 结构说明  : OTP0_3_W 寄存器结构定义。地址偏移量:0x0F5，初值:0x00，宽度:8
 寄存器说明: OTP0或操作寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pdob3_w : 8;  /* bit[0-7]: 与OTP0_3相或后送给模拟。 */
    } reg;
} PMIC_OTP0_3_W_UNION;
#endif
#define PMIC_OTP0_3_W_otp0_pdob3_w_START  (0)
#define PMIC_OTP0_3_W_otp0_pdob3_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP1_0_UNION
 结构说明  : OTP1_0 寄存器结构定义。地址偏移量:0x0F6，初值:0x00，宽度:8
 寄存器说明: OTP1回读寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob0 : 8;  /* bit[0-7]: OTP1回读值bit[7:0]。 */
    } reg;
} PMIC_OTP1_0_UNION;
#endif
#define PMIC_OTP1_0_otp1_pdob0_START  (0)
#define PMIC_OTP1_0_otp1_pdob0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP1_1_UNION
 结构说明  : OTP1_1 寄存器结构定义。地址偏移量:0x0F7，初值:0x00，宽度:8
 寄存器说明: OTP1回读寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob1 : 8;  /* bit[0-7]: OTP1回读值bit[15:8]。 */
    } reg;
} PMIC_OTP1_1_UNION;
#endif
#define PMIC_OTP1_1_otp1_pdob1_START  (0)
#define PMIC_OTP1_1_otp1_pdob1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP1_2_UNION
 结构说明  : OTP1_2 寄存器结构定义。地址偏移量:0x0F8，初值:0x00，宽度:8
 寄存器说明: OTP1回读寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob2 : 8;  /* bit[0-7]: OTP1回读值bit[23:16]。 */
    } reg;
} PMIC_OTP1_2_UNION;
#endif
#define PMIC_OTP1_2_otp1_pdob2_START  (0)
#define PMIC_OTP1_2_otp1_pdob2_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP1_3_UNION
 结构说明  : OTP1_3 寄存器结构定义。地址偏移量:0x0F9，初值:0x00，宽度:8
 寄存器说明: OTP1回读寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob3 : 8;  /* bit[0-7]: OTP1回读值bit[31:24]。 */
    } reg;
} PMIC_OTP1_3_UNION;
#endif
#define PMIC_OTP1_3_otp1_pdob3_START  (0)
#define PMIC_OTP1_3_otp1_pdob3_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP1_CTRL_0_UNION
 结构说明  : OTP1_CTRL_0 寄存器结构定义。地址偏移量:0x0FA，初值:0x00，宽度:8
 寄存器说明: OTP1控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pwe_int   : 1;  /* bit[0]  : OTP1写控制信号。
                                                         0：拉低otp_pwe，结束写操作；
                                                         1：拉高otp_pwe，发起写操作。
                                                         需保证otp_pwe的高电平持续时间满足otp器件的要求。 */
        unsigned char  otp1_pwe_pulse : 1;  /* bit[1]  : OTP1写脉冲控制。
                                                         0：不发起脉冲；
                                                         1：发起一个310us的高电平脉冲。 */
        unsigned char  otp1_por_int   : 1;  /* bit[2]  : OTP1读控制信号。
                                                         0：拉低otp_por，结束读操作；
                                                         1：拉高otp_por，发起读操作。
                                                         需保证otp_por的高电平持续时间满足otp器件的要求。 */
        unsigned char  otp1_por_pulse : 1;  /* bit[3]  : OTP1初始化控制信号。
                                                         0： 不发起脉冲；
                                                         1：发起一个30us的por高电平脉冲。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_OTP1_CTRL_0_UNION;
#endif
#define PMIC_OTP1_CTRL_0_otp1_pwe_int_START    (0)
#define PMIC_OTP1_CTRL_0_otp1_pwe_int_END      (0)
#define PMIC_OTP1_CTRL_0_otp1_pwe_pulse_START  (1)
#define PMIC_OTP1_CTRL_0_otp1_pwe_pulse_END    (1)
#define PMIC_OTP1_CTRL_0_otp1_por_int_START    (2)
#define PMIC_OTP1_CTRL_0_otp1_por_int_END      (2)
#define PMIC_OTP1_CTRL_0_otp1_por_pulse_START  (3)
#define PMIC_OTP1_CTRL_0_otp1_por_pulse_END    (3)


/*****************************************************************************
 结构名    : PMIC_OTP1_CTRL_1_UNION
 结构说明  : OTP1_CTRL_1 寄存器结构定义。地址偏移量:0x0FB，初值:0x00，宽度:8
 寄存器说明: OTP1控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pa  : 2;  /* bit[0-1]: OTP1的地址信号。
                                                   00：选择otp1器件的bit[7：0]进行读/写操作；
                                                   01：选择otp1器件的bit[15：8]进行读/写操作；
                                                   10：选择otp1器件的bit[23：16]进行读/写操作；
                                                   11：选择otp1器件的bit[31：24]进行读/写操作。 */
        unsigned char  otp1_ptm : 2;  /* bit[2-3]: OTP1测试模式使能信号。
                                                   00：用户模式；
                                                   01：margin-2读模式；
                                                   10：margin-1读模式；
                                                   11：未定义。 */
        unsigned char  reserved : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_OTP1_CTRL_1_UNION;
#endif
#define PMIC_OTP1_CTRL_1_otp1_pa_START   (0)
#define PMIC_OTP1_CTRL_1_otp1_pa_END     (1)
#define PMIC_OTP1_CTRL_1_otp1_ptm_START  (2)
#define PMIC_OTP1_CTRL_1_otp1_ptm_END    (3)


/*****************************************************************************
 结构名    : PMIC_OTP1_WDATA_UNION
 结构说明  : OTP1_WDATA 寄存器结构定义。地址偏移量:0x0FC，初值:0x00，宽度:8
 寄存器说明: OTP0写操作数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdin : 8;  /* bit[0-7]: OTP1的输入值寄存器。 */
    } reg;
} PMIC_OTP1_WDATA_UNION;
#endif
#define PMIC_OTP1_WDATA_otp1_pdin_START  (0)
#define PMIC_OTP1_WDATA_otp1_pdin_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP1_0_W_UNION
 结构说明  : OTP1_0_W 寄存器结构定义。地址偏移量:0x0FD，初值:0x00，宽度:8
 寄存器说明: OTP1或操作寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob0_w : 8;  /* bit[0-7]: 与OTP1_0相或后送给模拟。 */
    } reg;
} PMIC_OTP1_0_W_UNION;
#endif
#define PMIC_OTP1_0_W_otp1_pdob0_w_START  (0)
#define PMIC_OTP1_0_W_otp1_pdob0_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP1_1_W_UNION
 结构说明  : OTP1_1_W 寄存器结构定义。地址偏移量:0x0FE，初值:0x00，宽度:8
 寄存器说明: OTP1或操作寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob1_w : 8;  /* bit[0-7]: 与OTP1_1相或后送给模拟。 */
    } reg;
} PMIC_OTP1_1_W_UNION;
#endif
#define PMIC_OTP1_1_W_otp1_pdob1_w_START  (0)
#define PMIC_OTP1_1_W_otp1_pdob1_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP1_2_W_UNION
 结构说明  : OTP1_2_W 寄存器结构定义。地址偏移量:0x0FF，初值:0x00，宽度:8
 寄存器说明: OTP1或操作寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob2_w : 8;  /* bit[0-7]: 与OTP1_2相或后送给模拟。 */
    } reg;
} PMIC_OTP1_2_W_UNION;
#endif
#define PMIC_OTP1_2_W_otp1_pdob2_w_START  (0)
#define PMIC_OTP1_2_W_otp1_pdob2_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP1_3_W_UNION
 结构说明  : OTP1_3_W 寄存器结构定义。地址偏移量:0x100，初值:0x00，宽度:8
 寄存器说明: OTP1或操作寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp1_pdob3_w : 8;  /* bit[0-7]: 与OTP1_3相或后送给模拟。 */
    } reg;
} PMIC_OTP1_3_W_UNION;
#endif
#define PMIC_OTP1_3_W_otp1_pdob3_w_START  (0)
#define PMIC_OTP1_3_W_otp1_pdob3_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG0_UNION
 结构说明  : HRST_REG0 寄存器结构定义。地址偏移量:0x101，初值:0x00，宽度:8
 寄存器说明: RESETIN_N复位信息寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hrst_reg0 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG0_UNION;
#endif
#define PMIC_HRST_REG0_hrst_reg0_START  (0)
#define PMIC_HRST_REG0_hrst_reg0_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG1_UNION
 结构说明  : HRST_REG1 寄存器结构定义。地址偏移量:0x102，初值:0x00，宽度:8
 寄存器说明: RESETIN_N复位信息寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hrst_reg1 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG1_UNION;
#endif
#define PMIC_HRST_REG1_hrst_reg1_START  (0)
#define PMIC_HRST_REG1_hrst_reg1_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG2_UNION
 结构说明  : HRST_REG2 寄存器结构定义。地址偏移量:0x103，初值:0x00，宽度:8
 寄存器说明: RESETIN_N复位信息寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hrst_reg2 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG2_UNION;
#endif
#define PMIC_HRST_REG2_hrst_reg2_START  (0)
#define PMIC_HRST_REG2_hrst_reg2_END    (7)


/*****************************************************************************
 结构名    : PMIC_SOFT_RST_REG_UNION
 结构说明  : SOFT_RST_REG 寄存器结构定义。地址偏移量:0x104，初值:0x00，宽度:8
 寄存器说明: SOFT复位信息寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_rst_cfg : 8;  /* bit[0-7]: AUSTIN不使用，仅供V7R5使用（配置为8'h11让rtc模块处于复位状态以降低功耗，写8'h22解除rtc模块的复位）。
                                                       11：rtc复位拉低；
                                                       22：rtc复位拉高；
                                                       55：关闭整个PMU；
                                                       DD：重新产生一次上电过程；
                                                       EE：产生一次热复位；
                                                       其他无效，只用于数字内部debug，不开放配置。 */
    } reg;
} PMIC_SOFT_RST_REG_UNION;
#endif
#define PMIC_SOFT_RST_REG_soft_rst_cfg_START  (0)
#define PMIC_SOFT_RST_REG_soft_rst_cfg_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL0_UNION
 结构说明  : CLK_TOP_CTRL0 寄存器结构定义。地址偏移量:0x105，初值:0x00，宽度:8
 寄存器说明: 时钟控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_reg_otp     : 2;  /* bit[0-1]: XO core驱动电流配置。
                                                         00：增加1mA驱动能力；
                                                         01：增加2mA驱动能力；
                                                         10：增加3mA驱动能力；
                                                         11：增加4mA驱动能力。 */
        unsigned char  xo_ldo_curr    : 2;  /* bit[2-3]: XO_LDO偏置电流档位选择。
                                                         00：选择5uA档位；
                                                         01：选择2.5uA档位；
                                                         10：选择2.5uA档位；
                                                         11：选择1.7uA档位。 */
        unsigned char  xo_ldo_res     : 3;  /* bit[4-6]: 内部LDO的反馈电阻。
                                                         000：1.8V；
                                                         001：1.5V；
                                                         010：1.6V；
                                                         011：1.7V；
                                                         100：1.9V；
                                                         101: 2.0V；
                                                         110: 2.1V；
                                                         其他：不可配置。 */
        unsigned char  xo_ldo_reg_res : 1;  /* bit[7]  : 内部反馈电阻控制选择。
                                                         0：表示内部反馈电阻由OTP控制；
                                                         1：表示内部反馈电阻由Trim电阻控制。 */
    } reg;
} PMIC_CLK_TOP_CTRL0_UNION;
#endif
#define PMIC_CLK_TOP_CTRL0_xo_reg_otp_START      (0)
#define PMIC_CLK_TOP_CTRL0_xo_reg_otp_END        (1)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_curr_START     (2)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_curr_END       (3)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_res_START      (4)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_res_END        (6)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_reg_res_START  (7)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_reg_res_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL1_UNION
 结构说明  : CLK_TOP_CTRL1 寄存器结构定义。地址偏移量:0x106，初值:0x50，宽度:8
 寄存器说明: 时钟控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_xo_c1fix : 8;  /* bit[0-7]: 时钟频率精度trim寄存器1（和CLK_TOP_CTRL2[np_xo_c2fix]一起使用）。 */
    } reg;
} PMIC_CLK_TOP_CTRL1_UNION;
#endif
#define PMIC_CLK_TOP_CTRL1_np_xo_c1fix_START  (0)
#define PMIC_CLK_TOP_CTRL1_np_xo_c1fix_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL2_UNION
 结构说明  : CLK_TOP_CTRL2 寄存器结构定义。地址偏移量:0x107，初值:0x05，宽度:8
 寄存器说明: 时钟控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_xo_c2fix      : 4;  /* bit[0-3]: 时钟频率精度trim寄存器2（和CLK_TOP_CTRL1[np_xo_c1fix]一起使用）。 */
        unsigned char  xo_buff_reg_curr : 1;  /* bit[4]  : 时钟内部第一级buffer类型选择。
                                                           0：正弦波通过反向器整形为方波；
                                                           1：正弦波通过施密特触发器整形为方波。 */
        unsigned char  xo_otp_reg_sel1  : 1;  /* bit[5]  : XO core input buffer的电流配置选择。 
                                                           0：OTP控制；
                                                           1：寄存器控制。 */
        unsigned char  xo_otp_reg_sel0  : 1;  /* bit[6]  : XO core的电流配置选择。
                                                           0：OTP控制 ；
                                                           1：寄存器控制。 */
        unsigned char  xo_c1_cap        : 1;  /* bit[7]  : 不开放寄存器，模拟测试使用。 */
    } reg;
} PMIC_CLK_TOP_CTRL2_UNION;
#endif
#define PMIC_CLK_TOP_CTRL2_np_xo_c2fix_START       (0)
#define PMIC_CLK_TOP_CTRL2_np_xo_c2fix_END         (3)
#define PMIC_CLK_TOP_CTRL2_xo_buff_reg_curr_START  (4)
#define PMIC_CLK_TOP_CTRL2_xo_buff_reg_curr_END    (4)
#define PMIC_CLK_TOP_CTRL2_xo_otp_reg_sel1_START   (5)
#define PMIC_CLK_TOP_CTRL2_xo_otp_reg_sel1_END     (5)
#define PMIC_CLK_TOP_CTRL2_xo_otp_reg_sel0_START   (6)
#define PMIC_CLK_TOP_CTRL2_xo_otp_reg_sel0_END     (6)
#define PMIC_CLK_TOP_CTRL2_xo_c1_cap_START         (7)
#define PMIC_CLK_TOP_CTRL2_xo_c1_cap_END           (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL3_UNION
 结构说明  : CLK_TOP_CTRL3 寄存器结构定义。地址偏移量:0x108，初值:0x05，宽度:8
 寄存器说明: 时钟控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_freq_rf1  : 2;  /* bit[0-1]: RF1时钟buffer驱动能力控制；
                                                       00：表示驱动为3pF//100K；
                                                       01：表示驱动为10pF//100K；
                                                       10：表示驱动为16pF//100K；
                                                       11：表示驱动为25pF//100K。 */
        unsigned char  xo_freq_rf0  : 2;  /* bit[2-3]: RF0时钟buffer驱动能力控制；
                                                       00：表示驱动为3pF//100K；
                                                       01：表示驱动为10pF//100K；
                                                       10：表示驱动为16pF//100K；
                                                       11：表示驱动为25pF//100K。 */
        unsigned char  xo_sys_phase : 1;  /* bit[4]  : ABB时钟与RF0/RF1时钟相位控制。
                                                       0：ABB时钟与RF0/RF1时钟反相；
                                                       1：ABB时钟与RF0/RF1时钟同相。 */
        unsigned char  xo_tri_cap   : 3;  /* bit[5-7]: 时钟输出级三角波驱动负载调节。
                                                       000：默认0.8pF负载；
                                                       001：在默认基础上增加1.2pF负载；
                                                       010：在默认基础上增加0.8pF负载；
                                                       011：在默认基础上增加2pF负载；
                                                       100：在默认基础上增加1.6pF负载；
                                                       101：在默认基础上增加2.8pF负载；
                                                       110：在默认基础上增加2.4pF负载；
                                                       111：在默认基础上增加3.6pF负载。 */
    } reg;
} PMIC_CLK_TOP_CTRL3_UNION;
#endif
#define PMIC_CLK_TOP_CTRL3_xo_freq_rf1_START   (0)
#define PMIC_CLK_TOP_CTRL3_xo_freq_rf1_END     (1)
#define PMIC_CLK_TOP_CTRL3_xo_freq_rf0_START   (2)
#define PMIC_CLK_TOP_CTRL3_xo_freq_rf0_END     (3)
#define PMIC_CLK_TOP_CTRL3_xo_sys_phase_START  (4)
#define PMIC_CLK_TOP_CTRL3_xo_sys_phase_END    (4)
#define PMIC_CLK_TOP_CTRL3_xo_tri_cap_START    (5)
#define PMIC_CLK_TOP_CTRL3_xo_tri_cap_END      (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL4_UNION
 结构说明  : CLK_TOP_CTRL4 寄存器结构定义。地址偏移量:0x109，初值:0xD5，宽度:8
 寄存器说明: 时钟控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_freq_codec  : 2;  /* bit[0-1]: CODEC时钟buffer驱动能力控制；
                                                         00：表示驱动为7.5pF；
                                                         01：表示驱动为12.75pF；
                                                         10：表示驱动为3.75pF；
                                                         11：表示驱动为7.5pF。 */
        unsigned char  xo_freq_sys    : 2;  /* bit[2-3]: SYS时钟buffer驱动能力控制；
                                                         00：表示驱动为7.5pF；
                                                         01：表示驱动为12.75pF；
                                                         10：表示驱动为3.75pF；
                                                         11：表示驱动为7.5pF。 */
        unsigned char  xo_freq_wifibt : 2;  /* bit[4-5]: WIFIBT时钟buffer驱动能力控制；
                                                         00：表示驱动为3pF//100K；
                                                         01：表示驱动为10pF//100K；
                                                         10：表示驱动为16pF//100K；
                                                         11：表示驱动为25pF//100K。 */
        unsigned char  xo_freq_abb    : 2;  /* bit[6-7]: ABB时钟buffer驱动能力控制；
                                                         00：表示驱动为3pF//100K；
                                                         01：表示驱动为10pF//100K；
                                                         10：表示驱动为16pF//100K；
                                                         11：表示驱动为25pF//100K。 */
    } reg;
} PMIC_CLK_TOP_CTRL4_UNION;
#endif
#define PMIC_CLK_TOP_CTRL4_xo_freq_codec_START   (0)
#define PMIC_CLK_TOP_CTRL4_xo_freq_codec_END     (1)
#define PMIC_CLK_TOP_CTRL4_xo_freq_sys_START     (2)
#define PMIC_CLK_TOP_CTRL4_xo_freq_sys_END       (3)
#define PMIC_CLK_TOP_CTRL4_xo_freq_wifibt_START  (4)
#define PMIC_CLK_TOP_CTRL4_xo_freq_wifibt_END    (5)
#define PMIC_CLK_TOP_CTRL4_xo_freq_abb_START     (6)
#define PMIC_CLK_TOP_CTRL4_xo_freq_abb_END       (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL5_UNION
 结构说明  : CLK_TOP_CTRL5 寄存器结构定义。地址偏移量:0x10A，初值:0x0A，宽度:8
 寄存器说明: 时钟控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_codec_en : 1;  /* bit[0]  : clk_buff_codec使能信号（CODEC buf）。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  reg_xo_sys_en   : 1;  /* bit[1]  : clk_buff_sys使能信号（SYS buf）。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  reg_xo_wifi_en  : 1;  /* bit[2]  : clk_buff_wifibt使能信号（WIFIBT buf）。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  reg_xo_abb_en   : 1;  /* bit[3]  : clk_buff_abb使能信号（ABB buf）。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  xo_rf1_en       : 1;  /* bit[4]  : clk_buff_rf1使能信号（RF1 buf）。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  xo_rf0_en       : 1;  /* bit[5]  : clk_buff_rf0使能信号（RF0 buf）。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  reserved        : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_CLK_TOP_CTRL5_UNION;
#endif
#define PMIC_CLK_TOP_CTRL5_reg_xo_codec_en_START  (0)
#define PMIC_CLK_TOP_CTRL5_reg_xo_codec_en_END    (0)
#define PMIC_CLK_TOP_CTRL5_reg_xo_sys_en_START    (1)
#define PMIC_CLK_TOP_CTRL5_reg_xo_sys_en_END      (1)
#define PMIC_CLK_TOP_CTRL5_reg_xo_wifi_en_START   (2)
#define PMIC_CLK_TOP_CTRL5_reg_xo_wifi_en_END     (2)
#define PMIC_CLK_TOP_CTRL5_reg_xo_abb_en_START    (3)
#define PMIC_CLK_TOP_CTRL5_reg_xo_abb_en_END      (3)
#define PMIC_CLK_TOP_CTRL5_xo_rf1_en_START        (4)
#define PMIC_CLK_TOP_CTRL5_xo_rf1_en_END          (4)
#define PMIC_CLK_TOP_CTRL5_xo_rf0_en_START        (5)
#define PMIC_CLK_TOP_CTRL5_xo_rf0_en_END          (5)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL6_UNION
 结构说明  : CLK_TOP_CTRL6 寄存器结构定义。地址偏移量:0x10B，初值:0x07，宽度:8
 寄存器说明: 时钟控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_eco_in_n   : 1;  /* bit[0]  : 时钟进入低功耗使能信号。
                                                         0：拉低；
                                                         1：拉高。
                                                         注：寄存器需要将寄存器CORE_LDO_ECO_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  reg_xo_ldo_en  : 1;  /* bit[1]  : xo_ldo_en使能信号。
                                                         0：拉低；
                                                         1：拉高。
                                                         注：寄存器需要将寄存器CORE_LDO_ECO_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  reg_xo_core_en : 1;  /* bit[2]  : xo_core_en的使能信号。
                                                         0： 拉低；
                                                         1：拉高。
                                                         在DCXO和伪TCXO模式下（PDOB<26>=0），xo_core_en默认值为1
                                                         在TCXO模式下（PDOB<26>=1），xo_core_en默认为0
                                                         注：寄存器需要将寄存器CORE_LDO_ECO_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  reg_rc_debug   : 1;  /* bit[3]  : RC时钟debug使能信号。
                                                         0：正常使用；
                                                         1：将256K时钟引出。
                                                         注：寄存器需要将寄存器CORE_LDO_ECO_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_CLK_TOP_CTRL6_UNION;
#endif
#define PMIC_CLK_TOP_CTRL6_reg_eco_in_n_START    (0)
#define PMIC_CLK_TOP_CTRL6_reg_eco_in_n_END      (0)
#define PMIC_CLK_TOP_CTRL6_reg_xo_ldo_en_START   (1)
#define PMIC_CLK_TOP_CTRL6_reg_xo_ldo_en_END     (1)
#define PMIC_CLK_TOP_CTRL6_reg_xo_core_en_START  (2)
#define PMIC_CLK_TOP_CTRL6_reg_xo_core_en_END    (2)
#define PMIC_CLK_TOP_CTRL6_reg_rc_debug_START    (3)
#define PMIC_CLK_TOP_CTRL6_reg_rc_debug_END      (3)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL7_UNION
 结构说明  : CLK_TOP_CTRL7 寄存器结构定义。地址偏移量:0x10C，初值:0x02，宽度:8
 寄存器说明: 时钟控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_xo_wifibt_dig : 1;  /* bit[0]  : clk_wifibt buffer选择信号，模拟内部将该信号与1bit OTP(RF0/RF1/WIFI共用OTP)信号共同控制是否数字BUF。
                                                           0：模拟BUF(正弦波)；
                                                           1：数字BUF(方波)，
                                                           (OTP=1, np_xo_rf0_dig=1输出方波；任一bit为0输出正弦波)。 */
        unsigned char  np_xo_abb_dig    : 1;  /* bit[1]  : clk_abb buffer选择信号，模拟内部将该信号与1bit OTP(单独OTP)信号共同控制是否数字BUF。
                                                           0：模拟BUF(正弦波)；
                                                           1：数字BUF(方波)。
                                                           (OTP=1, np_xo_rf0_dig=1输出方波；任一bit为0输出正弦波)。 */
        unsigned char  np_xo_rf1_dig    : 1;  /* bit[2]  : clk_rf1 buffer选择信号，模拟内部将该信号与1bit OTP信(RF0/RF1/WIFI共用OTP)号共同控制是否数字BUF。
                                                           0：模拟BUF(正弦波)；
                                                           1：数字BUF(方波)。
                                                           (OTP=1, np_xo_rf0_dig=1输出方波；任一bit为0输出正弦波)。 */
        unsigned char  np_xo_rf0_dig    : 1;  /* bit[3]  : clk_rf0 buffer选择信号，模拟内部将该信号与1bit OTP(RF0/RF1/WIFI共用OTP)信号共同控制是否数字BUF。
                                                           0：模拟BUF(正弦波)；
                                                           1：数字BUF(方波)。
                                                           (OTP=1, np_xo_rf0_dig=1输出方波；任一bit为0输出正弦波)。 */
        unsigned char  reserved         : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_CLK_TOP_CTRL7_UNION;
#endif
#define PMIC_CLK_TOP_CTRL7_np_xo_wifibt_dig_START  (0)
#define PMIC_CLK_TOP_CTRL7_np_xo_wifibt_dig_END    (0)
#define PMIC_CLK_TOP_CTRL7_np_xo_abb_dig_START     (1)
#define PMIC_CLK_TOP_CTRL7_np_xo_abb_dig_END       (1)
#define PMIC_CLK_TOP_CTRL7_np_xo_rf1_dig_START     (2)
#define PMIC_CLK_TOP_CTRL7_np_xo_rf1_dig_END       (2)
#define PMIC_CLK_TOP_CTRL7_np_xo_rf0_dig_START     (3)
#define PMIC_CLK_TOP_CTRL7_np_xo_rf0_dig_END       (3)


/*****************************************************************************
 结构名    : PMIC_CLK_256K_CTRL0_UNION
 结构说明  : CLK_256K_CTRL0 寄存器结构定义。地址偏移量:0x10D，初值:0x00，宽度:8
 寄存器说明: 256K RC控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_256k_en0 : 8;  /* bit[0-7]: RC256K关闭控制。
                                                       0x5A：关闭256K时钟（同时reg_256k_en1为0xF0）；
                                                       其他：开启。 */
    } reg;
} PMIC_CLK_256K_CTRL0_UNION;
#endif
#define PMIC_CLK_256K_CTRL0_reg_256k_en0_START  (0)
#define PMIC_CLK_256K_CTRL0_reg_256k_en0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_256K_CTRL1_UNION
 结构说明  : CLK_256K_CTRL1 寄存器结构定义。地址偏移量:0x10E，初值:0x00，宽度:8
 寄存器说明: 256K RC控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_256k_en1 : 8;  /* bit[0-7]: RC256K关闭控制。
                                                       0xF0：关闭256K时钟（同时reg_256k_en0为0x5A）；
                                                       其他：开启。 */
    } reg;
} PMIC_CLK_256K_CTRL1_UNION;
#endif
#define PMIC_CLK_256K_CTRL1_reg_256k_en1_START  (0)
#define PMIC_CLK_256K_CTRL1_reg_256k_en1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_RESERVE0_UNION
 结构说明  : CLK_TOP_RESERVE0 寄存器结构定义。地址偏移量:0x10F，初值:0x00，宽度:8
 寄存器说明: 时钟控制预留寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_reserve0 : 8;  /* bit[0-7]: xo预留寄存器。 */
    } reg;
} PMIC_CLK_TOP_RESERVE0_UNION;
#endif
#define PMIC_CLK_TOP_RESERVE0_xo_reserve0_START  (0)
#define PMIC_CLK_TOP_RESERVE0_xo_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_RESERVE1_UNION
 结构说明  : CLK_TOP_RESERVE1 寄存器结构定义。地址偏移量:0x110，初值:0x00，宽度:8
 寄存器说明: 时钟控制预留寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_reserve1 : 8;  /* bit[0-7]: xo预留寄存器。 */
    } reg;
} PMIC_CLK_TOP_RESERVE1_UNION;
#endif
#define PMIC_CLK_TOP_RESERVE1_xo_reserve1_START  (0)
#define PMIC_CLK_TOP_RESERVE1_xo_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_SYS_DEBUG0_UNION
 结构说明  : SYS_DEBUG0 寄存器结构定义。地址偏移量:0x111，初值:0x00，宽度:8
 寄存器说明: 数字系统debug预留寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_debug0 : 8;  /* bit[0-7]: 数字系统debug预留寄存器。 */
    } reg;
} PMIC_SYS_DEBUG0_UNION;
#endif
#define PMIC_SYS_DEBUG0_sys_debug0_START  (0)
#define PMIC_SYS_DEBUG0_sys_debug0_END    (7)


/*****************************************************************************
 结构名    : PMIC_SYS_DEBUG1_UNION
 结构说明  : SYS_DEBUG1 寄存器结构定义。地址偏移量:0x112，初值:0xFF，宽度:8
 寄存器说明: 数字系统debug预留寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_debug1 : 8;  /* bit[0-7]: 数字系统debug预留寄存器。 */
    } reg;
} PMIC_SYS_DEBUG1_UNION;
#endif
#define PMIC_SYS_DEBUG1_sys_debug1_START  (0)
#define PMIC_SYS_DEBUG1_sys_debug1_END    (7)


/*****************************************************************************
 结构名    : PMIC_DAC0_DIN_MSB_UNION
 结构说明  : DAC0_DIN_MSB 寄存器结构定义。地址偏移量:0x113，初值:0x00，宽度:8
 寄存器说明: DAC0 din高位映射寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac0_din_msb : 2;  /* bit[0-1]: dac0 din[9：8]映射寄存器。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_DAC0_DIN_MSB_UNION;
#endif
#define PMIC_DAC0_DIN_MSB_dac0_din_msb_START  (0)
#define PMIC_DAC0_DIN_MSB_dac0_din_msb_END    (1)


/*****************************************************************************
 结构名    : PMIC_DAC0_DIN_LSB_UNION
 结构说明  : DAC0_DIN_LSB 寄存器结构定义。地址偏移量:0x114，初值:0x00，宽度:8
 寄存器说明: DAC0 din低位映射寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac0_din_lsb : 8;  /* bit[0-7]: dac0 din[7:0]映射寄存器。 */
    } reg;
} PMIC_DAC0_DIN_LSB_UNION;
#endif
#define PMIC_DAC0_DIN_LSB_dac0_din_lsb_START  (0)
#define PMIC_DAC0_DIN_LSB_dac0_din_lsb_END    (7)


/*****************************************************************************
 结构名    : PMIC_DAC1_DIN_MSB_UNION
 结构说明  : DAC1_DIN_MSB 寄存器结构定义。地址偏移量:0x115，初值:0x00，宽度:8
 寄存器说明: DAC1 din高位映射寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac1_din_msb : 2;  /* bit[0-1]: dac1 din[9：8]映射寄存器。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_DAC1_DIN_MSB_UNION;
#endif
#define PMIC_DAC1_DIN_MSB_dac1_din_msb_START  (0)
#define PMIC_DAC1_DIN_MSB_dac1_din_msb_END    (1)


/*****************************************************************************
 结构名    : PMIC_DAC1_DIN_LSB_UNION
 结构说明  : DAC1_DIN_LSB 寄存器结构定义。地址偏移量:0x116，初值:0x00，宽度:8
 寄存器说明: DAC1 din低位映射寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac1_din_lsb : 8;  /* bit[0-7]: dac1 din[7:0]映射寄存器。 */
    } reg;
} PMIC_DAC1_DIN_LSB_UNION;
#endif
#define PMIC_DAC1_DIN_LSB_dac1_din_lsb_START  (0)
#define PMIC_DAC1_DIN_LSB_dac1_din_lsb_END    (7)


/*****************************************************************************
 结构名    : PMIC_CORE_LDO_ECO_LOCK_UNION
 结构说明  : CORE_LDO_ECO_LOCK 寄存器结构定义。地址偏移量:0x117，初值:0x00，宽度:8
 寄存器说明: xo_core_en,xo_ldo_en,eco_in_n寄存器写屏蔽控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  core_ldo_eco_lock : 8;  /* bit[0-7]: 为防止软件误写CLK_TOP_CTRL6，导致系统出错。只有当core_ldo_eco_lock写为8'h6C的时候，CLK_TOP_CTRL6寄存器才允许被一直写入。 */
    } reg;
} PMIC_CORE_LDO_ECO_LOCK_UNION;
#endif
#define PMIC_CORE_LDO_ECO_LOCK_core_ldo_eco_lock_START  (0)
#define PMIC_CORE_LDO_ECO_LOCK_core_ldo_eco_lock_END    (7)




/****************************************************************************
                     (2/5) PMU_IRQ
 ****************************************************************************/
/*****************************************************************************
 结构名    : PMIC_NP_OCP0_UNION
 结构说明  : NP_OCP0 寄存器结构定义。地址偏移量:0x11A，初值:0x00，宽度:8
 寄存器说明: BUKC0-4，LDO0-2 OCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo2   : 1;  /* bit[0]: LDO2输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpldo1   : 1;  /* bit[1]: LDO1输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpldo0_2 : 1;  /* bit[2]: LDO0_2输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpbuck4  : 1;  /* bit[3]: BUCK4输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpbuck3  : 1;  /* bit[4]: BUCK3输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpbuck2  : 1;  /* bit[5]: BUCK2输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpbuck1  : 1;  /* bit[6]: BUCK1输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpbuck0  : 1;  /* bit[7]: BUCK0输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
    } reg;
} PMIC_NP_OCP0_UNION;
#endif
#define PMIC_NP_OCP0_np_ocpldo2_START    (0)
#define PMIC_NP_OCP0_np_ocpldo2_END      (0)
#define PMIC_NP_OCP0_np_ocpldo1_START    (1)
#define PMIC_NP_OCP0_np_ocpldo1_END      (1)
#define PMIC_NP_OCP0_np_ocpldo0_2_START  (2)
#define PMIC_NP_OCP0_np_ocpldo0_2_END    (2)
#define PMIC_NP_OCP0_np_ocpbuck4_START   (3)
#define PMIC_NP_OCP0_np_ocpbuck4_END     (3)
#define PMIC_NP_OCP0_np_ocpbuck3_START   (4)
#define PMIC_NP_OCP0_np_ocpbuck3_END     (4)
#define PMIC_NP_OCP0_np_ocpbuck2_START   (5)
#define PMIC_NP_OCP0_np_ocpbuck2_END     (5)
#define PMIC_NP_OCP0_np_ocpbuck1_START   (6)
#define PMIC_NP_OCP0_np_ocpbuck1_END     (6)
#define PMIC_NP_OCP0_np_ocpbuck0_START   (7)
#define PMIC_NP_OCP0_np_ocpbuck0_END     (7)


/*****************************************************************************
 结构名    : PMIC_NP_OCP1_UNION
 结构说明  : NP_OCP1 寄存器结构定义。地址偏移量:0x11B，初值:0x00，宽度:8
 寄存器说明: LDO3-11 OCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo11 : 1;  /* bit[0]: LDO11输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo10 : 1;  /* bit[1]: LDO10输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo9  : 1;  /* bit[2]: LDO9输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo8  : 1;  /* bit[3]: LDO8输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo7  : 1;  /* bit[4]: LDO7输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo5  : 1;  /* bit[5]: LDO5输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo4  : 1;  /* bit[6]: LDO4输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo3  : 1;  /* bit[7]: LDO3输出过载事件记录寄存器。
                                                    0：无中断；
                                                    1：有中断。 */
    } reg;
} PMIC_NP_OCP1_UNION;
#endif
#define PMIC_NP_OCP1_np_ocpldo11_START  (0)
#define PMIC_NP_OCP1_np_ocpldo11_END    (0)
#define PMIC_NP_OCP1_np_ocpldo10_START  (1)
#define PMIC_NP_OCP1_np_ocpldo10_END    (1)
#define PMIC_NP_OCP1_np_ocpldo9_START   (2)
#define PMIC_NP_OCP1_np_ocpldo9_END     (2)
#define PMIC_NP_OCP1_np_ocpldo8_START   (3)
#define PMIC_NP_OCP1_np_ocpldo8_END     (3)
#define PMIC_NP_OCP1_np_ocpldo7_START   (4)
#define PMIC_NP_OCP1_np_ocpldo7_END     (4)
#define PMIC_NP_OCP1_np_ocpldo5_START   (5)
#define PMIC_NP_OCP1_np_ocpldo5_END     (5)
#define PMIC_NP_OCP1_np_ocpldo4_START   (6)
#define PMIC_NP_OCP1_np_ocpldo4_END     (6)
#define PMIC_NP_OCP1_np_ocpldo3_START   (7)
#define PMIC_NP_OCP1_np_ocpldo3_END     (7)


/*****************************************************************************
 结构名    : PMIC_NP_OCP2_UNION
 结构说明  : NP_OCP2 寄存器结构定义。地址偏移量:0x11C，初值:0x00，宽度:8
 寄存器说明: LDO12-20 OCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo20 : 1;  /* bit[0]: LDO20输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo19 : 1;  /* bit[1]: LDO19输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo17 : 1;  /* bit[2]: LDO17输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo16 : 1;  /* bit[3]: LDO16输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo15 : 1;  /* bit[4]: LDO15输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo14 : 1;  /* bit[5]: LDO14输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo13 : 1;  /* bit[6]: LDO13输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo12 : 1;  /* bit[7]: LDO12输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
    } reg;
} PMIC_NP_OCP2_UNION;
#endif
#define PMIC_NP_OCP2_np_ocpldo20_START  (0)
#define PMIC_NP_OCP2_np_ocpldo20_END    (0)
#define PMIC_NP_OCP2_np_ocpldo19_START  (1)
#define PMIC_NP_OCP2_np_ocpldo19_END    (1)
#define PMIC_NP_OCP2_np_ocpldo17_START  (2)
#define PMIC_NP_OCP2_np_ocpldo17_END    (2)
#define PMIC_NP_OCP2_np_ocpldo16_START  (3)
#define PMIC_NP_OCP2_np_ocpldo16_END    (3)
#define PMIC_NP_OCP2_np_ocpldo15_START  (4)
#define PMIC_NP_OCP2_np_ocpldo15_END    (4)
#define PMIC_NP_OCP2_np_ocpldo14_START  (5)
#define PMIC_NP_OCP2_np_ocpldo14_END    (5)
#define PMIC_NP_OCP2_np_ocpldo13_START  (6)
#define PMIC_NP_OCP2_np_ocpldo13_END    (6)
#define PMIC_NP_OCP2_np_ocpldo12_START  (7)
#define PMIC_NP_OCP2_np_ocpldo12_END    (7)


/*****************************************************************************
 结构名    : PMIC_NP_OCP3_UNION
 结构说明  : NP_OCP3 寄存器结构定义。地址偏移量:0x11D，初值:0x00，宽度:8
 寄存器说明: LDO21-28 OCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo28 : 1;  /* bit[0]: LDO28输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo27 : 1;  /* bit[1]: LDO27输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo26 : 1;  /* bit[2]: LDO26输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo25 : 1;  /* bit[3]: LDO25输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo24 : 1;  /* bit[4]: LDO24输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo23 : 1;  /* bit[5]: LDO23输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo22 : 1;  /* bit[6]: LDO22输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo21 : 1;  /* bit[7]: LDO21输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
    } reg;
} PMIC_NP_OCP3_UNION;
#endif
#define PMIC_NP_OCP3_np_ocpldo28_START  (0)
#define PMIC_NP_OCP3_np_ocpldo28_END    (0)
#define PMIC_NP_OCP3_np_ocpldo27_START  (1)
#define PMIC_NP_OCP3_np_ocpldo27_END    (1)
#define PMIC_NP_OCP3_np_ocpldo26_START  (2)
#define PMIC_NP_OCP3_np_ocpldo26_END    (2)
#define PMIC_NP_OCP3_np_ocpldo25_START  (3)
#define PMIC_NP_OCP3_np_ocpldo25_END    (3)
#define PMIC_NP_OCP3_np_ocpldo24_START  (4)
#define PMIC_NP_OCP3_np_ocpldo24_END    (4)
#define PMIC_NP_OCP3_np_ocpldo23_START  (5)
#define PMIC_NP_OCP3_np_ocpldo23_END    (5)
#define PMIC_NP_OCP3_np_ocpldo22_START  (6)
#define PMIC_NP_OCP3_np_ocpldo22_END    (6)
#define PMIC_NP_OCP3_np_ocpldo21_START  (7)
#define PMIC_NP_OCP3_np_ocpldo21_END    (7)


/*****************************************************************************
 结构名    : PMIC_NP_OCP4_UNION
 结构说明  : NP_OCP4 寄存器结构定义。地址偏移量:0x11E，初值:0x00，宽度:8
 寄存器说明: LDO29-32 CLASSD OCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_classd_ocp : 1;  /* bit[0]  : classd输出过载事件记录寄存器。
                                                        0：没有发生过该事件；
                                                        1：发生过该事件。 */
        unsigned char  reserved      : 3;  /* bit[1-3]: 保留。 */
        unsigned char  np_ocpldo32   : 1;  /* bit[4]  : LDO32输出过载事件记录寄存器。
                                                        0：没有发生过该事件；
                                                        1：发生过该事件。 */
        unsigned char  np_ocpldo31   : 1;  /* bit[5]  : LDO31输出过载事件记录寄存器。
                                                        0：没有发生过该事件；
                                                        1：发生过该事件。 */
        unsigned char  np_ocpldo30   : 1;  /* bit[6]  : LDO30输出过载事件记录寄存器。
                                                        0：没有发生过该事件；
                                                        1：发生过该事件。 */
        unsigned char  np_ocpldo29   : 1;  /* bit[7]  : LDO29输出过载事件记录寄存器。
                                                        0：没有发生过该事件；
                                                        1：发生过该事件。 */
    } reg;
} PMIC_NP_OCP4_UNION;
#endif
#define PMIC_NP_OCP4_np_classd_ocp_START  (0)
#define PMIC_NP_OCP4_np_classd_ocp_END    (0)
#define PMIC_NP_OCP4_np_ocpldo32_START    (4)
#define PMIC_NP_OCP4_np_ocpldo32_END      (4)
#define PMIC_NP_OCP4_np_ocpldo31_START    (5)
#define PMIC_NP_OCP4_np_ocpldo31_END      (5)
#define PMIC_NP_OCP4_np_ocpldo30_START    (6)
#define PMIC_NP_OCP4_np_ocpldo30_END      (6)
#define PMIC_NP_OCP4_np_ocpldo29_START    (7)
#define PMIC_NP_OCP4_np_ocpldo29_END      (7)


/*****************************************************************************
 结构名    : PMIC_NP_SCP_UNION
 结构说明  : NP_SCP 寄存器结构定义。地址偏移量:0x11F，初值:0x00，宽度:8
 寄存器说明: BUCK0-4 SCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_buck4_scp : 1;  /* bit[0]  : BUCK4输出短路事件记录寄存器。
                                                       0：没有发生过该事件；
                                                       1：发生过该事件。 */
        unsigned char  np_buck3_scp : 1;  /* bit[1]  : BUCK3输出短路事件记录寄存器。
                                                       0：没有发生过该事件；
                                                       1：发生过该事件。 */
        unsigned char  np_buck2_scp : 1;  /* bit[2]  : BUCK2输出短路事件记录寄存器。
                                                       0：没有发生过该事件；
                                                       1：发生过该事件。 */
        unsigned char  np_buck1_scp : 1;  /* bit[3]  : BUCK1输出短路事件记录寄存器。
                                                       0：没有发生过该事件；
                                                       1：发生过该事件。 */
        unsigned char  np_buck0_scp : 1;  /* bit[4]  : BUCK0输出短路事件记录寄存器。
                                                       0：没有发生过该事件；
                                                       1：发生过该事件。 */
        unsigned char  reserved     : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_NP_SCP_UNION;
#endif
#define PMIC_NP_SCP_np_buck4_scp_START  (0)
#define PMIC_NP_SCP_np_buck4_scp_END    (0)
#define PMIC_NP_SCP_np_buck3_scp_START  (1)
#define PMIC_NP_SCP_np_buck3_scp_END    (1)
#define PMIC_NP_SCP_np_buck2_scp_START  (2)
#define PMIC_NP_SCP_np_buck2_scp_END    (2)
#define PMIC_NP_SCP_np_buck1_scp_START  (3)
#define PMIC_NP_SCP_np_buck1_scp_END    (3)
#define PMIC_NP_SCP_np_buck0_scp_START  (4)
#define PMIC_NP_SCP_np_buck0_scp_END    (4)


/*****************************************************************************
 结构名    : PMIC_IRQ0_UNION
 结构说明  : IRQ0 寄存器结构定义。地址偏移量:0x120，初值:0x00，宽度:8
 寄存器说明: 中断寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  por_d45mr             : 1;  /* bit[0]: por事件中断（pwr_rst_n拉高后约45ms后上报）。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  vbus_det_insert_d20mr : 1;  /* bit[1]: 充电器插入中断(上升沿去抖20ms)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  vbus_det_insert_d20mf : 1;  /* bit[2]: 充电器拔出中断(下降沿去抖20ms)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  alarmon_r             : 1;  /* bit[3]: 闹钟中断。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  pwronn_d6sf           : 1;  /* bit[4]: 按键按下超过6s事件中断(下降沿去抖6s)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  pwronn_d1sf           : 1;  /* bit[5]: 按键按下超过1s事件中断(下降沿去抖1s)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  pwronn_d20mr          : 1;  /* bit[6]: 按键释放事件中断(上升沿去抖20ms)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  pwronn_d20mf          : 1;  /* bit[7]: 按键按下事件中断(下降沿去抖20ms)。
                                                              0：无中断；
                                                              1：有中断。 */
    } reg;
} PMIC_IRQ0_UNION;
#endif
#define PMIC_IRQ0_por_d45mr_START              (0)
#define PMIC_IRQ0_por_d45mr_END                (0)
#define PMIC_IRQ0_vbus_det_insert_d20mr_START  (1)
#define PMIC_IRQ0_vbus_det_insert_d20mr_END    (1)
#define PMIC_IRQ0_vbus_det_insert_d20mf_START  (2)
#define PMIC_IRQ0_vbus_det_insert_d20mf_END    (2)
#define PMIC_IRQ0_alarmon_r_START              (3)
#define PMIC_IRQ0_alarmon_r_END                (3)
#define PMIC_IRQ0_pwronn_d6sf_START            (4)
#define PMIC_IRQ0_pwronn_d6sf_END              (4)
#define PMIC_IRQ0_pwronn_d1sf_START            (5)
#define PMIC_IRQ0_pwronn_d1sf_END              (5)
#define PMIC_IRQ0_pwronn_d20mr_START           (6)
#define PMIC_IRQ0_pwronn_d20mr_END             (6)
#define PMIC_IRQ0_pwronn_d20mf_START           (7)
#define PMIC_IRQ0_pwronn_d20mf_END             (7)


/*****************************************************************************
 结构名    : PMIC_IRQ1_UNION
 结构说明  : IRQ1 寄存器结构定义。地址偏移量:0x121，初值:0x00，宽度:8
 寄存器说明: 中断寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocp_r                 : 1;  /* bit[0]: OCP事件中断。
                                                              0：无中断；
                                                              1：有中断。表示至少有一个BUCK或者LDO过载，CPU接到以后要去查看OCP中断寄存器看看是哪一个过载。 */
        unsigned char  coul_r                : 1;  /* bit[1]: 库仑计事件中断。
                                                              0：无中断；
                                                              1：有中断。PMU接到以后要去查看下面的库仑计中断寄存器确认是哪一个中断。 */
        unsigned char  vsys_ov_d200ur        : 1;  /* bit[2]: 过压事件中断(上升沿去抖200us)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  vsys_uv_d10mr         : 1;  /* bit[3]: 欠压告警事件中断(上升沿去抖10ms，时间可配)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  vsys_pwroff_abs_2d    : 1;  /* bit[4]: 绝对欠压关机事件中断（同步两拍）。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  vsys_pwroff_deb_d80mr : 1;  /* bit[5]: 去抖欠压关机事件中断(上升沿去抖80ms，时间可配)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  thsd_otmp140_d1mr     : 1;  /* bit[6]: 过温140度事件中断(上升沿去抖1ms)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  thsd_otmp125_d1mr     : 1;  /* bit[7]: 过温（芯片温度超过设定的报警温度）事件中断(上升沿去抖1ms)。
                                                              0：无中断；
                                                              1：有中断。 */
    } reg;
} PMIC_IRQ1_UNION;
#endif
#define PMIC_IRQ1_ocp_r_START                  (0)
#define PMIC_IRQ1_ocp_r_END                    (0)
#define PMIC_IRQ1_coul_r_START                 (1)
#define PMIC_IRQ1_coul_r_END                   (1)
#define PMIC_IRQ1_vsys_ov_d200ur_START         (2)
#define PMIC_IRQ1_vsys_ov_d200ur_END           (2)
#define PMIC_IRQ1_vsys_uv_d10mr_START          (3)
#define PMIC_IRQ1_vsys_uv_d10mr_END            (3)
#define PMIC_IRQ1_vsys_pwroff_abs_2d_START     (4)
#define PMIC_IRQ1_vsys_pwroff_abs_2d_END       (4)
#define PMIC_IRQ1_vsys_pwroff_deb_d80mr_START  (5)
#define PMIC_IRQ1_vsys_pwroff_deb_d80mr_END    (5)
#define PMIC_IRQ1_thsd_otmp140_d1mr_START      (6)
#define PMIC_IRQ1_thsd_otmp140_d1mr_END        (6)
#define PMIC_IRQ1_thsd_otmp125_d1mr_START      (7)
#define PMIC_IRQ1_thsd_otmp125_d1mr_END        (7)


/*****************************************************************************
 结构名    : PMIC_IRQ2_UNION
 结构说明  : IRQ2 寄存器结构定义。地址偏移量:0x122，初值:0x00，宽度:8
 寄存器说明: 中断寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hresetn_d90uf : 1;  /* bit[0]  : 热复位（发生过RSTIN_N复位）事件中断。
                                                        0：无中断；
                                                        1：有中断。 */
        unsigned char  reserved      : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_IRQ2_UNION;
#endif
#define PMIC_IRQ2_hresetn_d90uf_START  (0)
#define PMIC_IRQ2_hresetn_d90uf_END    (0)


/*****************************************************************************
 结构名    : PMIC_IRQ3_UNION
 结构说明  : IRQ3 寄存器结构定义。地址偏移量:0x123，初值:0x00，宽度:8
 寄存器说明: 中断寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sim0_hpd_r : 1;  /* bit[0]: sim0_hpd上升沿中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned char  sim0_hpd_f : 1;  /* bit[1]: sim0_hpd下降沿中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned char  sim0_hpd_h : 1;  /* bit[2]: sim0_hpd高电平中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned char  sim0_hpd_l : 1;  /* bit[3]: sim0_hpd低电平中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned char  sim1_hpd_r : 1;  /* bit[4]: sim1_hpd上升沿中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned char  sim1_hpd_f : 1;  /* bit[5]: sim1_hpd下降沿中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned char  sim1_hpd_h : 1;  /* bit[6]: sim1_hpd高电平中断。
                                                   0：无中断；
                                                   1：有中断。 */
        unsigned char  sim1_hpd_l : 1;  /* bit[7]: sim1_hpd低电平中断。
                                                   0：无中断；
                                                   1：有中断。 */
    } reg;
} PMIC_IRQ3_UNION;
#endif
#define PMIC_IRQ3_sim0_hpd_r_START  (0)
#define PMIC_IRQ3_sim0_hpd_r_END    (0)
#define PMIC_IRQ3_sim0_hpd_f_START  (1)
#define PMIC_IRQ3_sim0_hpd_f_END    (1)
#define PMIC_IRQ3_sim0_hpd_h_START  (2)
#define PMIC_IRQ3_sim0_hpd_h_END    (2)
#define PMIC_IRQ3_sim0_hpd_l_START  (3)
#define PMIC_IRQ3_sim0_hpd_l_END    (3)
#define PMIC_IRQ3_sim1_hpd_r_START  (4)
#define PMIC_IRQ3_sim1_hpd_r_END    (4)
#define PMIC_IRQ3_sim1_hpd_f_START  (5)
#define PMIC_IRQ3_sim1_hpd_f_END    (5)
#define PMIC_IRQ3_sim1_hpd_h_START  (6)
#define PMIC_IRQ3_sim1_hpd_h_END    (6)
#define PMIC_IRQ3_sim1_hpd_l_START  (7)
#define PMIC_IRQ3_sim1_hpd_l_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ0_UNION
 结构说明  : OCP_IRQ0 寄存器结构定义。地址偏移量:0x124，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo2   : 1;  /* bit[0]: LDO2输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpldo1   : 1;  /* bit[1]: LDO1输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpldo0_2 : 1;  /* bit[2]: LDO0_2输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpbuck4  : 1;  /* bit[3]: BUCK4输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpbuck3  : 1;  /* bit[4]: BUCK3输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpbuck2  : 1;  /* bit[5]: BUCK2输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpbuck1  : 1;  /* bit[6]: BUCK1输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpbuck0  : 1;  /* bit[7]: BUCK0输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
    } reg;
} PMIC_OCP_IRQ0_UNION;
#endif
#define PMIC_OCP_IRQ0_ocpldo2_START    (0)
#define PMIC_OCP_IRQ0_ocpldo2_END      (0)
#define PMIC_OCP_IRQ0_ocpldo1_START    (1)
#define PMIC_OCP_IRQ0_ocpldo1_END      (1)
#define PMIC_OCP_IRQ0_ocpldo0_2_START  (2)
#define PMIC_OCP_IRQ0_ocpldo0_2_END    (2)
#define PMIC_OCP_IRQ0_ocpbuck4_START   (3)
#define PMIC_OCP_IRQ0_ocpbuck4_END     (3)
#define PMIC_OCP_IRQ0_ocpbuck3_START   (4)
#define PMIC_OCP_IRQ0_ocpbuck3_END     (4)
#define PMIC_OCP_IRQ0_ocpbuck2_START   (5)
#define PMIC_OCP_IRQ0_ocpbuck2_END     (5)
#define PMIC_OCP_IRQ0_ocpbuck1_START   (6)
#define PMIC_OCP_IRQ0_ocpbuck1_END     (6)
#define PMIC_OCP_IRQ0_ocpbuck0_START   (7)
#define PMIC_OCP_IRQ0_ocpbuck0_END     (7)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ1_UNION
 结构说明  : OCP_IRQ1 寄存器结构定义。地址偏移量:0x125，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo11 : 1;  /* bit[0]: LDO11输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo10 : 1;  /* bit[1]: LDO10输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo9  : 1;  /* bit[2]: LDO9输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo8  : 1;  /* bit[3]: LDO8输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo7  : 1;  /* bit[4]: LDO7输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo5  : 1;  /* bit[5]: LDO5输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo4  : 1;  /* bit[6]: LDO4输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo3  : 1;  /* bit[7]: LDO3输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
    } reg;
} PMIC_OCP_IRQ1_UNION;
#endif
#define PMIC_OCP_IRQ1_ocpldo11_START  (0)
#define PMIC_OCP_IRQ1_ocpldo11_END    (0)
#define PMIC_OCP_IRQ1_ocpldo10_START  (1)
#define PMIC_OCP_IRQ1_ocpldo10_END    (1)
#define PMIC_OCP_IRQ1_ocpldo9_START   (2)
#define PMIC_OCP_IRQ1_ocpldo9_END     (2)
#define PMIC_OCP_IRQ1_ocpldo8_START   (3)
#define PMIC_OCP_IRQ1_ocpldo8_END     (3)
#define PMIC_OCP_IRQ1_ocpldo7_START   (4)
#define PMIC_OCP_IRQ1_ocpldo7_END     (4)
#define PMIC_OCP_IRQ1_ocpldo5_START   (5)
#define PMIC_OCP_IRQ1_ocpldo5_END     (5)
#define PMIC_OCP_IRQ1_ocpldo4_START   (6)
#define PMIC_OCP_IRQ1_ocpldo4_END     (6)
#define PMIC_OCP_IRQ1_ocpldo3_START   (7)
#define PMIC_OCP_IRQ1_ocpldo3_END     (7)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ2_UNION
 结构说明  : OCP_IRQ2 寄存器结构定义。地址偏移量:0x126，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo20 : 1;  /* bit[0]: LDO20输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo19 : 1;  /* bit[1]: LDO19输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo17 : 1;  /* bit[2]: LDO17输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo16 : 1;  /* bit[3]: LDO16输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo15 : 1;  /* bit[4]: LDO15输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo14 : 1;  /* bit[5]: LDO14输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo13 : 1;  /* bit[6]: LDO13输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo12 : 1;  /* bit[7]: LDO12输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
    } reg;
} PMIC_OCP_IRQ2_UNION;
#endif
#define PMIC_OCP_IRQ2_ocpldo20_START  (0)
#define PMIC_OCP_IRQ2_ocpldo20_END    (0)
#define PMIC_OCP_IRQ2_ocpldo19_START  (1)
#define PMIC_OCP_IRQ2_ocpldo19_END    (1)
#define PMIC_OCP_IRQ2_ocpldo17_START  (2)
#define PMIC_OCP_IRQ2_ocpldo17_END    (2)
#define PMIC_OCP_IRQ2_ocpldo16_START  (3)
#define PMIC_OCP_IRQ2_ocpldo16_END    (3)
#define PMIC_OCP_IRQ2_ocpldo15_START  (4)
#define PMIC_OCP_IRQ2_ocpldo15_END    (4)
#define PMIC_OCP_IRQ2_ocpldo14_START  (5)
#define PMIC_OCP_IRQ2_ocpldo14_END    (5)
#define PMIC_OCP_IRQ2_ocpldo13_START  (6)
#define PMIC_OCP_IRQ2_ocpldo13_END    (6)
#define PMIC_OCP_IRQ2_ocpldo12_START  (7)
#define PMIC_OCP_IRQ2_ocpldo12_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ3_UNION
 结构说明  : OCP_IRQ3 寄存器结构定义。地址偏移量:0x127，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo28 : 1;  /* bit[0]: LDO28输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo27 : 1;  /* bit[1]: LDO27输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo26 : 1;  /* bit[2]: LDO26输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo25 : 1;  /* bit[3]: LDO25输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo24 : 1;  /* bit[4]: LDO24输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo23 : 1;  /* bit[5]: LDO23输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo22 : 1;  /* bit[6]: LDO22输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo21 : 1;  /* bit[7]: LDO21输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
    } reg;
} PMIC_OCP_IRQ3_UNION;
#endif
#define PMIC_OCP_IRQ3_ocpldo28_START  (0)
#define PMIC_OCP_IRQ3_ocpldo28_END    (0)
#define PMIC_OCP_IRQ3_ocpldo27_START  (1)
#define PMIC_OCP_IRQ3_ocpldo27_END    (1)
#define PMIC_OCP_IRQ3_ocpldo26_START  (2)
#define PMIC_OCP_IRQ3_ocpldo26_END    (2)
#define PMIC_OCP_IRQ3_ocpldo25_START  (3)
#define PMIC_OCP_IRQ3_ocpldo25_END    (3)
#define PMIC_OCP_IRQ3_ocpldo24_START  (4)
#define PMIC_OCP_IRQ3_ocpldo24_END    (4)
#define PMIC_OCP_IRQ3_ocpldo23_START  (5)
#define PMIC_OCP_IRQ3_ocpldo23_END    (5)
#define PMIC_OCP_IRQ3_ocpldo22_START  (6)
#define PMIC_OCP_IRQ3_ocpldo22_END    (6)
#define PMIC_OCP_IRQ3_ocpldo21_START  (7)
#define PMIC_OCP_IRQ3_ocpldo21_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ4_UNION
 结构说明  : OCP_IRQ4 寄存器结构定义。地址偏移量:0x128，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_ocp : 1;  /* bit[0]  : classd输出过载中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  reserved   : 3;  /* bit[1-3]: 保留。 */
        unsigned char  ocpldo32   : 1;  /* bit[4]  : LDO32输出过载中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  ocpldo31   : 1;  /* bit[5]  : LDO31输出过载中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  ocpldo30   : 1;  /* bit[6]  : LDO30输出过载中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  ocpldo29   : 1;  /* bit[7]  : LDO29输出过载中断。
                                                     0：无中断；
                                                     1：有中断。 */
    } reg;
} PMIC_OCP_IRQ4_UNION;
#endif
#define PMIC_OCP_IRQ4_classd_ocp_START  (0)
#define PMIC_OCP_IRQ4_classd_ocp_END    (0)
#define PMIC_OCP_IRQ4_ocpldo32_START    (4)
#define PMIC_OCP_IRQ4_ocpldo32_END      (4)
#define PMIC_OCP_IRQ4_ocpldo31_START    (5)
#define PMIC_OCP_IRQ4_ocpldo31_END      (5)
#define PMIC_OCP_IRQ4_ocpldo30_START    (6)
#define PMIC_OCP_IRQ4_ocpldo30_END      (6)
#define PMIC_OCP_IRQ4_ocpldo29_START    (7)
#define PMIC_OCP_IRQ4_ocpldo29_END      (7)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ5_UNION
 结构说明  : OCP_IRQ5 寄存器结构定义。地址偏移量:0x129，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck4_scp : 1;  /* bit[0]  : BUCK4输出短路中断。
                                                    0：无中断；
                                                    1：有中断。 */
        unsigned char  buck3_scp : 1;  /* bit[1]  : BUCK3输出短路中断。
                                                    0：无中断；
                                                    1：有中断。 */
        unsigned char  buck2_scp : 1;  /* bit[2]  : BUCK2输出短路中断。
                                                    0：无中断；
                                                    1：有中断。 */
        unsigned char  buck1_scp : 1;  /* bit[3]  : BUCK1输出短路中断。
                                                    0：无中断；
                                                    1：有中断。 */
        unsigned char  buck0_scp : 1;  /* bit[4]  : BUCK0输出短路中断。
                                                    0：无中断；
                                                    1：有中断。 */
        unsigned char  reserved  : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_OCP_IRQ5_UNION;
#endif
#define PMIC_OCP_IRQ5_buck4_scp_START  (0)
#define PMIC_OCP_IRQ5_buck4_scp_END    (0)
#define PMIC_OCP_IRQ5_buck3_scp_START  (1)
#define PMIC_OCP_IRQ5_buck3_scp_END    (1)
#define PMIC_OCP_IRQ5_buck2_scp_START  (2)
#define PMIC_OCP_IRQ5_buck2_scp_END    (2)
#define PMIC_OCP_IRQ5_buck1_scp_START  (3)
#define PMIC_OCP_IRQ5_buck1_scp_END    (3)
#define PMIC_OCP_IRQ5_buck0_scp_START  (4)
#define PMIC_OCP_IRQ5_buck0_scp_END    (4)


/*****************************************************************************
 结构名    : PMIC_NP_RECORD0_UNION
 结构说明  : NP_RECORD0 寄存器结构定义。地址偏移量:0x12A，初值:0x00，宽度:8
 寄存器说明: 事件记录寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_pwronn_restart   : 1;  /* bit[0]: 开机状态下按键按下8s触发重启。
                                                            0：没有发生过该事件；
                                                            1：发生过该事件。 */
        unsigned char  np_pwrhold_shutdown : 1;  /* bit[1]: pwr_hold拉低触发关机。
                                                            0：没有发生过该事件；
                                                            1：发生过该事件。  */
        unsigned char  np_pwronn_shutdown  : 1;  /* bit[2]: 开机状态下按键按下8s触发关机。
                                                            0：没有发生过该事件；
                                                            1：发生过该事件。 */
        unsigned char  np_pwrhold_pwrup    : 1;  /* bit[3]: pwr_hold触发开机。
                                                            0：没有发生过该事件；
                                                            1：发生过该事件。  */
        unsigned char  np_alarmon_pwrup    : 1;  /* bit[4]: 关机状态下闹钟触发开机(开机状态下的alarm_on不记录)。
                                                            0：没有发生过该事件；
                                                            1：发生过该事件。  */
        unsigned char  np_vbus_pwrup       : 1;  /* bit[5]: 关机状态下充电器插入200ms触发开机。 
                                                            0：没有发生过该事件；
                                                            1：发生过该事件。  */
        unsigned char  np_pwronn_pwrup     : 1;  /* bit[6]: 关机状态下按键按下500ms触发开机。
                                                            0：没有发生过该事件；
                                                            1：发生过该事件。 */
        unsigned char  np_fast_pwrup       : 1;  /* bit[7]: 产线快速开机。
                                                            0：没有发生过该事件；
                                                            1：发生过该事件。 */
    } reg;
} PMIC_NP_RECORD0_UNION;
#endif
#define PMIC_NP_RECORD0_np_pwronn_restart_START    (0)
#define PMIC_NP_RECORD0_np_pwronn_restart_END      (0)
#define PMIC_NP_RECORD0_np_pwrhold_shutdown_START  (1)
#define PMIC_NP_RECORD0_np_pwrhold_shutdown_END    (1)
#define PMIC_NP_RECORD0_np_pwronn_shutdown_START   (2)
#define PMIC_NP_RECORD0_np_pwronn_shutdown_END     (2)
#define PMIC_NP_RECORD0_np_pwrhold_pwrup_START     (3)
#define PMIC_NP_RECORD0_np_pwrhold_pwrup_END       (3)
#define PMIC_NP_RECORD0_np_alarmon_pwrup_START     (4)
#define PMIC_NP_RECORD0_np_alarmon_pwrup_END       (4)
#define PMIC_NP_RECORD0_np_vbus_pwrup_START        (5)
#define PMIC_NP_RECORD0_np_vbus_pwrup_END          (5)
#define PMIC_NP_RECORD0_np_pwronn_pwrup_START      (6)
#define PMIC_NP_RECORD0_np_pwronn_pwrup_END        (6)
#define PMIC_NP_RECORD0_np_fast_pwrup_START        (7)
#define PMIC_NP_RECORD0_np_fast_pwrup_END          (7)


/*****************************************************************************
 结构名    : PMIC_NP_RECORD1_UNION
 结构说明  : NP_RECORD1 寄存器结构定义。地址偏移量:0x12B，初值:0x08，宽度:8
 寄存器说明: 事件记录寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_tcxo_clk_sel_r : 1;  /* bit[0]: 32k RC切换到32K Crystal OSC 时钟。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。  */
        unsigned char  np_dcxo_clk_sel_r : 1;  /* bit[1]: 32K RC 切换到 19.2MHz/586 时钟。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。  */
        unsigned char  np_dcxo_clk_sel_f : 1;  /* bit[2]: 19.2MHz/586 切换到 32K RC时钟。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。  */
        unsigned char  np_vsys_vcoin_sel : 1;  /* bit[3]: VSYS与VCION切换信号。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。 */
        unsigned char  np_smpl           : 1;  /* bit[4]: SMPL发生记录
                                                          0：没有发生SMPL；
                                                          1：发生SMPL。 */
        unsigned char  np_core_io_vld_f  : 1;  /* bit[5]: core_io_vld异常下电事件记录（VDD_IO是否拉低）；
                                                          0：没有发生拉低事件；
                                                          1：有发生拉低事件。 */
        unsigned char  reserved          : 1;  /* bit[6]: 测试预留观测信号。 */
        unsigned char  np_pwrhold_1s     : 1;  /* bit[7]: SYS_RST_N拉高后1s时刻，VBUS不在位，并且pwr_hold为低触发关机。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。  */
    } reg;
} PMIC_NP_RECORD1_UNION;
#endif
#define PMIC_NP_RECORD1_np_tcxo_clk_sel_r_START  (0)
#define PMIC_NP_RECORD1_np_tcxo_clk_sel_r_END    (0)
#define PMIC_NP_RECORD1_np_dcxo_clk_sel_r_START  (1)
#define PMIC_NP_RECORD1_np_dcxo_clk_sel_r_END    (1)
#define PMIC_NP_RECORD1_np_dcxo_clk_sel_f_START  (2)
#define PMIC_NP_RECORD1_np_dcxo_clk_sel_f_END    (2)
#define PMIC_NP_RECORD1_np_vsys_vcoin_sel_START  (3)
#define PMIC_NP_RECORD1_np_vsys_vcoin_sel_END    (3)
#define PMIC_NP_RECORD1_np_smpl_START            (4)
#define PMIC_NP_RECORD1_np_smpl_END              (4)
#define PMIC_NP_RECORD1_np_core_io_vld_f_START   (5)
#define PMIC_NP_RECORD1_np_core_io_vld_f_END     (5)
#define PMIC_NP_RECORD1_np_pwrhold_1s_START      (7)
#define PMIC_NP_RECORD1_np_pwrhold_1s_END        (7)




/****************************************************************************
                     (3/5) PMU_RTC
 ****************************************************************************/
/*****************************************************************************
 结构名    : PMIC_RTCDR0_UNION
 结构说明  : RTCDR0 寄存器结构定义。地址偏移量:0x12C，初值:0x00，宽度:8
 寄存器说明: RTC当前时间寄存器bit[7:0]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr0 : 8;  /* bit[0-7]: 32 bits,RTC Data Register,读返回当前RTC值。 */
    } reg;
} PMIC_RTCDR0_UNION;
#endif
#define PMIC_RTCDR0_rtcdr0_START  (0)
#define PMIC_RTCDR0_rtcdr0_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCDR1_UNION
 结构说明  : RTCDR1 寄存器结构定义。地址偏移量:0x12D，初值:0x00，宽度:8
 寄存器说明: RTC当前时间寄存器bit[15:8]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCDR1_UNION;
#endif
#define PMIC_RTCDR1_rtcdr1_START  (0)
#define PMIC_RTCDR1_rtcdr1_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCDR2_UNION
 结构说明  : RTCDR2 寄存器结构定义。地址偏移量:0x12E，初值:0x00，宽度:8
 寄存器说明: RTC当前时间寄存器bit[23:16]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCDR2_UNION;
#endif
#define PMIC_RTCDR2_rtcdr2_START  (0)
#define PMIC_RTCDR2_rtcdr2_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCDR3_UNION
 结构说明  : RTCDR3 寄存器结构定义。地址偏移量:0x12F，初值:0x00，宽度:8
 寄存器说明: RTC当前时间寄存器bit[31:24]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcdr3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCDR3_UNION;
#endif
#define PMIC_RTCDR3_rtcdr3_START  (0)
#define PMIC_RTCDR3_rtcdr3_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCMR0_UNION
 结构说明  : RTCMR0 寄存器结构定义。地址偏移量:0x130，初值:0x00，宽度:8
 寄存器说明: RTC比较寄存器bit[7:0]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr0 : 8;  /* bit[0-7]: 32 bits,RTC match register 比较寄存器(设置闹铃时间)，读返回最后一次次设定值。（配置顺序要求先配置低位，最后配置最高位。读没有要求。顺序写完最后一组寄存器后，要等待3个32K cycle才能再次操作此寄存器） */
    } reg;
} PMIC_RTCMR0_UNION;
#endif
#define PMIC_RTCMR0_rtcmr0_START  (0)
#define PMIC_RTCMR0_rtcmr0_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCMR1_UNION
 结构说明  : RTCMR1 寄存器结构定义。地址偏移量:0x131，初值:0x00，宽度:8
 寄存器说明: RTC比较寄存器bit[15:8]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCMR1_UNION;
#endif
#define PMIC_RTCMR1_rtcmr1_START  (0)
#define PMIC_RTCMR1_rtcmr1_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCMR2_UNION
 结构说明  : RTCMR2 寄存器结构定义。地址偏移量:0x132，初值:0x00，宽度:8
 寄存器说明: RTC比较寄存器bit[23:16]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCMR2_UNION;
#endif
#define PMIC_RTCMR2_rtcmr2_START  (0)
#define PMIC_RTCMR2_rtcmr2_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCMR3_UNION
 结构说明  : RTCMR3 寄存器结构定义。地址偏移量:0x133，初值:0x00，宽度:8
 寄存器说明: RTC比较寄存器bit[31:24]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcmr3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCMR3_UNION;
#endif
#define PMIC_RTCMR3_rtcmr3_START  (0)
#define PMIC_RTCMR3_rtcmr3_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCLR0_UNION
 结构说明  : RTCLR0 寄存器结构定义。地址偏移量:0x134，初值:0x00，宽度:8
 寄存器说明: RTC加载寄存器bit[7:0]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr0 : 8;  /* bit[0-7]: 32 bits RTC load register 加载寄存器（设置当前时间），读返回最后次设定值。（配置顺序要求先配置低位，最后配置最高位。读没有要求。顺序写完最后一组寄存器后，要等待3个32K cycle才能再次操作此寄存器） */
    } reg;
} PMIC_RTCLR0_UNION;
#endif
#define PMIC_RTCLR0_rtcclr0_START  (0)
#define PMIC_RTCLR0_rtcclr0_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCLR1_UNION
 结构说明  : RTCLR1 寄存器结构定义。地址偏移量:0x135，初值:0x00，宽度:8
 寄存器说明: RTC加载寄存器bit[15:8]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCLR1_UNION;
#endif
#define PMIC_RTCLR1_rtcclr1_START  (0)
#define PMIC_RTCLR1_rtcclr1_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCLR2_UNION
 结构说明  : RTCLR2 寄存器结构定义。地址偏移量:0x136，初值:0x00，宽度:8
 寄存器说明: RTC加载寄存器bit[23:16]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCLR2_UNION;
#endif
#define PMIC_RTCLR2_rtcclr2_START  (0)
#define PMIC_RTCLR2_rtcclr2_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCLR3_UNION
 结构说明  : RTCLR3 寄存器结构定义。地址偏移量:0x137，初值:0x00，宽度:8
 寄存器说明: RTC加载寄存器bit[31:24]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtcclr3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_RTCLR3_UNION;
#endif
#define PMIC_RTCLR3_rtcclr3_START  (0)
#define PMIC_RTCLR3_rtcclr3_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTCCTRL_UNION
 结构说明  : RTCCTRL 寄存器结构定义。地址偏移量:0x138，初值:0x03，宽度:8
 寄存器说明: RTC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtccr           : 1;  /* bit[0]  : 读RTC控制位。
                                                          0：读RTC当前值，返回值全部为0；
                                                          1：读RTC当前值，返回值为实际当前值。
                                                          （此寄存器写完后，要等待3个32K cycle才能再次操作此寄存器） */
        unsigned char  ref_res_sel_int : 1;  /* bit[1]  : 基准VREF管脚滤波电阻选择 。 */
        unsigned char  reserved        : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_RTCCTRL_UNION;
#endif
#define PMIC_RTCCTRL_rtccr_START            (0)
#define PMIC_RTCCTRL_rtccr_END              (0)
#define PMIC_RTCCTRL_ref_res_sel_int_START  (1)
#define PMIC_RTCCTRL_ref_res_sel_int_END    (1)


/*****************************************************************************
 结构名    : PMIC_XO_THRESOLD0_UNION
 结构说明  : XO_THRESOLD0 寄存器结构定义。地址偏移量:0x139，初值:0xB8，宽度:8
 寄存器说明: XO_THRESOLD[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_low : 8;  /* bit[0-7]: 校准偏差阈值设置寄存器。
                                                               （此寄存器可以通过映射寄存器D2A_RES0和D2A_RES1读出） */
    } reg;
} PMIC_XO_THRESOLD0_UNION;
#endif
#define PMIC_XO_THRESOLD0_xo_cali_thresold_low_START  (0)
#define PMIC_XO_THRESOLD0_xo_cali_thresold_low_END    (7)


/*****************************************************************************
 结构名    : PMIC_XO_THRESOLD1_UNION
 结构说明  : XO_THRESOLD1 寄存器结构定义。地址偏移量:0x13A，初值:0x00，宽度:8
 寄存器说明: XO_THRESOLD[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold1_high : 8;  /* bit[0-7]: 校准偏差阈值设置寄存器。
                                                                 （此寄存器可以通过映射寄存器D2A_RES2读出） */
    } reg;
} PMIC_XO_THRESOLD1_UNION;
#endif
#define PMIC_XO_THRESOLD1_xo_cali_thresold1_high_START  (0)
#define PMIC_XO_THRESOLD1_xo_cali_thresold1_high_END    (7)


/*****************************************************************************
 结构名    : PMIC_CRC_VAULE0_UNION
 结构说明  : CRC_VAULE0 寄存器结构定义。地址偏移量:0x13B，初值:0x00，宽度:8
 寄存器说明: CRC_VALUE[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_value0 : 8;  /* bit[0-7]: DCXO模式下，在RTC时钟校准状态下得到的RC时钟校准值[7:0]。 */
    } reg;
} PMIC_CRC_VAULE0_UNION;
#endif
#define PMIC_CRC_VAULE0_crc_value0_START  (0)
#define PMIC_CRC_VAULE0_crc_value0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CRC_VAULE1_UNION
 结构说明  : CRC_VAULE1 寄存器结构定义。地址偏移量:0x13C，初值:0x27，宽度:8
 寄存器说明: CRC_VALUE[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_value1 : 8;  /* bit[0-7]: DCXO模式下，在RTC时钟校准状态下得到的RC时钟校准值[15:8]。 */
    } reg;
} PMIC_CRC_VAULE1_UNION;
#endif
#define PMIC_CRC_VAULE1_crc_value1_START  (0)
#define PMIC_CRC_VAULE1_crc_value1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CRC_VAULE2_UNION
 结构说明  : CRC_VAULE2 寄存器结构定义。地址偏移量:0x13D，初值:0x09，宽度:8
 寄存器说明: CRC_VALUE[20:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_value2 : 5;  /* bit[0-4]: DCXO模式下，在RTC时钟校准状态下得到的RC时钟校准值[20:16]。 */
        unsigned char  reserved   : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_CRC_VAULE2_UNION;
#endif
#define PMIC_CRC_VAULE2_crc_value2_START  (0)
#define PMIC_CRC_VAULE2_crc_value2_END    (4)


/*****************************************************************************
 结构名    : PMIC_RTC_PWRUP_TIMER0_UNION
 结构说明  : RTC_PWRUP_TIMER0 寄存器结构定义。地址偏移量:0x13E，初值:0x00，宽度:8
 寄存器说明: RTC上电拍照[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer0 : 8;  /* bit[0-7]: PMU上电时刻RTC计数拍照值[7:0]。 */
    } reg;
} PMIC_RTC_PWRUP_TIMER0_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER0_rtc_pwrup_timer0_START  (0)
#define PMIC_RTC_PWRUP_TIMER0_rtc_pwrup_timer0_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTC_PWRUP_TIMER1_UNION
 结构说明  : RTC_PWRUP_TIMER1 寄存器结构定义。地址偏移量:0x13F，初值:0x00，宽度:8
 寄存器说明: RTC上电拍照[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer1 : 8;  /* bit[0-7]: PMU上电时刻RTC计数拍照值[15:8]。 */
    } reg;
} PMIC_RTC_PWRUP_TIMER1_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER1_rtc_pwrup_timer1_START  (0)
#define PMIC_RTC_PWRUP_TIMER1_rtc_pwrup_timer1_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTC_PWRUP_TIMER2_UNION
 结构说明  : RTC_PWRUP_TIMER2 寄存器结构定义。地址偏移量:0x140，初值:0x00，宽度:8
 寄存器说明: RTC上电拍照[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer2 : 8;  /* bit[0-7]: PMU上电时刻RTC计数拍照值[23:16]。 */
    } reg;
} PMIC_RTC_PWRUP_TIMER2_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER2_rtc_pwrup_timer2_START  (0)
#define PMIC_RTC_PWRUP_TIMER2_rtc_pwrup_timer2_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTC_PWRUP_TIMER3_UNION
 结构说明  : RTC_PWRUP_TIMER3 寄存器结构定义。地址偏移量:0x141，初值:0x00，宽度:8
 寄存器说明: RTC上电拍照[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrup_timer3 : 8;  /* bit[0-7]: PMU上电时刻RTC计数拍照值[31:24]。 */
    } reg;
} PMIC_RTC_PWRUP_TIMER3_UNION;
#endif
#define PMIC_RTC_PWRUP_TIMER3_rtc_pwrup_timer3_START  (0)
#define PMIC_RTC_PWRUP_TIMER3_rtc_pwrup_timer3_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTC_PWRDOWN_TIMER0_UNION
 结构说明  : RTC_PWRDOWN_TIMER0 寄存器结构定义。地址偏移量:0x142，初值:0x00，宽度:8
 寄存器说明: RTC下电拍照[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer0 : 8;  /* bit[0-7]: PMU下电时刻RTC计数拍照值[7:0]。 */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER0_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER0_rtc_pwrdown_timer0_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER0_rtc_pwrdown_timer0_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTC_PWRDOWN_TIMER1_UNION
 结构说明  : RTC_PWRDOWN_TIMER1 寄存器结构定义。地址偏移量:0x143，初值:0x00，宽度:8
 寄存器说明: RTC下电拍照[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer1 : 8;  /* bit[0-7]: PMU下电时刻RTC计数拍照值[15:8]。 */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER1_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER1_rtc_pwrdown_timer1_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER1_rtc_pwrdown_timer1_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTC_PWRDOWN_TIMER2_UNION
 结构说明  : RTC_PWRDOWN_TIMER2 寄存器结构定义。地址偏移量:0x144，初值:0x00，宽度:8
 寄存器说明: RTC下电拍照[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer2 : 8;  /* bit[0-7]: PMU下电时刻RTC计数拍照值[23:16]。 */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER2_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER2_rtc_pwrdown_timer2_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER2_rtc_pwrdown_timer2_END    (7)


/*****************************************************************************
 结构名    : PMIC_RTC_PWRDOWN_TIMER3_UNION
 结构说明  : RTC_PWRDOWN_TIMER3 寄存器结构定义。地址偏移量:0x145，初值:0x00，宽度:8
 寄存器说明: RTC下电拍照[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtc_pwrdown_timer3 : 8;  /* bit[0-7]: PMU下电时刻RTC计数拍照值[31:24]。 */
    } reg;
} PMIC_RTC_PWRDOWN_TIMER3_UNION;
#endif
#define PMIC_RTC_PWRDOWN_TIMER3_rtc_pwrdown_timer3_START  (0)
#define PMIC_RTC_PWRDOWN_TIMER3_rtc_pwrdown_timer3_END    (7)




/****************************************************************************
                     (4/5) PMU_COUL
 ****************************************************************************/
/*****************************************************************************
 结构名    : PMIC_COUL_IRQ_UNION
 结构说明  : COUL_IRQ 寄存器结构定义。地址偏移量:0x14B，初值:0x00，宽度:8
 寄存器说明: 库仑计中断寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_i   : 1;  /* bit[0]  : cl_out>cl_int时上报中断。
                                                     0：无此中断；
                                                     1：上报中断。 */
        unsigned char  cl_out_i   : 1;  /* bit[1]  : cl_out计数到81%上报中断。
                                                     0：无此中断；
                                                     1：上报中断。 */
        unsigned char  cl_in_i    : 1;  /* bit[2]  : cl_in计数到81%上报中断。
                                                     0：无此中断；
                                                     1：上报中断。 */
        unsigned char  vbat_int_i : 1;  /* bit[3]  : vbat电压<设定的vbat_int值。
                                                     0：无此中断；
                                                     1：上报中断。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_COUL_IRQ_UNION;
#endif
#define PMIC_COUL_IRQ_cl_int_i_START    (0)
#define PMIC_COUL_IRQ_cl_int_i_END      (0)
#define PMIC_COUL_IRQ_cl_out_i_START    (1)
#define PMIC_COUL_IRQ_cl_out_i_END      (1)
#define PMIC_COUL_IRQ_cl_in_i_START     (2)
#define PMIC_COUL_IRQ_cl_in_i_END       (2)
#define PMIC_COUL_IRQ_vbat_int_i_START  (3)
#define PMIC_COUL_IRQ_vbat_int_i_END    (3)


/*****************************************************************************
 结构名    : PMIC_COUL_IRQ_MASK_UNION
 结构说明  : COUL_IRQ_MASK 寄存器结构定义。地址偏移量:0x14C，初值:0x00，宽度:8
 寄存器说明: 库仑计中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_i_mk   : 1;  /* bit[0]  : cl_int_i中断屏蔽位。
                                                        0：不屏蔽；
                                                        1：cl_int_i中断屏蔽。 */
        unsigned char  cl_out_i_mk   : 1;  /* bit[1]  : cl_out_i中断屏蔽位。
                                                        0：不屏蔽；
                                                        1：cl_out_i中断屏蔽。 */
        unsigned char  cl_in_i_mk    : 1;  /* bit[2]  : cl_in_i中断屏蔽位。
                                                        0：不屏蔽；
                                                        1：cl_in_i中断屏蔽。 */
        unsigned char  vbat_int_i_mk : 1;  /* bit[3]  : vbat_int_i中断屏蔽位。
                                                        0：不屏蔽；
                                                        1：vbat_int_i中断屏蔽。 */
        unsigned char  reserved      : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_COUL_IRQ_MASK_UNION;
#endif
#define PMIC_COUL_IRQ_MASK_cl_int_i_mk_START    (0)
#define PMIC_COUL_IRQ_MASK_cl_int_i_mk_END      (0)
#define PMIC_COUL_IRQ_MASK_cl_out_i_mk_START    (1)
#define PMIC_COUL_IRQ_MASK_cl_out_i_mk_END      (1)
#define PMIC_COUL_IRQ_MASK_cl_in_i_mk_START     (2)
#define PMIC_COUL_IRQ_MASK_cl_in_i_mk_END       (2)
#define PMIC_COUL_IRQ_MASK_vbat_int_i_mk_START  (3)
#define PMIC_COUL_IRQ_MASK_vbat_int_i_mk_END    (3)


/*****************************************************************************
 结构名    : PMIC_CURRENT_0_UNION
 结构说明  : CURRENT_0 寄存器结构定义。地址偏移量:0x14D，初值:0x00，宽度:8
 寄存器说明: 当前电流[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_0 : 8;  /* bit[0-7]: 当前电流值，此值是经过校准后的值。
                                                    （对于依靠多组寄存器存储的数据，软件读取时必须先读低8bit，再依次往高位读取，最后读取最高8bit。两次读取之间没有时间约束。下面所有多于8bit的寄存器的读写方式均要求按照此操作。） */
    } reg;
} PMIC_CURRENT_0_UNION;
#endif
#define PMIC_CURRENT_0_current_0_START  (0)
#define PMIC_CURRENT_0_current_0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT_1_UNION
 结构说明  : CURRENT_1 寄存器结构定义。地址偏移量:0x14E，初值:0x00，宽度:8
 寄存器说明: 当前电流[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT_1_UNION;
#endif
#define PMIC_CURRENT_1_current_1_START  (0)
#define PMIC_CURRENT_1_current_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT_0_UNION
 结构说明  : V_OUT_0 寄存器结构定义。地址偏移量:0x14F，初值:0xFF，宽度:8
 寄存器说明: 当前电压[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_0 : 8;  /* bit[0-7]: 当前电压值，此值是经过校准后的值。 */
    } reg;
} PMIC_V_OUT_0_UNION;
#endif
#define PMIC_V_OUT_0_v_out_0_START  (0)
#define PMIC_V_OUT_0_v_out_0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT_1_UNION
 结构说明  : V_OUT_1 寄存器结构定义。地址偏移量:0x150，初值:0xFF，宽度:8
 寄存器说明: 当前电压[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT_1_UNION;
#endif
#define PMIC_V_OUT_1_v_out_1_START  (0)
#define PMIC_V_OUT_1_v_out_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_CTRL_REG_UNION
 结构说明  : CLJ_CTRL_REG 寄存器结构定义。地址偏移量:0x151，初值:0x80，宽度:8
 寄存器说明: 库仑计控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_ctrl            : 3;  /* bit[0-2]: bit[2]：是否强制进入ECO模式控制。
                                                              0：不强制进入ECO模式；
                                                              1：强制进入ECO模式。
                                                              
                                                              bit[1]：库仑计是否跟随PMU进入ECO模式控制。
                                                              0：库仑计不跟随PMU进入ECO模式；
                                                              1：库仑计跟随PMU进入ECO模式。
                                                              仅发生在bit[2] == 0 时有效。（要想跟随PMU，同时需要将0x0DD寄存器清零）
                                                              
                                                              bit[0]：进入ECO模式时，使能信号是否去抖控制。
                                                              0：进入ECO模式使能信号不去抖；
                                                              1：进入ECO模式使能信号去抖。
                                                              仅发生在bit[1] ==1 时有效。
                                                              注：eco_ctrl该寄存器热复位后清零。 */
        unsigned char  reflash_value_ctrl  : 1;  /* bit[3]  : 库仑计更新数据方式选择：
                                                              0：所有状态都更新数据；
                                                              1：仅ECO模式更新数据。 */
        unsigned char  eco_filter_time     : 2;  /* bit[4-5]: 库仑计退出ECO模式使能信号去抖时间选择：
                                                              00：100ms；
                                                              01：200ms；
                                                              10：300ms；
                                                              11：400ms。
                                                              用于配置en_eco_mode去抖时长，默认为00。 */
        unsigned char  calibration_ctrl    : 1;  /* bit[6]  : 库仑计强制校准控制位。
                                                              0：不校准；
                                                              1：强制进入校准状态。 */
        unsigned char  coul_ctrl_onoff_reg : 1;  /* bit[7]  : 库仑计开关控制寄存器。
                                                              0：库仑计关闭；
                                                              1：库仑计开启。
                                                              （此组两次写之前至少间隔3个32kHz系统时钟周期） */
    } reg;
} PMIC_CLJ_CTRL_REG_UNION;
#endif
#define PMIC_CLJ_CTRL_REG_eco_ctrl_START             (0)
#define PMIC_CLJ_CTRL_REG_eco_ctrl_END               (2)
#define PMIC_CLJ_CTRL_REG_reflash_value_ctrl_START   (3)
#define PMIC_CLJ_CTRL_REG_reflash_value_ctrl_END     (3)
#define PMIC_CLJ_CTRL_REG_eco_filter_time_START      (4)
#define PMIC_CLJ_CTRL_REG_eco_filter_time_END        (5)
#define PMIC_CLJ_CTRL_REG_calibration_ctrl_START     (6)
#define PMIC_CLJ_CTRL_REG_calibration_ctrl_END       (6)
#define PMIC_CLJ_CTRL_REG_coul_ctrl_onoff_reg_START  (7)
#define PMIC_CLJ_CTRL_REG_coul_ctrl_onoff_reg_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_REFALSH_TIME_UNION
 结构说明  : ECO_REFALSH_TIME 寄存器结构定义。地址偏移量:0x152，初值:0x01，宽度:8
 寄存器说明: ECO_REFLASH工作时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_reflash_time : 8;  /* bit[0-7]: 此工作时间以一个单位代表110ms，为ECO_REFLASH时间；有效配置值为1~255，配置值大于255时，硬件直接饱和到255。默认为1。（此组两次写之前至少间隔3个32kHz系统时钟周期） */
    } reg;
} PMIC_ECO_REFALSH_TIME_UNION;
#endif
#define PMIC_ECO_REFALSH_TIME_eco_reflash_time_START  (0)
#define PMIC_ECO_REFALSH_TIME_eco_reflash_time_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_OUT0_UNION
 结构说明  : CL_OUT0 寄存器结构定义。地址偏移量:0x153，初值:0x00，宽度:8
 寄存器说明: cl_out[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out0 : 8;  /* bit[0-7]: 流出电量计数器[31:0]。
                                                  （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_CL_OUT0_UNION;
#endif
#define PMIC_CL_OUT0_cl_out0_START  (0)
#define PMIC_CL_OUT0_cl_out0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_OUT1_UNION
 结构说明  : CL_OUT1 寄存器结构定义。地址偏移量:0x154，初值:0x00，宽度:8
 寄存器说明: cl_out[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT1_UNION;
#endif
#define PMIC_CL_OUT1_cl_out1_START  (0)
#define PMIC_CL_OUT1_cl_out1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_OUT2_UNION
 结构说明  : CL_OUT2 寄存器结构定义。地址偏移量:0x155，初值:0x00，宽度:8
 寄存器说明: cl_out[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT2_UNION;
#endif
#define PMIC_CL_OUT2_cl_out2_START  (0)
#define PMIC_CL_OUT2_cl_out2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_OUT3_UNION
 结构说明  : CL_OUT3 寄存器结构定义。地址偏移量:0x156，初值:0x00，宽度:8
 寄存器说明: cl_out[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT3_UNION;
#endif
#define PMIC_CL_OUT3_cl_out3_START  (0)
#define PMIC_CL_OUT3_cl_out3_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_IN0_UNION
 结构说明  : CL_IN0 寄存器结构定义。地址偏移量:0x157，初值:0x00，宽度:8
 寄存器说明: cl_in[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in0 : 8;  /* bit[0-7]: 流入电量计数器[31:0]。
                                                 （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_CL_IN0_UNION;
#endif
#define PMIC_CL_IN0_cl_in0_START  (0)
#define PMIC_CL_IN0_cl_in0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_IN1_UNION
 结构说明  : CL_IN1 寄存器结构定义。地址偏移量:0x158，初值:0x00，宽度:8
 寄存器说明: cl_in[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN1_UNION;
#endif
#define PMIC_CL_IN1_cl_in1_START  (0)
#define PMIC_CL_IN1_cl_in1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_IN2_UNION
 结构说明  : CL_IN2 寄存器结构定义。地址偏移量:0x159，初值:0x00，宽度:8
 寄存器说明: cl_in[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN2_UNION;
#endif
#define PMIC_CL_IN2_cl_in2_START  (0)
#define PMIC_CL_IN2_cl_in2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_IN3_UNION
 结构说明  : CL_IN3 寄存器结构定义。地址偏移量:0x15A，初值:0x00，宽度:8
 寄存器说明: cl_in[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN3_UNION;
#endif
#define PMIC_CL_IN3_cl_in3_START  (0)
#define PMIC_CL_IN3_cl_in3_END    (7)


/*****************************************************************************
 结构名    : PMIC_CHG_TIMER0_UNION
 结构说明  : CHG_TIMER0 寄存器结构定义。地址偏移量:0x15B，初值:0x00，宽度:8
 寄存器说明: chg_timer[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer0 : 8;  /* bit[0-7]: 充电时间计数器[31:0]。
                                                     （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_CHG_TIMER0_UNION;
#endif
#define PMIC_CHG_TIMER0_chg_timer0_START  (0)
#define PMIC_CHG_TIMER0_chg_timer0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CHG_TIMER1_UNION
 结构说明  : CHG_TIMER1 寄存器结构定义。地址偏移量:0x15C，初值:0x00，宽度:8
 寄存器说明: chg_timer[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER1_UNION;
#endif
#define PMIC_CHG_TIMER1_chg_timer1_START  (0)
#define PMIC_CHG_TIMER1_chg_timer1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CHG_TIMER2_UNION
 结构说明  : CHG_TIMER2 寄存器结构定义。地址偏移量:0x15D，初值:0x00，宽度:8
 寄存器说明: chg_timer[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER2_UNION;
#endif
#define PMIC_CHG_TIMER2_chg_timer2_START  (0)
#define PMIC_CHG_TIMER2_chg_timer2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CHG_TIMER3_UNION
 结构说明  : CHG_TIMER3 寄存器结构定义。地址偏移量:0x15E，初值:0x00，宽度:8
 寄存器说明: chg_timer[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER3_UNION;
#endif
#define PMIC_CHG_TIMER3_chg_timer3_START  (0)
#define PMIC_CHG_TIMER3_chg_timer3_END    (7)


/*****************************************************************************
 结构名    : PMIC_LOAD_TIMER0_UNION
 结构说明  : LOAD_TIMER0 寄存器结构定义。地址偏移量:0x15F，初值:0x00，宽度:8
 寄存器说明: load_timer[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer0 : 8;  /* bit[0-7]: 放电时间计数器[31:0]。
                                                      （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_LOAD_TIMER0_UNION;
#endif
#define PMIC_LOAD_TIMER0_load_timer0_START  (0)
#define PMIC_LOAD_TIMER0_load_timer0_END    (7)


/*****************************************************************************
 结构名    : PMIC_LOAD_TIMER1_UNION
 结构说明  : LOAD_TIMER1 寄存器结构定义。地址偏移量:0x160，初值:0x00，宽度:8
 寄存器说明: load_timer[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER1_UNION;
#endif
#define PMIC_LOAD_TIMER1_load_timer1_START  (0)
#define PMIC_LOAD_TIMER1_load_timer1_END    (7)


/*****************************************************************************
 结构名    : PMIC_LOAD_TIMER2_UNION
 结构说明  : LOAD_TIMER2 寄存器结构定义。地址偏移量:0x161，初值:0x00，宽度:8
 寄存器说明: load_timer[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER2_UNION;
#endif
#define PMIC_LOAD_TIMER2_load_timer2_START  (0)
#define PMIC_LOAD_TIMER2_load_timer2_END    (7)


/*****************************************************************************
 结构名    : PMIC_LOAD_TIMER3_UNION
 结构说明  : LOAD_TIMER3 寄存器结构定义。地址偏移量:0x162，初值:0x00，宽度:8
 寄存器说明: load_timer[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER3_UNION;
#endif
#define PMIC_LOAD_TIMER3_load_timer3_START  (0)
#define PMIC_LOAD_TIMER3_load_timer3_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_INT0_UNION
 结构说明  : CL_INT0 寄存器结构定义。地址偏移量:0x163，初值:0x00，宽度:8
 寄存器说明: cl_int[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int0 : 8;  /* bit[0-7]: 流出电量中断比较寄存器[31:0]：
                                                  当cl_inout>cl_int时上报中断。
                                                  （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_CL_INT0_UNION;
#endif
#define PMIC_CL_INT0_cl_int0_START  (0)
#define PMIC_CL_INT0_cl_int0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_INT1_UNION
 结构说明  : CL_INT1 寄存器结构定义。地址偏移量:0x164，初值:0x00，宽度:8
 寄存器说明: cl_int[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT1_UNION;
#endif
#define PMIC_CL_INT1_cl_int1_START  (0)
#define PMIC_CL_INT1_cl_int1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_INT2_UNION
 结构说明  : CL_INT2 寄存器结构定义。地址偏移量:0x165，初值:0x00，宽度:8
 寄存器说明: cl_int[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT2_UNION;
#endif
#define PMIC_CL_INT2_cl_int2_START  (0)
#define PMIC_CL_INT2_cl_int2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_INT3_UNION
 结构说明  : CL_INT3 寄存器结构定义。地址偏移量:0x166，初值:0x80，宽度:8
 寄存器说明: cl_int[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT3_UNION;
#endif
#define PMIC_CL_INT3_cl_int3_START  (0)
#define PMIC_CL_INT3_cl_int3_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_INT0_UNION
 结构说明  : V_INT0 寄存器结构定义。地址偏移量:0x167，初值:0x00，宽度:8
 寄存器说明: v_int[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_int0 : 8;  /* bit[0-7]: 电压中断比较值寄存器[15:0]。
                                                 （先写低8bit，再写高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_V_INT0_UNION;
#endif
#define PMIC_V_INT0_v_int0_START  (0)
#define PMIC_V_INT0_v_int0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_INT1_UNION
 结构说明  : V_INT1 寄存器结构定义。地址偏移量:0x168，初值:0x00，宽度:8
 寄存器说明: v_int[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_int1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_INT1_UNION;
#endif
#define PMIC_V_INT1_v_int1_START  (0)
#define PMIC_V_INT1_v_int1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_CURRENT0_UNION
 结构说明  : OFFSET_CURRENT0 寄存器结构定义。地址偏移量:0x169，初值:0x00，宽度:8
 寄存器说明: offset_current[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current0 : 8;  /* bit[0-7]: 电流校准值[15:0]。 */
    } reg;
} PMIC_OFFSET_CURRENT0_UNION;
#endif
#define PMIC_OFFSET_CURRENT0_offset_current0_START  (0)
#define PMIC_OFFSET_CURRENT0_offset_current0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_CURRENT1_UNION
 结构说明  : OFFSET_CURRENT1 寄存器结构定义。地址偏移量:0x16A，初值:0x00，宽度:8
 寄存器说明: offset_current[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_CURRENT1_UNION;
#endif
#define PMIC_OFFSET_CURRENT1_offset_current1_START  (0)
#define PMIC_OFFSET_CURRENT1_offset_current1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_VOLTAGE0_UNION
 结构说明  : OFFSET_VOLTAGE0 寄存器结构定义。地址偏移量:0x16B，初值:0x00，宽度:8
 寄存器说明: offset_voltage[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage0 : 8;  /* bit[0-7]: 电压校准值[15:0]。 */
    } reg;
} PMIC_OFFSET_VOLTAGE0_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE0_offset_voltage0_START  (0)
#define PMIC_OFFSET_VOLTAGE0_offset_voltage0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_VOLTAGE1_UNION
 结构说明  : OFFSET_VOLTAGE1 寄存器结构定义。地址偏移量:0x16C，初值:0x00，宽度:8
 寄存器说明: offset_voltage[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_VOLTAGE1_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE1_offset_voltage1_START  (0)
#define PMIC_OFFSET_VOLTAGE1_offset_voltage1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCV_VOLTAGE0_UNION
 结构说明  : OCV_VOLTAGE0 寄存器结构定义。地址偏移量:0x16D，初值:0x00，宽度:8
 寄存器说明: v_ocv_data[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_ocv_data0 : 8;  /* bit[0-7]: 开机时OCV电压采样值[15:0]。此值是原始值，未经过校准。 */
    } reg;
} PMIC_OCV_VOLTAGE0_UNION;
#endif
#define PMIC_OCV_VOLTAGE0_v_ocv_data0_START  (0)
#define PMIC_OCV_VOLTAGE0_v_ocv_data0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCV_VOLTAGE1_UNION
 结构说明  : OCV_VOLTAGE1 寄存器结构定义。地址偏移量:0x16E，初值:0x00，宽度:8
 寄存器说明: v_ocv_data[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_ocv_data1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OCV_VOLTAGE1_UNION;
#endif
#define PMIC_OCV_VOLTAGE1_v_ocv_data1_START  (0)
#define PMIC_OCV_VOLTAGE1_v_ocv_data1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCV_CURRENT0_UNION
 结构说明  : OCV_CURRENT0 寄存器结构定义。地址偏移量:0x16F，初值:0x00，宽度:8
 寄存器说明: i_ocv_data[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_ocv_data0 : 8;  /* bit[0-7]: 开机时OCV电流采样值[15:0]。此值是原始值，未经过校准。 */
    } reg;
} PMIC_OCV_CURRENT0_UNION;
#endif
#define PMIC_OCV_CURRENT0_i_ocv_data0_START  (0)
#define PMIC_OCV_CURRENT0_i_ocv_data0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCV_CURRENT1_UNION
 结构说明  : OCV_CURRENT1 寄存器结构定义。地址偏移量:0x170，初值:0x00，宽度:8
 寄存器说明: i_ocv_data[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_ocv_data1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OCV_CURRENT1_UNION;
#endif
#define PMIC_OCV_CURRENT1_i_ocv_data1_START  (0)
#define PMIC_OCV_CURRENT1_i_ocv_data1_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLIN_0_UNION
 结构说明  : ECO_OUT_CLIN_0 寄存器结构定义。地址偏移量:0x171，初值:0x00，宽度:8
 寄存器说明: eco_out_clin[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin0 : 8;  /* bit[0-7]: 退出ECO模式流入电量计数器[13:0]。每次退出ECO模式自动记录当前流入电量，其余时刻保持。 */
    } reg;
} PMIC_ECO_OUT_CLIN_0_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_0_eco_out_clin0_START  (0)
#define PMIC_ECO_OUT_CLIN_0_eco_out_clin0_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLIN_1_UNION
 结构说明  : ECO_OUT_CLIN_1 寄存器结构定义。地址偏移量:0x172，初值:0x00，宽度:8
 寄存器说明: eco_out_clin[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_1_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_1_eco_out_clin1_START  (0)
#define PMIC_ECO_OUT_CLIN_1_eco_out_clin1_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLIN_2_UNION
 结构说明  : ECO_OUT_CLIN_2 寄存器结构定义。地址偏移量:0x173，初值:0x00，宽度:8
 寄存器说明: eco_out_clin[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_2_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_2_eco_out_clin2_START  (0)
#define PMIC_ECO_OUT_CLIN_2_eco_out_clin2_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLIN_3_UNION
 结构说明  : ECO_OUT_CLIN_3 寄存器结构定义。地址偏移量:0x174，初值:0x00，宽度:8
 寄存器说明: eco_out_clin[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_3_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_3_eco_out_clin3_START  (0)
#define PMIC_ECO_OUT_CLIN_3_eco_out_clin3_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLOUT_0_UNION
 结构说明  : ECO_OUT_CLOUT_0 寄存器结构定义。地址偏移量:0x175，初值:0x00，宽度:8
 寄存器说明: eco_out_clout[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout0 : 8;  /* bit[0-7]: 退出ECO模式流出电量计数器[31:0]。每次退出ECO模式自动记录当前流出电量，其余时刻保持。 */
    } reg;
} PMIC_ECO_OUT_CLOUT_0_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_0_eco_out_clout0_START  (0)
#define PMIC_ECO_OUT_CLOUT_0_eco_out_clout0_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLOUT_1_UNION
 结构说明  : ECO_OUT_CLOUT_1 寄存器结构定义。地址偏移量:0x176，初值:0x00，宽度:8
 寄存器说明: eco_out_clout[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_1_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_1_eco_out_clout1_START  (0)
#define PMIC_ECO_OUT_CLOUT_1_eco_out_clout1_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLOUT_2_UNION
 结构说明  : ECO_OUT_CLOUT_2 寄存器结构定义。地址偏移量:0x177，初值:0x00，宽度:8
 寄存器说明: eco_out_clout[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_2_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_2_eco_out_clout2_START  (0)
#define PMIC_ECO_OUT_CLOUT_2_eco_out_clout2_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLOUT_3_UNION
 结构说明  : ECO_OUT_CLOUT_3 寄存器结构定义。地址偏移量:0x178，初值:0x00，宽度:8
 寄存器说明: eco_out_clout[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_3_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_3_eco_out_clout3_START  (0)
#define PMIC_ECO_OUT_CLOUT_3_eco_out_clout3_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE0_UNION
 结构说明  : V_OUT0_PRE0 寄存器结构定义。地址偏移量:0x179，初值:0xFF，宽度:8
 寄存器说明: v_out_pre0[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre0 : 8;  /* bit[0-7]: 当前电池电压指示[15:0]，最高位代表符号位。 */
    } reg;
} PMIC_V_OUT0_PRE0_UNION;
#endif
#define PMIC_V_OUT0_PRE0_v_out0_pre0_START  (0)
#define PMIC_V_OUT0_PRE0_v_out0_pre0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE0_UNION
 结构说明  : V_OUT1_PRE0 寄存器结构定义。地址偏移量:0x17A，初值:0xFF，宽度:8
 寄存器说明: v_out_pre0[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre0 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE0_UNION;
#endif
#define PMIC_V_OUT1_PRE0_v_out1_pre0_START  (0)
#define PMIC_V_OUT1_PRE0_v_out1_pre0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE1_UNION
 结构说明  : V_OUT0_PRE1 寄存器结构定义。地址偏移量:0x17B，初值:0xFF，宽度:8
 寄存器说明: v_out_pre1[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre1 : 8;  /* bit[0-7]: 当前电压前一次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE1_UNION;
#endif
#define PMIC_V_OUT0_PRE1_v_out0_pre1_START  (0)
#define PMIC_V_OUT0_PRE1_v_out0_pre1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE1_UNION
 结构说明  : V_OUT1_PRE1 寄存器结构定义。地址偏移量:0x17C，初值:0xFF，宽度:8
 寄存器说明: v_out_pre1[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE1_UNION;
#endif
#define PMIC_V_OUT1_PRE1_v_out1_pre1_START  (0)
#define PMIC_V_OUT1_PRE1_v_out1_pre1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE2_UNION
 结构说明  : V_OUT0_PRE2 寄存器结构定义。地址偏移量:0x17D，初值:0xFF，宽度:8
 寄存器说明: v_out_pre2[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre2 : 8;  /* bit[0-7]: 当前电压前二次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE2_UNION;
#endif
#define PMIC_V_OUT0_PRE2_v_out0_pre2_START  (0)
#define PMIC_V_OUT0_PRE2_v_out0_pre2_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE2_UNION
 结构说明  : V_OUT1_PRE2 寄存器结构定义。地址偏移量:0x17E，初值:0xFF，宽度:8
 寄存器说明: v_out_pre2[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE2_UNION;
#endif
#define PMIC_V_OUT1_PRE2_v_out1_pre2_START  (0)
#define PMIC_V_OUT1_PRE2_v_out1_pre2_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE3_UNION
 结构说明  : V_OUT0_PRE3 寄存器结构定义。地址偏移量:0x17F，初值:0xFF，宽度:8
 寄存器说明: v_out_pre3[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre3 : 8;  /* bit[0-7]: 当前电压前三次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE3_UNION;
#endif
#define PMIC_V_OUT0_PRE3_v_out0_pre3_START  (0)
#define PMIC_V_OUT0_PRE3_v_out0_pre3_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE3_UNION
 结构说明  : V_OUT1_PRE3 寄存器结构定义。地址偏移量:0x180，初值:0xFF，宽度:8
 寄存器说明: v_out_pre3[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE3_UNION;
#endif
#define PMIC_V_OUT1_PRE3_v_out1_pre3_START  (0)
#define PMIC_V_OUT1_PRE3_v_out1_pre3_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE4_UNION
 结构说明  : V_OUT0_PRE4 寄存器结构定义。地址偏移量:0x181，初值:0xFF，宽度:8
 寄存器说明: v_out_pre4[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre4 : 8;  /* bit[0-7]: 当前电压前四次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE4_UNION;
#endif
#define PMIC_V_OUT0_PRE4_v_out0_pre4_START  (0)
#define PMIC_V_OUT0_PRE4_v_out0_pre4_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE4_UNION
 结构说明  : V_OUT1_PRE4 寄存器结构定义。地址偏移量:0x182，初值:0xFF，宽度:8
 寄存器说明: v_out_pre4[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre4 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE4_UNION;
#endif
#define PMIC_V_OUT1_PRE4_v_out1_pre4_START  (0)
#define PMIC_V_OUT1_PRE4_v_out1_pre4_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE5_UNION
 结构说明  : V_OUT0_PRE5 寄存器结构定义。地址偏移量:0x183，初值:0xFF，宽度:8
 寄存器说明: v_out_pre5[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre5 : 8;  /* bit[0-7]: 当前电压前五次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE5_UNION;
#endif
#define PMIC_V_OUT0_PRE5_v_out0_pre5_START  (0)
#define PMIC_V_OUT0_PRE5_v_out0_pre5_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE5_UNION
 结构说明  : V_OUT1_PRE5 寄存器结构定义。地址偏移量:0x184，初值:0xFF，宽度:8
 寄存器说明: v_out_pre5[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre5 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE5_UNION;
#endif
#define PMIC_V_OUT1_PRE5_v_out1_pre5_START  (0)
#define PMIC_V_OUT1_PRE5_v_out1_pre5_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE6_UNION
 结构说明  : V_OUT0_PRE6 寄存器结构定义。地址偏移量:0x185，初值:0xFF，宽度:8
 寄存器说明: v_out_pre6[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre6 : 8;  /* bit[0-7]: 当前电压前六次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE6_UNION;
#endif
#define PMIC_V_OUT0_PRE6_v_out0_pre6_START  (0)
#define PMIC_V_OUT0_PRE6_v_out0_pre6_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE6_UNION
 结构说明  : V_OUT1_PRE6 寄存器结构定义。地址偏移量:0x186，初值:0xFF，宽度:8
 寄存器说明: v_out_pre6[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre6 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE6_UNION;
#endif
#define PMIC_V_OUT1_PRE6_v_out1_pre6_START  (0)
#define PMIC_V_OUT1_PRE6_v_out1_pre6_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE7_UNION
 结构说明  : V_OUT0_PRE7 寄存器结构定义。地址偏移量:0x187，初值:0xFF，宽度:8
 寄存器说明: v_out_pre7[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre7 : 8;  /* bit[0-7]: 当前电压前七次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE7_UNION;
#endif
#define PMIC_V_OUT0_PRE7_v_out0_pre7_START  (0)
#define PMIC_V_OUT0_PRE7_v_out0_pre7_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE7_UNION
 结构说明  : V_OUT1_PRE7 寄存器结构定义。地址偏移量:0x188，初值:0xFF，宽度:8
 寄存器说明: v_out_pre7[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre7 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE7_UNION;
#endif
#define PMIC_V_OUT1_PRE7_v_out1_pre7_START  (0)
#define PMIC_V_OUT1_PRE7_v_out1_pre7_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE8_UNION
 结构说明  : V_OUT0_PRE8 寄存器结构定义。地址偏移量:0x189，初值:0xFF，宽度:8
 寄存器说明: v_out_pre8[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre8 : 8;  /* bit[0-7]: 当前电压前八次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE8_UNION;
#endif
#define PMIC_V_OUT0_PRE8_v_out0_pre8_START  (0)
#define PMIC_V_OUT0_PRE8_v_out0_pre8_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE8_UNION
 结构说明  : V_OUT1_PRE8 寄存器结构定义。地址偏移量:0x18A，初值:0xFF，宽度:8
 寄存器说明: v_out_pre8[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre8 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE8_UNION;
#endif
#define PMIC_V_OUT1_PRE8_v_out1_pre8_START  (0)
#define PMIC_V_OUT1_PRE8_v_out1_pre8_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE9_UNION
 结构说明  : V_OUT0_PRE9 寄存器结构定义。地址偏移量:0x18B，初值:0xFF，宽度:8
 寄存器说明: v_out_pre9[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out0_pre9 : 8;  /* bit[0-7]: 当前电压前九次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE9_UNION;
#endif
#define PMIC_V_OUT0_PRE9_v_out0_pre9_START  (0)
#define PMIC_V_OUT0_PRE9_v_out0_pre9_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE9_UNION
 结构说明  : V_OUT1_PRE9 寄存器结构定义。地址偏移量:0x18C，初值:0xFF，宽度:8
 寄存器说明: v_out_pre9[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out1_pre9 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE9_UNION;
#endif
#define PMIC_V_OUT1_PRE9_v_out1_pre9_START  (0)
#define PMIC_V_OUT1_PRE9_v_out1_pre9_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE0_UNION
 结构说明  : CURRENT0_PRE0 寄存器结构定义。地址偏移量:0x18D，初值:0x00，宽度:8
 寄存器说明: current_pre0[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre0 : 8;  /* bit[0-7]: 当前电流指示[15:0]，最高位代表符号位。 */
    } reg;
} PMIC_CURRENT0_PRE0_UNION;
#endif
#define PMIC_CURRENT0_PRE0_current0_pre0_START  (0)
#define PMIC_CURRENT0_PRE0_current0_pre0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE0_UNION
 结构说明  : CURRENT1_PRE0 寄存器结构定义。地址偏移量:0x18E，初值:0x00，宽度:8
 寄存器说明: current_pre0[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre0 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE0_UNION;
#endif
#define PMIC_CURRENT1_PRE0_current1_pre0_START  (0)
#define PMIC_CURRENT1_PRE0_current1_pre0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE1_UNION
 结构说明  : CURRENT0_PRE1 寄存器结构定义。地址偏移量:0x18F，初值:0x00，宽度:8
 寄存器说明: current_pre1[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre1 : 8;  /* bit[0-7]: 当前电流前一次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE1_UNION;
#endif
#define PMIC_CURRENT0_PRE1_current0_pre1_START  (0)
#define PMIC_CURRENT0_PRE1_current0_pre1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE1_UNION
 结构说明  : CURRENT1_PRE1 寄存器结构定义。地址偏移量:0x190，初值:0x00，宽度:8
 寄存器说明: current_pre1[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE1_UNION;
#endif
#define PMIC_CURRENT1_PRE1_current1_pre1_START  (0)
#define PMIC_CURRENT1_PRE1_current1_pre1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE2_UNION
 结构说明  : CURRENT0_PRE2 寄存器结构定义。地址偏移量:0x191，初值:0x00，宽度:8
 寄存器说明: current_pre2[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre2 : 8;  /* bit[0-7]: 当前电流前二次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE2_UNION;
#endif
#define PMIC_CURRENT0_PRE2_current0_pre2_START  (0)
#define PMIC_CURRENT0_PRE2_current0_pre2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE2_UNION
 结构说明  : CURRENT1_PRE2 寄存器结构定义。地址偏移量:0x192，初值:0x00，宽度:8
 寄存器说明: current_pre2[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE2_UNION;
#endif
#define PMIC_CURRENT1_PRE2_current1_pre2_START  (0)
#define PMIC_CURRENT1_PRE2_current1_pre2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE3_UNION
 结构说明  : CURRENT0_PRE3 寄存器结构定义。地址偏移量:0x193，初值:0x00，宽度:8
 寄存器说明: current_pre3[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre3 : 8;  /* bit[0-7]: 当前电流前三次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE3_UNION;
#endif
#define PMIC_CURRENT0_PRE3_current0_pre3_START  (0)
#define PMIC_CURRENT0_PRE3_current0_pre3_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE3_UNION
 结构说明  : CURRENT1_PRE3 寄存器结构定义。地址偏移量:0x194，初值:0x00，宽度:8
 寄存器说明: current_pre3[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE3_UNION;
#endif
#define PMIC_CURRENT1_PRE3_current1_pre3_START  (0)
#define PMIC_CURRENT1_PRE3_current1_pre3_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE4_UNION
 结构说明  : CURRENT0_PRE4 寄存器结构定义。地址偏移量:0x195，初值:0x00，宽度:8
 寄存器说明: current_pre4[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre4 : 8;  /* bit[0-7]: 当前电流前四次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE4_UNION;
#endif
#define PMIC_CURRENT0_PRE4_current0_pre4_START  (0)
#define PMIC_CURRENT0_PRE4_current0_pre4_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE4_UNION
 结构说明  : CURRENT1_PRE4 寄存器结构定义。地址偏移量:0x196，初值:0x00，宽度:8
 寄存器说明: current_pre4[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre4 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE4_UNION;
#endif
#define PMIC_CURRENT1_PRE4_current1_pre4_START  (0)
#define PMIC_CURRENT1_PRE4_current1_pre4_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE5_UNION
 结构说明  : CURRENT0_PRE5 寄存器结构定义。地址偏移量:0x197，初值:0x00，宽度:8
 寄存器说明: current_pre5[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre5 : 8;  /* bit[0-7]: 当前电流前五次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE5_UNION;
#endif
#define PMIC_CURRENT0_PRE5_current0_pre5_START  (0)
#define PMIC_CURRENT0_PRE5_current0_pre5_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE5_UNION
 结构说明  : CURRENT1_PRE5 寄存器结构定义。地址偏移量:0x198，初值:0x00，宽度:8
 寄存器说明: current_pre5[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre5 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE5_UNION;
#endif
#define PMIC_CURRENT1_PRE5_current1_pre5_START  (0)
#define PMIC_CURRENT1_PRE5_current1_pre5_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE6_UNION
 结构说明  : CURRENT0_PRE6 寄存器结构定义。地址偏移量:0x199，初值:0x00，宽度:8
 寄存器说明: current_pre6[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre6 : 8;  /* bit[0-7]: 当前电流前六次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE6_UNION;
#endif
#define PMIC_CURRENT0_PRE6_current0_pre6_START  (0)
#define PMIC_CURRENT0_PRE6_current0_pre6_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE6_UNION
 结构说明  : CURRENT1_PRE6 寄存器结构定义。地址偏移量:0x19A，初值:0x00，宽度:8
 寄存器说明: current_pre6[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre6 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE6_UNION;
#endif
#define PMIC_CURRENT1_PRE6_current1_pre6_START  (0)
#define PMIC_CURRENT1_PRE6_current1_pre6_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE7_UNION
 结构说明  : CURRENT0_PRE7 寄存器结构定义。地址偏移量:0x19B，初值:0x00，宽度:8
 寄存器说明: current_pre7[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre7 : 8;  /* bit[0-7]: 当前电流前七次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE7_UNION;
#endif
#define PMIC_CURRENT0_PRE7_current0_pre7_START  (0)
#define PMIC_CURRENT0_PRE7_current0_pre7_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE7_UNION
 结构说明  : CURRENT1_PRE7 寄存器结构定义。地址偏移量:0x19C，初值:0x00，宽度:8
 寄存器说明: current_pre7[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre7 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE7_UNION;
#endif
#define PMIC_CURRENT1_PRE7_current1_pre7_START  (0)
#define PMIC_CURRENT1_PRE7_current1_pre7_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE8_UNION
 结构说明  : CURRENT0_PRE8 寄存器结构定义。地址偏移量:0x19D，初值:0x00，宽度:8
 寄存器说明: current_pre8[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre8 : 8;  /* bit[0-7]: 当前电流前八次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE8_UNION;
#endif
#define PMIC_CURRENT0_PRE8_current0_pre8_START  (0)
#define PMIC_CURRENT0_PRE8_current0_pre8_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE8_UNION
 结构说明  : CURRENT1_PRE8 寄存器结构定义。地址偏移量:0x19E，初值:0x00，宽度:8
 寄存器说明: current_pre8[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre8 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE8_UNION;
#endif
#define PMIC_CURRENT1_PRE8_current1_pre8_START  (0)
#define PMIC_CURRENT1_PRE8_current1_pre8_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE9_UNION
 结构说明  : CURRENT0_PRE9 寄存器结构定义。地址偏移量:0x19F，初值:0x00，宽度:8
 寄存器说明: current_pre9[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current0_pre9 : 8;  /* bit[0-7]: 当前电流前九次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE9_UNION;
#endif
#define PMIC_CURRENT0_PRE9_current0_pre9_START  (0)
#define PMIC_CURRENT0_PRE9_current0_pre9_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE9_UNION
 结构说明  : CURRENT1_PRE9 寄存器结构定义。地址偏移量:0x1A0，初值:0x00，宽度:8
 寄存器说明: current_pre9[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current1_pre9 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE9_UNION;
#endif
#define PMIC_CURRENT1_PRE9_current1_pre9_START  (0)
#define PMIC_CURRENT1_PRE9_current1_pre9_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_CURRENT_MOD_0_UNION
 结构说明  : OFFSET_CURRENT_MOD_0 寄存器结构定义。地址偏移量:0x1A1，初值:0x00，宽度:8
 寄存器说明: 电流偏置调整[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_mod_0 : 8;  /* bit[0-7]: 电流偏置调整。
                                                               （先写低8bit，再写高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_OFFSET_CURRENT_MOD_0_UNION;
#endif
#define PMIC_OFFSET_CURRENT_MOD_0_offset_current_mod_0_START  (0)
#define PMIC_OFFSET_CURRENT_MOD_0_offset_current_mod_0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_CURRENT_MOD_1_UNION
 结构说明  : OFFSET_CURRENT_MOD_1 寄存器结构定义。地址偏移量:0x1A2，初值:0x00，宽度:8
 寄存器说明: 电流偏置调整[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_mod_1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_CURRENT_MOD_1_UNION;
#endif
#define PMIC_OFFSET_CURRENT_MOD_1_offset_current_mod_1_START  (0)
#define PMIC_OFFSET_CURRENT_MOD_1_offset_current_mod_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_VOLTAGE_MOD_0_UNION
 结构说明  : OFFSET_VOLTAGE_MOD_0 寄存器结构定义。地址偏移量:0x1A3，初值:0x00，宽度:8
 寄存器说明: 电压偏置调整[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_mod_0 : 8;  /* bit[0-7]: 电压偏置调整。
                                                               （先写低8bit，再写高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_OFFSET_VOLTAGE_MOD_0_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE_MOD_0_offset_voltage_mod_0_START  (0)
#define PMIC_OFFSET_VOLTAGE_MOD_0_offset_voltage_mod_0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_VOLTAGE_MOD_1_UNION
 结构说明  : OFFSET_VOLTAGE_MOD_1 寄存器结构定义。地址偏移量:0x1A4，初值:0x00，宽度:8
 寄存器说明: 电压偏置调整[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_mod_1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_VOLTAGE_MOD_1_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE_MOD_1_offset_voltage_mod_1_START  (0)
#define PMIC_OFFSET_VOLTAGE_MOD_1_offset_voltage_mod_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED1_UNION
 结构说明  : CLJ_RESERVED1 寄存器结构定义。地址偏移量:0x1A5，初值:0x00，宽度:8
 寄存器说明: 库仑计保留1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_rw_inf1 : 8;  /* bit[0-7]: 产品软件专用，对库仑计可维可测，仅用于记录数据，不对库仑计状态产生任何作用。 */
    } reg;
} PMIC_CLJ_RESERVED1_UNION;
#endif
#define PMIC_CLJ_RESERVED1_clj_rw_inf1_START  (0)
#define PMIC_CLJ_RESERVED1_clj_rw_inf1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED2_UNION
 结构说明  : CLJ_RESERVED2 寄存器结构定义。地址偏移量:0x1A6，初值:0x00，宽度:8
 寄存器说明: 库仑计保留2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_rw_inf2 : 8;  /* bit[0-7]: 产品软件专用，对库仑计可维可测，仅用于记录数据，不对库仑计状态产生任何作用。 */
    } reg;
} PMIC_CLJ_RESERVED2_UNION;
#endif
#define PMIC_CLJ_RESERVED2_clj_rw_inf2_START  (0)
#define PMIC_CLJ_RESERVED2_clj_rw_inf2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED3_UNION
 结构说明  : CLJ_RESERVED3 寄存器结构定义。地址偏移量:0x1A7，初值:0x00，宽度:8
 寄存器说明: 库仑计保留3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_rw_inf3 : 8;  /* bit[0-7]: 产品软件专用，对库仑计可维可测，仅用于记录数据，不对库仑计状态产生任何作用。 */
    } reg;
} PMIC_CLJ_RESERVED3_UNION;
#endif
#define PMIC_CLJ_RESERVED3_clj_rw_inf3_START  (0)
#define PMIC_CLJ_RESERVED3_clj_rw_inf3_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED4_UNION
 结构说明  : CLJ_RESERVED4 寄存器结构定义。地址偏移量:0x1A8，初值:0x00，宽度:8
 寄存器说明: 库仑计保留4寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_rw_inf4 : 8;  /* bit[0-7]: 产品软件专用，对库仑计可维可测，仅用于记录数据，不对库仑计状态产生任何作用。 */
    } reg;
} PMIC_CLJ_RESERVED4_UNION;
#endif
#define PMIC_CLJ_RESERVED4_clj_rw_inf4_START  (0)
#define PMIC_CLJ_RESERVED4_clj_rw_inf4_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED5_UNION
 结构说明  : CLJ_RESERVED5 寄存器结构定义。地址偏移量:0x1A9，初值:0x00，宽度:8
 寄存器说明: 库仑计保留5寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_reserve_1 : 8;  /* bit[0-7]: 库仑计模拟寄存器保留。 */
    } reg;
} PMIC_CLJ_RESERVED5_UNION;
#endif
#define PMIC_CLJ_RESERVED5_i_reserve_1_START  (0)
#define PMIC_CLJ_RESERVED5_i_reserve_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED6_UNION
 结构说明  : CLJ_RESERVED6 寄存器结构定义。地址偏移量:0x1AA，初值:0x00，宽度:8
 寄存器说明: 库仑计保留6寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_reserve_2 : 8;  /* bit[0-7]: 库仑计模拟寄存器保留。 */
    } reg;
} PMIC_CLJ_RESERVED6_UNION;
#endif
#define PMIC_CLJ_RESERVED6_i_reserve_2_START  (0)
#define PMIC_CLJ_RESERVED6_i_reserve_2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED7_UNION
 结构说明  : CLJ_RESERVED7 寄存器结构定义。地址偏移量:0x1AB，初值:0x00，宽度:8
 寄存器说明: 库仑计保留7寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_reserve_1 : 8;  /* bit[0-7]: 库仑计模拟寄存器保留。 */
    } reg;
} PMIC_CLJ_RESERVED7_UNION;
#endif
#define PMIC_CLJ_RESERVED7_v_reserve_1_START  (0)
#define PMIC_CLJ_RESERVED7_v_reserve_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_PMU_SOFT_RST_UNION
 结构说明  : PMU_SOFT_RST 寄存器结构定义。地址偏移量:0x1AC，初值:0x00，宽度:8
 寄存器说明: PMU软复位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_rst_n : 8;  /* bit[0-7]: 库仑计软复位：
                                                     0x11:复位库仑计模块；
                                                     0x1F:解除库仑计模块复位。
                                                     写入其他无效。
                                                     
                                                     CODEC模块软复位：
                                                     0x22:复位CODEC模块；
                                                     0x2F:解除CODEC模块复位。
                                                     写入其他无效。
                                                     
                                                     DCXO模式时钟校准软复位。
                                                     0x33:复位DCXO模式；
                                                     0x3F:解除DCXO模式复位。
                                                     写入其他无效。 */
    } reg;
} PMIC_PMU_SOFT_RST_UNION;
#endif
#define PMIC_PMU_SOFT_RST_soft_rst_n_START  (0)
#define PMIC_PMU_SOFT_RST_soft_rst_n_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_DEBUG_UNION
 结构说明  : CLJ_DEBUG 寄存器结构定义。地址偏移量:0x1AD，初值:0x00，宽度:8
 寄存器说明: 库仑计DEBUG专用1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cic_clk_inv_i    : 1;  /* bit[0]: 控制库仑计电流滤波电路第一级取反时钟。
                                                         0：无效；
                                                         1：有效。 */
        unsigned char  cic_clk_inv_v    : 1;  /* bit[1]: 控制库仑计电压滤波电路第一级取反时钟。
                                                         0：无效；
                                                         1：有效。 */
        unsigned char  adc_ana_v_output : 1;  /* bit[2]: 复用CK32_BT管脚，电压ADC模拟输出。 */
        unsigned char  adc_ana_i_output : 1;  /* bit[3]: 复用CK32_GPS管脚，电流ADC模拟输出。 */
        unsigned char  cali_en_i        : 1;  /* bit[4]: 电流检测是否校准选择。
                                                         0：保持正常；
                                                         1：电流始终不进行检测校准。 */
        unsigned char  cali_en_i_force  : 1;  /* bit[5]: 电流校准选择。
                                                         0：电流不强制校准；
                                                         1：电流强制校准。
                                                         以上功能均在clj_debug[4]=0时候作用。 */
        unsigned char  cali_en_v_force  : 1;  /* bit[6]: 电压校准选择。
                                                         0：电压不强制校准；
                                                         1：电压强制校准。
                                                         以上功能均在clj_debug[7]=0时候作用。 */
        unsigned char  cali_en_v        : 1;  /* bit[7]: 电压检测是否校准选择。
                                                         0：保持正常；
                                                         1：电压检测始终不进行校准。 */
    } reg;
} PMIC_CLJ_DEBUG_UNION;
#endif
#define PMIC_CLJ_DEBUG_cic_clk_inv_i_START     (0)
#define PMIC_CLJ_DEBUG_cic_clk_inv_i_END       (0)
#define PMIC_CLJ_DEBUG_cic_clk_inv_v_START     (1)
#define PMIC_CLJ_DEBUG_cic_clk_inv_v_END       (1)
#define PMIC_CLJ_DEBUG_adc_ana_v_output_START  (2)
#define PMIC_CLJ_DEBUG_adc_ana_v_output_END    (2)
#define PMIC_CLJ_DEBUG_adc_ana_i_output_START  (3)
#define PMIC_CLJ_DEBUG_adc_ana_i_output_END    (3)
#define PMIC_CLJ_DEBUG_cali_en_i_START         (4)
#define PMIC_CLJ_DEBUG_cali_en_i_END           (4)
#define PMIC_CLJ_DEBUG_cali_en_i_force_START   (5)
#define PMIC_CLJ_DEBUG_cali_en_i_force_END     (5)
#define PMIC_CLJ_DEBUG_cali_en_v_force_START   (6)
#define PMIC_CLJ_DEBUG_cali_en_v_force_END     (6)
#define PMIC_CLJ_DEBUG_cali_en_v_START         (7)
#define PMIC_CLJ_DEBUG_cali_en_v_END           (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_DEBUG_2_UNION
 结构说明  : CLJ_DEBUG_2 寄存器结构定义。地址偏移量:0x1AE，初值:0x00，宽度:8
 寄存器说明: 库仑计DEBUG专用2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_coul_always_off : 1;  /* bit[0]  : 电流计常关控制。
                                                                  0：正常功能；
                                                                  1：电流计常关。
                                                                  默认为1'b0。 */
        unsigned char  voltage_coul_always_off : 1;  /* bit[1]  : 电压计常关控制。
                                                                  0：正常功能；
                                                                  1：电压计常关。
                                                                  默认为1'b0。 */
        unsigned char  coul_gate_clk_en        : 1;  /* bit[2]  : 库仑计门控时钟使能。
                                                                  0：开启门控使能；
                                                                  1：关闭门控使能。
                                                                  默认为1'b0。 */
        unsigned char  reg_data_clr            : 1;  /* bit[3]  : 20组寄存器（电流，电压）检测值恢复初始值设置。
                                                                  0：不恢复初始值；
                                                                  1：恢复初始值。(写1自动清零) */
        unsigned char  reserved                : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_CLJ_DEBUG_2_UNION;
#endif
#define PMIC_CLJ_DEBUG_2_current_coul_always_off_START  (0)
#define PMIC_CLJ_DEBUG_2_current_coul_always_off_END    (0)
#define PMIC_CLJ_DEBUG_2_voltage_coul_always_off_START  (1)
#define PMIC_CLJ_DEBUG_2_voltage_coul_always_off_END    (1)
#define PMIC_CLJ_DEBUG_2_coul_gate_clk_en_START         (2)
#define PMIC_CLJ_DEBUG_2_coul_gate_clk_en_END           (2)
#define PMIC_CLJ_DEBUG_2_reg_data_clr_START             (3)
#define PMIC_CLJ_DEBUG_2_reg_data_clr_END               (3)


/*****************************************************************************
 结构名    : PMIC_STATE_TEST_UNION
 结构说明  : STATE_TEST 寄存器结构定义。地址偏移量:0x1AF，初值:0x00，宽度:8
 寄存器说明: 库仑计DEBUG专用3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  state_test : 3;  /* bit[0-2]: bit[2:0]表示电压电流跳转状态。
                                                     000：CLJ_OFF(库仑计关闭状态)；
                                                     001：CLJ_ON(库仑计开启状态)；
                                                     010：OCV_DETE(库仑计ocv电压采样状态)；
                                                     011：CALIBRATION(库仑计自动校准状态)；
                                                     100：NORMAL_FUNC(库仑计正常工作状态)；
                                                     101：ECO_REFLASH(库仑计进入低功耗前一拍状态)；
                                                     110：ECO_POWER_OFF(库仑计进入低功耗状态)；
                                                     111：WAITTING(库仑计退出低功耗后一拍状态)。” */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_STATE_TEST_UNION;
#endif
#define PMIC_STATE_TEST_state_test_START  (0)
#define PMIC_STATE_TEST_state_test_END    (2)


/*****************************************************************************
 结构名    : PMIC_COUL_RESERVE_UNION
 结构说明  : COUL_RESERVE 寄存器结构定义。地址偏移量:0x1B0，初值:0x00，宽度:8
 寄存器说明: 库仑计数模接口预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  coul_reserve : 8;  /* bit[0-7]: 数模接口预留寄存器。 */
    } reg;
} PMIC_COUL_RESERVE_UNION;
#endif
#define PMIC_COUL_RESERVE_coul_reserve_START  (0)
#define PMIC_COUL_RESERVE_coul_reserve_END    (7)


/*****************************************************************************
 结构名    : PMIC_SOFT_RESERE0_UNION
 结构说明  : SOFT_RESERE0 寄存器结构定义。地址偏移量:0x1B1，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve0 : 8;  /* bit[0-7]: 临终遗言寄存器。 */
    } reg;
} PMIC_SOFT_RESERE0_UNION;
#endif
#define PMIC_SOFT_RESERE0_soft_reserve0_START  (0)
#define PMIC_SOFT_RESERE0_soft_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_SOFT_RESERE1_UNION
 结构说明  : SOFT_RESERE1 寄存器结构定义。地址偏移量:0x1B2，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve1 : 8;  /* bit[0-7]: 临终遗言寄存器。 */
    } reg;
} PMIC_SOFT_RESERE1_UNION;
#endif
#define PMIC_SOFT_RESERE1_soft_reserve1_START  (0)
#define PMIC_SOFT_RESERE1_soft_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_SOFT_RESERE2_UNION
 结构说明  : SOFT_RESERE2 寄存器结构定义。地址偏移量:0x1B3，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve2 : 8;  /* bit[0-7]: 临终遗言寄存器。 */
    } reg;
} PMIC_SOFT_RESERE2_UNION;
#endif
#define PMIC_SOFT_RESERE2_soft_reserve2_START  (0)
#define PMIC_SOFT_RESERE2_soft_reserve2_END    (7)


/*****************************************************************************
 结构名    : PMIC_SOFT_RESERE3_UNION
 结构说明  : SOFT_RESERE3 寄存器结构定义。地址偏移量:0x1B4，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve3 : 8;  /* bit[0-7]: 临终遗言寄存器。 */
    } reg;
} PMIC_SOFT_RESERE3_UNION;
#endif
#define PMIC_SOFT_RESERE3_soft_reserve3_START  (0)
#define PMIC_SOFT_RESERE3_soft_reserve3_END    (7)


/*****************************************************************************
 结构名    : PMIC_SOFT_RESERE4_UNION
 结构说明  : SOFT_RESERE4 寄存器结构定义。地址偏移量:0x1B5，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve4 : 8;  /* bit[0-7]: 临终遗言寄存器。 */
    } reg;
} PMIC_SOFT_RESERE4_UNION;
#endif
#define PMIC_SOFT_RESERE4_soft_reserve4_START  (0)
#define PMIC_SOFT_RESERE4_soft_reserve4_END    (7)


/*****************************************************************************
 结构名    : PMIC_SOFT_RESERE5_UNION
 结构说明  : SOFT_RESERE5 寄存器结构定义。地址偏移量:0x1B6，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve5 : 8;  /* bit[0-7]: 临终遗言寄存器。 */
    } reg;
} PMIC_SOFT_RESERE5_UNION;
#endif
#define PMIC_SOFT_RESERE5_soft_reserve5_START  (0)
#define PMIC_SOFT_RESERE5_soft_reserve5_END    (7)


/*****************************************************************************
 结构名    : PMIC_SOFT_RESERE6_UNION
 结构说明  : SOFT_RESERE6 寄存器结构定义。地址偏移量:0x1B7，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve6 : 8;  /* bit[0-7]: 临终遗言寄存器。 */
    } reg;
} PMIC_SOFT_RESERE6_UNION;
#endif
#define PMIC_SOFT_RESERE6_soft_reserve6_START  (0)
#define PMIC_SOFT_RESERE6_soft_reserve6_END    (7)


/*****************************************************************************
 结构名    : PMIC_SOFT_RESERE7_UNION
 结构说明  : SOFT_RESERE7 寄存器结构定义。地址偏移量:0x1B8，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_reserve7 : 8;  /* bit[0-7]: 临终遗言寄存器。 */
    } reg;
} PMIC_SOFT_RESERE7_UNION;
#endif
#define PMIC_SOFT_RESERE7_soft_reserve7_START  (0)
#define PMIC_SOFT_RESERE7_soft_reserve7_END    (7)




/****************************************************************************
                     (5/5) HKADC
 ****************************************************************************/
/*****************************************************************************
 结构名    : PMIC_ADC_CTRL_UNION
 结构说明  : ADC_CTRL 寄存器结构定义。地址偏移量:0x00，初值:0x80，宽度:8
 寄存器说明: ADC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_chanl_sel : 5;  /* bit[0-4]: HKADC工作通道选择寄存器。
                                                          00000：HKADC_IN0；
                                                          00001：HKADC_IN1；
                                                          00010：HKADC_IN2；
                                                          00011：HKADC_IN3；
                                                          ……
                                                          01100：HKADC_IN12；
                                                          01101：HKADC_IN13；
                                                          01110：HKADC_IN14（VSYS内部通道）；
                                                          01111：HKADC_IN15（hkadc的内部校准通道，0.125v，255输出码）；
                                                          10000：HKADC_IN16（hkadc内部校准通道，测试用)
                                                          10001：HKADC_IN17（hkadc内部校准通道，测试用）
                                                          10010：保留；
                                                          ……
                                                          11111：保留。 */
        unsigned char  hkadc_fre_sel   : 2;  /* bit[5-6]: HKADC转换速率选择寄存器。
                                                          00：100kHz；
                                                          01：50kHz；
                                                          10：20kHz；
                                                          11：10kHz。 */
        unsigned char  hkadc_bapass    : 1;  /* bit[7]  : HKADC Bypass寄存器。
                                                          0：HKADC正常工作；
                                                          1：HKADC关闭。 */
    } reg;
} PMIC_ADC_CTRL_UNION;
#endif
#define PMIC_ADC_CTRL_hkadc_chanl_sel_START  (0)
#define PMIC_ADC_CTRL_hkadc_chanl_sel_END    (4)
#define PMIC_ADC_CTRL_hkadc_fre_sel_START    (5)
#define PMIC_ADC_CTRL_hkadc_fre_sel_END      (6)
#define PMIC_ADC_CTRL_hkadc_bapass_START     (7)
#define PMIC_ADC_CTRL_hkadc_bapass_END       (7)


/*****************************************************************************
 结构名    : PMIC_ADC_START_UNION
 结构说明  : ADC_START 寄存器结构定义。地址偏移量:0x01，初值:0x00，宽度:8
 寄存器说明: ADC转换开始寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_start : 1;  /* bit[0]  : 上升沿触发一次数据转换，启动转换完成后，HKADC自动清零该寄存器。  */
        unsigned char  reserved    : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_ADC_START_UNION;
#endif
#define PMIC_ADC_START_hkadc_start_START  (0)
#define PMIC_ADC_START_hkadc_start_END    (0)


/*****************************************************************************
 结构名    : PMIC_CONV_STATUS_UNION
 结构说明  : CONV_STATUS 寄存器结构定义。地址偏移量:0x02，初值:0x00，宽度:8
 寄存器说明: ADC转换状态指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_valid : 1;  /* bit[0]  : HKADC状态位。
                                                      0：转换过程中；
                                                      1：转换完毕。
                                                      (注：该bit在转换开始时，被拉低；在转换结束后，变成“1”，并且“1”一直持续到下一次转换开始)。 */
        unsigned char  reserved    : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_CONV_STATUS_UNION;
#endif
#define PMIC_CONV_STATUS_hkadc_valid_START  (0)
#define PMIC_CONV_STATUS_hkadc_valid_END    (0)


/*****************************************************************************
 结构名    : PMIC_ADC_DATA1_UNION
 结构说明  : ADC_DATA1 寄存器结构定义。地址偏移量:0x03，初值:0x00，宽度:8
 寄存器说明: ADC结果高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_data11_4 : 8;  /* bit[0-7]: 转换结果的高8位bit[11:4]。 */
    } reg;
} PMIC_ADC_DATA1_UNION;
#endif
#define PMIC_ADC_DATA1_hkadc_data11_4_START  (0)
#define PMIC_ADC_DATA1_hkadc_data11_4_END    (7)


/*****************************************************************************
 结构名    : PMIC_ADC_DATA0_UNION
 结构说明  : ADC_DATA0 寄存器结构定义。地址偏移量:0x04，初值:0x00，宽度:8
 寄存器说明: ADC结果低位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved      : 4;  /* bit[0-3]: 保留。 */
        unsigned char  hkadc_data3_0 : 4;  /* bit[4-7]: 转换结果的低4位bit[3:0]。 */
    } reg;
} PMIC_ADC_DATA0_UNION;
#endif
#define PMIC_ADC_DATA0_hkadc_data3_0_START  (4)
#define PMIC_ADC_DATA0_hkadc_data3_0_END    (7)


/*****************************************************************************
 结构名    : PMIC_ADC_CONV_UNION
 结构说明  : ADC_CONV 寄存器结构定义。地址偏移量:0x05，初值:0x00，宽度:8
 寄存器说明: ADC转换使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_buffer_sel : 1;  /* bit[0]  : HKADC采样通道buffer选通寄存器。
                                                           0：选择通道buffer选通状态；
                                                           1：不开启通道buffer。 */
        unsigned char  hkadc_config     : 6;  /* bit[1-6]: 保留。 */
        unsigned char  reserved         : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_ADC_CONV_UNION;
#endif
#define PMIC_ADC_CONV_hkadc_buffer_sel_START  (0)
#define PMIC_ADC_CONV_hkadc_buffer_sel_END    (0)
#define PMIC_ADC_CONV_hkadc_config_START      (1)
#define PMIC_ADC_CONV_hkadc_config_END        (6)


/*****************************************************************************
 结构名    : PMIC_ADC_CURRENT_UNION
 结构说明  : ADC_CURRENT 寄存器结构定义。地址偏移量:0x06，初值:0x00，宽度:8
 寄存器说明: ADCibas电流配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_ibias_sel : 8;  /* bit[0-7]: bit[7:6]：hkadc_comp bias选择寄存器。
                                                          00：4uA；
                                                          01：3uA；
                                                          10：2uA；
                                                          11：1uA。
                                                          bit[5:3]：备用。
                                                          bit[2:0]：hkadc_input buffer bias选择寄存器。
                                                          000：1.25u
                                                          001：1.75u；
                                                          010：0.75u；
                                                          011：1.25u；
                                                          100：1.00u；
                                                          101：1.50u；
                                                          110：0.50u；
                                                          111：1.00u。 */
    } reg;
} PMIC_ADC_CURRENT_UNION;
#endif
#define PMIC_ADC_CURRENT_hkadc_ibias_sel_START  (0)
#define PMIC_ADC_CURRENT_hkadc_ibias_sel_END    (7)


/*****************************************************************************
 结构名    : PMIC_ADC_CALI_CTRL_UNION
 结构说明  : ADC_CALI_CTRL 寄存器结构定义。地址偏移量:0x07，初值:0x00，宽度:8
 寄存器说明: ADC校准配置控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_cali_en  : 1;  /* bit[0]  : HKADC 校准使能。
                                                         0：HKADC校准关闭；
                                                         1：HKADC校准开启。
                                                         默认为0。 */
        unsigned char  hkadc_cali_sel : 1;  /* bit[1]  : HKADC校准值选择使能。
                                                         0：校准电路校准值；
                                                         1：软件配置校准值。 */
        unsigned char  reserved       : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_ADC_CALI_CTRL_UNION;
#endif
#define PMIC_ADC_CALI_CTRL_hkadc_cali_en_START   (0)
#define PMIC_ADC_CALI_CTRL_hkadc_cali_en_END     (0)
#define PMIC_ADC_CALI_CTRL_hkadc_cali_sel_START  (1)
#define PMIC_ADC_CALI_CTRL_hkadc_cali_sel_END    (1)


/*****************************************************************************
 结构名    : PMIC_ADC_CALI_VALUE_UNION
 结构说明  : ADC_CALI_VALUE 寄存器结构定义。地址偏移量:0x08，初值:0x00，宽度:8
 寄存器说明: ADC校准值寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_cali_data : 8;  /* bit[0-7]: HKADC电路校准值。 */
    } reg;
} PMIC_ADC_CALI_VALUE_UNION;
#endif
#define PMIC_ADC_CALI_VALUE_hkadc_cali_data_START  (0)
#define PMIC_ADC_CALI_VALUE_hkadc_cali_data_END    (7)


/*****************************************************************************
 结构名    : PMIC_ADC_CALI_CFG_UNION
 结构说明  : ADC_CALI_CFG 寄存器结构定义。地址偏移量:0x09，初值:0x00，宽度:8
 寄存器说明: ADC校准配置值寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_cali_cfg : 8;  /* bit[0-7]: HKADC软件配置校准值。 */
    } reg;
} PMIC_ADC_CALI_CFG_UNION;
#endif
#define PMIC_ADC_CALI_CFG_hkadc_cali_cfg_START  (0)
#define PMIC_ADC_CALI_CFG_hkadc_cali_cfg_END    (7)


/*****************************************************************************
 结构名    : PMIC_ADC_RSV0_UNION
 结构说明  : ADC_RSV0 寄存器结构定义。地址偏移量:0x0A，初值:0x00，宽度:8
 寄存器说明: HKADC预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_reserve0 : 8;  /* bit[0-7]: 保留。 */
    } reg;
} PMIC_ADC_RSV0_UNION;
#endif
#define PMIC_ADC_RSV0_hkadc_reserve0_START  (0)
#define PMIC_ADC_RSV0_hkadc_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_ADC_RSV1_UNION
 结构说明  : ADC_RSV1 寄存器结构定义。地址偏移量:0x0B，初值:0x00，宽度:8
 寄存器说明: HKADC预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_reserve1 : 8;  /* bit[0-7]: 保留。 */
    } reg;
} PMIC_ADC_RSV1_UNION;
#endif
#define PMIC_ADC_RSV1_hkadc_reserve1_START  (0)
#define PMIC_ADC_RSV1_hkadc_reserve1_END    (7)






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

#endif /* end of pmic_interface.h */
