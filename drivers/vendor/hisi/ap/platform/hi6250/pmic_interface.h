

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
   位域定义UNION结构:  PMIC_NP_D2A_RES0_UNION */
#define PMIC_NP_D2A_RES0_ADDR(base)               ((base) + (0x00A))

/* 寄存器说明：数模接口保留寄存器1。
   位域定义UNION结构:  PMIC_NP_D2A_RES1_UNION */
#define PMIC_NP_D2A_RES1_ADDR(base)               ((base) + (0x00B))

/* 寄存器说明：数模接口保留寄存器2。
   位域定义UNION结构:  PMIC_D2A_RES0_UNION */
#define PMIC_D2A_RES0_ADDR(base)                  ((base) + (0x00C))

/* 寄存器说明：数模接口保留寄存器3。
   位域定义UNION结构:  PMIC_D2A_RES1_UNION */
#define PMIC_D2A_RES1_ADDR(base)                  ((base) + (0x00D))

/* 寄存器说明：数模接口保留寄存器4。
   位域定义UNION结构:  PMIC_A2D_RES0_UNION */
#define PMIC_A2D_RES0_ADDR(base)                  ((base) + (0x00E))

/* 寄存器说明：数模接口保留寄存器5。
   位域定义UNION结构:  PMIC_A2D_RES1_UNION */
#define PMIC_A2D_RES1_ADDR(base)                  ((base) + (0x00F))

/* 寄存器说明：BUCK0开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_BUCK0_ONOFF_ECO_UNION */
#define PMIC_BUCK0_ONOFF_ECO_ADDR(base)           ((base) + (0x010))

/* 寄存器说明：BUCK1开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_BUCK1_ONOFF_ECO_UNION */
#define PMIC_BUCK1_ONOFF_ECO_ADDR(base)           ((base) + (0x011))

/* 寄存器说明：BUCK2开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_BUCK2_ONOFF_ECO_UNION */
#define PMIC_BUCK2_ONOFF_ECO_ADDR(base)           ((base) + (0x012))

/* 寄存器说明：BUCK3开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_BUCK3_ONOFF_ECO_UNION */
#define PMIC_BUCK3_ONOFF_ECO_ADDR(base)           ((base) + (0x013))

/* 寄存器说明：LDO0_1开关使能寄存器。
   位域定义UNION结构:  PMIC_LDO0_1_ONOFF_UNION */
#define PMIC_LDO0_1_ONOFF_ADDR(base)              ((base) + (0x014))

/* 寄存器说明：LDO0_2开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO0_2_ONOFF_ECO_UNION */
#define PMIC_LDO0_2_ONOFF_ECO_ADDR(base)          ((base) + (0x015))

/* 寄存器说明：LDO1开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO1_ONOFF_ECO_UNION */
#define PMIC_LDO1_ONOFF_ECO_ADDR(base)            ((base) + (0x016))

/* 寄存器说明：LDO2开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO2_ONOFF_ECO_UNION */
#define PMIC_LDO2_ONOFF_ECO_ADDR(base)            ((base) + (0x017))

/* 寄存器说明：LDO3开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO3_ONOFF_ECO_UNION */
#define PMIC_LDO3_ONOFF_ECO_ADDR(base)            ((base) + (0x018))

/* 寄存器说明：LDO4开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO4_ONOFF_ECO_UNION */
#define PMIC_LDO4_ONOFF_ECO_ADDR(base)            ((base) + (0x019))

/* 寄存器说明：LDO5开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO5_ONOFF_ECO_UNION */
#define PMIC_LDO5_ONOFF_ECO_ADDR(base)            ((base) + (0x01A))

/* 寄存器说明：LDO7开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO7_ONOFF_ECO_UNION */
#define PMIC_LDO7_ONOFF_ECO_ADDR(base)            ((base) + (0x01B))

/* 寄存器说明：LDO8开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO8_ONOFF_ECO_UNION */
#define PMIC_LDO8_ONOFF_ECO_ADDR(base)            ((base) + (0x01C))

/* 寄存器说明：LDO9开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO9_ONOFF_ECO_UNION */
#define PMIC_LDO9_ONOFF_ECO_ADDR(base)            ((base) + (0x01D))

/* 寄存器说明：LDO10开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO10_ONOFF_ECO_UNION */
#define PMIC_LDO10_ONOFF_ECO_ADDR(base)           ((base) + (0x01E))

/* 寄存器说明：LDO11开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO11_ONOFF_ECO_UNION */
#define PMIC_LDO11_ONOFF_ECO_ADDR(base)           ((base) + (0x01F))

/* 寄存器说明：LDO12开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO12_ONOFF_ECO_UNION */
#define PMIC_LDO12_ONOFF_ECO_ADDR(base)           ((base) + (0x020))

/* 寄存器说明：LDO13开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO13_ONOFF_ECO_UNION */
#define PMIC_LDO13_ONOFF_ECO_ADDR(base)           ((base) + (0x021))

/* 寄存器说明：LDO14开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO14_ONOFF_ECO_UNION */
#define PMIC_LDO14_ONOFF_ECO_ADDR(base)           ((base) + (0x022))

/* 寄存器说明：LDO15开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO15_ONOFF_ECO_UNION */
#define PMIC_LDO15_ONOFF_ECO_ADDR(base)           ((base) + (0x023))

/* 寄存器说明：LDO16开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO16_ONOFF_ECO_UNION */
#define PMIC_LDO16_ONOFF_ECO_ADDR(base)           ((base) + (0x024))

/* 寄存器说明：LDO17开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO17_ONOFF_ECO_UNION */
#define PMIC_LDO17_ONOFF_ECO_ADDR(base)           ((base) + (0x025))

/* 寄存器说明：LDO19开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO19_ONOFF_ECO_UNION */
#define PMIC_LDO19_ONOFF_ECO_ADDR(base)           ((base) + (0x026))

/* 寄存器说明：LDO20开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO20_ONOFF_ECO_UNION */
#define PMIC_LDO20_ONOFF_ECO_ADDR(base)           ((base) + (0x027))

/* 寄存器说明：LDO21开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO21_ONOFF_ECO_UNION */
#define PMIC_LDO21_ONOFF_ECO_ADDR(base)           ((base) + (0x028))

/* 寄存器说明：LDO22开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO22_ONOFF_ECO_UNION */
#define PMIC_LDO22_ONOFF_ECO_ADDR(base)           ((base) + (0x029))

/* 寄存器说明：LDO23开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO23_ONOFF_ECO_UNION */
#define PMIC_LDO23_ONOFF_ECO_ADDR(base)           ((base) + (0x02A))

/* 寄存器说明：LDO24开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO24_ONOFF_ECO_UNION */
#define PMIC_LDO24_ONOFF_ECO_ADDR(base)           ((base) + (0x02B))

/* 寄存器说明：LDO25开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO25_ONOFF_ECO_UNION */
#define PMIC_LDO25_ONOFF_ECO_ADDR(base)           ((base) + (0x02C))

/* 寄存器说明：LDO26开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO26_ONOFF_ECO_UNION */
#define PMIC_LDO26_ONOFF_ECO_ADDR(base)           ((base) + (0x02D))

/* 寄存器说明：LDO27开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO27_ONOFF_ECO_UNION */
#define PMIC_LDO27_ONOFF_ECO_ADDR(base)           ((base) + (0x02E))

/* 寄存器说明：LDO28开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO28_ONOFF_ECO_UNION */
#define PMIC_LDO28_ONOFF_ECO_ADDR(base)           ((base) + (0x02F))

/* 寄存器说明：LDO29开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO29_ONOFF_ECO_UNION */
#define PMIC_LDO29_ONOFF_ECO_ADDR(base)           ((base) + (0x030))

/* 寄存器说明：LDO开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO31_ONOFF_ECO_UNION */
#define PMIC_LDO31_ONOFF_ECO_ADDR(base)           ((base) + (0x031))

/* 寄存器说明：LDO32开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO32_ONOFF_ECO_UNION */
#define PMIC_LDO32_ONOFF_ECO_ADDR(base)           ((base) + (0x032))

/* 寄存器说明：LDO开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO33_ONOFF_ECO_UNION */
#define PMIC_LDO33_ONOFF_ECO_ADDR(base)           ((base) + (0x033))

/* 寄存器说明：LDO开关和ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO34_ONOFF_ECO_UNION */
#define PMIC_LDO34_ONOFF_ECO_ADDR(base)           ((base) + (0x034))

/* 寄存器说明：BUCK0调压寄存器。
   位域定义UNION结构:  PMIC_BUCK0_VSET_UNION */
#define PMIC_BUCK0_VSET_ADDR(base)                ((base) + (0x03A))

/* 寄存器说明：BUCK1调压寄存器。
   位域定义UNION结构:  PMIC_BUCK1_VSET_UNION */
#define PMIC_BUCK1_VSET_ADDR(base)                ((base) + (0x03B))

/* 寄存器说明：BUCK2调压寄存器。
   位域定义UNION结构:  PMIC_BUCK2_VSET_UNION */
#define PMIC_BUCK2_VSET_ADDR(base)                ((base) + (0x03C))

/* 寄存器说明：BUCK3调压寄存器。
   位域定义UNION结构:  PMIC_BUCK3_VSET_UNION */
#define PMIC_BUCK3_VSET_ADDR(base)                ((base) + (0x03D))

/* 寄存器说明：LDO0_2调压寄存器。
   位域定义UNION结构:  PMIC_LDO0_2_VSET_UNION */
#define PMIC_LDO0_2_VSET_ADDR(base)               ((base) + (0x03E))

/* 寄存器说明：LDO1调压寄存器。
   位域定义UNION结构:  PMIC_LDO1_VSET_UNION */
#define PMIC_LDO1_VSET_ADDR(base)                 ((base) + (0x03F))

/* 寄存器说明：LDO2调压寄存器。
   位域定义UNION结构:  PMIC_LDO2_VSET_UNION */
#define PMIC_LDO2_VSET_ADDR(base)                 ((base) + (0x040))

/* 寄存器说明：LDO3调压寄存器。
   位域定义UNION结构:  PMIC_LDO3_VSET_UNION */
#define PMIC_LDO3_VSET_ADDR(base)                 ((base) + (0x041))

/* 寄存器说明：LDO4调压寄存器。
   位域定义UNION结构:  PMIC_LDO4_VSET_UNION */
#define PMIC_LDO4_VSET_ADDR(base)                 ((base) + (0x042))

/* 寄存器说明：LDO5调压寄存器。
   位域定义UNION结构:  PMIC_LDO5_VSET_UNION */
#define PMIC_LDO5_VSET_ADDR(base)                 ((base) + (0x043))

/* 寄存器说明：LDO7调压寄存器。
   位域定义UNION结构:  PMIC_LDO7_VSET_UNION */
#define PMIC_LDO7_VSET_ADDR(base)                 ((base) + (0x044))

/* 寄存器说明：LDO8调压寄存器。
   位域定义UNION结构:  PMIC_LDO8_VSET_UNION */
#define PMIC_LDO8_VSET_ADDR(base)                 ((base) + (0x045))

/* 寄存器说明：LDO9调压寄存器。
   位域定义UNION结构:  PMIC_LDO9_VSET_UNION */
#define PMIC_LDO9_VSET_ADDR(base)                 ((base) + (0x046))

/* 寄存器说明：LDO10调压寄存器。
   位域定义UNION结构:  PMIC_LDO10_VSET_UNION */
#define PMIC_LDO10_VSET_ADDR(base)                ((base) + (0x047))

/* 寄存器说明：LDO11调压寄存器。
   位域定义UNION结构:  PMIC_LDO11_VSET_UNION */
#define PMIC_LDO11_VSET_ADDR(base)                ((base) + (0x048))

/* 寄存器说明：LDO12调压寄存器。
   位域定义UNION结构:  PMIC_LDO12_VSET_UNION */
#define PMIC_LDO12_VSET_ADDR(base)                ((base) + (0x049))

/* 寄存器说明：LDO13调压寄存器。
   位域定义UNION结构:  PMIC_LDO13_VSET_UNION */
#define PMIC_LDO13_VSET_ADDR(base)                ((base) + (0x04A))

/* 寄存器说明：LDO14调压寄存器。
   位域定义UNION结构:  PMIC_LDO14_VSET_UNION */
#define PMIC_LDO14_VSET_ADDR(base)                ((base) + (0x04B))

/* 寄存器说明：LDO15调压寄存器。
   位域定义UNION结构:  PMIC_LDO15_VSET_UNION */
#define PMIC_LDO15_VSET_ADDR(base)                ((base) + (0x04C))

/* 寄存器说明：LDO16调压寄存器。
   位域定义UNION结构:  PMIC_LDO16_VSET_UNION */
#define PMIC_LDO16_VSET_ADDR(base)                ((base) + (0x04D))

/* 寄存器说明：LDO17调压寄存器。
   位域定义UNION结构:  PMIC_LDO17_VSET_UNION */
#define PMIC_LDO17_VSET_ADDR(base)                ((base) + (0x04E))

/* 寄存器说明：LDO19调压寄存器。
   位域定义UNION结构:  PMIC_LDO19_VSET1_UNION */
#define PMIC_LDO19_VSET1_ADDR(base)               ((base) + (0x04F))

/* 寄存器说明：LDO20调压寄存器。
   位域定义UNION结构:  PMIC_LDO20_VSET_UNION */
#define PMIC_LDO20_VSET_ADDR(base)                ((base) + (0x050))

/* 寄存器说明：LDO21调压寄存器。
   位域定义UNION结构:  PMIC_LDO21_VSET_UNION */
#define PMIC_LDO21_VSET_ADDR(base)                ((base) + (0x051))

/* 寄存器说明：LDO22调压寄存器。
   位域定义UNION结构:  PMIC_LDO22_VSET_UNION */
#define PMIC_LDO22_VSET_ADDR(base)                ((base) + (0x052))

/* 寄存器说明：LDO23调压寄存器。
   位域定义UNION结构:  PMIC_LDO23_VSET_UNION */
#define PMIC_LDO23_VSET_ADDR(base)                ((base) + (0x053))

/* 寄存器说明：LDO24调压寄存器。
   位域定义UNION结构:  PMIC_LDO24_VSET_UNION */
#define PMIC_LDO24_VSET_ADDR(base)                ((base) + (0x054))

/* 寄存器说明：LDO25调压寄存器。
   位域定义UNION结构:  PMIC_LDO25_VSET_UNION */
#define PMIC_LDO25_VSET_ADDR(base)                ((base) + (0x055))

/* 寄存器说明：LDO26调压寄存器。
   位域定义UNION结构:  PMIC_LDO26_VSET_UNION */
#define PMIC_LDO26_VSET_ADDR(base)                ((base) + (0x056))

/* 寄存器说明：LDO27调压寄存器。
   位域定义UNION结构:  PMIC_LDO27_VSET_UNION */
#define PMIC_LDO27_VSET_ADDR(base)                ((base) + (0x057))

/* 寄存器说明：LDO28调压寄存器。
   位域定义UNION结构:  PMIC_LDO28_VSET_UNION */
#define PMIC_LDO28_VSET_ADDR(base)                ((base) + (0x058))

/* 寄存器说明：LDO29调压寄存器。
   位域定义UNION结构:  PMIC_LDO29_VSET_UNION */
#define PMIC_LDO29_VSET_ADDR(base)                ((base) + (0x059))

/* 寄存器说明：LDO31调压寄存器。
   位域定义UNION结构:  PMIC_LDO31_VSET_UNION */
#define PMIC_LDO31_VSET_ADDR(base)                ((base) + (0x05A))

/* 寄存器说明：LDO32调压寄存器。
   位域定义UNION结构:  PMIC_LDO32_VSET_UNION */
#define PMIC_LDO32_VSET_ADDR(base)                ((base) + (0x05B))

/* 寄存器说明：LDO33调压寄存器。
   位域定义UNION结构:  PMIC_LDO33_VSET_UNION */
#define PMIC_LDO33_VSET_ADDR(base)                ((base) + (0x05C))

/* 寄存器说明：LDO34调压寄存器。
   位域定义UNION结构:  PMIC_LDO34_VSET_UNION */
#define PMIC_LDO34_VSET_ADDR(base)                ((base) + (0x05D))

/* 寄存器说明：BUCK0控制寄存器0。
   位域定义UNION结构:  PMIC_BUCK0_CTRL0_UNION */
#define PMIC_BUCK0_CTRL0_ADDR(base)               ((base) + (0x064))

/* 寄存器说明：BUCK0控制寄存器1。
   位域定义UNION结构:  PMIC_BUCK0_CTRL1_UNION */
#define PMIC_BUCK0_CTRL1_ADDR(base)               ((base) + (0x065))

/* 寄存器说明：BUCK0控制寄存器2。
   位域定义UNION结构:  PMIC_BUCK0_CTRL2_UNION */
#define PMIC_BUCK0_CTRL2_ADDR(base)               ((base) + (0x066))

/* 寄存器说明：BUCK0控制寄存器3。
   位域定义UNION结构:  PMIC_BUCK0_CTRL3_UNION */
#define PMIC_BUCK0_CTRL3_ADDR(base)               ((base) + (0x067))

/* 寄存器说明：BUCK0控制寄存器4。
   位域定义UNION结构:  PMIC_BUCK0_CTRL4_UNION */
#define PMIC_BUCK0_CTRL4_ADDR(base)               ((base) + (0x068))

/* 寄存器说明：BUCK0控制寄存器5。
   位域定义UNION结构:  PMIC_BUCK0_CTRL5_UNION */
#define PMIC_BUCK0_CTRL5_ADDR(base)               ((base) + (0x069))

/* 寄存器说明：BUCK0控制寄存器6。
   位域定义UNION结构:  PMIC_BUCK0_CTRL6_UNION */
#define PMIC_BUCK0_CTRL6_ADDR(base)               ((base) + (0x06A))

/* 寄存器说明：BUCK0控制寄存器7。
   位域定义UNION结构:  PMIC_BUCK0_CTRL7_UNION */
#define PMIC_BUCK0_CTRL7_ADDR(base)               ((base) + (0x06B))

/* 寄存器说明：BUCK0控制寄存器8。
   位域定义UNION结构:  PMIC_BUCK0_CTRL8_UNION */
#define PMIC_BUCK0_CTRL8_ADDR(base)               ((base) + (0x06C))

/* 寄存器说明：BUCK1控制寄存器0。
   位域定义UNION结构:  PMIC_BUCK1_CTRL0_UNION */
#define PMIC_BUCK1_CTRL0_ADDR(base)               ((base) + (0x06D))

/* 寄存器说明：BUCK1控制寄存器1。
   位域定义UNION结构:  PMIC_BUCK1_CTRL1_UNION */
#define PMIC_BUCK1_CTRL1_ADDR(base)               ((base) + (0x06E))

/* 寄存器说明：BUCK1控制寄存器2。
   位域定义UNION结构:  PMIC_BUCK1_CTRL2_UNION */
#define PMIC_BUCK1_CTRL2_ADDR(base)               ((base) + (0x06F))

/* 寄存器说明：BUCK1控制寄存器3。
   位域定义UNION结构:  PMIC_BUCK1_CTRL3_UNION */
#define PMIC_BUCK1_CTRL3_ADDR(base)               ((base) + (0x070))

/* 寄存器说明：BUCK1控制寄存器4。
   位域定义UNION结构:  PMIC_BUCK1_CTRL4_UNION */
#define PMIC_BUCK1_CTRL4_ADDR(base)               ((base) + (0x071))

/* 寄存器说明：BUCK1控制寄存器5。
   位域定义UNION结构:  PMIC_BUCK1_CTRL5_UNION */
#define PMIC_BUCK1_CTRL5_ADDR(base)               ((base) + (0x072))

/* 寄存器说明：BUCK1控制寄存器6。
   位域定义UNION结构:  PMIC_BUCK1_CTRL6_UNION */
#define PMIC_BUCK1_CTRL6_ADDR(base)               ((base) + (0x073))

/* 寄存器说明：BUCK1控制寄存器7。
   位域定义UNION结构:  PMIC_BUCK1_CTRL7_UNION */
#define PMIC_BUCK1_CTRL7_ADDR(base)               ((base) + (0x074))

/* 寄存器说明：BUCK1控制寄存器8。
   位域定义UNION结构:  PMIC_BUCK1_CTRL8_UNION */
#define PMIC_BUCK1_CTRL8_ADDR(base)               ((base) + (0x075))

/* 寄存器说明：BUCK2控制寄存器0。
   位域定义UNION结构:  PMIC_BUCK2_CTRL0_UNION */
#define PMIC_BUCK2_CTRL0_ADDR(base)               ((base) + (0x076))

/* 寄存器说明：BUCK2控制寄存器1。
   位域定义UNION结构:  PMIC_BUCK2_CTRL1_UNION */
#define PMIC_BUCK2_CTRL1_ADDR(base)               ((base) + (0x077))

/* 寄存器说明：BUCK2控制寄存器2。
   位域定义UNION结构:  PMIC_BUCK2_CTRL2_UNION */
#define PMIC_BUCK2_CTRL2_ADDR(base)               ((base) + (0x078))

/* 寄存器说明：BUCK2控制寄存器3。
   位域定义UNION结构:  PMIC_BUCK2_CTRL3_UNION */
#define PMIC_BUCK2_CTRL3_ADDR(base)               ((base) + (0x079))

/* 寄存器说明：BUCK2控制寄存器4。
   位域定义UNION结构:  PMIC_BUCK2_CTRL4_UNION */
#define PMIC_BUCK2_CTRL4_ADDR(base)               ((base) + (0x07A))

/* 寄存器说明：BUCK2控制寄存器5。
   位域定义UNION结构:  PMIC_BUCK2_CTRL5_UNION */
#define PMIC_BUCK2_CTRL5_ADDR(base)               ((base) + (0x07B))

/* 寄存器说明：BUCK2控制寄存器6。
   位域定义UNION结构:  PMIC_BUCK2_CTRL6_UNION */
#define PMIC_BUCK2_CTRL6_ADDR(base)               ((base) + (0x07C))

/* 寄存器说明：BUCK2控制寄存器7。
   位域定义UNION结构:  PMIC_BUCK2_CTRL7_UNION */
#define PMIC_BUCK2_CTRL7_ADDR(base)               ((base) + (0x07D))

/* 寄存器说明：BUCK2控制寄存器8。
   位域定义UNION结构:  PMIC_BUCK2_CTRL8_UNION */
#define PMIC_BUCK2_CTRL8_ADDR(base)               ((base) + (0x07E))

/* 寄存器说明：BUCK3控制寄存器0。
   位域定义UNION结构:  PMIC_BUCK3_CTRL0_UNION */
#define PMIC_BUCK3_CTRL0_ADDR(base)               ((base) + (0x07F))

/* 寄存器说明：BUCK3控制寄存器1。
   位域定义UNION结构:  PMIC_BUCK3_CTRL1_UNION */
#define PMIC_BUCK3_CTRL1_ADDR(base)               ((base) + (0x080))

/* 寄存器说明：BUCK3控制寄存器2。
   位域定义UNION结构:  PMIC_BUCK3_CTRL2_UNION */
#define PMIC_BUCK3_CTRL2_ADDR(base)               ((base) + (0x081))

/* 寄存器说明：BUCK3控制寄存器3。
   位域定义UNION结构:  PMIC_BUCK3_CTRL3_UNION */
#define PMIC_BUCK3_CTRL3_ADDR(base)               ((base) + (0x082))

/* 寄存器说明：BUCK3控制寄存器4。
   位域定义UNION结构:  PMIC_BUCK3_CTRL4_UNION */
#define PMIC_BUCK3_CTRL4_ADDR(base)               ((base) + (0x083))

/* 寄存器说明：BUCK3控制寄存器5。
   位域定义UNION结构:  PMIC_BUCK3_CTRL5_UNION */
#define PMIC_BUCK3_CTRL5_ADDR(base)               ((base) + (0x084))

/* 寄存器说明：BUCK3控制寄存器6。
   位域定义UNION结构:  PMIC_BUCK3_CTRL6_UNION */
#define PMIC_BUCK3_CTRL6_ADDR(base)               ((base) + (0x085))

/* 寄存器说明：BUCK3控制寄存器7。
   位域定义UNION结构:  PMIC_BUCK3_CTRL7_UNION */
#define PMIC_BUCK3_CTRL7_ADDR(base)               ((base) + (0x086))

/* 寄存器说明：BUCK3控制寄存器8。
   位域定义UNION结构:  PMIC_BUCK3_CTRL8_UNION */
#define PMIC_BUCK3_CTRL8_ADDR(base)               ((base) + (0x087))

/* 寄存器说明：BUCK预留寄存器
   位域定义UNION结构:  PMIC_BUCK_RESERVE0_UNION */
#define PMIC_BUCK_RESERVE0_ADDR(base)             ((base) + (0x088))

/* 寄存器说明：BUCK预留寄存器
   位域定义UNION结构:  PMIC_BUCK_RESERVE1_UNION */
#define PMIC_BUCK_RESERVE1_ADDR(base)             ((base) + (0x089))

/* 寄存器说明：LDO0_2/LDO1控制寄存器。
   位域定义UNION结构:  PMIC_LDO_1_CTRL_UNION */
#define PMIC_LDO_1_CTRL_ADDR(base)                ((base) + (0x08A))

/* 寄存器说明：LDO1控制寄存器
   位域定义UNION结构:  PMIC_LDO1_CTRL_0_UNION */
#define PMIC_LDO1_CTRL_0_ADDR(base)               ((base) + (0x08B))

/* 寄存器说明：LDO1控制寄存器
   位域定义UNION结构:  PMIC_LDO1_CTRL_1_UNION */
#define PMIC_LDO1_CTRL_1_ADDR(base)               ((base) + (0x08C))

/* 寄存器说明：LDO2/LDO3控制寄存器。
   位域定义UNION结构:  PMIC_LDO2_3_CTRL_UNION */
#define PMIC_LDO2_3_CTRL_ADDR(base)               ((base) + (0x08D))

/* 寄存器说明：LDO3控制寄存器
   位域定义UNION结构:  PMIC_LDO3_CTRL_UNION */
#define PMIC_LDO3_CTRL_ADDR(base)                 ((base) + (0x08E))

/* 寄存器说明：LDO4/LDO5控制寄存器。
   位域定义UNION结构:  PMIC_LDO4_5_CTRL_UNION */
#define PMIC_LDO4_5_CTRL_ADDR(base)               ((base) + (0x08F))

/* 寄存器说明：LDO7/LDO8控制寄存器。
   位域定义UNION结构:  PMIC_LDO7_8_CTRL_UNION */
#define PMIC_LDO7_8_CTRL_ADDR(base)               ((base) + (0x090))

/* 寄存器说明：LDO9/LDO10控制寄存器。
   位域定义UNION结构:  PMIC_LDO9_10_CTRL_UNION */
#define PMIC_LDO9_10_CTRL_ADDR(base)              ((base) + (0x091))

/* 寄存器说明：LDO11/LDO12控制寄存器。
   位域定义UNION结构:  PMIC_LD11_12_CTRL_UNION */
#define PMIC_LD11_12_CTRL_ADDR(base)              ((base) + (0x092))

/* 寄存器说明：LDO13/LDO14控制寄存器。
   位域定义UNION结构:  PMIC_LDO13_14_CTRL_UNION */
#define PMIC_LDO13_14_CTRL_ADDR(base)             ((base) + (0x093))

/* 寄存器说明：LDO15/LDO16控制寄存器。
   位域定义UNION结构:  PMIC_LDO15_16_CTRL_UNION */
#define PMIC_LDO15_16_CTRL_ADDR(base)             ((base) + (0x094))

/* 寄存器说明：LDO17/LDO19控制寄存器。
   位域定义UNION结构:  PMIC_LDO17_19_CTRL_UNION */
#define PMIC_LDO17_19_CTRL_ADDR(base)             ((base) + (0x095))

/* 寄存器说明：LDO20/LDO21控制寄存器。
   位域定义UNION结构:  PMIC_LDO20_21_CTRL_UNION */
#define PMIC_LDO20_21_CTRL_ADDR(base)             ((base) + (0x096))

/* 寄存器说明：LDO22控制寄存器。
   位域定义UNION结构:  PMIC_LDO22_CTRL0_UNION */
#define PMIC_LDO22_CTRL0_ADDR(base)               ((base) + (0x097))

/* 寄存器说明：LDO22控制寄存器。
   位域定义UNION结构:  PMIC_LDO22_CTRL1_UNION */
#define PMIC_LDO22_CTRL1_ADDR(base)               ((base) + (0x098))

/* 寄存器说明：LDO22控制寄存器。
   位域定义UNION结构:  PMIC_LDO22_CTRL2_UNION */
#define PMIC_LDO22_CTRL2_ADDR(base)               ((base) + (0x099))

/* 寄存器说明：LDO23控制寄存器。
   位域定义UNION结构:  PMIC_LDO23_CTRL_UNION */
#define PMIC_LDO23_CTRL_ADDR(base)                ((base) + (0x09A))

/* 寄存器说明：LDO24/LDO25控制寄存器。
   位域定义UNION结构:  PMIC_LDO24_25_CTRL_UNION */
#define PMIC_LDO24_25_CTRL_ADDR(base)             ((base) + (0x09B))

/* 寄存器说明：LDO26控制寄存器。
   位域定义UNION结构:  PMIC_LDO26_CTRL_UNION */
#define PMIC_LDO26_CTRL_ADDR(base)                ((base) + (0x09C))

/* 寄存器说明：LDO27控制寄存器。
   位域定义UNION结构:  PMIC_LDO27_CTRL_UNION */
#define PMIC_LDO27_CTRL_ADDR(base)                ((base) + (0x09D))

/* 寄存器说明：LDO28/LDO29控制寄存器。
   位域定义UNION结构:  PMIC_LDO28_29_CTRL_UNION */
#define PMIC_LDO28_29_CTRL_ADDR(base)             ((base) + (0x09E))

/* 寄存器说明：LDO31/LDO32控制寄存器。
   位域定义UNION结构:  PMIC_LDO31_32_CTRL_UNION */
#define PMIC_LDO31_32_CTRL_ADDR(base)             ((base) + (0x09F))

/* 寄存器说明：LDO33/LDO34控制寄存器。
   位域定义UNION结构:  PMIC_LDO33_LDO34_CTRL_UNION */
#define PMIC_LDO33_LDO34_CTRL_ADDR(base)          ((base) + (0x0A0))

/* 寄存器说明：LDO预留寄存器
   位域定义UNION结构:  PMIC_LDO_RESERVE0_UNION */
#define PMIC_LDO_RESERVE0_ADDR(base)              ((base) + (0x0A1))

/* 寄存器说明：LDO预留寄存器
   位域定义UNION结构:  PMIC_LDO_RESERVE1_UNION */
#define PMIC_LDO_RESERVE1_ADDR(base)              ((base) + (0x0A2))

/* 寄存器说明：BUCK0/1/2/3 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_BUCK0_3_OCP_CTRL_UNION */
#define PMIC_BUCK0_3_OCP_CTRL_ADDR(base)          ((base) + (0x100))

/* 寄存器说明：BUCK4/LDO0/1/2 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO0_3_OCP_CTRL_UNION */
#define PMIC_LDO0_3_OCP_CTRL_ADDR(base)           ((base) + (0x101))

/* 寄存器说明：LCO3/4/5/7 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO4_8_OCP_CTRL_UNION */
#define PMIC_LDO4_8_OCP_CTRL_ADDR(base)           ((base) + (0x102))

/* 寄存器说明：LDO8/9/10/11 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO9_12_OCP_CTRL_UNION */
#define PMIC_LDO9_12_OCP_CTRL_ADDR(base)          ((base) + (0x103))

/* 寄存器说明：LDO12/13/14/15 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO13_16_OCP_CTRL_UNION */
#define PMIC_LDO13_16_OCP_CTRL_ADDR(base)         ((base) + (0x104))

/* 寄存器说明：LDO16/17/19/20 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO17_21_OCP_CTRL_UNION */
#define PMIC_LDO17_21_OCP_CTRL_ADDR(base)         ((base) + (0x105))

/* 寄存器说明：LDO21/22/23/24 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO22_25_OCP_CTRL_UNION */
#define PMIC_LDO22_25_OCP_CTRL_ADDR(base)         ((base) + (0x106))

/* 寄存器说明：LDO25/26/27/28 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO26_29_OCP_CTRL_UNION */
#define PMIC_LDO26_29_OCP_CTRL_ADDR(base)         ((base) + (0x107))

/* 寄存器说明：LDO31/32/33/34 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO31_34_OCP_CTRL_UNION */
#define PMIC_LDO31_34_OCP_CTRL_ADDR(base)         ((base) + (0x108))

/* 寄存器说明：LDO_BUFF SCP/CLASS OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_LDO_BUFF_CLASS_SCP_CTRL_UNION */
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_ADDR(base)   ((base) + (0x109))

/* 寄存器说明：BUCK0/1/2/3 OCP自动关断控制寄存器。
   位域定义UNION结构:  PMIC_BUCK0_3_SCP_CTRL_UNION */
#define PMIC_BUCK0_3_SCP_CTRL_ADDR(base)          ((base) + (0x10A))

/* 寄存器说明：LDO_PMUA ECO使能寄存器。
   位域定义UNION结构:  PMIC_LDO_PMUA_ECO_UNION */
#define PMIC_LDO_PMUA_ECO_ADDR(base)              ((base) + (0x10D))

/* 寄存器说明：LDO_PMUA调压寄存器。
   位域定义UNION结构:  PMIC_LDO_PMUA_VSET_UNION */
#define PMIC_LDO_PMUA_VSET_ADDR(base)             ((base) + (0x10E))

/* 寄存器说明：ABB时钟开关寄存器
   位域定义UNION结构:  PMIC_CLK_ABB_EN_UNION */
#define PMIC_CLK_ABB_EN_ADDR(base)                ((base) + (0x10F))

/* 寄存器说明：WIFI时钟开关寄存器
   位域定义UNION结构:  PMIC_CLK_WIFI_EN_UNION */
#define PMIC_CLK_WIFI_EN_ADDR(base)               ((base) + (0x110))

/* 寄存器说明：RF0时钟开关寄存器
   位域定义UNION结构:  PMIC_CLK_RF0_EN_UNION */
#define PMIC_CLK_RF0_EN_ADDR(base)                ((base) + (0x111))

/* 寄存器说明：RF1时钟开关寄存器
   位域定义UNION结构:  PMIC_CLK_RF1_EN_UNION */
#define PMIC_CLK_RF1_EN_ADDR(base)                ((base) + (0x112))

/* 寄存器说明：SYS时钟开关寄存器
   位域定义UNION结构:  PMIC_CLK_SYS_EN_UNION */
#define PMIC_CLK_SYS_EN_ADDR(base)                ((base) + (0x113))

/* 寄存器说明：CODEC时钟开关寄存器
   位域定义UNION结构:  PMIC_CLK_CODEC_EN_UNION */
#define PMIC_CLK_CODEC_EN_ADDR(base)              ((base) + (0x114))

/* 寄存器说明：ABB时钟配置寄存器
   位域定义UNION结构:  PMIC_CLK_ABB_CTRL_UNION */
#define PMIC_CLK_ABB_CTRL_ADDR(base)              ((base) + (0x115))

/* 寄存器说明：WIFI时钟配置寄存器
   位域定义UNION结构:  PMIC_CLK_WIFI_CTRL_UNION */
#define PMIC_CLK_WIFI_CTRL_ADDR(base)             ((base) + (0x116))

/* 寄存器说明：RF0时钟配置寄存器
   位域定义UNION结构:  PMIC_CLK_RF0_CTRL_UNION */
#define PMIC_CLK_RF0_CTRL_ADDR(base)              ((base) + (0x117))

/* 寄存器说明：RF1时钟配置寄存器
   位域定义UNION结构:  PMIC_CLK_RF1_CTRL_UNION */
#define PMIC_CLK_RF1_CTRL_ADDR(base)              ((base) + (0x118))

/* 寄存器说明：SYS时钟配置寄存器
   位域定义UNION结构:  PMIC_CLK_SYS_CTRL_UNION */
#define PMIC_CLK_SYS_CTRL_ADDR(base)              ((base) + (0x119))

/* 寄存器说明：CODEC时钟配置寄存器
   位域定义UNION结构:  PMIC_CLK_CODEC_CTRL_UNION */
#define PMIC_CLK_CODEC_CTRL_ADDR(base)            ((base) + (0x11A))

/* 寄存器说明：时钟控制寄存器0。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL0_UNION */
#define PMIC_CLK_TOP_CTRL0_ADDR(base)             ((base) + (0x11B))

/* 寄存器说明：时钟控制寄存器1。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL1_UNION */
#define PMIC_CLK_TOP_CTRL1_ADDR(base)             ((base) + (0x11C))

/* 寄存器说明：时钟控制寄存器2。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL2_UNION */
#define PMIC_CLK_TOP_CTRL2_ADDR(base)             ((base) + (0x11D))

/* 寄存器说明：时钟控制寄存器3。
   位域定义UNION结构:  PMIC_CLK_TOP_CTRL3_UNION */
#define PMIC_CLK_TOP_CTRL3_ADDR(base)             ((base) + (0x11E))

/* 寄存器说明：256K RC控制寄存器0。
   位域定义UNION结构:  PMIC_CLK_256K_CTRL0_UNION */
#define PMIC_CLK_256K_CTRL0_ADDR(base)            ((base) + (0x11F))

/* 寄存器说明：256K RC控制寄存器1。
   位域定义UNION结构:  PMIC_CLK_256K_CTRL1_UNION */
#define PMIC_CLK_256K_CTRL1_ADDR(base)            ((base) + (0x120))

/* 寄存器说明：32kHz时钟输出使能控制寄存器。
   位域定义UNION结构:  PMIC_OSC32K_ONOFF_CTRL_UNION */
#define PMIC_OSC32K_ONOFF_CTRL_ADDR(base)         ((base) + (0x121))

/* 寄存器说明：硬线屏蔽控制寄存器0。
   位域定义UNION结构:  PMIC_HARDWIRE_CTRL0_UNION */
#define PMIC_HARDWIRE_CTRL0_ADDR(base)            ((base) + (0x125))

/* 寄存器说明：硬线屏蔽控制寄存器1。
   位域定义UNION结构:  PMIC_HARDWIRE_CTRL1_UNION */
#define PMIC_HARDWIRE_CTRL1_ADDR(base)            ((base) + (0x126))

/* 寄存器说明：peri硬线控制寄存器0。
   位域定义UNION结构:  PMIC_PERI_CTRL0_UNION */
#define PMIC_PERI_CTRL0_ADDR(base)                ((base) + (0x127))

/* 寄存器说明：peri硬线控制寄存器1。
   位域定义UNION结构:  PMIC_PERI_CTRL1_UNION */
#define PMIC_PERI_CTRL1_ADDR(base)                ((base) + (0x128))

/* 寄存器说明：peri硬线控制寄存器2。
   位域定义UNION结构:  PMIC_PERI_CTRL2_UNION */
#define PMIC_PERI_CTRL2_ADDR(base)                ((base) + (0x129))

/* 寄存器说明：peri硬线控制寄存器3。
   位域定义UNION结构:  PMIC_PERI_CTRL3_UNION */
#define PMIC_PERI_CTRL3_ADDR(base)                ((base) + (0x12A))

/* 寄存器说明：peri硬线调压寄存器。
   位域定义UNION结构:  PMIC_PERI_VSET_CTRL_UNION */
#define PMIC_PERI_VSET_CTRL_ADDR(base)            ((base) + (0x12B))

/* 寄存器说明：peri硬线时间间隔控制寄存器。
   位域定义UNION结构:  PMIC_PERI_TIME__CTRL_UNION */
#define PMIC_PERI_TIME__CTRL_ADDR(base)           ((base) + (0x12C))

/* 寄存器说明：库仑计ECO使能控制寄存器。
   位域定义UNION结构:  PMIC_COUL_ECO_MASK_UNION */
#define PMIC_COUL_ECO_MASK_ADDR(base)             ((base) + (0x12D))

/* 寄存器说明：IRQ_MASK0控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_0_UNION */
#define PMIC_IRQ_MASK_0_ADDR(base)                ((base) + (0x130))

/* 寄存器说明：IRQ_MASK1控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_1_UNION */
#define PMIC_IRQ_MASK_1_ADDR(base)                ((base) + (0x131))

/* 寄存器说明：IRQ_MASK3控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_2_UNION */
#define PMIC_IRQ_MASK_2_ADDR(base)                ((base) + (0x132))

/* 寄存器说明：IRQ_MASK4控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_3_UNION */
#define PMIC_IRQ_MASK_3_ADDR(base)                ((base) + (0x133))

/* 寄存器说明：IRQ_MASK5控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_4_UNION */
#define PMIC_IRQ_MASK_4_ADDR(base)                ((base) + (0x134))

/* 寄存器说明：IRQ_MASK6控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_5_UNION */
#define PMIC_IRQ_MASK_5_ADDR(base)                ((base) + (0x135))

/* 寄存器说明：IRQ_MASK7控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_6_UNION */
#define PMIC_IRQ_MASK_6_ADDR(base)                ((base) + (0x136))

/* 寄存器说明：IRQ_MASK8控制寄存器。
   位域定义UNION结构:  PMIC_IRQ_MASK_7_UNION */
#define PMIC_IRQ_MASK_7_ADDR(base)                ((base) + (0x137))

/* 寄存器说明：NOPWRT控制寄存器。
   位域定义UNION结构:  PMIC_BACKUP_CHG_UNION */
#define PMIC_BACKUP_CHG_ADDR(base)                ((base) + (0x13A))

/* 寄存器说明：classd控制寄存器0。
   位域定义UNION结构:  PMIC_CLASSD_CTRL0_UNION */
#define PMIC_CLASSD_CTRL0_ADDR(base)              ((base) + (0x13B))

/* 寄存器说明：classd控制寄存器1。
   位域定义UNION结构:  PMIC_CLASSD_CTRL1_UNION */
#define PMIC_CLASSD_CTRL1_ADDR(base)              ((base) + (0x13C))

/* 寄存器说明：classd控制寄存器2。
   位域定义UNION结构:  PMIC_CLASSD_CTRL2_UNION */
#define PMIC_CLASSD_CTRL2_ADDR(base)              ((base) + (0x13D))

/* 寄存器说明：classd控制寄存器3。
   位域定义UNION结构:  PMIC_CLASSD_CTRL3_UNION */
#define PMIC_CLASSD_CTRL3_ADDR(base)              ((base) + (0x13E))

/* 寄存器说明：电压温度控制寄存器。
   位域定义UNION结构:  PMIC_TH_CTRL_UNION */
#define PMIC_TH_CTRL_ADDR(base)                   ((base) + (0x13F))

/* 寄存器说明：bg测试寄存器。
   位域定义UNION结构:  PMIC_BG_TEST_UNION */
#define PMIC_BG_TEST_ADDR(base)                   ((base) + (0x140))

/* 寄存器说明：DR345闪烁模式使能和模式寄存器。
   位域定义UNION结构:  PMIC_DR_EN_MODE_345_UNION */
#define PMIC_DR_EN_MODE_345_ADDR(base)            ((base) + (0x141))

/* 寄存器说明：DR12闪烁模式使能和模式寄存器。
   位域定义UNION结构:  PMIC_DR_EN_MODE_12_UNION */
#define PMIC_DR_EN_MODE_12_ADDR(base)             ((base) + (0x142))

/* 寄存器说明：DR12闪烁模式周期调节0寄存器。
   位域定义UNION结构:  PMIC_FLASH_PERIOD_DR12_UNION */
#define PMIC_FLASH_PERIOD_DR12_ADDR(base)         ((base) + (0x143))

/* 寄存器说明：DR12闪烁模式点亮时间调节0寄存器。
   位域定义UNION结构:  PMIC_FLASH_ON_DR12_UNION */
#define PMIC_FLASH_ON_DR12_ADDR(base)             ((base) + (0x144))

/* 寄存器说明：DR345闪烁模式周期调节1寄存器。
   位域定义UNION结构:  PMIC_FLASH_PERIOD_DR345_UNION */
#define PMIC_FLASH_PERIOD_DR345_ADDR(base)        ((base) + (0x145))

/* 寄存器说明：DR345闪烁模式点亮时间调节1寄存器。
   位域定义UNION结构:  PMIC_FLASH_ON_DR345_UNION */
#define PMIC_FLASH_ON_DR345_ADDR(base)            ((base) + (0x146))

/* 寄存器说明：DR灯模式选择寄存器。
   位域定义UNION结构:  PMIC_DR_MODE_SEL_UNION */
#define PMIC_DR_MODE_SEL_ADDR(base)               ((base) + (0x147))

/* 寄存器说明：DR1/2呼吸模式控制寄存器。
   位域定义UNION结构:  PMIC_DR_BRE_CTRL_UNION */
#define PMIC_DR_BRE_CTRL_ADDR(base)               ((base) + (0x148))

/* 寄存器说明：DR1和DR2常亮常暗时间配置寄存器。
   位域定义UNION结构:  PMIC_DR12_TIM_CONF0_UNION */
#define PMIC_DR12_TIM_CONF0_ADDR(base)            ((base) + (0x149))

/* 寄存器说明：DR1和DR2渐亮渐暗时间配置寄存器。
   位域定义UNION结构:  PMIC_DR12_TIM_CONF1_UNION */
#define PMIC_DR12_TIM_CONF1_ADDR(base)            ((base) + (0x14A))

/* 寄存器说明：DR1电流选择寄存器。
   位域定义UNION结构:  PMIC_DR1_ISET_UNION */
#define PMIC_DR1_ISET_ADDR(base)                  ((base) + (0x14B))

/* 寄存器说明：DR2电流选择寄存器。
   位域定义UNION结构:  PMIC_DR2_ISET_UNION */
#define PMIC_DR2_ISET_ADDR(base)                  ((base) + (0x14C))

/* 寄存器说明：DR3/4/5控制寄存器。
   位域定义UNION结构:  PMIC_DR_LED_CTRL_UNION */
#define PMIC_DR_LED_CTRL_ADDR(base)               ((base) + (0x14D))

/* 寄存器说明：DR3/4/5输出控制寄存器。
   位域定义UNION结构:  PMIC_DR_OUT_CTRL_UNION */
#define PMIC_DR_OUT_CTRL_ADDR(base)               ((base) + (0x14E))

/* 寄存器说明：DR3电流选择寄存器。
   位域定义UNION结构:  PMIC_DR3_ISET_UNION */
#define PMIC_DR3_ISET_ADDR(base)                  ((base) + (0x14F))

/* 寄存器说明：DR3启动延时配置寄存器。
   位域定义UNION结构:  PMIC_DR3_START_DEL_UNION */
#define PMIC_DR3_START_DEL_ADDR(base)             ((base) + (0x150))

/* 寄存器说明：DR4电流选择寄存器。
   位域定义UNION结构:  PMIC_DR4_ISET_UNION */
#define PMIC_DR4_ISET_ADDR(base)                  ((base) + (0x151))

/* 寄存器说明：DR4启动延时配置寄存器。
   位域定义UNION结构:  PMIC_DR4_START_DEL_UNION */
#define PMIC_DR4_START_DEL_ADDR(base)             ((base) + (0x152))

/* 寄存器说明：DR5电流选择寄存器。
   位域定义UNION结构:  PMIC_DR5_ISET_UNION */
#define PMIC_DR5_ISET_ADDR(base)                  ((base) + (0x153))

/* 寄存器说明：DR5启动延时配置寄存器。
   位域定义UNION结构:  PMIC_DR5_START_DEL_UNION */
#define PMIC_DR5_START_DEL_ADDR(base)             ((base) + (0x154))

/* 寄存器说明：DR345常亮常暗时间配置寄存器。
   位域定义UNION结构:  PMIC_DR334_TIM_CONF0_UNION */
#define PMIC_DR334_TIM_CONF0_ADDR(base)           ((base) + (0x155))

/* 寄存器说明：DR345渐亮渐暗时间配置寄存器。
   位域定义UNION结构:  PMIC_DR345_TIM_CONF1_UNION */
#define PMIC_DR345_TIM_CONF1_ADDR(base)           ((base) + (0x156))

/* 寄存器说明：IN端低压阈值调整寄存器。
   位域定义UNION结构:  PMIC_VSYS_LOW_SET_UNION */
#define PMIC_VSYS_LOW_SET_ADDR(base)              ((base) + (0x157))

/* 寄存器说明：nfc_on控制寄存器。
   位域定义UNION结构:  PMIC_NFC_ON_CTRL_UNION */
#define PMIC_NFC_ON_CTRL_ADDR(base)               ((base) + (0x158))

/* 寄存器说明：系统控制预留寄存器。
   位域定义UNION结构:  PMIC_SYS_CTRL_RESERVE_UNION */
#define PMIC_SYS_CTRL_RESERVE_ADDR(base)          ((base) + (0x159))

/* 寄存器说明：热复位下电控制寄存器。
   位域定义UNION结构:  PMIC_HRESET_PWRDOWN_CTRL_UNION */
#define PMIC_HRESET_PWRDOWN_CTRL_ADDR(base)       ((base) + (0x15A))

/* 寄存器说明：OCP和SPC滤波时间控制寄存器。
   位域定义UNION结构:  PMIC_OCP_DEB_CTRL0_UNION */
#define PMIC_OCP_DEB_CTRL0_ADDR(base)             ((base) + (0x15B))

/* 寄存器说明：OCP和SPC滤波时间控制寄存器。
   位域定义UNION结构:  PMIC_OCP_DEB_CTRL1_UNION */
#define PMIC_OCP_DEB_CTRL1_ADDR(base)             ((base) + (0x15C))

/* 寄存器说明：OCP和DOCP滤波开关寄存器。
   位域定义UNION结构:  PMIC_OCP_SCP_ONOFF_UNION */
#define PMIC_OCP_SCP_ONOFF_ADDR(base)             ((base) + (0x15D))

/* 寄存器说明：欠压关机滤波时间选择寄存器。
   位域定义UNION结构:  PMIC_PWROFF_DEB_CTRL_UNION */
#define PMIC_PWROFF_DEB_CTRL_ADDR(base)           ((base) + (0x15E))

/* 寄存器说明：系统控制寄存器0。
   位域定义UNION结构:  PMIC_SYS_CTRL0_UNION */
#define PMIC_SYS_CTRL0_ADDR(base)                 ((base) + (0x15F))

/* 寄存器说明：SMPL控制寄存器。
   位域定义UNION结构:  PMIC_SMPL_CTRL_UNION */
#define PMIC_SMPL_CTRL_ADDR(base)                 ((base) + (0x160))

/* 寄存器说明：系统控制寄存器1。
   位域定义UNION结构:  PMIC_SYS_CTRL1_UNION */
#define PMIC_SYS_CTRL1_ADDR(base)                 ((base) + (0x161))

/* 寄存器说明：SIM控制寄存器。
   位域定义UNION结构:  PMIC_SIM_CTRL_UNION */
#define PMIC_SIM_CTRL_ADDR(base)                  ((base) + (0x162))

/* 寄存器说明：SIM滤波控制寄存器。
   位域定义UNION结构:  PMIC_SIM_DEB_CTRL_UNION */
#define PMIC_SIM_DEB_CTRL_ADDR(base)              ((base) + (0x163))

/* 寄存器说明：DAC0 IBIAS配置寄存器。
   位域定义UNION结构:  PMIC_AUX0_IBIAS_CFG_UNION */
#define PMIC_AUX0_IBIAS_CFG_ADDR(base)            ((base) + (0x164))

/* 寄存器说明：DAC1 IBIAS配置寄存器。
   位域定义UNION结构:  PMIC_AUX1_IBIAS_CFG_UNION */
#define PMIC_AUX1_IBIAS_CFG_ADDR(base)            ((base) + (0x165))

/* 寄存器说明：OTP0回读寄存器0。
   位域定义UNION结构:  PMIC_OTP0_0_UNION */
#define PMIC_OTP0_0_ADDR(base)                    ((base) + (0x16A))

/* 寄存器说明：OTP0回读寄存器1。
   位域定义UNION结构:  PMIC_OTP0_1_UNION */
#define PMIC_OTP0_1_ADDR(base)                    ((base) + (0x16B))

/* 寄存器说明：OTP0回读寄存器2。
   位域定义UNION结构:  PMIC_OTP0_2_UNION */
#define PMIC_OTP0_2_ADDR(base)                    ((base) + (0x16C))

/* 寄存器说明：OTP0回读寄存器3。
   位域定义UNION结构:  PMIC_OTP0_3_UNION */
#define PMIC_OTP0_3_ADDR(base)                    ((base) + (0x16D))

/* 寄存器说明：OTP0控制寄存器0。
   位域定义UNION结构:  PMIC_OTP0_CTRL_0_UNION */
#define PMIC_OTP0_CTRL_0_ADDR(base)               ((base) + (0x16E))

/* 寄存器说明：OTP0控制寄存器1。
   位域定义UNION结构:  PMIC_OTP0_CTRL_1_UNION */
#define PMIC_OTP0_CTRL_1_ADDR(base)               ((base) + (0x16F))

/* 寄存器说明：OTP0写操作数据寄存器。
   位域定义UNION结构:  PMIC_OTP0_WDATA_UNION */
#define PMIC_OTP0_WDATA_ADDR(base)                ((base) + (0x170))

/* 寄存器说明：OTP0或操作寄存器0
   位域定义UNION结构:  PMIC_OTP0_0_W_UNION */
#define PMIC_OTP0_0_W_ADDR(base)                  ((base) + (0x171))

/* 寄存器说明：OTP0或操作寄存器1
   位域定义UNION结构:  PMIC_OTP0_1_W_UNION */
#define PMIC_OTP0_1_W_ADDR(base)                  ((base) + (0x172))

/* 寄存器说明：OTP0或操作寄存器2
   位域定义UNION结构:  PMIC_OTP0_2_W_UNION */
#define PMIC_OTP0_2_W_ADDR(base)                  ((base) + (0x173))

/* 寄存器说明：OTP0或操作寄存器3
   位域定义UNION结构:  PMIC_OTP0_3_W_UNION */
#define PMIC_OTP0_3_W_ADDR(base)                  ((base) + (0x174))

/* 寄存器说明：OTP1回读寄存器0。
   位域定义UNION结构:  PMIC_OTP1_0_UNION */
#define PMIC_OTP1_0_ADDR(base)                    ((base) + (0x175))

/* 寄存器说明：OTP1回读寄存器1。
   位域定义UNION结构:  PMIC_OTP1_1_UNION */
#define PMIC_OTP1_1_ADDR(base)                    ((base) + (0x176))

/* 寄存器说明：OTP1回读寄存器2。
   位域定义UNION结构:  PMIC_OTP1_2_UNION */
#define PMIC_OTP1_2_ADDR(base)                    ((base) + (0x177))

/* 寄存器说明：OTP1回读寄存器3。
   位域定义UNION结构:  PMIC_OTP1_3_UNION */
#define PMIC_OTP1_3_ADDR(base)                    ((base) + (0x178))

/* 寄存器说明：OTP1控制寄存器0。
   位域定义UNION结构:  PMIC_OTP1_CTRL_0_UNION */
#define PMIC_OTP1_CTRL_0_ADDR(base)               ((base) + (0x179))

/* 寄存器说明：OTP1控制寄存器1。
   位域定义UNION结构:  PMIC_OTP1_CTRL_1_UNION */
#define PMIC_OTP1_CTRL_1_ADDR(base)               ((base) + (0x17A))

/* 寄存器说明：OTP1写操作数据寄存器。
   位域定义UNION结构:  PMIC_OTP1_WDATA_UNION */
#define PMIC_OTP1_WDATA_ADDR(base)                ((base) + (0x17B))

/* 寄存器说明：OTP1或操作寄存器0。
   位域定义UNION结构:  PMIC_OTP1_0_W_UNION */
#define PMIC_OTP1_0_W_ADDR(base)                  ((base) + (0x17C))

/* 寄存器说明：OTP1或操作寄存器1。
   位域定义UNION结构:  PMIC_OTP1_1_W_UNION */
#define PMIC_OTP1_1_W_ADDR(base)                  ((base) + (0x17D))

/* 寄存器说明：OTP1或操作寄存器2。
   位域定义UNION结构:  PMIC_OTP1_2_W_UNION */
#define PMIC_OTP1_2_W_ADDR(base)                  ((base) + (0x17E))

/* 寄存器说明：OTP1或操作寄存器3。
   位域定义UNION结构:  PMIC_OTP1_3_W_UNION */
#define PMIC_OTP1_3_W_ADDR(base)                  ((base) + (0x17F))

/* 寄存器说明：OTP2回读寄存器0。
   位域定义UNION结构:  PMIC_OTP2_0_UNION */
#define PMIC_OTP2_0_ADDR(base)                    ((base) + (0x180))

/* 寄存器说明：OTP2回读寄存器1。
   位域定义UNION结构:  PMIC_OTP2_1_UNION */
#define PMIC_OTP2_1_ADDR(base)                    ((base) + (0x181))

/* 寄存器说明：OTP2回读寄存器2。
   位域定义UNION结构:  PMIC_OTP2_2_UNION */
#define PMIC_OTP2_2_ADDR(base)                    ((base) + (0x182))

/* 寄存器说明：OTP2回读寄存器3。
   位域定义UNION结构:  PMIC_OTP2_3_UNION */
#define PMIC_OTP2_3_ADDR(base)                    ((base) + (0x183))

/* 寄存器说明：OTP2控制寄存器0。
   位域定义UNION结构:  PMIC_OTP2_CTRL_0_UNION */
#define PMIC_OTP2_CTRL_0_ADDR(base)               ((base) + (0x184))

/* 寄存器说明：OTP2控制寄存器1。
   位域定义UNION结构:  PMIC_OTP2_CTRL_1_UNION */
#define PMIC_OTP2_CTRL_1_ADDR(base)               ((base) + (0x185))

/* 寄存器说明：OTP2写操作数据寄存器。
   位域定义UNION结构:  PMIC_OTP2_WDATA_UNION */
#define PMIC_OTP2_WDATA_ADDR(base)                ((base) + (0x186))

/* 寄存器说明：OTP2或操作寄存器0。
   位域定义UNION结构:  PMIC_OTP2_0_W_UNION */
#define PMIC_OTP2_0_W_ADDR(base)                  ((base) + (0x187))

/* 寄存器说明：OTP2或操作寄存器1。
   位域定义UNION结构:  PMIC_OTP2_1_W_UNION */
#define PMIC_OTP2_1_W_ADDR(base)                  ((base) + (0x188))

/* 寄存器说明：OTP2或操作寄存器2。
   位域定义UNION结构:  PMIC_OTP2_2_W_UNION */
#define PMIC_OTP2_2_W_ADDR(base)                  ((base) + (0x189))

/* 寄存器说明：OTP2或操作寄存器3。
   位域定义UNION结构:  PMIC_OTP2_3_W_UNION */
#define PMIC_OTP2_3_W_ADDR(base)                  ((base) + (0x18A))

/* 寄存器说明：软件预留寄存器0。
   位域定义UNION结构:  PMIC_HRST_REG0_UNION */
#define PMIC_HRST_REG0_ADDR(base)                 ((base) + (0x18B))

/* 寄存器说明：软件预留寄存器1。
   位域定义UNION结构:  PMIC_HRST_REG1_UNION */
#define PMIC_HRST_REG1_ADDR(base)                 ((base) + (0x18C))

/* 寄存器说明：软件预留寄存器2。
   位域定义UNION结构:  PMIC_HRST_REG2_UNION */
#define PMIC_HRST_REG2_ADDR(base)                 ((base) + (0x18D))

/* 寄存器说明：软件预留寄存器3。
   位域定义UNION结构:  PMIC_HRST_REG3_UNION */
#define PMIC_HRST_REG3_ADDR(base)                 ((base) + (0x18E))

/* 寄存器说明：软件预留寄存器4。
   位域定义UNION结构:  PMIC_HRST_REG4_UNION */
#define PMIC_HRST_REG4_ADDR(base)                 ((base) + (0x18F))

/* 寄存器说明：软件预留寄存器5。
   位域定义UNION结构:  PMIC_HRST_REG5_UNION */
#define PMIC_HRST_REG5_ADDR(base)                 ((base) + (0x190))

/* 寄存器说明：软件预留寄存器6。
   位域定义UNION结构:  PMIC_HRST_REG6_UNION */
#define PMIC_HRST_REG6_ADDR(base)                 ((base) + (0x191))

/* 寄存器说明：软件预留寄存器7。
   位域定义UNION结构:  PMIC_HRST_REG7_UNION */
#define PMIC_HRST_REG7_ADDR(base)                 ((base) + (0x192))

/* 寄存器说明：软件预留寄存器8。
   位域定义UNION结构:  PMIC_HRST_REG8_UNION */
#define PMIC_HRST_REG8_ADDR(base)                 ((base) + (0x193))

/* 寄存器说明：软件预留寄存器9。
   位域定义UNION结构:  PMIC_HRST_REG9_UNION */
#define PMIC_HRST_REG9_ADDR(base)                 ((base) + (0x194))

/* 寄存器说明：软件预留寄存器10。
   位域定义UNION结构:  PMIC_HRST_REG10_UNION */
#define PMIC_HRST_REG10_ADDR(base)                ((base) + (0x195))

/* 寄存器说明：软件预留寄存器11。
   位域定义UNION结构:  PMIC_HRST_REG11_UNION */
#define PMIC_HRST_REG11_ADDR(base)                ((base) + (0x196))

/* 寄存器说明：软件预留寄存器12。
   位域定义UNION结构:  PMIC_HRST_REG12_UNION */
#define PMIC_HRST_REG12_ADDR(base)                ((base) + (0x197))

/* 寄存器说明：软件预留寄存器13。
   位域定义UNION结构:  PMIC_HRST_REG13_UNION */
#define PMIC_HRST_REG13_ADDR(base)                ((base) + (0x198))

/* 寄存器说明：软件预留寄存器14。
   位域定义UNION结构:  PMIC_HRST_REG14_UNION */
#define PMIC_HRST_REG14_ADDR(base)                ((base) + (0x199))

/* 寄存器说明：DEBUG寄存器
   位域定义UNION结构:  PMIC_DEBUG_CTRL_UNION */
#define PMIC_DEBUG_CTRL_ADDR(base)                ((base) + (0x19A))

/* 寄存器说明：数字系统debug预留寄存器0。
   位域定义UNION结构:  PMIC_SYS_DEBUG0_UNION */
#define PMIC_SYS_DEBUG0_ADDR(base)                ((base) + (0x19B))

/* 寄存器说明：数字系统debug预留寄存器1。
   位域定义UNION结构:  PMIC_SYS_DEBUG1_UNION */
#define PMIC_SYS_DEBUG1_ADDR(base)                ((base) + (0x19C))

/* 寄存器说明：debug寄存器写屏蔽控制寄存器。
   位域定义UNION结构:  PMIC_DEBUG_LOCK_UNION */
#define PMIC_DEBUG_LOCK_ADDR(base)                ((base) + (0x19D))

/* 寄存器说明：DAC0 din高位映射寄存器。
   位域定义UNION结构:  PMIC_DAC0_DIN_MSB_UNION */
#define PMIC_DAC0_DIN_MSB_ADDR(base)              ((base) + (0x19F))

/* 寄存器说明：DAC0 din低位映射寄存器。
   位域定义UNION结构:  PMIC_DAC0_DIN_LSB_UNION */
#define PMIC_DAC0_DIN_LSB_ADDR(base)              ((base) + (0x1A0))

/* 寄存器说明：DAC1 din高位映射寄存器。
   位域定义UNION结构:  PMIC_DAC1_DIN_MSB_UNION */
#define PMIC_DAC1_DIN_MSB_ADDR(base)              ((base) + (0x1A1))

/* 寄存器说明：DAC1 din低位映射寄存器。
   位域定义UNION结构:  PMIC_DAC1_DIN_LSB_UNION */
#define PMIC_DAC1_DIN_LSB_ADDR(base)              ((base) + (0x1A2))



/****************************************************************************
                     (2/5) PMU_IRQ
 ****************************************************************************/
/* 寄存器说明：中断寄存器0。
   位域定义UNION结构:  PMIC_IRQ0_UNION */
#define PMIC_IRQ0_ADDR(base)                      ((base) + (0x1B0))

/* 寄存器说明：中断寄存器1。
   位域定义UNION结构:  PMIC_IRQ1_UNION */
#define PMIC_IRQ1_ADDR(base)                      ((base) + (0x1B1))

/* 寄存器说明：OCP中断寄存器0。
   位域定义UNION结构:  PMIC_OCP_IRQ0_UNION */
#define PMIC_OCP_IRQ0_ADDR(base)                  ((base) + (0x1B2))

/* 寄存器说明：OCP中断寄存器1。
   位域定义UNION结构:  PMIC_OCP_IRQ1_UNION */
#define PMIC_OCP_IRQ1_ADDR(base)                  ((base) + (0x1B3))

/* 寄存器说明：OCP中断寄存器3。
   位域定义UNION结构:  PMIC_OCP_IRQ2_UNION */
#define PMIC_OCP_IRQ2_ADDR(base)                  ((base) + (0x1B4))

/* 寄存器说明：OCP中断寄存器4。
   位域定义UNION结构:  PMIC_OCP_IRQ3_UNION */
#define PMIC_OCP_IRQ3_ADDR(base)                  ((base) + (0x1B5))

/* 寄存器说明：OCP中断寄存器5。
   位域定义UNION结构:  PMIC_OCP_IRQ4_UNION */
#define PMIC_OCP_IRQ4_ADDR(base)                  ((base) + (0x1B6))

/* 寄存器说明：OCP中断寄存器6。
   位域定义UNION结构:  PMIC_OCP_IRQ5_UNION */
#define PMIC_OCP_IRQ5_ADDR(base)                  ((base) + (0x1B7))

/* 寄存器说明：BUKC0-3，LDO0-3 OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP0_UNION */
#define PMIC_NP_OCP0_ADDR(base)                   ((base) + (0x1B8))

/* 寄存器说明：LDO4-12 OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP1_UNION */
#define PMIC_NP_OCP1_ADDR(base)                   ((base) + (0x1B9))

/* 寄存器说明：LDO12-20 OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP2_UNION */
#define PMIC_NP_OCP2_ADDR(base)                   ((base) + (0x1BA))

/* 寄存器说明：LDO21-28 OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP3_UNION */
#define PMIC_NP_OCP3_ADDR(base)                   ((base) + (0x1BB))

/* 寄存器说明：LDO31-34 CLASSD OCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_OCP4_UNION */
#define PMIC_NP_OCP4_ADDR(base)                   ((base) + (0x1BC))

/* 寄存器说明：BUCK0-3 SCP事件记录寄存器。
   位域定义UNION结构:  PMIC_NP_SCP_UNION */
#define PMIC_NP_SCP_ADDR(base)                    ((base) + (0x1BD))

/* 寄存器说明：事件记录寄存器0。
   位域定义UNION结构:  PMIC_NP_RECORD0_UNION */
#define PMIC_NP_RECORD0_ADDR(base)                ((base) + (0x1BE))

/* 寄存器说明：事件记录寄存器1。
   位域定义UNION结构:  PMIC_NP_RECORD1_UNION */
#define PMIC_NP_RECORD1_ADDR(base)                ((base) + (0x1BF))

/* 寄存器说明：事件记录寄存器2。
   位域定义UNION结构:  PMIC_NP_RECORD2_UNION */
#define PMIC_NP_RECORD2_ADDR(base)                ((base) + (0x1C0))

/* 寄存器说明：事件记录寄存器3。
   位域定义UNION结构:  PMIC_NP_RECORD3_UNION */
#define PMIC_NP_RECORD3_ADDR(base)                ((base) + (0x1C1))



/****************************************************************************
                     (3/5) PMU_RTC
 ****************************************************************************/
/* 寄存器说明：RTC当前时间寄存器bit[7:0]。
   位域定义UNION结构:  PMIC_RTCDR0_UNION */
#define PMIC_RTCDR0_ADDR(base)                    ((base) + (0x1D0))

/* 寄存器说明：RTC当前时间寄存器bit[15:8]。
   位域定义UNION结构:  PMIC_RTCDR1_UNION */
#define PMIC_RTCDR1_ADDR(base)                    ((base) + (0x1D1))

/* 寄存器说明：RTC当前时间寄存器bit[23:16]。
   位域定义UNION结构:  PMIC_RTCDR2_UNION */
#define PMIC_RTCDR2_ADDR(base)                    ((base) + (0x1D2))

/* 寄存器说明：RTC当前时间寄存器bit[31:24]。
   位域定义UNION结构:  PMIC_RTCDR3_UNION */
#define PMIC_RTCDR3_ADDR(base)                    ((base) + (0x1D3))

/* 寄存器说明：RTC比较寄存器bit[7:0]。
   位域定义UNION结构:  PMIC_RTCMR0_UNION */
#define PMIC_RTCMR0_ADDR(base)                    ((base) + (0x1D4))

/* 寄存器说明：RTC比较寄存器bit[15:8]。
   位域定义UNION结构:  PMIC_RTCMR1_UNION */
#define PMIC_RTCMR1_ADDR(base)                    ((base) + (0x1D5))

/* 寄存器说明：RTC比较寄存器bit[23:16]。
   位域定义UNION结构:  PMIC_RTCMR2_UNION */
#define PMIC_RTCMR2_ADDR(base)                    ((base) + (0x1D6))

/* 寄存器说明：RTC比较寄存器bit[31:24]。
   位域定义UNION结构:  PMIC_RTCMR3_UNION */
#define PMIC_RTCMR3_ADDR(base)                    ((base) + (0x1D7))

/* 寄存器说明：RTC加载寄存器bit[7:0]。
   位域定义UNION结构:  PMIC_RTCLR0_UNION */
#define PMIC_RTCLR0_ADDR(base)                    ((base) + (0x1D8))

/* 寄存器说明：RTC加载寄存器bit[15:8]。
   位域定义UNION结构:  PMIC_RTCLR1_UNION */
#define PMIC_RTCLR1_ADDR(base)                    ((base) + (0x1D9))

/* 寄存器说明：RTC加载寄存器bit[23:16]。
   位域定义UNION结构:  PMIC_RTCLR2_UNION */
#define PMIC_RTCLR2_ADDR(base)                    ((base) + (0x1DA))

/* 寄存器说明：RTC加载寄存器bit[31:24]。
   位域定义UNION结构:  PMIC_RTCLR3_UNION */
#define PMIC_RTCLR3_ADDR(base)                    ((base) + (0x1DB))

/* 寄存器说明：RTC控制寄存器。
   位域定义UNION结构:  PMIC_RTCCTRL_UNION */
#define PMIC_RTCCTRL_ADDR(base)                   ((base) + (0x1DC))

/* 寄存器说明：XO_THRESOLD[7:0]寄存器。
   位域定义UNION结构:  PMIC_XO_THRESOLD0_UNION */
#define PMIC_XO_THRESOLD0_ADDR(base)              ((base) + (0x1DD))

/* 寄存器说明：XO_THRESOLD[15:8]寄存器。
   位域定义UNION结构:  PMIC_XO_THRESOLD1_UNION */
#define PMIC_XO_THRESOLD1_ADDR(base)              ((base) + (0x1DE))

/* 寄存器说明：CRC_VALUE[7:0]寄存器。
   位域定义UNION结构:  PMIC_CRC_VAULE0_UNION */
#define PMIC_CRC_VAULE0_ADDR(base)                ((base) + (0x1DF))

/* 寄存器说明：CRC_VALUE[15:8]寄存器。
   位域定义UNION结构:  PMIC_CRC_VAULE1_UNION */
#define PMIC_CRC_VAULE1_ADDR(base)                ((base) + (0x1E0))

/* 寄存器说明：CRC_VALUE[20:16]寄存器。
   位域定义UNION结构:  PMIC_CRC_VAULE2_UNION */
#define PMIC_CRC_VAULE2_ADDR(base)                ((base) + (0x1E1))

/* 寄存器说明：RTC上电拍照[7:0]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRUP_TIMER0_UNION */
#define PMIC_RTC_PWRUP_TIMER0_ADDR(base)          ((base) + (0x1E2))

/* 寄存器说明：RTC上电拍照[15:8]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRUP_TIMER1_UNION */
#define PMIC_RTC_PWRUP_TIMER1_ADDR(base)          ((base) + (0x1E3))

/* 寄存器说明：RTC上电拍照[23:16]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRUP_TIMER2_UNION */
#define PMIC_RTC_PWRUP_TIMER2_ADDR(base)          ((base) + (0x1E4))

/* 寄存器说明：RTC上电拍照[31:24]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRUP_TIMER3_UNION */
#define PMIC_RTC_PWRUP_TIMER3_ADDR(base)          ((base) + (0x1E5))

/* 寄存器说明：RTC下电拍照[7:0]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRDOWN_TIMER0_UNION */
#define PMIC_RTC_PWRDOWN_TIMER0_ADDR(base)        ((base) + (0x1E6))

/* 寄存器说明：RTC下电拍照[15:8]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRDOWN_TIMER1_UNION */
#define PMIC_RTC_PWRDOWN_TIMER1_ADDR(base)        ((base) + (0x1E7))

/* 寄存器说明：RTC下电拍照[23:16]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRDOWN_TIMER2_UNION */
#define PMIC_RTC_PWRDOWN_TIMER2_ADDR(base)        ((base) + (0x1E8))

/* 寄存器说明：RTC下电拍照[31:24]寄存器。
   位域定义UNION结构:  PMIC_RTC_PWRDOWN_TIMER3_UNION */
#define PMIC_RTC_PWRDOWN_TIMER3_ADDR(base)        ((base) + (0x1E9))



/****************************************************************************
                     (4/5) PMU_COUL
 ****************************************************************************/
/* 寄存器说明：库仑计中断寄存器。
   位域定义UNION结构:  PMIC_COUL_IRQ_UNION */
#define PMIC_COUL_IRQ_ADDR(base)                  ((base) + (0x1F0))

/* 寄存器说明：库仑计中断屏蔽寄存器。
   位域定义UNION结构:  PMIC_COUL_IRQ_MASK_UNION */
#define PMIC_COUL_IRQ_MASK_ADDR(base)             ((base) + (0x1F1))

/* 寄存器说明：当前电流[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT_0_UNION */
#define PMIC_CURRENT_0_ADDR(base)                 ((base) + (0x1F2))

/* 寄存器说明：当前电流[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT_1_UNION */
#define PMIC_CURRENT_1_ADDR(base)                 ((base) + (0x1F3))

/* 寄存器说明：当前电压[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT_0_UNION */
#define PMIC_V_OUT_0_ADDR(base)                   ((base) + (0x1F4))

/* 寄存器说明：当前电压[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT_1_UNION */
#define PMIC_V_OUT_1_ADDR(base)                   ((base) + (0x1F5))

/* 寄存器说明：库仑计控制寄存器。
   位域定义UNION结构:  PMIC_CLJ_CTRL_REG_UNION */
#define PMIC_CLJ_CTRL_REG_ADDR(base)              ((base) + (0x1F6))

/* 寄存器说明：ECO_REFLASH工作时间寄存器。
   位域定义UNION结构:  PMIC_ECO_REFALSH_TIME_UNION */
#define PMIC_ECO_REFALSH_TIME_ADDR(base)          ((base) + (0x1F7))

/* 寄存器说明：cl_out[7:0]寄存器。
   位域定义UNION结构:  PMIC_CL_OUT0_UNION */
#define PMIC_CL_OUT0_ADDR(base)                   ((base) + (0x1F8))

/* 寄存器说明：cl_out[15:8]寄存器。
   位域定义UNION结构:  PMIC_CL_OUT1_UNION */
#define PMIC_CL_OUT1_ADDR(base)                   ((base) + (0x1F9))

/* 寄存器说明：cl_out[23:16]寄存器。
   位域定义UNION结构:  PMIC_CL_OUT2_UNION */
#define PMIC_CL_OUT2_ADDR(base)                   ((base) + (0x1FA))

/* 寄存器说明：cl_out[31:24]寄存器。
   位域定义UNION结构:  PMIC_CL_OUT3_UNION */
#define PMIC_CL_OUT3_ADDR(base)                   ((base) + (0x1FB))

/* 寄存器说明：cl_in[7:0]寄存器。
   位域定义UNION结构:  PMIC_CL_IN0_UNION */
#define PMIC_CL_IN0_ADDR(base)                    ((base) + (0x1FC))

/* 寄存器说明：cl_in[15:8]寄存器。
   位域定义UNION结构:  PMIC_CL_IN1_UNION */
#define PMIC_CL_IN1_ADDR(base)                    ((base) + (0x1FD))

/* 寄存器说明：cl_in[23:16]寄存器。
   位域定义UNION结构:  PMIC_CL_IN2_UNION */
#define PMIC_CL_IN2_ADDR(base)                    ((base) + (0x1FE))

/* 寄存器说明：cl_in[31:24]寄存器。
   位域定义UNION结构:  PMIC_CL_IN3_UNION */
#define PMIC_CL_IN3_ADDR(base)                    ((base) + (0x1FF))

/* 寄存器说明：chg_timer[7:0]寄存器。
   位域定义UNION结构:  PMIC_CHG_TIMER0_UNION */
#define PMIC_CHG_TIMER0_ADDR(base)                ((base) + (0x200))

/* 寄存器说明：chg_timer[15:8]寄存器。
   位域定义UNION结构:  PMIC_CHG_TIMER1_UNION */
#define PMIC_CHG_TIMER1_ADDR(base)                ((base) + (0x201))

/* 寄存器说明：chg_timer[23:16]寄存器。
   位域定义UNION结构:  PMIC_CHG_TIMER2_UNION */
#define PMIC_CHG_TIMER2_ADDR(base)                ((base) + (0x202))

/* 寄存器说明：chg_timer[31:24]寄存器。
   位域定义UNION结构:  PMIC_CHG_TIMER3_UNION */
#define PMIC_CHG_TIMER3_ADDR(base)                ((base) + (0x203))

/* 寄存器说明：load_timer[7:0]寄存器。
   位域定义UNION结构:  PMIC_LOAD_TIMER0_UNION */
#define PMIC_LOAD_TIMER0_ADDR(base)               ((base) + (0x204))

/* 寄存器说明：load_timer[15:8]寄存器。
   位域定义UNION结构:  PMIC_LOAD_TIMER1_UNION */
#define PMIC_LOAD_TIMER1_ADDR(base)               ((base) + (0x205))

/* 寄存器说明：load_timer[23:16]寄存器。
   位域定义UNION结构:  PMIC_LOAD_TIMER2_UNION */
#define PMIC_LOAD_TIMER2_ADDR(base)               ((base) + (0x206))

/* 寄存器说明：load_timer[31:24]寄存器。
   位域定义UNION结构:  PMIC_LOAD_TIMER3_UNION */
#define PMIC_LOAD_TIMER3_ADDR(base)               ((base) + (0x207))

/* 寄存器说明：cl_int[7:0]寄存器。
   位域定义UNION结构:  PMIC_CL_INT0_UNION */
#define PMIC_CL_INT0_ADDR(base)                   ((base) + (0x208))

/* 寄存器说明：cl_int[15:8]寄存器。
   位域定义UNION结构:  PMIC_CL_INT1_UNION */
#define PMIC_CL_INT1_ADDR(base)                   ((base) + (0x209))

/* 寄存器说明：cl_int[23:16]寄存器。
   位域定义UNION结构:  PMIC_CL_INT2_UNION */
#define PMIC_CL_INT2_ADDR(base)                   ((base) + (0x20A))

/* 寄存器说明：cl_int[31:24]寄存器。
   位域定义UNION结构:  PMIC_CL_INT3_UNION */
#define PMIC_CL_INT3_ADDR(base)                   ((base) + (0x20B))

/* 寄存器说明：v_int[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_INT0_UNION */
#define PMIC_V_INT0_ADDR(base)                    ((base) + (0x20C))

/* 寄存器说明：v_int[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_INT1_UNION */
#define PMIC_V_INT1_ADDR(base)                    ((base) + (0x20D))

/* 寄存器说明：offset_current[7:0]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_CURRENT0_UNION */
#define PMIC_OFFSET_CURRENT0_ADDR(base)           ((base) + (0x20E))

/* 寄存器说明：offset_current[15:8]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_CURRENT1_UNION */
#define PMIC_OFFSET_CURRENT1_ADDR(base)           ((base) + (0x20F))

/* 寄存器说明：offset_voltage[7:0]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_VOLTAGE0_UNION */
#define PMIC_OFFSET_VOLTAGE0_ADDR(base)           ((base) + (0x210))

/* 寄存器说明：offset_voltage[15:8]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_VOLTAGE1_UNION */
#define PMIC_OFFSET_VOLTAGE1_ADDR(base)           ((base) + (0x211))

/* 寄存器说明：v_ocv_data[7:0]寄存器。
   位域定义UNION结构:  PMIC_OCV_VOLTAGE0_UNION */
#define PMIC_OCV_VOLTAGE0_ADDR(base)              ((base) + (0x212))

/* 寄存器说明：v_ocv_data[15:8]寄存器。
   位域定义UNION结构:  PMIC_OCV_VOLTAGE1_UNION */
#define PMIC_OCV_VOLTAGE1_ADDR(base)              ((base) + (0x213))

/* 寄存器说明：i_ocv_data[7:0]寄存器。
   位域定义UNION结构:  PMIC_OCV_CURRENT0_UNION */
#define PMIC_OCV_CURRENT0_ADDR(base)              ((base) + (0x214))

/* 寄存器说明：i_ocv_data[15:8]寄存器。
   位域定义UNION结构:  PMIC_OCV_CURRENT1_UNION */
#define PMIC_OCV_CURRENT1_ADDR(base)              ((base) + (0x215))

/* 寄存器说明：eco_out_clin[7:0]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLIN_0_UNION */
#define PMIC_ECO_OUT_CLIN_0_ADDR(base)            ((base) + (0x216))

/* 寄存器说明：eco_out_clin[15:8]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLIN_1_UNION */
#define PMIC_ECO_OUT_CLIN_1_ADDR(base)            ((base) + (0x217))

/* 寄存器说明：eco_out_clin[23:16]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLIN_2_UNION */
#define PMIC_ECO_OUT_CLIN_2_ADDR(base)            ((base) + (0x218))

/* 寄存器说明：eco_out_clin[31:24]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLIN_3_UNION */
#define PMIC_ECO_OUT_CLIN_3_ADDR(base)            ((base) + (0x219))

/* 寄存器说明：eco_out_clout[7:0]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLOUT_0_UNION */
#define PMIC_ECO_OUT_CLOUT_0_ADDR(base)           ((base) + (0x21A))

/* 寄存器说明：eco_out_clout[15:8]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLOUT_1_UNION */
#define PMIC_ECO_OUT_CLOUT_1_ADDR(base)           ((base) + (0x21B))

/* 寄存器说明：eco_out_clout[23:16]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLOUT_2_UNION */
#define PMIC_ECO_OUT_CLOUT_2_ADDR(base)           ((base) + (0x21C))

/* 寄存器说明：eco_out_clout[31:24]寄存器。
   位域定义UNION结构:  PMIC_ECO_OUT_CLOUT_3_UNION */
#define PMIC_ECO_OUT_CLOUT_3_ADDR(base)           ((base) + (0x21D))

/* 寄存器说明：v_out_pre0[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE0_UNION */
#define PMIC_V_OUT0_PRE0_ADDR(base)               ((base) + (0x21E))

/* 寄存器说明：v_out_pre0[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE0_UNION */
#define PMIC_V_OUT1_PRE0_ADDR(base)               ((base) + (0x21F))

/* 寄存器说明：v_out_pre1[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE1_UNION */
#define PMIC_V_OUT0_PRE1_ADDR(base)               ((base) + (0x220))

/* 寄存器说明：v_out_pre1[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE1_UNION */
#define PMIC_V_OUT1_PRE1_ADDR(base)               ((base) + (0x221))

/* 寄存器说明：v_out_pre2[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE2_UNION */
#define PMIC_V_OUT0_PRE2_ADDR(base)               ((base) + (0x222))

/* 寄存器说明：v_out_pre2[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE2_UNION */
#define PMIC_V_OUT1_PRE2_ADDR(base)               ((base) + (0x223))

/* 寄存器说明：v_out_pre3[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE3_UNION */
#define PMIC_V_OUT0_PRE3_ADDR(base)               ((base) + (0x224))

/* 寄存器说明：v_out_pre3[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE3_UNION */
#define PMIC_V_OUT1_PRE3_ADDR(base)               ((base) + (0x225))

/* 寄存器说明：v_out_pre4[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE4_UNION */
#define PMIC_V_OUT0_PRE4_ADDR(base)               ((base) + (0x226))

/* 寄存器说明：v_out_pre4[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE4_UNION */
#define PMIC_V_OUT1_PRE4_ADDR(base)               ((base) + (0x227))

/* 寄存器说明：v_out_pre5[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE5_UNION */
#define PMIC_V_OUT0_PRE5_ADDR(base)               ((base) + (0x228))

/* 寄存器说明：v_out_pre5[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE5_UNION */
#define PMIC_V_OUT1_PRE5_ADDR(base)               ((base) + (0x229))

/* 寄存器说明：v_out_pre6[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE6_UNION */
#define PMIC_V_OUT0_PRE6_ADDR(base)               ((base) + (0x22A))

/* 寄存器说明：v_out_pre6[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE6_UNION */
#define PMIC_V_OUT1_PRE6_ADDR(base)               ((base) + (0x22B))

/* 寄存器说明：v_out_pre7[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE7_UNION */
#define PMIC_V_OUT0_PRE7_ADDR(base)               ((base) + (0x22C))

/* 寄存器说明：v_out_pre7[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE7_UNION */
#define PMIC_V_OUT1_PRE7_ADDR(base)               ((base) + (0x22D))

/* 寄存器说明：v_out_pre8[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE8_UNION */
#define PMIC_V_OUT0_PRE8_ADDR(base)               ((base) + (0x22E))

/* 寄存器说明：v_out_pre8[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE8_UNION */
#define PMIC_V_OUT1_PRE8_ADDR(base)               ((base) + (0x22F))

/* 寄存器说明：v_out_pre9[7:0]寄存器。
   位域定义UNION结构:  PMIC_V_OUT0_PRE9_UNION */
#define PMIC_V_OUT0_PRE9_ADDR(base)               ((base) + (0x230))

/* 寄存器说明：v_out_pre9[15:8]寄存器。
   位域定义UNION结构:  PMIC_V_OUT1_PRE9_UNION */
#define PMIC_V_OUT1_PRE9_ADDR(base)               ((base) + (0x231))

/* 寄存器说明：current_pre0[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE0_UNION */
#define PMIC_CURRENT0_PRE0_ADDR(base)             ((base) + (0x232))

/* 寄存器说明：current_pre0[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE0_UNION */
#define PMIC_CURRENT1_PRE0_ADDR(base)             ((base) + (0x233))

/* 寄存器说明：current_pre1[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE1_UNION */
#define PMIC_CURRENT0_PRE1_ADDR(base)             ((base) + (0x234))

/* 寄存器说明：current_pre1[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE1_UNION */
#define PMIC_CURRENT1_PRE1_ADDR(base)             ((base) + (0x235))

/* 寄存器说明：current_pre2[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE2_UNION */
#define PMIC_CURRENT0_PRE2_ADDR(base)             ((base) + (0x236))

/* 寄存器说明：current_pre2[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE2_UNION */
#define PMIC_CURRENT1_PRE2_ADDR(base)             ((base) + (0x237))

/* 寄存器说明：current_pre3[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE3_UNION */
#define PMIC_CURRENT0_PRE3_ADDR(base)             ((base) + (0x238))

/* 寄存器说明：current_pre3[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE3_UNION */
#define PMIC_CURRENT1_PRE3_ADDR(base)             ((base) + (0x239))

/* 寄存器说明：current_pre4[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE4_UNION */
#define PMIC_CURRENT0_PRE4_ADDR(base)             ((base) + (0x23A))

/* 寄存器说明：current_pre4[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE4_UNION */
#define PMIC_CURRENT1_PRE4_ADDR(base)             ((base) + (0x23B))

/* 寄存器说明：current_pre5[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE5_UNION */
#define PMIC_CURRENT0_PRE5_ADDR(base)             ((base) + (0x23C))

/* 寄存器说明：current_pre5[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE5_UNION */
#define PMIC_CURRENT1_PRE5_ADDR(base)             ((base) + (0x23D))

/* 寄存器说明：current_pre6[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE6_UNION */
#define PMIC_CURRENT0_PRE6_ADDR(base)             ((base) + (0x23E))

/* 寄存器说明：current_pre6[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE6_UNION */
#define PMIC_CURRENT1_PRE6_ADDR(base)             ((base) + (0x23F))

/* 寄存器说明：current_pre7[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE7_UNION */
#define PMIC_CURRENT0_PRE7_ADDR(base)             ((base) + (0x240))

/* 寄存器说明：current_pre7[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE7_UNION */
#define PMIC_CURRENT1_PRE7_ADDR(base)             ((base) + (0x241))

/* 寄存器说明：current_pre8[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE8_UNION */
#define PMIC_CURRENT0_PRE8_ADDR(base)             ((base) + (0x242))

/* 寄存器说明：current_pre8[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE8_UNION */
#define PMIC_CURRENT1_PRE8_ADDR(base)             ((base) + (0x243))

/* 寄存器说明：current_pre9[7:0]寄存器。
   位域定义UNION结构:  PMIC_CURRENT0_PRE9_UNION */
#define PMIC_CURRENT0_PRE9_ADDR(base)             ((base) + (0x244))

/* 寄存器说明：current_pre9[15:8]寄存器。
   位域定义UNION结构:  PMIC_CURRENT1_PRE9_UNION */
#define PMIC_CURRENT1_PRE9_ADDR(base)             ((base) + (0x245))

/* 寄存器说明：电流偏置调整[7:0]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_CURRENT_MOD_0_UNION */
#define PMIC_OFFSET_CURRENT_MOD_0_ADDR(base)      ((base) + (0x246))

/* 寄存器说明：电流偏置调整[15:8]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_CURRENT_MOD_1_UNION */
#define PMIC_OFFSET_CURRENT_MOD_1_ADDR(base)      ((base) + (0x247))

/* 寄存器说明：电压偏置调整[7:0]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_VOLTAGE_MOD_0_UNION */
#define PMIC_OFFSET_VOLTAGE_MOD_0_ADDR(base)      ((base) + (0x248))

/* 寄存器说明：电压偏置调整[15:8]寄存器。
   位域定义UNION结构:  PMIC_OFFSET_VOLTAGE_MOD_1_UNION */
#define PMIC_OFFSET_VOLTAGE_MOD_1_ADDR(base)      ((base) + (0x249))

/* 寄存器说明：库仑计模拟保留0寄存器
   位域定义UNION结构:  PMIC_COUL_RESERVE0_UNION */
#define PMIC_COUL_RESERVE0_ADDR(base)             ((base) + (0x24A))

/* 寄存器说明：库仑计保留0寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED0_UNION */
#define PMIC_CLJ_RESERVED0_ADDR(base)             ((base) + (0x24B))

/* 寄存器说明：库仑计保留1寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED1_UNION */
#define PMIC_CLJ_RESERVED1_ADDR(base)             ((base) + (0x24C))

/* 寄存器说明：库仑计保留2寄存器。
   位域定义UNION结构:  PMIC_CLJ_RESERVED2_UNION */
#define PMIC_CLJ_RESERVED2_ADDR(base)             ((base) + (0x24D))

/* 寄存器说明：PMU软复位寄存器。
   位域定义UNION结构:  PMIC_PMU_SOFT_RST_UNION */
#define PMIC_PMU_SOFT_RST_ADDR(base)              ((base) + (0x24E))

/* 寄存器说明：库仑计DEBUG专用1寄存器。
   位域定义UNION结构:  PMIC_CLJ_DEBUG_UNION */
#define PMIC_CLJ_DEBUG_ADDR(base)                 ((base) + (0x24F))

/* 寄存器说明：库仑计DEBUG专用2寄存器。
   位域定义UNION结构:  PMIC_CLJ_DEBUG_2_UNION */
#define PMIC_CLJ_DEBUG_2_ADDR(base)               ((base) + (0x250))

/* 寄存器说明：库仑计DEBUG专用3寄存器。
   位域定义UNION结构:  PMIC_STATE_TEST_UNION */
#define PMIC_STATE_TEST_ADDR(base)                ((base) + (0x251))

/* 寄存器说明：库仑计控制寄存器2
   位域定义UNION结构:  PMIC_CLJ_CTRL_REGS2_UNION */
#define PMIC_CLJ_CTRL_REGS2_ADDR(base)            ((base) + (0x252))

/* 寄存器说明：DEBUG寄存器写保护。
   位域定义UNION结构:  PMIC_DEBUG_WRITE_PRO_UNION */
#define PMIC_DEBUG_WRITE_PRO_ADDR(base)           ((base) + (0x253))



/****************************************************************************
                     (5/5) PMU_CODEC
 ****************************************************************************/
/* 寄存器说明：时钟使能配置寄存器。
   位域定义UNION结构:  PMIC_CLK_EN_CFG_UNION */
#define PMIC_CLK_EN_CFG_ADDR(base)                ((base) + (0x260))

/* 寄存器说明：数模接口时钟沿选择。
   位域定义UNION结构:  PMIC_CLK_EDGE_CFG_UNION */
#define PMIC_CLK_EDGE_CFG_ADDR(base)              ((base) + (0x261))

/* 寄存器说明：环回控制。
   位域定义UNION结构:  PMIC_LOOPBACK_CFG_UNION */
#define PMIC_LOOPBACK_CFG_ADDR(base)              ((base) + (0x262))

/* 寄存器说明：模拟中断原始状态寄存器。
   位域定义UNION结构:  PMIC_ANA_IRQ_SIG_STAT_UNION */
#define PMIC_ANA_IRQ_SIG_STAT_ADDR(base)          ((base) + (0x263))

/* 寄存器说明：ANA_IRQ_REG中断屏蔽寄存器。
   位域定义UNION结构:  PMIC_ANA_IRQM_REG0_UNION */
#define PMIC_ANA_IRQM_REG0_ADDR(base)             ((base) + (0x264))

/* 寄存器说明：模拟中断寄存器。0，写1清，读上报中断信息。
   位域定义UNION结构:  PMIC_ANA_IRQ_REG0_UNION */
#define PMIC_ANA_IRQ_REG0_ADDR(base)              ((base) + (0x265))

/* 寄存器说明：hs_det_irq去抖配置。
   位域定义UNION结构:  PMIC_DEB_CNT_HS_DET_CFG_UNION */
#define PMIC_DEB_CNT_HS_DET_CFG_ADDR(base)        ((base) + (0x266))

/* 寄存器说明：hs_mic_irq去抖配置。
   位域定义UNION结构:  PMIC_DEB_CNT_HS_MIC_CFG_UNION */
#define PMIC_DEB_CNT_HS_MIC_CFG_ADDR(base)        ((base) + (0x267))

/* 寄存器说明：reserved。
   位域定义UNION结构:  PMIC_CODEC_DIG_RES02_UNION */
#define PMIC_CODEC_DIG_RES02_ADDR(base)           ((base) + (0x268))

/* 寄存器说明：reserved。
   位域定义UNION结构:  PMIC_CODEC_DIG_RES03_UNION */
#define PMIC_CODEC_DIG_RES03_ADDR(base)           ((base) + (0x269))

/* 寄存器说明：ADC通路PD信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW01_UNION */
#define PMIC_CODEC_ANA_RW01_ADDR(base)            ((base) + (0x26A))

/* 寄存器说明：MICBIAS,MBHD信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW02_UNION */
#define PMIC_CODEC_ANA_RW02_ADDR(base)            ((base) + (0x26B))

/* 寄存器说明：Headphone和MIXEROUT的PD信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW03_UNION */
#define PMIC_CODEC_ANA_RW03_ADDR(base)            ((base) + (0x26C))

/* 寄存器说明：VREF电阻选择信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW04_UNION */
#define PMIC_CODEC_ANA_RW04_ADDR(base)            ((base) + (0x26D))

/* 寄存器说明：LINEPGAL通路选择及增益控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW05_UNION */
#define PMIC_CODEC_ANA_RW05_ADDR(base)            ((base) + (0x26E))

/* 寄存器说明：LINEPGAR通路选择及增益控制控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW06_UNION */
#define PMIC_CODEC_ANA_RW06_ADDR(base)            ((base) + (0x26F))

/* 寄存器说明：AUXPGAR通路选择及增益控制控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW07_UNION */
#define PMIC_CODEC_ANA_RW07_ADDR(base)            ((base) + (0x270))

/* 寄存器说明：MAINPGAR通路选择及增益控制控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW08_UNION */
#define PMIC_CODEC_ANA_RW08_ADDR(base)            ((base) + (0x271))

/* 寄存器说明：ADCR_MIXIN通路选择信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW09_UNION */
#define PMIC_CODEC_ANA_RW09_ADDR(base)            ((base) + (0x272))

/* 寄存器说明：ADCL_MIXIN通路选择信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW10_UNION */
#define PMIC_CODEC_ANA_RW10_ADDR(base)            ((base) + (0x273))

/* 寄存器说明：ADCL时序控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW11_UNION */
#define PMIC_CODEC_ANA_RW11_ADDR(base)            ((base) + (0x274))

/* 寄存器说明：ADCR时序控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW12_UNION */
#define PMIC_CODEC_ANA_RW12_ADDR(base)            ((base) + (0x275))

/* 寄存器说明：MIXOUT_HSL，MIXOUT_HSR通路选择信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW13_UNION */
#define PMIC_CODEC_ANA_RW13_ADDR(base)            ((base) + (0x276))

/* 寄存器说明：MIXOUT_EAR通路选择信号。，增益选择信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW14_UNION */
#define PMIC_CODEC_ANA_RW14_ADDR(base)            ((base) + (0x277))

/* 寄存器说明：DACICELL电流控制信号。，ChargePump死区时间控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW15_UNION */
#define PMIC_CODEC_ANA_RW15_ADDR(base)            ((base) + (0x278))

/* 寄存器说明：Headphonesoft使能信号。，ChargePump控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW16_UNION */
#define PMIC_CODEC_ANA_RW16_ADDR(base)            ((base) + (0x279))

/* 寄存器说明：HeadphoneL增益控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW17_UNION */
#define PMIC_CODEC_ANA_RW17_ADDR(base)            ((base) + (0x27A))

/* 寄存器说明：HeadphonR增益控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW18_UNION */
#define PMIC_CODEC_ANA_RW18_ADDR(base)            ((base) + (0x27B))

/* 寄存器说明：Earphone增益控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW19_UNION */
#define PMIC_CODEC_ANA_RW19_ADDR(base)            ((base) + (0x27C))

/* 寄存器说明：POP音延时控制信号。，ramp产生电路控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW20_UNION */
#define PMIC_CODEC_ANA_RW20_ADDR(base)            ((base) + (0x27D))

/* 寄存器说明：防POP电路控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW21_UNION */
#define PMIC_CODEC_ANA_RW21_ADDR(base)            ((base) + (0x27E))

/* 寄存器说明：HSMICBIAS，MICBIAS1输出偏置电压控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW22_UNION */
#define PMIC_CODEC_ANA_RW22_ADDR(base)            ((base) + (0x27F))

/* 寄存器说明：HSD_CTRL<2:0>,HSMICBIAS,MICBIAS1放电使能信号。，MBHD使能信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW23_UNION */
#define PMIC_CODEC_ANA_RW23_ADDR(base)            ((base) + (0x280))

/* 寄存器说明：MBHD_VREF_CTRL[7:0]。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW24_UNION */
#define PMIC_CODEC_ANA_RW24_ADDR(base)            ((base) + (0x281))

/* 寄存器说明：CP_CLK_CTRL[7:0]。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW25_UNION */
#define PMIC_CODEC_ANA_RW25_ADDR(base)            ((base) + (0x282))

/* 寄存器说明：ADC，DAC时钟沿选择信号。，ADC，DACchopper时钟选择信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW26_UNION */
#define PMIC_CODEC_ANA_RW26_ADDR(base)            ((base) + (0x283))

/* 寄存器说明：RX，ADC_SDM,LINEIN,MICPGA,CTCM，chopperbaypass信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW27_UNION */
#define PMIC_CODEC_ANA_RW27_ADDR(base)            ((base) + (0x284))

/* 寄存器说明：TX，DAC，MIXER_EAR,MIXER_HP，chopperbaypass信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW28_UNION */
#define PMIC_CODEC_ANA_RW28_ADDR(base)            ((base) + (0x285))

/* 寄存器说明：CODEC_IBIAS_ADJ1（HeadphoneMIXER_HP电流控制信号。）
   位域定义UNION结构:  PMIC_CODEC_ANA_RW29_UNION */
#define PMIC_CODEC_ANA_RW29_ADDR(base)            ((base) + (0x286))

/* 寄存器说明：CODEC_IBIAS_ADJ2（DAC，ADC_OPA1电流控制信号。）
   位域定义UNION结构:  PMIC_CODEC_ANA_RW30_UNION */
#define PMIC_CODEC_ANA_RW30_ADDR(base)            ((base) + (0x287))

/* 寄存器说明：CODEC_IBIAS_ADJ3（ADC_OPA2，ADC_COMP电流控制信号。）
   位域定义UNION结构:  PMIC_CODEC_ANA_RW31_UNION */
#define PMIC_CODEC_ANA_RW31_ADDR(base)            ((base) + (0x288))

/* 寄存器说明：CODEC_IBIAS_ADJ4（LINEIN，MICBIAS电流控制信号。）
   位域定义UNION结构:  PMIC_CODEC_ANA_RW32_UNION */
#define PMIC_CODEC_ANA_RW32_ADDR(base)            ((base) + (0x289))

/* 寄存器说明：CODEC_IBIAS_ADJ5（reserved，AUXMIC电流控制信号）。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW33_UNION */
#define PMIC_CODEC_ANA_RW33_ADDR(base)            ((base) + (0x28A))

/* 寄存器说明：CODEC_IBIAS_ADJ6（MAINMIC，MIXER_EAR电流控制信号。）
   位域定义UNION结构:  PMIC_CODEC_ANA_RW34_UNION */
#define PMIC_CODEC_ANA_RW34_ADDR(base)            ((base) + (0x28B))

/* 寄存器说明：CODEC_IBIAS_ADJ7（EAR，CODEC全局电流控制信号）。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW35_UNION */
#define PMIC_CODEC_ANA_RW35_ADDR(base)            ((base) + (0x28C))

/* 寄存器说明：ADC_DAC模拟环回控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW36_UNION */
#define PMIC_CODEC_ANA_RW36_ADDR(base)            ((base) + (0x28D))

/* 寄存器说明：HP_BIAS_PD 、CP_PD、CP_DET_PD控制信号。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW37_UNION */
#define PMIC_CODEC_ANA_RW37_ADDR(base)            ((base) + (0x28E))

/* 寄存器说明：DACL_PD、DACR_PD。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW38_UNION */
#define PMIC_CODEC_ANA_RW38_ADDR(base)            ((base) + (0x28F))

/* 寄存器说明：MIXOUT_EAR_PD、EAR_PD。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW39_UNION */
#define PMIC_CODEC_ANA_RW39_ADDR(base)            ((base) + (0x290))

/* 寄存器说明：CODEC_ANA_RW40。
   位域定义UNION结构:  PMIC_CODEC_ANA_RW40_UNION */
#define PMIC_CODEC_ANA_RW40_ADDR(base)            ((base) + (0x291))

/* 寄存器说明：CODEC_ANA_RO01。
   位域定义UNION结构:  PMIC_CODEC_ANA_RO01_UNION */
#define PMIC_CODEC_ANA_RO01_ADDR(base)            ((base) + (0x292))

/* 寄存器说明：CODEC_ANA_RO02。
   位域定义UNION结构:  PMIC_CODEC_ANA_RO02_UNION */
#define PMIC_CODEC_ANA_RO02_ADDR(base)            ((base) + (0x293))

/* 寄存器说明：OSC_BAK调节信号
   位域定义UNION结构:  PMIC_CODEC_ANA_RW41_UNION */
#define PMIC_CODEC_ANA_RW41_ADDR(base)            ((base) + (0x294))

/* 寄存器说明：FM模式下时钟切换选择信号
   位域定义UNION结构:  PMIC_CODEC_ANA_RW42_UNION */
#define PMIC_CODEC_ANA_RW42_ADDR(base)            ((base) + (0x295))

/* 寄存器说明：CODEC_ANA_RW43
   位域定义UNION结构:  PMIC_CODEC_ANA_RW43_UNION */
#define PMIC_CODEC_ANA_RW43_ADDR(base)            ((base) + (0x296))

/* 寄存器说明：CODEC_ANA_RW44
   位域定义UNION结构:  PMIC_CODEC_ANA_RW44_UNION */
#define PMIC_CODEC_ANA_RW44_ADDR(base)            ((base) + (0x297))

/* 寄存器说明：CODEC_ANA_RW45
   位域定义UNION结构:  PMIC_CODEC_ANA_RW45_UNION */
#define PMIC_CODEC_ANA_RW45_ADDR(base)            ((base) + (0x298))





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
 结构说明  : VERSION1 寄存器结构定义。地址偏移量:0x001，初值:0x35，宽度:8
 寄存器说明: 版本寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num1 : 8;  /* bit[0-7]: ASIC码35表示项目编号5。 */
    } reg;
} PMIC_VERSION1_UNION;
#endif
#define PMIC_VERSION1_project_num1_START  (0)
#define PMIC_VERSION1_project_num1_END    (7)


/*****************************************************************************
 结构名    : PMIC_VERSION2_UNION
 结构说明  : VERSION2 寄存器结构定义。地址偏移量:0x002，初值:0x35，宽度:8
 寄存器说明: 版本寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num2 : 8;  /* bit[0-7]: ASIC码35表示项目编号5。 */
    } reg;
} PMIC_VERSION2_UNION;
#endif
#define PMIC_VERSION2_project_num2_START  (0)
#define PMIC_VERSION2_project_num2_END    (7)


/*****************************************************************************
 结构名    : PMIC_VERSION3_UNION
 结构说明  : VERSION3 寄存器结构定义。地址偏移量:0x003，初值:0x35，宽度:8
 寄存器说明: 版本寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  project_num3 : 8;  /* bit[0-7]: ASIC码35表示项目编号5。 */
    } reg;
} PMIC_VERSION3_UNION;
#endif
#define PMIC_VERSION3_project_num3_START  (0)
#define PMIC_VERSION3_project_num3_END    (7)


/*****************************************************************************
 结构名    : PMIC_VERSION4_UNION
 结构说明  : VERSION4 寄存器结构定义。地址偏移量:0x004，初值:0x01，宽度:8
 寄存器说明: 版本寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  version : 8;  /* bit[0-7]: 表示版本为V100的1。 */
    } reg;
} PMIC_VERSION4_UNION;
#endif
#define PMIC_VERSION4_version_START  (0)
#define PMIC_VERSION4_version_END    (7)


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
        unsigned char  chip_id : 8;  /* bit[0-7]: 表示版本为V100的00。 */
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
        unsigned char  st_vsys_ov_d200ur        : 1;  /* bit[0]: 过压状态指示位(上升沿去抖200us)。
                                                                 0：VSYS电压小于6V；
                                                                 1：VSYS电压大于6V。 */
        unsigned char  st_vbus_det_insert_d20m  : 1;  /* bit[1]: USB状态指示位(双沿去抖20ms)。
                                                                 0：USB处于拔出状态；
                                                                 1：USB处于插入状态。 */
        unsigned char  st_vsys_pwroff_abs       : 1;  /* bit[2]: 绝对关机电压状态位指示位（没有同步）。
                                                                 0：VSYS电压大于2.3V；
                                                                 1：VSYS电压小于2.3V。 */
        unsigned char  st_vsys_pwroff_deb_d80mr : 1;  /* bit[3]: 去抖关机电压状态指示位（上升沿去抖80ms，时间可配）。
                                                                 0：VSYS大于2.6V(可寄存器配置为3.0V)；
                                                                 1：VSYS小于2.6V(可寄存器配置为3.0V)。
                                                                 配置寄存器在非下电区。 */
        unsigned char  st_vsys_pwron_d60ur      : 1;  /* bit[4]: 开机电压状态指示位（上升沿去抖60us）。
                                                                 0：VSYS大于2.8V(可寄存器配置为3.2V)；
                                                                 1：VSYS小于2.8V(可寄存器配置为3.2V)。
                                                                 配置寄存器在非下电区。 */
        unsigned char  st_thsd_otmp140_d1mr     : 1;  /* bit[5]: 过温状态位(上升沿去抖1ms)。
                                                                 0：温度小于140℃；
                                                                 1： 温度大于140℃。 */
        unsigned char  st_thsd_otmp125_d1mr     : 1;  /* bit[6]: 过温状态指示位(上升沿去抖1ms)。
                                                                 0：温度小于设置值；
                                                                 1：温度大于设置值(非140关机门限)。
                                                                 温度设置值参见TH_CTRL[thsd_tmp_set]，默认125℃。 */
        unsigned char  st_pwron_d20m            : 1;  /* bit[7]: 按键状态指示位(双沿去抖20ms)。
                                                                 0：按键未被按下；
                                                                 1：按键被按下。 */
    } reg;
} PMIC_STATUS0_UNION;
#endif
#define PMIC_STATUS0_st_vsys_ov_d200ur_START         (0)
#define PMIC_STATUS0_st_vsys_ov_d200ur_END           (0)
#define PMIC_STATUS0_st_vbus_det_insert_d20m_START   (1)
#define PMIC_STATUS0_st_vbus_det_insert_d20m_END     (1)
#define PMIC_STATUS0_st_vsys_pwroff_abs_START        (2)
#define PMIC_STATUS0_st_vsys_pwroff_abs_END          (2)
#define PMIC_STATUS0_st_vsys_pwroff_deb_d80mr_START  (3)
#define PMIC_STATUS0_st_vsys_pwroff_deb_d80mr_END    (3)
#define PMIC_STATUS0_st_vsys_pwron_d60ur_START       (4)
#define PMIC_STATUS0_st_vsys_pwron_d60ur_END         (4)
#define PMIC_STATUS0_st_thsd_otmp140_d1mr_START      (5)
#define PMIC_STATUS0_st_thsd_otmp140_d1mr_END        (5)
#define PMIC_STATUS0_st_thsd_otmp125_d1mr_START      (6)
#define PMIC_STATUS0_st_thsd_otmp125_d1mr_END        (6)
#define PMIC_STATUS0_st_pwron_d20m_START             (7)
#define PMIC_STATUS0_st_pwron_d20m_END               (7)


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
        unsigned char  st_dcxo_clk_sel       : 1;  /* bit[0]: DCXO模式当前工作时钟源。
                                                              0：32K RC；
                                                              1：19.2MHz 586分频时钟。 */
        unsigned char  st_tcxo_clk_sel       : 1;  /* bit[1]: TCXO模式当前工作时钟源。
                                                              0：32K RC；
                                                              1：32K Crystal OSC。 */
        unsigned char  st_xo_32k_sel         : 1;  /* bit[2]: 模式选择
                                                              0：DCXO；
                                                              1：TCXO。 */
        unsigned char  st_xo_19m2_sel        : 1;  /* bit[3]: XO 19.2M来源。
                                                              0：38.4M晶体；
                                                              1：19.2M晶振。 */
        unsigned char  st_buck1_vol_sel      : 1;  /* bit[4]: BUCK1的开机电压选择信号。
                                                              0：1.2V；
                                                              1：1.1V。 */
        unsigned char  st_sim0_hpd_d540u     : 1;  /* bit[5]: SIM0_HPD状态指示位(双沿去抖540us，时间可配)。
                                                              0：SIM0_HPD输入低电平；
                                                              1：SIM0_HPD输入高电平。 */
        unsigned char  st_sim1_hpd_d540u     : 1;  /* bit[6]: SIM1_HPD状态指示位(双沿去抖540us，时间可配)。
                                                              0：SIM1_HPD输入低电平；
                                                              1：SIM1_HPD输入高电平。 */
        unsigned char  st_avdd_osc_vld_d20nf : 1;  /* bit[7]: AVDD_OSC电源检测状态寄存器（下降沿去抖20ns）。
                                                              0：AVDD_OSC电压不合格；
                                                              1：AVDD_OSC电压合格。 */
    } reg;
} PMIC_STATUS1_UNION;
#endif
#define PMIC_STATUS1_st_dcxo_clk_sel_START        (0)
#define PMIC_STATUS1_st_dcxo_clk_sel_END          (0)
#define PMIC_STATUS1_st_tcxo_clk_sel_START        (1)
#define PMIC_STATUS1_st_tcxo_clk_sel_END          (1)
#define PMIC_STATUS1_st_xo_32k_sel_START          (2)
#define PMIC_STATUS1_st_xo_32k_sel_END            (2)
#define PMIC_STATUS1_st_xo_19m2_sel_START         (3)
#define PMIC_STATUS1_st_xo_19m2_sel_END           (3)
#define PMIC_STATUS1_st_buck1_vol_sel_START       (4)
#define PMIC_STATUS1_st_buck1_vol_sel_END         (4)
#define PMIC_STATUS1_st_sim0_hpd_d540u_START      (5)
#define PMIC_STATUS1_st_sim0_hpd_d540u_END        (5)
#define PMIC_STATUS1_st_sim1_hpd_d540u_START      (6)
#define PMIC_STATUS1_st_sim1_hpd_d540u_END        (6)
#define PMIC_STATUS1_st_avdd_osc_vld_d20nf_START  (7)
#define PMIC_STATUS1_st_avdd_osc_vld_d20nf_END    (7)


/*****************************************************************************
 结构名    : PMIC_NP_D2A_RES0_UNION
 结构说明  : NP_D2A_RES0 寄存器结构定义。地址偏移量:0x00A，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_d2a_reserve0 : 8;  /* bit[0-7]: 数字到模拟的保留信号。 */
    } reg;
} PMIC_NP_D2A_RES0_UNION;
#endif
#define PMIC_NP_D2A_RES0_np_d2a_reserve0_START  (0)
#define PMIC_NP_D2A_RES0_np_d2a_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_NP_D2A_RES1_UNION
 结构说明  : NP_D2A_RES1 寄存器结构定义。地址偏移量:0x00B，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_d2a_reserve1 : 8;  /* bit[0-7]: 数字到模拟的保留信号。 */
    } reg;
} PMIC_NP_D2A_RES1_UNION;
#endif
#define PMIC_NP_D2A_RES1_np_d2a_reserve1_START  (0)
#define PMIC_NP_D2A_RES1_np_d2a_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_D2A_RES0_UNION
 结构说明  : D2A_RES0 寄存器结构定义。地址偏移量:0x00C，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  d2a_reserve0 : 8;  /* bit[0-7]: 数字到模拟的保留信号。 */
    } reg;
} PMIC_D2A_RES0_UNION;
#endif
#define PMIC_D2A_RES0_d2a_reserve0_START  (0)
#define PMIC_D2A_RES0_d2a_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_D2A_RES1_UNION
 结构说明  : D2A_RES1 寄存器结构定义。地址偏移量:0x00D，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  d2a_reserve1 : 8;  /* bit[0-7]: 数字到模拟的保留信号。 */
    } reg;
} PMIC_D2A_RES1_UNION;
#endif
#define PMIC_D2A_RES1_d2a_reserve1_START  (0)
#define PMIC_D2A_RES1_d2a_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_A2D_RES0_UNION
 结构说明  : A2D_RES0 寄存器结构定义。地址偏移量:0x00E，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  a2d_reserve0 : 8;  /* bit[0-7]: 模拟到数字的保留信号。 */
    } reg;
} PMIC_A2D_RES0_UNION;
#endif
#define PMIC_A2D_RES0_a2d_reserve0_START  (0)
#define PMIC_A2D_RES0_a2d_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_A2D_RES1_UNION
 结构说明  : A2D_RES1 寄存器结构定义。地址偏移量:0x00F，初值:0x00，宽度:8
 寄存器说明: 数模接口保留寄存器5。
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
 结构名    : PMIC_BUCK0_ONOFF_ECO_UNION
 结构说明  : BUCK0_ONOFF_ECO 寄存器结构定义。地址偏移量:0x010，初值:0x01，宽度:8
 寄存器说明: BUCK0开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck0_en     : 1;  /* bit[0]  : BUCK0使能信号。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  st_buck0_en      : 1;  /* bit[1]  : BUCK0开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_buck0_eco_en : 1;  /* bit[4]  : BUCK0 eco模式选择。
                                                           0：正常；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_BUCK0_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_en_START      (0)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_en_END        (0)
#define PMIC_BUCK0_ONOFF_ECO_st_buck0_en_START       (1)
#define PMIC_BUCK0_ONOFF_ECO_st_buck0_en_END         (1)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_eco_en_START  (4)
#define PMIC_BUCK0_ONOFF_ECO_reg_buck0_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_BUCK1_ONOFF_ECO_UNION
 结构说明  : BUCK1_ONOFF_ECO 寄存器结构定义。地址偏移量:0x011，初值:0x01，宽度:8
 寄存器说明: BUCK1开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck1_en     : 1;  /* bit[0]  : BUCK1使能信号。
                                                           0：关闭；
                                                           1：开启。
                                                           注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  st_buck1_en      : 1;  /* bit[1]  : BUCK1开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_buck1_eco_en : 1;  /* bit[4]  : BUCK1 eco模式选择。
                                                           0：正常；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_BUCK1_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_en_START      (0)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_en_END        (0)
#define PMIC_BUCK1_ONOFF_ECO_st_buck1_en_START       (1)
#define PMIC_BUCK1_ONOFF_ECO_st_buck1_en_END         (1)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_eco_en_START  (4)
#define PMIC_BUCK1_ONOFF_ECO_reg_buck1_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_BUCK2_ONOFF_ECO_UNION
 结构说明  : BUCK2_ONOFF_ECO 寄存器结构定义。地址偏移量:0x012，初值:0x01，宽度:8
 寄存器说明: BUCK2开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck2_en     : 1;  /* bit[0]  : BUCK2使能信号。
                                                           0：关闭；
                                                           1：开启。
                                                           注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  st_buck2_en      : 1;  /* bit[1]  : BUCK2开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_buck2_eco_en : 1;  /* bit[4]  : BUCK2 eco模式选择。
                                                           0：正常；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_BUCK2_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_en_START      (0)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_en_END        (0)
#define PMIC_BUCK2_ONOFF_ECO_st_buck2_en_START       (1)
#define PMIC_BUCK2_ONOFF_ECO_st_buck2_en_END         (1)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_eco_en_START  (4)
#define PMIC_BUCK2_ONOFF_ECO_reg_buck2_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_BUCK3_ONOFF_ECO_UNION
 结构说明  : BUCK3_ONOFF_ECO 寄存器结构定义。地址偏移量:0x013，初值:0x01，宽度:8
 寄存器说明: BUCK3开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_buck3_en     : 1;  /* bit[0]  : BUCK3使能信号。
                                                           0：关闭；
                                                           1：开启。
                                                           注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  st_buck3_en      : 1;  /* bit[1]  : BUCK3开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_buck3_eco_en : 1;  /* bit[4]  : BUCK3 eco模式选择。
                                                           0：正常；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_BUCK3_ONOFF_ECO_UNION;
#endif
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_en_START      (0)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_en_END        (0)
#define PMIC_BUCK3_ONOFF_ECO_st_buck3_en_START       (1)
#define PMIC_BUCK3_ONOFF_ECO_st_buck3_en_END         (1)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_eco_en_START  (4)
#define PMIC_BUCK3_ONOFF_ECO_reg_buck3_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO0_1_ONOFF_UNION
 结构说明  : LDO0_1_ONOFF 寄存器结构定义。地址偏移量:0x014，初值:0x00，宽度:8
 寄存器说明: LDO0_1开关使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo0_1_en : 1;  /* bit[0]  : LDO0_1使能信号。
                                                        0：关闭；
                                                        1：使能。 */
        unsigned char  st_ldo0_1_en  : 1;  /* bit[1]  : LDO0_1开关状态寄存器。
                                                        0：关闭；
                                                        1：开启。 */
        unsigned char  reserved      : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO0_1_ONOFF_UNION;
#endif
#define PMIC_LDO0_1_ONOFF_reg_ldo0_1_en_START  (0)
#define PMIC_LDO0_1_ONOFF_reg_ldo0_1_en_END    (0)
#define PMIC_LDO0_1_ONOFF_st_ldo0_1_en_START   (1)
#define PMIC_LDO0_1_ONOFF_st_ldo0_1_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO0_2_ONOFF_ECO_UNION
 结构说明  : LDO0_2_ONOFF_ECO 寄存器结构定义。地址偏移量:0x015，初值:0x01，宽度:8
 寄存器说明: LDO0_2开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo0_2_en     : 1;  /* bit[0]  : LDO0_2使能信号。
                                                            0：关闭；
                                                            1：使能。 */
        unsigned char  st_ldo0_2_en      : 1;  /* bit[1]  : LDO0_2开关状态寄存器。
                                                            0：关闭；
                                                            1：开启。 */
        unsigned char  reserved_0        : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo0_2_eco_en : 1;  /* bit[4]  : LDO0_2进入低功耗ECO模式控制信号。
                                                            0：normal模式；
                                                            1：ECO模式。 */
        unsigned char  reserved_1        : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO0_2_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_en_START      (0)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_en_END        (0)
#define PMIC_LDO0_2_ONOFF_ECO_st_ldo0_2_en_START       (1)
#define PMIC_LDO0_2_ONOFF_ECO_st_ldo0_2_en_END         (1)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_eco_en_START  (4)
#define PMIC_LDO0_2_ONOFF_ECO_reg_ldo0_2_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO1_ONOFF_ECO_UNION
 结构说明  : LDO1_ONOFF_ECO 寄存器结构定义。地址偏移量:0x016，初值:0x00，宽度:8
 寄存器说明: LDO1开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo1_en : 1;  /* bit[0]  : LDO1使能信号。
                                                      0：关闭；
                                                      1：使能。 */
        unsigned char  st_ldo1_en  : 1;  /* bit[1]  : LDO1开关状态寄存器。
                                                      0：关闭；
                                                      1：开启。 */
        unsigned char  reserved    : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO1_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_en_START  (0)
#define PMIC_LDO1_ONOFF_ECO_reg_ldo1_en_END    (0)
#define PMIC_LDO1_ONOFF_ECO_st_ldo1_en_START   (1)
#define PMIC_LDO1_ONOFF_ECO_st_ldo1_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO2_ONOFF_ECO_UNION
 结构说明  : LDO2_ONOFF_ECO 寄存器结构定义。地址偏移量:0x017，初值:0x01，宽度:8
 寄存器说明: LDO2开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo2_en     : 1;  /* bit[0]  : LDO2使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  st_ldo2_en      : 1;  /* bit[1]  : LDO2开关状态寄存器。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  reserved_0      : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo2_eco_en : 1;  /* bit[4]  : LDO2进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO2_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_en_START      (0)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_en_END        (0)
#define PMIC_LDO2_ONOFF_ECO_st_ldo2_en_START       (1)
#define PMIC_LDO2_ONOFF_ECO_st_ldo2_en_END         (1)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_eco_en_START  (4)
#define PMIC_LDO2_ONOFF_ECO_reg_ldo2_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO3_ONOFF_ECO_UNION
 结构说明  : LDO3_ONOFF_ECO 寄存器结构定义。地址偏移量:0x018，初值:0x00，宽度:8
 寄存器说明: LDO3开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo3_en : 1;  /* bit[0]  : LDO3使能信号。
                                                      0：关闭；
                                                      1：使能。 */
        unsigned char  st_ldo3_en  : 1;  /* bit[1]  : LDO3开关状态寄存器。
                                                      0：关闭；
                                                      1：开启。 */
        unsigned char  reserved    : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO3_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_en_START  (0)
#define PMIC_LDO3_ONOFF_ECO_reg_ldo3_en_END    (0)
#define PMIC_LDO3_ONOFF_ECO_st_ldo3_en_START   (1)
#define PMIC_LDO3_ONOFF_ECO_st_ldo3_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO4_ONOFF_ECO_UNION
 结构说明  : LDO4_ONOFF_ECO 寄存器结构定义。地址偏移量:0x019，初值:0x00，宽度:8
 寄存器说明: LDO4开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo4_en     : 1;  /* bit[0]  : LDO4使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  st_ldo4_en      : 1;  /* bit[1]  : LDO4开关状态寄存器。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  reserved_0      : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo4_eco_en : 1;  /* bit[4]  : LDO4进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO4_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_en_START      (0)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_en_END        (0)
#define PMIC_LDO4_ONOFF_ECO_st_ldo4_en_START       (1)
#define PMIC_LDO4_ONOFF_ECO_st_ldo4_en_END         (1)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_eco_en_START  (4)
#define PMIC_LDO4_ONOFF_ECO_reg_ldo4_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO5_ONOFF_ECO_UNION
 结构说明  : LDO5_ONOFF_ECO 寄存器结构定义。地址偏移量:0x01A，初值:0x01，宽度:8
 寄存器说明: LDO5开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo5_en : 1;  /* bit[0]  : LDO5使能信号。
                                                      0：关闭；
                                                      1：使能。 */
        unsigned char  st_ldo5_en  : 1;  /* bit[1]  : LDO5开关状态寄存器。
                                                      0：关闭；
                                                      1：开启。 */
        unsigned char  reserved    : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO5_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_en_START  (0)
#define PMIC_LDO5_ONOFF_ECO_reg_ldo5_en_END    (0)
#define PMIC_LDO5_ONOFF_ECO_st_ldo5_en_START   (1)
#define PMIC_LDO5_ONOFF_ECO_st_ldo5_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO7_ONOFF_ECO_UNION
 结构说明  : LDO7_ONOFF_ECO 寄存器结构定义。地址偏移量:0x01B，初值:0x01，宽度:8
 寄存器说明: LDO7开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo7_en : 1;  /* bit[0]  : LDO7使能信号。
                                                      0：关闭；
                                                      1：使能。 */
        unsigned char  st_ldo7_en  : 1;  /* bit[1]  : LDO7开关状态寄存器。
                                                      0：关闭；
                                                      1：开启。 */
        unsigned char  reserved    : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO7_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_en_START  (0)
#define PMIC_LDO7_ONOFF_ECO_reg_ldo7_en_END    (0)
#define PMIC_LDO7_ONOFF_ECO_st_ldo7_en_START   (1)
#define PMIC_LDO7_ONOFF_ECO_st_ldo7_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO8_ONOFF_ECO_UNION
 结构说明  : LDO8_ONOFF_ECO 寄存器结构定义。地址偏移量:0x01C，初值:0x01，宽度:8
 寄存器说明: LDO8开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo8_en     : 1;  /* bit[0]  : LDO8使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  st_ldo8_en      : 1;  /* bit[1]  : LDO8开关状态寄存器。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  reserved_0      : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo8_eco_en : 1;  /* bit[4]  : LDO8进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO8_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_en_START      (0)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_en_END        (0)
#define PMIC_LDO8_ONOFF_ECO_st_ldo8_en_START       (1)
#define PMIC_LDO8_ONOFF_ECO_st_ldo8_en_END         (1)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_eco_en_START  (4)
#define PMIC_LDO8_ONOFF_ECO_reg_ldo8_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO9_ONOFF_ECO_UNION
 结构说明  : LDO9_ONOFF_ECO 寄存器结构定义。地址偏移量:0x01D，初值:0x00，宽度:8
 寄存器说明: LDO9开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo9_en     : 1;  /* bit[0]  : LDO9使能信号。
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  st_ldo9_en      : 1;  /* bit[1]  : LDO9开关状态寄存器。
                                                          0：关闭；
                                                          1：开启。 */
        unsigned char  reserved_0      : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo9_eco_en : 1;  /* bit[4]  : LDO9进入低功耗ECO模式控制信号。
                                                          0：normal模式；
                                                          1：ECO模式。 */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO9_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_en_START      (0)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_en_END        (0)
#define PMIC_LDO9_ONOFF_ECO_st_ldo9_en_START       (1)
#define PMIC_LDO9_ONOFF_ECO_st_ldo9_en_END         (1)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_eco_en_START  (4)
#define PMIC_LDO9_ONOFF_ECO_reg_ldo9_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO10_ONOFF_ECO_UNION
 结构说明  : LDO10_ONOFF_ECO 寄存器结构定义。地址偏移量:0x01E，初值:0x01，宽度:8
 寄存器说明: LDO10开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo10_en     : 1;  /* bit[0]  : LDO10使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  st_ldo10_en      : 1;  /* bit[1]  : LDO10开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo10_eco_en : 1;  /* bit[4]  : LDO10进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO10_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_en_START      (0)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_en_END        (0)
#define PMIC_LDO10_ONOFF_ECO_st_ldo10_en_START       (1)
#define PMIC_LDO10_ONOFF_ECO_st_ldo10_en_END         (1)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_eco_en_START  (4)
#define PMIC_LDO10_ONOFF_ECO_reg_ldo10_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO11_ONOFF_ECO_UNION
 结构说明  : LDO11_ONOFF_ECO 寄存器结构定义。地址偏移量:0x01F，初值:0x00，宽度:8
 寄存器说明: LDO11开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo11_en     : 1;  /* bit[0]  : LDO11使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  st_ldo11_en      : 1;  /* bit[1]  : LDO11开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo11_eco_en : 1;  /* bit[4]  : LDO11进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO11_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_en_START      (0)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_en_END        (0)
#define PMIC_LDO11_ONOFF_ECO_st_ldo11_en_START       (1)
#define PMIC_LDO11_ONOFF_ECO_st_ldo11_en_END         (1)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_eco_en_START  (4)
#define PMIC_LDO11_ONOFF_ECO_reg_ldo11_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO12_ONOFF_ECO_UNION
 结构说明  : LDO12_ONOFF_ECO 寄存器结构定义。地址偏移量:0x020，初值:0x00，宽度:8
 寄存器说明: LDO12开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo12_en     : 1;  /* bit[0]  : LDO12使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  st_ldo12_en      : 1;  /* bit[1]  : LDO12开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo12_eco_en : 1;  /* bit[4]  : LDO12进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO12_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_en_START      (0)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_en_END        (0)
#define PMIC_LDO12_ONOFF_ECO_st_ldo12_en_START       (1)
#define PMIC_LDO12_ONOFF_ECO_st_ldo12_en_END         (1)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_eco_en_START  (4)
#define PMIC_LDO12_ONOFF_ECO_reg_ldo12_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO13_ONOFF_ECO_UNION
 结构说明  : LDO13_ONOFF_ECO 寄存器结构定义。地址偏移量:0x021，初值:0x00，宽度:8
 寄存器说明: LDO13开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo13_en : 1;  /* bit[0]  : LDO13使能信号(默认不开启，可通过OTP配置默认开启（默认值为1）)。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo13_en  : 1;  /* bit[1]  : LDO13开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO13_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_en_START  (0)
#define PMIC_LDO13_ONOFF_ECO_reg_ldo13_en_END    (0)
#define PMIC_LDO13_ONOFF_ECO_st_ldo13_en_START   (1)
#define PMIC_LDO13_ONOFF_ECO_st_ldo13_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO14_ONOFF_ECO_UNION
 结构说明  : LDO14_ONOFF_ECO 寄存器结构定义。地址偏移量:0x022，初值:0x00，宽度:8
 寄存器说明: LDO14开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo14_en : 1;  /* bit[0]  : LDO14使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo14_en  : 1;  /* bit[1]  : LDO14开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO14_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_en_START  (0)
#define PMIC_LDO14_ONOFF_ECO_reg_ldo14_en_END    (0)
#define PMIC_LDO14_ONOFF_ECO_st_ldo14_en_START   (1)
#define PMIC_LDO14_ONOFF_ECO_st_ldo14_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO15_ONOFF_ECO_UNION
 结构说明  : LDO15_ONOFF_ECO 寄存器结构定义。地址偏移量:0x023，初值:0x01，宽度:8
 寄存器说明: LDO15开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo15_en     : 1;  /* bit[0]  : LDO15使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  st_ldo15_en      : 1;  /* bit[1]  : LDO15开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo15_eco_en : 1;  /* bit[4]  : LDO15进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO15_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_en_START      (0)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_en_END        (0)
#define PMIC_LDO15_ONOFF_ECO_st_ldo15_en_START       (1)
#define PMIC_LDO15_ONOFF_ECO_st_ldo15_en_END         (1)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_eco_en_START  (4)
#define PMIC_LDO15_ONOFF_ECO_reg_ldo15_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO16_ONOFF_ECO_UNION
 结构说明  : LDO16_ONOFF_ECO 寄存器结构定义。地址偏移量:0x024，初值:0x00，宽度:8
 寄存器说明: LDO16开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo16_en     : 1;  /* bit[0]  : LDO16使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  st_ldo16_en      : 1;  /* bit[1]  : LDO16开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo16_eco_en : 1;  /* bit[4]  : LDO16进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO16_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_en_START      (0)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_en_END        (0)
#define PMIC_LDO16_ONOFF_ECO_st_ldo16_en_START       (1)
#define PMIC_LDO16_ONOFF_ECO_st_ldo16_en_END         (1)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_eco_en_START  (4)
#define PMIC_LDO16_ONOFF_ECO_reg_ldo16_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO17_ONOFF_ECO_UNION
 结构说明  : LDO17_ONOFF_ECO 寄存器结构定义。地址偏移量:0x025，初值:0x00，宽度:8
 寄存器说明: LDO17开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo17_en     : 1;  /* bit[0]  : LDO17使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  st_ldo17_en      : 1;  /* bit[1]  : LDO17开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo17_eco_en : 1;  /* bit[4]  : LDO17进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO17_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_en_START      (0)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_en_END        (0)
#define PMIC_LDO17_ONOFF_ECO_st_ldo17_en_START       (1)
#define PMIC_LDO17_ONOFF_ECO_st_ldo17_en_END         (1)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_eco_en_START  (4)
#define PMIC_LDO17_ONOFF_ECO_reg_ldo17_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO19_ONOFF_ECO_UNION
 结构说明  : LDO19_ONOFF_ECO 寄存器结构定义。地址偏移量:0x026，初值:0x00，宽度:8
 寄存器说明: LDO19开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo19_en : 1;  /* bit[0]  : LDO19使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo19_en  : 1;  /* bit[1]  : LDO19开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO19_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_en_START  (0)
#define PMIC_LDO19_ONOFF_ECO_reg_ldo19_en_END    (0)
#define PMIC_LDO19_ONOFF_ECO_st_ldo19_en_START   (1)
#define PMIC_LDO19_ONOFF_ECO_st_ldo19_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO20_ONOFF_ECO_UNION
 结构说明  : LDO20_ONOFF_ECO 寄存器结构定义。地址偏移量:0x027，初值:0x00，宽度:8
 寄存器说明: LDO20开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo20_en : 1;  /* bit[0]  : LDO20使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo20_en  : 1;  /* bit[1]  : LDO20开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO20_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_en_START  (0)
#define PMIC_LDO20_ONOFF_ECO_reg_ldo20_en_END    (0)
#define PMIC_LDO20_ONOFF_ECO_st_ldo20_en_START   (1)
#define PMIC_LDO20_ONOFF_ECO_st_ldo20_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO21_ONOFF_ECO_UNION
 结构说明  : LDO21_ONOFF_ECO 寄存器结构定义。地址偏移量:0x028，初值:0x00，宽度:8
 寄存器说明: LDO21开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo21_en : 1;  /* bit[0]  : LDO21使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo21_en  : 1;  /* bit[1]  : LDO21开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO21_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_en_START  (0)
#define PMIC_LDO21_ONOFF_ECO_reg_ldo21_en_END    (0)
#define PMIC_LDO21_ONOFF_ECO_st_ldo21_en_START   (1)
#define PMIC_LDO21_ONOFF_ECO_st_ldo21_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO22_ONOFF_ECO_UNION
 结构说明  : LDO22_ONOFF_ECO 寄存器结构定义。地址偏移量:0x029，初值:0x00，宽度:8
 寄存器说明: LDO22开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo22_en : 1;  /* bit[0]  : LDO22使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo22_en  : 1;  /* bit[1]  : LDO22开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO22_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_en_START  (0)
#define PMIC_LDO22_ONOFF_ECO_reg_ldo22_en_END    (0)
#define PMIC_LDO22_ONOFF_ECO_st_ldo22_en_START   (1)
#define PMIC_LDO22_ONOFF_ECO_st_ldo22_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO23_ONOFF_ECO_UNION
 结构说明  : LDO23_ONOFF_ECO 寄存器结构定义。地址偏移量:0x02A，初值:0x01，宽度:8
 寄存器说明: LDO23开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo23_en : 1;  /* bit[0]  : LDO23使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo23_en  : 1;  /* bit[1]  : LDO23开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO23_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_en_START  (0)
#define PMIC_LDO23_ONOFF_ECO_reg_ldo23_en_END    (0)
#define PMIC_LDO23_ONOFF_ECO_st_ldo23_en_START   (1)
#define PMIC_LDO23_ONOFF_ECO_st_ldo23_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO24_ONOFF_ECO_UNION
 结构说明  : LDO24_ONOFF_ECO 寄存器结构定义。地址偏移量:0x02B，初值:0x01，宽度:8
 寄存器说明: LDO24开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo24_en     : 1;  /* bit[0]  : LDO24使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  st_ldo24_en      : 1;  /* bit[1]  : LDO24开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo24_eco_en : 1;  /* bit[4]  : LDO24进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO24_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_en_START      (0)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_en_END        (0)
#define PMIC_LDO24_ONOFF_ECO_st_ldo24_en_START       (1)
#define PMIC_LDO24_ONOFF_ECO_st_ldo24_en_END         (1)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_eco_en_START  (4)
#define PMIC_LDO24_ONOFF_ECO_reg_ldo24_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO25_ONOFF_ECO_UNION
 结构说明  : LDO25_ONOFF_ECO 寄存器结构定义。地址偏移量:0x02C，初值:0x00，宽度:8
 寄存器说明: LDO25开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo25_en : 1;  /* bit[0]  : LDO25使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo25_en  : 1;  /* bit[1]  : LDO25开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO25_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_en_START  (0)
#define PMIC_LDO25_ONOFF_ECO_reg_ldo25_en_END    (0)
#define PMIC_LDO25_ONOFF_ECO_st_ldo25_en_START   (1)
#define PMIC_LDO25_ONOFF_ECO_st_ldo25_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO26_ONOFF_ECO_UNION
 结构说明  : LDO26_ONOFF_ECO 寄存器结构定义。地址偏移量:0x02D，初值:0x01，宽度:8
 寄存器说明: LDO26开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo26_en     : 1;  /* bit[0]  : LDO26使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  st_ldo26_en      : 1;  /* bit[1]  : LDO26开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo26_eco_en : 1;  /* bit[4]  : LDO26进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO26_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_en_START      (0)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_en_END        (0)
#define PMIC_LDO26_ONOFF_ECO_st_ldo26_en_START       (1)
#define PMIC_LDO26_ONOFF_ECO_st_ldo26_en_END         (1)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_eco_en_START  (4)
#define PMIC_LDO26_ONOFF_ECO_reg_ldo26_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO27_ONOFF_ECO_UNION
 结构说明  : LDO27_ONOFF_ECO 寄存器结构定义。地址偏移量:0x02E，初值:0x01，宽度:8
 寄存器说明: LDO27开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo27_en : 1;  /* bit[0]  : LDO27使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo27_en  : 1;  /* bit[1]  : LDO27开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO27_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_en_START  (0)
#define PMIC_LDO27_ONOFF_ECO_reg_ldo27_en_END    (0)
#define PMIC_LDO27_ONOFF_ECO_st_ldo27_en_START   (1)
#define PMIC_LDO27_ONOFF_ECO_st_ldo27_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO28_ONOFF_ECO_UNION
 结构说明  : LDO28_ONOFF_ECO 寄存器结构定义。地址偏移量:0x02F，初值:0x00，宽度:8
 寄存器说明: LDO28开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo28_en : 1;  /* bit[0]  : LDO28使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo28_en  : 1;  /* bit[1]  : LDO28开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO28_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_en_START  (0)
#define PMIC_LDO28_ONOFF_ECO_reg_ldo28_en_END    (0)
#define PMIC_LDO28_ONOFF_ECO_st_ldo28_en_START   (1)
#define PMIC_LDO28_ONOFF_ECO_st_ldo28_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO29_ONOFF_ECO_UNION
 结构说明  : LDO29_ONOFF_ECO 寄存器结构定义。地址偏移量:0x030，初值:0x01，宽度:8
 寄存器说明: LDO29开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo29_en     : 1;  /* bit[0]  : LDO29使能信号。
                                                           0：关闭；
                                                           1：使能。 */
        unsigned char  st_ldo29_en      : 1;  /* bit[1]  : LDO29开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo29_eco_en : 1;  /* bit[4]  : LDO29进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO29_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_en_START      (0)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_en_END        (0)
#define PMIC_LDO29_ONOFF_ECO_st_ldo29_en_START       (1)
#define PMIC_LDO29_ONOFF_ECO_st_ldo29_en_END         (1)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_eco_en_START  (4)
#define PMIC_LDO29_ONOFF_ECO_reg_ldo29_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO31_ONOFF_ECO_UNION
 结构说明  : LDO31_ONOFF_ECO 寄存器结构定义。地址偏移量:0x031，初值:0x00，宽度:8
 寄存器说明: LDO开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo31_en : 1;  /* bit[0]  : LDO31使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo31_en  : 1;  /* bit[1]  : LDO31开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO31_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_en_START  (0)
#define PMIC_LDO31_ONOFF_ECO_reg_ldo31_en_END    (0)
#define PMIC_LDO31_ONOFF_ECO_st_ldo31_en_START   (1)
#define PMIC_LDO31_ONOFF_ECO_st_ldo31_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO32_ONOFF_ECO_UNION
 结构说明  : LDO32_ONOFF_ECO 寄存器结构定义。地址偏移量:0x032，初值:0x00，宽度:8
 寄存器说明: LDO32开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo32_en : 1;  /* bit[0]  : LDO32使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo32_en  : 1;  /* bit[1]  : LDO32开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO32_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_en_START  (0)
#define PMIC_LDO32_ONOFF_ECO_reg_ldo32_en_END    (0)
#define PMIC_LDO32_ONOFF_ECO_st_ldo32_en_START   (1)
#define PMIC_LDO32_ONOFF_ECO_st_ldo32_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO33_ONOFF_ECO_UNION
 结构说明  : LDO33_ONOFF_ECO 寄存器结构定义。地址偏移量:0x033，初值:0x00，宽度:8
 寄存器说明: LDO开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo33_en : 1;  /* bit[0]  : LDO33使能信号。
                                                       0：关闭；
                                                       1：使能。 */
        unsigned char  st_ldo33_en  : 1;  /* bit[1]  : LDO33开关状态寄存器。
                                                       0：关闭；
                                                       1：开启。 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_LDO33_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO33_ONOFF_ECO_reg_ldo33_en_START  (0)
#define PMIC_LDO33_ONOFF_ECO_reg_ldo33_en_END    (0)
#define PMIC_LDO33_ONOFF_ECO_st_ldo33_en_START   (1)
#define PMIC_LDO33_ONOFF_ECO_st_ldo33_en_END     (1)


/*****************************************************************************
 结构名    : PMIC_LDO34_ONOFF_ECO_UNION
 结构说明  : LDO34_ONOFF_ECO 寄存器结构定义。地址偏移量:0x034，初值:0x01，宽度:8
 寄存器说明: LDO开关和ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_ldo34_en     : 1;  /* bit[0]  : LDO34使能信号。
                                                           0：关闭；
                                                           1：使能。
                                                           注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  st_ldo34_en      : 1;  /* bit[1]  : LDO34开关状态寄存器。
                                                           0：关闭；
                                                           1：开启。 */
        unsigned char  reserved_0       : 2;  /* bit[2-3]: 保留。 */
        unsigned char  reg_ldo34_eco_en : 1;  /* bit[4]  : LDO34进入低功耗ECO模式控制信号。
                                                           0：normal模式；
                                                           1：ECO模式。 */
        unsigned char  reserved_1       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO34_ONOFF_ECO_UNION;
#endif
#define PMIC_LDO34_ONOFF_ECO_reg_ldo34_en_START      (0)
#define PMIC_LDO34_ONOFF_ECO_reg_ldo34_en_END        (0)
#define PMIC_LDO34_ONOFF_ECO_st_ldo34_en_START       (1)
#define PMIC_LDO34_ONOFF_ECO_st_ldo34_en_END         (1)
#define PMIC_LDO34_ONOFF_ECO_reg_ldo34_eco_en_START  (4)
#define PMIC_LDO34_ONOFF_ECO_reg_ldo34_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_BUCK0_VSET_UNION
 结构说明  : BUCK0_VSET 寄存器结构定义。地址偏移量:0x03A，初值:0x05，宽度:8
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
 结构名    : PMIC_BUCK1_VSET_UNION
 结构说明  : BUCK1_VSET 寄存器结构定义。地址偏移量:0x03B，初值:0xCC，宽度:8
 寄存器说明: BUCK1调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_vset     : 4;  /* bit[0-3]: BUCK1输出电压调节，默认开机电压1.2V, buck1_vol_sel控制默认值：0：1.2V；1：1.12V。
                                                         0000：1.08V；
                                                         0001：1.09V；
                                                         0010：1.10V；
                                                         0011：1.11V；
                                                         0100：1.12V；
                                                         0101：1.13V；
                                                         0110：1.14V；
                                                         0111：1.15V；
                                                         1000：1.16V；
                                                         1001：1.17V；
                                                         1010：1.18V；
                                                         1011：1.19V；
                                                         1100：1.20V；
                                                         1101：1.21V；
                                                         1110：1.22V；
                                                         1111：1.23V。 */
        unsigned char  buck1_vset_adj : 4;  /* bit[4-7]: BUCK1输出电压值在PERI_EN有效时可配置成不同档位的值,buck1_vol_sel控制默认值：0：1.2V；1：1.12V。
                                                         0000：1.08V；
                                                         0001：1.09V；
                                                         0010：1.10V；
                                                         0011：1.11V；
                                                         0100：1.12V；
                                                         0101：1.13V；
                                                         0110：1.14V；
                                                         0111：1.15V；
                                                         1000：1.16V；
                                                         1001：1.17V；
                                                         1010：1.18V；
                                                         1011：1.19V；
                                                         1100：1.20V；
                                                         1101：1.21V；
                                                         1110：1.22V；
                                                         1111：1.23V。 */
    } reg;
} PMIC_BUCK1_VSET_UNION;
#endif
#define PMIC_BUCK1_VSET_buck1_vset_START      (0)
#define PMIC_BUCK1_VSET_buck1_vset_END        (3)
#define PMIC_BUCK1_VSET_buck1_vset_adj_START  (4)
#define PMIC_BUCK1_VSET_buck1_vset_adj_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_VSET_UNION
 结构说明  : BUCK2_VSET 寄存器结构定义。地址偏移量:0x03C，初值:0x44，宽度:8
 寄存器说明: BUCK2调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_vset     : 4;  /* bit[0-3]: BUCK2输出电压调节。
                                                         0000：1.250V；
                                                         0001：1.275V；
                                                         0010：1.300V；
                                                         0011：1.325V；
                                                         0100：1.350V；
                                                         0101：1.375V；
                                                         0110：1.400V；
                                                         0111：1.425V；
                                                         1000：1.450V；
                                                         1001：1.475V；
                                                         1010：1.500V；
                                                         1011：1.525V；
                                                         1100：1.550V；
                                                         1101：1.575V；
                                                         1110：1.600V；
                                                         1111：1.625V。 */
        unsigned char  buck2_vset_adj : 4;  /* bit[4-7]: BUCK2输出目标电压在PERI_EN有效时可配置的档位。
                                                         0000：1.250V；
                                                         0001：1.275V；
                                                         0010：1.300V；
                                                         0011：1.325V；
                                                         0100：1.350V；
                                                         0101：1.375V；
                                                         0110：1.400V；
                                                         0111：1.425V；
                                                         1000：1.450V；
                                                         1001：1.475V；
                                                         1010：1.500V；
                                                         1011：1.525V；
                                                         1100：1.550V；
                                                         1101：1.575V；
                                                         1110：1.600V；
                                                         1111：1.625V。 */
    } reg;
} PMIC_BUCK2_VSET_UNION;
#endif
#define PMIC_BUCK2_VSET_buck2_vset_START      (0)
#define PMIC_BUCK2_VSET_buck2_vset_END        (3)
#define PMIC_BUCK2_VSET_buck2_vset_adj_START  (4)
#define PMIC_BUCK2_VSET_buck2_vset_adj_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_VSET_UNION
 结构说明  : BUCK3_VSET 寄存器结构定义。地址偏移量:0x03D，初值:0x77，宽度:8
 寄存器说明: BUCK3调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_vset     : 4;  /* bit[0-3]: BUCK3输出电压调节。
                                                         0000：1.720V；
                                                         0001：1.760V；
                                                         0010：1.800V；
                                                         0011：1.840V；
                                                         0100：1.880V；
                                                         0101：1.920V；
                                                         0110：1.960V；
                                                         0111：2.000V；
                                                         1000：2.040V；
                                                         1001：2.080V；
                                                         1010：2.120V；
                                                         1011：2.160V；
                                                         1100：2.200V；
                                                         1101：2.240V；
                                                         1110：2.280V；
                                                         1111：2.320V。 */
        unsigned char  buck3_vset_adj : 4;  /* bit[4-7]: BUCK3输出目标电压在PERI_EN有效时可配置的档位。
                                                         0000：1.720V；
                                                         0001：1.760V；
                                                         0010：1.800V；
                                                         0011：1.840V；
                                                         0100：1.880V；
                                                         0101：1.920V；
                                                         0110：1.960V；
                                                         0111：2.000V；
                                                         1000：2.040V；
                                                         1001：2.080V；
                                                         1010：2.120V；
                                                         1011：2.160V；
                                                         1100：2.200V；
                                                         1101：2.240V；
                                                         1110：2.280V；
                                                         1111：2.320V。 */
    } reg;
} PMIC_BUCK3_VSET_UNION;
#endif
#define PMIC_BUCK3_VSET_buck3_vset_START      (0)
#define PMIC_BUCK3_VSET_buck3_vset_END        (3)
#define PMIC_BUCK3_VSET_buck3_vset_adj_START  (4)
#define PMIC_BUCK3_VSET_buck3_vset_adj_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO0_2_VSET_UNION
 结构说明  : LDO0_2_VSET 寄存器结构定义。地址偏移量:0x03E，初值:0x55，宽度:8
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
 结构名    : PMIC_LDO1_VSET_UNION
 结构说明  : LDO1_VSET 寄存器结构定义。地址偏移量:0x03F，初值:0x00，宽度:8
 寄存器说明: LDO1调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_vset : 4;  /* bit[0-3]: LDO1输出电压设置，默认电压1.0V。
                                                    0000：1.20V；
                                                    0001：1.21V；
                                                    0010：1.22V；
                                                    0011：1.23V；
                                                    0100：1.24V；
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
                                                    1111：1.35V。 */
        unsigned char  reserved  : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO1_VSET_UNION;
#endif
#define PMIC_LDO1_VSET_ldo1_vset_START  (0)
#define PMIC_LDO1_VSET_ldo1_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO2_VSET_UNION
 结构说明  : LDO2_VSET 寄存器结构定义。地址偏移量:0x040，初值:0x33，宽度:8
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
 结构名    : PMIC_LDO3_VSET_UNION
 结构说明  : LDO3_VSET 寄存器结构定义。地址偏移量:0x041，初值:0x00，宽度:8
 寄存器说明: LDO3调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_vset : 4;  /* bit[0-3]: LDO3输出电压设置。
                                                    0000：1.83V；
                                                    0001：1.84V；
                                                    0010：1.85V；
                                                    0011：1.86V；
                                                    0100：1.87V；
                                                    0101：1.88V；
                                                    0110：1.89V；
                                                    0111：1.90V。
                                                    1000：1.91V；
                                                    1001：1.92V；
                                                    1010：1.93V；
                                                    1011：1.94V；
                                                    1100：1.95V；
                                                    1101：1.96V；
                                                    1110：1.97V；
                                                    1111：1.98V。 */
        unsigned char  reserved  : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO3_VSET_UNION;
#endif
#define PMIC_LDO3_VSET_ldo3_vset_START  (0)
#define PMIC_LDO3_VSET_ldo3_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO4_VSET_UNION
 结构说明  : LDO4_VSET 寄存器结构定义。地址偏移量:0x042，初值:0x00，宽度:8
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
 结构名    : PMIC_LDO5_VSET_UNION
 结构说明  : LDO5_VSET 寄存器结构定义。地址偏移量:0x043，初值:0x03，宽度:8
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
 结构名    : PMIC_LDO7_VSET_UNION
 结构说明  : LDO7_VSET 寄存器结构定义。地址偏移量:0x044，初值:0x02，宽度:8
 寄存器说明: LDO7调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo7_vset : 3;  /* bit[0-2]: LDO7输出电压设置。
                                                    000：0.88V；
                                                    001：0.89V；
                                                    010：0.90V；
                                                    011：0.91V；
                                                    100：0.92V；
                                                    101：0.93V；
                                                    110：0.94V；
                                                    111：0.95V。 */
        unsigned char  reserved  : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO7_VSET_UNION;
#endif
#define PMIC_LDO7_VSET_ldo7_vset_START  (0)
#define PMIC_LDO7_VSET_ldo7_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO8_VSET_UNION
 结构说明  : LDO8_VSET 寄存器结构定义。地址偏移量:0x045，初值:0x03，宽度:8
 寄存器说明: LDO8调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo8_vset : 3;  /* bit[0-2]: LDO8输出电压设置，ldo8_vset[3]不使用。
                                                    000：1.700V；
                                                    001：1.750V；
                                                    010：1.775V；
                                                    011：1.800V；
                                                    100：1.825V；
                                                    101：1.850V；
                                                    110：1.900V；
                                                    111：1.950V。 */
        unsigned char  reserved  : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO8_VSET_UNION;
#endif
#define PMIC_LDO8_VSET_ldo8_vset_START  (0)
#define PMIC_LDO8_VSET_ldo8_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO9_VSET_UNION
 结构说明  : LDO9_VSET 寄存器结构定义。地址偏移量:0x046，初值:0x00，宽度:8
 寄存器说明: LDO9调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo9_vset : 3;  /* bit[0-2]: LDO9输出电压设置。
                                                    000：1.750V；
                                                    001：1.800V；
                                                    010：1.825V；
                                                    011：2.800V；
                                                    100：2.850V；
                                                    101：2.950V；
                                                    110：3.000V；
                                                    111：3.300V。 */
        unsigned char  reserved  : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO9_VSET_UNION;
#endif
#define PMIC_LDO9_VSET_ldo9_vset_START  (0)
#define PMIC_LDO9_VSET_ldo9_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO10_VSET_UNION
 结构说明  : LDO10_VSET 寄存器结构定义。地址偏移量:0x047，初值:0x06，宽度:8
 寄存器说明: LDO10调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo10_vset : 3;  /* bit[0-2]: LDO10输出电压设置。
                                                     000：2.6V；
                                                     001：2.7V；
                                                     010：2.8V；
                                                     011：2.9V；
                                                     100: 3.0V；
                                                     101: 3.1V；
                                                     110：3.2V；
                                                     111：3.3V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO10_VSET_UNION;
#endif
#define PMIC_LDO10_VSET_ldo10_vset_START  (0)
#define PMIC_LDO10_VSET_ldo10_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO11_VSET_UNION
 结构说明  : LDO11_VSET 寄存器结构定义。地址偏移量:0x048，初值:0x00，宽度:8
 寄存器说明: LDO11调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo11_vset : 3;  /* bit[0-2]: LDO11输出电压设置。
                                                     000：1.750V；
                                                     001：1.800V；
                                                     010：1.825V；
                                                     011：2.800V；
                                                     100：2.850V；
                                                     101：2.950V；
                                                     110：3.000V；
                                                     111：3.300V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO11_VSET_UNION;
#endif
#define PMIC_LDO11_VSET_ldo11_vset_START  (0)
#define PMIC_LDO11_VSET_ldo11_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO12_VSET_UNION
 结构说明  : LDO12_VSET 寄存器结构定义。地址偏移量:0x049，初值:0x00，宽度:8
 寄存器说明: LDO12调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo12_vset : 3;  /* bit[0-2]: LDO12输出电压设置。
                                                     000：1.750V；
                                                     001：1.800V；
                                                     010：1.825V；
                                                     011：2.800V；
                                                     100：2.850V；
                                                     101：2.950V；
                                                     110：3.000V；
                                                     111：3.300V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO12_VSET_UNION;
#endif
#define PMIC_LDO12_VSET_ldo12_vset_START  (0)
#define PMIC_LDO12_VSET_ldo12_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO13_VSET_UNION
 结构说明  : LDO13_VSET 寄存器结构定义。地址偏移量:0x04A，初值:0x06，宽度:8
 寄存器说明: LDO13调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo13_vset : 3;  /* bit[0-2]: LDO13输出电压设置。
                                                     000：1.80V；
                                                     001：2.50V；
                                                     010：2.60V；
                                                     011：2.70V；
                                                     100：2.75V；
                                                     101：2.80V；
                                                     110：2.85V；
                                                     111：2.90V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO13_VSET_UNION;
#endif
#define PMIC_LDO13_VSET_ldo13_vset_START  (0)
#define PMIC_LDO13_VSET_ldo13_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO14_VSET_UNION
 结构说明  : LDO14_VSET 寄存器结构定义。地址偏移量:0x04B，初值:0x00，宽度:8
 寄存器说明: LDO14调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo14_vset : 3;  /* bit[0-2]: LDO14输出电压设置。
                                                     000：1.750V；
                                                     001：1.800V；
                                                     010：1.825V；
                                                     011：2.800V；
                                                     100：2.850V；
                                                     101：2.950V；
                                                     110：3.000V；
                                                     111：3.300V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO14_VSET_UNION;
#endif
#define PMIC_LDO14_VSET_ldo14_vset_START  (0)
#define PMIC_LDO14_VSET_ldo14_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO15_VSET_UNION
 结构说明  : LDO15_VSET 寄存器结构定义。地址偏移量:0x04C，初值:0x06，宽度:8
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
                                                     001：1.80V；
                                                     010：2.40V；
                                                     011：2.60V；
                                                     100：2.70V；
                                                     101：2.85V；
                                                     110：2.95V；
                                                     111：3.00V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO15_VSET_UNION;
#endif
#define PMIC_LDO15_VSET_ldo15_vset_START  (0)
#define PMIC_LDO15_VSET_ldo15_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO16_VSET_UNION
 结构说明  : LDO16_VSET 寄存器结构定义。地址偏移量:0x04D，初值:0x00，宽度:8
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
                                                     001：1.80V；
                                                     010：2.40V；
                                                     011：2.60V；
                                                     100：2.70V；
                                                     101：2.85V；
                                                     110：2.95V；
                                                     111：3.00V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO16_VSET_UNION;
#endif
#define PMIC_LDO16_VSET_ldo16_vset_START  (0)
#define PMIC_LDO16_VSET_ldo16_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO17_VSET_UNION
 结构说明  : LDO17_VSET 寄存器结构定义。地址偏移量:0x04E，初值:0x00，宽度:8
 寄存器说明: LDO17调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo17_vset : 3;  /* bit[0-2]: LDO17输出电压设置。
                                                     000：2.60V；
                                                     001：2.70V；
                                                     010：2.80V；
                                                     011：2.85V；
                                                     100：3.00V；
                                                     101：3.10V；
                                                     110：3.20V；
                                                     111：3.30V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO17_VSET_UNION;
#endif
#define PMIC_LDO17_VSET_ldo17_vset_START  (0)
#define PMIC_LDO17_VSET_ldo17_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO19_VSET1_UNION
 结构说明  : LDO19_VSET1 寄存器结构定义。地址偏移量:0x04F，初值:0x00，宽度:8
 寄存器说明: LDO19调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo19_vset : 3;  /* bit[0-2]: LDO19输出电压设置。
                                                     000：1.80V；
                                                     001：2.50V；
                                                     010：2.60V；
                                                     011：2.70V；
                                                     100：2.75V；
                                                     101：2.80V；
                                                     110：2.85V；
                                                     111：2.90V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO19_VSET1_UNION;
#endif
#define PMIC_LDO19_VSET1_ldo19_vset_START  (0)
#define PMIC_LDO19_VSET1_ldo19_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO20_VSET_UNION
 结构说明  : LDO20_VSET 寄存器结构定义。地址偏移量:0x050，初值:0x02，宽度:8
 寄存器说明: LDO20调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo20_vset : 4;  /* bit[0-3]: LDO20输出电压设置。
                                                     0000：0.90V；
                                                     0001：0.95V；
                                                     0010：1.00V；
                                                     0011：1.05V；
                                                     0100：1.10V；
                                                     0101：1.20V；
                                                     0110：1.25V；
                                                     0111：1.26V；
                                                     1000：1.27V；
                                                     1001：1.28V；
                                                     1010：1.29V；
                                                     1011：1.30V；
                                                     1100：1.31V；
                                                     1101：1.32V；
                                                     其他：无效。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO20_VSET_UNION;
#endif
#define PMIC_LDO20_VSET_ldo20_vset_START  (0)
#define PMIC_LDO20_VSET_ldo20_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO21_VSET_UNION
 结构说明  : LDO21_VSET 寄存器结构定义。地址偏移量:0x051，初值:0x00，宽度:8
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
 结构名    : PMIC_LDO22_VSET_UNION
 结构说明  : LDO22_VSET 寄存器结构定义。地址偏移量:0x052，初值:0x00，宽度:8
 寄存器说明: LDO22调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_vset : 4;  /* bit[0-3]: LDO22输出电压设置。
                                                     0000：1.20V；
                                                     0001：1.21V；
                                                     0010：1.22V；
                                                     0011：1.23V；
                                                     0100：1.24V；
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
                                                     1111：1.35V。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO22_VSET_UNION;
#endif
#define PMIC_LDO22_VSET_ldo22_vset_START  (0)
#define PMIC_LDO22_VSET_ldo22_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO23_VSET_UNION
 结构说明  : LDO23_VSET 寄存器结构定义。地址偏移量:0x053，初值:0x04，宽度:8
 寄存器说明: LDO23调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo23_vset : 3;  /* bit[0-2]: LDO23输出电压设置。
                                                     000：1.90V；
                                                     001：1.95V；
                                                     010：2.00V；
                                                     011：2.05V；
                                                     100：2.10V；
                                                     101：2.15V；
                                                     110：2.20V；
                                                     111：2.25V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO23_VSET_UNION;
#endif
#define PMIC_LDO23_VSET_ldo23_vset_START  (0)
#define PMIC_LDO23_VSET_ldo23_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO24_VSET_UNION
 结构说明  : LDO24_VSET 寄存器结构定义。地址偏移量:0x054，初值:0x02，宽度:8
 寄存器说明: LDO24调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo24_vset : 3;  /* bit[0-2]: LDO24输出电压设置。
                                                     000：2.60V；
                                                     001：2.70V；
                                                     010：2.80V；
                                                     011：2.85V；
                                                     100：3.00V；
                                                     101：3.10V；
                                                     110：3.20V；
                                                     111：3.30V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO24_VSET_UNION;
#endif
#define PMIC_LDO24_VSET_ldo24_vset_START  (0)
#define PMIC_LDO24_VSET_ldo24_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO25_VSET_UNION
 结构说明  : LDO25_VSET 寄存器结构定义。地址偏移量:0x055，初值:0x00，宽度:8
 寄存器说明: LDO25调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo25_vset : 3;  /* bit[0-2]: LDO25输出电压设置。
                                                     000：1.50V；
                                                     001：1.80V；
                                                     010：2.40V；
                                                     011：2.50V；
                                                     100：2.60V；
                                                     101：2.70V；
                                                     110：2.85V；
                                                     111：3.00V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO25_VSET_UNION;
#endif
#define PMIC_LDO25_VSET_ldo25_vset_START  (0)
#define PMIC_LDO25_VSET_ldo25_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO26_VSET_UNION
 结构说明  : LDO26_VSET 寄存器结构定义。地址偏移量:0x056，初值:0x07，宽度:8
 寄存器说明: LDO26调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo26_vset : 3;  /* bit[0-2]: LDO26输出电压设置。
                                                     000：1.20V；
                                                     001：1.25V；
                                                     010：1.30V；
                                                     011：1.35V；
                                                     100：1.40V；
                                                     101：1.50V；
                                                     110：1.60V；
                                                     111：1.70V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO26_VSET_UNION;
#endif
#define PMIC_LDO26_VSET_ldo26_vset_START  (0)
#define PMIC_LDO26_VSET_ldo26_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO27_VSET_UNION
 结构说明  : LDO27_VSET 寄存器结构定义。地址偏移量:0x057，初值:0x05，宽度:8
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
 结构名    : PMIC_LDO28_VSET_UNION
 结构说明  : LDO28_VSET 寄存器结构定义。地址偏移量:0x058，初值:0x00，宽度:8
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
 结构名    : PMIC_LDO29_VSET_UNION
 结构说明  : LDO29_VSET 寄存器结构定义。地址偏移量:0x059，初值:0x33，宽度:8
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
                                                         100：1.225V；
                                                         101：1.250V；
                                                         110：1.275V；
                                                         111：1.300V。 */
        unsigned char  reserved_0     : 1;  /* bit[3]  : 保留。 */
        unsigned char  ldo29_vset_adj : 3;  /* bit[4-6]: LDO29输出目标电压在PERI_EN有效时可配置的档位。
                                                         000：1.000V；
                                                         001：1.050V；
                                                         010：1.100V；
                                                         011：1.200V；
                                                         100：1.225V；
                                                         101：1.250V；
                                                         110：1.275V；
                                                         111：1.300V。 */
        unsigned char  reserved_1     : 1;  /* bit[7]  : 保留。 */
    } reg;
} PMIC_LDO29_VSET_UNION;
#endif
#define PMIC_LDO29_VSET_ldo29_vset_START      (0)
#define PMIC_LDO29_VSET_ldo29_vset_END        (2)
#define PMIC_LDO29_VSET_ldo29_vset_adj_START  (4)
#define PMIC_LDO29_VSET_ldo29_vset_adj_END    (6)


/*****************************************************************************
 结构名    : PMIC_LDO31_VSET_UNION
 结构说明  : LDO31_VSET 寄存器结构定义。地址偏移量:0x05A，初值:0x00，宽度:8
 寄存器说明: LDO31调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo31_vset : 3;  /* bit[0-2]: LDO31输出电压设置。
                                                     000：2.5V；
                                                     001：2.6V；
                                                     010：2.7V；
                                                     011：2.8V；
                                                     100：2.9V；
                                                     101：3.0V；
                                                     110：3.1V；
                                                     111：3.2V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO31_VSET_UNION;
#endif
#define PMIC_LDO31_VSET_ldo31_vset_START  (0)
#define PMIC_LDO31_VSET_ldo31_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO32_VSET_UNION
 结构说明  : LDO32_VSET 寄存器结构定义。地址偏移量:0x05B，初值:0x02，宽度:8
 寄存器说明: LDO32调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo32_vset : 4;  /* bit[0-3]: LDO32输出电压设置。
                                                     0000：0.90V；
                                                     0001：0.95V；
                                                     0010：1.00V；
                                                     0011：1.05V；
                                                     0100：1.10V；
                                                     0101：1.20V；
                                                     0110：1.25V；
                                                     0111：1.26V；
                                                     1000：1.27V；
                                                     1001：1.28V；
                                                     1010：1.29V；
                                                     1011：1.30V；
                                                     1100：1.31V；
                                                     1101：1.32V；
                                                     其他：无效。 */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO32_VSET_UNION;
#endif
#define PMIC_LDO32_VSET_ldo32_vset_START  (0)
#define PMIC_LDO32_VSET_ldo32_vset_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO33_VSET_UNION
 结构说明  : LDO33_VSET 寄存器结构定义。地址偏移量:0x05C，初值:0x00，宽度:8
 寄存器说明: LDO33调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo33_vset : 3;  /* bit[0-2]: LDO33输出电压设置。
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
} PMIC_LDO33_VSET_UNION;
#endif
#define PMIC_LDO33_VSET_ldo33_vset_START  (0)
#define PMIC_LDO33_VSET_ldo33_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_LDO34_VSET_UNION
 结构说明  : LDO34_VSET 寄存器结构定义。地址偏移量:0x05D，初值:0x06，宽度:8
 寄存器说明: LDO34调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo34_vset : 3;  /* bit[0-2]: LDO34输出电压设置。
                                                     000：2.60V；
                                                     001：2.70V；
                                                     010：2.80V；
                                                     011：2.90V；
                                                     100：3.00V；
                                                     101：3.05V；
                                                     110：3.10V；
                                                     111：3.20V。 */
        unsigned char  reserved   : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO34_VSET_UNION;
#endif
#define PMIC_LDO34_VSET_ldo34_vset_START  (0)
#define PMIC_LDO34_VSET_ldo34_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL0_UNION
 结构说明  : BUCK0_CTRL0 寄存器结构定义。地址偏移量:0x064，初值:0xD4，宽度:8
 寄存器说明: BUCK0控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_dbias   : 4;  /* bit[0-3]: buck0 <1:0>比较器偏置电流调节（00~11增大）
                                                         buck0<3:2> 比较器主偏置电流调节（00~11增大） */
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
#define PMIC_BUCK0_CTRL0_buck0_dbias_START    (0)
#define PMIC_BUCK0_CTRL0_buck0_dbias_END      (3)
#define PMIC_BUCK0_CTRL0_buck0_adj_rlx_START  (4)
#define PMIC_BUCK0_CTRL0_buck0_adj_rlx_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL1_UNION
 结构说明  : BUCK0_CTRL1 寄存器结构定义。地址偏移量:0x065，初值:0x55，宽度:8
 寄存器说明: BUCK0控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ng_dt_sel   : 1;  /* bit[0]  : BUCK0 P管到N管死区模式选择。
                                                            0：不并入新死区控制模式；
                                                            1：并入新死区控制模式。 */
        unsigned char  buck0_pg_dt_sel   : 1;  /* bit[1]  : BUCK0 N管到P管死区模式选择。
                                                            0：不并入新死区控制模式；
                                                            1：并入新死区控制模式。 */
        unsigned char  buck0_nmos_switch : 1;  /* bit[2]  : buck0 eco到normal切换时NMOS开启切换方式。
                                                            0：和dmd同时切换；
                                                            1：在dmd之后切换。 */
        unsigned char  reserved          : 1;  /* bit[3]  : 保留 */
        unsigned char  buck0_dt_sel      : 2;  /* bit[4-5]: 死区时间调节。
                                                            0：不额外延迟5ns；
                                                            1：额外延迟5ns。 */
        unsigned char  buck0_ocp_sel     : 2;  /* bit[6-7]: BUCK0 OCP点调整。
                                                            00：4.15A；
                                                            01：4.70A；
                                                            10：5.27A；
                                                            11：5.82A。 */
    } reg;
} PMIC_BUCK0_CTRL1_UNION;
#endif
#define PMIC_BUCK0_CTRL1_buck0_ng_dt_sel_START    (0)
#define PMIC_BUCK0_CTRL1_buck0_ng_dt_sel_END      (0)
#define PMIC_BUCK0_CTRL1_buck0_pg_dt_sel_START    (1)
#define PMIC_BUCK0_CTRL1_buck0_pg_dt_sel_END      (1)
#define PMIC_BUCK0_CTRL1_buck0_nmos_switch_START  (2)
#define PMIC_BUCK0_CTRL1_buck0_nmos_switch_END    (2)
#define PMIC_BUCK0_CTRL1_buck0_dt_sel_START       (4)
#define PMIC_BUCK0_CTRL1_buck0_dt_sel_END         (5)
#define PMIC_BUCK0_CTRL1_buck0_ocp_sel_START      (6)
#define PMIC_BUCK0_CTRL1_buck0_ocp_sel_END        (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL2_UNION
 结构说明  : BUCK0_CTRL2 寄存器结构定义。地址偏移量:0x066，初值:0x99，宽度:8
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
 结构说明  : BUCK0_CTRL3 寄存器结构定义。地址偏移量:0x067，初值:0x61，宽度:8
 寄存器说明: BUCK0控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reg_r   : 2;  /* bit[0-1]: BUCK0内部regulator电阻，用于调节regulator带宽。
                                                        00：2.8kHz；
                                                        01：45kHz；
                                                        10：85kHz；
                                                        11：152kHz。 */
        unsigned char  reserved      : 2;  /* bit[2-3]: 保留。 */
        unsigned char  buck0_reg_en  : 1;  /* bit[4]  : BUCK0内部精度调整器使能信号。
                                                        0：使能；
                                                        1：不使能。 */
        unsigned char  buck0_adj_clx : 2;  /* bit[5-6]: buck0 LX反馈滤波电容调节
                                                        （11：电容全接入，00：电容全不接入） */
        unsigned char  buck0_ocp_dis : 1;  /* bit[7]  : BUCK0 内部OCP环路屏蔽信号。
                                                        0：不屏蔽；
                                                        1：屏蔽。 */
    } reg;
} PMIC_BUCK0_CTRL3_UNION;
#endif
#define PMIC_BUCK0_CTRL3_buck0_reg_r_START    (0)
#define PMIC_BUCK0_CTRL3_buck0_reg_r_END      (1)
#define PMIC_BUCK0_CTRL3_buck0_reg_en_START   (4)
#define PMIC_BUCK0_CTRL3_buck0_reg_en_END     (4)
#define PMIC_BUCK0_CTRL3_buck0_adj_clx_START  (5)
#define PMIC_BUCK0_CTRL3_buck0_adj_clx_END    (6)
#define PMIC_BUCK0_CTRL3_buck0_ocp_dis_START  (7)
#define PMIC_BUCK0_CTRL3_buck0_ocp_dis_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL4_UNION
 结构说明  : BUCK0_CTRL4 寄存器结构定义。地址偏移量:0x068，初值:0x60，宽度:8
 寄存器说明: BUCK0控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_short_pdp  : 1;  /* bit[0]  : 短路保护屏蔽寄存器。
                                                           0：使能短路保护，0.4V门限；
                                                           1：不使能短路保护，0V门限。 */
        unsigned char  buck0_reg_ss     : 1;  /* bit[1]  : BUCK0软启动时内部regulator状态。
                                                           0：正常状态；
                                                           1：单位增益反馈。 */
        unsigned char  buck0_regop_c    : 1;  /* bit[2]  : BUCK0内部regulator OP输出电容，用于调节OP的slew-rate。
                                                           0：slew-rate慢；
                                                           1：slew-rate快。 */
        unsigned char  buck0_filter_ton : 2;  /* bit[3-4]: 比较器滤毛刺（00~11增大） */
        unsigned char  buck0_reg_dr     : 3;  /* bit[5-7]: BUCK0内部regulator电阻，用于调节regulator调整精度范围。
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
#define PMIC_BUCK0_CTRL4_buck0_short_pdp_START   (0)
#define PMIC_BUCK0_CTRL4_buck0_short_pdp_END     (0)
#define PMIC_BUCK0_CTRL4_buck0_reg_ss_START      (1)
#define PMIC_BUCK0_CTRL4_buck0_reg_ss_END        (1)
#define PMIC_BUCK0_CTRL4_buck0_regop_c_START     (2)
#define PMIC_BUCK0_CTRL4_buck0_regop_c_END       (2)
#define PMIC_BUCK0_CTRL4_buck0_filter_ton_START  (3)
#define PMIC_BUCK0_CTRL4_buck0_filter_ton_END    (4)
#define PMIC_BUCK0_CTRL4_buck0_reg_dr_START      (5)
#define PMIC_BUCK0_CTRL4_buck0_reg_dr_END        (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL5_UNION
 结构说明  : BUCK0_CTRL5 寄存器结构定义。地址偏移量:0x069，初值:0x00，宽度:8
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
        unsigned char  buck0_eco_ng   : 1;  /* bit[2]  : BUCK0用于关闭NMOS power管。
                                                         0：强制关闭；
                                                         1：不强制关闭。 */
        unsigned char  buck0_reg_bias : 1;  /* bit[3]  : BUCK0内部regulator电容，用于调节regulator带宽。
                                                         0：0.5uA；
                                                         1：1uA。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK0_CTRL5_UNION;
#endif
#define PMIC_BUCK0_CTRL5_buck0_ton_START       (0)
#define PMIC_BUCK0_CTRL5_buck0_ton_END         (1)
#define PMIC_BUCK0_CTRL5_buck0_eco_ng_START    (2)
#define PMIC_BUCK0_CTRL5_buck0_eco_ng_END      (2)
#define PMIC_BUCK0_CTRL5_buck0_reg_bias_START  (3)
#define PMIC_BUCK0_CTRL5_buck0_reg_bias_END    (3)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL6_UNION
 结构说明  : BUCK0_CTRL6 寄存器结构定义。地址偏移量:0x06A，初值:0x69，宽度:8
 寄存器说明: BUCK0控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_dmd_ton  : 3;  /* bit[0-2]: buck0发生dmd时的加入导通时间量（000~111增大） */
        unsigned char  buck0_ocp_toff : 2;  /* bit[3-4]: buck0发生ocp时最小关断时间量 （00~11增大） */
        unsigned char  buck0_dmd_sel  : 3;  /* bit[5-7]: buck0 dmd点选择（000~111增大） */
    } reg;
} PMIC_BUCK0_CTRL6_UNION;
#endif
#define PMIC_BUCK0_CTRL6_buck0_dmd_ton_START   (0)
#define PMIC_BUCK0_CTRL6_buck0_dmd_ton_END     (2)
#define PMIC_BUCK0_CTRL6_buck0_ocp_toff_START  (3)
#define PMIC_BUCK0_CTRL6_buck0_ocp_toff_END    (4)
#define PMIC_BUCK0_CTRL6_buck0_dmd_sel_START   (5)
#define PMIC_BUCK0_CTRL6_buck0_dmd_sel_END     (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL7_UNION
 结构说明  : BUCK0_CTRL7 寄存器结构定义。地址偏移量:0x06B，初值:0x00，宽度:8
 寄存器说明: BUCK0控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_ton_dmd     : 1;  /* bit[0]  : buck0发生dmd时屏蔽控制最小导通时间 （0：不屏蔽） */
        unsigned char  buck0_eco_dmd     : 1;  /* bit[1]  : 在正常模式下强制NMOS管关闭（0：不强制，1：强制） */
        unsigned char  buck0_cmp_filter  : 1;  /* bit[2]  : 比较器滤毛刺功能（0：不虑毛刺；1：虑毛刺） */
        unsigned char  buck0_ocp_delay   : 1;  /* bit[3]  : ocp屏蔽时间延长20ns信号（0：不延长，1：延长） */
        unsigned char  buck0_dmd_clamp   : 1;  /* bit[4]  : 老dmd嵌位使能信号（0：加上；1：不加上） */
        unsigned char  buck0_regop_clamp : 1;  /* bit[5]  : regulator 嵌位电路使能（1：使能。0：不使能） */
        unsigned char  reserved          : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_BUCK0_CTRL7_UNION;
#endif
#define PMIC_BUCK0_CTRL7_buck0_ton_dmd_START      (0)
#define PMIC_BUCK0_CTRL7_buck0_ton_dmd_END        (0)
#define PMIC_BUCK0_CTRL7_buck0_eco_dmd_START      (1)
#define PMIC_BUCK0_CTRL7_buck0_eco_dmd_END        (1)
#define PMIC_BUCK0_CTRL7_buck0_cmp_filter_START   (2)
#define PMIC_BUCK0_CTRL7_buck0_cmp_filter_END     (2)
#define PMIC_BUCK0_CTRL7_buck0_ocp_delay_START    (3)
#define PMIC_BUCK0_CTRL7_buck0_ocp_delay_END      (3)
#define PMIC_BUCK0_CTRL7_buck0_dmd_clamp_START    (4)
#define PMIC_BUCK0_CTRL7_buck0_dmd_clamp_END      (4)
#define PMIC_BUCK0_CTRL7_buck0_regop_clamp_START  (5)
#define PMIC_BUCK0_CTRL7_buck0_regop_clamp_END    (5)


/*****************************************************************************
 结构名    : PMIC_BUCK0_CTRL8_UNION
 结构说明  : BUCK0_CTRL8 寄存器结构定义。地址偏移量:0x06C，初值:0x00，宽度:8
 寄存器说明: BUCK0控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck0_reserve : 8;  /* bit[0-7]: BUCK0备用寄存器。 */
    } reg;
} PMIC_BUCK0_CTRL8_UNION;
#endif
#define PMIC_BUCK0_CTRL8_buck0_reserve_START  (0)
#define PMIC_BUCK0_CTRL8_buck0_reserve_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL0_UNION
 结构说明  : BUCK1_CTRL0 寄存器结构定义。地址偏移量:0x06D，初值:0xD5，宽度:8
 寄存器说明: BUCK1控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_dbias   : 4;  /* bit[0-3]: buck1 <1:0>比较器偏置电流调节（00~11增大）
                                                         buck1<3:2> 比较器主偏置电流调节（00~11增大） */
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
#define PMIC_BUCK1_CTRL0_buck1_dbias_START    (0)
#define PMIC_BUCK1_CTRL0_buck1_dbias_END      (3)
#define PMIC_BUCK1_CTRL0_buck1_adj_rlx_START  (4)
#define PMIC_BUCK1_CTRL0_buck1_adj_rlx_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL1_UNION
 结构说明  : BUCK1_CTRL1 寄存器结构定义。地址偏移量:0x06E，初值:0x55，宽度:8
 寄存器说明: BUCK1控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ng_dt_sel   : 1;  /* bit[0]  : BUCK1 P管到N管死区模式选择。
                                                            0：不并入新死区控制模式；
                                                            1：并入新死区控制模式。 */
        unsigned char  buck1_pg_dt_sel   : 1;  /* bit[1]  : BUCK1 N管到P管死区模式选择。
                                                            0：不并入新死区控制模式；
                                                            1：并入新死区控制模式。 */
        unsigned char  buck1_nmos_switch : 1;  /* bit[2]  : buck1 eco到normal切换时NMOS开启切换方式：（0：和dmd同时切换，1：在dmd之后切换） */
        unsigned char  reserved          : 1;  /* bit[3]  : 保留。 */
        unsigned char  buck1_dt_sel      : 2;  /* bit[4-5]: 死区时间调节。
                                                            0：不额外延迟5ns；
                                                            1：额外延迟5ns。 */
        unsigned char  buck1_ocp_sel     : 2;  /* bit[6-7]: BUCK1 OCP点调整。
                                                            00：2.627A；
                                                            01：3.198A；
                                                            10：3.753A；
                                                            11：4.318A。 */
    } reg;
} PMIC_BUCK1_CTRL1_UNION;
#endif
#define PMIC_BUCK1_CTRL1_buck1_ng_dt_sel_START    (0)
#define PMIC_BUCK1_CTRL1_buck1_ng_dt_sel_END      (0)
#define PMIC_BUCK1_CTRL1_buck1_pg_dt_sel_START    (1)
#define PMIC_BUCK1_CTRL1_buck1_pg_dt_sel_END      (1)
#define PMIC_BUCK1_CTRL1_buck1_nmos_switch_START  (2)
#define PMIC_BUCK1_CTRL1_buck1_nmos_switch_END    (2)
#define PMIC_BUCK1_CTRL1_buck1_dt_sel_START       (4)
#define PMIC_BUCK1_CTRL1_buck1_dt_sel_END         (5)
#define PMIC_BUCK1_CTRL1_buck1_ocp_sel_START      (6)
#define PMIC_BUCK1_CTRL1_buck1_ocp_sel_END        (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL2_UNION
 结构说明  : BUCK1_CTRL2 寄存器结构定义。地址偏移量:0x06F，初值:0x99，宽度:8
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
 结构说明  : BUCK1_CTRL3 寄存器结构定义。地址偏移量:0x070，初值:0x61，宽度:8
 寄存器说明: BUCK1控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reg_r   : 2;  /* bit[0-1]: BUCK1内部regulator电阻，用于调节regulator带宽。
                                                        00：2.8kHz；
                                                        01：45kHz；
                                                        10：85kHz；
                                                        11：152kHz。 */
        unsigned char  reserved      : 2;  /* bit[2-3]: 保留。 */
        unsigned char  buck1_reg_en  : 1;  /* bit[4]  : BUCK1内部精度调整器使能信号。
                                                        0：使能；
                                                        1：不使能。 */
        unsigned char  buck1_adj_clx : 2;  /* bit[5-6]: buck1 LX反馈滤波电容调节
                                                        （11：电容全接入，00：电容全不接入） */
        unsigned char  buck1_ocp_dis : 1;  /* bit[7]  : BUCK1 内部OCP环路屏蔽信号。
                                                        0：不屏蔽；
                                                        1：屏蔽。 */
    } reg;
} PMIC_BUCK1_CTRL3_UNION;
#endif
#define PMIC_BUCK1_CTRL3_buck1_reg_r_START    (0)
#define PMIC_BUCK1_CTRL3_buck1_reg_r_END      (1)
#define PMIC_BUCK1_CTRL3_buck1_reg_en_START   (4)
#define PMIC_BUCK1_CTRL3_buck1_reg_en_END     (4)
#define PMIC_BUCK1_CTRL3_buck1_adj_clx_START  (5)
#define PMIC_BUCK1_CTRL3_buck1_adj_clx_END    (6)
#define PMIC_BUCK1_CTRL3_buck1_ocp_dis_START  (7)
#define PMIC_BUCK1_CTRL3_buck1_ocp_dis_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL4_UNION
 结构说明  : BUCK1_CTRL4 寄存器结构定义。地址偏移量:0x071，初值:0x60，宽度:8
 寄存器说明: BUCK1控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_short_pdp  : 1;  /* bit[0]  : 短路保护屏蔽寄存器。
                                                           0：使能短路保护，0.4V门限；
                                                           1：不使能短路保护，0V门限。 */
        unsigned char  buck1_reg_ss     : 1;  /* bit[1]  : BUCK1软启动时内部regulator状态。
                                                           0：正常状态；
                                                           1：单位增益反馈。 */
        unsigned char  buck1_regop_c    : 1;  /* bit[2]  : BUCK1内部regulator OP输出电容，用于调节OP的slew-rate。
                                                           0：slew-rate慢；
                                                           1：slew-rate快。 */
        unsigned char  buck1_filter_ton : 2;  /* bit[3-4]: 比较器滤毛刺（00~11增大） */
        unsigned char  buck1_reg_dr     : 3;  /* bit[5-7]: BUCK1内部regulator电阻，用于调节regulator调整精度范围。
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
#define PMIC_BUCK1_CTRL4_buck1_short_pdp_START   (0)
#define PMIC_BUCK1_CTRL4_buck1_short_pdp_END     (0)
#define PMIC_BUCK1_CTRL4_buck1_reg_ss_START      (1)
#define PMIC_BUCK1_CTRL4_buck1_reg_ss_END        (1)
#define PMIC_BUCK1_CTRL4_buck1_regop_c_START     (2)
#define PMIC_BUCK1_CTRL4_buck1_regop_c_END       (2)
#define PMIC_BUCK1_CTRL4_buck1_filter_ton_START  (3)
#define PMIC_BUCK1_CTRL4_buck1_filter_ton_END    (4)
#define PMIC_BUCK1_CTRL4_buck1_reg_dr_START      (5)
#define PMIC_BUCK1_CTRL4_buck1_reg_dr_END        (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL5_UNION
 结构说明  : BUCK1_CTRL5 寄存器结构定义。地址偏移量:0x072，初值:0x01，宽度:8
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
        unsigned char  buck1_eco_ng   : 1;  /* bit[2]  : BUCK1用于关闭NMOS power管。
                                                         0：强制关闭；
                                                         1：不强制关闭。 */
        unsigned char  buck1_reg_bias : 1;  /* bit[3]  : BUCK1内部regulator电容，用于调节regulator带宽。
                                                         0：0.5uA；
                                                         1：1uA。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK1_CTRL5_UNION;
#endif
#define PMIC_BUCK1_CTRL5_buck1_ton_START       (0)
#define PMIC_BUCK1_CTRL5_buck1_ton_END         (1)
#define PMIC_BUCK1_CTRL5_buck1_eco_ng_START    (2)
#define PMIC_BUCK1_CTRL5_buck1_eco_ng_END      (2)
#define PMIC_BUCK1_CTRL5_buck1_reg_bias_START  (3)
#define PMIC_BUCK1_CTRL5_buck1_reg_bias_END    (3)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL6_UNION
 结构说明  : BUCK1_CTRL6 寄存器结构定义。地址偏移量:0x073，初值:0x6B，宽度:8
 寄存器说明: BUCK1控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_dmd_ton  : 3;  /* bit[0-2]: buck1发生dmd时的加入导通时间量（000~111增大） */
        unsigned char  buck1_ocp_toff : 2;  /* bit[3-4]: buck1发生ocp时最小关断时间量 （00~11增大） */
        unsigned char  buck1_dmd_sel  : 3;  /* bit[5-7]: buck1 dmd点选择（000~111增大） */
    } reg;
} PMIC_BUCK1_CTRL6_UNION;
#endif
#define PMIC_BUCK1_CTRL6_buck1_dmd_ton_START   (0)
#define PMIC_BUCK1_CTRL6_buck1_dmd_ton_END     (2)
#define PMIC_BUCK1_CTRL6_buck1_ocp_toff_START  (3)
#define PMIC_BUCK1_CTRL6_buck1_ocp_toff_END    (4)
#define PMIC_BUCK1_CTRL6_buck1_dmd_sel_START   (5)
#define PMIC_BUCK1_CTRL6_buck1_dmd_sel_END     (7)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL7_UNION
 结构说明  : BUCK1_CTRL7 寄存器结构定义。地址偏移量:0x074，初值:0x00，宽度:8
 寄存器说明: BUCK1控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_ton_dmd     : 1;  /* bit[0]  : buck1发生dmd时屏蔽控制最小导通时间 （0：不屏蔽） */
        unsigned char  buck1_eco_dmd     : 1;  /* bit[1]  : 在正常模式下强制NMOS管关闭（0：不强制，1：强制） */
        unsigned char  buck1_cmp_filter  : 1;  /* bit[2]  : 比较器滤毛刺功能（0：不虑毛刺；1：虑毛刺） */
        unsigned char  buck1_ocp_delay   : 1;  /* bit[3]  : ocp屏蔽时间延长20ns信号（0：不延长，1：延长） */
        unsigned char  buck1_dmd_clamp   : 1;  /* bit[4]  : 老dmd嵌位使能信号（0：加上；1：不加上） */
        unsigned char  buck1_regop_clamp : 1;  /* bit[5]  : regulator 嵌位电路使能（1：使能。0：不使能） */
        unsigned char  reserved          : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_BUCK1_CTRL7_UNION;
#endif
#define PMIC_BUCK1_CTRL7_buck1_ton_dmd_START      (0)
#define PMIC_BUCK1_CTRL7_buck1_ton_dmd_END        (0)
#define PMIC_BUCK1_CTRL7_buck1_eco_dmd_START      (1)
#define PMIC_BUCK1_CTRL7_buck1_eco_dmd_END        (1)
#define PMIC_BUCK1_CTRL7_buck1_cmp_filter_START   (2)
#define PMIC_BUCK1_CTRL7_buck1_cmp_filter_END     (2)
#define PMIC_BUCK1_CTRL7_buck1_ocp_delay_START    (3)
#define PMIC_BUCK1_CTRL7_buck1_ocp_delay_END      (3)
#define PMIC_BUCK1_CTRL7_buck1_dmd_clamp_START    (4)
#define PMIC_BUCK1_CTRL7_buck1_dmd_clamp_END      (4)
#define PMIC_BUCK1_CTRL7_buck1_regop_clamp_START  (5)
#define PMIC_BUCK1_CTRL7_buck1_regop_clamp_END    (5)


/*****************************************************************************
 结构名    : PMIC_BUCK1_CTRL8_UNION
 结构说明  : BUCK1_CTRL8 寄存器结构定义。地址偏移量:0x075，初值:0x00，宽度:8
 寄存器说明: BUCK1控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck1_reserve : 8;  /* bit[0-7]: BUCK1备用寄存器。 */
    } reg;
} PMIC_BUCK1_CTRL8_UNION;
#endif
#define PMIC_BUCK1_CTRL8_buck1_reserve_START  (0)
#define PMIC_BUCK1_CTRL8_buck1_reserve_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL0_UNION
 结构说明  : BUCK2_CTRL0 寄存器结构定义。地址偏移量:0x076，初值:0xA5，宽度:8
 寄存器说明: BUCK2控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_dbias   : 4;  /* bit[0-3]: buck2 <1:0>比较器偏置电流调节（00~11增大）
                                                         buck2<3:2> 比较器主偏置电流调节（00~11增大） */
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
#define PMIC_BUCK2_CTRL0_buck2_dbias_START    (0)
#define PMIC_BUCK2_CTRL0_buck2_dbias_END      (3)
#define PMIC_BUCK2_CTRL0_buck2_adj_rlx_START  (4)
#define PMIC_BUCK2_CTRL0_buck2_adj_rlx_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL1_UNION
 结构说明  : BUCK2_CTRL1 寄存器结构定义。地址偏移量:0x077，初值:0x55，宽度:8
 寄存器说明: BUCK2控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ng_dt_sel   : 1;  /* bit[0]  : BUCK2 P管到N管死区模式选择。
                                                            0：不并入新死区控制模式；
                                                            1：并入新死区控制模式。 */
        unsigned char  buck2_pg_dt_sel   : 1;  /* bit[1]  : BUCK2 N管到P管死区模式选择。
                                                            0：不并入新死区控制模式；
                                                            1：并入新死区控制模式。 */
        unsigned char  buck2_nmos_switch : 1;  /* bit[2]  : buck2 eco到normal切换时NMOS开启切换方式：（0：和dmd同时切换，1：在dmd之后切换） */
        unsigned char  reserved          : 1;  /* bit[3]  : 保留。 */
        unsigned char  buck2_dt_sel      : 2;  /* bit[4-5]: 死区时间调节。
                                                            0：不额外延迟5ns；
                                                            1：额外延迟5ns。 */
        unsigned char  buck2_ocp_sel     : 2;  /* bit[6-7]: BUCK2 OCP点调整。
                                                            00：2.516A；
                                                            01：3.097A；
                                                            10：3.656A；
                                                            11：4.212A。 */
    } reg;
} PMIC_BUCK2_CTRL1_UNION;
#endif
#define PMIC_BUCK2_CTRL1_buck2_ng_dt_sel_START    (0)
#define PMIC_BUCK2_CTRL1_buck2_ng_dt_sel_END      (0)
#define PMIC_BUCK2_CTRL1_buck2_pg_dt_sel_START    (1)
#define PMIC_BUCK2_CTRL1_buck2_pg_dt_sel_END      (1)
#define PMIC_BUCK2_CTRL1_buck2_nmos_switch_START  (2)
#define PMIC_BUCK2_CTRL1_buck2_nmos_switch_END    (2)
#define PMIC_BUCK2_CTRL1_buck2_dt_sel_START       (4)
#define PMIC_BUCK2_CTRL1_buck2_dt_sel_END         (5)
#define PMIC_BUCK2_CTRL1_buck2_ocp_sel_START      (6)
#define PMIC_BUCK2_CTRL1_buck2_ocp_sel_END        (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL2_UNION
 结构说明  : BUCK2_CTRL2 寄存器结构定义。地址偏移量:0x078，初值:0x99，宽度:8
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
 结构说明  : BUCK2_CTRL3 寄存器结构定义。地址偏移量:0x079，初值:0x21，宽度:8
 寄存器说明: BUCK2控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reg_r   : 2;  /* bit[0-1]: BUCK2内部regulator电阻，用于调节regulator带宽。
                                                        00：2.8kHz；
                                                        01：45kHz；
                                                        10：85kHz；
                                                        11：152kHz。 */
        unsigned char  reserved      : 2;  /* bit[2-3]: 保留。 */
        unsigned char  buck2_reg_en  : 1;  /* bit[4]  : BUCK2内部精度调整器使能信号。
                                                        0：使能；
                                                        1：不使能。 */
        unsigned char  buck2_adj_clx : 2;  /* bit[5-6]: buck2 LX反馈滤波电容调节
                                                        （11：电容全接入，00：电容全不接入） */
        unsigned char  buck2_ocp_dis : 1;  /* bit[7]  : BUCK2 内部OCP环路屏蔽信号。
                                                        0：不屏蔽；
                                                        1：屏蔽。 */
    } reg;
} PMIC_BUCK2_CTRL3_UNION;
#endif
#define PMIC_BUCK2_CTRL3_buck2_reg_r_START    (0)
#define PMIC_BUCK2_CTRL3_buck2_reg_r_END      (1)
#define PMIC_BUCK2_CTRL3_buck2_reg_en_START   (4)
#define PMIC_BUCK2_CTRL3_buck2_reg_en_END     (4)
#define PMIC_BUCK2_CTRL3_buck2_adj_clx_START  (5)
#define PMIC_BUCK2_CTRL3_buck2_adj_clx_END    (6)
#define PMIC_BUCK2_CTRL3_buck2_ocp_dis_START  (7)
#define PMIC_BUCK2_CTRL3_buck2_ocp_dis_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL4_UNION
 结构说明  : BUCK2_CTRL4 寄存器结构定义。地址偏移量:0x07A，初值:0x60，宽度:8
 寄存器说明: BUCK2控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_short_pdp  : 1;  /* bit[0]  : 短路保护屏蔽寄存器。
                                                           0：使能短路保护，0.4V门限；
                                                           1：不使能短路保护，0V门限。 */
        unsigned char  buck2_reg_ss     : 1;  /* bit[1]  : BUCK2软启动时内部regulator状态。
                                                           0：正常状态；
                                                           1：单位增益反馈。 */
        unsigned char  buck2_regop_c    : 1;  /* bit[2]  : BUCK2内部regulator OP输出电容，用于调节OP的slew-rate。
                                                           0：slew-rate慢；
                                                           1：slew-rate快。 */
        unsigned char  buck2_filter_ton : 2;  /* bit[3-4]: 比较器滤毛刺（00~11增大） */
        unsigned char  buck2_reg_dr     : 3;  /* bit[5-7]: BUCK2内部regulator电阻，用于调节regulator调整精度范围。
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
#define PMIC_BUCK2_CTRL4_buck2_short_pdp_START   (0)
#define PMIC_BUCK2_CTRL4_buck2_short_pdp_END     (0)
#define PMIC_BUCK2_CTRL4_buck2_reg_ss_START      (1)
#define PMIC_BUCK2_CTRL4_buck2_reg_ss_END        (1)
#define PMIC_BUCK2_CTRL4_buck2_regop_c_START     (2)
#define PMIC_BUCK2_CTRL4_buck2_regop_c_END       (2)
#define PMIC_BUCK2_CTRL4_buck2_filter_ton_START  (3)
#define PMIC_BUCK2_CTRL4_buck2_filter_ton_END    (4)
#define PMIC_BUCK2_CTRL4_buck2_reg_dr_START      (5)
#define PMIC_BUCK2_CTRL4_buck2_reg_dr_END        (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL5_UNION
 结构说明  : BUCK2_CTRL5 寄存器结构定义。地址偏移量:0x07B，初值:0x00，宽度:8
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
        unsigned char  buck2_eco_ng   : 1;  /* bit[2]  : BUCK2用于关闭NMOS power管。
                                                         0：强制关闭；
                                                         1：不强制关闭。 */
        unsigned char  buck2_reg_bias : 1;  /* bit[3]  : BUCK2内部regulator电容，用于调节regulator带宽。
                                                         0：0.5uA；
                                                         1：1uA。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK2_CTRL5_UNION;
#endif
#define PMIC_BUCK2_CTRL5_buck2_ton_START       (0)
#define PMIC_BUCK2_CTRL5_buck2_ton_END         (1)
#define PMIC_BUCK2_CTRL5_buck2_eco_ng_START    (2)
#define PMIC_BUCK2_CTRL5_buck2_eco_ng_END      (2)
#define PMIC_BUCK2_CTRL5_buck2_reg_bias_START  (3)
#define PMIC_BUCK2_CTRL5_buck2_reg_bias_END    (3)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL6_UNION
 结构说明  : BUCK2_CTRL6 寄存器结构定义。地址偏移量:0x07C，初值:0x69，宽度:8
 寄存器说明: BUCK2控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_dmd_ton  : 3;  /* bit[0-2]: buck2发生dmd时的加入导通时间量（000~111增大） */
        unsigned char  buck2_ocp_toff : 2;  /* bit[3-4]: buck2发生ocp时最小关断时间量 （00~11增大） */
        unsigned char  buck2_dmd_sel  : 3;  /* bit[5-7]: buck2 dmd点选择（000~111增大） */
    } reg;
} PMIC_BUCK2_CTRL6_UNION;
#endif
#define PMIC_BUCK2_CTRL6_buck2_dmd_ton_START   (0)
#define PMIC_BUCK2_CTRL6_buck2_dmd_ton_END     (2)
#define PMIC_BUCK2_CTRL6_buck2_ocp_toff_START  (3)
#define PMIC_BUCK2_CTRL6_buck2_ocp_toff_END    (4)
#define PMIC_BUCK2_CTRL6_buck2_dmd_sel_START   (5)
#define PMIC_BUCK2_CTRL6_buck2_dmd_sel_END     (7)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL7_UNION
 结构说明  : BUCK2_CTRL7 寄存器结构定义。地址偏移量:0x07D，初值:0x00，宽度:8
 寄存器说明: BUCK2控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_ton_dmd     : 1;  /* bit[0]  : buck2发生dmd时屏蔽控制最小导通时间 （0：不屏蔽） */
        unsigned char  buck2_eco_dmd     : 1;  /* bit[1]  : 在正常模式下强制NMOS管关闭（0：不强制，1：强制） */
        unsigned char  buck2_cmp_filter  : 1;  /* bit[2]  : 比较器滤毛刺功能（0：不虑毛刺；1：虑毛刺） */
        unsigned char  buck2_ocp_delay   : 1;  /* bit[3]  : ocp屏蔽时间延长20ns信号（0：不延长，1：延长） */
        unsigned char  buck2_dmd_clamp   : 1;  /* bit[4]  : 老dmd嵌位使能信号（0：加上；1：不加上） */
        unsigned char  buck2_regop_clamp : 1;  /* bit[5]  : regulator 嵌位电路使能（1：使能。0：不使能） */
        unsigned char  reserved          : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_BUCK2_CTRL7_UNION;
#endif
#define PMIC_BUCK2_CTRL7_buck2_ton_dmd_START      (0)
#define PMIC_BUCK2_CTRL7_buck2_ton_dmd_END        (0)
#define PMIC_BUCK2_CTRL7_buck2_eco_dmd_START      (1)
#define PMIC_BUCK2_CTRL7_buck2_eco_dmd_END        (1)
#define PMIC_BUCK2_CTRL7_buck2_cmp_filter_START   (2)
#define PMIC_BUCK2_CTRL7_buck2_cmp_filter_END     (2)
#define PMIC_BUCK2_CTRL7_buck2_ocp_delay_START    (3)
#define PMIC_BUCK2_CTRL7_buck2_ocp_delay_END      (3)
#define PMIC_BUCK2_CTRL7_buck2_dmd_clamp_START    (4)
#define PMIC_BUCK2_CTRL7_buck2_dmd_clamp_END      (4)
#define PMIC_BUCK2_CTRL7_buck2_regop_clamp_START  (5)
#define PMIC_BUCK2_CTRL7_buck2_regop_clamp_END    (5)


/*****************************************************************************
 结构名    : PMIC_BUCK2_CTRL8_UNION
 结构说明  : BUCK2_CTRL8 寄存器结构定义。地址偏移量:0x07E，初值:0x00，宽度:8
 寄存器说明: BUCK2控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck2_reserve : 8;  /* bit[0-7]: BUCK2备用寄存器。 */
    } reg;
} PMIC_BUCK2_CTRL8_UNION;
#endif
#define PMIC_BUCK2_CTRL8_buck2_reserve_START  (0)
#define PMIC_BUCK2_CTRL8_buck2_reserve_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL0_UNION
 结构说明  : BUCK3_CTRL0 寄存器结构定义。地址偏移量:0x07F，初值:0xA5，宽度:8
 寄存器说明: BUCK3控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_dbias   : 4;  /* bit[0-3]: buck3 <1:0>比较器偏置电流调节（00~11增大）
                                                         buck3<3:2> 比较器主偏置电流调节（00~11增大） */
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
#define PMIC_BUCK3_CTRL0_buck3_dbias_START    (0)
#define PMIC_BUCK3_CTRL0_buck3_dbias_END      (3)
#define PMIC_BUCK3_CTRL0_buck3_adj_rlx_START  (4)
#define PMIC_BUCK3_CTRL0_buck3_adj_rlx_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL1_UNION
 结构说明  : BUCK3_CTRL1 寄存器结构定义。地址偏移量:0x080，初值:0x55，宽度:8
 寄存器说明: BUCK3控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ng_dt_sel   : 1;  /* bit[0]  : BUCK3 P管到N管死区模式选择。
                                                            0：不并入新死区控制模式；
                                                            1：并入新死区控制模式。 */
        unsigned char  buck3_pg_dt_sel   : 1;  /* bit[1]  : BUCK3 N管到P管死区模式选择。
                                                            0：不并入新死区控制模式；
                                                            1：并入新死区控制模式。 */
        unsigned char  buck3_nmos_switch : 1;  /* bit[2]  : buck3 eco到normal切换时NMOS开启切换方式：（0：和dmd同时切换，1：在dmd之后切换） */
        unsigned char  reserved          : 1;  /* bit[3]  : 保留。 */
        unsigned char  buck3_dt_sel      : 2;  /* bit[4-5]: 死区时间调节。
                                                            0：不额外延迟5ns；
                                                            1：额外延迟5ns。 */
        unsigned char  buck3_ocp_sel     : 2;  /* bit[6-7]: BUCK3 OCP点调整。
                                                            00：2.489A；
                                                            01：3.070A；
                                                            10：3.629A；
                                                            11：4.190A。 */
    } reg;
} PMIC_BUCK3_CTRL1_UNION;
#endif
#define PMIC_BUCK3_CTRL1_buck3_ng_dt_sel_START    (0)
#define PMIC_BUCK3_CTRL1_buck3_ng_dt_sel_END      (0)
#define PMIC_BUCK3_CTRL1_buck3_pg_dt_sel_START    (1)
#define PMIC_BUCK3_CTRL1_buck3_pg_dt_sel_END      (1)
#define PMIC_BUCK3_CTRL1_buck3_nmos_switch_START  (2)
#define PMIC_BUCK3_CTRL1_buck3_nmos_switch_END    (2)
#define PMIC_BUCK3_CTRL1_buck3_dt_sel_START       (4)
#define PMIC_BUCK3_CTRL1_buck3_dt_sel_END         (5)
#define PMIC_BUCK3_CTRL1_buck3_ocp_sel_START      (6)
#define PMIC_BUCK3_CTRL1_buck3_ocp_sel_END        (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL2_UNION
 结构说明  : BUCK3_CTRL2 寄存器结构定义。地址偏移量:0x081，初值:0x99，宽度:8
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
 结构说明  : BUCK3_CTRL3 寄存器结构定义。地址偏移量:0x082，初值:0x21，宽度:8
 寄存器说明: BUCK3控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reg_r   : 2;  /* bit[0-1]: BUCK3内部regulator电阻，用于调节regulator带宽。
                                                        00：2.8kHz；
                                                        01：45kHz；
                                                        10：85kHz；
                                                        11：152kHz。 */
        unsigned char  reserved      : 2;  /* bit[2-3]: 保留。 */
        unsigned char  buck3_reg_en  : 1;  /* bit[4]  : BUCK3内部精度调整器使能信号。
                                                        0：使能；
                                                        1：不使能。 */
        unsigned char  buck3_adj_clx : 2;  /* bit[5-6]: buck3 LX反馈滤波电容调节
                                                        （11：电容全接入，00：电容全不接入） */
        unsigned char  buck3_ocp_dis : 1;  /* bit[7]  : BUCK3 内部OCP环路屏蔽信号。
                                                        0：不屏蔽；
                                                        1：屏蔽。 */
    } reg;
} PMIC_BUCK3_CTRL3_UNION;
#endif
#define PMIC_BUCK3_CTRL3_buck3_reg_r_START    (0)
#define PMIC_BUCK3_CTRL3_buck3_reg_r_END      (1)
#define PMIC_BUCK3_CTRL3_buck3_reg_en_START   (4)
#define PMIC_BUCK3_CTRL3_buck3_reg_en_END     (4)
#define PMIC_BUCK3_CTRL3_buck3_adj_clx_START  (5)
#define PMIC_BUCK3_CTRL3_buck3_adj_clx_END    (6)
#define PMIC_BUCK3_CTRL3_buck3_ocp_dis_START  (7)
#define PMIC_BUCK3_CTRL3_buck3_ocp_dis_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL4_UNION
 结构说明  : BUCK3_CTRL4 寄存器结构定义。地址偏移量:0x083，初值:0x60，宽度:8
 寄存器说明: BUCK3控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_short_pdp  : 1;  /* bit[0]  : 短路保护屏蔽寄存器。
                                                           0：使能短路保护，0.4V门限；
                                                           1：不使能短路保护，0V门限。 */
        unsigned char  buck3_reg_ss     : 1;  /* bit[1]  : BUCK3软启动时内部regulator状态。
                                                           0：正常状态；
                                                           1：单位增益反馈。 */
        unsigned char  buck3_regop_c    : 1;  /* bit[2]  : BUCK3内部regulator OP输出电容，用于调节OP的slew-rate。
                                                           0：slew-rate慢；
                                                           1：slew-rate快。 */
        unsigned char  buck3_filter_ton : 2;  /* bit[3-4]: 比较器滤毛刺（00~11增大） */
        unsigned char  buck3_reg_dr     : 3;  /* bit[5-7]: BUCK3内部regulator电阻，用于调节regulator调整精度范围。
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
#define PMIC_BUCK3_CTRL4_buck3_short_pdp_START   (0)
#define PMIC_BUCK3_CTRL4_buck3_short_pdp_END     (0)
#define PMIC_BUCK3_CTRL4_buck3_reg_ss_START      (1)
#define PMIC_BUCK3_CTRL4_buck3_reg_ss_END        (1)
#define PMIC_BUCK3_CTRL4_buck3_regop_c_START     (2)
#define PMIC_BUCK3_CTRL4_buck3_regop_c_END       (2)
#define PMIC_BUCK3_CTRL4_buck3_filter_ton_START  (3)
#define PMIC_BUCK3_CTRL4_buck3_filter_ton_END    (4)
#define PMIC_BUCK3_CTRL4_buck3_reg_dr_START      (5)
#define PMIC_BUCK3_CTRL4_buck3_reg_dr_END        (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL5_UNION
 结构说明  : BUCK3_CTRL5 寄存器结构定义。地址偏移量:0x084，初值:0x01，宽度:8
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
        unsigned char  buck3_eco_ng   : 1;  /* bit[2]  : BUCK3用于关闭NMOS power管。
                                                         0：强制关闭；
                                                         1：不强制关闭。 */
        unsigned char  buck3_reg_bias : 1;  /* bit[3]  : BUCK3内部regulator电容，用于调节regulator带宽。
                                                         0：电容小；
                                                         1：电容大。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BUCK3_CTRL5_UNION;
#endif
#define PMIC_BUCK3_CTRL5_buck3_ton_START       (0)
#define PMIC_BUCK3_CTRL5_buck3_ton_END         (1)
#define PMIC_BUCK3_CTRL5_buck3_eco_ng_START    (2)
#define PMIC_BUCK3_CTRL5_buck3_eco_ng_END      (2)
#define PMIC_BUCK3_CTRL5_buck3_reg_bias_START  (3)
#define PMIC_BUCK3_CTRL5_buck3_reg_bias_END    (3)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL6_UNION
 结构说明  : BUCK3_CTRL6 寄存器结构定义。地址偏移量:0x085，初值:0x69，宽度:8
 寄存器说明: BUCK3控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_dmd_ton  : 3;  /* bit[0-2]: buck3发生dmd时的加入导通时间量（000~111增大） */
        unsigned char  buck3_ocp_toff : 2;  /* bit[3-4]: buck3发生ocp时最小关断时间量 （00~11增大） */
        unsigned char  buck3_dmd_sel  : 3;  /* bit[5-7]: buck3 dmd点选择（000~111增大） */
    } reg;
} PMIC_BUCK3_CTRL6_UNION;
#endif
#define PMIC_BUCK3_CTRL6_buck3_dmd_ton_START   (0)
#define PMIC_BUCK3_CTRL6_buck3_dmd_ton_END     (2)
#define PMIC_BUCK3_CTRL6_buck3_ocp_toff_START  (3)
#define PMIC_BUCK3_CTRL6_buck3_ocp_toff_END    (4)
#define PMIC_BUCK3_CTRL6_buck3_dmd_sel_START   (5)
#define PMIC_BUCK3_CTRL6_buck3_dmd_sel_END     (7)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL7_UNION
 结构说明  : BUCK3_CTRL7 寄存器结构定义。地址偏移量:0x086，初值:0x00，宽度:8
 寄存器说明: BUCK3控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_ton_dmd     : 1;  /* bit[0]  : buck3发生dmd时屏蔽控制最小导通时间 （0：不屏蔽） */
        unsigned char  buck3_eco_dmd     : 1;  /* bit[1]  : 在正常模式下强制NMOS管关闭（0：不强制，1：强制） */
        unsigned char  buck3_cmp_filter  : 1;  /* bit[2]  : 比较器滤毛刺功能（0：不虑毛刺；1：虑毛刺） */
        unsigned char  buck3_ocp_delay   : 1;  /* bit[3]  : ocp屏蔽时间延长20ns信号（0：不延长，1：延长） */
        unsigned char  buck3_dmd_clamp   : 1;  /* bit[4]  : 老dmd嵌位使能信号（0：加上；1：不加上） */
        unsigned char  buck3_regop_clamp : 1;  /* bit[5]  : regulator 嵌位电路使能（1：使能。0：不使能） */
        unsigned char  reserved          : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_BUCK3_CTRL7_UNION;
#endif
#define PMIC_BUCK3_CTRL7_buck3_ton_dmd_START      (0)
#define PMIC_BUCK3_CTRL7_buck3_ton_dmd_END        (0)
#define PMIC_BUCK3_CTRL7_buck3_eco_dmd_START      (1)
#define PMIC_BUCK3_CTRL7_buck3_eco_dmd_END        (1)
#define PMIC_BUCK3_CTRL7_buck3_cmp_filter_START   (2)
#define PMIC_BUCK3_CTRL7_buck3_cmp_filter_END     (2)
#define PMIC_BUCK3_CTRL7_buck3_ocp_delay_START    (3)
#define PMIC_BUCK3_CTRL7_buck3_ocp_delay_END      (3)
#define PMIC_BUCK3_CTRL7_buck3_dmd_clamp_START    (4)
#define PMIC_BUCK3_CTRL7_buck3_dmd_clamp_END      (4)
#define PMIC_BUCK3_CTRL7_buck3_regop_clamp_START  (5)
#define PMIC_BUCK3_CTRL7_buck3_regop_clamp_END    (5)


/*****************************************************************************
 结构名    : PMIC_BUCK3_CTRL8_UNION
 结构说明  : BUCK3_CTRL8 寄存器结构定义。地址偏移量:0x087，初值:0x00，宽度:8
 寄存器说明: BUCK3控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_reserve : 8;  /* bit[0-7]: BUCK3备用寄存器。 */
    } reg;
} PMIC_BUCK3_CTRL8_UNION;
#endif
#define PMIC_BUCK3_CTRL8_buck3_reserve_START  (0)
#define PMIC_BUCK3_CTRL8_buck3_reserve_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK_RESERVE0_UNION
 结构说明  : BUCK_RESERVE0 寄存器结构定义。地址偏移量:0x088，初值:0x00，宽度:8
 寄存器说明: BUCK预留寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve0 : 8;  /* bit[0-7]: BUCK备用寄存器 */
    } reg;
} PMIC_BUCK_RESERVE0_UNION;
#endif
#define PMIC_BUCK_RESERVE0_buck_reserve0_START  (0)
#define PMIC_BUCK_RESERVE0_buck_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK_RESERVE1_UNION
 结构说明  : BUCK_RESERVE1 寄存器结构定义。地址偏移量:0x089，初值:0x00，宽度:8
 寄存器说明: BUCK预留寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve1 : 8;  /* bit[0-7]: BUCK备用寄存器 */
    } reg;
} PMIC_BUCK_RESERVE1_UNION;
#endif
#define PMIC_BUCK_RESERVE1_buck_reserve1_START  (0)
#define PMIC_BUCK_RESERVE1_buck_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO_1_CTRL_UNION
 结构说明  : LDO_1_CTRL 寄存器结构定义。地址偏移量:0x08A，初值:0x11，宽度:8
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
 结构名    : PMIC_LDO1_CTRL_0_UNION
 结构说明  : LDO1_CTRL_0 寄存器结构定义。地址偏移量:0x08B，初值:0x60，宽度:8
 寄存器说明: LDO1控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_ref_buf_bypass : 1;  /* bit[0]  : LDO1的REF是否不屏蔽运放，直接通过PIN脚输出。
                                                              0：不屏蔽运放；
                                                              1：屏蔽运放。 */
        unsigned char  ldo1_psrr2_set      : 3;  /* bit[1-3]: LDO1 PSRR 提升电路2的档位调节（000表示无提升功能，后续档位影响依次增大） */
        unsigned char  ldo1_psrr1_set      : 3;  /* bit[4-6]: LDO1 PSRR 提升电路1的档位调节（000表示无提升功能，后续档位影响依次增大） */
        unsigned char  ldo1_psrr_en        : 1;  /* bit[7]  : LDO1 PSRR 提升电路使能信号。
                                                              0：代表关闭；
                                                              1：代表使能。 */
    } reg;
} PMIC_LDO1_CTRL_0_UNION;
#endif
#define PMIC_LDO1_CTRL_0_ldo1_ref_buf_bypass_START  (0)
#define PMIC_LDO1_CTRL_0_ldo1_ref_buf_bypass_END    (0)
#define PMIC_LDO1_CTRL_0_ldo1_psrr2_set_START       (1)
#define PMIC_LDO1_CTRL_0_ldo1_psrr2_set_END         (3)
#define PMIC_LDO1_CTRL_0_ldo1_psrr1_set_START       (4)
#define PMIC_LDO1_CTRL_0_ldo1_psrr1_set_END         (6)
#define PMIC_LDO1_CTRL_0_ldo1_psrr_en_START         (7)
#define PMIC_LDO1_CTRL_0_ldo1_psrr_en_END           (7)


/*****************************************************************************
 结构名    : PMIC_LDO1_CTRL_1_UNION
 结构说明  : LDO1_CTRL_1 寄存器结构定义。地址偏移量:0x08C，初值:0x58，宽度:8
 寄存器说明: LDO1控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo1_ocps_en      : 1;  /* bit[0]  : LDO1的S-clamp OCP环路开启的使能信号。0：关闭；
                                                            1：使能。  */
        unsigned char  ldo1_bw_en        : 1;  /* bit[1]  : LDO1 buffer电路电流的调节使能。
                                                            0：表示随负载变化；
                                                            1：表示不随负载变化。 */
        unsigned char  ldo1_vgpr_en      : 1;  /* bit[2]  : LDO1的 POWER管gate电压保护。
                                                            0：关闭；
                                                            1：开启。 */
        unsigned char  ldo1_ref_buf_rset : 2;  /* bit[3-4]: LDO1的REF运放后级输出滤波电阻选择(00:最小; 11最大) */
        unsigned char  ldo1_comp         : 3;  /* bit[5-7]: LDO1的补偿调节 */
    } reg;
} PMIC_LDO1_CTRL_1_UNION;
#endif
#define PMIC_LDO1_CTRL_1_ldo1_ocps_en_START       (0)
#define PMIC_LDO1_CTRL_1_ldo1_ocps_en_END         (0)
#define PMIC_LDO1_CTRL_1_ldo1_bw_en_START         (1)
#define PMIC_LDO1_CTRL_1_ldo1_bw_en_END           (1)
#define PMIC_LDO1_CTRL_1_ldo1_vgpr_en_START       (2)
#define PMIC_LDO1_CTRL_1_ldo1_vgpr_en_END         (2)
#define PMIC_LDO1_CTRL_1_ldo1_ref_buf_rset_START  (3)
#define PMIC_LDO1_CTRL_1_ldo1_ref_buf_rset_END    (4)
#define PMIC_LDO1_CTRL_1_ldo1_comp_START          (5)
#define PMIC_LDO1_CTRL_1_ldo1_comp_END            (7)


/*****************************************************************************
 结构名    : PMIC_LDO2_3_CTRL_UNION
 结构说明  : LDO2_3_CTRL 寄存器结构定义。地址偏移量:0x08D，初值:0x11，宽度:8
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
} PMIC_LDO2_3_CTRL_UNION;
#endif
#define PMIC_LDO2_3_CTRL_ldo3_vrset_START    (0)
#define PMIC_LDO2_3_CTRL_ldo3_vrset_END      (2)
#define PMIC_LDO2_3_CTRL_ldo3_ocp_enn_START  (3)
#define PMIC_LDO2_3_CTRL_ldo3_ocp_enn_END    (3)
#define PMIC_LDO2_3_CTRL_ldo2_vrset_START    (4)
#define PMIC_LDO2_3_CTRL_ldo2_vrset_END      (6)
#define PMIC_LDO2_3_CTRL_ldo2_ocp_enn_START  (7)
#define PMIC_LDO2_3_CTRL_ldo2_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO3_CTRL_UNION
 结构说明  : LDO3_CTRL 寄存器结构定义。地址偏移量:0x08E，初值:0x88，宽度:8
 寄存器说明: LDO3控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_i_sst     : 1;  /* bit[0]  : ldo3的缓启电流调整。
                                                         0：表示缓启电流为默认值；
                                                         1：表示增大缓启电流。 */
        unsigned char  ldo3_psrr2_set : 3;  /* bit[1-3]: ldo3 PSRR 提升电路1的档位调节（档位影响依次增大） */
        unsigned char  ldo3_psrr1_set : 3;  /* bit[4-6]: ldo3 PSRR 提升电路1的档位调节（档位影响依次增大） */
        unsigned char  ldo3_psrr_en   : 1;  /* bit[7]  : ldo3 PSRR 提升电路使能 */
    } reg;
} PMIC_LDO3_CTRL_UNION;
#endif
#define PMIC_LDO3_CTRL_ldo3_i_sst_START      (0)
#define PMIC_LDO3_CTRL_ldo3_i_sst_END        (0)
#define PMIC_LDO3_CTRL_ldo3_psrr2_set_START  (1)
#define PMIC_LDO3_CTRL_ldo3_psrr2_set_END    (3)
#define PMIC_LDO3_CTRL_ldo3_psrr1_set_START  (4)
#define PMIC_LDO3_CTRL_ldo3_psrr1_set_END    (6)
#define PMIC_LDO3_CTRL_ldo3_psrr_en_START    (7)
#define PMIC_LDO3_CTRL_ldo3_psrr_en_END      (7)


/*****************************************************************************
 结构名    : PMIC_LDO4_5_CTRL_UNION
 结构说明  : LDO4_5_CTRL 寄存器结构定义。地址偏移量:0x08F，初值:0x11，宽度:8
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
 结构说明  : LDO7_8_CTRL 寄存器结构定义。地址偏移量:0x090，初值:0x11，宽度:8
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
 结构说明  : LDO9_10_CTRL 寄存器结构定义。地址偏移量:0x091，初值:0x11，宽度:8
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
 结构说明  : LD11_12_CTRL 寄存器结构定义。地址偏移量:0x092，初值:0x11，宽度:8
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
 结构说明  : LDO13_14_CTRL 寄存器结构定义。地址偏移量:0x093，初值:0x11，宽度:8
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
 结构说明  : LDO15_16_CTRL 寄存器结构定义。地址偏移量:0x094，初值:0x11，宽度:8
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
 结构说明  : LDO17_19_CTRL 寄存器结构定义。地址偏移量:0x095，初值:0x11，宽度:8
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
 结构说明  : LDO20_21_CTRL 寄存器结构定义。地址偏移量:0x096，初值:0x11，宽度:8
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
 结构名    : PMIC_LDO22_CTRL0_UNION
 结构说明  : LDO22_CTRL0 寄存器结构定义。地址偏移量:0x097，初值:0x01，宽度:8
 寄存器说明: LDO22控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_vrset   : 3;  /* bit[0-2]: LDO22负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo22_ocp_enn : 1;  /* bit[3]  : LDO22限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  reserved      : 4;  /* bit[4-7]: 保留 */
    } reg;
} PMIC_LDO22_CTRL0_UNION;
#endif
#define PMIC_LDO22_CTRL0_ldo22_vrset_START    (0)
#define PMIC_LDO22_CTRL0_ldo22_vrset_END      (2)
#define PMIC_LDO22_CTRL0_ldo22_ocp_enn_START  (3)
#define PMIC_LDO22_CTRL0_ldo22_ocp_enn_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO22_CTRL1_UNION
 结构说明  : LDO22_CTRL1 寄存器结构定义。地址偏移量:0x098，初值:0x60，宽度:8
 寄存器说明: LDO22控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_ref_buf_bypass : 1;  /* bit[0]  : ldo22的REF是否不屏蔽运放，直接通过PIN脚输出。
                                                               0：不屏蔽运放；
                                                               1：屏蔽运放。 */
        unsigned char  ldo22_psrr2_set      : 3;  /* bit[1-3]: ldo22 PSRR 提升电路2的档位调节（000表示无提升功能，后续档位影响依次增大） */
        unsigned char  ldo22_psrr1_set      : 3;  /* bit[4-6]: ldo22 PSRR 提升电路1的档位调节（000表示无提升功能，后续档位影响依次增大） */
        unsigned char  ldo22_psrr_en        : 1;  /* bit[7]  : ldo22 PSRR 提升电路使能信号。
                                                               0：代表关闭；
                                                               1：代表使能。 */
    } reg;
} PMIC_LDO22_CTRL1_UNION;
#endif
#define PMIC_LDO22_CTRL1_ldo22_ref_buf_bypass_START  (0)
#define PMIC_LDO22_CTRL1_ldo22_ref_buf_bypass_END    (0)
#define PMIC_LDO22_CTRL1_ldo22_psrr2_set_START       (1)
#define PMIC_LDO22_CTRL1_ldo22_psrr2_set_END         (3)
#define PMIC_LDO22_CTRL1_ldo22_psrr1_set_START       (4)
#define PMIC_LDO22_CTRL1_ldo22_psrr1_set_END         (6)
#define PMIC_LDO22_CTRL1_ldo22_psrr_en_START         (7)
#define PMIC_LDO22_CTRL1_ldo22_psrr_en_END           (7)


/*****************************************************************************
 结构名    : PMIC_LDO22_CTRL2_UNION
 结构说明  : LDO22_CTRL2 寄存器结构定义。地址偏移量:0x099，初值:0x58，宽度:8
 寄存器说明: LDO22控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo22_ocps_en      : 1;  /* bit[0]  : ldo22的S-clamp OCP环路开启的使能信号。0：关闭；
                                                             1：使能。  */
        unsigned char  ldo22_bw_en        : 1;  /* bit[1]  : ldo22 buffer电路电流的调节使能。
                                                             0：表示随负载变化；
                                                             1：表示不随负载变化。 */
        unsigned char  ldo22_vgpr_en      : 1;  /* bit[2]  : ldo22的 POWER管gate电压保护。
                                                             0：关闭；
                                                             1：开启。 */
        unsigned char  ldo22_ref_buf_rset : 2;  /* bit[3-4]: ldo22的REF运放后级输出滤波电阻选择(00:最小; 11最大) */
        unsigned char  ldo22_comp         : 3;  /* bit[5-7]: ldo22的补偿调节 */
    } reg;
} PMIC_LDO22_CTRL2_UNION;
#endif
#define PMIC_LDO22_CTRL2_ldo22_ocps_en_START       (0)
#define PMIC_LDO22_CTRL2_ldo22_ocps_en_END         (0)
#define PMIC_LDO22_CTRL2_ldo22_bw_en_START         (1)
#define PMIC_LDO22_CTRL2_ldo22_bw_en_END           (1)
#define PMIC_LDO22_CTRL2_ldo22_vgpr_en_START       (2)
#define PMIC_LDO22_CTRL2_ldo22_vgpr_en_END         (2)
#define PMIC_LDO22_CTRL2_ldo22_ref_buf_rset_START  (3)
#define PMIC_LDO22_CTRL2_ldo22_ref_buf_rset_END    (4)
#define PMIC_LDO22_CTRL2_ldo22_comp_START          (5)
#define PMIC_LDO22_CTRL2_ldo22_comp_END            (7)


/*****************************************************************************
 结构名    : PMIC_LDO23_CTRL_UNION
 结构说明  : LDO23_CTRL 寄存器结构定义。地址偏移量:0x09A，初值:0x01，宽度:8
 寄存器说明: LDO23控制寄存器。
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
        unsigned char  reserved      : 4;  /* bit[4-7]: 保留 */
    } reg;
} PMIC_LDO23_CTRL_UNION;
#endif
#define PMIC_LDO23_CTRL_ldo23_vrset_START    (0)
#define PMIC_LDO23_CTRL_ldo23_vrset_END      (2)
#define PMIC_LDO23_CTRL_ldo23_ocp_enn_START  (3)
#define PMIC_LDO23_CTRL_ldo23_ocp_enn_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO24_25_CTRL_UNION
 结构说明  : LDO24_25_CTRL 寄存器结构定义。地址偏移量:0x09B，初值:0x11，宽度:8
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
 结构名    : PMIC_LDO26_CTRL_UNION
 结构说明  : LDO26_CTRL 寄存器结构定义。地址偏移量:0x09C，初值:0x01，宽度:8
 寄存器说明: LDO26控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo26_vrset   : 3;  /* bit[0-2]: LDO26负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo26_ocp_enn : 1;  /* bit[3]  : LDO26限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo26_i_sst   : 1;  /* bit[4]  : LDO26的缓启电流调整。
                                                        0：表示缓启电流为默认值；
                                                        1：表示增大缓启电流。 */
        unsigned char  reserved      : 3;  /* bit[5-7]: 保留 */
    } reg;
} PMIC_LDO26_CTRL_UNION;
#endif
#define PMIC_LDO26_CTRL_ldo26_vrset_START    (0)
#define PMIC_LDO26_CTRL_ldo26_vrset_END      (2)
#define PMIC_LDO26_CTRL_ldo26_ocp_enn_START  (3)
#define PMIC_LDO26_CTRL_ldo26_ocp_enn_END    (3)
#define PMIC_LDO26_CTRL_ldo26_i_sst_START    (4)
#define PMIC_LDO26_CTRL_ldo26_i_sst_END      (4)


/*****************************************************************************
 结构名    : PMIC_LDO27_CTRL_UNION
 结构说明  : LDO27_CTRL 寄存器结构定义。地址偏移量:0x09D，初值:0x01，宽度:8
 寄存器说明: LDO27控制寄存器。
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
        unsigned char  reserved      : 4;  /* bit[4-7]: 保留 */
    } reg;
} PMIC_LDO27_CTRL_UNION;
#endif
#define PMIC_LDO27_CTRL_ldo27_vrset_START    (0)
#define PMIC_LDO27_CTRL_ldo27_vrset_END      (2)
#define PMIC_LDO27_CTRL_ldo27_ocp_enn_START  (3)
#define PMIC_LDO27_CTRL_ldo27_ocp_enn_END    (3)


/*****************************************************************************
 结构名    : PMIC_LDO28_29_CTRL_UNION
 结构说明  : LDO28_29_CTRL 寄存器结构定义。地址偏移量:0x09E，初值:0x11，宽度:8
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
 结构名    : PMIC_LDO31_32_CTRL_UNION
 结构说明  : LDO31_32_CTRL 寄存器结构定义。地址偏移量:0x09F，初值:0x11，宽度:8
 寄存器说明: LDO31/LDO32控制寄存器。
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
        unsigned char  ldo31_vrset   : 3;  /* bit[4-6]: LDO31负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo31_ocp_enn : 1;  /* bit[7]  : LDO31限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO31_32_CTRL_UNION;
#endif
#define PMIC_LDO31_32_CTRL_ldo32_vrset_START    (0)
#define PMIC_LDO31_32_CTRL_ldo32_vrset_END      (2)
#define PMIC_LDO31_32_CTRL_ldo32_ocp_enn_START  (3)
#define PMIC_LDO31_32_CTRL_ldo32_ocp_enn_END    (3)
#define PMIC_LDO31_32_CTRL_ldo31_vrset_START    (4)
#define PMIC_LDO31_32_CTRL_ldo31_vrset_END      (6)
#define PMIC_LDO31_32_CTRL_ldo31_ocp_enn_START  (7)
#define PMIC_LDO31_32_CTRL_ldo31_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO33_LDO34_CTRL_UNION
 结构说明  : LDO33_LDO34_CTRL 寄存器结构定义。地址偏移量:0x0A0，初值:0x11，宽度:8
 寄存器说明: LDO33/LDO34控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo34_vrset   : 3;  /* bit[0-2]: LDO34负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo34_ocp_enn : 1;  /* bit[3]  : LDO34限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
        unsigned char  ldo33_vrset   : 3;  /* bit[4-6]: LDO33负载调整率补偿调整。
                                                        000：不补偿；
                                                        001：补偿5mV；
                                                        010：补偿10mV；
                                                        011：补偿15mV；
                                                        100：补偿20mV；
                                                        101：补偿25mV；
                                                        110：补偿30mV；
                                                        111：补偿35mV。 */
        unsigned char  ldo33_ocp_enn : 1;  /* bit[7]  : LDO33限流模式选择信号。
                                                        0：表示告警限流；
                                                        1：表示告警不限流。 */
    } reg;
} PMIC_LDO33_LDO34_CTRL_UNION;
#endif
#define PMIC_LDO33_LDO34_CTRL_ldo34_vrset_START    (0)
#define PMIC_LDO33_LDO34_CTRL_ldo34_vrset_END      (2)
#define PMIC_LDO33_LDO34_CTRL_ldo34_ocp_enn_START  (3)
#define PMIC_LDO33_LDO34_CTRL_ldo34_ocp_enn_END    (3)
#define PMIC_LDO33_LDO34_CTRL_ldo33_vrset_START    (4)
#define PMIC_LDO33_LDO34_CTRL_ldo33_vrset_END      (6)
#define PMIC_LDO33_LDO34_CTRL_ldo33_ocp_enn_START  (7)
#define PMIC_LDO33_LDO34_CTRL_ldo33_ocp_enn_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO_RESERVE0_UNION
 结构说明  : LDO_RESERVE0 寄存器结构定义。地址偏移量:0x0A1，初值:0x00，宽度:8
 寄存器说明: LDO预留寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo_reserve0 : 8;  /* bit[0-7]: ldo预留寄存器 */
    } reg;
} PMIC_LDO_RESERVE0_UNION;
#endif
#define PMIC_LDO_RESERVE0_ldo_reserve0_START  (0)
#define PMIC_LDO_RESERVE0_ldo_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO_RESERVE1_UNION
 结构说明  : LDO_RESERVE1 寄存器结构定义。地址偏移量:0x0A2，初值:0x00，宽度:8
 寄存器说明: LDO预留寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo_reserve1 : 8;  /* bit[0-7]: ldo预留寄存器 */
    } reg;
} PMIC_LDO_RESERVE1_UNION;
#endif
#define PMIC_LDO_RESERVE1_ldo_reserve1_START  (0)
#define PMIC_LDO_RESERVE1_ldo_reserve1_END    (7)


/*****************************************************************************
 结构名    : PMIC_BUCK0_3_OCP_CTRL_UNION
 结构说明  : BUCK0_3_OCP_CTRL 寄存器结构定义。地址偏移量:0x100，初值:0xFF，宽度:8
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
 结构名    : PMIC_LDO0_3_OCP_CTRL_UNION
 结构说明  : LDO0_3_OCP_CTRL 寄存器结构定义。地址偏移量:0x101，初值:0xDD，宽度:8
 寄存器说明: BUCK4/LDO0/1/2 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo3_ocp_auto_stop : 2;  /* bit[0-1]: LDO3在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo2_ocp_auto_stop : 2;  /* bit[2-3]: LDO2在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo1_ocp_auto_stop : 2;  /* bit[4-5]: LDO1在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo0_ocp_auto_stop : 2;  /* bit[6-7]: LDO0在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO0_3_OCP_CTRL_UNION;
#endif
#define PMIC_LDO0_3_OCP_CTRL_ldo3_ocp_auto_stop_START  (0)
#define PMIC_LDO0_3_OCP_CTRL_ldo3_ocp_auto_stop_END    (1)
#define PMIC_LDO0_3_OCP_CTRL_ldo2_ocp_auto_stop_START  (2)
#define PMIC_LDO0_3_OCP_CTRL_ldo2_ocp_auto_stop_END    (3)
#define PMIC_LDO0_3_OCP_CTRL_ldo1_ocp_auto_stop_START  (4)
#define PMIC_LDO0_3_OCP_CTRL_ldo1_ocp_auto_stop_END    (5)
#define PMIC_LDO0_3_OCP_CTRL_ldo0_ocp_auto_stop_START  (6)
#define PMIC_LDO0_3_OCP_CTRL_ldo0_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO4_8_OCP_CTRL_UNION
 结构说明  : LDO4_8_OCP_CTRL 寄存器结构定义。地址偏移量:0x102，初值:0x77，宽度:8
 寄存器说明: LCO3/4/5/7 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo8_ocp_auto_stop : 2;  /* bit[0-1]: LDO8在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo7_ocp_auto_stop : 2;  /* bit[2-3]: LDO7在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo5_ocp_auto_stop : 2;  /* bit[4-5]: LDO5在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo4_ocp_auto_stop : 2;  /* bit[6-7]: LDO4在发生OCP时是否自动关闭功能选择位。
                                                             X0： 仅上报中断，不自动关闭，PMU不下电；
                                                             01： 上报中断，自动关闭，PMU不下电；
                                                             11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO4_8_OCP_CTRL_UNION;
#endif
#define PMIC_LDO4_8_OCP_CTRL_ldo8_ocp_auto_stop_START  (0)
#define PMIC_LDO4_8_OCP_CTRL_ldo8_ocp_auto_stop_END    (1)
#define PMIC_LDO4_8_OCP_CTRL_ldo7_ocp_auto_stop_START  (2)
#define PMIC_LDO4_8_OCP_CTRL_ldo7_ocp_auto_stop_END    (3)
#define PMIC_LDO4_8_OCP_CTRL_ldo5_ocp_auto_stop_START  (4)
#define PMIC_LDO4_8_OCP_CTRL_ldo5_ocp_auto_stop_END    (5)
#define PMIC_LDO4_8_OCP_CTRL_ldo4_ocp_auto_stop_START  (6)
#define PMIC_LDO4_8_OCP_CTRL_ldo4_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO9_12_OCP_CTRL_UNION
 结构说明  : LDO9_12_OCP_CTRL 寄存器结构定义。地址偏移量:0x103，初值:0x75，宽度:8
 寄存器说明: LDO8/9/10/11 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo12_ocp_auto_stop : 2;  /* bit[0-1]: LDO12在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo11_ocp_auto_stop : 2;  /* bit[2-3]: LDO11在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo10_ocp_auto_stop : 2;  /* bit[4-5]: LDO10在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo9_ocp_auto_stop  : 2;  /* bit[6-7]: LDO9在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO9_12_OCP_CTRL_UNION;
#endif
#define PMIC_LDO9_12_OCP_CTRL_ldo12_ocp_auto_stop_START  (0)
#define PMIC_LDO9_12_OCP_CTRL_ldo12_ocp_auto_stop_END    (1)
#define PMIC_LDO9_12_OCP_CTRL_ldo11_ocp_auto_stop_START  (2)
#define PMIC_LDO9_12_OCP_CTRL_ldo11_ocp_auto_stop_END    (3)
#define PMIC_LDO9_12_OCP_CTRL_ldo10_ocp_auto_stop_START  (4)
#define PMIC_LDO9_12_OCP_CTRL_ldo10_ocp_auto_stop_END    (5)
#define PMIC_LDO9_12_OCP_CTRL_ldo9_ocp_auto_stop_START   (6)
#define PMIC_LDO9_12_OCP_CTRL_ldo9_ocp_auto_stop_END     (7)


/*****************************************************************************
 结构名    : PMIC_LDO13_16_OCP_CTRL_UNION
 结构说明  : LDO13_16_OCP_CTRL 寄存器结构定义。地址偏移量:0x104，初值:0x5D，宽度:8
 寄存器说明: LDO12/13/14/15 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo16_ocp_auto_stop : 2;  /* bit[0-1]: LDO16在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo15_ocp_auto_stop : 2;  /* bit[2-3]: LDO15在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo14_ocp_auto_stop : 2;  /* bit[4-5]: LDO14在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo13_ocp_auto_stop : 2;  /* bit[6-7]: LDO13在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO13_16_OCP_CTRL_UNION;
#endif
#define PMIC_LDO13_16_OCP_CTRL_ldo16_ocp_auto_stop_START  (0)
#define PMIC_LDO13_16_OCP_CTRL_ldo16_ocp_auto_stop_END    (1)
#define PMIC_LDO13_16_OCP_CTRL_ldo15_ocp_auto_stop_START  (2)
#define PMIC_LDO13_16_OCP_CTRL_ldo15_ocp_auto_stop_END    (3)
#define PMIC_LDO13_16_OCP_CTRL_ldo14_ocp_auto_stop_START  (4)
#define PMIC_LDO13_16_OCP_CTRL_ldo14_ocp_auto_stop_END    (5)
#define PMIC_LDO13_16_OCP_CTRL_ldo13_ocp_auto_stop_START  (6)
#define PMIC_LDO13_16_OCP_CTRL_ldo13_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO17_21_OCP_CTRL_UNION
 结构说明  : LDO17_21_OCP_CTRL 寄存器结构定义。地址偏移量:0x105，初值:0x55，宽度:8
 寄存器说明: LDO16/17/19/20 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo21_ocp_auto_stop : 2;  /* bit[0-1]: LDO21在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo20_ocp_auto_stop : 2;  /* bit[2-3]: LDO20在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo19_ocp_auto_stop : 2;  /* bit[4-5]: LDO19在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo17_ocp_auto_stop : 2;  /* bit[6-7]: LDO17在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO17_21_OCP_CTRL_UNION;
#endif
#define PMIC_LDO17_21_OCP_CTRL_ldo21_ocp_auto_stop_START  (0)
#define PMIC_LDO17_21_OCP_CTRL_ldo21_ocp_auto_stop_END    (1)
#define PMIC_LDO17_21_OCP_CTRL_ldo20_ocp_auto_stop_START  (2)
#define PMIC_LDO17_21_OCP_CTRL_ldo20_ocp_auto_stop_END    (3)
#define PMIC_LDO17_21_OCP_CTRL_ldo19_ocp_auto_stop_START  (4)
#define PMIC_LDO17_21_OCP_CTRL_ldo19_ocp_auto_stop_END    (5)
#define PMIC_LDO17_21_OCP_CTRL_ldo17_ocp_auto_stop_START  (6)
#define PMIC_LDO17_21_OCP_CTRL_ldo17_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO22_25_OCP_CTRL_UNION
 结构说明  : LDO22_25_OCP_CTRL 寄存器结构定义。地址偏移量:0x106，初值:0x7D，宽度:8
 寄存器说明: LDO21/22/23/24 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo25_ocp_auto_stop : 2;  /* bit[0-1]: LDO25在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo24_ocp_auto_stop : 2;  /* bit[2-3]: LDO24在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo23_ocp_auto_stop : 2;  /* bit[4-5]: LDO23在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo22_ocp_auto_stop : 2;  /* bit[6-7]: LDO22在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO22_25_OCP_CTRL_UNION;
#endif
#define PMIC_LDO22_25_OCP_CTRL_ldo25_ocp_auto_stop_START  (0)
#define PMIC_LDO22_25_OCP_CTRL_ldo25_ocp_auto_stop_END    (1)
#define PMIC_LDO22_25_OCP_CTRL_ldo24_ocp_auto_stop_START  (2)
#define PMIC_LDO22_25_OCP_CTRL_ldo24_ocp_auto_stop_END    (3)
#define PMIC_LDO22_25_OCP_CTRL_ldo23_ocp_auto_stop_START  (4)
#define PMIC_LDO22_25_OCP_CTRL_ldo23_ocp_auto_stop_END    (5)
#define PMIC_LDO22_25_OCP_CTRL_ldo22_ocp_auto_stop_START  (6)
#define PMIC_LDO22_25_OCP_CTRL_ldo22_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO26_29_OCP_CTRL_UNION
 结构说明  : LDO26_29_OCP_CTRL 寄存器结构定义。地址偏移量:0x107，初值:0xF7，宽度:8
 寄存器说明: LDO25/26/27/28 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo29_ocp_auto_stop : 2;  /* bit[0-1]: LDO29在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo28_ocp_auto_stop : 2;  /* bit[2-3]: LDO28在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo27_ocp_auto_stop : 2;  /* bit[4-5]: LDO27在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo26_ocp_auto_stop : 2;  /* bit[6-7]: LDO26在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO26_29_OCP_CTRL_UNION;
#endif
#define PMIC_LDO26_29_OCP_CTRL_ldo29_ocp_auto_stop_START  (0)
#define PMIC_LDO26_29_OCP_CTRL_ldo29_ocp_auto_stop_END    (1)
#define PMIC_LDO26_29_OCP_CTRL_ldo28_ocp_auto_stop_START  (2)
#define PMIC_LDO26_29_OCP_CTRL_ldo28_ocp_auto_stop_END    (3)
#define PMIC_LDO26_29_OCP_CTRL_ldo27_ocp_auto_stop_START  (4)
#define PMIC_LDO26_29_OCP_CTRL_ldo27_ocp_auto_stop_END    (5)
#define PMIC_LDO26_29_OCP_CTRL_ldo26_ocp_auto_stop_START  (6)
#define PMIC_LDO26_29_OCP_CTRL_ldo26_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO31_34_OCP_CTRL_UNION
 结构说明  : LDO31_34_OCP_CTRL 寄存器结构定义。地址偏移量:0x108，初值:0x57，宽度:8
 寄存器说明: LDO31/32/33/34 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo34_ocp_auto_stop : 2;  /* bit[0-1]: LDO34在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo33_ocp_auto_stop : 2;  /* bit[2-3]: LDO33在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo32_ocp_auto_stop : 2;  /* bit[4-5]: LDO32在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  ldo31_ocp_auto_stop : 2;  /* bit[6-7]: LDO31在发生OCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_LDO31_34_OCP_CTRL_UNION;
#endif
#define PMIC_LDO31_34_OCP_CTRL_ldo34_ocp_auto_stop_START  (0)
#define PMIC_LDO31_34_OCP_CTRL_ldo34_ocp_auto_stop_END    (1)
#define PMIC_LDO31_34_OCP_CTRL_ldo33_ocp_auto_stop_START  (2)
#define PMIC_LDO31_34_OCP_CTRL_ldo33_ocp_auto_stop_END    (3)
#define PMIC_LDO31_34_OCP_CTRL_ldo32_ocp_auto_stop_START  (4)
#define PMIC_LDO31_34_OCP_CTRL_ldo32_ocp_auto_stop_END    (5)
#define PMIC_LDO31_34_OCP_CTRL_ldo31_ocp_auto_stop_START  (6)
#define PMIC_LDO31_34_OCP_CTRL_ldo31_ocp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO_BUFF_CLASS_SCP_CTRL_UNION
 结构说明  : LDO_BUFF_CLASS_SCP_CTRL 寄存器结构定义。地址偏移量:0x109，初值:0x0D，宽度:8
 寄存器说明: LDO_BUFF SCP/CLASS OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  classd_ocp_auto_stop      : 2;  /* bit[0-1]: class在发生OCP时是否自动关闭功能选择位。
                                                                    X0： 仅上报中断，不自动关闭，PMU不下电；
                                                                    01： 上报中断，自动关闭，PMU不下电；
                                                                    11：上报中断，自动关闭，PMU下电。 */
        unsigned char  xo_ldo_buff_scp_auto_stop : 2;  /* bit[2-3]: xo_ldo_buff在发生SCP时是否自动关闭功能选择位。
                                                                    X0： 仅上报中断，不自动关闭，PMU不下电；
                                                                    01： 上报中断，自动关闭，PMU不下电；
                                                                    11：上报中断，自动关闭，PMU下电。 */
        unsigned char  reserved                  : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_LDO_BUFF_CLASS_SCP_CTRL_UNION;
#endif
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_classd_ocp_auto_stop_START       (0)
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_classd_ocp_auto_stop_END         (1)
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_xo_ldo_buff_scp_auto_stop_START  (2)
#define PMIC_LDO_BUFF_CLASS_SCP_CTRL_xo_ldo_buff_scp_auto_stop_END    (3)


/*****************************************************************************
 结构名    : PMIC_BUCK0_3_SCP_CTRL_UNION
 结构说明  : BUCK0_3_SCP_CTRL 寄存器结构定义。地址偏移量:0x10A，初值:0xFF，宽度:8
 寄存器说明: BUCK0/1/2/3 OCP自动关断控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_scp_auto_stop : 2;  /* bit[0-1]: BUCK3在发生SCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck2_scp_auto_stop : 2;  /* bit[2-3]: BUCK2在发生SCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck1_scp_auto_stop : 2;  /* bit[4-5]: BUCK1在发生SCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
        unsigned char  buck0_scp_auto_stop : 2;  /* bit[6-7]: BUCK0在发生SCP时是否自动关闭功能选择位。
                                                              X0： 仅上报中断，不自动关闭，PMU不下电；
                                                              01： 上报中断，自动关闭，PMU不下电；
                                                              11：上报中断，自动关闭，PMU下电。 */
    } reg;
} PMIC_BUCK0_3_SCP_CTRL_UNION;
#endif
#define PMIC_BUCK0_3_SCP_CTRL_buck3_scp_auto_stop_START  (0)
#define PMIC_BUCK0_3_SCP_CTRL_buck3_scp_auto_stop_END    (1)
#define PMIC_BUCK0_3_SCP_CTRL_buck2_scp_auto_stop_START  (2)
#define PMIC_BUCK0_3_SCP_CTRL_buck2_scp_auto_stop_END    (3)
#define PMIC_BUCK0_3_SCP_CTRL_buck1_scp_auto_stop_START  (4)
#define PMIC_BUCK0_3_SCP_CTRL_buck1_scp_auto_stop_END    (5)
#define PMIC_BUCK0_3_SCP_CTRL_buck0_scp_auto_stop_START  (6)
#define PMIC_BUCK0_3_SCP_CTRL_buck0_scp_auto_stop_END    (7)


/*****************************************************************************
 结构名    : PMIC_LDO_PMUA_ECO_UNION
 结构说明  : LDO_PMUA_ECO 寄存器结构定义。地址偏移量:0x10D，初值:0x00，宽度:8
 寄存器说明: LDO_PMUA ECO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  st_pmua_en      : 1;  /* bit[0]  : PMUA数模接口状态寄存器。
                                                          0：表示关闭PMUA；
                                                          1：表示打开PMUA。 */
        unsigned char  reserved_0      : 3;  /* bit[1-3]:  */
        unsigned char  reg_pmua_eco_en : 1;  /* bit[4]  : PMUA进入ECO模式控制信号。
                                                          0：0代表normal模式；
                                                          1：ECO模式。 */
        unsigned char  reserved_1      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_LDO_PMUA_ECO_UNION;
#endif
#define PMIC_LDO_PMUA_ECO_st_pmua_en_START       (0)
#define PMIC_LDO_PMUA_ECO_st_pmua_en_END         (0)
#define PMIC_LDO_PMUA_ECO_reg_pmua_eco_en_START  (4)
#define PMIC_LDO_PMUA_ECO_reg_pmua_eco_en_END    (4)


/*****************************************************************************
 结构名    : PMIC_LDO_PMUA_VSET_UNION
 结构说明  : LDO_PMUA_VSET 寄存器结构定义。地址偏移量:0x10E，初值:0x01，宽度:8
 寄存器说明: LDO_PMUA调压寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  pmua_vset : 3;  /* bit[0-2]: LDO_PMUA输出电压设置。
                                                    000：1.70；
                                                    001：1.80；
                                                    010：1.90；
                                                    011：2.00；
                                                    其他：无效。 */
        unsigned char  reserved  : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_LDO_PMUA_VSET_UNION;
#endif
#define PMIC_LDO_PMUA_VSET_pmua_vset_START  (0)
#define PMIC_LDO_PMUA_VSET_pmua_vset_END    (2)


/*****************************************************************************
 结构名    : PMIC_CLK_ABB_EN_UNION
 结构说明  : CLK_ABB_EN 寄存器结构定义。地址偏移量:0x10F，初值:0x01，宽度:8
 寄存器说明: ABB时钟开关寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_abb_en : 1;  /* bit[0]  : clk_abb使能信号（注：ABB buf）。
                                                        0：不使能；
                                                        1：使能。 */
        unsigned char  reserved      : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_CLK_ABB_EN_UNION;
#endif
#define PMIC_CLK_ABB_EN_reg_xo_abb_en_START  (0)
#define PMIC_CLK_ABB_EN_reg_xo_abb_en_END    (0)


/*****************************************************************************
 结构名    : PMIC_CLK_WIFI_EN_UNION
 结构说明  : CLK_WIFI_EN 寄存器结构定义。地址偏移量:0x110，初值:0x00，宽度:8
 寄存器说明: WIFI时钟开关寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_wifi_en : 1;  /* bit[0]  : clk_wifi使能信号（注：WIFI buf）。
                                                         0：不使能；
                                                         1：使能。 */
        unsigned char  reserved       : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_CLK_WIFI_EN_UNION;
#endif
#define PMIC_CLK_WIFI_EN_reg_xo_wifi_en_START  (0)
#define PMIC_CLK_WIFI_EN_reg_xo_wifi_en_END    (0)


/*****************************************************************************
 结构名    : PMIC_CLK_RF0_EN_UNION
 结构说明  : CLK_RF0_EN 寄存器结构定义。地址偏移量:0x111，初值:0x00，宽度:8
 寄存器说明: RF0时钟开关寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_rf0_en : 1;  /* bit[0]  : clk_rf0使能信号（注：RF0 buf）。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned char  reserved  : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_CLK_RF0_EN_UNION;
#endif
#define PMIC_CLK_RF0_EN_xo_rf0_en_START  (0)
#define PMIC_CLK_RF0_EN_xo_rf0_en_END    (0)


/*****************************************************************************
 结构名    : PMIC_CLK_RF1_EN_UNION
 结构说明  : CLK_RF1_EN 寄存器结构定义。地址偏移量:0x112，初值:0x00，宽度:8
 寄存器说明: RF1时钟开关寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_rf1_en : 1;  /* bit[0]  : clk_rf1使能信号（注：RF1 buf）。
                                                    0：不使能；
                                                    1：使能。 */
        unsigned char  reserved  : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_CLK_RF1_EN_UNION;
#endif
#define PMIC_CLK_RF1_EN_xo_rf1_en_START  (0)
#define PMIC_CLK_RF1_EN_xo_rf1_en_END    (0)


/*****************************************************************************
 结构名    : PMIC_CLK_SYS_EN_UNION
 结构说明  : CLK_SYS_EN 寄存器结构定义。地址偏移量:0x113，初值:0x01，宽度:8
 寄存器说明: SYS时钟开关寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_sys_en : 1;  /* bit[0]  : clk_sys使能信号（注:Vsys buf）。
                                                        0：不使能；
                                                        1：使能。 */
        unsigned char  reserved      : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_CLK_SYS_EN_UNION;
#endif
#define PMIC_CLK_SYS_EN_reg_xo_sys_en_START  (0)
#define PMIC_CLK_SYS_EN_reg_xo_sys_en_END    (0)


/*****************************************************************************
 结构名    : PMIC_CLK_CODEC_EN_UNION
 结构说明  : CLK_CODEC_EN 寄存器结构定义。地址偏移量:0x114，初值:0x00，宽度:8
 寄存器说明: CODEC时钟开关寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_xo_codec_en : 1;  /* bit[0]  : clk_codec使能信号
                                                          0：不使能；
                                                          1：使能。 */
        unsigned char  reserved        : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_CLK_CODEC_EN_UNION;
#endif
#define PMIC_CLK_CODEC_EN_reg_xo_codec_en_START  (0)
#define PMIC_CLK_CODEC_EN_reg_xo_codec_en_END    (0)


/*****************************************************************************
 结构名    : PMIC_CLK_ABB_CTRL_UNION
 结构说明  : CLK_ABB_CTRL 寄存器结构定义。地址偏移量:0x115，初值:0x03，宽度:8
 寄存器说明: ABB时钟配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_abb_drv : 2;  /* bit[0-1]: clk_abb驱动能力控制，00表示驱动为3pF//100K,11表示驱动30pF//100K */
        unsigned char  reserved   : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_CLK_ABB_CTRL_UNION;
#endif
#define PMIC_CLK_ABB_CTRL_xo_abb_drv_START  (0)
#define PMIC_CLK_ABB_CTRL_xo_abb_drv_END    (1)


/*****************************************************************************
 结构名    : PMIC_CLK_WIFI_CTRL_UNION
 结构说明  : CLK_WIFI_CTRL 寄存器结构定义。地址偏移量:0x116，初值:0x05，宽度:8
 寄存器说明: WIFI时钟配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_wifi_drv        : 2;  /* bit[0-1]: clk_wifi驱动能力控制，00表示驱动为3pF//100K,11表示驱动30pF//100K */
        unsigned char  np_xo_dig_wifi_sel : 1;  /* bit[2]  : 0：对应方波；
                                                             1：对应正弦。 */
        unsigned char  reserved           : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_CLK_WIFI_CTRL_UNION;
#endif
#define PMIC_CLK_WIFI_CTRL_xo_wifi_drv_START         (0)
#define PMIC_CLK_WIFI_CTRL_xo_wifi_drv_END           (1)
#define PMIC_CLK_WIFI_CTRL_np_xo_dig_wifi_sel_START  (2)
#define PMIC_CLK_WIFI_CTRL_np_xo_dig_wifi_sel_END    (2)


/*****************************************************************************
 结构名    : PMIC_CLK_RF0_CTRL_UNION
 结构说明  : CLK_RF0_CTRL 寄存器结构定义。地址偏移量:0x117，初值:0x05，宽度:8
 寄存器说明: RF0时钟配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_rf0_drv        : 2;  /* bit[0-1]: clk_rf0驱动能力控制，00表示驱动为3pF//100K,11表示驱动30pF//100K */
        unsigned char  np_xo_dig_rf0_sel : 1;  /* bit[2]  : 0：对应方波；
                                                            1：对应正弦。 */
        unsigned char  reserved          : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_CLK_RF0_CTRL_UNION;
#endif
#define PMIC_CLK_RF0_CTRL_xo_rf0_drv_START         (0)
#define PMIC_CLK_RF0_CTRL_xo_rf0_drv_END           (1)
#define PMIC_CLK_RF0_CTRL_np_xo_dig_rf0_sel_START  (2)
#define PMIC_CLK_RF0_CTRL_np_xo_dig_rf0_sel_END    (2)


/*****************************************************************************
 结构名    : PMIC_CLK_RF1_CTRL_UNION
 结构说明  : CLK_RF1_CTRL 寄存器结构定义。地址偏移量:0x118，初值:0x05，宽度:8
 寄存器说明: RF1时钟配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_rf1_drv        : 2;  /* bit[0-1]: clk_rf1驱动能力控制，00表示驱动为3pF//100K,11表示驱动30pF//100K */
        unsigned char  np_xo_dig_rf1_sel : 1;  /* bit[2]  : 0：对应方波；
                                                            1：对应正弦。 */
        unsigned char  reserved          : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_CLK_RF1_CTRL_UNION;
#endif
#define PMIC_CLK_RF1_CTRL_xo_rf1_drv_START         (0)
#define PMIC_CLK_RF1_CTRL_xo_rf1_drv_END           (1)
#define PMIC_CLK_RF1_CTRL_np_xo_dig_rf1_sel_START  (2)
#define PMIC_CLK_RF1_CTRL_np_xo_dig_rf1_sel_END    (2)


/*****************************************************************************
 结构名    : PMIC_CLK_SYS_CTRL_UNION
 结构说明  : CLK_SYS_CTRL 寄存器结构定义。地址偏移量:0x119，初值:0x03，宽度:8
 寄存器说明: SYS时钟配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_sys_drv : 2;  /* bit[0-1]: clk_sys驱动能力控制，00表示驱动为3pF//100K,11表示驱动30pF//100K */
        unsigned char  reserved   : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_CLK_SYS_CTRL_UNION;
#endif
#define PMIC_CLK_SYS_CTRL_xo_sys_drv_START  (0)
#define PMIC_CLK_SYS_CTRL_xo_sys_drv_END    (1)


/*****************************************************************************
 结构名    : PMIC_CLK_CODEC_CTRL_UNION
 结构说明  : CLK_CODEC_CTRL 寄存器结构定义。地址偏移量:0x11A，初值:0x01，宽度:8
 寄存器说明: CODEC时钟配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_codec_drv : 2;  /* bit[0-1]: clk_codec驱动能力控制，00表示驱动为3pF//100K,11表示驱动30pF//100K */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} PMIC_CLK_CODEC_CTRL_UNION;
#endif
#define PMIC_CLK_CODEC_CTRL_xo_codec_drv_START  (0)
#define PMIC_CLK_CODEC_CTRL_xo_codec_drv_END    (1)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL0_UNION
 结构说明  : CLK_TOP_CTRL0 寄存器结构定义。地址偏移量:0x11B，初值:0x50，宽度:8
 寄存器说明: 时钟控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_ldo_buff_curr : 2;  /* bit[0-1]: 内部LDO偏置电流制。 */
        unsigned char  reserved         : 2;  /* bit[2-3]: 保留。 */
        unsigned char  np_xo_trim_c2fix : 4;  /* bit[4-7]: 时钟频率精度trim寄存器2（和CLK_TOP_CTRL1[np_xo_c1fix]一起使用）。 */
    } reg;
} PMIC_CLK_TOP_CTRL0_UNION;
#endif
#define PMIC_CLK_TOP_CTRL0_xo_ldo_buff_curr_START  (0)
#define PMIC_CLK_TOP_CTRL0_xo_ldo_buff_curr_END    (1)
#define PMIC_CLK_TOP_CTRL0_np_xo_trim_c2fix_START  (4)
#define PMIC_CLK_TOP_CTRL0_np_xo_trim_c2fix_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL1_UNION
 结构说明  : CLK_TOP_CTRL1 寄存器结构定义。地址偏移量:0x11C，初值:0x50，宽度:8
 寄存器说明: 时钟控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_xo_trim_c1fix : 8;  /* bit[0-7]: 时钟频率精度trim寄存器1（和CLK_TOP_CTRL0[np_xo_c2fix]一起使用）。 */
    } reg;
} PMIC_CLK_TOP_CTRL1_UNION;
#endif
#define PMIC_CLK_TOP_CTRL1_np_xo_trim_c1fix_START  (0)
#define PMIC_CLK_TOP_CTRL1_np_xo_trim_c1fix_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL2_UNION
 结构说明  : CLK_TOP_CTRL2 寄存器结构定义。地址偏移量:0x11D，初值:0x00，宽度:8
 寄存器说明: 时钟控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_delay_sel : 2;  /* bit[0-1]: 时钟输出的Delay时间的控制选择信号 */
        unsigned char  xo_tri_cap   : 1;  /* bit[2]  : 时钟的三角波电路的电容控制 */
        unsigned char  reserved     : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_CLK_TOP_CTRL2_UNION;
#endif
#define PMIC_CLK_TOP_CTRL2_xo_delay_sel_START  (0)
#define PMIC_CLK_TOP_CTRL2_xo_delay_sel_END    (1)
#define PMIC_CLK_TOP_CTRL2_xo_tri_cap_START    (2)
#define PMIC_CLK_TOP_CTRL2_xo_tri_cap_END      (2)


/*****************************************************************************
 结构名    : PMIC_CLK_TOP_CTRL3_UNION
 结构说明  : CLK_TOP_CTRL3 寄存器结构定义。地址偏移量:0x11E，初值:0x00，宽度:8
 寄存器说明: 时钟控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_reserve : 8;  /* bit[0-7]: xo预留寄存器。 */
    } reg;
} PMIC_CLK_TOP_CTRL3_UNION;
#endif
#define PMIC_CLK_TOP_CTRL3_xo_reserve_START  (0)
#define PMIC_CLK_TOP_CTRL3_xo_reserve_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_256K_CTRL0_UNION
 结构说明  : CLK_256K_CTRL0 寄存器结构定义。地址偏移量:0x11F，初值:0x00，宽度:8
 寄存器说明: 256K RC控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_reg_256k_en0 : 8;  /* bit[0-7]: RC256K关闭控制。
                                                          0x5A：关闭256K时钟（同时reg_256k_en1为0xF0）；
                                                          其他：开启。 */
    } reg;
} PMIC_CLK_256K_CTRL0_UNION;
#endif
#define PMIC_CLK_256K_CTRL0_np_reg_256k_en0_START  (0)
#define PMIC_CLK_256K_CTRL0_np_reg_256k_en0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLK_256K_CTRL1_UNION
 结构说明  : CLK_256K_CTRL1 寄存器结构定义。地址偏移量:0x120，初值:0x00，宽度:8
 寄存器说明: 256K RC控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_reg_256k_en1 : 8;  /* bit[0-7]: RC256K关闭控制。
                                                          0xF0：关闭256K时钟（同时reg_256k_en0为0x5A）；
                                                          其他：开启。 */
    } reg;
} PMIC_CLK_256K_CTRL1_UNION;
#endif
#define PMIC_CLK_256K_CTRL1_np_reg_256k_en1_START  (0)
#define PMIC_CLK_256K_CTRL1_np_reg_256k_en1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OSC32K_ONOFF_CTRL_UNION
 结构说明  : OSC32K_ONOFF_CTRL 寄存器结构定义。地址偏移量:0x121，初值:0x01，宽度:8
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
 结构名    : PMIC_HARDWIRE_CTRL0_UNION
 结构说明  : HARDWIRE_CTRL0 寄存器结构定义。地址偏移量:0x125，初值:0x1F，宽度:8
 寄存器说明: 硬线屏蔽控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reg_eco_in_hd_mask      : 1;  /* bit[0]  : 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对eco_in_n的拉低/拉高控制作用。
                                                                  0：不屏蔽；
                                                                  1：屏蔽。 */
        unsigned char  reg_xo_ldo_buff_hd_mask : 1;  /* bit[1]  : 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对xo_ldo_buff_n的拉低/拉高控制作用。
                                                                  0：不屏蔽；
                                                                  1：屏蔽。 */
        unsigned char  reg_sys_clk_hd_mask     : 1;  /* bit[2]  : 是否屏蔽硬线SYS_CLK_EN对sys_clk的开/关控制作用。
                                                                  0：不屏蔽；
                                                                  1：屏蔽。 */
        unsigned char  reg_abb_clk_hd_mask     : 1;  /* bit[3]  : 是否屏蔽硬线SYS_CLK_EN对abb_clk的开/关控制作用。
                                                                  0：不屏蔽；
                                                                  1：屏蔽。 */
        unsigned char  reg_wifi_clk_hd_mask    : 1;  /* bit[4]  : 是否屏蔽硬线WIFIBT_CLK_EN对wifibt_clk的开/关控制作用。
                                                                  0：不屏蔽；
                                                                  1：屏蔽。 */
        unsigned char  reserved                : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_HARDWIRE_CTRL0_UNION;
#endif
#define PMIC_HARDWIRE_CTRL0_reg_eco_in_hd_mask_START       (0)
#define PMIC_HARDWIRE_CTRL0_reg_eco_in_hd_mask_END         (0)
#define PMIC_HARDWIRE_CTRL0_reg_xo_ldo_buff_hd_mask_START  (1)
#define PMIC_HARDWIRE_CTRL0_reg_xo_ldo_buff_hd_mask_END    (1)
#define PMIC_HARDWIRE_CTRL0_reg_sys_clk_hd_mask_START      (2)
#define PMIC_HARDWIRE_CTRL0_reg_sys_clk_hd_mask_END        (2)
#define PMIC_HARDWIRE_CTRL0_reg_abb_clk_hd_mask_START      (3)
#define PMIC_HARDWIRE_CTRL0_reg_abb_clk_hd_mask_END        (3)
#define PMIC_HARDWIRE_CTRL0_reg_wifi_clk_hd_mask_START     (4)
#define PMIC_HARDWIRE_CTRL0_reg_wifi_clk_hd_mask_END       (4)


/*****************************************************************************
 结构名    : PMIC_HARDWIRE_CTRL1_UNION
 结构说明  : HARDWIRE_CTRL1 寄存器结构定义。地址偏移量:0x126，初值:0x0F，宽度:8
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
        unsigned char  reg_ldo13_hd_mask : 1;  /* bit[3]  : 是否屏蔽“SYS_CLK_EN|WIFIBT_CLK_EN|reg_xo_codec_en寄存器”组合逻辑对ldo13的开/关控制作用。
                                                            0：不屏蔽；
                                                            1：屏蔽。 */
        unsigned char  reserved          : 4;  /* bit[4-7]: 保留 */
    } reg;
} PMIC_HARDWIRE_CTRL1_UNION;
#endif
#define PMIC_HARDWIRE_CTRL1_reg_ldo27_hd_mask_START  (0)
#define PMIC_HARDWIRE_CTRL1_reg_ldo27_hd_mask_END    (0)
#define PMIC_HARDWIRE_CTRL1_reg_ldo26_hd_mask_START  (1)
#define PMIC_HARDWIRE_CTRL1_reg_ldo26_hd_mask_END    (2)
#define PMIC_HARDWIRE_CTRL1_reg_ldo13_hd_mask_START  (3)
#define PMIC_HARDWIRE_CTRL1_reg_ldo13_hd_mask_END    (3)


/*****************************************************************************
 结构名    : PMIC_PERI_CTRL0_UNION
 结构说明  : PERI_CTRL0 寄存器结构定义。地址偏移量:0x127，初值:0x00，宽度:8
 寄存器说明: peri硬线控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo23_on : 1;  /* bit[0]  : LDO23受控源选择寄存器。
                                                           0：受寄存器和上下电控制开/关；
                                                           1：受peri_en控制而开/关。 */
        unsigned char  peri_en_ldo10_on : 1;  /* bit[1]  : LDO10受控源选择寄存器。
                                                           0：受寄存器和上下电控制开/关；
                                                           1：受peri_en控制而开/关。 */
        unsigned char  peri_en_ldo7_on  : 1;  /* bit[2]  : LDO7受控源选择寄存器。
                                                           0：受寄存器和上下电控制开/关；
                                                           1：受peri_en控制而开/关。 */
        unsigned char  peri_en_ldo5_on  : 1;  /* bit[3]  : LDO5受控源选择寄存器。
                                                           0：受寄存器和上下电控制开/关；
                                                           1：受peri_en控制而开/关。 */
        unsigned char  peri_en_buck0_on : 1;  /* bit[4]  : BUCK0受控源选择寄存器。
                                                           0：受寄存器和上下电控制开/关；
                                                           1：受peri_en控制而开/关。 */
        unsigned char  reserved         : 3;  /* bit[5-7]: 保留 */
    } reg;
} PMIC_PERI_CTRL0_UNION;
#endif
#define PMIC_PERI_CTRL0_peri_en_ldo23_on_START  (0)
#define PMIC_PERI_CTRL0_peri_en_ldo23_on_END    (0)
#define PMIC_PERI_CTRL0_peri_en_ldo10_on_START  (1)
#define PMIC_PERI_CTRL0_peri_en_ldo10_on_END    (1)
#define PMIC_PERI_CTRL0_peri_en_ldo7_on_START   (2)
#define PMIC_PERI_CTRL0_peri_en_ldo7_on_END     (2)
#define PMIC_PERI_CTRL0_peri_en_ldo5_on_START   (3)
#define PMIC_PERI_CTRL0_peri_en_ldo5_on_END     (3)
#define PMIC_PERI_CTRL0_peri_en_buck0_on_START  (4)
#define PMIC_PERI_CTRL0_peri_en_buck0_on_END    (4)


/*****************************************************************************
 结构名    : PMIC_PERI_CTRL1_UNION
 结构说明  : PERI_CTRL1 寄存器结构定义。地址偏移量:0x128，初值:0x00，宽度:8
 寄存器说明: peri硬线控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo8_eco   : 1;  /* bit[0]: LDO8低功耗受控源选择寄存器。
                                                           0：受寄存器控制开进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo4_eco   : 1;  /* bit[1]: LDO4低功耗受控源选择寄存器。
                                                           0：受寄存器控制开进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo2_eco   : 1;  /* bit[2]: LDO2低功耗受控源选择寄存器。
                                                           0：受寄存器控制开进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo0_2_eco : 1;  /* bit[3]: LDO0_2低功耗受控源选择寄存器。
                                                           0：受寄存器控制开进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_buck3_eco  : 1;  /* bit[4]: BUCK3低功耗受控源选择寄存器。
                                                           0：受寄存器控制开进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_buck2_eco  : 1;  /* bit[5]: BUCK2低功耗受控源选择寄存器。
                                                           0：受寄存器控制开进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_buck1_eco  : 1;  /* bit[6]: BUCK1低功耗受控源选择寄存器。
                                                           0：受寄存器控制开进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_buck0_eco  : 1;  /* bit[7]: BUCK0低功耗受控源选择寄存器。
                                                           0：受寄存器控制开进/出ECO；
                                                           1：受peri_en控制而进/出ECO。 */
    } reg;
} PMIC_PERI_CTRL1_UNION;
#endif
#define PMIC_PERI_CTRL1_peri_en_ldo8_eco_START    (0)
#define PMIC_PERI_CTRL1_peri_en_ldo8_eco_END      (0)
#define PMIC_PERI_CTRL1_peri_en_ldo4_eco_START    (1)
#define PMIC_PERI_CTRL1_peri_en_ldo4_eco_END      (1)
#define PMIC_PERI_CTRL1_peri_en_ldo2_eco_START    (2)
#define PMIC_PERI_CTRL1_peri_en_ldo2_eco_END      (2)
#define PMIC_PERI_CTRL1_peri_en_ldo0_2_eco_START  (3)
#define PMIC_PERI_CTRL1_peri_en_ldo0_2_eco_END    (3)
#define PMIC_PERI_CTRL1_peri_en_buck3_eco_START   (4)
#define PMIC_PERI_CTRL1_peri_en_buck3_eco_END     (4)
#define PMIC_PERI_CTRL1_peri_en_buck2_eco_START   (5)
#define PMIC_PERI_CTRL1_peri_en_buck2_eco_END     (5)
#define PMIC_PERI_CTRL1_peri_en_buck1_eco_START   (6)
#define PMIC_PERI_CTRL1_peri_en_buck1_eco_END     (6)
#define PMIC_PERI_CTRL1_peri_en_buck0_eco_START   (7)
#define PMIC_PERI_CTRL1_peri_en_buck0_eco_END     (7)


/*****************************************************************************
 结构名    : PMIC_PERI_CTRL2_UNION
 结构说明  : PERI_CTRL2 寄存器结构定义。地址偏移量:0x129，初值:0x00，宽度:8
 寄存器说明: peri硬线控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_ldo24_eco : 1;  /* bit[0]: LDO24低功耗受控源选择寄存器。
                                                          0：受寄存器控制开进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo17_eco : 1;  /* bit[1]: LDO17低功耗受控源选择寄存器。
                                                          0：受寄存器控制开进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo16_eco : 1;  /* bit[2]: LDO16低功耗受控源选择寄存器。
                                                          0：受寄存器控制开进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo15_eco : 1;  /* bit[3]: LDO15低功耗受控源选择寄存器。
                                                          0：受寄存器控制开进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo12_eco : 1;  /* bit[4]: LDO12低功耗受控源选择寄存器。
                                                          0：受寄存器控制开进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo11_eco : 1;  /* bit[5]: LDO11低功耗受控源选择寄存器。
                                                          0：受寄存器控制开进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo10_eco : 1;  /* bit[6]: LDO10低功耗受控源选择寄存器。
                                                          0：受寄存器控制开进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo9_eco  : 1;  /* bit[7]: LDO9低功耗受控源选择寄存器。
                                                          0：受寄存器控制开进/出ECO；
                                                          1：受peri_en控制而进/出ECO。 */
    } reg;
} PMIC_PERI_CTRL2_UNION;
#endif
#define PMIC_PERI_CTRL2_peri_en_ldo24_eco_START  (0)
#define PMIC_PERI_CTRL2_peri_en_ldo24_eco_END    (0)
#define PMIC_PERI_CTRL2_peri_en_ldo17_eco_START  (1)
#define PMIC_PERI_CTRL2_peri_en_ldo17_eco_END    (1)
#define PMIC_PERI_CTRL2_peri_en_ldo16_eco_START  (2)
#define PMIC_PERI_CTRL2_peri_en_ldo16_eco_END    (2)
#define PMIC_PERI_CTRL2_peri_en_ldo15_eco_START  (3)
#define PMIC_PERI_CTRL2_peri_en_ldo15_eco_END    (3)
#define PMIC_PERI_CTRL2_peri_en_ldo12_eco_START  (4)
#define PMIC_PERI_CTRL2_peri_en_ldo12_eco_END    (4)
#define PMIC_PERI_CTRL2_peri_en_ldo11_eco_START  (5)
#define PMIC_PERI_CTRL2_peri_en_ldo11_eco_END    (5)
#define PMIC_PERI_CTRL2_peri_en_ldo10_eco_START  (6)
#define PMIC_PERI_CTRL2_peri_en_ldo10_eco_END    (6)
#define PMIC_PERI_CTRL2_peri_en_ldo9_eco_START   (7)
#define PMIC_PERI_CTRL2_peri_en_ldo9_eco_END     (7)


/*****************************************************************************
 结构名    : PMIC_PERI_CTRL3_UNION
 结构说明  : PERI_CTRL3 寄存器结构定义。地址偏移量:0x12A，初值:0x00，宽度:8
 寄存器说明: peri硬线控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_en_thsd_eco  : 1;  /* bit[0]  : THSD低功耗受控源选择寄存器。
                                                            0：受寄存器控制开进/出ECO；
                                                            1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_pmua_eco  : 1;  /* bit[1]  : PMUA低功耗受控源选择寄存器。
                                                            0：受寄存器控制开进/出ECO；
                                                            1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo34_eco : 1;  /* bit[2]  : LDO34低功耗受控源选择寄存器。
                                                            0：受寄存器控制开进/出ECO；
                                                            1：受peri_en控制而进/出ECO。 */
        unsigned char  peri_en_ldo29_eco : 1;  /* bit[3]  : LDO29低功耗受控源选择寄存器。
                                                            0：受寄存器控制开进/出ECO；
                                                            1：受peri_en控制而进/出ECO。 */
        unsigned char  reserved          : 4;  /* bit[4-7]: 保留 */
    } reg;
} PMIC_PERI_CTRL3_UNION;
#endif
#define PMIC_PERI_CTRL3_peri_en_thsd_eco_START   (0)
#define PMIC_PERI_CTRL3_peri_en_thsd_eco_END     (0)
#define PMIC_PERI_CTRL3_peri_en_pmua_eco_START   (1)
#define PMIC_PERI_CTRL3_peri_en_pmua_eco_END     (1)
#define PMIC_PERI_CTRL3_peri_en_ldo34_eco_START  (2)
#define PMIC_PERI_CTRL3_peri_en_ldo34_eco_END    (2)
#define PMIC_PERI_CTRL3_peri_en_ldo29_eco_START  (3)
#define PMIC_PERI_CTRL3_peri_en_ldo29_eco_END    (3)


/*****************************************************************************
 结构名    : PMIC_PERI_VSET_CTRL_UNION
 结构说明  : PERI_VSET_CTRL 寄存器结构定义。地址偏移量:0x12B，初值:0x00，宽度:8
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
 结构说明  : PERI_TIME__CTRL 寄存器结构定义。地址偏移量:0x12C，初值:0x00，宽度:8
 寄存器说明: peri硬线时间间隔控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  peri_time_sel : 1;  /* bit[0]  : PERI_EN拉高上电间隔控制位。
                                                        0：peri_en拉高时LDO上电间隔为120us，BUCK上电间隔为240us；
                                                        1：peri_en拉高时LDO5和LDO8上电间隔为60us，BUCK上电间隔为120us。 */
        unsigned char  reserved      : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_PERI_TIME__CTRL_UNION;
#endif
#define PMIC_PERI_TIME__CTRL_peri_time_sel_START  (0)
#define PMIC_PERI_TIME__CTRL_peri_time_sel_END    (0)


/*****************************************************************************
 结构名    : PMIC_COUL_ECO_MASK_UNION
 结构说明  : COUL_ECO_MASK 寄存器结构定义。地址偏移量:0x12D，初值:0x07，宽度:8
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
 结构名    : PMIC_IRQ_MASK_0_UNION
 结构说明  : IRQ_MASK_0 寄存器结构定义。地址偏移量:0x130，初值:0x00，宽度:8
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
                                                     bit[0]：过温125°中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_0_UNION;
#endif
#define PMIC_IRQ_MASK_0_irq_mask_0_START  (0)
#define PMIC_IRQ_MASK_0_irq_mask_0_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_1_UNION
 结构说明  : IRQ_MASK_1 寄存器结构定义。地址偏移量:0x131，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK1控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_1 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7:6]：保留使用，可读写；
                                                     bit[5]：sim_hpd1下降沿中断屏蔽；
                                                     bit[4]：sim_hpd1上升沿中断屏蔽；
                                                     bit[3]：sim_hpd0下降沿中断屏蔽；
                                                     bit[2]：sim_hpd0上升沿中断屏蔽；
                                                     bit[1]：库仑计中断总屏蔽；
                                                     bit[0]：OCP中断总屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_1_UNION;
#endif
#define PMIC_IRQ_MASK_1_irq_mask_1_START  (0)
#define PMIC_IRQ_MASK_1_irq_mask_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_2_UNION
 结构说明  : IRQ_MASK_2 寄存器结构定义。地址偏移量:0x132，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK3控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_2 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：BUCK0输出过载中断屏蔽；
                                                     bit[6]：BUCK1输出过载中断屏蔽；
                                                     bit[5]：BUCK2输出过载中断屏蔽；
                                                     bit[4]：BUCK3输出过载中断屏蔽；
                                                     bit[3]：LDO0_2输出过载中断屏蔽；
                                                     bit[2]：LDO1输出过载中断屏蔽；
                                                     bit[1]：LDO2输出过载中断屏蔽;
                                                     bit[0]：LDO3输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_2_UNION;
#endif
#define PMIC_IRQ_MASK_2_irq_mask_2_START  (0)
#define PMIC_IRQ_MASK_2_irq_mask_2_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_3_UNION
 结构说明  : IRQ_MASK_3 寄存器结构定义。地址偏移量:0x133，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK4控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_3 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：LDO4输出过载中断屏蔽；
                                                     bit[6]：LDO5输出过载中断屏蔽；
                                                     bit[5]：LDO7输出过载中断屏蔽；
                                                     bit[4]：LDO8输出过载中断屏蔽；
                                                     bit[3]：LDO9输出过载中断屏蔽；
                                                     bit[2]：LDO10输出过载中断屏蔽；
                                                     bit[1]：LDO11输出过载中断屏蔽;
                                                     bit[0]：LDO12输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_3_UNION;
#endif
#define PMIC_IRQ_MASK_3_irq_mask_3_START  (0)
#define PMIC_IRQ_MASK_3_irq_mask_3_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_4_UNION
 结构说明  : IRQ_MASK_4 寄存器结构定义。地址偏移量:0x134，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK5控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_4 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：LDO13输出过载中断屏蔽；
                                                     bit[6]：LDO14输出过载中断屏蔽；
                                                     bit[5]：LDO15输出过载中断屏蔽；
                                                     bit[4]：LDO16输出过载中断屏蔽；
                                                     bit[3]：LDO17输出过载中断屏蔽；
                                                     bit[2]：LDO19输出过载中断屏蔽；
                                                     bit[1]：LDO20输出过载中断屏蔽；
                                                     bit[0]：LDO21输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_4_UNION;
#endif
#define PMIC_IRQ_MASK_4_irq_mask_4_START  (0)
#define PMIC_IRQ_MASK_4_irq_mask_4_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_5_UNION
 结构说明  : IRQ_MASK_5 寄存器结构定义。地址偏移量:0x135，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK6控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_5 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7]：LDO22输出过载中断屏蔽；
                                                     bit[6]：LDO23输出过载中断屏蔽；
                                                     bit[5]：LDO24输出过载中断屏蔽；
                                                     bit[4]：LDO25输出过载中断屏蔽；
                                                     bit[3]：LDO26输出过载中断屏蔽；
                                                     bit[2]：LDO27输出过载中断屏蔽；
                                                     bit[1]：LDO28输出过载中断屏蔽；
                                                     bit[0]：LDO29输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_5_UNION;
#endif
#define PMIC_IRQ_MASK_5_irq_mask_5_START  (0)
#define PMIC_IRQ_MASK_5_irq_mask_5_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_6_UNION
 结构说明  : IRQ_MASK_6 寄存器结构定义。地址偏移量:0x136，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK7控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_6 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7:5]：保留使用，可读写；
                                                     bit[4]：LDO31输出过载中断屏蔽；
                                                     bit[3]：LDO32输出过载中断屏蔽；
                                                     bit[2]：LDO33输出过载中断屏蔽；
                                                     bit[1]：LDO34输出过载中断屏蔽；
                                                     bit[0]：class输出过载中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_6_UNION;
#endif
#define PMIC_IRQ_MASK_6_irq_mask_6_START  (0)
#define PMIC_IRQ_MASK_6_irq_mask_6_END    (7)


/*****************************************************************************
 结构名    : PMIC_IRQ_MASK_7_UNION
 结构说明  : IRQ_MASK_7 寄存器结构定义。地址偏移量:0x137，初值:0x00，宽度:8
 寄存器说明: IRQ_MASK8控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  irq_mask_7 : 8;  /* bit[0-7]: 中断mask，写1屏蔽。
                                                     bit[7：5]：保留使用，可读写；
                                                     bit[4]：xo_ldo_buff输出短路中断屏蔽
                                                     bit[3]：BUCK0输出短路中断屏蔽；
                                                     bit[2]：BUCK1输出短路中断屏蔽；
                                                     bit[1]：BUCK2输出短路中断屏蔽；
                                                     bit[0]：BUCK3输出短路中断屏蔽。 */
    } reg;
} PMIC_IRQ_MASK_7_UNION;
#endif
#define PMIC_IRQ_MASK_7_irq_mask_7_START  (0)
#define PMIC_IRQ_MASK_7_irq_mask_7_END    (7)


/*****************************************************************************
 结构名    : PMIC_BACKUP_CHG_UNION
 结构说明  : BACKUP_CHG 寄存器结构定义。地址偏移量:0x13A，初值:0x09，宽度:8
 寄存器说明: NOPWRT控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_chg_en     : 1;  /* bit[0]  : 备用电池充电使能。
                                                        0：不使能；
                                                        1：使能。 */
        unsigned char  np_chg_bypass : 1;  /* bit[1]  : 备用电池直通模式控制。
                                                        0：不直通；
                                                        1：直通。  */
        unsigned char  np_chg_vset   : 2;  /* bit[2-3]: 备用电池充电电压选择。
                                                        00：2.5V；
                                                        01：3.0V；
                                                        1X：3.3V。 */
        unsigned char  reserved      : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_BACKUP_CHG_UNION;
#endif
#define PMIC_BACKUP_CHG_np_chg_en_START      (0)
#define PMIC_BACKUP_CHG_np_chg_en_END        (0)
#define PMIC_BACKUP_CHG_np_chg_bypass_START  (1)
#define PMIC_BACKUP_CHG_np_chg_bypass_END    (1)
#define PMIC_BACKUP_CHG_np_chg_vset_START    (2)
#define PMIC_BACKUP_CHG_np_chg_vset_END      (3)


/*****************************************************************************
 结构名    : PMIC_CLASSD_CTRL0_UNION
 结构说明  : CLASSD_CTRL0 寄存器结构定义。地址偏移量:0x13B，初值:0x00，宽度:8
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
                                                          00：1.5A；
                                                          01：2.0A；
                                                          10：2.5A；
                                                          11：3.0A。 */
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
 结构说明  : CLASSD_CTRL1 寄存器结构定义。地址偏移量:0x13C，初值:0x00，宽度:8
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
        unsigned char  classd_p_sel  : 2;  /* bit[2-3]: 驱动级pmos控制。
                                                        00：开一路pmos；
                                                        01：开两路pmos；
                                                        10：开三路pmos；
                                                        11：开四路pmos。 */
        unsigned char  classd_n_sel  : 2;  /* bit[4-5]: 驱动级nmos控制。
                                                        00：开一路nmos；
                                                        01：开两路nmos；
                                                        10：开三路nmos；
                                                        11：开四路nmos。 */
        unsigned char  reserved      : 2;  /* bit[6-7]: 保留 */
    } reg;
} PMIC_CLASSD_CTRL1_UNION;
#endif
#define PMIC_CLASSD_CTRL1_classd_i_pump_START  (0)
#define PMIC_CLASSD_CTRL1_classd_i_pump_END    (1)
#define PMIC_CLASSD_CTRL1_classd_p_sel_START   (2)
#define PMIC_CLASSD_CTRL1_classd_p_sel_END     (3)
#define PMIC_CLASSD_CTRL1_classd_n_sel_START   (4)
#define PMIC_CLASSD_CTRL1_classd_n_sel_END     (5)


/*****************************************************************************
 结构名    : PMIC_CLASSD_CTRL2_UNION
 结构说明  : CLASSD_CTRL2 寄存器结构定义。地址偏移量:0x13D，初值:0x00，宽度:8
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
        unsigned char  classd_ocp_bps  : 1;  /* bit[2]  : 过流保护控制。
                                                          0：开启过流保护；
                                                          1：bypass过流保护电路（OCP信号不上报）。 */
        unsigned char  reserved        : 1;  /* bit[3]  : 保留 */
        unsigned char  classd_reserve0 : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_CLASSD_CTRL2_UNION;
#endif
#define PMIC_CLASSD_CTRL2_classd_pls_byp_START   (0)
#define PMIC_CLASSD_CTRL2_classd_pls_byp_END     (0)
#define PMIC_CLASSD_CTRL2_classd_dt_sel_START    (1)
#define PMIC_CLASSD_CTRL2_classd_dt_sel_END      (1)
#define PMIC_CLASSD_CTRL2_classd_ocp_bps_START   (2)
#define PMIC_CLASSD_CTRL2_classd_ocp_bps_END     (2)
#define PMIC_CLASSD_CTRL2_classd_reserve0_START  (4)
#define PMIC_CLASSD_CTRL2_classd_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLASSD_CTRL3_UNION
 结构说明  : CLASSD_CTRL3 寄存器结构定义。地址偏移量:0x13E，初值:0x00，宽度:8
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
 结构说明  : TH_CTRL 寄存器结构定义。地址偏移量:0x13F，初值:0xD1，宽度:8
 寄存器说明: 电压温度控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_res_sel_int   : 1;  /* bit[0]  : 基准VREF管脚滤波电阻选择 。 */
        unsigned char  ref_ibias_trim_en : 2;  /* bit[1-2]: 基准电流Trim使能信号 */
        unsigned char  reserved          : 1;  /* bit[3]  : 保留 */
        unsigned char  reg_thsd_en       : 1;  /* bit[4]  : THSD过温保护模块关闭/开关控制位。
                                                            0：关闭THSD过温保护模块；
                                                            1：开启THSD过温保护模块。 */
        unsigned char  reg_thsd_eco_en   : 1;  /* bit[5]  : THSD过温保护模块ECO控制位。
                                                            0：退出低功耗模式；
                                                            1：进入低功耗模式；高电平为10ms，周期为1s的周期信号。 */
        unsigned char  thsd_tmp_set      : 2;  /* bit[6-7]: 温度保护模块报警温度设置。
                                                            00：95℃；
                                                            01：105℃；
                                                            10：115℃；
                                                            11：125℃。 */
    } reg;
} PMIC_TH_CTRL_UNION;
#endif
#define PMIC_TH_CTRL_ref_res_sel_int_START    (0)
#define PMIC_TH_CTRL_ref_res_sel_int_END      (0)
#define PMIC_TH_CTRL_ref_ibias_trim_en_START  (1)
#define PMIC_TH_CTRL_ref_ibias_trim_en_END    (2)
#define PMIC_TH_CTRL_reg_thsd_en_START        (4)
#define PMIC_TH_CTRL_reg_thsd_en_END          (4)
#define PMIC_TH_CTRL_reg_thsd_eco_en_START    (5)
#define PMIC_TH_CTRL_reg_thsd_eco_en_END      (5)
#define PMIC_TH_CTRL_thsd_tmp_set_START       (6)
#define PMIC_TH_CTRL_thsd_tmp_set_END         (7)


/*****************************************************************************
 结构名    : PMIC_BG_TEST_UNION
 结构说明  : BG_TEST 寄存器结构定义。地址偏移量:0x140，初值:0x00，宽度:8
 寄存器说明: bg测试寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_reserve : 8;  /* bit[0-7]: 基准测试模式预留。 */
    } reg;
} PMIC_BG_TEST_UNION;
#endif
#define PMIC_BG_TEST_ref_reserve_START  (0)
#define PMIC_BG_TEST_ref_reserve_END    (7)


/*****************************************************************************
 结构名    : PMIC_DR_EN_MODE_345_UNION
 结构说明  : DR_EN_MODE_345 寄存器结构定义。地址偏移量:0x141，初值:0x00，宽度:8
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
 结构说明  : DR_EN_MODE_12 寄存器结构定义。地址偏移量:0x142，初值:0x00，宽度:8
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
 结构说明  : FLASH_PERIOD_DR12 寄存器结构定义。地址偏移量:0x143，初值:0x3F，宽度:8
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
 结构说明  : FLASH_ON_DR12 寄存器结构定义。地址偏移量:0x144，初值:0x1F，宽度:8
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
 结构说明  : FLASH_PERIOD_DR345 寄存器结构定义。地址偏移量:0x145，初值:0x3F，宽度:8
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
 结构说明  : FLASH_ON_DR345 寄存器结构定义。地址偏移量:0x146，初值:0x1F，宽度:8
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
 结构说明  : DR_MODE_SEL 寄存器结构定义。地址偏移量:0x147，初值:0x00，宽度:8
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
 结构说明  : DR_BRE_CTRL 寄存器结构定义。地址偏移量:0x148，初值:0x00，宽度:8
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
 结构说明  : DR12_TIM_CONF0 寄存器结构定义。地址偏移量:0x149，初值:0x33，宽度:8
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
 结构说明  : DR12_TIM_CONF1 寄存器结构定义。地址偏移量:0x14A，初值:0x33，宽度:8
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
 结构说明  : DR1_ISET 寄存器结构定义。地址偏移量:0x14B，初值:0x00，宽度:8
 寄存器说明: DR1电流选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr1_iset : 3;  /* bit[0-2]: DR1电流调节。 000：1 mA；
                                                   001：3 mA；
                                                   010：5 mA；
                                                   011：7 mA；
                                                   100：9 mA；
                                                   101：11 mA；
                                                   110：13 mA；
                                                   111：15 mA。 */
        unsigned char  reserved : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_DR1_ISET_UNION;
#endif
#define PMIC_DR1_ISET_dr1_iset_START  (0)
#define PMIC_DR1_ISET_dr1_iset_END    (2)


/*****************************************************************************
 结构名    : PMIC_DR2_ISET_UNION
 结构说明  : DR2_ISET 寄存器结构定义。地址偏移量:0x14C，初值:0x00，宽度:8
 寄存器说明: DR2电流选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dr2_iset : 3;  /* bit[0-2]: DR2电流调节。 000：1 mA；
                                                   001：3 mA；
                                                   010：5 mA；
                                                   011：7 mA；
                                                   100：9 mA；
                                                   101：11 mA；
                                                   110：13 mA；
                                                   111：15 mA。 */
        unsigned char  reserved : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_DR2_ISET_UNION;
#endif
#define PMIC_DR2_ISET_dr2_iset_START  (0)
#define PMIC_DR2_ISET_dr2_iset_END    (2)


/*****************************************************************************
 结构名    : PMIC_DR_LED_CTRL_UNION
 结构说明  : DR_LED_CTRL 寄存器结构定义。地址偏移量:0x14D，初值:0x00，宽度:8
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
 结构说明  : DR_OUT_CTRL 寄存器结构定义。地址偏移量:0x14E，初值:0x00，宽度:8
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
 结构说明  : DR3_ISET 寄存器结构定义。地址偏移量:0x14F，初值:0x00，宽度:8
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
 结构说明  : DR3_START_DEL 寄存器结构定义。地址偏移量:0x150，初值:0x10，宽度:8
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
 结构说明  : DR4_ISET 寄存器结构定义。地址偏移量:0x151，初值:0x00，宽度:8
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
 结构说明  : DR4_START_DEL 寄存器结构定义。地址偏移量:0x152，初值:0x10，宽度:8
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
 结构说明  : DR5_ISET 寄存器结构定义。地址偏移量:0x153，初值:0x00，宽度:8
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
 结构说明  : DR5_START_DEL 寄存器结构定义。地址偏移量:0x154，初值:0x10，宽度:8
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
 结构说明  : DR334_TIM_CONF0 寄存器结构定义。地址偏移量:0x155，初值:0x44，宽度:8
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
 结构说明  : DR345_TIM_CONF1 寄存器结构定义。地址偏移量:0x156，初值:0x33，宽度:8
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
 结构名    : PMIC_VSYS_LOW_SET_UNION
 结构说明  : VSYS_LOW_SET 寄存器结构定义。地址偏移量:0x157，初值:0x21，宽度:8
 寄存器说明: IN端低压阈值调整寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_vsys_pwroff_deb_set : 3;  /* bit[0-2]: 关机电压阈值调节，低于此电压PMU关机。
                                                                 000：2.5V；
                                                                 001：2.6V；
                                                                 010：2.7V；
                                                                 011：2.8V；
                                                                 100：2.9V；
                                                                 101：3.0V；
                                                                 110：3.1V；
                                                                 111：3.2V。 */
        unsigned char  np_vsys_pwroff_abs_set : 1;  /* bit[3]  : vsys端低电压判断阈值电压调整，低于此电压立刻关机，不滤波。
                                                                 0：2.3V；
                                                                 1：2.4V。 */
        unsigned char  np_vsys_pwron_set      : 3;  /* bit[4-6]: 开机电压阈值调节，高于此电压PMU开机。
                                                                 000：2.6V；
                                                                 001：2.7V；
                                                                 010：2.8V；
                                                                 011：2.9V；
                                                                 100：3.0V；
                                                                 101：3.1V；
                                                                 110：3.2V；
                                                                 111：3.3V。 */
        unsigned char  reserved               : 1;  /* bit[7]  : 保留 */
    } reg;
} PMIC_VSYS_LOW_SET_UNION;
#endif
#define PMIC_VSYS_LOW_SET_np_vsys_pwroff_deb_set_START  (0)
#define PMIC_VSYS_LOW_SET_np_vsys_pwroff_deb_set_END    (2)
#define PMIC_VSYS_LOW_SET_np_vsys_pwroff_abs_set_START  (3)
#define PMIC_VSYS_LOW_SET_np_vsys_pwroff_abs_set_END    (3)
#define PMIC_VSYS_LOW_SET_np_vsys_pwron_set_START       (4)
#define PMIC_VSYS_LOW_SET_np_vsys_pwron_set_END         (6)


/*****************************************************************************
 结构名    : PMIC_NFC_ON_CTRL_UNION
 结构说明  : NFC_ON_CTRL 寄存器结构定义。地址偏移量:0x158，初值:0x00，宽度:8
 寄存器说明: nfc_on控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_nfc_on_d2a : 1;  /* bit[0]  : NFC_ON输出管脚，非掉电寄存器，放在PMUD域下面。
                                                        0：NFC_ON管脚输出0电平；
                                                        1：NFC_ON管脚输出1.8V。 */
        unsigned char  reserved      : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_NFC_ON_CTRL_UNION;
#endif
#define PMIC_NFC_ON_CTRL_np_nfc_on_d2a_START  (0)
#define PMIC_NFC_ON_CTRL_np_nfc_on_d2a_END    (0)


/*****************************************************************************
 结构名    : PMIC_SYS_CTRL_RESERVE_UNION
 结构说明  : SYS_CTRL_RESERVE 寄存器结构定义。地址偏移量:0x159，初值:0x00，宽度:8
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
 结构名    : PMIC_HRESET_PWRDOWN_CTRL_UNION
 结构说明  : HRESET_PWRDOWN_CTRL 寄存器结构定义。地址偏移量:0x15A，初值:0x01，宽度:8
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
        unsigned char  reserved       : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_HRESET_PWRDOWN_CTRL_UNION;
#endif
#define PMIC_HRESET_PWRDOWN_CTRL_hreset_mode_START  (0)
#define PMIC_HRESET_PWRDOWN_CTRL_hreset_mode_END    (0)


/*****************************************************************************
 结构名    : PMIC_OCP_DEB_CTRL0_UNION
 结构说明  : OCP_DEB_CTRL0 寄存器结构定义。地址偏移量:0x15B，初值:0x04，宽度:8
 寄存器说明: OCP和SPC滤波时间控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo31_ocp_deb_sel : 2;  /* bit[0-1]: LDO31的OCP滤波时间。
                                                            000：1ms；
                                                            001：2ms；
                                                            010：4ms；
                                                            011：8ms。 */
        unsigned char  ldo_ocp_deb_sel   : 2;  /* bit[2-3]: LDO的OCP滤波时间（除了LDO31）。
                                                            000：0.5ms
                                                            001：1ms；
                                                            010：2ms；
                                                            011：4ms。 */
        unsigned char  buck_scp_deb_sel  : 2;  /* bit[4-5]: BUCK的SCP，滤波时间选择。
                                                            00：60us（非绝对60us，可能是90us或120us等较小值）；
                                                            01：0.5ms；
                                                            10：1ms；
                                                            11：2ms。 */
        unsigned char  buck_ocp_deb_sel  : 2;  /* bit[6-7]: BUCK的OCP，滤波时间选择。
                                                            00：60us（非绝对60us，可能是90us或120us等较小值）；
                                                            01：0.5ms；
                                                            10：1ms；
                                                            11：2ms。 */
    } reg;
} PMIC_OCP_DEB_CTRL0_UNION;
#endif
#define PMIC_OCP_DEB_CTRL0_ldo31_ocp_deb_sel_START  (0)
#define PMIC_OCP_DEB_CTRL0_ldo31_ocp_deb_sel_END    (1)
#define PMIC_OCP_DEB_CTRL0_ldo_ocp_deb_sel_START    (2)
#define PMIC_OCP_DEB_CTRL0_ldo_ocp_deb_sel_END      (3)
#define PMIC_OCP_DEB_CTRL0_buck_scp_deb_sel_START   (4)
#define PMIC_OCP_DEB_CTRL0_buck_scp_deb_sel_END     (5)
#define PMIC_OCP_DEB_CTRL0_buck_ocp_deb_sel_START   (6)
#define PMIC_OCP_DEB_CTRL0_buck_ocp_deb_sel_END     (7)


/*****************************************************************************
 结构名    : PMIC_OCP_DEB_CTRL1_UNION
 结构说明  : OCP_DEB_CTRL1 寄存器结构定义。地址偏移量:0x15C，初值:0xC5，宽度:8
 寄存器说明: OCP和SPC滤波时间控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vin_ldoh_deb_sel        : 2;  /* bit[0-1]: vin_ldoh的滤波时间。
                                                                  000：0.5ms
                                                                  001：1ms；
                                                                  010：2ms；
                                                                  011：4ms。 */
        unsigned char  xo_ldo_buff_scp_deb_sel : 2;  /* bit[2-3]: xo_ldo_buff的SCP滤波时间。
                                                                  000：0.5ms
                                                                  001：1ms；
                                                                  010：2ms；
                                                                  011：4ms。 */
        unsigned char  classd_ocp_deb_sel      : 2;  /* bit[4-5]: classd的OCP，滤波时间选择。
                                                                  00：60us（非绝对60us，可能是90us或120us等较小值）；
                                                                  01：0.5ms；
                                                                  10：1ms；
                                                                  11：2ms。 */
        unsigned char  ldo27_ocp_deb_sel       : 2;  /* bit[6-7]: LDO31的OCP滤波时间。
                                                                  000：0.5ms
                                                                  001：1ms；
                                                                  010：2ms；
                                                                  011：4ms。 */
    } reg;
} PMIC_OCP_DEB_CTRL1_UNION;
#endif
#define PMIC_OCP_DEB_CTRL1_vin_ldoh_deb_sel_START         (0)
#define PMIC_OCP_DEB_CTRL1_vin_ldoh_deb_sel_END           (1)
#define PMIC_OCP_DEB_CTRL1_xo_ldo_buff_scp_deb_sel_START  (2)
#define PMIC_OCP_DEB_CTRL1_xo_ldo_buff_scp_deb_sel_END    (3)
#define PMIC_OCP_DEB_CTRL1_classd_ocp_deb_sel_START       (4)
#define PMIC_OCP_DEB_CTRL1_classd_ocp_deb_sel_END         (5)
#define PMIC_OCP_DEB_CTRL1_ldo27_ocp_deb_sel_START        (6)
#define PMIC_OCP_DEB_CTRL1_ldo27_ocp_deb_sel_END          (7)


/*****************************************************************************
 结构名    : PMIC_OCP_SCP_ONOFF_UNION
 结构说明  : OCP_SCP_ONOFF 寄存器结构定义。地址偏移量:0x15D，初值:0xFF，宽度:8
 寄存器说明: OCP和DOCP滤波开关寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  en_vin_ldoh_deb        : 1;  /* bit[0]: vin_ldoh滤波功能使能位。
                                                               0：vin_ldoh 滤波不使能；
                                                               1：vin_ldoh 滤波使能。 */
        unsigned char  en_xo_ldo_buff_scp_deb : 1;  /* bit[1]: xo_ldo_buff SCP滤波功能使能位。
                                                               0：xo_ldo_buff 滤波不使能；
                                                               1：xo_ldo_buff 滤波使能。 */
        unsigned char  en_classd_ocp_deb      : 1;  /* bit[2]: CLASSD OCP滤波功能使能位。
                                                               0：CLASSD OCP 滤波不使能；
                                                               1：CLASSD OCP 滤波使能。 */
        unsigned char  en_ldo31_ocp_deb       : 1;  /* bit[3]: LDO31 OCP滤波功能使能位。
                                                               0：LDO31 OCP 滤波不使能；
                                                               1：LDO31 OCP 滤波使能。 */
        unsigned char  en_ldo_ocp_deb         : 1;  /* bit[4]: LDO OCP（除了LDO31）滤波功能使能位。
                                                               0：LDO OCP 滤波不使能；
                                                               1：LDO OCP 滤波使能。 */
        unsigned char  en_buck_scp_deb        : 1;  /* bit[5]: BUCK scp滤波功能使能位。
                                                               0：BUCK scp 滤波不使能；
                                                               1：BUCK scp 滤波使能。 */
        unsigned char  en_buck_ocp_deb        : 1;  /* bit[6]: BUCK OCP滤波功能使能位。
                                                               0：BUCK OCP 滤波不使能；
                                                               1：BUCK OCP 滤波使能。 */
        unsigned char  en_ldo27_ocp_deb       : 1;  /* bit[7]: LDO27 OCP滤波功能使能位。
                                                               0：LDO27 OCP 滤波不使能；
                                                               1：LDO27 OCP 滤波使能。 */
    } reg;
} PMIC_OCP_SCP_ONOFF_UNION;
#endif
#define PMIC_OCP_SCP_ONOFF_en_vin_ldoh_deb_START         (0)
#define PMIC_OCP_SCP_ONOFF_en_vin_ldoh_deb_END           (0)
#define PMIC_OCP_SCP_ONOFF_en_xo_ldo_buff_scp_deb_START  (1)
#define PMIC_OCP_SCP_ONOFF_en_xo_ldo_buff_scp_deb_END    (1)
#define PMIC_OCP_SCP_ONOFF_en_classd_ocp_deb_START       (2)
#define PMIC_OCP_SCP_ONOFF_en_classd_ocp_deb_END         (2)
#define PMIC_OCP_SCP_ONOFF_en_ldo31_ocp_deb_START        (3)
#define PMIC_OCP_SCP_ONOFF_en_ldo31_ocp_deb_END          (3)
#define PMIC_OCP_SCP_ONOFF_en_ldo_ocp_deb_START          (4)
#define PMIC_OCP_SCP_ONOFF_en_ldo_ocp_deb_END            (4)
#define PMIC_OCP_SCP_ONOFF_en_buck_scp_deb_START         (5)
#define PMIC_OCP_SCP_ONOFF_en_buck_scp_deb_END           (5)
#define PMIC_OCP_SCP_ONOFF_en_buck_ocp_deb_START         (6)
#define PMIC_OCP_SCP_ONOFF_en_buck_ocp_deb_END           (6)
#define PMIC_OCP_SCP_ONOFF_en_ldo27_ocp_deb_START        (7)
#define PMIC_OCP_SCP_ONOFF_en_ldo27_ocp_deb_END          (7)


/*****************************************************************************
 结构名    : PMIC_PWROFF_DEB_CTRL_UNION
 结构说明  : PWROFF_DEB_CTRL 寄存器结构定义。地址偏移量:0x15E，初值:0x07，宽度:8
 寄存器说明: 欠压关机滤波时间选择寄存器。
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
        unsigned char  reserved            : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_PWROFF_DEB_CTRL_UNION;
#endif
#define PMIC_PWROFF_DEB_CTRL_vsys_pwroff_deb_sel_START  (0)
#define PMIC_PWROFF_DEB_CTRL_vsys_pwroff_deb_sel_END    (2)


/*****************************************************************************
 结构名    : PMIC_SYS_CTRL0_UNION
 结构说明  : SYS_CTRL0 寄存器结构定义。地址偏移量:0x15F，初值:0x00，宽度:8
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
                                                                  1：不自动关机。
                                                                  注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  vsys_pwroff_deb_pd_mask : 1;  /* bit[1]  : vsys小于2.6v时是否自动关机控制位。
                                                                  0：自动关机；
                                                                  1：不自动关机。
                                                                  注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  thsd_otmp140_pd_mask    : 1;  /* bit[2]  : 温度超过140度时是否自动关机控制位。
                                                                  0：自动关机；
                                                                  1：不自动关机。
                                                                  注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  vsys_ov_pd_mask         : 1;  /* bit[3]  : vsys过压时是否自动关机控制位。
                                                                  0：自动关机；
                                                                  1：不自动关机。
                                                                  注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  vin_ldoh_vld_pd_mask    : 1;  /* bit[4]  : VIN_LDOH电源不合格时是否自动关机控制位。
                                                                  0：自动关机；
                                                                  1：不自动关机。
                                                                  注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  reserved                : 3;  /* bit[5-7]: 保留。 */
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
#define PMIC_SYS_CTRL0_vin_ldoh_vld_pd_mask_START     (4)
#define PMIC_SYS_CTRL0_vin_ldoh_vld_pd_mask_END       (4)


/*****************************************************************************
 结构名    : PMIC_SMPL_CTRL_UNION
 结构说明  : SMPL_CTRL 寄存器结构定义。地址偏移量:0x160，初值:0x00，宽度:8
 寄存器说明: SMPL控制寄存器。
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
        unsigned char  reserved         : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_SMPL_CTRL_UNION;
#endif
#define PMIC_SMPL_CTRL_np_smpl_open_en_START   (0)
#define PMIC_SMPL_CTRL_np_smpl_open_en_END     (0)
#define PMIC_SMPL_CTRL_np_smpl_time_sel_START  (1)
#define PMIC_SMPL_CTRL_np_smpl_time_sel_END    (2)


/*****************************************************************************
 结构名    : PMIC_SYS_CTRL1_UNION
 结构说明  : SYS_CTRL1 寄存器结构定义。地址偏移量:0x161，初值:0x02，宽度:8
 寄存器说明: 系统控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_pwron_8s_sel   : 1;  /* bit[0]  : 开机状态下按下pwron_n长达8s关机或者重启选择。
                                                            0：长按键重启；
                                                            1：长按键关机。 */
        unsigned char  np_pwron_time_sel : 2;  /* bit[1-2]: 长按键生效时间配置寄存器。
                                                            00:7s；
                                                            01:8s；
                                                            10:9s；
                                                            11:10s。 */
        unsigned char  reserved          : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_SYS_CTRL1_UNION;
#endif
#define PMIC_SYS_CTRL1_np_pwron_8s_sel_START    (0)
#define PMIC_SYS_CTRL1_np_pwron_8s_sel_END      (0)
#define PMIC_SYS_CTRL1_np_pwron_time_sel_START  (1)
#define PMIC_SYS_CTRL1_np_pwron_time_sel_END    (2)


/*****************************************************************************
 结构名    : PMIC_SIM_CTRL_UNION
 结构说明  : SIM_CTRL 寄存器结构定义。地址偏移量:0x162，初值:0x00，宽度:8
 寄存器说明: SIM控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sim0_hpd_r_pd_en : 1;  /* bit[0]  : 发生sim0_hpd上升沿中断时是否关闭LDO11控制位。
                                                           0：不关闭LDO11；
                                                           1：关闭LDO11。 */
        unsigned char  sim0_hpd_f_pd_en : 1;  /* bit[1]  : 发生sim0_hpd下降沿中断时是否关闭LDO11控制位。
                                                           0：不关闭LDO11；
                                                           1：关闭LDO11。 */
        unsigned char  sim1_hpd_r_pd_en : 1;  /* bit[2]  : 发生sim1_hpd上升沿中断时是否关闭LDO12控制位。
                                                           0：不关闭LDO12；
                                                           1：关闭LDO12。 */
        unsigned char  sim1_hpd_f_pd_en : 1;  /* bit[3]  : 发生sim1_hpd下降沿中断时是否关闭LDO12控制位。
                                                           0：不关闭LDO12；
                                                           1：关闭LDO12。 */
        unsigned char  reserved         : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_SIM_CTRL_UNION;
#endif
#define PMIC_SIM_CTRL_sim0_hpd_r_pd_en_START  (0)
#define PMIC_SIM_CTRL_sim0_hpd_r_pd_en_END    (0)
#define PMIC_SIM_CTRL_sim0_hpd_f_pd_en_START  (1)
#define PMIC_SIM_CTRL_sim0_hpd_f_pd_en_END    (1)
#define PMIC_SIM_CTRL_sim1_hpd_r_pd_en_START  (2)
#define PMIC_SIM_CTRL_sim1_hpd_r_pd_en_END    (2)
#define PMIC_SIM_CTRL_sim1_hpd_f_pd_en_START  (3)
#define PMIC_SIM_CTRL_sim1_hpd_f_pd_en_END    (3)


/*****************************************************************************
 结构名    : PMIC_SIM_DEB_CTRL_UNION
 结构说明  : SIM_DEB_CTRL 寄存器结构定义。地址偏移量:0x163，初值:0x27，宽度:8
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
 结构名    : PMIC_AUX0_IBIAS_CFG_UNION
 结构说明  : AUX0_IBIAS_CFG 寄存器结构定义。地址偏移量:0x164，初值:0x0A，宽度:8
 寄存器说明: DAC0 IBIAS配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  aux0_offset_cfg : 2;  /* bit[0-1]: AUXDAC0 OFFSET调节。
                                                          00：+7.5mV；
                                                          01：0mV；
                                                          10：0mV；
                                                          11：-7.5mV。 */
        unsigned char  aux0_ibias_cfg  : 2;  /* bit[2-3]: AUXDAC0偏置电流调节。
                                                          00：2.5uA；
                                                          01：5.0uA；
                                                          10：5.0uA；
                                                          11：7.5uA。 */
        unsigned char  reserved        : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_AUX0_IBIAS_CFG_UNION;
#endif
#define PMIC_AUX0_IBIAS_CFG_aux0_offset_cfg_START  (0)
#define PMIC_AUX0_IBIAS_CFG_aux0_offset_cfg_END    (1)
#define PMIC_AUX0_IBIAS_CFG_aux0_ibias_cfg_START   (2)
#define PMIC_AUX0_IBIAS_CFG_aux0_ibias_cfg_END     (3)


/*****************************************************************************
 结构名    : PMIC_AUX1_IBIAS_CFG_UNION
 结构说明  : AUX1_IBIAS_CFG 寄存器结构定义。地址偏移量:0x165，初值:0x0A，宽度:8
 寄存器说明: DAC1 IBIAS配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  aux1_offset_cfg : 2;  /* bit[0-1]: AUXDAC1 OFFSET调节。
                                                          00：+7.5mV；
                                                          01：0mV；
                                                          10：0mV；
                                                          11：-7.5mV。 */
        unsigned char  aux1_ibias_cfg  : 2;  /* bit[2-3]: AUXDAC1偏置电流调节。
                                                          00：2.5uA；
                                                          01：5.0uA；
                                                          10：5.0uA；
                                                          11：7.5uA。 */
        unsigned char  reserved        : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_AUX1_IBIAS_CFG_UNION;
#endif
#define PMIC_AUX1_IBIAS_CFG_aux1_offset_cfg_START  (0)
#define PMIC_AUX1_IBIAS_CFG_aux1_offset_cfg_END    (1)
#define PMIC_AUX1_IBIAS_CFG_aux1_ibias_cfg_START   (2)
#define PMIC_AUX1_IBIAS_CFG_aux1_ibias_cfg_END     (3)


/*****************************************************************************
 结构名    : PMIC_OTP0_0_UNION
 结构说明  : OTP0_0 寄存器结构定义。地址偏移量:0x16A，初值:0x00，宽度:8
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
 结构说明  : OTP0_1 寄存器结构定义。地址偏移量:0x16B，初值:0x00，宽度:8
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
 结构说明  : OTP0_2 寄存器结构定义。地址偏移量:0x16C，初值:0x00，宽度:8
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
 结构说明  : OTP0_3 寄存器结构定义。地址偏移量:0x16D，初值:0x00，宽度:8
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
 结构说明  : OTP0_CTRL_0 寄存器结构定义。地址偏移量:0x16E，初值:0x00，宽度:8
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
 结构说明  : OTP0_CTRL_1 寄存器结构定义。地址偏移量:0x16F，初值:0x00，宽度:8
 寄存器说明: OTP0控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp0_pa      : 2;  /* bit[0-1]: OTP0的地址信号。
                                                       00：选择otp0器件的bit[7:0]进行读/写操作；
                                                       01：选择otp0器件的bit[15:8]进行读/写操作；
                                                       10：选择otp0器件的bit[23:16]进行读/写操作；
                                                       11：选择otp0器件的bit[31:24]进行读/写操作。 */
        unsigned char  otp0_ptm     : 2;  /* bit[2-3]: OTP0测试模式使能信号。
                                                       00：用户模式；
                                                       01：margin-2读模式；
                                                       10：margin-1读模式；
                                                       11：未定义。 */
        unsigned char  otp012_pprog : 1;  /* bit[4]  : OTP012编程模式使能信号。
                                                       0：关闭otp编程；
                                                       1：使能otp编程。 */
        unsigned char  reserved     : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_OTP0_CTRL_1_UNION;
#endif
#define PMIC_OTP0_CTRL_1_otp0_pa_START       (0)
#define PMIC_OTP0_CTRL_1_otp0_pa_END         (1)
#define PMIC_OTP0_CTRL_1_otp0_ptm_START      (2)
#define PMIC_OTP0_CTRL_1_otp0_ptm_END        (3)
#define PMIC_OTP0_CTRL_1_otp012_pprog_START  (4)
#define PMIC_OTP0_CTRL_1_otp012_pprog_END    (4)


/*****************************************************************************
 结构名    : PMIC_OTP0_WDATA_UNION
 结构说明  : OTP0_WDATA 寄存器结构定义。地址偏移量:0x170，初值:0x00，宽度:8
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
 结构说明  : OTP0_0_W 寄存器结构定义。地址偏移量:0x171，初值:0x00，宽度:8
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
 结构说明  : OTP0_1_W 寄存器结构定义。地址偏移量:0x172，初值:0x00，宽度:8
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
 结构说明  : OTP0_2_W 寄存器结构定义。地址偏移量:0x173，初值:0x00，宽度:8
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
 结构说明  : OTP0_3_W 寄存器结构定义。地址偏移量:0x174，初值:0x00，宽度:8
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
 结构说明  : OTP1_0 寄存器结构定义。地址偏移量:0x175，初值:0x00，宽度:8
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
 结构说明  : OTP1_1 寄存器结构定义。地址偏移量:0x176，初值:0x00，宽度:8
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
 结构说明  : OTP1_2 寄存器结构定义。地址偏移量:0x177，初值:0x00，宽度:8
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
 结构说明  : OTP1_3 寄存器结构定义。地址偏移量:0x178，初值:0x00，宽度:8
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
 结构说明  : OTP1_CTRL_0 寄存器结构定义。地址偏移量:0x179，初值:0x00，宽度:8
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
 结构说明  : OTP1_CTRL_1 寄存器结构定义。地址偏移量:0x17A，初值:0x00，宽度:8
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
 结构说明  : OTP1_WDATA 寄存器结构定义。地址偏移量:0x17B，初值:0x00，宽度:8
 寄存器说明: OTP1写操作数据寄存器。
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
 结构说明  : OTP1_0_W 寄存器结构定义。地址偏移量:0x17C，初值:0x00，宽度:8
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
 结构说明  : OTP1_1_W 寄存器结构定义。地址偏移量:0x17D，初值:0x00，宽度:8
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
 结构说明  : OTP1_2_W 寄存器结构定义。地址偏移量:0x17E，初值:0x00，宽度:8
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
 结构说明  : OTP1_3_W 寄存器结构定义。地址偏移量:0x17F，初值:0x00，宽度:8
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
 结构名    : PMIC_OTP2_0_UNION
 结构说明  : OTP2_0 寄存器结构定义。地址偏移量:0x180，初值:0x00，宽度:8
 寄存器说明: OTP2回读寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob0 : 8;  /* bit[0-7]: OTP2回读值bit[7:0]。 */
    } reg;
} PMIC_OTP2_0_UNION;
#endif
#define PMIC_OTP2_0_otp2_pdob0_START  (0)
#define PMIC_OTP2_0_otp2_pdob0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP2_1_UNION
 结构说明  : OTP2_1 寄存器结构定义。地址偏移量:0x181，初值:0x00，宽度:8
 寄存器说明: OTP2回读寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob1 : 8;  /* bit[0-7]: OTP2回读值bit[15:8]。 */
    } reg;
} PMIC_OTP2_1_UNION;
#endif
#define PMIC_OTP2_1_otp2_pdob1_START  (0)
#define PMIC_OTP2_1_otp2_pdob1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP2_2_UNION
 结构说明  : OTP2_2 寄存器结构定义。地址偏移量:0x182，初值:0x00，宽度:8
 寄存器说明: OTP2回读寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob2 : 8;  /* bit[0-7]: OTP2回读值bit[23:16]。 */
    } reg;
} PMIC_OTP2_2_UNION;
#endif
#define PMIC_OTP2_2_otp2_pdob2_START  (0)
#define PMIC_OTP2_2_otp2_pdob2_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP2_3_UNION
 结构说明  : OTP2_3 寄存器结构定义。地址偏移量:0x183，初值:0x00，宽度:8
 寄存器说明: OTP2回读寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob3 : 8;  /* bit[0-7]: OTP2回读值bit[31:24]。 */
    } reg;
} PMIC_OTP2_3_UNION;
#endif
#define PMIC_OTP2_3_otp2_pdob3_START  (0)
#define PMIC_OTP2_3_otp2_pdob3_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP2_CTRL_0_UNION
 结构说明  : OTP2_CTRL_0 寄存器结构定义。地址偏移量:0x184，初值:0x00，宽度:8
 寄存器说明: OTP2控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pwe_int   : 1;  /* bit[0]  : OTP2写控制信号。
                                                         0：拉低otp_pwe，结束写操作；
                                                         1：拉高otp_pwe，发起写操作。
                                                         需保证otp_pwe的高电平持续时间满足otp器件的要求。 */
        unsigned char  otp2_pwe_pulse : 1;  /* bit[1]  : OTP2写脉冲控制。
                                                         0：不发起脉冲；
                                                         1：发起一个310us的高电平脉冲。 */
        unsigned char  otp2_por_int   : 1;  /* bit[2]  : OTP2读控制信号。
                                                         0：拉低otp_por，结束读操作；
                                                         1：拉高otp_por，发起读操作。
                                                         需保证otp_por的高电平持续时间满足otp器件的要求。 */
        unsigned char  otp2_por_pulse : 1;  /* bit[3]  : OTP2初始化控制信号。
                                                         0： 不发起脉冲；
                                                         1：发起一个30us的por高电平脉冲。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_OTP2_CTRL_0_UNION;
#endif
#define PMIC_OTP2_CTRL_0_otp2_pwe_int_START    (0)
#define PMIC_OTP2_CTRL_0_otp2_pwe_int_END      (0)
#define PMIC_OTP2_CTRL_0_otp2_pwe_pulse_START  (1)
#define PMIC_OTP2_CTRL_0_otp2_pwe_pulse_END    (1)
#define PMIC_OTP2_CTRL_0_otp2_por_int_START    (2)
#define PMIC_OTP2_CTRL_0_otp2_por_int_END      (2)
#define PMIC_OTP2_CTRL_0_otp2_por_pulse_START  (3)
#define PMIC_OTP2_CTRL_0_otp2_por_pulse_END    (3)


/*****************************************************************************
 结构名    : PMIC_OTP2_CTRL_1_UNION
 结构说明  : OTP2_CTRL_1 寄存器结构定义。地址偏移量:0x185，初值:0x00，宽度:8
 寄存器说明: OTP2控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pa  : 2;  /* bit[0-1]: OTP2的地址信号。
                                                   00：选择otp1器件的bit[7：0]进行读/写操作；
                                                   01：选择otp1器件的bit[15：8]进行读/写操作；
                                                   10：选择otp1器件的bit[23：16]进行读/写操作；
                                                   11：选择otp1器件的bit[31：24]进行读/写操作。 */
        unsigned char  otp2_ptm : 2;  /* bit[2-3]: OTP2测试模式使能信号。
                                                   00：用户模式；
                                                   01：margin-2读模式；
                                                   10：margin-1读模式；
                                                   11：未定义。 */
        unsigned char  reserved : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_OTP2_CTRL_1_UNION;
#endif
#define PMIC_OTP2_CTRL_1_otp2_pa_START   (0)
#define PMIC_OTP2_CTRL_1_otp2_pa_END     (1)
#define PMIC_OTP2_CTRL_1_otp2_ptm_START  (2)
#define PMIC_OTP2_CTRL_1_otp2_ptm_END    (3)


/*****************************************************************************
 结构名    : PMIC_OTP2_WDATA_UNION
 结构说明  : OTP2_WDATA 寄存器结构定义。地址偏移量:0x186，初值:0x00，宽度:8
 寄存器说明: OTP2写操作数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdin : 8;  /* bit[0-7]: OTP2的输入值寄存器。 */
    } reg;
} PMIC_OTP2_WDATA_UNION;
#endif
#define PMIC_OTP2_WDATA_otp2_pdin_START  (0)
#define PMIC_OTP2_WDATA_otp2_pdin_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP2_0_W_UNION
 结构说明  : OTP2_0_W 寄存器结构定义。地址偏移量:0x187，初值:0x00，宽度:8
 寄存器说明: OTP2或操作寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob0_w : 8;  /* bit[0-7]: 与OTP2_0相或后送给模拟。 */
    } reg;
} PMIC_OTP2_0_W_UNION;
#endif
#define PMIC_OTP2_0_W_otp2_pdob0_w_START  (0)
#define PMIC_OTP2_0_W_otp2_pdob0_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP2_1_W_UNION
 结构说明  : OTP2_1_W 寄存器结构定义。地址偏移量:0x188，初值:0x00，宽度:8
 寄存器说明: OTP2或操作寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob1_w : 8;  /* bit[0-7]: 与OTP2_1相或后送给模拟。 */
    } reg;
} PMIC_OTP2_1_W_UNION;
#endif
#define PMIC_OTP2_1_W_otp2_pdob1_w_START  (0)
#define PMIC_OTP2_1_W_otp2_pdob1_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP2_2_W_UNION
 结构说明  : OTP2_2_W 寄存器结构定义。地址偏移量:0x189，初值:0x00，宽度:8
 寄存器说明: OTP2或操作寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob2_w : 8;  /* bit[0-7]: 与OTP2_2相或后送给模拟。 */
    } reg;
} PMIC_OTP2_2_W_UNION;
#endif
#define PMIC_OTP2_2_W_otp2_pdob2_w_START  (0)
#define PMIC_OTP2_2_W_otp2_pdob2_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_OTP2_3_W_UNION
 结构说明  : OTP2_3_W 寄存器结构定义。地址偏移量:0x18A，初值:0x00，宽度:8
 寄存器说明: OTP2或操作寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otp2_pdob3_w : 8;  /* bit[0-7]: 与OTP2_3相或后送给模拟。 */
    } reg;
} PMIC_OTP2_3_W_UNION;
#endif
#define PMIC_OTP2_3_W_otp2_pdob3_w_START  (0)
#define PMIC_OTP2_3_W_otp2_pdob3_w_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG0_UNION
 结构说明  : HRST_REG0 寄存器结构定义。地址偏移量:0x18B，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg0 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG0_UNION;
#endif
#define PMIC_HRST_REG0_np_hrst_reg0_START  (0)
#define PMIC_HRST_REG0_np_hrst_reg0_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG1_UNION
 结构说明  : HRST_REG1 寄存器结构定义。地址偏移量:0x18C，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg1 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG1_UNION;
#endif
#define PMIC_HRST_REG1_np_hrst_reg1_START  (0)
#define PMIC_HRST_REG1_np_hrst_reg1_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG2_UNION
 结构说明  : HRST_REG2 寄存器结构定义。地址偏移量:0x18D，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg2 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG2_UNION;
#endif
#define PMIC_HRST_REG2_np_hrst_reg2_START  (0)
#define PMIC_HRST_REG2_np_hrst_reg2_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG3_UNION
 结构说明  : HRST_REG3 寄存器结构定义。地址偏移量:0x18E，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg3 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG3_UNION;
#endif
#define PMIC_HRST_REG3_np_hrst_reg3_START  (0)
#define PMIC_HRST_REG3_np_hrst_reg3_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG4_UNION
 结构说明  : HRST_REG4 寄存器结构定义。地址偏移量:0x18F，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg4 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG4_UNION;
#endif
#define PMIC_HRST_REG4_np_hrst_reg4_START  (0)
#define PMIC_HRST_REG4_np_hrst_reg4_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG5_UNION
 结构说明  : HRST_REG5 寄存器结构定义。地址偏移量:0x190，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg5 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG5_UNION;
#endif
#define PMIC_HRST_REG5_np_hrst_reg5_START  (0)
#define PMIC_HRST_REG5_np_hrst_reg5_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG6_UNION
 结构说明  : HRST_REG6 寄存器结构定义。地址偏移量:0x191，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg6 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG6_UNION;
#endif
#define PMIC_HRST_REG6_np_hrst_reg6_START  (0)
#define PMIC_HRST_REG6_np_hrst_reg6_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG7_UNION
 结构说明  : HRST_REG7 寄存器结构定义。地址偏移量:0x192，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg7 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG7_UNION;
#endif
#define PMIC_HRST_REG7_np_hrst_reg7_START  (0)
#define PMIC_HRST_REG7_np_hrst_reg7_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG8_UNION
 结构说明  : HRST_REG8 寄存器结构定义。地址偏移量:0x193，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg8 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG8_UNION;
#endif
#define PMIC_HRST_REG8_np_hrst_reg8_START  (0)
#define PMIC_HRST_REG8_np_hrst_reg8_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG9_UNION
 结构说明  : HRST_REG9 寄存器结构定义。地址偏移量:0x194，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg9 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG9_UNION;
#endif
#define PMIC_HRST_REG9_np_hrst_reg9_START  (0)
#define PMIC_HRST_REG9_np_hrst_reg9_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG10_UNION
 结构说明  : HRST_REG10 寄存器结构定义。地址偏移量:0x195，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg10 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG10_UNION;
#endif
#define PMIC_HRST_REG10_np_hrst_reg10_START  (0)
#define PMIC_HRST_REG10_np_hrst_reg10_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG11_UNION
 结构说明  : HRST_REG11 寄存器结构定义。地址偏移量:0x196，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg11 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG11_UNION;
#endif
#define PMIC_HRST_REG11_np_hrst_reg11_START  (0)
#define PMIC_HRST_REG11_np_hrst_reg11_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG12_UNION
 结构说明  : HRST_REG12 寄存器结构定义。地址偏移量:0x197，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器12。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg12 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG12_UNION;
#endif
#define PMIC_HRST_REG12_np_hrst_reg12_START  (0)
#define PMIC_HRST_REG12_np_hrst_reg12_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG13_UNION
 结构说明  : HRST_REG13 寄存器结构定义。地址偏移量:0x198，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器13。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg13 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG13_UNION;
#endif
#define PMIC_HRST_REG13_np_hrst_reg13_START  (0)
#define PMIC_HRST_REG13_np_hrst_reg13_END    (7)


/*****************************************************************************
 结构名    : PMIC_HRST_REG14_UNION
 结构说明  : HRST_REG14 寄存器结构定义。地址偏移量:0x199，初值:0x00，宽度:8
 寄存器说明: 软件预留寄存器14。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_hrst_reg14 : 8;  /* bit[0-7]: 写入值，不会被下电状态机复位；读返回上次写入值，作为热复位前信息记录寄存器。 */
    } reg;
} PMIC_HRST_REG14_UNION;
#endif
#define PMIC_HRST_REG14_np_hrst_reg14_START  (0)
#define PMIC_HRST_REG14_np_hrst_reg14_END    (7)


/*****************************************************************************
 结构名    : PMIC_DEBUG_CTRL_UNION
 结构说明  : DEBUG_CTRL 寄存器结构定义。地址偏移量:0x19A，初值:0x00，宽度:8
 寄存器说明: DEBUG寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_reg_rc_debug : 1;  /* bit[0]  : RC时钟debug使能信号。
                                                          0：正常使用；
                                                          1：将256K时钟引出。
                                                          注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
        unsigned char  reserved        : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_DEBUG_CTRL_UNION;
#endif
#define PMIC_DEBUG_CTRL_np_reg_rc_debug_START  (0)
#define PMIC_DEBUG_CTRL_np_reg_rc_debug_END    (0)


/*****************************************************************************
 结构名    : PMIC_SYS_DEBUG0_UNION
 结构说明  : SYS_DEBUG0 寄存器结构定义。地址偏移量:0x19B，初值:0x00，宽度:8
 寄存器说明: 数字系统debug预留寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_debug0 : 8;  /* bit[0-7]: 数字系统debug预留寄存器。
                                                     注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
    } reg;
} PMIC_SYS_DEBUG0_UNION;
#endif
#define PMIC_SYS_DEBUG0_sys_debug0_START  (0)
#define PMIC_SYS_DEBUG0_sys_debug0_END    (7)


/*****************************************************************************
 结构名    : PMIC_SYS_DEBUG1_UNION
 结构说明  : SYS_DEBUG1 寄存器结构定义。地址偏移量:0x19C，初值:0x00，宽度:8
 寄存器说明: 数字系统debug预留寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_debug1 : 8;  /* bit[0-7]: 数字系统debug预留寄存器。
                                                     注：寄存器需要将寄存器DEBUG_LOCK配置为8'h6C，此寄存器才能配置生效。读不受限。 */
    } reg;
} PMIC_SYS_DEBUG1_UNION;
#endif
#define PMIC_SYS_DEBUG1_sys_debug1_START  (0)
#define PMIC_SYS_DEBUG1_sys_debug1_END    (7)


/*****************************************************************************
 结构名    : PMIC_DEBUG_LOCK_UNION
 结构说明  : DEBUG_LOCK 寄存器结构定义。地址偏移量:0x19D，初值:0x00，宽度:8
 寄存器说明: debug寄存器写屏蔽控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  debug_lock : 8;  /* bit[0-7]: 为防止软件误写SYS_CTRL0，DEBUG_CTRL，SYS_DEBUG0/1，导致系统出错。只有当debug_lock写为8'h6C的时候，上述3个寄存器才允许被一直写入。 */
    } reg;
} PMIC_DEBUG_LOCK_UNION;
#endif
#define PMIC_DEBUG_LOCK_debug_lock_START  (0)
#define PMIC_DEBUG_LOCK_debug_lock_END    (7)


/*****************************************************************************
 结构名    : PMIC_DAC0_DIN_MSB_UNION
 结构说明  : DAC0_DIN_MSB 寄存器结构定义。地址偏移量:0x19F，初值:0x00，宽度:8
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
 结构说明  : DAC0_DIN_LSB 寄存器结构定义。地址偏移量:0x1A0，初值:0x00，宽度:8
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
 结构说明  : DAC1_DIN_MSB 寄存器结构定义。地址偏移量:0x1A1，初值:0x00，宽度:8
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
 结构说明  : DAC1_DIN_LSB 寄存器结构定义。地址偏移量:0x1A2，初值:0x00，宽度:8
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




/****************************************************************************
                     (2/5) PMU_IRQ
 ****************************************************************************/
/*****************************************************************************
 结构名    : PMIC_IRQ0_UNION
 结构说明  : IRQ0 寄存器结构定义。地址偏移量:0x1B0，初值:0x00，宽度:8
 寄存器说明: 中断寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  thsd_otmp125_d1mr     : 1;  /* bit[0]: 过温（芯片温度超过设定的报警温度）事件中断(上升沿去抖1ms)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  vbus_det_insert_d20mr : 1;  /* bit[1]: 开机状态下，充电器插入中断(上升沿去抖20ms)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  vbus_det_insert_d20mf : 1;  /* bit[2]: 开机状态下，充电器拔出中断(下降沿去抖20ms)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  alarmon_r             : 1;  /* bit[3]: 开机状态下，闹钟中断。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  pwronn_d6sf           : 1;  /* bit[4]: 开机状态下，按键按下超过6s事件中断(下降沿去抖6s)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  pwronn_d1sf           : 1;  /* bit[5]: 开机状态下，按键按下超过1s事件中断(下降沿去抖1s)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  pwronn_d20mr          : 1;  /* bit[6]: 开机状态下，按键释放事件中断(上升沿去抖20ms)。
                                                              0：无中断；
                                                              1：有中断。 */
        unsigned char  pwronn_d20mf          : 1;  /* bit[7]: 开机状态下，按键按下事件中断(下降沿去抖20ms)。
                                                              0：无中断；
                                                              1：有中断。 */
    } reg;
} PMIC_IRQ0_UNION;
#endif
#define PMIC_IRQ0_thsd_otmp125_d1mr_START      (0)
#define PMIC_IRQ0_thsd_otmp125_d1mr_END        (0)
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
 结构说明  : IRQ1 寄存器结构定义。地址偏移量:0x1B1，初值:0x00，宽度:8
 寄存器说明: 中断寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocp_scp_r  : 1;  /* bit[0]  : OCP/SCP总中断
                                                     0:无此中断；
                                                     1:表示至少有一个BUCK发生过流保护或者短路保护，或者CLASSD/LDO发生过流保护，CPU查询到后要去查看下面的过流保存寄存器查看是哪一个发生过流，并将其写1清后，中断消除。 */
        unsigned char  coul_r     : 1;  /* bit[1]  : 库仑计事件中断。
                                                     0：无中断；
                                                     1：有中断。PMU接到以后要去查看下面的库仑计中断寄存器确认是哪一个中断。 */
        unsigned char  sim0_hpd_r : 1;  /* bit[2]  : sim0_hpd上升沿中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  sim0_hpd_f : 1;  /* bit[3]  : sim0_hpd下降沿中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  sim1_hpd_r : 1;  /* bit[4]  : sim1_hpd上升沿中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  sim1_hpd_f : 1;  /* bit[5]  : sim1_hpd下降沿中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  reserved   : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_IRQ1_UNION;
#endif
#define PMIC_IRQ1_ocp_scp_r_START   (0)
#define PMIC_IRQ1_ocp_scp_r_END     (0)
#define PMIC_IRQ1_coul_r_START      (1)
#define PMIC_IRQ1_coul_r_END        (1)
#define PMIC_IRQ1_sim0_hpd_r_START  (2)
#define PMIC_IRQ1_sim0_hpd_r_END    (2)
#define PMIC_IRQ1_sim0_hpd_f_START  (3)
#define PMIC_IRQ1_sim0_hpd_f_END    (3)
#define PMIC_IRQ1_sim1_hpd_r_START  (4)
#define PMIC_IRQ1_sim1_hpd_r_END    (4)
#define PMIC_IRQ1_sim1_hpd_f_START  (5)
#define PMIC_IRQ1_sim1_hpd_f_END    (5)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ0_UNION
 结构说明  : OCP_IRQ0 寄存器结构定义。地址偏移量:0x1B2，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo3   : 1;  /* bit[0]: LDO3输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpldo2   : 1;  /* bit[1]: LDO2输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpldo1   : 1;  /* bit[2]: LDO1输出过载中断。
                                                  0：无中断；
                                                  1：有中断。 */
        unsigned char  ocpldo0_2 : 1;  /* bit[3]: LDO0_2输出过载中断。
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
#define PMIC_OCP_IRQ0_ocpldo3_START    (0)
#define PMIC_OCP_IRQ0_ocpldo3_END      (0)
#define PMIC_OCP_IRQ0_ocpldo2_START    (1)
#define PMIC_OCP_IRQ0_ocpldo2_END      (1)
#define PMIC_OCP_IRQ0_ocpldo1_START    (2)
#define PMIC_OCP_IRQ0_ocpldo1_END      (2)
#define PMIC_OCP_IRQ0_ocpldo0_2_START  (3)
#define PMIC_OCP_IRQ0_ocpldo0_2_END    (3)
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
 结构说明  : OCP_IRQ1 寄存器结构定义。地址偏移量:0x1B3，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo12 : 1;  /* bit[0]: LDO12输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo11 : 1;  /* bit[1]: LDO11输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo10 : 1;  /* bit[2]: LDO10输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo9  : 1;  /* bit[3]: LDO9输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo8  : 1;  /* bit[4]: LDO8输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo7  : 1;  /* bit[5]: LDO7输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo5  : 1;  /* bit[6]: LDO5输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo4  : 1;  /* bit[7]: LDO4输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
    } reg;
} PMIC_OCP_IRQ1_UNION;
#endif
#define PMIC_OCP_IRQ1_ocpldo12_START  (0)
#define PMIC_OCP_IRQ1_ocpldo12_END    (0)
#define PMIC_OCP_IRQ1_ocpldo11_START  (1)
#define PMIC_OCP_IRQ1_ocpldo11_END    (1)
#define PMIC_OCP_IRQ1_ocpldo10_START  (2)
#define PMIC_OCP_IRQ1_ocpldo10_END    (2)
#define PMIC_OCP_IRQ1_ocpldo9_START   (3)
#define PMIC_OCP_IRQ1_ocpldo9_END     (3)
#define PMIC_OCP_IRQ1_ocpldo8_START   (4)
#define PMIC_OCP_IRQ1_ocpldo8_END     (4)
#define PMIC_OCP_IRQ1_ocpldo7_START   (5)
#define PMIC_OCP_IRQ1_ocpldo7_END     (5)
#define PMIC_OCP_IRQ1_ocpldo5_START   (6)
#define PMIC_OCP_IRQ1_ocpldo5_END     (6)
#define PMIC_OCP_IRQ1_ocpldo4_START   (7)
#define PMIC_OCP_IRQ1_ocpldo4_END     (7)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ2_UNION
 结构说明  : OCP_IRQ2 寄存器结构定义。地址偏移量:0x1B4，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo21 : 1;  /* bit[0]: LDO21输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo20 : 1;  /* bit[1]: LDO20输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo19 : 1;  /* bit[2]: LDO19输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo17 : 1;  /* bit[3]: LDO17输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo16 : 1;  /* bit[4]: LDO16输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo15 : 1;  /* bit[5]: LDO15输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo14 : 1;  /* bit[6]: LDO14输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo13 : 1;  /* bit[7]: LDO13输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
    } reg;
} PMIC_OCP_IRQ2_UNION;
#endif
#define PMIC_OCP_IRQ2_ocpldo21_START  (0)
#define PMIC_OCP_IRQ2_ocpldo21_END    (0)
#define PMIC_OCP_IRQ2_ocpldo20_START  (1)
#define PMIC_OCP_IRQ2_ocpldo20_END    (1)
#define PMIC_OCP_IRQ2_ocpldo19_START  (2)
#define PMIC_OCP_IRQ2_ocpldo19_END    (2)
#define PMIC_OCP_IRQ2_ocpldo17_START  (3)
#define PMIC_OCP_IRQ2_ocpldo17_END    (3)
#define PMIC_OCP_IRQ2_ocpldo16_START  (4)
#define PMIC_OCP_IRQ2_ocpldo16_END    (4)
#define PMIC_OCP_IRQ2_ocpldo15_START  (5)
#define PMIC_OCP_IRQ2_ocpldo15_END    (5)
#define PMIC_OCP_IRQ2_ocpldo14_START  (6)
#define PMIC_OCP_IRQ2_ocpldo14_END    (6)
#define PMIC_OCP_IRQ2_ocpldo13_START  (7)
#define PMIC_OCP_IRQ2_ocpldo13_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ3_UNION
 结构说明  : OCP_IRQ3 寄存器结构定义。地址偏移量:0x1B5，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ocpldo29 : 1;  /* bit[0]: LDO29输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo28 : 1;  /* bit[1]: LDO28输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo27 : 1;  /* bit[2]: LDO27输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo26 : 1;  /* bit[3]: LDO26输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo25 : 1;  /* bit[4]: LDO25输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo24 : 1;  /* bit[5]: LDO24输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo23 : 1;  /* bit[6]: LDO23输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
        unsigned char  ocpldo22 : 1;  /* bit[7]: LDO22输出过载中断。
                                                 0：无中断；
                                                 1：有中断。 */
    } reg;
} PMIC_OCP_IRQ3_UNION;
#endif
#define PMIC_OCP_IRQ3_ocpldo29_START  (0)
#define PMIC_OCP_IRQ3_ocpldo29_END    (0)
#define PMIC_OCP_IRQ3_ocpldo28_START  (1)
#define PMIC_OCP_IRQ3_ocpldo28_END    (1)
#define PMIC_OCP_IRQ3_ocpldo27_START  (2)
#define PMIC_OCP_IRQ3_ocpldo27_END    (2)
#define PMIC_OCP_IRQ3_ocpldo26_START  (3)
#define PMIC_OCP_IRQ3_ocpldo26_END    (3)
#define PMIC_OCP_IRQ3_ocpldo25_START  (4)
#define PMIC_OCP_IRQ3_ocpldo25_END    (4)
#define PMIC_OCP_IRQ3_ocpldo24_START  (5)
#define PMIC_OCP_IRQ3_ocpldo24_END    (5)
#define PMIC_OCP_IRQ3_ocpldo23_START  (6)
#define PMIC_OCP_IRQ3_ocpldo23_END    (6)
#define PMIC_OCP_IRQ3_ocpldo22_START  (7)
#define PMIC_OCP_IRQ3_ocpldo22_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ4_UNION
 结构说明  : OCP_IRQ4 寄存器结构定义。地址偏移量:0x1B6，初值:0x00，宽度:8
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
        unsigned char  ocpldo34   : 1;  /* bit[1]  : LDO34输出过载中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  ocpldo33   : 1;  /* bit[2]  : LDO33输出过载中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  ocpldo32   : 1;  /* bit[3]  : LDO32输出过载中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  ocpldo31   : 1;  /* bit[4]  : LDO31输出过载中断。
                                                     0：无中断；
                                                     1：有中断。 */
        unsigned char  reserved   : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_OCP_IRQ4_UNION;
#endif
#define PMIC_OCP_IRQ4_classd_ocp_START  (0)
#define PMIC_OCP_IRQ4_classd_ocp_END    (0)
#define PMIC_OCP_IRQ4_ocpldo34_START    (1)
#define PMIC_OCP_IRQ4_ocpldo34_END      (1)
#define PMIC_OCP_IRQ4_ocpldo33_START    (2)
#define PMIC_OCP_IRQ4_ocpldo33_END      (2)
#define PMIC_OCP_IRQ4_ocpldo32_START    (3)
#define PMIC_OCP_IRQ4_ocpldo32_END      (3)
#define PMIC_OCP_IRQ4_ocpldo31_START    (4)
#define PMIC_OCP_IRQ4_ocpldo31_END      (4)


/*****************************************************************************
 结构名    : PMIC_OCP_IRQ5_UNION
 结构说明  : OCP_IRQ5 寄存器结构定义。地址偏移量:0x1B7，初值:0x00，宽度:8
 寄存器说明: OCP中断寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck3_scp       : 1;  /* bit[0]  : BUCK3输出短路中断。
                                                          0：无中断；
                                                          1：有中断。 */
        unsigned char  buck2_scp       : 1;  /* bit[1]  : BUCK2输出短路中断。
                                                          0：无中断；
                                                          1：有中断。 */
        unsigned char  buck1_scp       : 1;  /* bit[2]  : BUCK1输出短路中断。
                                                          0：无中断；
                                                          1：有中断。 */
        unsigned char  buck0_scp       : 1;  /* bit[3]  : BUCK0输出短路中断。
                                                          0：无中断；
                                                          1：有中断。 */
        unsigned char  xo_ldo_buff_scp : 1;  /* bit[4]  : xo_ldo_buff输出短路中断。
                                                          0：无中断；
                                                          1：有中断。 */
        unsigned char  reserved        : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_OCP_IRQ5_UNION;
#endif
#define PMIC_OCP_IRQ5_buck3_scp_START        (0)
#define PMIC_OCP_IRQ5_buck3_scp_END          (0)
#define PMIC_OCP_IRQ5_buck2_scp_START        (1)
#define PMIC_OCP_IRQ5_buck2_scp_END          (1)
#define PMIC_OCP_IRQ5_buck1_scp_START        (2)
#define PMIC_OCP_IRQ5_buck1_scp_END          (2)
#define PMIC_OCP_IRQ5_buck0_scp_START        (3)
#define PMIC_OCP_IRQ5_buck0_scp_END          (3)
#define PMIC_OCP_IRQ5_xo_ldo_buff_scp_START  (4)
#define PMIC_OCP_IRQ5_xo_ldo_buff_scp_END    (4)


/*****************************************************************************
 结构名    : PMIC_NP_OCP0_UNION
 结构说明  : NP_OCP0 寄存器结构定义。地址偏移量:0x1B8，初值:0x00，宽度:8
 寄存器说明: BUKC0-3，LDO0-3 OCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo3   : 1;  /* bit[0]: LDO3输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpldo2   : 1;  /* bit[1]: LDO2输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpldo1   : 1;  /* bit[2]: LDO1输出过载事件记录寄存器。
                                                     0：没有发生过该事件；
                                                     1：发生过该事件。 */
        unsigned char  np_ocpldo0_2 : 1;  /* bit[3]: LDO0_2输出过载事件记录寄存器。
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
#define PMIC_NP_OCP0_np_ocpldo3_START    (0)
#define PMIC_NP_OCP0_np_ocpldo3_END      (0)
#define PMIC_NP_OCP0_np_ocpldo2_START    (1)
#define PMIC_NP_OCP0_np_ocpldo2_END      (1)
#define PMIC_NP_OCP0_np_ocpldo1_START    (2)
#define PMIC_NP_OCP0_np_ocpldo1_END      (2)
#define PMIC_NP_OCP0_np_ocpldo0_2_START  (3)
#define PMIC_NP_OCP0_np_ocpldo0_2_END    (3)
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
 结构说明  : NP_OCP1 寄存器结构定义。地址偏移量:0x1B9，初值:0x00，宽度:8
 寄存器说明: LDO4-12 OCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo12 : 1;  /* bit[0]: LDO12输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo11 : 1;  /* bit[1]: LDO11输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo10 : 1;  /* bit[2]: LDO10输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo9  : 1;  /* bit[3]: LDO9输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo8  : 1;  /* bit[4]: LDO8输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo7  : 1;  /* bit[5]: LDO7输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo5  : 1;  /* bit[6]: LDO5输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo4  : 1;  /* bit[7]: LDO3输出过载事件记录寄存器。
                                                    0：无中断；
                                                    1：有中断。 */
    } reg;
} PMIC_NP_OCP1_UNION;
#endif
#define PMIC_NP_OCP1_np_ocpldo12_START  (0)
#define PMIC_NP_OCP1_np_ocpldo12_END    (0)
#define PMIC_NP_OCP1_np_ocpldo11_START  (1)
#define PMIC_NP_OCP1_np_ocpldo11_END    (1)
#define PMIC_NP_OCP1_np_ocpldo10_START  (2)
#define PMIC_NP_OCP1_np_ocpldo10_END    (2)
#define PMIC_NP_OCP1_np_ocpldo9_START   (3)
#define PMIC_NP_OCP1_np_ocpldo9_END     (3)
#define PMIC_NP_OCP1_np_ocpldo8_START   (4)
#define PMIC_NP_OCP1_np_ocpldo8_END     (4)
#define PMIC_NP_OCP1_np_ocpldo7_START   (5)
#define PMIC_NP_OCP1_np_ocpldo7_END     (5)
#define PMIC_NP_OCP1_np_ocpldo5_START   (6)
#define PMIC_NP_OCP1_np_ocpldo5_END     (6)
#define PMIC_NP_OCP1_np_ocpldo4_START   (7)
#define PMIC_NP_OCP1_np_ocpldo4_END     (7)


/*****************************************************************************
 结构名    : PMIC_NP_OCP2_UNION
 结构说明  : NP_OCP2 寄存器结构定义。地址偏移量:0x1BA，初值:0x00，宽度:8
 寄存器说明: LDO12-20 OCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo21 : 1;  /* bit[0]: LDO21输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo20 : 1;  /* bit[1]: LDO20输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo19 : 1;  /* bit[2]: LDO19输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo17 : 1;  /* bit[3]: LDO17输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo16 : 1;  /* bit[4]: LDO16输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo15 : 1;  /* bit[5]: LDO15输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo14 : 1;  /* bit[6]: LDO14输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo13 : 1;  /* bit[7]: LDO13输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
    } reg;
} PMIC_NP_OCP2_UNION;
#endif
#define PMIC_NP_OCP2_np_ocpldo21_START  (0)
#define PMIC_NP_OCP2_np_ocpldo21_END    (0)
#define PMIC_NP_OCP2_np_ocpldo20_START  (1)
#define PMIC_NP_OCP2_np_ocpldo20_END    (1)
#define PMIC_NP_OCP2_np_ocpldo19_START  (2)
#define PMIC_NP_OCP2_np_ocpldo19_END    (2)
#define PMIC_NP_OCP2_np_ocpldo17_START  (3)
#define PMIC_NP_OCP2_np_ocpldo17_END    (3)
#define PMIC_NP_OCP2_np_ocpldo16_START  (4)
#define PMIC_NP_OCP2_np_ocpldo16_END    (4)
#define PMIC_NP_OCP2_np_ocpldo15_START  (5)
#define PMIC_NP_OCP2_np_ocpldo15_END    (5)
#define PMIC_NP_OCP2_np_ocpldo14_START  (6)
#define PMIC_NP_OCP2_np_ocpldo14_END    (6)
#define PMIC_NP_OCP2_np_ocpldo13_START  (7)
#define PMIC_NP_OCP2_np_ocpldo13_END    (7)


/*****************************************************************************
 结构名    : PMIC_NP_OCP3_UNION
 结构说明  : NP_OCP3 寄存器结构定义。地址偏移量:0x1BB，初值:0x00，宽度:8
 寄存器说明: LDO21-28 OCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_ocpldo29 : 1;  /* bit[0]: LDO29输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo28 : 1;  /* bit[1]: LDO28输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo27 : 1;  /* bit[2]: LDO27输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo26 : 1;  /* bit[3]: LDO26输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo25 : 1;  /* bit[4]: LDO25输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo24 : 1;  /* bit[5]: LDO24输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo23 : 1;  /* bit[6]: LDO23输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
        unsigned char  np_ocpldo22 : 1;  /* bit[7]: LDO22输出过载事件记录寄存器。
                                                    0：没有发生过该事件；
                                                    1：发生过该事件。 */
    } reg;
} PMIC_NP_OCP3_UNION;
#endif
#define PMIC_NP_OCP3_np_ocpldo29_START  (0)
#define PMIC_NP_OCP3_np_ocpldo29_END    (0)
#define PMIC_NP_OCP3_np_ocpldo28_START  (1)
#define PMIC_NP_OCP3_np_ocpldo28_END    (1)
#define PMIC_NP_OCP3_np_ocpldo27_START  (2)
#define PMIC_NP_OCP3_np_ocpldo27_END    (2)
#define PMIC_NP_OCP3_np_ocpldo26_START  (3)
#define PMIC_NP_OCP3_np_ocpldo26_END    (3)
#define PMIC_NP_OCP3_np_ocpldo25_START  (4)
#define PMIC_NP_OCP3_np_ocpldo25_END    (4)
#define PMIC_NP_OCP3_np_ocpldo24_START  (5)
#define PMIC_NP_OCP3_np_ocpldo24_END    (5)
#define PMIC_NP_OCP3_np_ocpldo23_START  (6)
#define PMIC_NP_OCP3_np_ocpldo23_END    (6)
#define PMIC_NP_OCP3_np_ocpldo22_START  (7)
#define PMIC_NP_OCP3_np_ocpldo22_END    (7)


/*****************************************************************************
 结构名    : PMIC_NP_OCP4_UNION
 结构说明  : NP_OCP4 寄存器结构定义。地址偏移量:0x1BC，初值:0x00，宽度:8
 寄存器说明: LDO31-34 CLASSD OCP事件记录寄存器。
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
        unsigned char  np_ocpldo34   : 1;  /* bit[1]  : LDO34输出过载事件记录寄存器。
                                                        0：没有发生过该事件；
                                                        1：发生过该事件。 */
        unsigned char  np_ocpldo33   : 1;  /* bit[2]  : LDO33输出过载事件记录寄存器。
                                                        0：没有发生过该事件；
                                                        1：发生过该事件。 */
        unsigned char  np_ocpldo32   : 1;  /* bit[3]  : LDO32输出过载事件记录寄存器。
                                                        0：没有发生过该事件；
                                                        1：发生过该事件。 */
        unsigned char  np_ocpldo31   : 1;  /* bit[4]  : LDO31输出过载事件记录寄存器。
                                                        0：没有发生过该事件；
                                                        1：发生过该事件。 */
        unsigned char  reserved      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_NP_OCP4_UNION;
#endif
#define PMIC_NP_OCP4_np_classd_ocp_START  (0)
#define PMIC_NP_OCP4_np_classd_ocp_END    (0)
#define PMIC_NP_OCP4_np_ocpldo34_START    (1)
#define PMIC_NP_OCP4_np_ocpldo34_END      (1)
#define PMIC_NP_OCP4_np_ocpldo33_START    (2)
#define PMIC_NP_OCP4_np_ocpldo33_END      (2)
#define PMIC_NP_OCP4_np_ocpldo32_START    (3)
#define PMIC_NP_OCP4_np_ocpldo32_END      (3)
#define PMIC_NP_OCP4_np_ocpldo31_START    (4)
#define PMIC_NP_OCP4_np_ocpldo31_END      (4)


/*****************************************************************************
 结构名    : PMIC_NP_SCP_UNION
 结构说明  : NP_SCP 寄存器结构定义。地址偏移量:0x1BD，初值:0x00，宽度:8
 寄存器说明: BUCK0-3 SCP事件记录寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_buck3_scp       : 1;  /* bit[0]  : BUCK3输出短路事件记录寄存器。
                                                             0：没有发生过该事件；
                                                             1：发生过该事件。 */
        unsigned char  np_buck2_scp       : 1;  /* bit[1]  : BUCK2输出短路事件记录寄存器。
                                                             0：没有发生过该事件；
                                                             1：发生过该事件。 */
        unsigned char  np_buck1_scp       : 1;  /* bit[2]  : BUCK1输出短路事件记录寄存器。
                                                             0：没有发生过该事件；
                                                             1：发生过该事件。 */
        unsigned char  np_buck0_scp       : 1;  /* bit[3]  : BUCK0输出短路事件记录寄存器。
                                                             0：没有发生过该事件；
                                                             1：发生过该事件。 */
        unsigned char  np_xo_ldo_buff_scp : 1;  /* bit[4]  : xo_ldo_buff输出短路事件记录寄存器。
                                                             0：没有发生过该事件；
                                                             1：发生过该事件。 */
        unsigned char  reserved           : 3;  /* bit[5-7]: 保留。 */
    } reg;
} PMIC_NP_SCP_UNION;
#endif
#define PMIC_NP_SCP_np_buck3_scp_START        (0)
#define PMIC_NP_SCP_np_buck3_scp_END          (0)
#define PMIC_NP_SCP_np_buck2_scp_START        (1)
#define PMIC_NP_SCP_np_buck2_scp_END          (1)
#define PMIC_NP_SCP_np_buck1_scp_START        (2)
#define PMIC_NP_SCP_np_buck1_scp_END          (2)
#define PMIC_NP_SCP_np_buck0_scp_START        (3)
#define PMIC_NP_SCP_np_buck0_scp_END          (3)
#define PMIC_NP_SCP_np_xo_ldo_buff_scp_START  (4)
#define PMIC_NP_SCP_np_xo_ldo_buff_scp_END    (4)


/*****************************************************************************
 结构名    : PMIC_NP_RECORD0_UNION
 结构说明  : NP_RECORD0 寄存器结构定义。地址偏移量:0x1BE，初值:0x00，宽度:8
 寄存器说明: 事件记录寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_vsys_ov_d200ur        : 1;  /* bit[0]: 过压事件(上升沿去抖200us)。
                                                                 0：没有发生过该事件；
                                                                 1：发生过该事件。 */
        unsigned char  np_vsys_pwroff_abs_2d    : 1;  /* bit[1]: 绝对欠压事件。
                                                                 0：没有发生过该事件；
                                                                 1：发生过该事件。 */
        unsigned char  np_vsys_pwroff_deb_d80mr : 1;  /* bit[2]: 去抖欠压事件(上升沿去抖80ms，时间可配)。
                                                                 0：没有发生过该事件；
                                                                 1：发生过该事件。 */
        unsigned char  np_thsd_otmp140_d1mr     : 1;  /* bit[3]: 过温140度事件(上升沿去抖1ms)。
                                                                 0：没有发生过该事件；
                                                                 1：发生过该事件。 */
        unsigned char  np_thsd_otmp125_d1mr     : 1;  /* bit[4]: 过温125度下电事件(上升沿去抖1ms)。
                                                                 0：没有发生过该事件；
                                                                 1：发生过该事件。 */
        unsigned char  np_hresetn_d90uf         : 1;  /* bit[5]: 热复位事件（包含下电和非下电热复位）。
                                                                 0：无热复位事件；
                                                                 1：有热复位事件。 */
        unsigned char  np_avdd_osc_vld_d20nf    : 1;  /* bit[6]: AVDD_OSC电源异常事件（下降沿去抖20ns）：
                                                                 0：没有发生过该事件；
                                                                 1：发生过该事件。 */
        unsigned char  np_19m2_dis              : 1;  /* bit[7]: 19.2M时钟异常消失事件：
                                                                 0：没有发生过该事件；
                                                                 1：发生过该事件。 */
    } reg;
} PMIC_NP_RECORD0_UNION;
#endif
#define PMIC_NP_RECORD0_np_vsys_ov_d200ur_START         (0)
#define PMIC_NP_RECORD0_np_vsys_ov_d200ur_END           (0)
#define PMIC_NP_RECORD0_np_vsys_pwroff_abs_2d_START     (1)
#define PMIC_NP_RECORD0_np_vsys_pwroff_abs_2d_END       (1)
#define PMIC_NP_RECORD0_np_vsys_pwroff_deb_d80mr_START  (2)
#define PMIC_NP_RECORD0_np_vsys_pwroff_deb_d80mr_END    (2)
#define PMIC_NP_RECORD0_np_thsd_otmp140_d1mr_START      (3)
#define PMIC_NP_RECORD0_np_thsd_otmp140_d1mr_END        (3)
#define PMIC_NP_RECORD0_np_thsd_otmp125_d1mr_START      (4)
#define PMIC_NP_RECORD0_np_thsd_otmp125_d1mr_END        (4)
#define PMIC_NP_RECORD0_np_hresetn_d90uf_START          (5)
#define PMIC_NP_RECORD0_np_hresetn_d90uf_END            (5)
#define PMIC_NP_RECORD0_np_avdd_osc_vld_d20nf_START     (6)
#define PMIC_NP_RECORD0_np_avdd_osc_vld_d20nf_END       (6)
#define PMIC_NP_RECORD0_np_19m2_dis_START               (7)
#define PMIC_NP_RECORD0_np_19m2_dis_END                 (7)


/*****************************************************************************
 结构名    : PMIC_NP_RECORD1_UNION
 结构说明  : NP_RECORD1 寄存器结构定义。地址偏移量:0x1BF，初值:0x00，宽度:8
 寄存器说明: 事件记录寄存器1。
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
} PMIC_NP_RECORD1_UNION;
#endif
#define PMIC_NP_RECORD1_np_pwronn_restart_START    (0)
#define PMIC_NP_RECORD1_np_pwronn_restart_END      (0)
#define PMIC_NP_RECORD1_np_pwrhold_shutdown_START  (1)
#define PMIC_NP_RECORD1_np_pwrhold_shutdown_END    (1)
#define PMIC_NP_RECORD1_np_pwronn_shutdown_START   (2)
#define PMIC_NP_RECORD1_np_pwronn_shutdown_END     (2)
#define PMIC_NP_RECORD1_np_pwrhold_pwrup_START     (3)
#define PMIC_NP_RECORD1_np_pwrhold_pwrup_END       (3)
#define PMIC_NP_RECORD1_np_alarmon_pwrup_START     (4)
#define PMIC_NP_RECORD1_np_alarmon_pwrup_END       (4)
#define PMIC_NP_RECORD1_np_vbus_pwrup_START        (5)
#define PMIC_NP_RECORD1_np_vbus_pwrup_END          (5)
#define PMIC_NP_RECORD1_np_pwronn_pwrup_START      (6)
#define PMIC_NP_RECORD1_np_pwronn_pwrup_END        (6)
#define PMIC_NP_RECORD1_np_fast_pwrup_START        (7)
#define PMIC_NP_RECORD1_np_fast_pwrup_END          (7)


/*****************************************************************************
 结构名    : PMIC_NP_RECORD2_UNION
 结构说明  : NP_RECORD2 寄存器结构定义。地址偏移量:0x1C0，初值:0x10，宽度:8
 寄存器说明: 事件记录寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_tcxo_clk_sel_r : 1;  /* bit[0]: 32K RC切换到32K Crystal OSC 时钟。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。  */
        unsigned char  np_tcxo_clk_sel_f : 1;  /* bit[1]: 32K Crystal OSC切换到32K RC 时钟。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。  */
        unsigned char  np_dcxo_clk_sel_r : 1;  /* bit[2]: 32K RC 切换到 19.2MHz/586 时钟。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。  */
        unsigned char  np_dcxo_clk_sel_f : 1;  /* bit[3]: 19.2MHz/586 切换到 32K RC时钟。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。  */
        unsigned char  np_vsys_vcoin_sel : 1;  /* bit[4]: VSYS与VCION切换信号。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。 */
        unsigned char  np_smpl           : 1;  /* bit[5]: SMPL发生记录
                                                          0：没有发生SMPL；
                                                          1：发生SMPL。 */
        unsigned char  np_core_io_vld_f  : 1;  /* bit[6]: core_io_vld异常下电事件记录（VDD_IO是否拉低）；
                                                          0：没有发生拉低事件；
                                                          1：有发生拉低事件。 */
        unsigned char  np_pwrhold_1s     : 1;  /* bit[7]: SYS_RST_N拉高后1s时刻，VBUS不在位，并且pwr_hold为低触发关机。
                                                          0：没有发生过该事件；
                                                          1：发生过该事件。  */
    } reg;
} PMIC_NP_RECORD2_UNION;
#endif
#define PMIC_NP_RECORD2_np_tcxo_clk_sel_r_START  (0)
#define PMIC_NP_RECORD2_np_tcxo_clk_sel_r_END    (0)
#define PMIC_NP_RECORD2_np_tcxo_clk_sel_f_START  (1)
#define PMIC_NP_RECORD2_np_tcxo_clk_sel_f_END    (1)
#define PMIC_NP_RECORD2_np_dcxo_clk_sel_r_START  (2)
#define PMIC_NP_RECORD2_np_dcxo_clk_sel_r_END    (2)
#define PMIC_NP_RECORD2_np_dcxo_clk_sel_f_START  (3)
#define PMIC_NP_RECORD2_np_dcxo_clk_sel_f_END    (3)
#define PMIC_NP_RECORD2_np_vsys_vcoin_sel_START  (4)
#define PMIC_NP_RECORD2_np_vsys_vcoin_sel_END    (4)
#define PMIC_NP_RECORD2_np_smpl_START            (5)
#define PMIC_NP_RECORD2_np_smpl_END              (5)
#define PMIC_NP_RECORD2_np_core_io_vld_f_START   (6)
#define PMIC_NP_RECORD2_np_core_io_vld_f_END     (6)
#define PMIC_NP_RECORD2_np_pwrhold_1s_START      (7)
#define PMIC_NP_RECORD2_np_pwrhold_1s_END        (7)


/*****************************************************************************
 结构名    : PMIC_NP_RECORD3_UNION
 结构说明  : NP_RECORD3 寄存器结构定义。地址偏移量:0x1C1，初值:0x00，宽度:8
 寄存器说明: 事件记录寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  np_pmua_short_f      : 1;  /* bit[0]  : pmua输出过载事件记录寄存器。
                                                               0：没有发生过该事件；
                                                               1：发生过该事件。 */
        unsigned char  np_ldo34_short_f     : 1;  /* bit[1]  : LDO34输出过载事件记录寄存器。
                                                               0：没有发生过该事件；
                                                               1：发生过该事件。 */
        unsigned char  np_vin_ldoh_shutdown : 1;  /* bit[2]  : vin_ldo异常事件记录寄存器。
                                                               0：没有发生过该事件；
                                                               1：发生过该事件。  */
        unsigned char  reserved             : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_NP_RECORD3_UNION;
#endif
#define PMIC_NP_RECORD3_np_pmua_short_f_START       (0)
#define PMIC_NP_RECORD3_np_pmua_short_f_END         (0)
#define PMIC_NP_RECORD3_np_ldo34_short_f_START      (1)
#define PMIC_NP_RECORD3_np_ldo34_short_f_END        (1)
#define PMIC_NP_RECORD3_np_vin_ldoh_shutdown_START  (2)
#define PMIC_NP_RECORD3_np_vin_ldoh_shutdown_END    (2)




/****************************************************************************
                     (3/5) PMU_RTC
 ****************************************************************************/
/*****************************************************************************
 结构名    : PMIC_RTCDR0_UNION
 结构说明  : RTCDR0 寄存器结构定义。地址偏移量:0x1D0，初值:0x00，宽度:8
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
 结构说明  : RTCDR1 寄存器结构定义。地址偏移量:0x1D1，初值:0x00，宽度:8
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
 结构说明  : RTCDR2 寄存器结构定义。地址偏移量:0x1D2，初值:0x00，宽度:8
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
 结构说明  : RTCDR3 寄存器结构定义。地址偏移量:0x1D3，初值:0x00，宽度:8
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
 结构说明  : RTCMR0 寄存器结构定义。地址偏移量:0x1D4，初值:0x00，宽度:8
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
 结构说明  : RTCMR1 寄存器结构定义。地址偏移量:0x1D5，初值:0x00，宽度:8
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
 结构说明  : RTCMR2 寄存器结构定义。地址偏移量:0x1D6，初值:0x00，宽度:8
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
 结构说明  : RTCMR3 寄存器结构定义。地址偏移量:0x1D7，初值:0x00，宽度:8
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
 结构说明  : RTCLR0 寄存器结构定义。地址偏移量:0x1D8，初值:0x00，宽度:8
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
 结构说明  : RTCLR1 寄存器结构定义。地址偏移量:0x1D9，初值:0x00，宽度:8
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
 结构说明  : RTCLR2 寄存器结构定义。地址偏移量:0x1DA，初值:0x00，宽度:8
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
 结构说明  : RTCLR3 寄存器结构定义。地址偏移量:0x1DB，初值:0x00，宽度:8
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
 结构说明  : RTCCTRL 寄存器结构定义。地址偏移量:0x1DC，初值:0x01，宽度:8
 寄存器说明: RTC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rtccr    : 1;  /* bit[0]  : 读RTC控制位。
                                                   0：读RTC当前值，返回值全部为0；
                                                   1：读RTC当前值，返回值为实际当前值。
                                                   （此寄存器写完后，要等待3个32K cycle才能再次操作此寄存器） */
        unsigned char  reserved : 7;  /* bit[1-7]: 保留。 */
    } reg;
} PMIC_RTCCTRL_UNION;
#endif
#define PMIC_RTCCTRL_rtccr_START     (0)
#define PMIC_RTCCTRL_rtccr_END       (0)


/*****************************************************************************
 结构名    : PMIC_XO_THRESOLD0_UNION
 结构说明  : XO_THRESOLD0 寄存器结构定义。地址偏移量:0x1DD，初值:0xFF，宽度:8
 寄存器说明: XO_THRESOLD[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold_low : 8;  /* bit[0-7]: 校准偏差阈值设置寄存器（推荐值0xB8，300ppm）。 */
    } reg;
} PMIC_XO_THRESOLD0_UNION;
#endif
#define PMIC_XO_THRESOLD0_xo_cali_thresold_low_START  (0)
#define PMIC_XO_THRESOLD0_xo_cali_thresold_low_END    (7)


/*****************************************************************************
 结构名    : PMIC_XO_THRESOLD1_UNION
 结构说明  : XO_THRESOLD1 寄存器结构定义。地址偏移量:0x1DE，初值:0xFF，宽度:8
 寄存器说明: XO_THRESOLD[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  xo_cali_thresold1_high : 8;  /* bit[0-7]: 校准偏差阈值设置寄存器。 */
    } reg;
} PMIC_XO_THRESOLD1_UNION;
#endif
#define PMIC_XO_THRESOLD1_xo_cali_thresold1_high_START  (0)
#define PMIC_XO_THRESOLD1_xo_cali_thresold1_high_END    (7)


/*****************************************************************************
 结构名    : PMIC_CRC_VAULE0_UNION
 结构说明  : CRC_VAULE0 寄存器结构定义。地址偏移量:0x1DF，初值:0xC0，宽度:8
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
 结构说明  : CRC_VAULE1 寄存器结构定义。地址偏移量:0x1E0，初值:0x27，宽度:8
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
 结构说明  : CRC_VAULE2 寄存器结构定义。地址偏移量:0x1E1，初值:0x09，宽度:8
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
 结构说明  : RTC_PWRUP_TIMER0 寄存器结构定义。地址偏移量:0x1E2，初值:0x00，宽度:8
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
 结构说明  : RTC_PWRUP_TIMER1 寄存器结构定义。地址偏移量:0x1E3，初值:0x00，宽度:8
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
 结构说明  : RTC_PWRUP_TIMER2 寄存器结构定义。地址偏移量:0x1E4，初值:0x00，宽度:8
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
 结构说明  : RTC_PWRUP_TIMER3 寄存器结构定义。地址偏移量:0x1E5，初值:0x00，宽度:8
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
 结构说明  : RTC_PWRDOWN_TIMER0 寄存器结构定义。地址偏移量:0x1E6，初值:0x00，宽度:8
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
 结构说明  : RTC_PWRDOWN_TIMER1 寄存器结构定义。地址偏移量:0x1E7，初值:0x00，宽度:8
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
 结构说明  : RTC_PWRDOWN_TIMER2 寄存器结构定义。地址偏移量:0x1E8，初值:0x00，宽度:8
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
 结构说明  : RTC_PWRDOWN_TIMER3 寄存器结构定义。地址偏移量:0x1E9，初值:0x00，宽度:8
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
 结构说明  : COUL_IRQ 寄存器结构定义。地址偏移量:0x1F0，初值:0x00，宽度:8
 寄存器说明: 库仑计中断寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_gate_int : 1;  /* bit[0]  : cl_out>cl_int时上报中断。
                                                      0：无此中断；
                                                      1：上报中断。 */
        unsigned char  cl_out_int  : 1;  /* bit[1]  : cl_out计数到81%上报中断。
                                                      0：无此中断；
                                                      1：上报中断。 */
        unsigned char  cl_in_int   : 1;  /* bit[2]  : cl_in计数到81%上报中断。
                                                      0：无此中断；
                                                      1：上报中断。 */
        unsigned char  v_gate_int  : 1;  /* bit[3]  : vbat电压<设定的v_int值。
                                                      0：无此中断；
                                                      1：上报中断。 */
        unsigned char  reserved    : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_COUL_IRQ_UNION;
#endif
#define PMIC_COUL_IRQ_cl_gate_int_START  (0)
#define PMIC_COUL_IRQ_cl_gate_int_END    (0)
#define PMIC_COUL_IRQ_cl_out_int_START   (1)
#define PMIC_COUL_IRQ_cl_out_int_END     (1)
#define PMIC_COUL_IRQ_cl_in_int_START    (2)
#define PMIC_COUL_IRQ_cl_in_int_END      (2)
#define PMIC_COUL_IRQ_v_gate_int_START   (3)
#define PMIC_COUL_IRQ_v_gate_int_END     (3)


/*****************************************************************************
 结构名    : PMIC_COUL_IRQ_MASK_UNION
 结构说明  : COUL_IRQ_MASK 寄存器结构定义。地址偏移量:0x1F1，初值:0x00，宽度:8
 寄存器说明: 库仑计中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_gate_int_mk : 1;  /* bit[0]  : cl_gate_int中断屏蔽位。
                                                         0：不屏蔽；
                                                         1：cl_int_i中断屏蔽。 */
        unsigned char  cl_out_int_mk  : 1;  /* bit[1]  : cl_out_int中断屏蔽位。
                                                         0：不屏蔽；
                                                         1：cl_out_i中断屏蔽。 */
        unsigned char  cl_in_int_mk   : 1;  /* bit[2]  : cl_in_int中断屏蔽位。
                                                         0：不屏蔽；
                                                         1：cl_in_i中断屏蔽。 */
        unsigned char  v_gate_int_mk  : 1;  /* bit[3]  : v_gate_int中断屏蔽位。
                                                         0：不屏蔽；
                                                         1：vbat_int_i中断屏蔽。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} PMIC_COUL_IRQ_MASK_UNION;
#endif
#define PMIC_COUL_IRQ_MASK_cl_gate_int_mk_START  (0)
#define PMIC_COUL_IRQ_MASK_cl_gate_int_mk_END    (0)
#define PMIC_COUL_IRQ_MASK_cl_out_int_mk_START   (1)
#define PMIC_COUL_IRQ_MASK_cl_out_int_mk_END     (1)
#define PMIC_COUL_IRQ_MASK_cl_in_int_mk_START    (2)
#define PMIC_COUL_IRQ_MASK_cl_in_int_mk_END      (2)
#define PMIC_COUL_IRQ_MASK_v_gate_int_mk_START   (3)
#define PMIC_COUL_IRQ_MASK_v_gate_int_mk_END     (3)


/*****************************************************************************
 结构名    : PMIC_CURRENT_0_UNION
 结构说明  : CURRENT_0 寄存器结构定义。地址偏移量:0x1F2，初值:0x00，宽度:8
 寄存器说明: 当前电流[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_s0 : 8;  /* bit[0-7]: 当前电流值，此值是经过校准后的值。
                                                     （对于依靠多组寄存器存储的数据，软件读取时必须先读低8bit，再依次往高位读取，最后读取最高8bit。两次读取之间没有时间约束。下面所有多于8bit的寄存器的读写方式均要求按照此操作。） */
    } reg;
} PMIC_CURRENT_0_UNION;
#endif
#define PMIC_CURRENT_0_current_s0_START  (0)
#define PMIC_CURRENT_0_current_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT_1_UNION
 结构说明  : CURRENT_1 寄存器结构定义。地址偏移量:0x1F3，初值:0x00，宽度:8
 寄存器说明: 当前电流[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT_1_UNION;
#endif
#define PMIC_CURRENT_1_current_s1_START  (0)
#define PMIC_CURRENT_1_current_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT_0_UNION
 结构说明  : V_OUT_0 寄存器结构定义。地址偏移量:0x1F4，初值:0xFF，宽度:8
 寄存器说明: 当前电压[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_s0 : 8;  /* bit[0-7]: 当前电压值，此值是经过校准后的值。 */
    } reg;
} PMIC_V_OUT_0_UNION;
#endif
#define PMIC_V_OUT_0_v_out_s0_START  (0)
#define PMIC_V_OUT_0_v_out_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT_1_UNION
 结构说明  : V_OUT_1 寄存器结构定义。地址偏移量:0x1F5，初值:0xFF，宽度:8
 寄存器说明: 当前电压[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT_1_UNION;
#endif
#define PMIC_V_OUT_1_v_out_s1_START  (0)
#define PMIC_V_OUT_1_v_out_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_CTRL_REG_UNION
 结构说明  : CLJ_CTRL_REG 寄存器结构定义。地址偏移量:0x1F6，初值:0x00，宽度:8
 寄存器说明: 库仑计控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_ctrl           : 3;  /* bit[0-2]: bit[2]：是否强制进入ECO模式控制。
                                                             0：不强制进入ECO模式；
                                                             1：强制进入ECO模式。
                                                             
                                                             bit[1]：库仑计是否跟随PMU进入ECO模式控制。
                                                             0：库仑计不跟随PMU进入ECO模式；
                                                             1：库仑计跟随PMU进入ECO模式。
                                                             仅发生在bit[2] == 0 时有效。（要想跟随PMU，同时需要将0x12D[COUL_ECO_MASK]寄存器清零）
                                                             
                                                             bit[0]：进入ECO模式时，使能信号是否去抖控制。
                                                             0：进入ECO模式使能信号不去抖；
                                                             1：进入ECO模式使能信号去抖。
                                                             仅发生在bit[1] ==1 时有效。
                                                             注：eco_ctrl该寄存器热复位后清零。 */
        unsigned char  reflash_value_ctrl : 1;  /* bit[3]  : 库仑计更新数据方式选择：
                                                             0：所有状态都更新数据；
                                                             1：仅ECO模式更新数据。 */
        unsigned char  eco_filter_time    : 3;  /* bit[4-6]: 库仑计退出ECO模式使能信号去抖时间选择：
                                                             000：50ms；
                                                             001：100ms；
                                                             010：150ms；
                                                             011：200ms；
                                                             100: 250ms；
                                                             101: 300ms；
                                                             110: 350ms；
                                                             111: 400ms；
                                                             用于配置en_eco_mode去抖时长，默认为000。 */
        unsigned char  calibration_ctrl   : 1;  /* bit[7]  : 库仑计强制校准控制位。
                                                             0：不校准；
                                                             1：强制进入校准状态。 */
    } reg;
} PMIC_CLJ_CTRL_REG_UNION;
#endif
#define PMIC_CLJ_CTRL_REG_eco_ctrl_START            (0)
#define PMIC_CLJ_CTRL_REG_eco_ctrl_END              (2)
#define PMIC_CLJ_CTRL_REG_reflash_value_ctrl_START  (3)
#define PMIC_CLJ_CTRL_REG_reflash_value_ctrl_END    (3)
#define PMIC_CLJ_CTRL_REG_eco_filter_time_START     (4)
#define PMIC_CLJ_CTRL_REG_eco_filter_time_END       (6)
#define PMIC_CLJ_CTRL_REG_calibration_ctrl_START    (7)
#define PMIC_CLJ_CTRL_REG_calibration_ctrl_END      (7)


/*****************************************************************************
 结构名    : PMIC_ECO_REFALSH_TIME_UNION
 结构说明  : ECO_REFALSH_TIME 寄存器结构定义。地址偏移量:0x1F7，初值:0x01，宽度:8
 寄存器说明: ECO_REFLASH工作时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_reflash_time : 8;  /* bit[0-7]: 此工作时间以一个单位代表110ms，为ECO_REFLASH时间；有效配置值为1~255，配置值大于255时，硬件直接饱和到255。默认为1。
                                                           软件配置库仑计进出ECO模式，只启用采1拍，停9拍，等待1拍的常规模式，其余多个FLASH周期的模式暂无应用，不对其进行验证覆盖。 */
    } reg;
} PMIC_ECO_REFALSH_TIME_UNION;
#endif
#define PMIC_ECO_REFALSH_TIME_eco_reflash_time_START  (0)
#define PMIC_ECO_REFALSH_TIME_eco_reflash_time_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_OUT0_UNION
 结构说明  : CL_OUT0 寄存器结构定义。地址偏移量:0x1F8，初值:0x00，宽度:8
 寄存器说明: cl_out[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out_s0 : 8;  /* bit[0-7]: 流出电量计数器[31:0]。
                                                    （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_CL_OUT0_UNION;
#endif
#define PMIC_CL_OUT0_cl_out_s0_START  (0)
#define PMIC_CL_OUT0_cl_out_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_OUT1_UNION
 结构说明  : CL_OUT1 寄存器结构定义。地址偏移量:0x1F9，初值:0x00，宽度:8
 寄存器说明: cl_out[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT1_UNION;
#endif
#define PMIC_CL_OUT1_cl_out_s1_START  (0)
#define PMIC_CL_OUT1_cl_out_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_OUT2_UNION
 结构说明  : CL_OUT2 寄存器结构定义。地址偏移量:0x1FA，初值:0x00，宽度:8
 寄存器说明: cl_out[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT2_UNION;
#endif
#define PMIC_CL_OUT2_cl_out_s2_START  (0)
#define PMIC_CL_OUT2_cl_out_s2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_OUT3_UNION
 结构说明  : CL_OUT3 寄存器结构定义。地址偏移量:0x1FB，初值:0x00，宽度:8
 寄存器说明: cl_out[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_out_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_OUT3_UNION;
#endif
#define PMIC_CL_OUT3_cl_out_s3_START  (0)
#define PMIC_CL_OUT3_cl_out_s3_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_IN0_UNION
 结构说明  : CL_IN0 寄存器结构定义。地址偏移量:0x1FC，初值:0x00，宽度:8
 寄存器说明: cl_in[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in_s0 : 8;  /* bit[0-7]: 流入电量计数器[31:0]。
                                                   （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_CL_IN0_UNION;
#endif
#define PMIC_CL_IN0_cl_in_s0_START  (0)
#define PMIC_CL_IN0_cl_in_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_IN1_UNION
 结构说明  : CL_IN1 寄存器结构定义。地址偏移量:0x1FD，初值:0x00，宽度:8
 寄存器说明: cl_in[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN1_UNION;
#endif
#define PMIC_CL_IN1_cl_in_s1_START  (0)
#define PMIC_CL_IN1_cl_in_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_IN2_UNION
 结构说明  : CL_IN2 寄存器结构定义。地址偏移量:0x1FE，初值:0x00，宽度:8
 寄存器说明: cl_in[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN2_UNION;
#endif
#define PMIC_CL_IN2_cl_in_s2_START  (0)
#define PMIC_CL_IN2_cl_in_s2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_IN3_UNION
 结构说明  : CL_IN3 寄存器结构定义。地址偏移量:0x1FF，初值:0x00，宽度:8
 寄存器说明: cl_in[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_in_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_IN3_UNION;
#endif
#define PMIC_CL_IN3_cl_in_s3_START  (0)
#define PMIC_CL_IN3_cl_in_s3_END    (7)


/*****************************************************************************
 结构名    : PMIC_CHG_TIMER0_UNION
 结构说明  : CHG_TIMER0 寄存器结构定义。地址偏移量:0x200，初值:0x00，宽度:8
 寄存器说明: chg_timer[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer_s0 : 8;  /* bit[0-7]: 充电时间计数器[31:0]。
                                                       （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_CHG_TIMER0_UNION;
#endif
#define PMIC_CHG_TIMER0_chg_timer_s0_START  (0)
#define PMIC_CHG_TIMER0_chg_timer_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CHG_TIMER1_UNION
 结构说明  : CHG_TIMER1 寄存器结构定义。地址偏移量:0x201，初值:0x00，宽度:8
 寄存器说明: chg_timer[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER1_UNION;
#endif
#define PMIC_CHG_TIMER1_chg_timer_s1_START  (0)
#define PMIC_CHG_TIMER1_chg_timer_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CHG_TIMER2_UNION
 结构说明  : CHG_TIMER2 寄存器结构定义。地址偏移量:0x202，初值:0x00，宽度:8
 寄存器说明: chg_timer[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER2_UNION;
#endif
#define PMIC_CHG_TIMER2_chg_timer_s2_START  (0)
#define PMIC_CHG_TIMER2_chg_timer_s2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CHG_TIMER3_UNION
 结构说明  : CHG_TIMER3 寄存器结构定义。地址偏移量:0x203，初值:0x00，宽度:8
 寄存器说明: chg_timer[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_timer_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CHG_TIMER3_UNION;
#endif
#define PMIC_CHG_TIMER3_chg_timer_s3_START  (0)
#define PMIC_CHG_TIMER3_chg_timer_s3_END    (7)


/*****************************************************************************
 结构名    : PMIC_LOAD_TIMER0_UNION
 结构说明  : LOAD_TIMER0 寄存器结构定义。地址偏移量:0x204，初值:0x00，宽度:8
 寄存器说明: load_timer[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer_s0 : 8;  /* bit[0-7]: 放电时间计数器[31:0]。
                                                        （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_LOAD_TIMER0_UNION;
#endif
#define PMIC_LOAD_TIMER0_load_timer_s0_START  (0)
#define PMIC_LOAD_TIMER0_load_timer_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_LOAD_TIMER1_UNION
 结构说明  : LOAD_TIMER1 寄存器结构定义。地址偏移量:0x205，初值:0x00，宽度:8
 寄存器说明: load_timer[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER1_UNION;
#endif
#define PMIC_LOAD_TIMER1_load_timer_s1_START  (0)
#define PMIC_LOAD_TIMER1_load_timer_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_LOAD_TIMER2_UNION
 结构说明  : LOAD_TIMER2 寄存器结构定义。地址偏移量:0x206，初值:0x00，宽度:8
 寄存器说明: load_timer[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER2_UNION;
#endif
#define PMIC_LOAD_TIMER2_load_timer_s2_START  (0)
#define PMIC_LOAD_TIMER2_load_timer_s2_END    (7)


/*****************************************************************************
 结构名    : PMIC_LOAD_TIMER3_UNION
 结构说明  : LOAD_TIMER3 寄存器结构定义。地址偏移量:0x207，初值:0x00，宽度:8
 寄存器说明: load_timer[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  load_timer_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_LOAD_TIMER3_UNION;
#endif
#define PMIC_LOAD_TIMER3_load_timer_s3_START  (0)
#define PMIC_LOAD_TIMER3_load_timer_s3_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_INT0_UNION
 结构说明  : CL_INT0 寄存器结构定义。地址偏移量:0x208，初值:0x00，宽度:8
 寄存器说明: cl_int[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_s0 : 8;  /* bit[0-7]: 流出电量中断比较寄存器[31:0]：
                                                    当cl_inout>cl_int时上报中断。
                                                    （从低8bit，依次往高位写入，最后写入最高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据最高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_CL_INT0_UNION;
#endif
#define PMIC_CL_INT0_cl_int_s0_START  (0)
#define PMIC_CL_INT0_cl_int_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_INT1_UNION
 结构说明  : CL_INT1 寄存器结构定义。地址偏移量:0x209，初值:0x00，宽度:8
 寄存器说明: cl_int[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT1_UNION;
#endif
#define PMIC_CL_INT1_cl_int_s1_START  (0)
#define PMIC_CL_INT1_cl_int_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_INT2_UNION
 结构说明  : CL_INT2 寄存器结构定义。地址偏移量:0x20A，初值:0x00，宽度:8
 寄存器说明: cl_int[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT2_UNION;
#endif
#define PMIC_CL_INT2_cl_int_s2_START  (0)
#define PMIC_CL_INT2_cl_int_s2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CL_INT3_UNION
 结构说明  : CL_INT3 寄存器结构定义。地址偏移量:0x20B，初值:0x80，宽度:8
 寄存器说明: cl_int[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cl_int_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CL_INT3_UNION;
#endif
#define PMIC_CL_INT3_cl_int_s3_START  (0)
#define PMIC_CL_INT3_cl_int_s3_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_INT0_UNION
 结构说明  : V_INT0 寄存器结构定义。地址偏移量:0x20C，初值:0x00，宽度:8
 寄存器说明: v_int[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_int_s0 : 8;  /* bit[0-7]: 电压中断比较值寄存器[15:0]。
                                                   （先写低8bit，再写高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_V_INT0_UNION;
#endif
#define PMIC_V_INT0_v_int_s0_START  (0)
#define PMIC_V_INT0_v_int_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_INT1_UNION
 结构说明  : V_INT1 寄存器结构定义。地址偏移量:0x20D，初值:0x00，宽度:8
 寄存器说明: v_int[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_int_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_INT1_UNION;
#endif
#define PMIC_V_INT1_v_int_s1_START  (0)
#define PMIC_V_INT1_v_int_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_CURRENT0_UNION
 结构说明  : OFFSET_CURRENT0 寄存器结构定义。地址偏移量:0x20E，初值:0x00，宽度:8
 寄存器说明: offset_current[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_s0 : 8;  /* bit[0-7]: 电流校准值[15:0]。 */
    } reg;
} PMIC_OFFSET_CURRENT0_UNION;
#endif
#define PMIC_OFFSET_CURRENT0_offset_current_s0_START  (0)
#define PMIC_OFFSET_CURRENT0_offset_current_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_CURRENT1_UNION
 结构说明  : OFFSET_CURRENT1 寄存器结构定义。地址偏移量:0x20F，初值:0x00，宽度:8
 寄存器说明: offset_current[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_CURRENT1_UNION;
#endif
#define PMIC_OFFSET_CURRENT1_offset_current_s1_START  (0)
#define PMIC_OFFSET_CURRENT1_offset_current_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_VOLTAGE0_UNION
 结构说明  : OFFSET_VOLTAGE0 寄存器结构定义。地址偏移量:0x210，初值:0x00，宽度:8
 寄存器说明: offset_voltage[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_s0 : 8;  /* bit[0-7]: 电压校准值[15:0]。 */
    } reg;
} PMIC_OFFSET_VOLTAGE0_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE0_offset_voltage_s0_START  (0)
#define PMIC_OFFSET_VOLTAGE0_offset_voltage_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_VOLTAGE1_UNION
 结构说明  : OFFSET_VOLTAGE1 寄存器结构定义。地址偏移量:0x211，初值:0x00，宽度:8
 寄存器说明: offset_voltage[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_VOLTAGE1_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE1_offset_voltage_s1_START  (0)
#define PMIC_OFFSET_VOLTAGE1_offset_voltage_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCV_VOLTAGE0_UNION
 结构说明  : OCV_VOLTAGE0 寄存器结构定义。地址偏移量:0x212，初值:0x00，宽度:8
 寄存器说明: v_ocv_data[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_ocv_data_s0 : 8;  /* bit[0-7]: 开机时OCV电压采样值[15:0]。此值是原始值，未经过校准。 */
    } reg;
} PMIC_OCV_VOLTAGE0_UNION;
#endif
#define PMIC_OCV_VOLTAGE0_v_ocv_data_s0_START  (0)
#define PMIC_OCV_VOLTAGE0_v_ocv_data_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCV_VOLTAGE1_UNION
 结构说明  : OCV_VOLTAGE1 寄存器结构定义。地址偏移量:0x213，初值:0x00，宽度:8
 寄存器说明: v_ocv_data[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_ocv_data_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OCV_VOLTAGE1_UNION;
#endif
#define PMIC_OCV_VOLTAGE1_v_ocv_data_s1_START  (0)
#define PMIC_OCV_VOLTAGE1_v_ocv_data_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCV_CURRENT0_UNION
 结构说明  : OCV_CURRENT0 寄存器结构定义。地址偏移量:0x214，初值:0x00，宽度:8
 寄存器说明: i_ocv_data[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_ocv_data_s0 : 8;  /* bit[0-7]: 开机时OCV电流采样值[15:0]。此值是原始值，未经过校准。 */
    } reg;
} PMIC_OCV_CURRENT0_UNION;
#endif
#define PMIC_OCV_CURRENT0_i_ocv_data_s0_START  (0)
#define PMIC_OCV_CURRENT0_i_ocv_data_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OCV_CURRENT1_UNION
 结构说明  : OCV_CURRENT1 寄存器结构定义。地址偏移量:0x215，初值:0x00，宽度:8
 寄存器说明: i_ocv_data[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_ocv_data_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OCV_CURRENT1_UNION;
#endif
#define PMIC_OCV_CURRENT1_i_ocv_data_s1_START  (0)
#define PMIC_OCV_CURRENT1_i_ocv_data_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLIN_0_UNION
 结构说明  : ECO_OUT_CLIN_0 寄存器结构定义。地址偏移量:0x216，初值:0x00，宽度:8
 寄存器说明: eco_out_clin[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin_s0 : 8;  /* bit[0-7]: 退出ECO模式流入电量计数器[13:0]。每次退出ECO模式自动记录当前流入电量，其余时刻保持。 */
    } reg;
} PMIC_ECO_OUT_CLIN_0_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_0_eco_out_clin_s0_START  (0)
#define PMIC_ECO_OUT_CLIN_0_eco_out_clin_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLIN_1_UNION
 结构说明  : ECO_OUT_CLIN_1 寄存器结构定义。地址偏移量:0x217，初值:0x00，宽度:8
 寄存器说明: eco_out_clin[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_1_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_1_eco_out_clin_s1_START  (0)
#define PMIC_ECO_OUT_CLIN_1_eco_out_clin_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLIN_2_UNION
 结构说明  : ECO_OUT_CLIN_2 寄存器结构定义。地址偏移量:0x218，初值:0x00，宽度:8
 寄存器说明: eco_out_clin[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_2_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_2_eco_out_clin_s2_START  (0)
#define PMIC_ECO_OUT_CLIN_2_eco_out_clin_s2_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLIN_3_UNION
 结构说明  : ECO_OUT_CLIN_3 寄存器结构定义。地址偏移量:0x219，初值:0x00，宽度:8
 寄存器说明: eco_out_clin[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clin_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLIN_3_UNION;
#endif
#define PMIC_ECO_OUT_CLIN_3_eco_out_clin_s3_START  (0)
#define PMIC_ECO_OUT_CLIN_3_eco_out_clin_s3_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLOUT_0_UNION
 结构说明  : ECO_OUT_CLOUT_0 寄存器结构定义。地址偏移量:0x21A，初值:0x00，宽度:8
 寄存器说明: eco_out_clout[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout_s0 : 8;  /* bit[0-7]: 退出ECO模式流出电量计数器[31:0]。每次退出ECO模式自动记录当前流出电量，其余时刻保持。 */
    } reg;
} PMIC_ECO_OUT_CLOUT_0_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_0_eco_out_clout_s0_START  (0)
#define PMIC_ECO_OUT_CLOUT_0_eco_out_clout_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLOUT_1_UNION
 结构说明  : ECO_OUT_CLOUT_1 寄存器结构定义。地址偏移量:0x21B，初值:0x00，宽度:8
 寄存器说明: eco_out_clout[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_1_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_1_eco_out_clout_s1_START  (0)
#define PMIC_ECO_OUT_CLOUT_1_eco_out_clout_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLOUT_2_UNION
 结构说明  : ECO_OUT_CLOUT_2 寄存器结构定义。地址偏移量:0x21C，初值:0x00，宽度:8
 寄存器说明: eco_out_clout[23:16]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout_s2 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_2_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_2_eco_out_clout_s2_START  (0)
#define PMIC_ECO_OUT_CLOUT_2_eco_out_clout_s2_END    (7)


/*****************************************************************************
 结构名    : PMIC_ECO_OUT_CLOUT_3_UNION
 结构说明  : ECO_OUT_CLOUT_3 寄存器结构定义。地址偏移量:0x21D，初值:0x00，宽度:8
 寄存器说明: eco_out_clout[31:24]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  eco_out_clout_s3 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_ECO_OUT_CLOUT_3_UNION;
#endif
#define PMIC_ECO_OUT_CLOUT_3_eco_out_clout_s3_START  (0)
#define PMIC_ECO_OUT_CLOUT_3_eco_out_clout_s3_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE0_UNION
 结构说明  : V_OUT0_PRE0 寄存器结构定义。地址偏移量:0x21E，初值:0xFF，宽度:8
 寄存器说明: v_out_pre0[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre0_s0 : 8;  /* bit[0-7]: 当前电池电压指示[15:0]，最高位代表符号位。 */
    } reg;
} PMIC_V_OUT0_PRE0_UNION;
#endif
#define PMIC_V_OUT0_PRE0_v_out_pre0_s0_START  (0)
#define PMIC_V_OUT0_PRE0_v_out_pre0_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE0_UNION
 结构说明  : V_OUT1_PRE0 寄存器结构定义。地址偏移量:0x21F，初值:0xFF，宽度:8
 寄存器说明: v_out_pre0[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre0_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE0_UNION;
#endif
#define PMIC_V_OUT1_PRE0_v_out_pre0_s1_START  (0)
#define PMIC_V_OUT1_PRE0_v_out_pre0_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE1_UNION
 结构说明  : V_OUT0_PRE1 寄存器结构定义。地址偏移量:0x220，初值:0xFF，宽度:8
 寄存器说明: v_out_pre1[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre1_s0 : 8;  /* bit[0-7]: 当前电压前一次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE1_UNION;
#endif
#define PMIC_V_OUT0_PRE1_v_out_pre1_s0_START  (0)
#define PMIC_V_OUT0_PRE1_v_out_pre1_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE1_UNION
 结构说明  : V_OUT1_PRE1 寄存器结构定义。地址偏移量:0x221，初值:0xFF，宽度:8
 寄存器说明: v_out_pre1[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre1_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE1_UNION;
#endif
#define PMIC_V_OUT1_PRE1_v_out_pre1_s1_START  (0)
#define PMIC_V_OUT1_PRE1_v_out_pre1_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE2_UNION
 结构说明  : V_OUT0_PRE2 寄存器结构定义。地址偏移量:0x222，初值:0xFF，宽度:8
 寄存器说明: v_out_pre2[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre2_s0 : 8;  /* bit[0-7]: 当前电压前二次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE2_UNION;
#endif
#define PMIC_V_OUT0_PRE2_v_out_pre2_s0_START  (0)
#define PMIC_V_OUT0_PRE2_v_out_pre2_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE2_UNION
 结构说明  : V_OUT1_PRE2 寄存器结构定义。地址偏移量:0x223，初值:0xFF，宽度:8
 寄存器说明: v_out_pre2[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre2_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE2_UNION;
#endif
#define PMIC_V_OUT1_PRE2_v_out_pre2_s1_START  (0)
#define PMIC_V_OUT1_PRE2_v_out_pre2_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE3_UNION
 结构说明  : V_OUT0_PRE3 寄存器结构定义。地址偏移量:0x224，初值:0xFF，宽度:8
 寄存器说明: v_out_pre3[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre3_s0 : 8;  /* bit[0-7]: 当前电压前三次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE3_UNION;
#endif
#define PMIC_V_OUT0_PRE3_v_out_pre3_s0_START  (0)
#define PMIC_V_OUT0_PRE3_v_out_pre3_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE3_UNION
 结构说明  : V_OUT1_PRE3 寄存器结构定义。地址偏移量:0x225，初值:0xFF，宽度:8
 寄存器说明: v_out_pre3[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre3_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE3_UNION;
#endif
#define PMIC_V_OUT1_PRE3_v_out_pre3_s1_START  (0)
#define PMIC_V_OUT1_PRE3_v_out_pre3_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE4_UNION
 结构说明  : V_OUT0_PRE4 寄存器结构定义。地址偏移量:0x226，初值:0xFF，宽度:8
 寄存器说明: v_out_pre4[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre4_s0 : 8;  /* bit[0-7]: 当前电压前四次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE4_UNION;
#endif
#define PMIC_V_OUT0_PRE4_v_out_pre4_s0_START  (0)
#define PMIC_V_OUT0_PRE4_v_out_pre4_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE4_UNION
 结构说明  : V_OUT1_PRE4 寄存器结构定义。地址偏移量:0x227，初值:0xFF，宽度:8
 寄存器说明: v_out_pre4[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre4_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE4_UNION;
#endif
#define PMIC_V_OUT1_PRE4_v_out_pre4_s1_START  (0)
#define PMIC_V_OUT1_PRE4_v_out_pre4_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE5_UNION
 结构说明  : V_OUT0_PRE5 寄存器结构定义。地址偏移量:0x228，初值:0xFF，宽度:8
 寄存器说明: v_out_pre5[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre5_s0 : 8;  /* bit[0-7]: 当前电压前五次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE5_UNION;
#endif
#define PMIC_V_OUT0_PRE5_v_out_pre5_s0_START  (0)
#define PMIC_V_OUT0_PRE5_v_out_pre5_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE5_UNION
 结构说明  : V_OUT1_PRE5 寄存器结构定义。地址偏移量:0x229，初值:0xFF，宽度:8
 寄存器说明: v_out_pre5[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre5_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE5_UNION;
#endif
#define PMIC_V_OUT1_PRE5_v_out_pre5_s1_START  (0)
#define PMIC_V_OUT1_PRE5_v_out_pre5_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE6_UNION
 结构说明  : V_OUT0_PRE6 寄存器结构定义。地址偏移量:0x22A，初值:0xFF，宽度:8
 寄存器说明: v_out_pre6[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre6_s0 : 8;  /* bit[0-7]: 当前电压前六次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE6_UNION;
#endif
#define PMIC_V_OUT0_PRE6_v_out_pre6_s0_START  (0)
#define PMIC_V_OUT0_PRE6_v_out_pre6_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE6_UNION
 结构说明  : V_OUT1_PRE6 寄存器结构定义。地址偏移量:0x22B，初值:0xFF，宽度:8
 寄存器说明: v_out_pre6[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre6_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE6_UNION;
#endif
#define PMIC_V_OUT1_PRE6_v_out_pre6_s1_START  (0)
#define PMIC_V_OUT1_PRE6_v_out_pre6_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE7_UNION
 结构说明  : V_OUT0_PRE7 寄存器结构定义。地址偏移量:0x22C，初值:0xFF，宽度:8
 寄存器说明: v_out_pre7[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre7_s0 : 8;  /* bit[0-7]: 当前电压前七次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE7_UNION;
#endif
#define PMIC_V_OUT0_PRE7_v_out_pre7_s0_START  (0)
#define PMIC_V_OUT0_PRE7_v_out_pre7_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE7_UNION
 结构说明  : V_OUT1_PRE7 寄存器结构定义。地址偏移量:0x22D，初值:0xFF，宽度:8
 寄存器说明: v_out_pre7[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre7_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE7_UNION;
#endif
#define PMIC_V_OUT1_PRE7_v_out_pre7_s1_START  (0)
#define PMIC_V_OUT1_PRE7_v_out_pre7_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE8_UNION
 结构说明  : V_OUT0_PRE8 寄存器结构定义。地址偏移量:0x22E，初值:0xFF，宽度:8
 寄存器说明: v_out_pre8[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre8_s0 : 8;  /* bit[0-7]: 当前电压前八次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE8_UNION;
#endif
#define PMIC_V_OUT0_PRE8_v_out_pre8_s0_START  (0)
#define PMIC_V_OUT0_PRE8_v_out_pre8_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE8_UNION
 结构说明  : V_OUT1_PRE8 寄存器结构定义。地址偏移量:0x22F，初值:0xFF，宽度:8
 寄存器说明: v_out_pre8[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre8_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE8_UNION;
#endif
#define PMIC_V_OUT1_PRE8_v_out_pre8_s1_START  (0)
#define PMIC_V_OUT1_PRE8_v_out_pre8_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT0_PRE9_UNION
 结构说明  : V_OUT0_PRE9 寄存器结构定义。地址偏移量:0x230，初值:0xFF，宽度:8
 寄存器说明: v_out_pre9[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre9_s0 : 8;  /* bit[0-7]: 当前电压前九次值[15:0]。 */
    } reg;
} PMIC_V_OUT0_PRE9_UNION;
#endif
#define PMIC_V_OUT0_PRE9_v_out_pre9_s0_START  (0)
#define PMIC_V_OUT0_PRE9_v_out_pre9_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_V_OUT1_PRE9_UNION
 结构说明  : V_OUT1_PRE9 寄存器结构定义。地址偏移量:0x231，初值:0xFF，宽度:8
 寄存器说明: v_out_pre9[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_out_pre9_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_V_OUT1_PRE9_UNION;
#endif
#define PMIC_V_OUT1_PRE9_v_out_pre9_s1_START  (0)
#define PMIC_V_OUT1_PRE9_v_out_pre9_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE0_UNION
 结构说明  : CURRENT0_PRE0 寄存器结构定义。地址偏移量:0x232，初值:0x00，宽度:8
 寄存器说明: current_pre0[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre0_s0 : 8;  /* bit[0-7]: 当前电流指示[15:0]，最高位代表符号位。 */
    } reg;
} PMIC_CURRENT0_PRE0_UNION;
#endif
#define PMIC_CURRENT0_PRE0_current_pre0_s0_START  (0)
#define PMIC_CURRENT0_PRE0_current_pre0_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE0_UNION
 结构说明  : CURRENT1_PRE0 寄存器结构定义。地址偏移量:0x233，初值:0x00，宽度:8
 寄存器说明: current_pre0[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre0_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE0_UNION;
#endif
#define PMIC_CURRENT1_PRE0_current_pre0_s1_START  (0)
#define PMIC_CURRENT1_PRE0_current_pre0_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE1_UNION
 结构说明  : CURRENT0_PRE1 寄存器结构定义。地址偏移量:0x234，初值:0x00，宽度:8
 寄存器说明: current_pre1[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre1_s0 : 8;  /* bit[0-7]: 当前电流前一次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE1_UNION;
#endif
#define PMIC_CURRENT0_PRE1_current_pre1_s0_START  (0)
#define PMIC_CURRENT0_PRE1_current_pre1_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE1_UNION
 结构说明  : CURRENT1_PRE1 寄存器结构定义。地址偏移量:0x235，初值:0x00，宽度:8
 寄存器说明: current_pre1[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre1_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE1_UNION;
#endif
#define PMIC_CURRENT1_PRE1_current_pre1_s1_START  (0)
#define PMIC_CURRENT1_PRE1_current_pre1_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE2_UNION
 结构说明  : CURRENT0_PRE2 寄存器结构定义。地址偏移量:0x236，初值:0x00，宽度:8
 寄存器说明: current_pre2[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre2_s0 : 8;  /* bit[0-7]: 当前电流前二次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE2_UNION;
#endif
#define PMIC_CURRENT0_PRE2_current_pre2_s0_START  (0)
#define PMIC_CURRENT0_PRE2_current_pre2_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE2_UNION
 结构说明  : CURRENT1_PRE2 寄存器结构定义。地址偏移量:0x237，初值:0x00，宽度:8
 寄存器说明: current_pre2[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre2_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE2_UNION;
#endif
#define PMIC_CURRENT1_PRE2_current_pre2_s1_START  (0)
#define PMIC_CURRENT1_PRE2_current_pre2_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE3_UNION
 结构说明  : CURRENT0_PRE3 寄存器结构定义。地址偏移量:0x238，初值:0x00，宽度:8
 寄存器说明: current_pre3[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre3_s0 : 8;  /* bit[0-7]: 当前电流前三次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE3_UNION;
#endif
#define PMIC_CURRENT0_PRE3_current_pre3_s0_START  (0)
#define PMIC_CURRENT0_PRE3_current_pre3_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE3_UNION
 结构说明  : CURRENT1_PRE3 寄存器结构定义。地址偏移量:0x239，初值:0x00，宽度:8
 寄存器说明: current_pre3[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre3_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE3_UNION;
#endif
#define PMIC_CURRENT1_PRE3_current_pre3_s1_START  (0)
#define PMIC_CURRENT1_PRE3_current_pre3_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE4_UNION
 结构说明  : CURRENT0_PRE4 寄存器结构定义。地址偏移量:0x23A，初值:0x00，宽度:8
 寄存器说明: current_pre4[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre4_s0 : 8;  /* bit[0-7]: 当前电流前四次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE4_UNION;
#endif
#define PMIC_CURRENT0_PRE4_current_pre4_s0_START  (0)
#define PMIC_CURRENT0_PRE4_current_pre4_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE4_UNION
 结构说明  : CURRENT1_PRE4 寄存器结构定义。地址偏移量:0x23B，初值:0x00，宽度:8
 寄存器说明: current_pre4[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre4_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE4_UNION;
#endif
#define PMIC_CURRENT1_PRE4_current_pre4_s1_START  (0)
#define PMIC_CURRENT1_PRE4_current_pre4_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE5_UNION
 结构说明  : CURRENT0_PRE5 寄存器结构定义。地址偏移量:0x23C，初值:0x00，宽度:8
 寄存器说明: current_pre5[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre5_s0 : 8;  /* bit[0-7]: 当前电流前五次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE5_UNION;
#endif
#define PMIC_CURRENT0_PRE5_current_pre5_s0_START  (0)
#define PMIC_CURRENT0_PRE5_current_pre5_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE5_UNION
 结构说明  : CURRENT1_PRE5 寄存器结构定义。地址偏移量:0x23D，初值:0x00，宽度:8
 寄存器说明: current_pre5[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre5_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE5_UNION;
#endif
#define PMIC_CURRENT1_PRE5_current_pre5_s1_START  (0)
#define PMIC_CURRENT1_PRE5_current_pre5_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE6_UNION
 结构说明  : CURRENT0_PRE6 寄存器结构定义。地址偏移量:0x23E，初值:0x00，宽度:8
 寄存器说明: current_pre6[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre6_s0 : 8;  /* bit[0-7]: 当前电流前六次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE6_UNION;
#endif
#define PMIC_CURRENT0_PRE6_current_pre6_s0_START  (0)
#define PMIC_CURRENT0_PRE6_current_pre6_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE6_UNION
 结构说明  : CURRENT1_PRE6 寄存器结构定义。地址偏移量:0x23F，初值:0x00，宽度:8
 寄存器说明: current_pre6[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre6_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE6_UNION;
#endif
#define PMIC_CURRENT1_PRE6_current_pre6_s1_START  (0)
#define PMIC_CURRENT1_PRE6_current_pre6_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE7_UNION
 结构说明  : CURRENT0_PRE7 寄存器结构定义。地址偏移量:0x240，初值:0x00，宽度:8
 寄存器说明: current_pre7[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre7_s0 : 8;  /* bit[0-7]: 当前电流前七次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE7_UNION;
#endif
#define PMIC_CURRENT0_PRE7_current_pre7_s0_START  (0)
#define PMIC_CURRENT0_PRE7_current_pre7_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE7_UNION
 结构说明  : CURRENT1_PRE7 寄存器结构定义。地址偏移量:0x241，初值:0x00，宽度:8
 寄存器说明: current_pre7[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre7_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE7_UNION;
#endif
#define PMIC_CURRENT1_PRE7_current_pre7_s1_START  (0)
#define PMIC_CURRENT1_PRE7_current_pre7_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE8_UNION
 结构说明  : CURRENT0_PRE8 寄存器结构定义。地址偏移量:0x242，初值:0x00，宽度:8
 寄存器说明: current_pre8[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre8_s0 : 8;  /* bit[0-7]: 当前电流前八次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE8_UNION;
#endif
#define PMIC_CURRENT0_PRE8_current_pre8_s0_START  (0)
#define PMIC_CURRENT0_PRE8_current_pre8_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE8_UNION
 结构说明  : CURRENT1_PRE8 寄存器结构定义。地址偏移量:0x243，初值:0x00，宽度:8
 寄存器说明: current_pre8[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre8_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE8_UNION;
#endif
#define PMIC_CURRENT1_PRE8_current_pre8_s1_START  (0)
#define PMIC_CURRENT1_PRE8_current_pre8_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT0_PRE9_UNION
 结构说明  : CURRENT0_PRE9 寄存器结构定义。地址偏移量:0x244，初值:0x00，宽度:8
 寄存器说明: current_pre9[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre9_s0 : 8;  /* bit[0-7]: 当前电流前九次值[15:0]。 */
    } reg;
} PMIC_CURRENT0_PRE9_UNION;
#endif
#define PMIC_CURRENT0_PRE9_current_pre9_s0_START  (0)
#define PMIC_CURRENT0_PRE9_current_pre9_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CURRENT1_PRE9_UNION
 结构说明  : CURRENT1_PRE9 寄存器结构定义。地址偏移量:0x245，初值:0x00，宽度:8
 寄存器说明: current_pre9[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_pre9_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CURRENT1_PRE9_UNION;
#endif
#define PMIC_CURRENT1_PRE9_current_pre9_s1_START  (0)
#define PMIC_CURRENT1_PRE9_current_pre9_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_CURRENT_MOD_0_UNION
 结构说明  : OFFSET_CURRENT_MOD_0 寄存器结构定义。地址偏移量:0x246，初值:0x00，宽度:8
 寄存器说明: 电流偏置调整[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_mod_s0 : 8;  /* bit[0-7]: 电流偏置调整。
                                                                （先写低8bit，再写高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_OFFSET_CURRENT_MOD_0_UNION;
#endif
#define PMIC_OFFSET_CURRENT_MOD_0_offset_current_mod_s0_START  (0)
#define PMIC_OFFSET_CURRENT_MOD_0_offset_current_mod_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_CURRENT_MOD_1_UNION
 结构说明  : OFFSET_CURRENT_MOD_1 寄存器结构定义。地址偏移量:0x247，初值:0x00，宽度:8
 寄存器说明: 电流偏置调整[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_current_mod_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_CURRENT_MOD_1_UNION;
#endif
#define PMIC_OFFSET_CURRENT_MOD_1_offset_current_mod_s1_START  (0)
#define PMIC_OFFSET_CURRENT_MOD_1_offset_current_mod_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_VOLTAGE_MOD_0_UNION
 结构说明  : OFFSET_VOLTAGE_MOD_0 寄存器结构定义。地址偏移量:0x248，初值:0x00，宽度:8
 寄存器说明: 电压偏置调整[7:0]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_mod_s0 : 8;  /* bit[0-7]: 电压偏置调整。
                                                                （先写低8bit，再写高8bit；一组数据写操作结束后，下一组数据低8bit写操作与上组数据高8bit写操作至少间隔3个32kHz系统时钟周期。） */
    } reg;
} PMIC_OFFSET_VOLTAGE_MOD_0_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE_MOD_0_offset_voltage_mod_s0_START  (0)
#define PMIC_OFFSET_VOLTAGE_MOD_0_offset_voltage_mod_s0_END    (7)


/*****************************************************************************
 结构名    : PMIC_OFFSET_VOLTAGE_MOD_1_UNION
 结构说明  : OFFSET_VOLTAGE_MOD_1 寄存器结构定义。地址偏移量:0x249，初值:0x00，宽度:8
 寄存器说明: 电压偏置调整[15:8]寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  offset_voltage_mod_s1 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_OFFSET_VOLTAGE_MOD_1_UNION;
#endif
#define PMIC_OFFSET_VOLTAGE_MOD_1_offset_voltage_mod_s1_START  (0)
#define PMIC_OFFSET_VOLTAGE_MOD_1_offset_voltage_mod_s1_END    (7)


/*****************************************************************************
 结构名    : PMIC_COUL_RESERVE0_UNION
 结构说明  : COUL_RESERVE0 寄存器结构定义。地址偏移量:0x24A，初值:0x00，宽度:8
 寄存器说明: 库仑计模拟保留0寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  coul_reserve0 : 8;  /* bit[0-7]: 库仑计模拟寄存器保留。（软件不可占用） */
    } reg;
} PMIC_COUL_RESERVE0_UNION;
#endif
#define PMIC_COUL_RESERVE0_coul_reserve0_START  (0)
#define PMIC_COUL_RESERVE0_coul_reserve0_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED0_UNION
 结构说明  : CLJ_RESERVED0 寄存器结构定义。地址偏移量:0x24B，初值:0x00，宽度:8
 寄存器说明: 库仑计保留0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_reserve_1 : 8;  /* bit[0-7]: 库仑计模拟寄存器保留。 */
    } reg;
} PMIC_CLJ_RESERVED0_UNION;
#endif
#define PMIC_CLJ_RESERVED0_i_reserve_1_START  (0)
#define PMIC_CLJ_RESERVED0_i_reserve_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED1_UNION
 结构说明  : CLJ_RESERVED1 寄存器结构定义。地址偏移量:0x24C，初值:0x00，宽度:8
 寄存器说明: 库仑计保留1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  i_reserve_2 : 8;  /* bit[0-7]: 库仑计模拟寄存器保留。 */
    } reg;
} PMIC_CLJ_RESERVED1_UNION;
#endif
#define PMIC_CLJ_RESERVED1_i_reserve_2_START  (0)
#define PMIC_CLJ_RESERVED1_i_reserve_2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_RESERVED2_UNION
 结构说明  : CLJ_RESERVED2 寄存器结构定义。地址偏移量:0x24D，初值:0x00，宽度:8
 寄存器说明: 库仑计保留2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  v_reserve_1 : 8;  /* bit[0-7]: 库仑计模拟寄存器保留。 */
    } reg;
} PMIC_CLJ_RESERVED2_UNION;
#endif
#define PMIC_CLJ_RESERVED2_v_reserve_1_START  (0)
#define PMIC_CLJ_RESERVED2_v_reserve_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_PMU_SOFT_RST_UNION
 结构说明  : PMU_SOFT_RST 寄存器结构定义。地址偏移量:0x24E，初值:0x00，宽度:8
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
                                                     写入其他无效。 */
    } reg;
} PMIC_PMU_SOFT_RST_UNION;
#endif
#define PMIC_PMU_SOFT_RST_soft_rst_n_START  (0)
#define PMIC_PMU_SOFT_RST_soft_rst_n_END    (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_DEBUG_UNION
 结构说明  : CLJ_DEBUG 寄存器结构定义。地址偏移量:0x24F，初值:0x00，宽度:8
 寄存器说明: 库仑计DEBUG专用1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clj_debug_0     : 1;  /* bit[0]: 控制库仑计电流滤波电路第一级取反时钟。
                                                        0：无效；
                                                        1：有效。 */
        unsigned char  clj_debug_1     : 1;  /* bit[1]: 控制库仑计电压滤波电路第一级取反时钟。
                                                        0：无效；
                                                        1：有效。 */
        unsigned char  clj_debug_2     : 1;  /* bit[2]: 复用CK32_BT管脚，电压ADC模拟输出。 */
        unsigned char  clj_debug_3     : 1;  /* bit[3]: 复用CK32_GPS管脚，电流ADC模拟输出。 */
        unsigned char  cali_en_i       : 1;  /* bit[4]: 电流检测是否校准选择。
                                                        0：保持正常；
                                                        1：电流始终不进行检测校准。 */
        unsigned char  cali_en_i_force : 1;  /* bit[5]: 电流校准选择。
                                                        0：电流不强制校准；
                                                        1：电流强制校准。
                                                        以上功能均在clj_debug[4]=0时候作用。 */
        unsigned char  cali_en_v_force : 1;  /* bit[6]: 电压校准选择。
                                                        0：电压不强制校准；
                                                        1：电压强制校准。
                                                        以上功能均在clj_debug[7]=0时候作用。 */
        unsigned char  cali_en_v       : 1;  /* bit[7]: 电压检测是否校准选择。
                                                        0：保持正常；
                                                        1：电压检测始终不进行校准。 */
    } reg;
} PMIC_CLJ_DEBUG_UNION;
#endif
#define PMIC_CLJ_DEBUG_clj_debug_0_START      (0)
#define PMIC_CLJ_DEBUG_clj_debug_0_END        (0)
#define PMIC_CLJ_DEBUG_clj_debug_1_START      (1)
#define PMIC_CLJ_DEBUG_clj_debug_1_END        (1)
#define PMIC_CLJ_DEBUG_clj_debug_2_START      (2)
#define PMIC_CLJ_DEBUG_clj_debug_2_END        (2)
#define PMIC_CLJ_DEBUG_clj_debug_3_START      (3)
#define PMIC_CLJ_DEBUG_clj_debug_3_END        (3)
#define PMIC_CLJ_DEBUG_cali_en_i_START        (4)
#define PMIC_CLJ_DEBUG_cali_en_i_END          (4)
#define PMIC_CLJ_DEBUG_cali_en_i_force_START  (5)
#define PMIC_CLJ_DEBUG_cali_en_i_force_END    (5)
#define PMIC_CLJ_DEBUG_cali_en_v_force_START  (6)
#define PMIC_CLJ_DEBUG_cali_en_v_force_END    (6)
#define PMIC_CLJ_DEBUG_cali_en_v_START        (7)
#define PMIC_CLJ_DEBUG_cali_en_v_END          (7)


/*****************************************************************************
 结构名    : PMIC_CLJ_DEBUG_2_UNION
 结构说明  : CLJ_DEBUG_2 寄存器结构定义。地址偏移量:0x250，初值:0x00，宽度:8
 寄存器说明: 库仑计DEBUG专用2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  current_coul_always_off : 1;  /* bit[0]  : 电流计常关控制：
                                                                  0：正常功能；
                                                                  1：电流计常关。
                                                                  默认为1'b0。 */
        unsigned char  voltage_coul_always_off : 1;  /* bit[1]  : 电压计常关控制：
                                                                  0：正常功能；
                                                                  1：电压计常关。
                                                                  默认为1'b0。 */
        unsigned char  clj_debug_2_2           : 1;  /* bit[2]  : 库仑计门控时钟使能：
                                                                  0：开启门控使能；
                                                                  1：关闭门控使能。
                                                                  默认为1'b0。 */
        unsigned char  reserved                : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_CLJ_DEBUG_2_UNION;
#endif
#define PMIC_CLJ_DEBUG_2_current_coul_always_off_START  (0)
#define PMIC_CLJ_DEBUG_2_current_coul_always_off_END    (0)
#define PMIC_CLJ_DEBUG_2_voltage_coul_always_off_START  (1)
#define PMIC_CLJ_DEBUG_2_voltage_coul_always_off_END    (1)
#define PMIC_CLJ_DEBUG_2_clj_debug_2_2_START            (2)
#define PMIC_CLJ_DEBUG_2_clj_debug_2_2_END              (2)


/*****************************************************************************
 结构名    : PMIC_STATE_TEST_UNION
 结构说明  : STATE_TEST 寄存器结构定义。地址偏移量:0x251，初值:0x00，宽度:8
 寄存器说明: 库仑计DEBUG专用3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mstate   : 3;  /* bit[0-2]: bit[2:0]表示电压电流跳转状态。
                                                   000：CLJ_OFF(库仑计关闭状态)；
                                                   001：CLJ_ON(库仑计开启状态)；
                                                   010：OCV_DETE(库仑计ocv电压采样状态)；
                                                   011：CALIBRATION(库仑计自动校准状态)；
                                                   100：NORMAL_FUNC(库仑计正常工作状态)；
                                                   101：ECO_REFLASH(库仑计进入低功耗前一拍状态)；
                                                   110：ECO_POWER_OFF(库仑计进入低功耗状态)；
                                                   111：WAITTING(库仑计退出低功耗后一拍状态)。” */
        unsigned char  reserved : 5;  /* bit[3-7]: 保留。 */
    } reg;
} PMIC_STATE_TEST_UNION;
#endif
#define PMIC_STATE_TEST_mstate_START    (0)
#define PMIC_STATE_TEST_mstate_END      (2)


/*****************************************************************************
 结构名    : PMIC_CLJ_CTRL_REGS2_UNION
 结构说明  : CLJ_CTRL_REGS2 寄存器结构定义。地址偏移量:0x252，初值:0x01，宽度:8
 寄存器说明: 库仑计控制寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  coul_ctrl_onoff_reg  : 1;  /* bit[0]  : 库仑计开关控制寄存器：
                                                               0：库仑计关闭；
                                                               1：库仑计开启。 */
        unsigned char  reg_data_clr         : 1;  /* bit[1]  : 10组寄存器（电流，电压）检测值恢复初始值设置：
                                                               0：不恢复初始值；
                                                               1：恢复初始值。 */
        unsigned char  cali_auto_time       : 3;  /* bit[2-4]: 库仑计硬件校准周期可配：
                                                               000：15s；
                                                               001：30s；
                                                               010：60s；
                                                               011：2min；
                                                               100：4min；
                                                               101：8min；
                                                               110：16min；
                                                               111：32min */
        unsigned char  cali_auto_onoff_ctrl : 1;  /* bit[5]  : 库仑计硬件定时校准控制位：
                                                               0：不校准；
                                                               1：进入校准状态。 */
        unsigned char  reserved             : 2;  /* bit[6-7]: 保留。 */
    } reg;
} PMIC_CLJ_CTRL_REGS2_UNION;
#endif
#define PMIC_CLJ_CTRL_REGS2_coul_ctrl_onoff_reg_START   (0)
#define PMIC_CLJ_CTRL_REGS2_coul_ctrl_onoff_reg_END     (0)
#define PMIC_CLJ_CTRL_REGS2_reg_data_clr_START          (1)
#define PMIC_CLJ_CTRL_REGS2_reg_data_clr_END            (1)
#define PMIC_CLJ_CTRL_REGS2_cali_auto_time_START        (2)
#define PMIC_CLJ_CTRL_REGS2_cali_auto_time_END          (4)
#define PMIC_CLJ_CTRL_REGS2_cali_auto_onoff_ctrl_START  (5)
#define PMIC_CLJ_CTRL_REGS2_cali_auto_onoff_ctrl_END    (5)


/*****************************************************************************
 结构名    : PMIC_DEBUG_WRITE_PRO_UNION
 结构说明  : DEBUG_WRITE_PRO 寄存器结构定义。地址偏移量:0x253，初值:0x56，宽度:8
 寄存器说明: DEBUG寄存器写保护。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  debug_write_pro : 8;  /* bit[0-7]: CLJ_DEBUG和CLJ_DEBUG_2寄存器写保护功能：
                                                          0x56：保护DEBUG寄存器；
                                                          0xa9：解保护DEBUG寄存器。
                                                          (其他值，保持原有状态，不做动作) */
    } reg;
} PMIC_DEBUG_WRITE_PRO_UNION;
#endif
#define PMIC_DEBUG_WRITE_PRO_debug_write_pro_START  (0)
#define PMIC_DEBUG_WRITE_PRO_debug_write_pro_END    (7)




/****************************************************************************
                     (5/5) PMU_CODEC
 ****************************************************************************/
/*****************************************************************************
 结构名    : PMIC_CLK_EN_CFG_UNION
 结构说明  : CLK_EN_CFG 寄存器结构定义。地址偏移量:0x260，初值:0x00，宽度:8
 寄存器说明: 时钟使能配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dacl_en  : 1;  /* bit[0]  : DACL时钟使能：
                                                   0：关闭时钟；
                                                   1：打开时钟。 */
        unsigned char  dacr_en  : 1;  /* bit[1]  : DACR时钟使能：
                                                   0：关闭时钟；
                                                   1：打开时钟。 */
        unsigned char  adcl_en  : 1;  /* bit[2]  : ADCL时钟使能：
                                                   0：关闭时钟；
                                                   1：打开时钟。 */
        unsigned char  adcr_en  : 1;  /* bit[3]  : ADCR时钟使能：
                                                   0：关闭时钟；
                                                   1：打开时钟。 */
        unsigned char  sif_en   : 1;  /* bit[4]  : SIF时钟使能：
                                                   0：关闭时钟；
                                                   1：打开时钟。 */
        unsigned char  reserved : 3;  /* bit[5-7]: reserved */
    } reg;
} PMIC_CLK_EN_CFG_UNION;
#endif
#define PMIC_CLK_EN_CFG_dacl_en_START   (0)
#define PMIC_CLK_EN_CFG_dacl_en_END     (0)
#define PMIC_CLK_EN_CFG_dacr_en_START   (1)
#define PMIC_CLK_EN_CFG_dacr_en_END     (1)
#define PMIC_CLK_EN_CFG_adcl_en_START   (2)
#define PMIC_CLK_EN_CFG_adcl_en_END     (2)
#define PMIC_CLK_EN_CFG_adcr_en_START   (3)
#define PMIC_CLK_EN_CFG_adcr_en_END     (3)
#define PMIC_CLK_EN_CFG_sif_en_START    (4)
#define PMIC_CLK_EN_CFG_sif_en_END      (4)


/*****************************************************************************
 结构名    : PMIC_CLK_EDGE_CFG_UNION
 结构说明  : CLK_EDGE_CFG 寄存器结构定义。地址偏移量:0x261，初值:0x0F，宽度:8
 寄存器说明: 数模接口时钟沿选择。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dacl_clk_edge_sel : 1;  /* bit[0]  : DACL时钟沿选择：
                                                            0：反沿；
                                                            1：与模拟部分分频时钟同沿。 */
        unsigned char  dacr_clk_edge_sel : 1;  /* bit[1]  : DACR时钟沿选择：
                                                            0：反沿；
                                                            1：与模拟部分分频时钟同沿。 */
        unsigned char  adcl_clk_edge_sel : 1;  /* bit[2]  : ADCL时钟沿选择：
                                                            0：反沿；
                                                            1：与模拟部分分频时钟同沿。 */
        unsigned char  adcr_clk_edge_sel : 1;  /* bit[3]  : ADCR时钟沿选择：
                                                            0：反沿；
                                                            1：与模拟部分分频时钟同沿。 */
        unsigned char  reserved          : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_CLK_EDGE_CFG_UNION;
#endif
#define PMIC_CLK_EDGE_CFG_dacl_clk_edge_sel_START  (0)
#define PMIC_CLK_EDGE_CFG_dacl_clk_edge_sel_END    (0)
#define PMIC_CLK_EDGE_CFG_dacr_clk_edge_sel_START  (1)
#define PMIC_CLK_EDGE_CFG_dacr_clk_edge_sel_END    (1)
#define PMIC_CLK_EDGE_CFG_adcl_clk_edge_sel_START  (2)
#define PMIC_CLK_EDGE_CFG_adcl_clk_edge_sel_END    (2)
#define PMIC_CLK_EDGE_CFG_adcr_clk_edge_sel_START  (3)
#define PMIC_CLK_EDGE_CFG_adcr_clk_edge_sel_END    (3)


/*****************************************************************************
 结构名    : PMIC_LOOPBACK_CFG_UNION
 结构说明  : LOOPBACK_CFG 寄存器结构定义。地址偏移量:0x262，初值:0x00，宽度:8
 寄存器说明: 环回控制。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac_loopback     : 1;  /* bit[0]  : DAC通道数据环回控制：
                                                           1'b0：数据来自于串行接口；
                                                           1'b1：DACL并行数据来自于模拟ADCL并行输入，DACR并行数据来自于模拟ADCR并行输入 */
        unsigned char  adc_loopback     : 1;  /* bit[1]  : ADC通道数据环回控制：
                                                           1'b0：adc并行数据来自于模拟并行输入；
                                                           1'b1：adc并行数据来自于dac的并行输出 */
        unsigned char  sif_s2p_loopback : 1;  /* bit[2]  : SIF串行输出数据环回使能：
                                                           1：ADC串行输出环回到DAC串行输入
                                                           0：不环回 */
        unsigned char  dac_dem_din_sel  : 1;  /* bit[3]  : DAC通道输入数据选择：
                                                           1'b1: 选择减4后数据输入；
                                                           1'b0: 选择原输入输入； */
        unsigned char  reserved         : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_LOOPBACK_CFG_UNION;
#endif
#define PMIC_LOOPBACK_CFG_dac_loopback_START      (0)
#define PMIC_LOOPBACK_CFG_dac_loopback_END        (0)
#define PMIC_LOOPBACK_CFG_adc_loopback_START      (1)
#define PMIC_LOOPBACK_CFG_adc_loopback_END        (1)
#define PMIC_LOOPBACK_CFG_sif_s2p_loopback_START  (2)
#define PMIC_LOOPBACK_CFG_sif_s2p_loopback_END    (2)
#define PMIC_LOOPBACK_CFG_dac_dem_din_sel_START   (3)
#define PMIC_LOOPBACK_CFG_dac_dem_din_sel_END     (3)


/*****************************************************************************
 结构名    : PMIC_ANA_IRQ_SIG_STAT_UNION
 结构说明  : ANA_IRQ_SIG_STAT 寄存器结构定义。地址偏移量:0x263，初值:0x00，宽度:8
 寄存器说明: 模拟中断原始状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hs_mic_nor1_irq : 1;  /* bit[0]  : 正常模式下，COMP_H比较器中断，检测上升和下降沿均有效；
                                                          1：COMP_H比较器输出高，DETECT电平<0.85Vmicbias（默认值）；
                                                          0：COMP_H比较器输出低，DETECT电平>0.85Vmicbias（默认值）； */
        unsigned char  hs_mic_nor2_irq : 1;  /* bit[1]  : 正常模式下，COMP_L比较器中断，检测上升和下降沿均有效；
                                                          1：COMP_L比较器输出高，DETECT电平>600mV（默认值）；
                                                          0：COMP_L比较器输出低，DETECT电平<600mV（默认值）； */
        unsigned char  hs_mic_eco_irq  : 1;  /* bit[2]  : ECO模式下，COMP_ECO比较器中断，检测上升和下降沿均有效；
                                                          1：COMP_ECO比较器输出高，ECO模式下按键未按下，DETECT电平>100mV（默认值）；
                                                          0：COMP_ECO比较器输出低，ECO模式下按键按下，DETECT电平<100mV（默认值）； */
        unsigned char  hs_det_irq      : 1;  /* bit[3]  : 耳机插入检测中断，检测上升和下降沿均有效；
                                                          1：检测上升沿后，且读值为“1”时，表示有耳机插入；
                                                          0：检测下降沿后，且读值为“0”时，表示耳机拔出； */
        unsigned char  reserved        : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_ANA_IRQ_SIG_STAT_UNION;
#endif
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_nor1_irq_START  (0)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_nor1_irq_END    (0)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_nor2_irq_START  (1)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_nor2_irq_END    (1)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_eco_irq_START   (2)
#define PMIC_ANA_IRQ_SIG_STAT_hs_mic_eco_irq_END     (2)
#define PMIC_ANA_IRQ_SIG_STAT_hs_det_irq_START       (3)
#define PMIC_ANA_IRQ_SIG_STAT_hs_det_irq_END         (3)


/*****************************************************************************
 结构名    : PMIC_ANA_IRQM_REG0_UNION
 结构说明  : ANA_IRQM_REG0 寄存器结构定义。地址偏移量:0x264，初值:0x00，宽度:8
 寄存器说明: ANA_IRQ_REG中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ana_irq_mask : 8;  /* bit[0-7]: [7]:耳机拔出检测中断屏蔽位： 
                                                       [6]:耳机插入检测中断屏蔽位：
                                                       [5]:COMP_ECO比较器输出由高到低中断屏蔽位：
                                                       [4]:COMP_ECO比较器输出由低到高中断屏蔽位：
                                                       [3]:COMP_L比较器输出由高到低中断屏蔽位：
                                                       [2]:COMP_L比较器输出由低到高中断屏蔽位：
                                                       [1]:COMP_H比较器输出由高到低中断屏蔽位：
                                                       [0]:COMP_H比较器输出由低到高中断屏蔽位：
                                                       1：屏蔽中断；
                                                       0：正常输出中断。 */
    } reg;
} PMIC_ANA_IRQM_REG0_UNION;
#endif
#define PMIC_ANA_IRQM_REG0_ana_irq_mask_START  (0)
#define PMIC_ANA_IRQM_REG0_ana_irq_mask_END    (7)


/*****************************************************************************
 结构名    : PMIC_ANA_IRQ_REG0_UNION
 结构说明  : ANA_IRQ_REG0 寄存器结构定义。地址偏移量:0x265，初值:0x00，宽度:8
 寄存器说明: 模拟中断寄存器。0，写1清，读上报中断信息。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hs_mic_nor1_irq_pos : 1;  /* bit[0]: COMP_H比较器输出由低到高中断，检测高电平有效；
                                                            1：写1时清除中断，查询时表示中断有效；
                                                            0：查询时表示中断无效。 */
        unsigned char  hs_mic_nor1_irq_neg : 1;  /* bit[1]: COMP_H比较器输出由高到低中断，检测低电平有效；
                                                            1：写1时清除中断，查询时表示中断有效；
                                                            0：查询时表示中断无效。 */
        unsigned char  hs_mic_nor2_irq_pos : 1;  /* bit[2]: COMP_L比较器输出由低到高中断，检测高电平有效；
                                                            1：写1时清除中断，查询时表示中断有效；
                                                            0：查询时表示中断无效。 */
        unsigned char  hs_mic_nor2_irq_neg : 1;  /* bit[3]: COMP_L比较器输出由高到低中断，检测低电平有效；
                                                            1：写1时清除中断，查询时表示中断有效；
                                                            0：查询时表示中断无效。 */
        unsigned char  hs_mic_eco_irq_pos  : 1;  /* bit[4]: COMP_ECO比较器输出由低到高中断，检测高电平有效；
                                                            1：写1时清除中断，查询时表示中断有效；
                                                            0：查询时表示中断无效。 */
        unsigned char  hs_mic_eco_irq_neg  : 1;  /* bit[5]: COMP_ECO比较器输出由高到低中断，检测低电平有效；
                                                            1：写1时清除中断，查询时表示中断有效；
                                                            0：查询时表示中断无效。 */
        unsigned char  hs_det_irq_pos      : 1;  /* bit[6]: 耳机插入检测中断，检测高电平有效；
                                                            1：写1时清除中断，查询时表示中断有效；
                                                            0：查询时表示中断无效。 */
        unsigned char  hs_det_irq_neg      : 1;  /* bit[7]: 耳机拔出检测中断，检测低电平有效；
                                                            1：写1时清除中断，查询时表示中断有效；
                                                            0：查询时表示中断无效。 */
    } reg;
} PMIC_ANA_IRQ_REG0_UNION;
#endif
#define PMIC_ANA_IRQ_REG0_hs_mic_nor1_irq_pos_START  (0)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor1_irq_pos_END    (0)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor1_irq_neg_START  (1)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor1_irq_neg_END    (1)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor2_irq_pos_START  (2)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor2_irq_pos_END    (2)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor2_irq_neg_START  (3)
#define PMIC_ANA_IRQ_REG0_hs_mic_nor2_irq_neg_END    (3)
#define PMIC_ANA_IRQ_REG0_hs_mic_eco_irq_pos_START   (4)
#define PMIC_ANA_IRQ_REG0_hs_mic_eco_irq_pos_END     (4)
#define PMIC_ANA_IRQ_REG0_hs_mic_eco_irq_neg_START   (5)
#define PMIC_ANA_IRQ_REG0_hs_mic_eco_irq_neg_END     (5)
#define PMIC_ANA_IRQ_REG0_hs_det_irq_pos_START       (6)
#define PMIC_ANA_IRQ_REG0_hs_det_irq_pos_END         (6)
#define PMIC_ANA_IRQ_REG0_hs_det_irq_neg_START       (7)
#define PMIC_ANA_IRQ_REG0_hs_det_irq_neg_END         (7)


/*****************************************************************************
 结构名    : PMIC_DEB_CNT_HS_DET_CFG_UNION
 结构说明  : DEB_CNT_HS_DET_CFG 寄存器结构定义。地址偏移量:0x266，初值:0x14，宽度:8
 寄存器说明: hs_det_irq去抖配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  deb_cnt_hs_det_irq    : 5;  /* bit[0-4]: 去抖动周期计数器，以32k时钟计数
                                                                周期为1ms*计数值。
                                                                默认周期为20*1ms = 20ms
                                                                延时范围：0~32ms */
        unsigned char  bypass_deb_hs_det_irq : 1;  /* bit[5]  : 旁路hs_det_irq中断去抖动功能。
                                                                0：去抖动功能有效；
                                                                1：去抖动功能无效。 */
        unsigned char  reserved              : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_DEB_CNT_HS_DET_CFG_UNION;
#endif
#define PMIC_DEB_CNT_HS_DET_CFG_deb_cnt_hs_det_irq_START     (0)
#define PMIC_DEB_CNT_HS_DET_CFG_deb_cnt_hs_det_irq_END       (4)
#define PMIC_DEB_CNT_HS_DET_CFG_bypass_deb_hs_det_irq_START  (5)
#define PMIC_DEB_CNT_HS_DET_CFG_bypass_deb_hs_det_irq_END    (5)


/*****************************************************************************
 结构名    : PMIC_DEB_CNT_HS_MIC_CFG_UNION
 结构说明  : DEB_CNT_HS_MIC_CFG 寄存器结构定义。地址偏移量:0x267，初值:0x0A，宽度:8
 寄存器说明: hs_mic_irq去抖配置。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  deb_cnt_hs_mic_irq    : 5;  /* bit[0-4]: 去抖动周期计数器，以32k时钟计数
                                                                周期为1ms*计数值。
                                                                默认周期为10*1ms = 10ms
                                                                延时范围：0~32ms */
        unsigned char  bypass_deb_hs_mic_irq : 1;  /* bit[5]  : 旁路hs_mic_irq中断去抖动功能。
                                                                0：去抖动功能有效；
                                                                1：去抖动功能无效。 */
        unsigned char  reserved              : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_DEB_CNT_HS_MIC_CFG_UNION;
#endif
#define PMIC_DEB_CNT_HS_MIC_CFG_deb_cnt_hs_mic_irq_START     (0)
#define PMIC_DEB_CNT_HS_MIC_CFG_deb_cnt_hs_mic_irq_END       (4)
#define PMIC_DEB_CNT_HS_MIC_CFG_bypass_deb_hs_mic_irq_START  (5)
#define PMIC_DEB_CNT_HS_MIC_CFG_bypass_deb_hs_mic_irq_END    (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_DIG_RES02_UNION
 结构说明  : CODEC_DIG_RES02 寄存器结构定义。地址偏移量:0x268，初值:0x00，宽度:8
 寄存器说明: reserved。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved : 8;  /* bit[0-7]: reserved */
    } reg;
} PMIC_CODEC_DIG_RES02_UNION;
#endif


/*****************************************************************************
 结构名    : PMIC_CODEC_DIG_RES03_UNION
 结构说明  : CODEC_DIG_RES03 寄存器结构定义。地址偏移量:0x269，初值:0x00，宽度:8
 寄存器说明: reserved。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved : 8;  /* bit[0-7]: reserved */
    } reg;
} PMIC_CODEC_DIG_RES03_UNION;
#endif


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW01_UNION
 结构说明  : CODEC_ANA_RW01 寄存器结构定义。地址偏移量:0x26A，初值:0x3F，宽度:8
 寄存器说明: ADC通路PD信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  linepgar_pd : 1;  /* bit[0]  : LINEPGAR_PD控制信号(LINEPGAR_PD):
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  linepgal_pd : 1;  /* bit[1]  : LINEPGAL_PD控制信号(LINEPGAL_PD):
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  auxpga_pd   : 1;  /* bit[2]  : AUXPGA_PD控制信号(AUXPGAR_PD):
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  mainpga_pd  : 1;  /* bit[3]  : MAINPGA_PD控制信号(MAINPGAR_PD):
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  adcr_pd     : 1;  /* bit[4]  : ADCR PD控制信号(ADCR_PD):
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  adcl_pd     : 1;  /* bit[5]  : ADCL PD控制信号(ADCL_PD):
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  reserved    : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW01_UNION;
#endif
#define PMIC_CODEC_ANA_RW01_linepgar_pd_START  (0)
#define PMIC_CODEC_ANA_RW01_linepgar_pd_END    (0)
#define PMIC_CODEC_ANA_RW01_linepgal_pd_START  (1)
#define PMIC_CODEC_ANA_RW01_linepgal_pd_END    (1)
#define PMIC_CODEC_ANA_RW01_auxpga_pd_START    (2)
#define PMIC_CODEC_ANA_RW01_auxpga_pd_END      (2)
#define PMIC_CODEC_ANA_RW01_mainpga_pd_START   (3)
#define PMIC_CODEC_ANA_RW01_mainpga_pd_END     (3)
#define PMIC_CODEC_ANA_RW01_adcr_pd_START      (4)
#define PMIC_CODEC_ANA_RW01_adcr_pd_END        (4)
#define PMIC_CODEC_ANA_RW01_adcl_pd_START      (5)
#define PMIC_CODEC_ANA_RW01_adcl_pd_END        (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW02_UNION
 结构说明  : CODEC_ANA_RW02 寄存器结构定义。地址偏移量:0x26B，初值:0xFF，宽度:8
 寄存器说明: MICBIAS,MBHD信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ibias_pd     : 1;  /* bit[0]: 整个芯片的Ibias的上电控制信号(IBIAS_PD)：
                                                     0：正常工作；
                                                     1：PD； */
        unsigned char  reserved_0   : 1;  /* bit[1]: reserved */
        unsigned char  reserved_1   : 1;  /* bit[2]: reserved */
        unsigned char  reserved_2   : 1;  /* bit[3]: reserved */
        unsigned char  mbhd_buff_pd : 1;  /* bit[4]: MBHD buff上电控制信号(MBHD_BUFF_PD)：
                                                     0：正常工作；
                                                     1：PD */
        unsigned char  mbhd_comp_pd : 1;  /* bit[5]: MBHD comp上电控制信号(MBHD_COMP_PD)：
                                                     0：正常工作；
                                                     1：PD */
        unsigned char  hsmicb_pd    : 1;  /* bit[6]: 耳机MICBIAS上电控制信号(HSMICB_PD)：
                                                     0：正常工作；
                                                     1：PD */
        unsigned char  micb1_pd     : 1;  /* bit[7]: MICBIAS1上电控制信号(MICB1_PD)：
                                                     0：正常工作；
                                                     1：PD */
    } reg;
} PMIC_CODEC_ANA_RW02_UNION;
#endif
#define PMIC_CODEC_ANA_RW02_ibias_pd_START      (0)
#define PMIC_CODEC_ANA_RW02_ibias_pd_END        (0)
#define PMIC_CODEC_ANA_RW02_mbhd_buff_pd_START  (4)
#define PMIC_CODEC_ANA_RW02_mbhd_buff_pd_END    (4)
#define PMIC_CODEC_ANA_RW02_mbhd_comp_pd_START  (5)
#define PMIC_CODEC_ANA_RW02_mbhd_comp_pd_END    (5)
#define PMIC_CODEC_ANA_RW02_hsmicb_pd_START     (6)
#define PMIC_CODEC_ANA_RW02_hsmicb_pd_END       (6)
#define PMIC_CODEC_ANA_RW02_micb1_pd_START      (7)
#define PMIC_CODEC_ANA_RW02_micb1_pd_END        (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW03_UNION
 结构说明  : CODEC_ANA_RW03 寄存器结构定义。地址偏移量:0x26C，初值:0xFF，宽度:8
 寄存器说明: Headphone和MIXEROUT的PD信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0    : 1;  /* bit[0]: reserved */
        unsigned char  hsr_pd        : 1;  /* bit[1]: HeadphoneR上电控制信号(HSR_PD)：
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  hsl_pd        : 1;  /* bit[2]: HeadphoneL上电控制信号(HSL_PD)：
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  reserved_1    : 1;  /* bit[3]: reserved */
        unsigned char  mixout_hsr_pd : 1;  /* bit[4]: MIXOUT_HSR上电控制信号(MIXOUT_HSR_PD)：
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  mixout_hsl_pd : 1;  /* bit[5]: MIXOUT_HSL上电控制信号(MIXOUT_HSL_PD)：
                                                      0：正常工作；
                                                      1：PD */
        unsigned char  reserved_2    : 1;  /* bit[6]: reserved */
        unsigned char  reserved_3    : 1;  /* bit[7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW03_UNION;
#endif
#define PMIC_CODEC_ANA_RW03_hsr_pd_START         (1)
#define PMIC_CODEC_ANA_RW03_hsr_pd_END           (1)
#define PMIC_CODEC_ANA_RW03_hsl_pd_START         (2)
#define PMIC_CODEC_ANA_RW03_hsl_pd_END           (2)
#define PMIC_CODEC_ANA_RW03_mixout_hsr_pd_START  (4)
#define PMIC_CODEC_ANA_RW03_mixout_hsr_pd_END    (4)
#define PMIC_CODEC_ANA_RW03_mixout_hsl_pd_START  (5)
#define PMIC_CODEC_ANA_RW03_mixout_hsl_pd_END    (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW04_UNION
 结构说明  : CODEC_ANA_RW04 寄存器结构定义。地址偏移量:0x26D，初值:0x00，宽度:8
 寄存器说明: VREF电阻选择信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vrefsel     : 2;  /* bit[0-1]: VREF 电阻选择信号（VREFSEL<1:0>）;
                                                      00:无效；
                                                      01: 100kohm 分压电阻
                                                      10: 500kohm 分压电阻
                                                      11: 1kohm 分压电阻 */
        unsigned char  analog_loop : 1;  /* bit[2]  : CODEC模拟ADC_DAC环回控制信号(ANALOG_LOOP):
                                                      0:不环回；
                                                      1:环回；(ADCL_DACL,ADCR_DACR) */
        unsigned char  reserved    : 5;  /* bit[3-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW04_UNION;
#endif
#define PMIC_CODEC_ANA_RW04_vrefsel_START      (0)
#define PMIC_CODEC_ANA_RW04_vrefsel_END        (1)
#define PMIC_CODEC_ANA_RW04_analog_loop_START  (2)
#define PMIC_CODEC_ANA_RW04_analog_loop_END    (2)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW05_UNION
 结构说明  : CODEC_ANA_RW05 寄存器结构定义。地址偏移量:0x26E，初值:0x0F，宽度:8
 寄存器说明: LINEPGAL通路选择及增益控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  linepgal_mute : 1;  /* bit[0]  : LINEPGAL的通路MUTE信号(LINEPGAL_MUTE)；
                                                        0:通路正常工作；
                                                        1：通路MUTE; */
        unsigned char  linepgal_gain : 4;  /* bit[1-4]: LINEPGAL的通路增益信号(LINEPGAL_GAIN<3:0>)；
                                                        0000:-26dB；
                                                        0001:-24dB；
                                                        0010:-22dB；
                                                        0011:-20dB;
                                                        0100:-18dB;
                                                        0101:-15dB；
                                                        0110:-12dB；
                                                        0111:-9dB；
                                                        1000:-6dB；
                                                        1001:-3dB；
                                                        1010:0dB；
                                                        1011:-3dB;
                                                        1100:6dB;
                                                        1101:10dB；
                                                        1110:14dB；
                                                        1111:18dB。 */
        unsigned char  linepgal_sel  : 2;  /* bit[5-6]: LINEPGAL的通路选择信号(LINEPGAL_SEL<1:0>)；
                                                        01:LINEINL和LINEINR组成差分输入；
                                                        10:LINEINL和VCM组成单端输入；
                                                        other：等效于MUTE; */
        unsigned char  reserved      : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW05_UNION;
#endif
#define PMIC_CODEC_ANA_RW05_linepgal_mute_START  (0)
#define PMIC_CODEC_ANA_RW05_linepgal_mute_END    (0)
#define PMIC_CODEC_ANA_RW05_linepgal_gain_START  (1)
#define PMIC_CODEC_ANA_RW05_linepgal_gain_END    (4)
#define PMIC_CODEC_ANA_RW05_linepgal_sel_START   (5)
#define PMIC_CODEC_ANA_RW05_linepgal_sel_END     (6)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW06_UNION
 结构说明  : CODEC_ANA_RW06 寄存器结构定义。地址偏移量:0x26F，初值:0x0F，宽度:8
 寄存器说明: LINEPGAR通路选择及增益控制控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  linepgar_mute : 1;  /* bit[0]  : LINEPGAR的通路MUTE信号(LINEPGAR_MUTE)；
                                                        0:通路正常工作；
                                                        1：通路MUTE; */
        unsigned char  linepgar_gain : 4;  /* bit[1-4]: LINEPGAR的通路增益信号(LINEPGAR_GAIN<3:0>)；
                                                        0000:-26dB；
                                                        0001:-24dB；
                                                        0010:-22dB；
                                                        0011:-20dB;
                                                        0100:-18dB;
                                                        0101:-15dB；
                                                        0110:-12dB；
                                                        0111:-9dB；
                                                        1000:-6dB；
                                                        1001:-3dB；
                                                        1010:0dB；
                                                        1011:-3dB;
                                                        1100:6dB;
                                                        1101:10dB；
                                                        1110:14dB；
                                                        1111:18dB。 */
        unsigned char  linepgar_sel  : 2;  /* bit[5-6]: LINEPGAR的通路选择信号(LINEPGAR_SEL<1:0>)；
                                                        01:LINEINR和LINEINL组成差分输入；
                                                        10:LINEINR和VCM组成单端输入；
                                                        other：等效于MUTE; */
        unsigned char  reserved      : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW06_UNION;
#endif
#define PMIC_CODEC_ANA_RW06_linepgar_mute_START  (0)
#define PMIC_CODEC_ANA_RW06_linepgar_mute_END    (0)
#define PMIC_CODEC_ANA_RW06_linepgar_gain_START  (1)
#define PMIC_CODEC_ANA_RW06_linepgar_gain_END    (4)
#define PMIC_CODEC_ANA_RW06_linepgar_sel_START   (5)
#define PMIC_CODEC_ANA_RW06_linepgar_sel_END     (6)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW07_UNION
 结构说明  : CODEC_ANA_RW07 寄存器结构定义。地址偏移量:0x270，初值:0x05，宽度:8
 寄存器说明: AUXPGAR通路选择及增益控制控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  auxpga_sel        : 2;  /* bit[0-1]: AUXPGA的通路选择信号(AUXPGA_SEL<1:0>)；
                                                            00:PD有效
                                                            01:AUXMIC输入
                                                            10:选择VCM输入；
                                                            11：等效于MUTE； */
        unsigned char  auxpga_mute       : 1;  /* bit[2]  : AUXPGA的通路MUTE信号(AUXPGA_MUTE)；
                                                            0:通路正常工作；
                                                            1：通路MUTE; */
        unsigned char  auxpga_gain       : 3;  /* bit[3-5]: AUXPGA的通路增益信号(AUXPGA_GAIN<2:0>)；
                                                            000: 0dB；
                                                            001: 2dB；
                                                            010: 4dB；
                                                            011: 6dB；
                                                            100: 8dB；
                                                            101: 10dB；
                                                            110: 12dB；
                                                            111: 14dB； */
        unsigned char  auxpga_boost      : 1;  /* bit[6]  : AUXPGA的BOOST控制信号(AUXPGA_BOOST)；
                                                            0:正常增益；
                                                            1:26dB增益； */
        unsigned char  micpga_unlock_bps : 1;  /* bit[7]  : MICPGA防死锁控制信号（MICPGA_UNLOCK_BPS）；
                                                            0:防死锁有效；
                                                            1:防死锁无效； */
    } reg;
} PMIC_CODEC_ANA_RW07_UNION;
#endif
#define PMIC_CODEC_ANA_RW07_auxpga_sel_START         (0)
#define PMIC_CODEC_ANA_RW07_auxpga_sel_END           (1)
#define PMIC_CODEC_ANA_RW07_auxpga_mute_START        (2)
#define PMIC_CODEC_ANA_RW07_auxpga_mute_END          (2)
#define PMIC_CODEC_ANA_RW07_auxpga_gain_START        (3)
#define PMIC_CODEC_ANA_RW07_auxpga_gain_END          (5)
#define PMIC_CODEC_ANA_RW07_auxpga_boost_START       (6)
#define PMIC_CODEC_ANA_RW07_auxpga_boost_END         (6)
#define PMIC_CODEC_ANA_RW07_micpga_unlock_bps_START  (7)
#define PMIC_CODEC_ANA_RW07_micpga_unlock_bps_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW08_UNION
 结构说明  : CODEC_ANA_RW08 寄存器结构定义。地址偏移量:0x271，初值:0x01，宽度:8
 寄存器说明: MAINPGAR通路选择及增益控制控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mainpga_mute  : 1;  /* bit[0]  : MAINPGA的通路MUTE信号(MAINPGA_MUTE)；
                                                        0:通路正常工作；
                                                        1：通路MUTE; */
        unsigned char  mainpga_gain  : 3;  /* bit[1-3]: MAINPGA的通路增益信号(MAINPGA_GAIN<2:0>)；
                                                        000: 0dB；
                                                        001: 2dB；
                                                        010: 4dB；
                                                        011: 6dB；
                                                        100: 8dB；
                                                        101: 10dB；
                                                        110: 12dB；
                                                        111: 14dB； */
        unsigned char  mainpga_boost : 1;  /* bit[4]  : MAINPGA的BOOST控制信号(MAINPGA_BOOST)；
                                                        0:正常增益；
                                                        1:26dB增益； */
        unsigned char  mainpga_sel   : 2;  /* bit[5-6]: MAINPGA的通路选择信号(MAINPGA_SEL<1:0>)；
                                                        01：选择手机MIC输入；
                                                        10:选择耳机MIC输入；
                                                        others：等效于MUTE； */
        unsigned char  reserved      : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW08_UNION;
#endif
#define PMIC_CODEC_ANA_RW08_mainpga_mute_START   (0)
#define PMIC_CODEC_ANA_RW08_mainpga_mute_END     (0)
#define PMIC_CODEC_ANA_RW08_mainpga_gain_START   (1)
#define PMIC_CODEC_ANA_RW08_mainpga_gain_END     (3)
#define PMIC_CODEC_ANA_RW08_mainpga_boost_START  (4)
#define PMIC_CODEC_ANA_RW08_mainpga_boost_END    (4)
#define PMIC_CODEC_ANA_RW08_mainpga_sel_START    (5)
#define PMIC_CODEC_ANA_RW08_mainpga_sel_END      (6)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW09_UNION
 结构说明  : CODEC_ANA_RW09 寄存器结构定义。地址偏移量:0x272，初值:0x00，宽度:8
 寄存器说明: ADCR_MIXIN通路选择信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  adcr_mixin : 6;  /* bit[0-5]: ADCR_MIXIN的输入信号通路选择控制信号(ADCR_MIXIN<5:0>):
                                                     XXXXX1:AUXPGA的输出信号；
                                                     XXXX1X:MAINPGA的输出信号；
                                                     XXX1XX:LINEINR的输出信号；
                                                     XX1XXX:LINEINL的输出信号；
                                                     X1XXXX:DACR的输出信号；
                                                     1XXXXX:DACL的输出信号； */
        unsigned char  reserved   : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW09_UNION;
#endif
#define PMIC_CODEC_ANA_RW09_adcr_mixin_START  (0)
#define PMIC_CODEC_ANA_RW09_adcr_mixin_END    (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW10_UNION
 结构说明  : CODEC_ANA_RW10 寄存器结构定义。地址偏移量:0x273，初值:0x00，宽度:8
 寄存器说明: ADCL_MIXIN通路选择信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  adcl_mixin : 6;  /* bit[0-5]: ADCL_MIXIN的输入信号通路选择控制信号(ADCL_MIXIN<5:0>):
                                                     XXXXX1:AUXPGA的输出信号；
                                                     XXXX1X:MAINPGA的输出信号；
                                                     XXX1XX:LINEINR的输出信号；
                                                     XX1XXX:LINEINL的输出信号；
                                                     X1XXXX:DACR的输出信号；
                                                     1XXXXX:DACL的输出信号； */
        unsigned char  reserved   : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW10_UNION;
#endif
#define PMIC_CODEC_ANA_RW10_adcl_mixin_START  (0)
#define PMIC_CODEC_ANA_RW10_adcl_mixin_END    (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW11_UNION
 结构说明  : CODEC_ANA_RW11 寄存器结构定义。地址偏移量:0x274，初值:0x12，宽度:8
 寄存器说明: ADCL时序控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  adcl_dwa_bps     : 1;  /* bit[0]  : ADCL通路DWA Baypass控制信号(ADCL_DWA_BPS):
                                                           0:打开DWA；
                                                           1:Baypass DWA功能； */
        unsigned char  adcl_flstn       : 2;  /* bit[1-2]: ADCL的FlashADC的参考电压选择信号(ADCL_FLSTN<1:0>):
                                                           00:参考电压为1.05倍；
                                                           01:参考电压为1倍；
                                                           10:参考电压为0.95倍；
                                                           11:参考电压为0.9倍； */
        unsigned char  adcl_dac_bias    : 2;  /* bit[3-4]: ADCL的反馈DAC的偏置选择信号(ADCL_DAC_BIAS<1:0>):
                                                           00:偏置电压为0.9倍；
                                                           01:偏置电压为0.95倍；
                                                           10:偏置电压为1倍；
                                                           11:偏置电压为1.1倍； */
        unsigned char  adcl_clk_delay_0 : 1;  /* bit[5]  : ADCL_CLK_DELAY<0>:ADCL内部CLK时序(CLK_TIMING_SEL)；
                                                           0: 默认延时
                                                           1: 增加延时 */
        unsigned char  adcl_clk_delay_1 : 1;  /* bit[6]  : ADCL_CLK_DELAY<1>:ADCL内部CLK延时(CLK_DELAY_SEL)；
                                                           0: 默认延时
                                                           1: 增加延时 */
        unsigned char  adcl_clk_delay_2 : 1;  /* bit[7]  : ADCL_CLK_DELAY<2>:ADCL的输出数据的时(DOUT_TIMING_SEL)；
                                                           0: 默认延时
                                                           1: 增加延时 */
    } reg;
} PMIC_CODEC_ANA_RW11_UNION;
#endif
#define PMIC_CODEC_ANA_RW11_adcl_dwa_bps_START      (0)
#define PMIC_CODEC_ANA_RW11_adcl_dwa_bps_END        (0)
#define PMIC_CODEC_ANA_RW11_adcl_flstn_START        (1)
#define PMIC_CODEC_ANA_RW11_adcl_flstn_END          (2)
#define PMIC_CODEC_ANA_RW11_adcl_dac_bias_START     (3)
#define PMIC_CODEC_ANA_RW11_adcl_dac_bias_END       (4)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_0_START  (5)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_0_END    (5)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_1_START  (6)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_1_END    (6)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_2_START  (7)
#define PMIC_CODEC_ANA_RW11_adcl_clk_delay_2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW12_UNION
 结构说明  : CODEC_ANA_RW12 寄存器结构定义。地址偏移量:0x275，初值:0x12，宽度:8
 寄存器说明: ADCR时序控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  adcr_dwa_bps     : 1;  /* bit[0]  : ADCR通路DWA Baypass控制信号(ADCR_DWA_BPS):
                                                           0:打开DWA；
                                                           1:Baypass DWA功能； */
        unsigned char  adcr_flstn       : 2;  /* bit[1-2]: ADCR的FlashADC的参考电压选择信号(ADCR_FLSTN<1:0>):
                                                           00:参考电压为1.05倍；
                                                           01:参考电压为1倍；
                                                           10:参考电压为0.95倍；
                                                           11:参考电压为0.9倍； */
        unsigned char  adcr_dac_bias    : 2;  /* bit[3-4]: ADCR的反馈DAC的偏置选择信号(ADCR_DAC_BIAS<1:0>):
                                                           00:偏置电压为0.9倍；
                                                           01:偏置电压为0.95倍；
                                                           10:偏置电压为1倍；
                                                           11:偏置电压为1.1倍； */
        unsigned char  adcr_clk_delay_0 : 1;  /* bit[5]  : ADCR_CLK_DELAY<0>:ADCR内部CLK时序(CLK_TIMING_SEL)；
                                                           0: 默认延时
                                                           1: 增加延时 */
        unsigned char  adcr_clk_delay_1 : 1;  /* bit[6]  : ADCR_CLK_DELAY<1>:ADCR内部CLK延时(CLK_DELAY_SEL)；
                                                           0: 默认延时
                                                           1: 增加延时 */
        unsigned char  adcr_clk_delay_2 : 1;  /* bit[7]  : 
                                                           ADCR_CLK_DELAY<2>:ADCR的输出数据的时序(DOUT_TIMING_SEL)；
                                                           0: 默认延时
                                                           1: 增加延时 */
    } reg;
} PMIC_CODEC_ANA_RW12_UNION;
#endif
#define PMIC_CODEC_ANA_RW12_adcr_dwa_bps_START      (0)
#define PMIC_CODEC_ANA_RW12_adcr_dwa_bps_END        (0)
#define PMIC_CODEC_ANA_RW12_adcr_flstn_START        (1)
#define PMIC_CODEC_ANA_RW12_adcr_flstn_END          (2)
#define PMIC_CODEC_ANA_RW12_adcr_dac_bias_START     (3)
#define PMIC_CODEC_ANA_RW12_adcr_dac_bias_END       (4)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_0_START  (5)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_0_END    (5)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_1_START  (6)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_1_END    (6)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_2_START  (7)
#define PMIC_CODEC_ANA_RW12_adcr_clk_delay_2_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW13_UNION
 结构说明  : CODEC_ANA_RW13 寄存器结构定义。地址偏移量:0x276，初值:0x12，宽度:8
 寄存器说明: MIXOUT_HSL，MIXOUT_HSR通路选择信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mixout_hsr : 4;  /* bit[0-3]: MIXOUT_HSR的输入信号通路选择控制信号(MIXOUT_HSR<3:0>):
                                                     XXX1:LINEINR的输出信号；
                                                     XX1X:LINEINL的输出信号；
                                                     X1XX:DACR的输出信号；
                                                     1XXX:DACL的输出信号； */
        unsigned char  mixout_hsl : 4;  /* bit[4-7]: MIXOUT_HSL的输入信号通路选择控制信号(MIXOUT_HSL<3:0>):
                                                     XXX1:LINEINR的输出信号；
                                                     XX1X:LINEINL的输出信号；
                                                     X1XX:DACR的输出信号；
                                                     1XXX:DACL的输出信号； */
    } reg;
} PMIC_CODEC_ANA_RW13_UNION;
#endif
#define PMIC_CODEC_ANA_RW13_mixout_hsr_START  (0)
#define PMIC_CODEC_ANA_RW13_mixout_hsr_END    (3)
#define PMIC_CODEC_ANA_RW13_mixout_hsl_START  (4)
#define PMIC_CODEC_ANA_RW13_mixout_hsl_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW14_UNION
 结构说明  : CODEC_ANA_RW14 寄存器结构定义。地址偏移量:0x277，初值:0x13，宽度:8
 寄存器说明: MIXOUT_EAR通路选择信号。，增益选择信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cr_mixf    : 4;  /* bit[0-3]: MIXOUT_EAR的0dB,-6dB选择控制信号(CR_MIXF<3:0>):
                                                     XXX1:LINEINR支路0dB；XXX0:LINEINR支路-6dB
                                                     XX1X:LINEINL支路0dB；XX0X:LINEINL支路-6dB
                                                     X1XX:DACR支路0dB；X0XX:DACR支路-6dB
                                                     1XXX:DACL支路0dB；0XXX:DACL支路-6dB； */
        unsigned char  mixout_ear : 4;  /* bit[4-7]: MIXOUT_EAR的输入信号通路选择控制信号(MIXOUT_EAR<3:0>):
                                                     XXX1:LINEINR的输出信号；
                                                     XX1X:LINEINL的输出信号；
                                                     X1XX:DACR的输出信号；
                                                     1XXX:DACL的输出信号； */
    } reg;
} PMIC_CODEC_ANA_RW14_UNION;
#endif
#define PMIC_CODEC_ANA_RW14_cr_mixf_START     (0)
#define PMIC_CODEC_ANA_RW14_cr_mixf_END       (3)
#define PMIC_CODEC_ANA_RW14_mixout_ear_START  (4)
#define PMIC_CODEC_ANA_RW14_mixout_ear_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW15_UNION
 结构说明  : CODEC_ANA_RW15 寄存器结构定义。地址偏移量:0x278，初值:0x50，宽度:8
 寄存器说明: DACICELL电流控制信号。，ChargePump死区时间控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cp_dtc_3   : 2;  /* bit[0-1]: Charge Pump三相时钟死区时间控制信号（CP_DTC_3<1:0>)；
                                                     00:10ns（默认）
                                                     01:20ns
                                                     10:30ns
                                                     11:50ns */
        unsigned char  cp_dtc_2   : 2;  /* bit[2-3]: Charge Pump两相时钟死区时间控制信号（CP_DTC_2<1:0>)；
                                                     00:10ns（默认）
                                                     01:20ns
                                                     10:30ns
                                                     11:50ns */
        unsigned char  dacr_ictrl : 2;  /* bit[4-5]: DACR ICELLS的电流控制信号(DACR_ICTRL<1:0>):
                                                     00:电流变为0.9倍；
                                                     01:正常电流；
                                                     10:电流变为1.1倍；
                                                     11:电流变为1.2倍； */
        unsigned char  dacl_ictrl : 2;  /* bit[6-7]: DACL ICELLS的电流控制信号(DACL_ICTRL<1:0>):
                                                     00:电流变为0.9倍；
                                                     01:正常电流；
                                                     10:电流变为1.1倍；
                                                     11:电流变为1.2倍； */
    } reg;
} PMIC_CODEC_ANA_RW15_UNION;
#endif
#define PMIC_CODEC_ANA_RW15_cp_dtc_3_START    (0)
#define PMIC_CODEC_ANA_RW15_cp_dtc_3_END      (1)
#define PMIC_CODEC_ANA_RW15_cp_dtc_2_START    (2)
#define PMIC_CODEC_ANA_RW15_cp_dtc_2_END      (3)
#define PMIC_CODEC_ANA_RW15_dacr_ictrl_START  (4)
#define PMIC_CODEC_ANA_RW15_dacr_ictrl_END    (5)
#define PMIC_CODEC_ANA_RW15_dacl_ictrl_START  (6)
#define PMIC_CODEC_ANA_RW15_dacl_ictrl_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW16_UNION
 结构说明  : CODEC_ANA_RW16 寄存器结构定义。地址偏移量:0x279，初值:0x80，宽度:8
 寄存器说明: Headphonesoft使能信号。，ChargePump控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cp_dr_ctrl : 2;  /* bit[0-1]: Change Pump 导通开关驱动能力选择（CP_DR_CTRL<1:0>);
                                                     00: 最小驱动（默认）
                                                     01: 较小驱动
                                                     10: 较大驱动
                                                     11:最大驱动 */
        unsigned char  classg_ref : 2;  /* bit[2-3]: CLASSG模式下输入幅度的参考选择信号(CLASSG_REF<1:0>):
                                                     00: VREF为200mV；
                                                     01: VREF为400mV；
                                                     10: VREF为300mV；
                                                     11: VREF为500mV； */
        unsigned char  cp_mode    : 2;  /* bit[4-5]: Charge Pump的输出电压的模式控制信号(CP_MODE<1:0>):
                                                     00:固定输出正负1.8V的电源；
                                                     01:固定输出正负0.9V的电源；
                                                     10:CLASSG模式，输出电压随输入信号可调；
                                                     11:CLASSG模式，输出电压随输入信号可调； */
        unsigned char  en_cp_mode : 1;  /* bit[6]  : Headphone正常模式，CLASSG模式偏置管调整信号（EN_CP_MODE）:
                                                     0: 偏置管标准模式；
                                                     1: 偏置管叠加模式； */
        unsigned char  hp_soft_en : 1;  /* bit[7]  : Headphone soft使能控制信号(HP_SOFT_EN):
                                                     0: 正常使能；
                                                     1: soft使能； */
    } reg;
} PMIC_CODEC_ANA_RW16_UNION;
#endif
#define PMIC_CODEC_ANA_RW16_cp_dr_ctrl_START  (0)
#define PMIC_CODEC_ANA_RW16_cp_dr_ctrl_END    (1)
#define PMIC_CODEC_ANA_RW16_classg_ref_START  (2)
#define PMIC_CODEC_ANA_RW16_classg_ref_END    (3)
#define PMIC_CODEC_ANA_RW16_cp_mode_START     (4)
#define PMIC_CODEC_ANA_RW16_cp_mode_END       (5)
#define PMIC_CODEC_ANA_RW16_en_cp_mode_START  (6)
#define PMIC_CODEC_ANA_RW16_en_cp_mode_END    (6)
#define PMIC_CODEC_ANA_RW16_hp_soft_en_START  (7)
#define PMIC_CODEC_ANA_RW16_hp_soft_en_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW17_UNION
 结构说明  : CODEC_ANA_RW17 寄存器结构定义。地址偏移量:0x27A，初值:0x20，宽度:8
 寄存器说明: HeadphoneL增益控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hsl_min_gain : 1;  /* bit[0]  : HeadphoneL的通路最小增益选择信号(HSL_MIN_GAIN)；
                                                       0:最小增益(-26dB)无效；
                                                       1：最小增益(-26dB)有效; */
        unsigned char  hsl_gain     : 4;  /* bit[1-4]: HeadphoneL的通路增益信号(HSL_GAIN<3:0>)；
                                                       0000:-20dB；
                                                       0001:-18dB；
                                                       0010：-16.5dB；
                                                       0011: -15dB;
                                                       0100:-13.5dB;
                                                       0101:-12dB;
                                                       0110:-10.5dB;
                                                       0111:-9.5dB;
                                                       1000:-8.5dB;
                                                       1001:-7.5dB;
                                                       1010:-6.5dB;
                                                       1011:-5.5dB;
                                                       1100:-4.5dB;
                                                       1101:-3dB;
                                                       1110: -1.5dB;
                                                       1111:0dB; */
        unsigned char  hsl_mute     : 1;  /* bit[5]  : HeadphoneL的通路MUTE信号(HSL_MUTE)；
                                                       0:通路正常工作；
                                                       1：通路MUTE; */
        unsigned char  HS_LIT_LP_L  : 1;  /* bit[6]  : HeadphoneL的POP小环路MUTE信号(HS_LIT_LP_L)；
                                                       0：小环路MUTE不使能 ，此时小环路的mute由hsl_mute控制；
                                                       1：小环路MUTE使能; */
        unsigned char  reserved     : 1;  /* bit[7]  : 
                                                       reserved */
    } reg;
} PMIC_CODEC_ANA_RW17_UNION;
#endif
#define PMIC_CODEC_ANA_RW17_hsl_min_gain_START  (0)
#define PMIC_CODEC_ANA_RW17_hsl_min_gain_END    (0)
#define PMIC_CODEC_ANA_RW17_hsl_gain_START      (1)
#define PMIC_CODEC_ANA_RW17_hsl_gain_END        (4)
#define PMIC_CODEC_ANA_RW17_hsl_mute_START      (5)
#define PMIC_CODEC_ANA_RW17_hsl_mute_END        (5)
#define PMIC_CODEC_ANA_RW17_HS_LIT_LP_L_START   (6)
#define PMIC_CODEC_ANA_RW17_HS_LIT_LP_L_END     (6)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW18_UNION
 结构说明  : CODEC_ANA_RW18 寄存器结构定义。地址偏移量:0x27B，初值:0x20，宽度:8
 寄存器说明: HeadphonR增益控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hsr_min_gain : 1;  /* bit[0]  : HeadphoneR的通路最小增益选择信号(HSR_MIN_GAIN)；
                                                       0:最小增益(-26dB)无效；
                                                       1：最小增益(-26dB)有效; */
        unsigned char  hsr_gain     : 4;  /* bit[1-4]: HeadphoneR的通路增益信号(HSR_GAIN<3:0>)；
                                                       0000:-20dB；
                                                       0001:-18dB；
                                                       0010：-16.5dB；
                                                       0011: -15dB;
                                                       0100:-13.5dB;
                                                       0101:-12dB;
                                                       0110:-10.5dB;
                                                       0111:-9.5dB;
                                                       1000:-8.5dB;
                                                       1001:-7.5dB;
                                                       1010:-6.5dB;
                                                       1011:-5.5dB;
                                                       1100:-4.5dB;
                                                       1101:-3dB;
                                                       1110: -1.5dB;
                                                       1111:0dB; */
        unsigned char  hsr_mute     : 1;  /* bit[5]  : HeadphoneR的通路MUTE信号(HSR_MUTE)；
                                                       0:通路正常工作；
                                                       1：通路MUTE; */
        unsigned char  HS_LIT_LP_R  : 1;  /* bit[6]  : HeadphoneR的POP小环路MUTE信号(HS_LIT_LP_R)；
                                                       0：小环路MUTE不使能 ，此时小环路的mute由hsl_mute控制；
                                                       1：小环路MUTE使能; */
        unsigned char  reserved     : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW18_UNION;
#endif
#define PMIC_CODEC_ANA_RW18_hsr_min_gain_START  (0)
#define PMIC_CODEC_ANA_RW18_hsr_min_gain_END    (0)
#define PMIC_CODEC_ANA_RW18_hsr_gain_START      (1)
#define PMIC_CODEC_ANA_RW18_hsr_gain_END        (4)
#define PMIC_CODEC_ANA_RW18_hsr_mute_START      (5)
#define PMIC_CODEC_ANA_RW18_hsr_mute_END        (5)
#define PMIC_CODEC_ANA_RW18_HS_LIT_LP_R_START   (6)
#define PMIC_CODEC_ANA_RW18_HS_LIT_LP_R_END     (6)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW19_UNION
 结构说明  : CODEC_ANA_RW19 寄存器结构定义。地址偏移量:0x27C，初值:0x21，宽度:8
 寄存器说明: Earphone增益控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ear_cm_ctrl : 1;  /* bit[0]  : EAR的共模控制信号(EAR_CM_CTRL):
                                                      0:输出经过500欧姆电阻到VCM；
                                                      1:输出经过30K欧姆电阻到VCM； */
        unsigned char  ear_gain    : 4;  /* bit[1-4]: EAR的通路增益信号(EAR_GAIN<5:0>)；
                                                      0000:-20dB；
                                                      0001:-18dB；
                                                      0010：-16dB；
                                                      0011: -14dB;
                                                      0100:-12dB;
                                                      0101:-10dB;
                                                      0110:-8dB;
                                                      0111:-6dB;
                                                      1000:-4dB;
                                                      1001:-2dB;
                                                      1010:-0dB;
                                                      1011:2dB;
                                                      1100:4dB;
                                                      1101:5dB;
                                                      1110:6dB;
                                                      1111:7dB。 */
        unsigned char  ear_mute    : 1;  /* bit[5]  : EAR的通路MUTE信号(EAR_MUTE)；
                                                      0:通路正常工作；
                                                      1：通路MUTE; */
        unsigned char  reserved    : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW19_UNION;
#endif
#define PMIC_CODEC_ANA_RW19_ear_cm_ctrl_START  (0)
#define PMIC_CODEC_ANA_RW19_ear_cm_ctrl_END    (0)
#define PMIC_CODEC_ANA_RW19_ear_gain_START     (1)
#define PMIC_CODEC_ANA_RW19_ear_gain_END       (4)
#define PMIC_CODEC_ANA_RW19_ear_mute_START     (5)
#define PMIC_CODEC_ANA_RW19_ear_mute_END       (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW20_UNION
 结构说明  : CODEC_ANA_RW20 寄存器结构定义。地址偏移量:0x27D，初值:0x40，宽度:8
 寄存器说明: POP音延时控制信号。，ramp产生电路控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  pop_ramp_ct_2_0 : 3;  /* bit[0-2]: ramp产生电路,输入clk选择(POP_RAMP_CT<2:0>：
                                                          000：48k
                                                          001：48k/2
                                                          010：48k/4
                                                          011：48k/8
                                                          1*0：48k/16
                                                          1*1：48k/32 */
        unsigned char  pop_ramp_ct_3   : 1;  /* bit[3]  : ramp产生电路,脉宽控制(POP_RAMP_CT<3>)：
                                                          0：normal；（正常使用）
                                                          1：mormal*1.5 */
        unsigned char  pop_ramp_ct_4   : 1;  /* bit[4]  : ramp产生电路,cap选择(POP_RAMP_CT<4>)：
                                                          0：normal；（正常使用）
                                                          1：mormal*1.5 */
        unsigned char  clk_dl          : 3;  /* bit[5-7]: POP音上电延时控制(CLK_DL)：(clk_sel=0，括号中为clk_sel=1)
                                                          
                                                          000：7.98m (15.96m )
                                                          001：13.34m (26.68m)
                                                          010：18.68m (37.36m)
                                                          011：23.98m (47.96m)
                                                          100：29.28m (58.56m)
                                                          101：34.58m (69.16m)
                                                          110：39.88m (79.96m)
                                                          111：45.18m (90.36m) */
    } reg;
} PMIC_CODEC_ANA_RW20_UNION;
#endif
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_2_0_START  (0)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_2_0_END    (2)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_3_START    (3)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_3_END      (3)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_4_START    (4)
#define PMIC_CODEC_ANA_RW20_pop_ramp_ct_4_END      (4)
#define PMIC_CODEC_ANA_RW20_clk_dl_START           (5)
#define PMIC_CODEC_ANA_RW20_clk_dl_END             (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW21_UNION
 结构说明  : CODEC_ANA_RW21 寄存器结构定义。地址偏移量:0x27E，初值:0x10，宽度:8
 寄存器说明: 防POP电路控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rst_n_r        : 1;  /* bit[0]  : RST HP右通路 POP音控制模块(RST_N_R)：
                                                         0：RST 有效
                                                         1：Normal； */
        unsigned char  rst_n_l        : 1;  /* bit[1]  : RST HP左通路 POP音控制模块(RST_N_L)：
                                                         0：RST 有效
                                                         1：Normal； */
        unsigned char  pop_dis        : 1;  /* bit[2]  : POP音控制模块byass选项(POP_DIS)：
                                                         0：enable POP音控制电路；
                                                         1：bypass POP音控制电路； */
        unsigned char  clk_sel        : 1;  /* bit[3]  : POP音延时控制电路,clk选择(CLK_SEL)：（与1E7<7:5>配合使用）
                                                         0:188Hz；
                                                         1:94Hz； */
        unsigned char  pdd_en         : 1;  /* bit[4]  : HP PD信号delay 控制(PDD_EN)：
                                                         0：PD信号直接输出到HP模块；
                                                         1：PD信号经过delay输出到HP模块；（正常模式） */
        unsigned char  pop_new_bypass : 1;  /* bit[5]  : 新POP音解决方案的BYPASS信号：
                                                         0：新方案使能；
                                                         1：新方案不使能； */
        unsigned char  reserved       : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW21_UNION;
#endif
#define PMIC_CODEC_ANA_RW21_rst_n_r_START         (0)
#define PMIC_CODEC_ANA_RW21_rst_n_r_END           (0)
#define PMIC_CODEC_ANA_RW21_rst_n_l_START         (1)
#define PMIC_CODEC_ANA_RW21_rst_n_l_END           (1)
#define PMIC_CODEC_ANA_RW21_pop_dis_START         (2)
#define PMIC_CODEC_ANA_RW21_pop_dis_END           (2)
#define PMIC_CODEC_ANA_RW21_clk_sel_START         (3)
#define PMIC_CODEC_ANA_RW21_clk_sel_END           (3)
#define PMIC_CODEC_ANA_RW21_pdd_en_START          (4)
#define PMIC_CODEC_ANA_RW21_pdd_en_END            (4)
#define PMIC_CODEC_ANA_RW21_pop_new_bypass_START  (5)
#define PMIC_CODEC_ANA_RW21_pop_new_bypass_END    (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW22_UNION
 结构说明  : CODEC_ANA_RW22 寄存器结构定义。地址偏移量:0x27F，初值:0x00，宽度:8
 寄存器说明: HSMICBIAS，MICBIAS1输出偏置电压控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  micb1_adj  : 3;  /* bit[0-2]: MICBIAS1输出偏置电压控制信号(MICB1_ADJ<2:0>):
                                                     000: 2.1V；
                                                     001: 2.2V；
                                                     010: 2.3V；
                                                     011: 2.4V；
                                                     100: 2.5V；
                                                     101: 2.6V；
                                                     110: 2.7V；
                                                     111: 2.8V； */
        unsigned char  hsmicb_adj : 3;  /* bit[3-5]: HSMICBIAS输出偏置电压控制信号(HSMICB_ADJ<2:0>):
                                                     000: 2.1V；
                                                     001: 2.2V；
                                                     010: 2.3V；
                                                     011: 2.4V；
                                                     100: 2.5V；
                                                     101: 2.6V；
                                                     110: 2.7V；
                                                     111: 2.8V； */
        unsigned char  reserved   : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW22_UNION;
#endif
#define PMIC_CODEC_ANA_RW22_micb1_adj_START   (0)
#define PMIC_CODEC_ANA_RW22_micb1_adj_END     (2)
#define PMIC_CODEC_ANA_RW22_hsmicb_adj_START  (3)
#define PMIC_CODEC_ANA_RW22_hsmicb_adj_END    (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW23_UNION
 结构说明  : CODEC_ANA_RW23 寄存器结构定义。地址偏移量:0x280，初值:0x08，宽度:8
 寄存器说明: HSD_CTRL<2:0>,HSMICBIAS,MICBIAS1放电使能信号。，MBHD使能信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mbhd_eco_en  : 1;  /* bit[0]  : ECO模式下，MBHD使能信号(MBHD_ECO_EN):
                                                       0:不使能；
                                                       1:使能； */
        unsigned char  micb1_dschg  : 1;  /* bit[1]  : MICBIAS1放电使能信号(MICB1_DSCHG):
                                                       0:不使能；
                                                       1:使能； */
        unsigned char  hsmicb_dschg : 1;  /* bit[2]  : HSMICBIAS放电使能信号(HSMICB_DSCHG):
                                                       0:不使能；
                                                       1:使能； */
        unsigned char  hsd_ctrl_0   : 1;  /* bit[3]  : HSD EN 控制(HSD_CTRL<0>)：
                                                       0: HS 模块不使能；
                                                       1：HS 模块使能；（正常模式） */
        unsigned char  hsd_ctrl_1   : 1;  /* bit[4]  : HSD INV 控制(HSD_CTRL<1>)：
                                                       0: HS 输出反向；（正常模式）
                                                       1：HS 输出不反向； */
        unsigned char  hsd_ctrl_2   : 1;  /* bit[5]  : HSD POLLDOWN 控制（HSD_CTRL<2>)：
                                                       0: Headset 模块正常工作；（正常模式）
                                                       1：HSD 输入下拉； */
        unsigned char  reserved     : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW23_UNION;
#endif
#define PMIC_CODEC_ANA_RW23_mbhd_eco_en_START   (0)
#define PMIC_CODEC_ANA_RW23_mbhd_eco_en_END     (0)
#define PMIC_CODEC_ANA_RW23_micb1_dschg_START   (1)
#define PMIC_CODEC_ANA_RW23_micb1_dschg_END     (1)
#define PMIC_CODEC_ANA_RW23_hsmicb_dschg_START  (2)
#define PMIC_CODEC_ANA_RW23_hsmicb_dschg_END    (2)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_0_START    (3)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_0_END      (3)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_1_START    (4)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_1_END      (4)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_2_START    (5)
#define PMIC_CODEC_ANA_RW23_hsd_ctrl_2_END      (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW24_UNION
 结构说明  : CODEC_ANA_RW24 寄存器结构定义。地址偏移量:0x281，初值:0x84，宽度:8
 寄存器说明: MBHD_VREF_CTRL[7:0]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mbhd_vref_ctrl_1_0 : 2;  /* bit[0-1]: Normal模式下，COMPL比较器电压阈值，档位分配(mbhd_vref_ctrl<1:0>：
                                                             00: 600mV
                                                             01: 700mV
                                                             10: 800mV
                                                             11: 900mV */
        unsigned char  mbhd_vref_ctrl_3_2 : 2;  /* bit[2-3]: Normal模式下，COMPH比较器电压阈值，档位分配(mbhd_vref_ctrl<3:2>)：
                                                             00:80%*Vmicbias;
                                                             01:85%*Vmicbias;
                                                             10:90%Vmicbias;
                                                             11:95%*Vmicbias */
        unsigned char  mbhd_vref_ctrl_6_4 : 3;  /* bit[4-6]: ECO模式下，ECO_COMP比较器电压阈值，档位分配(mbhd_vref_ctrl<6:4>)：
                                                             000：100mV
                                                             001：125mV
                                                             010: 150mV
                                                             011: 175mV
                                                             100: 200mV
                                                             101: 225mV
                                                             110: 250mV
                                                             111：275mV */
        unsigned char  mbhd_vref_pd       : 1;  /* bit[7]  : 按键检测模块比较器分压电阻PD信号(mbhd_vref_pd)：
                                                             0：VREF及比较器正常工作；
                                                             1：VREF及比较器PD；（在无耳机在位状态下，开启PD=1） */
    } reg;
} PMIC_CODEC_ANA_RW24_UNION;
#endif
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_1_0_START  (0)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_1_0_END    (1)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_3_2_START  (2)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_3_2_END    (3)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_6_4_START  (4)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_ctrl_6_4_END    (6)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_pd_START        (7)
#define PMIC_CODEC_ANA_RW24_mbhd_vref_pd_END          (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW25_UNION
 结构说明  : CODEC_ANA_RW25 寄存器结构定义。地址偏移量:0x282，初值:0x30，宽度:8
 寄存器说明: CP_CLK_CTRL[7:0]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cp_det_sel    : 2;  /* bit[0-1]: ChargePump输出电源域切换延时控制信号(CP_DET_SEL<1:0>):
                                                        00: 375Hz；
                                                        01: 187.5Hz；
                                                        10: 94Hz；
                                                        11: 47Hz； */
        unsigned char  cp_det_clk_pd : 1;  /* bit[2]  : ChargePump输出电源域切换延时控制信号PD（CP_DET_CLK_PD）:
                                                        0：正常输出时钟；
                                                        1：PD */
        unsigned char  cp_clk_pd     : 1;  /* bit[3]  : ChargePump开关时钟控制信号（CP_CLK_PD）:
                                                        0：正常输出时钟；
                                                        1：PD */
        unsigned char  cp_sel        : 3;  /* bit[4-6]: ChargePump开关频率选择信号(CP_SEL<2:0>):
                                                        000: 6.144MHz；
                                                        001: 3.072MHz；
                                                        010: 1.536MHz；
                                                        011: 768KHz；
                                                        100: 384KHz；
                                                        101: 192KHz；
                                                        110: 96KHz；
                                                        111: 48KHz； */
        unsigned char  hs_sys_clk_pd : 1;  /* bit[7]  : Headphone 系统时钟PD信号（HS_SYS_CLK_PD）
                                                        0：正常输出时钟；
                                                        1：PD */
    } reg;
} PMIC_CODEC_ANA_RW25_UNION;
#endif
#define PMIC_CODEC_ANA_RW25_cp_det_sel_START     (0)
#define PMIC_CODEC_ANA_RW25_cp_det_sel_END       (1)
#define PMIC_CODEC_ANA_RW25_cp_det_clk_pd_START  (2)
#define PMIC_CODEC_ANA_RW25_cp_det_clk_pd_END    (2)
#define PMIC_CODEC_ANA_RW25_cp_clk_pd_START      (3)
#define PMIC_CODEC_ANA_RW25_cp_clk_pd_END        (3)
#define PMIC_CODEC_ANA_RW25_cp_sel_START         (4)
#define PMIC_CODEC_ANA_RW25_cp_sel_END           (6)
#define PMIC_CODEC_ANA_RW25_hs_sys_clk_pd_START  (7)
#define PMIC_CODEC_ANA_RW25_hs_sys_clk_pd_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW26_UNION
 结构说明  : CODEC_ANA_RW26 寄存器结构定义。地址偏移量:0x283，初值:0x09，宽度:8
 寄存器说明: ADC，DAC时钟沿选择信号。，ADC，DACchopper时钟选择信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dac_chop_clk_sel   : 2;  /* bit[0-1]: DAC的chopper时钟选择信号(DAC_CHOP_CLK_SEL<1:0>):
                                                             00: 3MHz；
                                                             01: 1.5MHz；
                                                             10: 750KHz；
                                                             11: 375KHz； */
        unsigned char  adc_chop_clk_sel   : 2;  /* bit[2-3]: ADC的chopper时钟选择信号(ADC_CHOP_CLK_SEL<1:0>):
                                                             00: 384KHz；
                                                             01: 192KHz；
                                                             10: 96KHz；
                                                             11: 48KHz； */
        unsigned char  dac_clk_sys_edge_0 : 1;  /* bit[4]  : DAC时钟相位选择信号(DAC_CLK_SYS_EDG_0):
                                                             0:DAC时钟选择二分频后同相时钟
                                                             1:DAC时钟选择二分频后反相时钟 */
        unsigned char  dac_clk_sys_edge_1 : 1;  /* bit[5]  : DAC时钟沿选择信号(DAC_CLK_SYS_EDG_1):
                                                             0:DAC时钟沿同输入12.288MHz时钟沿反沿；
                                                             1:DAC时钟沿同输入12.288MHz时钟沿同沿； */
        unsigned char  adc_clk_sys_edge_0 : 1;  /* bit[6]  : ADC时钟相位选择信号(ADC_CLK_SYS_EDG_0):
                                                             0:ADC时钟选择二分频后同相时钟
                                                             1:ADC时钟选择二分频后反相时钟 */
        unsigned char  adc_clk_sys_edge_1 : 1;  /* bit[7]  : ADC时钟沿选择信号(ADC_CLK_SYS_EDG_1):
                                                             0:ADC时钟沿同输入12.288MHz时钟沿反沿；
                                                             1:ADC时钟沿同输入12.288MHz时钟沿同沿； */
    } reg;
} PMIC_CODEC_ANA_RW26_UNION;
#endif
#define PMIC_CODEC_ANA_RW26_dac_chop_clk_sel_START    (0)
#define PMIC_CODEC_ANA_RW26_dac_chop_clk_sel_END      (1)
#define PMIC_CODEC_ANA_RW26_adc_chop_clk_sel_START    (2)
#define PMIC_CODEC_ANA_RW26_adc_chop_clk_sel_END      (3)
#define PMIC_CODEC_ANA_RW26_dac_clk_sys_edge_0_START  (4)
#define PMIC_CODEC_ANA_RW26_dac_clk_sys_edge_0_END    (4)
#define PMIC_CODEC_ANA_RW26_dac_clk_sys_edge_1_START  (5)
#define PMIC_CODEC_ANA_RW26_dac_clk_sys_edge_1_END    (5)
#define PMIC_CODEC_ANA_RW26_adc_clk_sys_edge_0_START  (6)
#define PMIC_CODEC_ANA_RW26_adc_clk_sys_edge_0_END    (6)
#define PMIC_CODEC_ANA_RW26_adc_clk_sys_edge_1_START  (7)
#define PMIC_CODEC_ANA_RW26_adc_clk_sys_edge_1_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW27_UNION
 结构说明  : CODEC_ANA_RW27 寄存器结构定义。地址偏移量:0x284，初值:0x00，宽度:8
 寄存器说明: RX，ADC_SDM,LINEIN,MICPGA,CTCM，chopperbaypass信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ctcm_chop_bps    : 1;  /* bit[0]  : CTCM Chopper Baypass控制信号(CTCM_CHOP_BPS):
                                                           0:打开Chopper功能；
                                                           1:Baypass Chopper功能； */
        unsigned char  micpga_chop_bps  : 1;  /* bit[1]  : MICPGA Chopper Baypass控制信号(MICPGA_CHOP_BPS):
                                                           0:打开Chopper功能；
                                                           1:Baypass Chopper功能； */
        unsigned char  linein_chop_bps  : 1;  /* bit[2]  : LINEIN Chopper Baypass控制信号(LINEIN_CHOP_BPS):
                                                           0:打开Chopper功能；
                                                           1:Baypass Chopper功能； */
        unsigned char  adc_sdm_chop_bps : 1;  /* bit[3]  : ADC_SDM Chopper Baypass控制信号(ADC_SDM_CHOP_BPS):
                                                           0:打开Chopper功能；
                                                           1:Baypass Chopper功能； */
        unsigned char  rx_chop_bps      : 1;  /* bit[4]  : RX Chopper Baypass控制信号(RX_CHOP_BPS):
                                                           0:打开Chopper功能；
                                                           1:Baypass Chopper功能； */
        unsigned char  reserved         : 3;  /* bit[5-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW27_UNION;
#endif
#define PMIC_CODEC_ANA_RW27_ctcm_chop_bps_START     (0)
#define PMIC_CODEC_ANA_RW27_ctcm_chop_bps_END       (0)
#define PMIC_CODEC_ANA_RW27_micpga_chop_bps_START   (1)
#define PMIC_CODEC_ANA_RW27_micpga_chop_bps_END     (1)
#define PMIC_CODEC_ANA_RW27_linein_chop_bps_START   (2)
#define PMIC_CODEC_ANA_RW27_linein_chop_bps_END     (2)
#define PMIC_CODEC_ANA_RW27_adc_sdm_chop_bps_START  (3)
#define PMIC_CODEC_ANA_RW27_adc_sdm_chop_bps_END    (3)
#define PMIC_CODEC_ANA_RW27_rx_chop_bps_START       (4)
#define PMIC_CODEC_ANA_RW27_rx_chop_bps_END         (4)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW28_UNION
 结构说明  : CODEC_ANA_RW28 寄存器结构定义。地址偏移量:0x285，初值:0x00，宽度:8
 寄存器说明: TX，DAC，MIXER_EAR,MIXER_HP，chopperbaypass信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hs_chop_bps      : 1;  /* bit[0]  : MIXER FOR Headphone Chopper Baypass控制信号(HS_CHOP_BPS):
                                                           0:打开Chopper功能；
                                                           1:Baypass Chopper功能； */
        unsigned char  ear_cld_chop_bps : 1;  /* bit[1]  : MIXER FOR Earphone and Classd Chopper Baypass控制信号(EAR_CLD_CHOP_BPS):
                                                           0:打开Chopper功能；
                                                           1:Baypass Chopper功能； */
        unsigned char  dac_chop_bps     : 1;  /* bit[2]  : DAC Chopper Baypass控制信号(DAC_CHOP_BPS):
                                                           0:打开Chopper功能；
                                                           1:Baypass Chopper功能； */
        unsigned char  tx_chop_bps      : 1;  /* bit[3]  : TX Chopper Baypass控制信号(TX_CHOP_BPS):
                                                           0:打开Chopper功能；
                                                           1:Baypass Chopper功能； */
        unsigned char  reserved         : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW28_UNION;
#endif
#define PMIC_CODEC_ANA_RW28_hs_chop_bps_START       (0)
#define PMIC_CODEC_ANA_RW28_hs_chop_bps_END         (0)
#define PMIC_CODEC_ANA_RW28_ear_cld_chop_bps_START  (1)
#define PMIC_CODEC_ANA_RW28_ear_cld_chop_bps_END    (1)
#define PMIC_CODEC_ANA_RW28_dac_chop_bps_START      (2)
#define PMIC_CODEC_ANA_RW28_dac_chop_bps_END        (2)
#define PMIC_CODEC_ANA_RW28_tx_chop_bps_START       (3)
#define PMIC_CODEC_ANA_RW28_tx_chop_bps_END         (3)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW29_UNION
 结构说明  : CODEC_ANA_RW29 寄存器结构定义。地址偏移量:0x286，初值:0x2D，宽度:8
 寄存器说明: CODEC_IBIAS_ADJ1（HeadphoneMIXER_HP电流控制信号。）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_mixer_hp : 3;  /* bit[0-2]: MIXER_HP的电流控制信号:
                                                        000: 2.5uA；
                                                        001: 3uA；
                                                        010: 3.5uA；
                                                        011: 4uA；
                                                        100: 4.5uA；
                                                        101: 5uA；
                                                        110: 7uA；
                                                        111: 9uA； */
        unsigned char  ib05_hp       : 3;  /* bit[3-5]: Headphone_amp的电流控制信号:
                                                        000: 2.5uA；
                                                        001: 3uA；
                                                        010: 3.5uA；
                                                        011: 4uA；
                                                        100: 4.5uA；
                                                        101: 5uA；
                                                        110: 7uA；
                                                        111: 9uA； */
        unsigned char  reserved      : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW29_UNION;
#endif
#define PMIC_CODEC_ANA_RW29_ib05_mixer_hp_START  (0)
#define PMIC_CODEC_ANA_RW29_ib05_mixer_hp_END    (2)
#define PMIC_CODEC_ANA_RW29_ib05_hp_START        (3)
#define PMIC_CODEC_ANA_RW29_ib05_hp_END          (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW30_UNION
 结构说明  : CODEC_ANA_RW30 寄存器结构定义。地址偏移量:0x287，初值:0x2D，宽度:8
 寄存器说明: CODEC_IBIAS_ADJ2（DAC，ADC_OPA1电流控制信号。）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_adc_opa1 : 3;  /* bit[0-2]: IB05_ADC_OPA1的电流控制信号(IB05_ADC_OPA1):
                                                        000: 2.5uA；
                                                        001: 3uA；
                                                        010: 3.5uA；
                                                        011: 4uA；
                                                        100: 4.5uA；
                                                        101: 5uA；
                                                        110: 7uA；
                                                        111: 9uA； */
        unsigned char  ib05_dac      : 3;  /* bit[3-5]: DAC的电流控制信号(IB05_DAC):
                                                        000: 2.5uA；
                                                        001: 3uA；
                                                        010: 3.5uA；
                                                        011: 4uA；
                                                        100: 4.5uA；
                                                        101: 5uA；
                                                        110: 7uA；
                                                        111: 9uA； */
        unsigned char  reserved      : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW30_UNION;
#endif
#define PMIC_CODEC_ANA_RW30_ib05_adc_opa1_START  (0)
#define PMIC_CODEC_ANA_RW30_ib05_adc_opa1_END    (2)
#define PMIC_CODEC_ANA_RW30_ib05_dac_START       (3)
#define PMIC_CODEC_ANA_RW30_ib05_dac_END         (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW31_UNION
 结构说明  : CODEC_ANA_RW31 寄存器结构定义。地址偏移量:0x288，初值:0x2D，宽度:8
 寄存器说明: CODEC_IBIAS_ADJ3（ADC_OPA2，ADC_COMP电流控制信号。）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_adc_comp : 3;  /* bit[0-2]: IB05_ADC_COMP的电流控制信号(IB05_ADC_COMP):
                                                        000: 2.5uA；
                                                        001: 3uA；
                                                        010: 3.5uA；
                                                        011: 4uA；
                                                        100: 4.5uA；
                                                        101: 5uA；
                                                        110: 7uA；
                                                        111: 9uA； */
        unsigned char  ib05_adc_opa2 : 3;  /* bit[3-5]: IB05_ADC_OPA2的电流控制信号(IB05_ADC_OPA2):
                                                        000: 2.5uA；
                                                        001: 3uA；
                                                        010: 3.5uA；
                                                        011: 4uA；
                                                        100: 4.5uA；
                                                        101: 5uA；
                                                        110: 7uA；
                                                        111: 9uA； */
        unsigned char  reserved      : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW31_UNION;
#endif
#define PMIC_CODEC_ANA_RW31_ib05_adc_comp_START  (0)
#define PMIC_CODEC_ANA_RW31_ib05_adc_comp_END    (2)
#define PMIC_CODEC_ANA_RW31_ib05_adc_opa2_START  (3)
#define PMIC_CODEC_ANA_RW31_ib05_adc_opa2_END    (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW32_UNION
 结构说明  : CODEC_ANA_RW32 寄存器结构定义。地址偏移量:0x289，初值:0x2D，宽度:8
 寄存器说明: CODEC_IBIAS_ADJ4（LINEIN，MICBIAS电流控制信号。）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_micbias    : 3;  /* bit[0-2]: IB05_MICBIAS的电流控制信号(IB05_MICBIAS):
                                                          000: 2.5uA；
                                                          001: 3uA；
                                                          010: 3.5uA；
                                                          011: 4uA；
                                                          100: 4.5uA；
                                                          101: 5uA；
                                                          110: 7uA；
                                                          111: 9uA； */
        unsigned char  ib05_adc_linein : 3;  /* bit[3-5]: IB05_ADC_LINEIN的电流控制信号(IB05_ADC_LINEIN):
                                                          000: 2.5uA；
                                                          001: 3uA；
                                                          010: 3.5uA；
                                                          011: 4uA；
                                                          100: 4.5uA；
                                                          101: 5uA；
                                                          110: 7uA；
                                                          111: 9uA； */
        unsigned char  reserved        : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW32_UNION;
#endif
#define PMIC_CODEC_ANA_RW32_ib05_micbias_START     (0)
#define PMIC_CODEC_ANA_RW32_ib05_micbias_END       (2)
#define PMIC_CODEC_ANA_RW32_ib05_adc_linein_START  (3)
#define PMIC_CODEC_ANA_RW32_ib05_adc_linein_END    (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW33_UNION
 结构说明  : CODEC_ANA_RW33 寄存器结构定义。地址偏移量:0x28A，初值:0x2D，宽度:8
 寄存器说明: CODEC_IBIAS_ADJ5（reserved，AUXMIC电流控制信号）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_auxmic : 3;  /* bit[0-2]: IB05_AUXMIC的电流控制信号(IB05_AUXMIC):
                                                      000: 2.5uA；
                                                      001: 3uA；
                                                      010: 3.5uA；
                                                      011: 4uA；
                                                      100: 4.5uA；
                                                      101: 5uA；
                                                      110: 7uA；
                                                      111: 9uA； */
        unsigned char  ib05_rev    : 3;  /* bit[3-5]: IB05_CTCM的电流控制信号(IB05_CTCM):
                                                      000: 2.5uA；
                                                      001: 3uA；
                                                      010: 3.5uA；
                                                      011: 4uA；
                                                      100: 4.5uA；
                                                      101: 5uA；
                                                      110: 7uA；
                                                      111: 9uA； */
        unsigned char  reserved    : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW33_UNION;
#endif
#define PMIC_CODEC_ANA_RW33_ib05_auxmic_START  (0)
#define PMIC_CODEC_ANA_RW33_ib05_auxmic_END    (2)
#define PMIC_CODEC_ANA_RW33_ib05_rev_START     (3)
#define PMIC_CODEC_ANA_RW33_ib05_rev_END       (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW34_UNION
 结构说明  : CODEC_ANA_RW34 寄存器结构定义。地址偏移量:0x28B，初值:0x2D，宽度:8
 寄存器说明: CODEC_IBIAS_ADJ6（MAINMIC，MIXER_EAR电流控制信号。）
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ib05_mixer_ear : 3;  /* bit[0-2]: IB05_MIXER_EAR的电流控制信号(IB05_MIXER_EAR):
                                                         000: 2.5uA；
                                                         001: 3uA；
                                                         010: 3.5uA；
                                                         011: 4uA；
                                                         100: 4.5uA；
                                                         101: 5uA；
                                                         110: 7uA；
                                                         111: 9uA； */
        unsigned char  ib05_mainmic   : 3;  /* bit[3-5]: IB05_MAINMIC的电流控制信号(IB05_MAINMIC):
                                                         000: 2.5uA；
                                                         001: 3uA；
                                                         010: 3.5uA；
                                                         011: 4uA；
                                                         100: 4.5uA；
                                                         101: 5uA；
                                                         110: 7uA；
                                                         111: 9uA； */
        unsigned char  reserved       : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW34_UNION;
#endif
#define PMIC_CODEC_ANA_RW34_ib05_mixer_ear_START  (0)
#define PMIC_CODEC_ANA_RW34_ib05_mixer_ear_END    (2)
#define PMIC_CODEC_ANA_RW34_ib05_mainmic_START    (3)
#define PMIC_CODEC_ANA_RW34_ib05_mainmic_END      (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW35_UNION
 结构说明  : CODEC_ANA_RW35 寄存器结构定义。地址偏移量:0x28C，初值:0x0A，宽度:8
 寄存器说明: CODEC_IBIAS_ADJ7（EAR，CODEC全局电流控制信号）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  codec_bias_adj : 1;  /* bit[0]  : CODEC的全局电流控制信号(CODEC_IBIAS_ADJ):
                                                         0:5uA；
                                                         1:7.5uA； */
        unsigned char  ib05_ear       : 3;  /* bit[1-3]: IB05_EAR的电流控制信号(IB05_EAR):
                                                         000: 2.5uA；
                                                         001: 3uA；
                                                         010: 3.5uA；
                                                         011: 4uA；
                                                         100: 4.5uA；
                                                         101: 5uA；
                                                         110: 7uA；
                                                         111: 9uA； */
        unsigned char  reserved       : 4;  /* bit[4-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW35_UNION;
#endif
#define PMIC_CODEC_ANA_RW35_codec_bias_adj_START  (0)
#define PMIC_CODEC_ANA_RW35_codec_bias_adj_END    (0)
#define PMIC_CODEC_ANA_RW35_ib05_ear_START        (1)
#define PMIC_CODEC_ANA_RW35_ib05_ear_END          (3)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW36_UNION
 结构说明  : CODEC_ANA_RW36 寄存器结构定义。地址偏移量:0x28D，初值:0x00，宽度:8
 寄存器说明: ADC_DAC模拟环回控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hpl_pop_res_c : 2;  /* bit[0-1]: HeadphoneL 中POP音强弱输出管间电阻阻值选择控制信号HPL_POP_RES_C<1:0>：
                                                        00：1.5K；
                                                        01：3K；
                                                        10：4.5K；
                                                        11：6K； */
        unsigned char  reserved      : 6;  /* bit[2-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW36_UNION;
#endif
#define PMIC_CODEC_ANA_RW36_hpl_pop_res_c_START  (0)
#define PMIC_CODEC_ANA_RW36_hpl_pop_res_c_END    (1)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW37_UNION
 结构说明  : CODEC_ANA_RW37 寄存器结构定义。地址偏移量:0x28E，初值:0x00，宽度:8
 寄存器说明: HP_BIAS_PD 、CP_PD、CP_DET_PD控制信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cp_det_pd  : 1;  /* bit[0]  : ChargePump Detect上电控制信号(CP_DET_PD)：
                                                     0：PD；
                                                     1：正常工作; */
        unsigned char  cp_pd      : 1;  /* bit[1]  : ChargePump上电控制信号(CP_PD)：
                                                     0：PD；
                                                     1：正常工作; */
        unsigned char  hp_bias_pd : 1;  /* bit[2]  : Headphone ibias上电控制信号（HP_BIAS_PD）
                                                     0：PD；
                                                     1：正常工作; */
        unsigned char  reserved   : 5;  /* bit[3-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW37_UNION;
#endif
#define PMIC_CODEC_ANA_RW37_cp_det_pd_START   (0)
#define PMIC_CODEC_ANA_RW37_cp_det_pd_END     (0)
#define PMIC_CODEC_ANA_RW37_cp_pd_START       (1)
#define PMIC_CODEC_ANA_RW37_cp_pd_END         (1)
#define PMIC_CODEC_ANA_RW37_hp_bias_pd_START  (2)
#define PMIC_CODEC_ANA_RW37_hp_bias_pd_END    (2)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW38_UNION
 结构说明  : CODEC_ANA_RW38 寄存器结构定义。地址偏移量:0x28F，初值:0x00，宽度:8
 寄存器说明: DACL_PD、DACR_PD。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  dacr_pd  : 1;  /* bit[0]  : DACR上电控制信号(DACR_PD)：
                                                   0：PD；
                                                   1：正常工作; */
        unsigned char  dacl_pd  : 1;  /* bit[1]  : DACL上电控制信号(DACL_PD)：
                                                   0：PD；
                                                   1：正常工作; */
        unsigned char  reserved : 6;  /* bit[2-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW38_UNION;
#endif
#define PMIC_CODEC_ANA_RW38_dacr_pd_START   (0)
#define PMIC_CODEC_ANA_RW38_dacr_pd_END     (0)
#define PMIC_CODEC_ANA_RW38_dacl_pd_START   (1)
#define PMIC_CODEC_ANA_RW38_dacl_pd_END     (1)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW39_UNION
 结构说明  : CODEC_ANA_RW39 寄存器结构定义。地址偏移量:0x290，初值:0x00，宽度:8
 寄存器说明: MIXOUT_EAR_PD、EAR_PD。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ear_pd        : 1;  /* bit[0]  : EAR上电控制信号(EAR_PD)：
                                                        0：PD；
                                                        1：正常工作; */
        unsigned char  mixout_ear_pd : 1;  /* bit[1]  : MIXOUT_EAR上电控制信号(MIXOUT_EAR_PD)：
                                                        0：PD；
                                                        1：正常工作; */
        unsigned char  ear_vref_en   : 1;  /* bit[2]  : EAR_VREF上电控制信号(EAR_VREF_EN)：
                                                        0：PD；
                                                        1：正常工作; */
        unsigned char  reserved      : 5;  /* bit[3-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW39_UNION;
#endif
#define PMIC_CODEC_ANA_RW39_ear_pd_START         (0)
#define PMIC_CODEC_ANA_RW39_ear_pd_END           (0)
#define PMIC_CODEC_ANA_RW39_mixout_ear_pd_START  (1)
#define PMIC_CODEC_ANA_RW39_mixout_ear_pd_END    (1)
#define PMIC_CODEC_ANA_RW39_ear_vref_en_START    (2)
#define PMIC_CODEC_ANA_RW39_ear_vref_en_END      (2)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW40_UNION
 结构说明  : CODEC_ANA_RW40 寄存器结构定义。地址偏移量:0x291，初值:0x00，宽度:8
 寄存器说明: CODEC_ANA_RW40。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hpr_pop_res_c : 2;  /* bit[0-1]: HeadphoneR 中POP音强弱输出管间电阻阻值选择控制信号HPR_POP_RES_C<1:0>：
                                                        00：1.5K；
                                                        01：3K；
                                                        10：4.5K；
                                                        11：6K； */
        unsigned char  reserved      : 6;  /* bit[2-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW40_UNION;
#endif
#define PMIC_CODEC_ANA_RW40_hpr_pop_res_c_START  (0)
#define PMIC_CODEC_ANA_RW40_hpr_pop_res_c_END    (1)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RO01_UNION
 结构说明  : CODEC_ANA_RO01 寄存器结构定义。地址偏移量:0x292，初值:0x00，宽度:8
 寄存器说明: CODEC_ANA_RO01。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  codec_ana_ro01 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CODEC_ANA_RO01_UNION;
#endif
#define PMIC_CODEC_ANA_RO01_codec_ana_ro01_START  (0)
#define PMIC_CODEC_ANA_RO01_codec_ana_ro01_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RO02_UNION
 结构说明  : CODEC_ANA_RO02 寄存器结构定义。地址偏移量:0x293，初值:0x00，宽度:8
 寄存器说明: CODEC_ANA_RO02。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  codec_ana_ro02 : 8;  /* bit[0-7]:  */
    } reg;
} PMIC_CODEC_ANA_RO02_UNION;
#endif
#define PMIC_CODEC_ANA_RO02_codec_ana_ro02_START  (0)
#define PMIC_CODEC_ANA_RO02_codec_ana_ro02_END    (7)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW41_UNION
 结构说明  : CODEC_ANA_RW41 寄存器结构定义。地址偏移量:0x294，初值:0x27，宽度:8
 寄存器说明: OSC_BAK调节信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  osc_bak_adj     : 4;  /* bit[0-3]: FM模式下备用时钟调节信号(OSC_BAK_ADJ<3:0>)：
                                                          TT condition
                                                          0000：NO CLK；禁止
                                                          0001：0.517MHz；
                                                          0010：0.992MHz；
                                                          0011：1.445MHz；
                                                          0100：1.872MHz；
                                                          0101：2.296MHz；
                                                          0110：2.705MHz；
                                                          0111：3.115MHz；
                                                          1000：3.490MHz；
                                                          1001：3.889MHz；
                                                          1010：4.275MHz；
                                                          1011：4.669MHz；
                                                          1100：5.033MHz；
                                                          1101：5.421MHz；
                                                          1110：5.795MHz；
                                                          1111：6.18MHz； */
        unsigned char  osc_bak_ins_sel : 1;  /* bit[4]  : FM模式下备用时钟代替原时钟位置选择信号(OSC_BAK_INS_SEL)
                                                          0：备用时钟在PLL时钟分频链的3M处代替PLL时钟；（配合OSC_BAK_ADJ=7时使用）
                                                          1：备用时钟在PLL时钟分频链的6M处代替PLL时钟；（配合OSC_BAK_ADJ=15时使用） */
        unsigned char  osc_bak_pd      : 1;  /* bit[5]  : 备用时钟PD信号(OSC_BAK_PD)
                                                          0：正常工作；
                                                          1：PD； */
        unsigned char  reserved        : 2;  /* bit[6-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW41_UNION;
#endif
#define PMIC_CODEC_ANA_RW41_osc_bak_adj_START      (0)
#define PMIC_CODEC_ANA_RW41_osc_bak_adj_END        (3)
#define PMIC_CODEC_ANA_RW41_osc_bak_ins_sel_START  (4)
#define PMIC_CODEC_ANA_RW41_osc_bak_ins_sel_END    (4)
#define PMIC_CODEC_ANA_RW41_osc_bak_pd_START       (5)
#define PMIC_CODEC_ANA_RW41_osc_bak_pd_END         (5)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW42_UNION
 结构说明  : CODEC_ANA_RW42 寄存器结构定义。地址偏移量:0x295，初值:0x00，宽度:8
 寄存器说明: FM模式下时钟切换选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  clk_cp_src_sel     : 1;  /* bit[0]  : Chargepump时钟源选择信号(CLK_CP_SRC_SEL)
                                                             CLK_CP/CLK_CP_DET/CLK_POP_48K
                                                             0：选择PLL时钟；
                                                             1：选择OSC_BAK时钟； */
        unsigned char  clk_txchop_src_sel : 1;  /* bit[1]  : RX通路CHOP时钟源选择信号(CLK_TXCHOP_SRC_SEL)
                                                             CLK_DAC_CHOP/CLK_ERA_CLKD_CHOP/CLK_HS_CHOP
                                                             0：选择PLL时钟；
                                                             1：选择OSC_BAK时钟； */
        unsigned char  clk_rxchop_src_sel : 1;  /* bit[2]  : RX通路CHOP时钟源选择信号(CLK_RXCHOP_SRC_SEL)
                                                             CLK_LINEIN_CHOP/CLK_MICPGA_CHOP/CLK_ADC_SDM_CHOP/CLK_CTCM_CHOP
                                                             0：选择PLL时钟；
                                                             1：选择OSC_BAK时钟； */
        unsigned char  reserved           : 5;  /* bit[3-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW42_UNION;
#endif
#define PMIC_CODEC_ANA_RW42_clk_cp_src_sel_START      (0)
#define PMIC_CODEC_ANA_RW42_clk_cp_src_sel_END        (0)
#define PMIC_CODEC_ANA_RW42_clk_txchop_src_sel_START  (1)
#define PMIC_CODEC_ANA_RW42_clk_txchop_src_sel_END    (1)
#define PMIC_CODEC_ANA_RW42_clk_rxchop_src_sel_START  (2)
#define PMIC_CODEC_ANA_RW42_clk_rxchop_src_sel_END    (2)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW43_UNION
 结构说明  : CODEC_ANA_RW43 寄存器结构定义。地址偏移量:0x296，初值:0x74，宽度:8
 寄存器说明: CODEC_ANA_RW43
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  push_adj_n : 3;  /* bit[0-2]: Headphone 防POP音HP N端下拉开关控制信号PUSH_ADJ_N<2:0>
                                                     000：8/15；
                                                     001：9/15；
                                                     010：10/15；
                                                     011：11/15；
                                                     100：12/15（默认）；
                                                     101：13/15；
                                                     110：14/15；
                                                     111：full尺寸； */
        unsigned char  reserved_0 : 1;  /* bit[3]  : reserved */
        unsigned char  push_adj_p : 3;  /* bit[4-6]: Headphone 防POP音HP P端下拉开关控制信号PUSH_ADJ_P<2:0>
                                                     000：8/15；
                                                     001：9/15；
                                                     010：10/15；
                                                     011：11/15；
                                                     100：12/15；
                                                     101：13/15；
                                                     110：14/15；
                                                     111：full尺寸（默认）； */
        unsigned char  reserved_1 : 1;  /* bit[7]  : reserved */
    } reg;
} PMIC_CODEC_ANA_RW43_UNION;
#endif
#define PMIC_CODEC_ANA_RW43_push_adj_n_START  (0)
#define PMIC_CODEC_ANA_RW43_push_adj_n_END    (2)
#define PMIC_CODEC_ANA_RW43_push_adj_p_START  (4)
#define PMIC_CODEC_ANA_RW43_push_adj_p_END    (6)


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW44_UNION
 结构说明  : CODEC_ANA_RW44 寄存器结构定义。地址偏移量:0x297，初值:0x00，宽度:8
 寄存器说明: CODEC_ANA_RW44
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved : 8;  /* bit[0-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW44_UNION;
#endif


/*****************************************************************************
 结构名    : PMIC_CODEC_ANA_RW45_UNION
 结构说明  : CODEC_ANA_RW45 寄存器结构定义。地址偏移量:0x298，初值:0x00，宽度:8
 寄存器说明: CODEC_ANA_RW45
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved : 8;  /* bit[0-7]: reserved */
    } reg;
} PMIC_CODEC_ANA_RW45_UNION;
#endif






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

#endif /* end of soc_pmic_interface.h */
