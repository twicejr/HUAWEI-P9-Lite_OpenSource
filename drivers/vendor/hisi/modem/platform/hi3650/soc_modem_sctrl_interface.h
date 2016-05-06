/******************************************************************************

                 版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_modem_sctrl_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2013-12-26 13:49:08
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月26日
    作    者   : y00186965
    修改内容   : 从《Hi6210V100 SOC寄存器手册_MODEM_SCTRL.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_MODEM_SCTRL_INTERFACE_H__
#define __SOC_MODEM_SCTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) cpu_if_mdm_sc_auto
 ****************************************************************************/
/* 寄存器说明：上电区时钟使能寄存器。用于使能外设时钟。对比特写1，使能对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ADDR(base)     ((base) + (0x0000))

/* 寄存器说明：上电区时钟禁止寄存器。用于禁止外设时钟。对比特写1，禁止对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ADDR(base)    ((base) + (0x0004))

/* 寄存器说明：上电区时钟状态寄存器。用于回读各外设时钟的状态。外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：上电区复位使能寄存器。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ADDR(base)     ((base) + (0x0018))

/* 寄存器说明：上电区复位禁止寄存器。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ADDR(base)    ((base) + (0x001C))

/* 寄存器说明：上电区复位状态寄存器。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ADDR(base) ((base) + (0x0020))

/* 寄存器说明：掉电区时钟使能寄存器。用于控制各掉电区总的时钟使能。对相应位写1使能相应电压域时钟，写0无影响。该寄存器只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_ADDR(base)     ((base) + (0x0040))

/* 寄存器说明：掉电区时钟禁止寄存器。用于控制各掉电区总的时钟禁止。对相应位写1禁止相应掉电区时钟，写0无影响。该寄存器只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_ADDR(base)    ((base) + (0x0044))

/* 寄存器说明：下电区时钟状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_ADDR(base) ((base) + (0x0048))

/* 寄存器说明：掉电区复位使能寄存器。用于控制各掉电区总的复位使能。对相应位写1使能相应掉电区复位信号（即进入复位态），写0无影响。该寄存器只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_ADDR(base)     ((base) + (0x004C))

/* 寄存器说明：掉电区复位禁止寄存器。用于控制各掉电区总的复位禁止。对相应位写1禁止相应掉电区复位信号（即退出复位态），写0无影响。该寄存器只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_ADDR(base)    ((base) + (0x0050))

/* 寄存器说明：下电区复位状态
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_ADDR(base) ((base) + (0x0054))

/* 寄存器说明：掉电区ISO使能寄存器。用于控制各掉电区相关的Isolation Cell使能。对相应位写1使能相应掉电区IsoLation Cell（即信号隔断），写0无影响。该寄存器只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_ADDR(base)     ((base) + (0x0058))

/* 寄存器说明：掉电区ISO禁止寄存器。用于控制各掉电区相关的Isolation Cell禁止。对相应位写1禁止相应掉电区IsoLation Cell（即信号不隔断），写0无影响。该寄存器只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_ADDR(base)    ((base) + (0x005C))

/* 寄存器说明：下电区ISO状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_ADDR(base) ((base) + (0x0060))

/* 寄存器说明：掉电区电源使能寄存器。用于控制各掉电区的电源使能，对相应位写1打开相应电压域电源，写0无影响。该寄存器存只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_ADDR(base)  ((base) + (0x0064))

/* 寄存器说明：掉电区电源禁止寄存器。用于控制各掉电区的电源禁止，对相应位写1关闭相应电压域电源，写0无影响。该寄存器存只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_ADDR(base) ((base) + (0x0068))

/* 寄存器说明：掉电区电源配置状态
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_ADDR(base) ((base) + (0x006C))

/* 寄存器说明：下电区MTCMOS延时链电源反馈信号
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_ADDR(base) ((base) + (0x0074))

/* 寄存器说明：系统POWER状态寄存器。用于监测系统所处的POWER状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_ADDR(base) ((base) + (0x0078))

/* 寄存器说明：外设时钟使能寄存器。用于使能外设时钟。对比特写1，使能对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_ADDR(base) ((base) + (0x0100))

/* 寄存器说明：外设时钟禁止寄存器。用于禁止外设时钟。对比特写1，禁止对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_ADDR(base) ((base) + (0x0104))

/* 寄存器说明：外设时钟状态寄存器9。用于回读各外设时钟的状态。外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_ADDR(base) ((base) + (0x0108))

/* 寄存器说明：BBP时钟使能寄存器0。用于使能外设时钟。对比特写1，使能对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_ADDR(base)   ((base) + (0x0120))

/* 寄存器说明：外设时钟禁止寄存器0。用于禁止外设时钟。对比特写1，禁止对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_ADDR(base)  ((base) + (0x0124))

/* 寄存器说明：外设时钟状态寄存器0。用于回读各外设时钟的状态。外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_ADDR(base) ((base) + (0x0128))

/* 寄存器说明：BBP时钟使能寄存器1。用于使能外设时钟。对比特写1，使能对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_ADDR(base)   ((base) + (0x012C))

/* 寄存器说明：外设时钟禁止寄存器1。用于禁止外设时钟。对比特写1，禁止对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_ADDR(base)  ((base) + (0x0130))

/* 寄存器说明：外设时钟状态寄存器1。用于回读各外设时钟的状态。外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_ADDR(base) ((base) + (0x0134))

/* 寄存器说明：外设复位使能寄存器。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_ADDR(base) ((base) + (0x0150))

/* 寄存器说明：外设复位禁止寄存器。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_ADDR(base) ((base) + (0x0154))

/* 寄存器说明：外设复位状态寄存器6。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_ADDR(base) ((base) + (0x0158))

/* 寄存器说明：BBP复位使能寄存器。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_ADDR(base)   ((base) + (0x0170))

/* 寄存器说明：BBP复位禁止寄存器。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_ADDR(base)  ((base) + (0x0174))

/* 寄存器说明：BBP复位状态寄存器。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_ADDR(base) ((base) + (0x0178))

/* 寄存器说明：BBP复位使能寄存器1。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_ADDR(base)   ((base) + (0x017C))

/* 寄存器说明：BBP复位禁止寄存器1。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_ADDR(base)  ((base) + (0x0180))

/* 寄存器说明：BBP复位状态寄存器1。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_ADDR(base) ((base) + (0x0184))

/* 寄存器说明：
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_ADDR(base) ((base) + (0x01E0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_ADDR(base) ((base) + (0x01E4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_ADDR(base) ((base) + (0x01E8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_ADDR(base) ((base) + (0x01F0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_ADDR(base) ((base) + (0x01F4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_ADDR(base) ((base) + (0x01F8))

/* 寄存器说明：系统二级中断使能寄存器。用于对系统二级中断进行屏蔽设置。对应bit为1表示使能相应中断，为0表示屏蔽中断。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_ADDR(base) ((base) + (0x0200))

/* 寄存器说明：系统二级中断中断寄存器。用于指示系统二级原始中断状态（屏蔽前）。对应bit为1表示有中断，为0表示无中断。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_ADDR(base) ((base) + (0x0204))

/* 寄存器说明：系统二级中断屏蔽后寄存器。用于指示系统二级中断状态（屏蔽后）。对应bit为1表示有中断，为0表示无中断。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_ADDR(base) ((base) + (0x0208))

/* 寄存器说明：ccpu唤醒中断送给mcu的中断使能寄存器0。用于对mcu的唤醒中断进行屏蔽设置。对应bit为1表示使能相应中断，为0表示屏蔽中断。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ADDR(base) ((base) + (0x020C))

/* 寄存器说明：mcpu唤醒中断送给mcu的原始唤醒中断寄存器。用于指示mcu的原始唤醒中断状态（屏蔽前）。对应bit为1表示有中断，为0表示无中断。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ADDR(base) ((base) + (0x0210))

/* 寄存器说明：mcpu唤醒中断送给mcu的屏蔽后唤醒中断寄存器。用于指示mcu的当前唤醒中断状态（屏蔽后）。对应bit为1表示有中断，为0表示无中断。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ADDR(base) ((base) + (0x0214))

/* 寄存器说明：mcpu唤醒中断送给mcu的唤醒中断使能寄存器。用于对mcu的唤醒中断进行屏蔽设置。对应bit为1表示使能相应中断，为0表示屏蔽中断。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ADDR(base) ((base) + (0x0218))

/* 寄存器说明：mcpu唤醒中断送给mcu的原始唤醒中断寄存器。用于指示mcu的原始唤醒中断状态（屏蔽前）。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ADDR(base) ((base) + (0x021C))

/* 寄存器说明：mcpu唤醒中断送给mcu的屏蔽后唤醒中断寄存器。用于指示mcu的当前唤醒中断状态（屏蔽后）。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ADDR(base) ((base) + (0x0220))

/* 寄存器说明：原始内部中断寄存器，用于指示SC内部的原始中断状态(屏蔽前)。对应bit为1表示有中断，为0表示无中断
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_ADDR(base) ((base) + (0x0224))

/* 寄存器说明：屏蔽后内部中断寄存器。用于指示SC当前内部中断状态(屏蔽后)，对应bit为1表示有中断，为0表示无中断
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_ADDR(base) ((base) + (0x0228))

/* 寄存器说明：内部中断清除寄存器。给相应中断比特位写1，表示清除对应的中断状态，包括原始内部中断寄存器和屏蔽后内部中断寄存器
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_ADDR(base)    ((base) + (0x022C))

/* 寄存器说明：内部中断屏蔽寄存器。对比特写1，打开屏蔽；写0不影响屏蔽的状态
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_EN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_ADDR(base)       ((base) + (0x0230))

/* 寄存器说明：内部中断屏蔽寄存器，对比特写1，禁止屏蔽；写0不影响时钟屏蔽的状态
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_DIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_ADDR(base)      ((base) + (0x0234))

/* 寄存器说明：内部中断使能寄存器，用于SC内部中断的屏蔽设置。对应bit为1表示使能相应中断，为0表示屏蔽中断
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_ADDR(base)  ((base) + (0x0238))

/* 寄存器说明：中断计数使能寄存器，软件调试使用
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_ADDR(base) ((base) + (0x0250))

/* 寄存器说明：中断计数使能寄存器，软件调试使用
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_ADDR(base) ((base) + (0x0254))

/* 寄存器说明：中断计数状态寄存器0。用于软件调试。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_ADDR(base) ((base) + (0x0258))

/* 寄存器说明：中断计数状态寄存器1。用于软件调试。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_ADDR(base) ((base) + (0x025C))

/* 寄存器说明：中断计数状态寄存器2。用于软件调试。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_ADDR(base) ((base) + (0x0260))

/* 寄存器说明：中断计数状态寄存器3。用于软件调试。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_ADDR(base) ((base) + (0x0264))

/* 寄存器说明：中断计数状态寄存器4。用于软件调试。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_ADDR(base) ((base) + (0x0268))

/* 寄存器说明：中断计数状态寄存器5。用于软件调试。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_UNION */
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_ADDR(base) ((base) + (0x026C))

/* 寄存器说明：BBP 单双TCXO时钟选择控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_ADDR(base) ((base) + (0x0270))

/* 寄存器说明：BBE16 debug reset控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_ADDR(base) ((base) + (0x0274))

/* 寄存器说明：timer使能寄存器0。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_ADDR(base)    ((base) + (0x02A0))

/* 寄存器说明：timer使能寄存器1。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_ADDR(base)    ((base) + (0x02A4))

/* 寄存器说明：timer使能寄存器2。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_ADDR(base)    ((base) + (0x02A8))

/* 寄存器说明：Modem子系统自定义CCPU remap冗错上报控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_ADDR(base) ((base) + (0x02AC))

/* 寄存器说明：Modem子系统自定义CCPU remap状态上报
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_ADDR(base) ((base) + (0x02B0))

/* 寄存器说明：Modem子系统自定义CCPU功 remap SRAM地址配置寄存器
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_ADDR(base) ((base) + (0x02B4))

/* 寄存器说明：Modem子系统自定义CCPU功能remap使能配置寄存器
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_ADDR(base) ((base) + (0x02B8))

/* 寄存器说明：Modem子系统自定义CCPU功能控制remap 基地址
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_ADDR(base) ((base) + (0x02BC))

/* 寄存器说明：Modem子系统自定义CCPU功能控制，debug相关
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_ADDR(base) ((base) + (0x02C0))

/* 寄存器说明：ALWAYSON和外设系统控制寄存器，功能包含SCI控制、NOC Timeout控制、TCXO AFC高阻控制、modem给sysnoc门控的投票
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_ADDR(base) ((base) + (0x02C4))

/* 寄存器说明：外设控制寄存器。功能包含UPACC、CICOM、CICOM模式选择、DMAC
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ADDR(base)  ((base) + (0x02C8))

/* 寄存器说明：外设状态寄存器，功能包含CICOM状态
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_ADDR(base)  ((base) + (0x02CC))

/* 寄存器说明：MDM_NOC总线上Master设备的优先级控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_ADDR(base) ((base) + (0x02D0))

/* 寄存器说明：MDM_NOC总线上Master设备的优先级控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_ADDR(base) ((base) + (0x02D4))

/* 寄存器说明：MDM_NOC总线上Master设备的优先级控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_ADDR(base) ((base) + (0x02D8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_ADDR(base) ((base) + (0x02DC))

/* 寄存器说明：外设控制寄存器。功能包含mdmsys_ramctrl_s和mdmsys_ramctrl_d1w2r控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_MEMCTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_ADDR(base)      ((base) + (0x02E0))

/* 寄存器说明：BBE16配置寄存器。功能包含BBE16的trace和notrace memory控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_ADDR(base) ((base) + (0x02E4))

/* 寄存器说明：Modem子系统自定义BBE16的控制。功能包括BBE16地址保护功能指示,BBE16分区即将下电请求，BBE16时钟树低功耗使能
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_ADDR(base) ((base) + (0x02E8))

/* 寄存器说明：BBE16 TCM 的BBE16和外部复用选择信号
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_ADDR(base) ((base) + (0x02EC))

/* 寄存器说明：BBE16控制寄存器，功能包含LTE总线优先级、LTEDSP控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_ADDR(base)  ((base) + (0x02F0))

/* 寄存器说明：BBP子系统控制寄存器，功能包含LTEDSP NMI中断请求
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_ADDR(base)  ((base) + (0x02F4))

/* 寄存器说明：BBE16状态寄存器。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_ADDR(base)  ((base) + (0x02F8))

/* 寄存器说明：BBP子系统状态寄存器，功能包含LTEDSP状态
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_ADDR(base)  ((base) + (0x02FC))

/* 寄存器说明：BBE16 访问DDR保护地址段配置，地址配置精度为1M
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_ADDR(base) ((base) + (0x0300))

/* 寄存器说明：MDMNOC power domain 控制寄存器
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_ADDR(base) ((base) + (0x0304))

/* 寄存器说明：MDMNOC power domain上报寄存器
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_ADDR(base) ((base) + (0x0308))

/* 寄存器说明：MDM_NOC总线上Master设备的优先级控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_UNION */
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_ADDR(base) ((base) + (0x030C))

/* 寄存器说明：BBP控制寄存器，功能包含BBP Local总线控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_ADDR(base) ((base) + (0x0310))

/* 寄存器说明：CCPU分区局部AXI总线状态上报
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ADDR(base) ((base) + (0x0314))

/* 寄存器说明：BBE16分区局部AXI总线状态上报
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_ADDR(base) ((base) + (0x0318))

/* 寄存器说明：MDM_NOC总线低功耗运行模式控制
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_UNION */
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_ADDR(base) ((base) + (0x031C))

/* 寄存器说明：时钟参数配置寄存器0
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_ADDR(base)  ((base) + (0x0320))

/* 寄存器说明：时钟参数配置寄存器1
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_ADDR(base)  ((base) + (0x0324))

/* 寄存器说明：时钟参数配置寄存器2
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_ADDR(base)  ((base) + (0x0328))

/* 寄存器说明：掉电区电源稳定计数器1。用于指示各掉电区电源调整后电压稳定所需的时间。该寄存器只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_ADDR(base)   ((base) + (0x0330))

/* 寄存器说明：掉电区电源稳定计数器1。用于指示各掉电区电源调整后电压稳定所需的时间。该寄存器只在上电复位时被复位。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_ADDR(base)   ((base) + (0x0334))

/* 寄存器说明：BBE16分区下电后SRAM地址控制寄存器。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_ADDR(base) ((base) + (0x0340))

/* 寄存器说明：BBE16访问DDR越界保护的映射地址值配置寄存器
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_ADDR(base) ((base) + (0x0344))

/* 寄存器说明：slicer count0
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_ADDR(base) ((base) + (0x0350))

/* 寄存器说明：slicer count1
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_ADDR(base) ((base) + (0x0354))

/* 寄存器说明：slicer count2
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_ADDR(base) ((base) + (0x0358))

/* 寄存器说明：slicer count3
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_ADDR(base) ((base) + (0x035C))

/* 寄存器说明：slicer count4
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_ADDR(base) ((base) + (0x0360))

/* 寄存器说明：slicer count5
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_ADDR(base) ((base) + (0x0364))

/* 寄存器说明：slicer count6
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_ADDR(base) ((base) + (0x0368))

/* 寄存器说明：slicer count7
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_ADDR(base) ((base) + (0x036C))

/* 寄存器说明：WBBPID寄存器。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_WBBPID_UNION */
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_ADDR(base)       ((base) + (0x0380))

/* 寄存器说明：GBBPID寄存器。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_GBBPID_UNION */
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_ADDR(base)       ((base) + (0x0384))

/* 寄存器说明：BBP可维可测读次数计数器
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_UNION */
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_ADDR(base) ((base) + (0x0388))

/* 寄存器说明：BBP可维可测读次数计数器
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_UNION */
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_ADDR(base) ((base) + (0x038C))

/* 寄存器说明：Modem 版本寄存器
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_UNION */
#define SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_ADDR(base)  ((base) + (0x0394))

/* 寄存器说明：保留寄存器，提供软件测试或调试使用。寄存器数值随系统复位
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_RESERVED01_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED01_ADDR(base)   ((base) + (0x0398))

/* 寄存器说明：保留寄存器，提供软件测试或调试使用。寄存器数值随系统复位
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_RESERVED02_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED02_ADDR(base)   ((base) + (0x039C))

/* 寄存器说明：保留上报寄存器，提供芯片ECO使用。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_RESERVED03_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED03_ADDR(base)   ((base) + (0x03A0))

/* 寄存器说明：保留寄存器，提供软件测试或调试使用。寄存器数值不随系统复位
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_RESERVED04_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED04_ADDR(base)   ((base) + (0x03A4))

/* 寄存器说明：保留寄存器，提供软件测试或调试使用。寄存器数值不随系统复位
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_RESERVED05_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED05_ADDR(base)   ((base) + (0x03A8))

/* 寄存器说明：保留寄存器，提供软件测试或调试使用。寄存器数值不随系统复位
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_RESERVED06_UNION */
#define SOC_MODEM_SCTRL_MDMSC_RESERVED06_ADDR(base)   ((base) + (0x03AC))

/* 寄存器说明：BBP中G/W/C送给ARM的唤醒指示(此寄存器只用于FPGA调试)
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_UNION */
#define SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_ADDR(base) ((base) + (0x03B0))

/* 寄存器说明：PMU SSI cnt计数上报(仅用于FPGA调试)
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_ADDR(base) ((base) + (0x03B4))

/* 寄存器说明：Modem子系统Modem_SC TESTPIN信号选择信号
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_UNION */
#define SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_ADDR(base)  ((base) + (0x03B8))

/* 寄存器说明：Modem子系统TESTPIN信号选择信号
   位域定义UNION结构:  SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_UNION */
#define SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_ADDR(base)  ((base) + (0x03BC))

/* 寄存器说明：BBIT MODEM子系统全局复位使能寄存器。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_ADDR(base) ((base) + (0x03D0))

/* 寄存器说明：BBIT MODEM子系统全局复位禁止寄存器。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_ADDR(base) ((base) + (0x03D4))

/* 寄存器说明：BBIT MODEM子系统全局复位状态寄存器。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
   位域定义UNION结构:  SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_UNION */
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_ADDR(base) ((base) + (0x03D8))





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
                     (1/1) cpu_if_mdm_sc_auto
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_UNION
 结构说明  : MDMSC_AO_CLKEN 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 上电区时钟使能寄存器。用于使能外设时钟。对比特写1，使能对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_clken_sci0_pclk         : 1;  /* bit[0]    : [0] : SCI0 工作时钟 */
        unsigned int  ao_peri_clken_sci1_pclk         : 1;  /* bit[1]    : [1] : SCI1 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer0_pclk : 1;  /* bit[2]    : [2] : Modem侧 Timer0 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer1_pclk : 1;  /* bit[3]    : [3] : Modem侧 Timer1 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer2_pclk : 1;  /* bit[4]    : [4] : Modem侧 Timer2 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer3_pclk : 1;  /* bit[5]    : [5] : Modem侧 Timer3 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer4_pclk : 1;  /* bit[6]    : [6] : Modem侧 Timer4 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer5_pclk : 1;  /* bit[7]    : [7] : Modem侧 Timer5 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer6_pclk : 1;  /* bit[8]    : [8] : Modem侧 Timer6 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer7_pclk : 1;  /* bit[9]    : [9] : Modem侧 Timer7 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer8_pclk : 1;  /* bit[10]   : [10] : Modem侧 Timer8 工作时钟 */
        unsigned int  ao_peri_clken_modem_timer9_pclk : 1;  /* bit[11]   : [11] : Modem侧 Timer9 工作时钟 */
        unsigned int  ao_peri_clken_watchdog0_pclk    : 1;  /* bit[12]   : [12] : ccpu Watchdog 工作时钟 */
        unsigned int  ao_peri_clken_watchdog1_pclk    : 1;  /* bit[13]   : [13]: bbe16 Watchdog 工作时钟 */
        unsigned int  ao_peri_clken_apb_bbp_on        : 1;  /* bit[14]   : [14] : BBP上电区APB接口时钟 */
        unsigned int  ao_peri_clken_19m_bbp_on        : 1;  /* bit[15]   : [15] : BBP上电区tcxo时钟 */
        unsigned int  reserved_0                      : 1;  /* bit[16]   : reserved */
        unsigned int  ao_peri_clken_104m_gbbp1_on     : 1;  /* bit[17]   : [17]:bbp上电区GU时钟clk_104m_gbbp1_on */
        unsigned int  reserved_1                      : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                      : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_clken_104m_gbbp2_on     : 1;  /* bit[20]   : [20]:bbp上电区GU时钟clk_104m_gbbp2_on */
        unsigned int  reserved_3                      : 11; /* bit[21-31]: 时钟使能定义如下（写1时钟打开）： */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_sci0_pclk_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_sci0_pclk_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_sci1_pclk_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_sci1_pclk_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer0_pclk_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer0_pclk_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer1_pclk_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer1_pclk_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer2_pclk_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer2_pclk_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer3_pclk_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer3_pclk_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer4_pclk_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer4_pclk_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer5_pclk_START  (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer5_pclk_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer6_pclk_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer6_pclk_END    (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer7_pclk_START  (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer7_pclk_END    (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer8_pclk_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer8_pclk_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer9_pclk_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_modem_timer9_pclk_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_watchdog0_pclk_START     (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_watchdog0_pclk_END       (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_watchdog1_pclk_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_watchdog1_pclk_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_apb_bbp_on_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_apb_bbp_on_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_19m_bbp_on_START         (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_19m_bbp_on_END           (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_104m_gbbp1_on_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_104m_gbbp1_on_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_104m_gbbp2_on_START      (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_ao_peri_clken_104m_gbbp2_on_END        (20)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_UNION
 结构说明  : MDMSC_AO_CLKDIS 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 上电区时钟禁止寄存器。用于禁止外设时钟。对比特写1，禁止对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_clkdis_sci0_pclk         : 1;  /* bit[0]    : [0] : SCI0 工作时钟 */
        unsigned int  ao_peri_clkdis_sci1_pclk         : 1;  /* bit[1]    : [1] : SCI1 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer0_pclk : 1;  /* bit[2]    : [2] : Modem侧 Timer0 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer1_pclk : 1;  /* bit[3]    : [3] : Modem侧 Timer1 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer2_pclk : 1;  /* bit[4]    : [4] : Modem侧 Timer2 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer3_pclk : 1;  /* bit[5]    : [5] : Modem侧 Timer3 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer4_pclk : 1;  /* bit[6]    : [6] : Modem侧 Timer4 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer5_pclk : 1;  /* bit[7]    : [7] : Modem侧 Timer5 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer6_pclk : 1;  /* bit[8]    : [8] : Modem侧 Timer6 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer7_pclk : 1;  /* bit[9]    : [9] : Modem侧 Timer7 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer8_pclk : 1;  /* bit[10]   : [10] : Modem侧 Timer8 工作时钟 */
        unsigned int  ao_peri_clkdis_modem_timer9_pclk : 1;  /* bit[11]   : [11] : Modem侧 Timer9 工作时钟 */
        unsigned int  ao_peri_clkdis_watchdog0_pclk    : 1;  /* bit[12]   : [12] : ccpu Watchdog 工作时钟 */
        unsigned int  ao_peri_clkdis_watchdog1_pclk    : 1;  /* bit[13]   : [13]: bbe16 Watchdog 工作时钟 */
        unsigned int  ao_peri_clkdis_apb_bbp_on        : 1;  /* bit[14]   : [14] : BBP上电区APB接口时钟 */
        unsigned int  ao_peri_clkdis_19m_bbp_on        : 1;  /* bit[15]   : [15] : BBP上电区tcxo时钟 */
        unsigned int  reserved_0                       : 1;  /* bit[16]   : reserved */
        unsigned int  ao_peri_clkdis_104m_gbbp1_on     : 1;  /* bit[17]   : [17]:bbp上电区GU时钟clk_104m_gbbp1_on */
        unsigned int  reserved_1                       : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                       : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_clkdis_104m_gbbp2_on     : 1;  /* bit[20]   : [20]:bbp上电区GU时钟clk_104m_gbbp2_on */
        unsigned int  reserved_3                       : 11; /* bit[21-31]: 时钟禁止定义如下（写1时钟关闭）：  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_sci0_pclk_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_sci0_pclk_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_sci1_pclk_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_sci1_pclk_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer0_pclk_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer0_pclk_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer1_pclk_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer1_pclk_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer2_pclk_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer2_pclk_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer3_pclk_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer3_pclk_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer4_pclk_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer4_pclk_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer5_pclk_START  (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer5_pclk_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer6_pclk_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer6_pclk_END    (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer7_pclk_START  (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer7_pclk_END    (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer8_pclk_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer8_pclk_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer9_pclk_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_modem_timer9_pclk_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_watchdog0_pclk_START     (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_watchdog0_pclk_END       (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_watchdog1_pclk_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_watchdog1_pclk_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_apb_bbp_on_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_apb_bbp_on_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_19m_bbp_on_START         (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_19m_bbp_on_END           (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_104m_gbbp1_on_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_104m_gbbp1_on_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_104m_gbbp2_on_START      (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKDIS_ao_peri_clkdis_104m_gbbp2_on_END        (20)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_UNION
 结构说明  : MDMSC_AO_CLKEN_STAT 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 上电区时钟状态寄存器。用于回读各外设时钟的状态。外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_clken_stat_sci0_pclk         : 1;  /* bit[0]    : [0] : SCI0 工作时钟 */
        unsigned int  ao_peri_clken_stat_sci1_pclk         : 1;  /* bit[1]    : [1] : SCI1 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer0_pclk : 1;  /* bit[2]    : [2] : Modem侧 Timer0 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer1_pclk : 1;  /* bit[3]    : [3] : Modem侧 Timer1 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer2_pclk : 1;  /* bit[4]    : [4] : Modem侧 Timer2 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer3_pclk : 1;  /* bit[5]    : [5] : Modem侧 Timer3 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer4_pclk : 1;  /* bit[6]    : [6] : Modem侧 Timer4 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer5_pclk : 1;  /* bit[7]    : [7] : Modem侧 Timer5 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer6_pclk : 1;  /* bit[8]    : [8] : Modem侧 Timer6 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer7_pclk : 1;  /* bit[9]    : [9] : Modem侧 Timer7 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer8_pclk : 1;  /* bit[10]   : [10] : Modem侧 Timer8 工作时钟 */
        unsigned int  ao_peri_clken_stat_modem_timer9_pclk : 1;  /* bit[11]   : [11] : Modem侧 Timer9 工作时钟 */
        unsigned int  ao_peri_clken_stat_watchdog0_pclk    : 1;  /* bit[12]   : [12] : ccpu Watchdog 工作时钟 */
        unsigned int  ao_peri_clken_stat_watchdog1_pclk    : 1;  /* bit[13]   : [13]: bbe16 Watchdog 工作时钟 */
        unsigned int  ao_peri_clken_stat_apb_bbp_on        : 1;  /* bit[14]   : [14] : BBP上电区APB接口时钟 */
        unsigned int  ao_peri_clken_stat_19m_bbp_on        : 1;  /* bit[15]   : [15] : BBP上电区tcxo时钟 */
        unsigned int  reserved_0                           : 1;  /* bit[16]   : reserved */
        unsigned int  ao_peri_clken_stat_104m_gbbp1_on     : 1;  /* bit[17]   : [17]:bbp上电区GU时钟clk_104m_gbbp1_on */
        unsigned int  reserved_1                           : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                           : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_clken_stat_104m_gbbp2_on     : 1;  /* bit[20]   : [20]:bbp上电区GU时钟clk_104m_gbbp2_on */
        unsigned int  reserved_3                           : 11; /* bit[21-31]: 时钟状态定义如下（高电平表示时钟打开）：  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_sci0_pclk_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_sci0_pclk_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_sci1_pclk_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_sci1_pclk_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer0_pclk_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer0_pclk_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer1_pclk_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer1_pclk_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer2_pclk_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer2_pclk_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer3_pclk_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer3_pclk_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer4_pclk_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer4_pclk_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer5_pclk_START  (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer5_pclk_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer6_pclk_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer6_pclk_END    (8)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer7_pclk_START  (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer7_pclk_END    (9)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer8_pclk_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer8_pclk_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer9_pclk_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_modem_timer9_pclk_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_watchdog0_pclk_START     (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_watchdog0_pclk_END       (12)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_watchdog1_pclk_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_watchdog1_pclk_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_apb_bbp_on_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_apb_bbp_on_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_19m_bbp_on_START         (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_19m_bbp_on_END           (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_104m_gbbp1_on_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_104m_gbbp1_on_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_104m_gbbp2_on_START      (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_CLKEN_STAT_ao_peri_clken_stat_104m_gbbp2_on_END        (20)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_UNION
 结构说明  : MDMSC_AO_RSTEN 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 上电区复位使能寄存器。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_rsten_sci0                  : 1;  /* bit[0]    : [0] : SCI0工作时钟域软复位 */
        unsigned int  ao_peri_rsten_sci1                  : 1;  /* bit[1]    : [1] : SCI1工作时钟域软复位 */
        unsigned int  reserved_0                          : 12; /* bit[2-13] : reserved */
        unsigned int  ao_peri_rsten_reset_apb_bbp_on_n    : 1;  /* bit[14]   : [14] :BBP上电区复位 reset_apb_bbp_on_n */
        unsigned int  ao_peri_rsten_reset_19m_bbp_on_n    : 1;  /* bit[15]   : [15] : BBP上电区复位reset_19m_bbp_on_n */
        unsigned int  ao_peri_rsten_reset_32k_bbp_on_n    : 1;  /* bit[16]   : [16] :BBP上电区复位 reset_32k_bbp_on_n */
        unsigned int  ao_peri_rsten_reset_104m_gbbp1_on_n : 1;  /* bit[17]   : [17] : BBP上电区复位reset_104m_gbbp1_on_n */
        unsigned int  reserved_1                          : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                          : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_rsten_reset_104m_gbbp2_on_n : 1;  /* bit[20]   : [20] : BBP上电区复位reset_104m_gbbp2_on_n */
        unsigned int  reserved_3                          : 11; /* bit[21-31]: 复位使能定义如下（写1复位使能）。
                                                                               [31:21] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_sci0_START                   (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_sci0_END                     (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_sci1_START                   (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_sci1_END                     (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_apb_bbp_on_n_START     (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_apb_bbp_on_n_END       (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_19m_bbp_on_n_START     (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_19m_bbp_on_n_END       (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_32k_bbp_on_n_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_32k_bbp_on_n_END       (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_104m_gbbp1_on_n_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_104m_gbbp1_on_n_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_104m_gbbp2_on_n_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_ao_peri_rsten_reset_104m_gbbp2_on_n_END    (20)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_UNION
 结构说明  : MDMSC_AO_RSTDIS 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 上电区复位禁止寄存器。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_rstdis_sci0                  : 1;  /* bit[0]    : [0] : SCI0工作时钟域软复位 */
        unsigned int  ao_peri_rstdis_sci1                  : 1;  /* bit[1]    : [1] : SCI1工作时钟域软复位 */
        unsigned int  reserved_0                           : 12; /* bit[2-13] : reserved */
        unsigned int  ao_peri_rstdis_reset_apb_bbp_on_n    : 1;  /* bit[14]   : [14] :BBP上电区复位 reset_apb_bbp_on_n */
        unsigned int  ao_peri_rstdis_reset_19m_bbp_on_n    : 1;  /* bit[15]   : [15] : BBP上电区复位reset_19m_bbp_on_n */
        unsigned int  ao_peri_rstdis_reset_32k_bbp_on_n    : 1;  /* bit[16]   : [16] :BBP上电区复位 reset_32k_bbp_on_n */
        unsigned int  ao_peri_rstdis_reset_104m_gbbp1_on_n : 1;  /* bit[17]   : [17] : BBP上电区复位reset_104m_gbbp1_on_n */
        unsigned int  reserved_1                           : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                           : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_rstdis_reset_104m_gbbp2_on_n : 1;  /* bit[20]   : [20] : BBP上电区复位reset_104m_gbbp2_on_n */
        unsigned int  reserved_3                           : 11; /* bit[21-31]: 复位禁止定义如下（写1复位解除）。
                                                                                [31:21] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_sci0_START                   (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_sci0_END                     (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_sci1_START                   (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_sci1_END                     (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_apb_bbp_on_n_START     (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_apb_bbp_on_n_END       (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_19m_bbp_on_n_START     (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_19m_bbp_on_n_END       (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_32k_bbp_on_n_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_32k_bbp_on_n_END       (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_104m_gbbp1_on_n_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_104m_gbbp1_on_n_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_104m_gbbp2_on_n_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTDIS_ao_peri_rstdis_reset_104m_gbbp2_on_n_END    (20)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_UNION
 结构说明  : MDMSC_AO_RSTEN_STAT 寄存器结构定义。地址偏移量:0x0020，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 上电区复位状态寄存器。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_peri_rsten_stat_sci0            : 1;  /* bit[0]    : [0] : SCI0工作时钟域软复位 */
        unsigned int  ao_peri_rsten_stat_sci1            : 1;  /* bit[1]    : [1] : SCI1工作时钟域软复位 */
        unsigned int  reserved_0                         : 12; /* bit[2-13] : reserved */
        unsigned int  ao_peri_rsten_stat_apb_bbp_on_n    : 1;  /* bit[14]   : [14] :BBP上电区复位 reset_apb_bbp_on_n */
        unsigned int  ao_peri_rsten_stat_19m_bbp_on_n    : 1;  /* bit[15]   : [15] : BBP上电区复位reset_19m_bbp_on_n */
        unsigned int  ao_peri_rsten_stat_32k_bbp_on_n    : 1;  /* bit[16]   : [16] :BBP上电区复位 reset_32k_bbp_on_n */
        unsigned int  ao_peri_rsten_stat_104m_gbbp1_on_n : 1;  /* bit[17]   : [17] : BBP上电区复位reset_104m_gbbp1_on_n */
        unsigned int  reserved_1                         : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_2                         : 1;  /* bit[19]   : reserved */
        unsigned int  ao_peri_rsten_stat_104m_gbbp2_on_n : 1;  /* bit[20]   : [20] : BBP上电区复位reset_104m_gbbp2_on_n */
        unsigned int  reserved_3                         : 11; /* bit[21-31]: 复位状态定义如下（高电平表示处于复位）
                                                                              [31:21] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_sci0_START             (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_sci0_END               (0)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_sci1_START             (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_sci1_END               (1)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_apb_bbp_on_n_START     (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_apb_bbp_on_n_END       (14)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_19m_bbp_on_n_START     (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_19m_bbp_on_n_END       (15)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_32k_bbp_on_n_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_32k_bbp_on_n_END       (16)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_104m_gbbp1_on_n_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_104m_gbbp1_on_n_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_104m_gbbp2_on_n_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_AO_RSTEN_STAT_ao_peri_rsten_stat_104m_gbbp2_on_n_END    (20)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_UNION
 结构说明  : MDMSC_PW_CLKEN 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 掉电区时钟使能寄存器。用于控制各掉电区总的时钟使能。对相应位写1使能相应电压域时钟，写0无影响。该寄存器只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_clken_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_clken_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区  */
        unsigned int  pw_clken_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0      : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1      : 28; /* bit[4-31]: [31:4]：保留
                                                            */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_pw_clken_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_UNION
 结构说明  : MDMSC_PW_CLKDIS 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 掉电区时钟禁止寄存器。用于控制各掉电区总的时钟禁止。对相应位写1禁止相应掉电区时钟，写0无影响。该寄存器只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_clkdis_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_clkdis_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区  */
        unsigned int  pw_clkdis_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0       : 1;  /* bit[3]   : [3]：BBP PS下电区  */
        unsigned int  reserved_1       : 28; /* bit[4-31]: [31:4]：保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKDIS_pw_clkdis_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_UNION
 结构说明  : MDMSC_PW_CLKEN_STAT 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: 下电区时钟状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_clken_stat_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_clken_stat_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区  */
        unsigned int  pw_clken_stat_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0           : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1           : 28; /* bit[4-31]: 0：关闭；
                                                               1：打开。
                                                               [31:4]：保留  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_CLKEN_STAT_pw_clken_stat_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_UNION
 结构说明  : MDMSC_PW_RSTEN 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 掉电区复位使能寄存器。用于控制各掉电区总的复位使能。对相应位写1使能相应掉电区复位信号（即进入复位态），写0无影响。该寄存器只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_rsten_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_rsten_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区  */
        unsigned int  pw_rsten_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0      : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1      : 28; /* bit[4-31]: [31:4]：保留
                                                            */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_pw_rsten_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_UNION
 结构说明  : MDMSC_PW_RSTDIS 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 掉电区复位禁止寄存器。用于控制各掉电区总的复位禁止。对相应位写1禁止相应掉电区复位信号（即退出复位态），写0无影响。该寄存器只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_rstdis_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_rstdis_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区  */
        unsigned int  pw_rstdis_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0       : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1       : 28; /* bit[4-31]: [31:4]：保留
                                                             */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTDIS_pw_rstdis_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_UNION
 结构说明  : MDMSC_PW_RSTEN_STAT 寄存器结构定义。地址偏移量:0x0054，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 下电区复位状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_rsten_stat_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_rsten_stat_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区  */
        unsigned int  pw_rsten_stat_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0           : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1           : 28; /* bit[4-31]: 下电区复位状态。
                                                               [31:4]：保留
                                                               0：复位不使能；
                                                               1：复位使能。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_RSTEN_STAT_pw_rsten_stat_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_UNION
 结构说明  : MDMSC_PW_ISOEN 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 掉电区ISO使能寄存器。用于控制各掉电区相关的Isolation Cell使能。对相应位写1使能相应掉电区IsoLation Cell（即信号隔断），写0无影响。该寄存器只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_isoen_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_isoen_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区(无MTCMOS隔离，此信号无用)  */
        unsigned int  pw_isoen_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0      : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1      : 28; /* bit[4-31]: [31:4]：保留
                                                            */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_pw_isoen_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_UNION
 结构说明  : MDMSC_PW_ISODIS 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 掉电区ISO禁止寄存器。用于控制各掉电区相关的Isolation Cell禁止。对相应位写1禁止相应掉电区IsoLation Cell（即信号不隔断），写0无影响。该寄存器只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_isodis_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_isodis_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区(无MTCMOS隔离，此信号无用)  */
        unsigned int  pw_isodis_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0       : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1       : 28; /* bit[4-31]: [31:4]：保留
                                                             */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISODIS_pw_isodis_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_UNION
 结构说明  : MDMSC_PW_ISOEN_STAT 寄存器结构定义。地址偏移量:0x0060，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 下电区ISO状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_iso_stat_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_iso_stat_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区(无MTCMOS隔离，此信号无用)  */
        unsigned int  pw_iso_stat_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0         : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1         : 28; /* bit[4-31]: 下电区ISO状态。[31:4]：保留
                                                             0：isolation不使能；
                                                             1：isolation使能。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_ISOEN_STAT_pw_iso_stat_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_UNION
 结构说明  : MDMSC_PW_MTCMOSEN 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: 掉电区电源使能寄存器。用于控制各掉电区的电源使能，对相应位写1打开相应电压域电源，写0无影响。该寄存器存只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmosen_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_mtcmosen_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区(无MTCMOS隔离，此信号无用)  */
        unsigned int  pw_mtcmosen_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0         : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1         : 28; /* bit[4-31]: [31:4]：保留  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSEN_pw_mtcmosen_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_UNION
 结构说明  : MDMSC_PW_MTCMOSDIS 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 掉电区电源禁止寄存器。用于控制各掉电区的电源禁止，对相应位写1关闭相应电压域电源，写0无影响。该寄存器存只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmosdis_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_mtcmosdis_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区(无MTCMOS隔离，此信号无用)  */
        unsigned int  pw_mtcmosdis_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0          : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1          : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOSDIS_pw_mtcmosdis_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_UNION
 结构说明  : MDMSC_PW_MTCMOS_STAT 寄存器结构定义。地址偏移量:0x006C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 掉电区电源配置状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmos_stat_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_mtcmos_stat_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区(无MTCMOS隔离，此信号无用)  */
        unsigned int  pw_mtcmos_stat_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0            : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1            : 28; /* bit[4-31]: 下电区MTCMOS状态。[31:4]：保留
                                                                1:mtcmos打开
                                                                0:mtcmos关闭 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_STAT_pw_mtcmos_stat_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_UNION
 结构说明  : MDMSC_PW_MTCMOS_ACK_SUB 寄存器结构定义。地址偏移量:0x0074，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 下电区MTCMOS延时链电源反馈信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmos_ack_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_mtcmos_ack_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区(无MTCMOS隔离，此信号无用)  */
        unsigned int  pw_mtcmos_ack_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0           : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1           : 28; /* bit[4-31]: 下电区MTCMOS延时链电源反馈信号。
                                                               0：电源关闭；
                                                               1：电源打开。
                                                               [31:4]：保留  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_ACK_SUB_pw_mtcmos_ack_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_UNION
 结构说明  : MDMSC_PW_MTCMOS_TIMEOUT_STAT 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 系统POWER状态寄存器。用于监测系统所处的POWER状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pw_mtcmos_timeout_stat_dspbbe : 1;  /* bit[0]   : [0]：DSPBBE下电区 */
        unsigned int  pw_mtcmos_timeout_stat_bbp_cs : 1;  /* bit[1]   : [1]：BBP CS下电区  */
        unsigned int  pw_mtcmos_timeout_stat_lte    : 1;  /* bit[2]   : [2]：LTEBBPTOP下电区  */
        unsigned int  reserved_0                    : 1;  /* bit[3]   : [3]：BBP PS下电区(保留，因Harq Mem共享，移到AO_Sctrl中)  */
        unsigned int  reserved_1                    : 28; /* bit[4-31]: 下电区MTCMOS稳定计数器溢出指示信号。
                                                                        [31:4]：保留 
                                                                        0：未溢出；
                                                                        1：MTCMOS稳定状态。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_dspbbe_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_bbp_cs_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_bbp_cs_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_lte_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_PW_MTCMOS_TIMEOUT_STAT_pw_mtcmos_timeout_stat_lte_END       (2)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_UNION
 结构说明  : MDMSC_PERIPH_CLKEN 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器。用于使能外设时钟。对比特写1，使能对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                  : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                  : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                  : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                  : 1;  /* bit[3]    : reserved */
        unsigned int  periph_clken_bbe16_kernel   : 1;  /* bit[4]    : BBE16内核时钟 */
        unsigned int  periph_clken_clk_bbe16_lbus : 1;  /* bit[5]    : BBE16 局部AXI总线时钟 */
        unsigned int  reserved_4                  : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                  : 1;  /* bit[7]    : reserved */
        unsigned int  periph_clken_modem_dmac     : 1;  /* bit[8]    : ModemDMAC工作时钟 */
        unsigned int  periph_clken_cicom_upacc    : 1;  /* bit[9]    : UPACC时钟 */
        unsigned int  reserved_6                  : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                  : 1;  /* bit[11]   : reserved */
        unsigned int  periph_clken_cicom_l_cipher : 1;  /* bit[12]   : LCIPHER时钟 */
        unsigned int  periph_clken_cicom_gu0      : 1;  /* bit[13]   : GUCIPHER0时钟 */
        unsigned int  reserved_8                  : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                  : 1;  /* bit[15]   : reserved */
        unsigned int  periph_clken_modem_uart0    : 1;  /* bit[16]   : Modem侧UART0工作时钟 */
        unsigned int  reserved_10                 : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                 : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_12                 : 13; /* bit[19-31]: 时钟使能定义如下（写1时钟打开）：Modem子系统外设IP时钟控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_bbe16_kernel_START    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_bbe16_kernel_END      (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_clk_bbe16_lbus_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_clk_bbe16_lbus_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_modem_dmac_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_modem_dmac_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_upacc_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_upacc_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_l_cipher_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_l_cipher_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_gu0_START       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_cicom_gu0_END         (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_modem_uart0_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_periph_clken_modem_uart0_END       (16)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_UNION
 结构说明  : MDMSC_PERIPH_CLKDIS 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器。用于禁止外设时钟。对比特写1，禁止对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                   : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                   : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                   : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                   : 1;  /* bit[3]    : reserved */
        unsigned int  periph_clkdis_bbe16_kernel   : 1;  /* bit[4]    : BBE16内核时钟 */
        unsigned int  periph_clkdis_clk_bbe16_lbus : 1;  /* bit[5]    : BBE16 局部AXI总线时钟 */
        unsigned int  reserved_4                   : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                   : 1;  /* bit[7]    : reserved */
        unsigned int  periph_clkdis_modem_dmac     : 1;  /* bit[8]    : ModemDMAC工作时钟 */
        unsigned int  periph_clkdis_cicom_upacc    : 1;  /* bit[9]    : UPACC时钟 */
        unsigned int  reserved_6                   : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                   : 1;  /* bit[11]   : reserved */
        unsigned int  periph_clkdis_cicom_l_cipher : 1;  /* bit[12]   : LCIPHER时钟 */
        unsigned int  periph_clkdis_cicom_gu0      : 1;  /* bit[13]   : GUCIPHER0时钟 */
        unsigned int  reserved_8                   : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                   : 1;  /* bit[15]   : reserved */
        unsigned int  periph_clkdis_modem_uart0    : 1;  /* bit[16]   : Modem侧UART0工作时钟 */
        unsigned int  reserved_10                  : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                  : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_12                  : 13; /* bit[19-31]: 时钟禁止定义如下（写1时钟关闭）：Modem子系统外设IP时钟控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_bbe16_kernel_START    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_bbe16_kernel_END      (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_clk_bbe16_lbus_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_clk_bbe16_lbus_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_modem_dmac_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_modem_dmac_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_upacc_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_upacc_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_l_cipher_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_l_cipher_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_gu0_START       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_cicom_gu0_END         (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_modem_uart0_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKDIS_periph_clkdis_modem_uart0_END       (16)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_UNION
 结构说明  : MDMSC_PERIPH_CLKEN_STAT 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟状态寄存器9。用于回读各外设时钟的状态。外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                       : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                       : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                       : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                       : 1;  /* bit[3]    : reserved */
        unsigned int  periph_clken_stat_bbe16_kernel   : 1;  /* bit[4]    : BBE16内核时钟 */
        unsigned int  periph_clken_stat_clk_bbe16_lbus : 1;  /* bit[5]    : BBE16 局部AXI总线时钟 */
        unsigned int  reserved_4                       : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                       : 1;  /* bit[7]    : reserved */
        unsigned int  periph_clken_stat_modem_dmac     : 1;  /* bit[8]    : ModemDMAC工作时钟 */
        unsigned int  periph_clken_stat_cicom_upacc    : 1;  /* bit[9]    : UPACC时钟 */
        unsigned int  reserved_6                       : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                       : 1;  /* bit[11]   : reserved */
        unsigned int  periph_clken_stat_cicom_l_cipher : 1;  /* bit[12]   : LCIPHER时钟 */
        unsigned int  periph_clken_stat_cicom_gu0      : 1;  /* bit[13]   : GUCIPHER0时钟 */
        unsigned int  reserved_8                       : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                       : 1;  /* bit[15]   : reserved */
        unsigned int  periph_clken_stat_modem_uart0    : 1;  /* bit[16]   : Modem侧UART0工作时钟 */
        unsigned int  reserved_10                      : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                      : 1;  /* bit[18]   : reserved */
        unsigned int  reserved_12                      : 13; /* bit[19-31]: 时钟状态定义如下（高电平表示时钟打开）：Modem子系统外设IP时钟控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_bbe16_kernel_START    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_bbe16_kernel_END      (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_clk_bbe16_lbus_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_clk_bbe16_lbus_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_modem_dmac_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_modem_dmac_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_upacc_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_upacc_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_l_cipher_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_l_cipher_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_gu0_START       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_cicom_gu0_END         (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_modem_uart0_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CLKEN_STAT_periph_clken_stat_modem_uart0_END       (16)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_UNION
 结构说明  : MDMSC_BBP_CLKEN0 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: BBP时钟使能寄存器0。用于使能外设时钟。对比特写1，使能对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clken0_122m_tds         : 1;  /* bit[0]    : clk_122m_tds */
        unsigned int  bbp_clken0_245m_tds         : 1;  /* bit[1]    : clk_245m_tds */
        unsigned int  bbp_clken0_19m_cs           : 1;  /* bit[2]    : clk_19m_cs */
        unsigned int  reserved_0                  : 1;  /* bit[3]    : reserved */
        unsigned int  bbp_clken0_122m_twc         : 1;  /* bit[4]    : clk_122_twc */
        unsigned int  reserved_1                  : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clken0_122m_wc_abb      : 1;  /* bit[6]    : clk_122m_wc_abb */
        unsigned int  bbp_clken0_61m_wbbp_cs      : 1;  /* bit[7]    : clk_61m_wbbp_cs */
        unsigned int  bbp_clken0_122m_wbbp_cs     : 1;  /* bit[8]    : clk_122m_wbbp_cs */
        unsigned int  bbp_clken0_122m_tw          : 1;  /* bit[9]    : clk_122m_tw */
        unsigned int  bbp_clken0_104m_gbbp1       : 1;  /* bit[10]   : clk_104m_gbbp1 */
        unsigned int  bbp_clken0_axis_cs          : 1;  /* bit[11]   : clk_axis_cs */
        unsigned int  bbp_clken0_122m_cbbp        : 1;  /* bit[12]   : clk_122m_cbbp */
        unsigned int  reserved_2                  : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_clken0_axim_bbc         : 1;  /* bit[14]   : clk_axim_bbc */
        unsigned int  bbp_clken0_122m_lte_pdf_bbc : 1;  /* bit[15]   : clk_122m_lte_pdf_bbc */
        unsigned int  bbp_clken0_122m_lte_pdt_bbc : 1;  /* bit[16]   : clk_122m_lte_pdt_bbc */
        unsigned int  bbp_clken0_245m_lte_bbc     : 1;  /* bit[17]   : clk_245m_lte_bbc */
        unsigned int  bbp_clken0_245m_wbbp_cs     : 1;  /* bit[18]   : clk_245m_wbbp_cs */
        unsigned int  bbp_clken0_104m_gbbp_sdr    : 1;  /* bit[19]   : clk_104m_gbbp_sdr */
        unsigned int  bbp_clken0_245m_wbbp_sdr    : 1;  /* bit[20]   : clk_245m_wbbp_sdr */
        unsigned int  bbp_clken0_104m_gbbp2       : 1;  /* bit[21]   : clk_104m_gbbp2 */
        unsigned int  bbp_clken0_150m_noc_cs      : 1;  /* bit[22]   : clk_150m_noc_cs */
        unsigned int  bbp_clken0_axim_bbpmst      : 1;  /* bit[23]   : clk_axim_bbpmst */
        unsigned int  bbp_clken0_19m_ch0_bbc      : 1;  /* bit[24]   : clk_19m_ch0_bbc */
        unsigned int  bbp_clken0_19m_ch1_bbc      : 1;  /* bit[25]   : clk_19m_ch1_bbc */
        unsigned int  reserved_3                  : 6;  /* bit[26-31]: 时钟使能定义如下（写1时钟打开）：BBP CS分区相关时钟控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN0_bbp_clken0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_UNION
 结构说明  : MDMSC_BBP_CLKDIS0 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器0。用于禁止外设时钟。对比特写1，禁止对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clkdis0_122m_tds         : 1;  /* bit[0]    : clk_122m_tds */
        unsigned int  bbp_clkdis0_245m_tds         : 1;  /* bit[1]    : clk_245m_tds */
        unsigned int  bbp_clkdis0_19m_cs           : 1;  /* bit[2]    : clk_19m_cs */
        unsigned int  reserved_0                   : 1;  /* bit[3]    : reserved */
        unsigned int  bbp_clkdis0_122m_twc         : 1;  /* bit[4]    : clk_122_twc */
        unsigned int  reserved_1                   : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clkdis0_122m_wc_abb      : 1;  /* bit[6]    : clk_122m_wc_abb */
        unsigned int  bbp_clkdis0_61m_wbbp_cs      : 1;  /* bit[7]    : clk_61m_wbbp_cs */
        unsigned int  bbp_clkdis0_122m_wbbp_cs     : 1;  /* bit[8]    : clk_122m_wbbp_cs */
        unsigned int  bbp_clkdis0_122m_tw          : 1;  /* bit[9]    : clk_122m_tw */
        unsigned int  bbp_clkdis0_104m_gbbp1       : 1;  /* bit[10]   : clk_104m_gbbp1 */
        unsigned int  bbp_clkdis0_axis_cs          : 1;  /* bit[11]   : clk_axis_cs */
        unsigned int  bbp_clkdis0_122m_cbbp        : 1;  /* bit[12]   : clk_122m_cbbp */
        unsigned int  reserved_2                   : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_clkdis0_axim_bbc         : 1;  /* bit[14]   : clk_axim_bbc */
        unsigned int  bbp_clkdis0_122m_lte_pdf_bbc : 1;  /* bit[15]   : clk_122m_lte_pdf_bbc */
        unsigned int  bbp_clkdis0_122m_lte_pdt_bbc : 1;  /* bit[16]   : clk_122m_lte_pdt_bbc */
        unsigned int  bbp_clkdis0_245m_lte_bbc     : 1;  /* bit[17]   : clk_245m_lte_bbc */
        unsigned int  bbp_clkdis0_245m_wbbp_cs     : 1;  /* bit[18]   : clk_245m_wbbp_cs */
        unsigned int  bbp_clkdis0_104m_gbbp_sdr    : 1;  /* bit[19]   : clk_104m_gbbp_sdr */
        unsigned int  bbp_clkdis0_245m_wbbp_sdr    : 1;  /* bit[20]   : clk_245m_wbbp_sdr */
        unsigned int  bbp_clkdis0_104m_gbbp2       : 1;  /* bit[21]   : clk_104m_gbbp2 */
        unsigned int  bbp_clkdis0_150m_noc_cs      : 1;  /* bit[22]   : clk_150m_noc_cs */
        unsigned int  bbp_clkdis0_axim_bbpmst      : 1;  /* bit[23]   : clk_axim_bbpmst */
        unsigned int  bbp_clkdis0_19m_ch0_bbc      : 1;  /* bit[24]   : clk_19m_ch0_bbc */
        unsigned int  bbp_clkdis0_19m_ch1_bbc      : 1;  /* bit[25]   : clk_19m_ch1_bbc */
        unsigned int  reserved_3                   : 6;  /* bit[26-31]: 时钟禁止定义如下（写1时钟关闭）：BBP CS分区相关时钟控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS0_bbp_clkdis0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_UNION
 结构说明  : MDMSC_BBP_CLKEN_STAT0 寄存器结构定义。地址偏移量:0x0128，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟状态寄存器0。用于回读各外设时钟的状态。外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clken_stat0_122m_tds         : 1;  /* bit[0]    : clk_122m_tds */
        unsigned int  bbp_clken_stat0_245m_tds         : 1;  /* bit[1]    : clk_245m_tds */
        unsigned int  bbp_clken_stat0_19m_cs           : 1;  /* bit[2]    : clk_19m_cs */
        unsigned int  reserved_0                       : 1;  /* bit[3]    : reserved */
        unsigned int  bbp_clken_stat0_122m_twc         : 1;  /* bit[4]    : clk_122_twc */
        unsigned int  reserved_1                       : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clken_stat0_122m_wc_abb      : 1;  /* bit[6]    : clk_122m_wc_abb */
        unsigned int  bbp_clken_stat0_61m_wbbp_cs      : 1;  /* bit[7]    : clk_61m_wbbp_cs */
        unsigned int  bbp_clken_stat0_122m_wbbp_cs     : 1;  /* bit[8]    : clk_122m_wbbp_cs */
        unsigned int  bbp_clken_stat0_122m_tw          : 1;  /* bit[9]    : clk_122m_tw */
        unsigned int  bbp_clken_stat0_104m_gbbp1       : 1;  /* bit[10]   : clk_104m_gbbp1 */
        unsigned int  bbp_clken_stat0_axis_cs          : 1;  /* bit[11]   : clk_axis_cs */
        unsigned int  bbp_clken_stat0_122m_cbbp        : 1;  /* bit[12]   : clk_122m_cbbp */
        unsigned int  reserved_2                       : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_clken_stat0_axim_bbc         : 1;  /* bit[14]   : clk_axim_bbc */
        unsigned int  bbp_clken_stat0_122m_lte_pdf_bbc : 1;  /* bit[15]   : clk_122m_lte_pdf_bbc */
        unsigned int  bbp_clken_stat0_122m_lte_pdt_bbc : 1;  /* bit[16]   : clk_122m_lte_pdt_bbc */
        unsigned int  bbp_clken_stat0_245m_lte_bbc     : 1;  /* bit[17]   : clk_245m_lte_bbc */
        unsigned int  bbp_clken_stat0_245m_wbbp_cs     : 1;  /* bit[18]   : clk_245m_wbbp_cs */
        unsigned int  bbp_clken_stat0_104m_gbbp_sdr    : 1;  /* bit[19]   : clk_104m_gbbp_sdr */
        unsigned int  bbp_clken_stat0_245m_wbbp_sdr    : 1;  /* bit[20]   : clk_245m_wbbp_sdr */
        unsigned int  bbp_clken_stat0_104m_gbbp2       : 1;  /* bit[21]   : clk_104m_gbbp2 */
        unsigned int  bbp_clken_stat0_150m_noc_cs      : 1;  /* bit[22]   : clk_150m_noc_cs */
        unsigned int  bbp_clken_stat0_axim_bbpmst      : 1;  /* bit[23]   : clk_axim_bbpmst */
        unsigned int  bbp_clken_stat0_19m_ch0_bbc      : 1;  /* bit[24]   : clk_19m_ch0_bbc */
        unsigned int  bbp_clken_stat0_19m_ch1_bbc      : 1;  /* bit[25]   : clk_19m_ch1_bbc */
        unsigned int  reserved_3                       : 6;  /* bit[26-31]: 时钟状态定义如下（高电平表示时钟打开）：BBP CS分区相关时钟控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT0_bbp_clken_stat0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_UNION
 结构说明  : MDMSC_BBP_CLKEN1 寄存器结构定义。地址偏移量:0x012C，初值:0x00000000，宽度:32
 寄存器说明: BBP时钟使能寄存器1。用于使能外设时钟。对比特写1，使能对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clken1_axim_wbbp     : 1;  /* bit[0]    : clk_axim_wbbp */
        unsigned int  bbp_clken1_61m_wbbp_ps   : 1;  /* bit[1]    : clk_61m_wbbp_ps */
        unsigned int  bbp_clken1_122m_wbbp_ps  : 1;  /* bit[2]    : clk_122m_wbbp_ps */
        unsigned int  bbp_clken1_245m_wbbp_ps  : 1;  /* bit[3]    : clk_245m_wbbp_ps */
        unsigned int  bbp_clken1_245m_irm      : 1;  /* bit[4]    : clk_245m_irm */
        unsigned int  reserved_0               : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clken1_122m_cbbp_irm : 1;  /* bit[6]    : clk_122m_cbbp_irm */
        unsigned int  bbp_clken1_axis_irm      : 1;  /* bit[7]    : clk_axis_irm */
        unsigned int  bbp_clken1_122m_wc_irm   : 1;  /* bit[8]    : clk_122m_wc_irm */
        unsigned int  reserved_1               : 1;  /* bit[9]    : reserved */
        unsigned int  reserved_2               : 6;  /* bit[10-15]: reserved */
        unsigned int  bbp_clken1_axi_lte       : 1;  /* bit[16]   : clk_axi_lte */
        unsigned int  bbp_clken1_122m_lte_pdf  : 1;  /* bit[17]   : clk_122m_lte_pdf */
        unsigned int  bbp_clken1_122m_lte_pdt  : 1;  /* bit[18]   : clk_122m_lte_pdt */
        unsigned int  bbp_clken1_122m_tds_pdt  : 1;  /* bit[19]   : clk_122m_tds_pdt */
        unsigned int  bbp_clken1_245m_lte      : 1;  /* bit[20]   : clk_245m_lte */
        unsigned int  bbp_clken1_19m_lte       : 1;  /* bit[21]   : clk_19m_lte */
        unsigned int  reserved_3               : 10; /* bit[22-31]: 时钟使能定义如下（写1时钟打开）：BBP PS分区和LTE分区相关时钟控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_wc_irm_END      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axi_lte_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_axi_lte_END          (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_lte_pdf_START   (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_lte_pdf_END     (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_lte_pdt_START   (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_lte_pdt_END     (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_tds_pdt_START   (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_122m_tds_pdt_END     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_lte_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_245m_lte_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_19m_lte_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN1_bbp_clken1_19m_lte_END          (21)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_UNION
 结构说明  : MDMSC_BBP_CLKDIS1 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器1。用于禁止外设时钟。对比特写1，禁止对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clkdis1_axim_wbbp     : 1;  /* bit[0]    : clk_axim_wbbp */
        unsigned int  bbp_clkdis1_61m_wbbp_ps   : 1;  /* bit[1]    : clk_61m_wbbp_ps */
        unsigned int  bbp_clkdis1_122m_wbbp_ps  : 1;  /* bit[2]    : clk_122m_wbbp_ps */
        unsigned int  bbp_clkdis1_245m_wbbp_ps  : 1;  /* bit[3]    : clk_245m_wbbp_ps */
        unsigned int  bbp_clkdis1_245m_irm      : 1;  /* bit[4]    : clk_245m_irm */
        unsigned int  reserved_0                : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clkdis1_122m_cbbp_irm : 1;  /* bit[6]    : clk_122m_cbbp_irm */
        unsigned int  bbp_clkdis1_axis_irm      : 1;  /* bit[7]    : clk_axis_irm */
        unsigned int  bbp_clkdis1_122m_wc_irm   : 1;  /* bit[8]    : clk_122m_wc_irm */
        unsigned int  reserved_1                : 1;  /* bit[9]    : reserved */
        unsigned int  reserved_2                : 6;  /* bit[10-15]: reserved */
        unsigned int  bbp_clkdis1_axi_lte       : 1;  /* bit[16]   : clk_axi_lte */
        unsigned int  bbp_clkdis1_122m_lte_pdf  : 1;  /* bit[17]   : clk_122m_lte_pdf */
        unsigned int  bbp_clkdis1_122m_lte_pdt  : 1;  /* bit[18]   : clk_122m_lte_pdt */
        unsigned int  bbp_clkdis1_122m_tds_pdt  : 1;  /* bit[19]   : clk_122m_tds_pdt */
        unsigned int  bbp_clkdis1_245m_lte      : 1;  /* bit[20]   : clk_245m_lte */
        unsigned int  bbp_clkdis1_19m_lte       : 1;  /* bit[21]   : clk_19m_lte */
        unsigned int  reserved_3                : 10; /* bit[22-31]: 时钟禁止定义如下（写1时钟关闭）：BBP PS分区和LTE分区相关时钟控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_wc_irm_END      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axi_lte_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_axi_lte_END          (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_lte_pdf_START   (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_lte_pdf_END     (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_lte_pdt_START   (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_lte_pdt_END     (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_tds_pdt_START   (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_122m_tds_pdt_END     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_lte_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_245m_lte_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_19m_lte_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKDIS1_bbp_clkdis1_19m_lte_END          (21)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_UNION
 结构说明  : MDMSC_BBP_CLKEN_STAT1 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟状态寄存器1。用于回读各外设时钟的状态。外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clken_stat1_axim_wbbp     : 1;  /* bit[0]    : clk_axim_wbbp */
        unsigned int  bbp_clken_stat1_61m_wbbp_ps   : 1;  /* bit[1]    : clk_61m_wbbp_ps */
        unsigned int  bbp_clken_stat1_122m_wbbp_ps  : 1;  /* bit[2]    : clk_122m_wbbp_ps */
        unsigned int  bbp_clken_stat1_245m_wbbp_ps  : 1;  /* bit[3]    : clk_245m_wbbp_ps */
        unsigned int  bbp_clken_stat1_245m_irm      : 1;  /* bit[4]    : clk_245m_irm */
        unsigned int  reserved_0                    : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_clken_stat1_122m_cbbp_irm : 1;  /* bit[6]    : clk_122m_cbbp_irm */
        unsigned int  bbp_clken_stat1_axis_irm      : 1;  /* bit[7]    : clk_axis_irm */
        unsigned int  bbp_clken_stat1_122m_wc_irm   : 1;  /* bit[8]    : clk_122m_wc_irm */
        unsigned int  reserved_1                    : 1;  /* bit[9]    : reserved */
        unsigned int  reserved_2                    : 6;  /* bit[10-15]: reserved */
        unsigned int  bbp_clken_stat1_axi_lte       : 1;  /* bit[16]   : clk_axi_lte */
        unsigned int  bbp_clken_stat1_122m_lte_pdf  : 1;  /* bit[17]   : clk_122m_lte_pdf */
        unsigned int  bbp_clken_stat1_122m_lte_pdt  : 1;  /* bit[18]   : clk_122m_lte_pdt */
        unsigned int  bbp_clken_stat1_122m_tds_pdt  : 1;  /* bit[19]   : clk_122m_tds_pdt */
        unsigned int  bbp_clken_stat1_245m_lte      : 1;  /* bit[20]   : clk_245m_lte */
        unsigned int  bbp_clken_stat1_19m_lte       : 1;  /* bit[21]   : clk_19m_lte */
        unsigned int  reserved_3                    : 10; /* bit[22-31]: 时钟状态定义如下（高电平表示时钟打开）：BBP PS分区和LTE分区相关时钟控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_wc_irm_END      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axi_lte_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_axi_lte_END          (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_lte_pdf_START   (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_lte_pdf_END     (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_lte_pdt_START   (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_lte_pdt_END     (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_tds_pdt_START   (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_122m_tds_pdt_END     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_lte_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_245m_lte_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_19m_lte_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_CLKEN_STAT1_bbp_clken_stat1_19m_lte_END          (21)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_UNION
 结构说明  : MDMSC_PERIPH_RSTEN 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 外设复位使能寄存器。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                : 1;  /* bit[3]    : reserved */
        unsigned int  periph_rsten_bbe16_kernel : 1;  /* bit[4]    : BBE16内核时钟域软复位 */
        unsigned int  periph_rsten_bbe16_lbus   : 1;  /* bit[5]    : BBE16 局部AXI总线软复位 */
        unsigned int  reserved_4                : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                : 1;  /* bit[7]    : reserved */
        unsigned int  periph_rsten_mdmac        : 1;  /* bit[8]    : mdmac工作时钟域软复位 */
        unsigned int  periph_rsten_upacc        : 1;  /* bit[9]    : upacc工作时钟域软复位 */
        unsigned int  reserved_6                : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                : 1;  /* bit[11]   : reserved */
        unsigned int  periph_rsten_lcipher      : 1;  /* bit[12]   : lcipher工作时钟域软复位 */
        unsigned int  periph_rsten_gucipher0    : 1;  /* bit[13]   : gucipher0工作时钟域软复位 */
        unsigned int  reserved_8                : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                : 1;  /* bit[15]   : reserved */
        unsigned int  periph_rsten_muart0       : 1;  /* bit[16]   : Modem侧UART0工作时钟域软复位 */
        unsigned int  reserved_10               : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11               : 14; /* bit[18-31]: 复位使能定义如下（写1复位使能）。Modem子系统外设IP软复位控制
                                                                     [31:18] 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_bbe16_kernel_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_bbe16_kernel_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_bbe16_lbus_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_bbe16_lbus_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_mdmac_START         (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_mdmac_END           (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_upacc_START         (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_upacc_END           (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_lcipher_START       (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_lcipher_END         (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_gucipher0_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_gucipher0_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_muart0_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_periph_rsten_muart0_END          (16)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_UNION
 结构说明  : MDMSC_PERIPH_RSTDIS 寄存器结构定义。地址偏移量:0x0154，初值:0x00000000，宽度:32
 寄存器说明: 外设复位禁止寄存器。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                 : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                 : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                 : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                 : 1;  /* bit[3]    : reserved */
        unsigned int  periph_rstdis_bbe16_kernel : 1;  /* bit[4]    : BBE16内核时钟域软复位 */
        unsigned int  periph_rstdis_bbe16_lbus   : 1;  /* bit[5]    : BBE16 局部AXI总线软复位 */
        unsigned int  reserved_4                 : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                 : 1;  /* bit[7]    : reserved */
        unsigned int  periph_rstdis_mdmac        : 1;  /* bit[8]    : mdmac工作时钟域软复位 */
        unsigned int  periph_rstdis_upacc        : 1;  /* bit[9]    : upacc工作时钟域软复位 */
        unsigned int  reserved_6                 : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                 : 1;  /* bit[11]   : reserved */
        unsigned int  periph_rstdis_lcipher      : 1;  /* bit[12]   : lcipher工作时钟域软复位 */
        unsigned int  periph_rstdis_gucipher0    : 1;  /* bit[13]   : gucipher0工作时钟域软复位 */
        unsigned int  reserved_8                 : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                 : 1;  /* bit[15]   : reserved */
        unsigned int  periph_rstdis_muart0       : 1;  /* bit[16]   : Modem侧UART0工作时钟域软复位 */
        unsigned int  reserved_10                : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                : 14; /* bit[18-31]: 复位禁止定义如下（写1复位解除）。Modem子系统外设IP软复位控制
                                                                      [31:18] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_bbe16_kernel_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_bbe16_kernel_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_bbe16_lbus_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_bbe16_lbus_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_mdmac_START         (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_mdmac_END           (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_upacc_START         (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_upacc_END           (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_lcipher_START       (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_lcipher_END         (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_gucipher0_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_gucipher0_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_muart0_START        (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTDIS_periph_rstdis_muart0_END          (16)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_UNION
 结构说明  : MDMSC_PERIPH_RSTEN_STAT 寄存器结构定义。地址偏移量:0x0158，初值:0xFFFFFFFE，宽度:32
 寄存器说明: 外设复位状态寄存器6。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                     : 1;  /* bit[0]    : reserved */
        unsigned int  reserved_1                     : 1;  /* bit[1]    : reserved */
        unsigned int  reserved_2                     : 1;  /* bit[2]    : reserved */
        unsigned int  reserved_3                     : 1;  /* bit[3]    : reserved */
        unsigned int  periph_rsten_stat_bbe16_kernel : 1;  /* bit[4]    : BBE16内核时钟域软复位 */
        unsigned int  periph_rsten_stat_bbe16_lbus   : 1;  /* bit[5]    : BBE16 局部AXI总线软复位 */
        unsigned int  reserved_4                     : 1;  /* bit[6]    : reserved */
        unsigned int  reserved_5                     : 1;  /* bit[7]    : reserved */
        unsigned int  periph_rsten_stat_mdmac        : 1;  /* bit[8]    : mdmac工作时钟域软复位 */
        unsigned int  periph_rsten_stat_upacc        : 1;  /* bit[9]    : upacc工作时钟域软复位 */
        unsigned int  reserved_6                     : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_7                     : 1;  /* bit[11]   : reserved */
        unsigned int  periph_rsten_stat_lcipher      : 1;  /* bit[12]   : lcipher工作时钟域软复位 */
        unsigned int  periph_rsten_stat_gucipher0    : 1;  /* bit[13]   : gucipher0工作时钟域软复位 */
        unsigned int  reserved_8                     : 1;  /* bit[14]   : reserved */
        unsigned int  reserved_9                     : 1;  /* bit[15]   : reserved */
        unsigned int  periph_rsten_stat_stat_muart0  : 1;  /* bit[16]   : Modem侧UART0工作时钟域软复位 */
        unsigned int  reserved_10                    : 1;  /* bit[17]   : reserved */
        unsigned int  reserved_11                    : 14; /* bit[18-31]: 复位状态定义如下（高电平表示处于复位）Modem子系统外设IP软复位控制
                                                                          [31:18] : Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_bbe16_kernel_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_bbe16_kernel_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_bbe16_lbus_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_bbe16_lbus_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_mdmac_START         (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_mdmac_END           (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_upacc_START         (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_upacc_END           (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_lcipher_START       (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_lcipher_END         (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_gucipher0_START     (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_gucipher0_END       (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_stat_muart0_START   (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_RSTEN_STAT_periph_rsten_stat_stat_muart0_END     (16)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_UNION
 结构说明  : MDMSC_BBP_RSTEN0 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: BBP复位使能寄存器。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rsten0_122m_tds         : 1;  /* bit[0]    : rst_122m_tds_n */
        unsigned int  bbp_rsten0_245m_tds         : 1;  /* bit[1]    : rst_245m_tds_n */
        unsigned int  bbp_rsten0_19m_cs           : 1;  /* bit[2]    : rst_19m_cs_n */
        unsigned int  bbp_rsten0_32k_cs           : 1;  /* bit[3]    : rst_32k_cs_n */
        unsigned int  bbp_rsten0_122m_twc         : 1;  /* bit[4]    : rst_122m_twc_n */
        unsigned int  reserved_0                  : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_rsten0_122m_wc_abb      : 1;  /* bit[6]    : rst_122m_wc_abb_n */
        unsigned int  bbp_rsten0_61m_wbbp_cs      : 1;  /* bit[7]    : rst_61m_wbbp_cs_n */
        unsigned int  bbp_rsten0_122m_wbbp_cs     : 1;  /* bit[8]    : rst_122m_wbbp_cs_n */
        unsigned int  bbp_rsten0_122m_tw          : 1;  /* bit[9]    : rst_122m_tw_n */
        unsigned int  bbp_rsten0_104m_gbbp1       : 1;  /* bit[10]   : rst_104m_gbbp1_n */
        unsigned int  bbp_rsten0_axis_cs          : 1;  /* bit[11]   : rst_axis_cs_n */
        unsigned int  bbp_rsten0_122m_cbbp        : 1;  /* bit[12]   : rst_122m_cbbp_n */
        unsigned int  reserved_1                  : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_rsten0_axim_bbc         : 1;  /* bit[14]   : rst_axim_bbc_n */
        unsigned int  bbp_rsten0_122m_lte_pdf_bbc : 1;  /* bit[15]   : rst_122m_lte_pdf_bbc_n */
        unsigned int  bbp_rsten0_122m_lte_pdt_bbc : 1;  /* bit[16]   : rst_122m_lte_pdt_bbc_n */
        unsigned int  bbp_rsten0_245m_lte_bbc     : 1;  /* bit[17]   : rst_245m_lte_bbc_n */
        unsigned int  bbp_rsten0_245m_wbbp_cs     : 1;  /* bit[18]   : rst_245m_wbbp_cs_n */
        unsigned int  bbp_rsten0_104m_gbbp_sdr    : 1;  /* bit[19]   : rst_104m_gbbp_sdr_n */
        unsigned int  bbp_rsten0_245m_wbbp_sdr    : 1;  /* bit[20]   : rst_245m_wbbp_sdr_n */
        unsigned int  bbp_rsten0_104m_gbbp2       : 1;  /* bit[21]   : rst_104m_gbbp2_n */
        unsigned int  bbp_rsten0_150m_noc_cs      : 1;  /* bit[22]   : rst_150m_noc_cs_n */
        unsigned int  bbp_rsten0_axim_bbpmst      : 1;  /* bit[23]   : rst_axim_bbpmst_n */
        unsigned int  bbp_rsten0_19m_ch0_bbc      : 1;  /* bit[24]   : rst_19m_ch0_bbc_n */
        unsigned int  bbp_rsten0_19m_ch1_bbc      : 1;  /* bit[25]   : rst_19m_ch1_bbc_n */
        unsigned int  reserved_2                  : 6;  /* bit[26-31]: 复位使能定义如下（写1复位使能）。BBP CS分区复位控制
                                                                       保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_32k_cs_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_32k_cs_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN0_bbp_rsten0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_UNION
 结构说明  : MDMSC_BBP_RSTDIS0 寄存器结构定义。地址偏移量:0x0174，初值:0x00000000，宽度:32
 寄存器说明: BBP复位禁止寄存器。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rstdis0_122m_tds         : 1;  /* bit[0]    : rst_122m_tds_n */
        unsigned int  bbp_rstdis0_245m_tds         : 1;  /* bit[1]    : rst_245m_tds_n */
        unsigned int  bbp_rstdis0_19m_cs           : 1;  /* bit[2]    : rst_19m_cs_n */
        unsigned int  bbp_rstdis0_32k_cs           : 1;  /* bit[3]    : rst_32k_cs_n */
        unsigned int  bbp_rstdis0_122m_twc         : 1;  /* bit[4]    : rst_122m_twc_n */
        unsigned int  reserved_0                   : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_rstdis0_122m_wc_abb      : 1;  /* bit[6]    : rst_122m_wc_abb_n */
        unsigned int  bbp_rstdis0_61m_wbbp_cs      : 1;  /* bit[7]    : rst_61m_wbbp_cs_n */
        unsigned int  bbp_rstdis0_122m_wbbp_cs     : 1;  /* bit[8]    : rst_122m_wbbp_cs_n */
        unsigned int  bbp_rstdis0_122m_tw          : 1;  /* bit[9]    : rst_122m_tw_n */
        unsigned int  bbp_rstdis0_104m_gbbp1       : 1;  /* bit[10]   : rst_104m_gbbp1_n */
        unsigned int  bbp_rstdis0_axis_cs          : 1;  /* bit[11]   : rst_axis_cs_n */
        unsigned int  bbp_rstdis0_122m_cbbp        : 1;  /* bit[12]   : rst_122m_cbbp_n */
        unsigned int  reserved_1                   : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_rstdis0_axim_bbc         : 1;  /* bit[14]   : rst_axim_bbc_n */
        unsigned int  bbp_rstdis0_122m_lte_pdf_bbc : 1;  /* bit[15]   : rst_122m_lte_pdf_bbc_n */
        unsigned int  bbp_rstdis0_122m_lte_pdt_bbc : 1;  /* bit[16]   : rst_122m_lte_pdt_bbc_n */
        unsigned int  bbp_rstdis0_245m_lte_bbc     : 1;  /* bit[17]   : rst_245m_lte_bbc_n */
        unsigned int  bbp_rstdis0_245m_wbbp_cs     : 1;  /* bit[18]   : rst_245m_wbbp_cs_n */
        unsigned int  bbp_rstdis0_104m_gbbp_sdr    : 1;  /* bit[19]   : rst_104m_gbbp_sdr_n */
        unsigned int  bbp_rstdis0_245m_wbbp_sdr    : 1;  /* bit[20]   : rst_245m_wbbp_sdr_n */
        unsigned int  bbp_rstdis0_104m_gbbp2       : 1;  /* bit[21]   : rst_104m_gbbp2_n */
        unsigned int  bbp_rstdis0_150m_noc_cs      : 1;  /* bit[22]   : rst_150m_noc_cs_n */
        unsigned int  bbp_rstdis0_axim_bbpmst      : 1;  /* bit[23]   : rst_axim_bbpmst_n */
        unsigned int  bbp_rstdis0_19m_ch0_bbc      : 1;  /* bit[24]   : rst_19m_ch0_bbc_n */
        unsigned int  bbp_rstdis0_19m_ch1_bbc      : 1;  /* bit[25]   : rst_19m_ch1_bbc_n */
        unsigned int  reserved_2                   : 6;  /* bit[26-31]: 复位禁止定义如下（写1复位解除）。BBP CS分区复位控制
                                                                        保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_32k_cs_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_32k_cs_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS0_bbp_rstdis0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_UNION
 结构说明  : MDMSC_BBP_RSTEN_STAT0 寄存器结构定义。地址偏移量:0x0178，初值:0xFFFFFFFF，宽度:32
 寄存器说明: BBP复位状态寄存器。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rsten_stat0_122m_tds         : 1;  /* bit[0]    : rst_122m_tds_n */
        unsigned int  bbp_rsten_stat0_245m_tds         : 1;  /* bit[1]    : rst_245m_tds_n */
        unsigned int  bbp_rsten_stat0_19m_cs           : 1;  /* bit[2]    : rst_19m_cs_n */
        unsigned int  bbp_rsten_stat0_32k_cs           : 1;  /* bit[3]    : rst_32k_cs_n */
        unsigned int  bbp_rsten_stat0_122m_twc         : 1;  /* bit[4]    : rst_122m_twc_n */
        unsigned int  reserved_0                       : 1;  /* bit[5]    : reserved */
        unsigned int  bbp_rsten_stat0_122m_wc_abb      : 1;  /* bit[6]    : rst_122m_wc_abb_n */
        unsigned int  bbp_rsten_stat0_61m_wbbp_cs      : 1;  /* bit[7]    : rst_61m_wbbp_cs_n */
        unsigned int  bbp_rsten_stat0_122m_wbbp_cs     : 1;  /* bit[8]    : rst_122m_wbbp_cs_n */
        unsigned int  bbp_rsten_stat0_122m_tw          : 1;  /* bit[9]    : rst_122m_tw_n */
        unsigned int  bbp_rsten_stat0_104m_gbbp1       : 1;  /* bit[10]   : rst_104m_gbbp1_n */
        unsigned int  bbp_rsten_stat0_axis_cs          : 1;  /* bit[11]   : rst_axis_cs_n */
        unsigned int  bbp_rsten_stat0_122m_cbbp        : 1;  /* bit[12]   : rst_122m_cbbp_n */
        unsigned int  reserved_1                       : 1;  /* bit[13]   : reserved */
        unsigned int  bbp_rsten_stat0_axim_bbc         : 1;  /* bit[14]   : rst_axim_bbc_n */
        unsigned int  bbp_rsten_stat0_122m_lte_pdf_bbc : 1;  /* bit[15]   : rst_122m_lte_pdf_bbc_n */
        unsigned int  bbp_rsten_stat0_122m_lte_pdt_bbc : 1;  /* bit[16]   : rst_122m_lte_pdt_bbc_n */
        unsigned int  bbp_rsten_stat0_245m_lte_bbc     : 1;  /* bit[17]   : rst_245m_lte_bbc_n */
        unsigned int  bbp_rsten_stat0_245m_wbbp_cs     : 1;  /* bit[18]   : rst_245m_wbbp_cs_n */
        unsigned int  bbp_rsten_stat0_104m_gbbp_sdr    : 1;  /* bit[19]   : rst_104m_gbbp_sdr_n */
        unsigned int  bbp_rsten_stat0_245m_wbbp_sdr    : 1;  /* bit[20]   : rst_245m_wbbp_sdr_n */
        unsigned int  bbp_rsten_stat0_104m_gbbp2       : 1;  /* bit[21]   : rst_104m_gbbp2_n */
        unsigned int  bbp_rsten_stat0_150m_noc_cs      : 1;  /* bit[22]   : rst_150m_noc_cs_n */
        unsigned int  bbp_rsten_stat0_axim_bbpmst      : 1;  /* bit[23]   : rst_axim_bbpmst_n */
        unsigned int  bbp_rsten_stat0_19m_ch0_bbc      : 1;  /* bit[24]   : rst_19m_ch0_bbc_n */
        unsigned int  bbp_rsten_stat0_19m_ch1_bbc      : 1;  /* bit[25]   : rst_19m_ch1_bbc_n */
        unsigned int  reserved_2                       : 6;  /* bit[26-31]: 复位状态定义如下（高电平表示处于复位）BBP CS分区复位控制。
                                                                            保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_tds_START          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_tds_END            (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_tds_START          (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_tds_END            (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_cs_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_cs_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_32k_cs_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_32k_cs_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_twc_START          (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_twc_END            (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_wc_abb_START       (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_wc_abb_END         (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_61m_wbbp_cs_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_61m_wbbp_cs_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_wbbp_cs_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_wbbp_cs_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_tw_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_tw_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp1_START        (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp1_END          (10)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axis_cs_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axis_cs_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_cbbp_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_cbbp_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axim_bbc_START          (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axim_bbc_END            (14)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_lte_pdf_bbc_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_lte_pdf_bbc_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_lte_pdt_bbc_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_122m_lte_pdt_bbc_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_lte_bbc_START      (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_lte_bbc_END        (17)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_wbbp_cs_START      (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_wbbp_cs_END        (18)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp_sdr_START     (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp_sdr_END       (19)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_wbbp_sdr_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_245m_wbbp_sdr_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp2_START        (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_104m_gbbp2_END          (21)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_150m_noc_cs_START       (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_150m_noc_cs_END         (22)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axim_bbpmst_START       (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_axim_bbpmst_END         (23)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_ch0_bbc_START       (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_ch0_bbc_END         (24)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_ch1_bbc_START       (25)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT0_bbp_rsten_stat0_19m_ch1_bbc_END         (25)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_UNION
 结构说明  : MDMSC_BBP_RSTEN1 寄存器结构定义。地址偏移量:0x017C，初值:0x00000000，宽度:32
 寄存器说明: BBP复位使能寄存器1。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rsten1_axim_wbbp     : 1;  /* bit[0]   : rst_axim_wbbp_n */
        unsigned int  bbp_rsten1_61m_wbbp_ps   : 1;  /* bit[1]   : rst_61m_wbbp_ps_n */
        unsigned int  bbp_rsten1_122m_wbbp_ps  : 1;  /* bit[2]   : rst_122m_wbbp_ps_n */
        unsigned int  bbp_rsten1_245m_wbbp_ps  : 1;  /* bit[3]   : rst_245m_wbbp_ps_n */
        unsigned int  bbp_rsten1_245m_irm      : 1;  /* bit[4]   : rst_245m_157m_irm_n */
        unsigned int  reserved_0               : 1;  /* bit[5]   : reserved */
        unsigned int  bbp_rsten1_122m_cbbp_irm : 1;  /* bit[6]   : rst_122m_cbbp_irm_n */
        unsigned int  bbp_rsten1_axis_irm      : 1;  /* bit[7]   : rst_axis_irm_n */
        unsigned int  bbp_rsten1_122m_wc_irm   : 1;  /* bit[8]   : rst_122m_wc_irm_n */
        unsigned int  reserved_1               : 23; /* bit[9-31]: 复位使能定义如下（写1复位使能）。BBP PS分区和LTE分区复位控制
                                                                   Reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN1_bbp_rsten1_122m_wc_irm_END      (8)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_UNION
 结构说明  : MDMSC_BBP_RSTDIS1 寄存器结构定义。地址偏移量:0x0180，初值:0x00000000，宽度:32
 寄存器说明: BBP复位禁止寄存器1。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rstdis1_axim_wbbp     : 1;  /* bit[0]   : rst_axim_wbbp_n */
        unsigned int  bbp_rstdis1_61m_wbbp_ps   : 1;  /* bit[1]   : rst_61m_wbbp_ps_n */
        unsigned int  bbp_rstdis1_122m_wbbp_ps  : 1;  /* bit[2]   : rst_122m_wbbp_ps_n */
        unsigned int  bbp_rstdis1_245m_wbbp_ps  : 1;  /* bit[3]   : rst_245m_wbbp_ps_n */
        unsigned int  bbp_rstdis1_245m_irm      : 1;  /* bit[4]   : rst_245m_irm_n */
        unsigned int  reserved_0                : 1;  /* bit[5]   : reserved */
        unsigned int  bbp_rstdis1_122m_cbbp_irm : 1;  /* bit[6]   : rst_122m_cbbp_irm_n */
        unsigned int  bbp_rstdis1_axis_irm      : 1;  /* bit[7]   : rst_axis_irm_n */
        unsigned int  bbp_rstdis1_122m_wc_irm   : 1;  /* bit[8]   : rst_122m_wc_irm_n */
        unsigned int  reserved_1                : 23; /* bit[9-31]: 复位禁止定义如下（写1复位解除）。BBP PS分区和LTE分区复位控制
                                                                    Reseved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTDIS1_bbp_rstdis1_122m_wc_irm_END      (8)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_UNION
 结构说明  : MDMSC_BBP_RSTEN_STAT1 寄存器结构定义。地址偏移量:0x0184，初值:0xFFFFFFFF，宽度:32
 寄存器说明: BBP复位状态寄存器1。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_rsten_stat1_axim_wbbp     : 1;  /* bit[0]   : rst_axim_wbbp_n */
        unsigned int  bbp_rsten_stat1_61m_wbbp_ps   : 1;  /* bit[1]   : rst_61m_wbbp_ps_n */
        unsigned int  bbp_rsten_stat1_122m_wbbp_ps  : 1;  /* bit[2]   : rst_122m_wbbp_ps_n */
        unsigned int  bbp_rsten_stat1_245m_wbbp_ps  : 1;  /* bit[3]   : rst_245m_wbbp_ps_n */
        unsigned int  bbp_rsten_stat1_245m_irm      : 1;  /* bit[4]   : rst_245m_157m_irm_n */
        unsigned int  reserved_0                    : 1;  /* bit[5]   : reserved */
        unsigned int  bbp_rsten_stat1_122m_cbbp_irm : 1;  /* bit[6]   : rst_122m_cbbp_irm_n */
        unsigned int  bbp_rsten_stat1_axis_irm      : 1;  /* bit[7]   : rst_axis_irm_n */
        unsigned int  bbp_rsten_stat1_122m_wc_irm   : 1;  /* bit[8]   : rst_122m_wc_irm_n */
        unsigned int  reserved_1                    : 23; /* bit[9-31]: 复位状态定义如下（高电平表示处于复位）BBP PS分区和LTE分区复位控制
                                                                        Reseved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_axim_wbbp_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_axim_wbbp_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_61m_wbbp_ps_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_61m_wbbp_ps_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_wbbp_ps_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_wbbp_ps_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_245m_wbbp_ps_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_245m_wbbp_ps_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_245m_irm_START       (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_245m_irm_END         (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_cbbp_irm_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_cbbp_irm_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_axis_irm_START       (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_axis_irm_END         (7)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_wc_irm_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_BBP_RSTEN_STAT1_bbp_rsten_stat1_122m_wc_irm_END      (8)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_UNION
 结构说明  : MDMSC_SECONDARY_NEWINT0_EN 寄存器结构定义。地址偏移量:0x01E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_en_ipc_s_inner_core_intr4  : 1;  /* bit[0]    : 安全IPC输出给Tensilica BBE16的核间中断(ipc_s_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_en_ipc_ns_inner_core_intr4 : 1;  /* bit[1]    : 非安全IPC输出给Tensilica BBE16的核间中断(ipc_ns_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_en_ipc_s_lock_intr4        : 1;  /* bit[2]    : 安全IPC输出给Tensilica BBE16的资源锁中断(ipc_s_lock_intr[4]) */
        unsigned int  sc_secondary_int_en_ipc_ns_lock_intr4       : 1;  /* bit[3]    : 非安全IPC输出给Tensilica BBE16的资源锁中断(ipc_ns_lock_intr[4]) */
        unsigned int  reserved_0                                  : 12; /* bit[4-15] : 保留 */
        unsigned int  reserved_1                                  : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_s_inner_core_intr4_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_s_inner_core_intr4_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_ns_inner_core_intr4_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_ns_inner_core_intr4_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_s_lock_intr4_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_s_lock_intr4_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_ns_lock_intr4_START        (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_EN_sc_secondary_int_en_ipc_ns_lock_intr4_END          (3)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_UNION
 结构说明  : MDMSC_SECONDARY_NEWINT0_STATRAW 寄存器结构定义。地址偏移量:0x01E4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_raw_ipc_s_inner_core_intr4  : 1;  /* bit[0]    : 安全IPC输出给Tensilica BBE16的核间中断(ipc_s_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_raw_ipc_ns_inner_core_intr4 : 1;  /* bit[1]    : 非安全IPC输出给Tensilica BBE16的核间中断(ipc_ns_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_raw_ipc_s_lock_intr4        : 1;  /* bit[2]    : 安全IPC输出给Tensilica BBE16的资源锁中断(ipc_s_lock_intr[4]) */
        unsigned int  sc_secondary_int_raw_ipc_ns_lock_intr4       : 1;  /* bit[3]    : 非安全IPC输出给Tensilica BBE16的资源锁中断(ipc_ns_lock_intr[4]) */
        unsigned int  reserved_0                                   : 12; /* bit[4-15] : 保留 */
        unsigned int  reserved_1                                   : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_s_inner_core_intr4_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_s_inner_core_intr4_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_ns_inner_core_intr4_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_ns_inner_core_intr4_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_s_lock_intr4_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_s_lock_intr4_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_ns_lock_intr4_START        (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATRAW_sc_secondary_int_raw_ipc_ns_lock_intr4_END          (3)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_UNION
 结构说明  : MDMSC_SECONDARY_NEWINT0_STATMSK 寄存器结构定义。地址偏移量:0x01E8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_mask_ipc_s_inner_core_intr4  : 1;  /* bit[0]    : 安全IPC输出给Tensilica BBE16的核间中断(ipc_s_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_mask_ipc_ns_inner_core_intr4 : 1;  /* bit[1]    : 非安全IPC输出给Tensilica BBE16的核间中断(ipc_ns_inner_core_intr[4]) */
        unsigned int  sc_secondary_int_mask_ipc_s_lock_intr4        : 1;  /* bit[2]    : 安全IPC输出给Tensilica BBE16的资源锁中断(ipc_s_lock_intr[4]) */
        unsigned int  sc_secondary_int_mask_ipc_ns_lock_intr4       : 1;  /* bit[3]    : 非安全IPC输出给Tensilica BBE16的资源锁中断(ipc_ns_lock_intr[4]) */
        unsigned int  reserved_0                                    : 12; /* bit[4-15] : 保留 */
        unsigned int  reserved_1                                    : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_s_inner_core_intr4_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_s_inner_core_intr4_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_ns_inner_core_intr4_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_ns_inner_core_intr4_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_s_lock_intr4_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_s_lock_intr4_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_ns_lock_intr4_START        (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT0_STATMSK_sc_secondary_int_mask_ipc_ns_lock_intr4_END          (3)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_UNION
 结构说明  : MDMSC_SECONDARY_NEWINT1_EN 寄存器结构定义。地址偏移量:0x01F0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                              : 16; /* bit[0-15] : 保留 */
        unsigned int  sc_secondary_int_en_axierrirq_n         : 1;  /* bit[16]   : 局部总线写操作时B通道返回的error中断 */
        unsigned int  sc_secondary_int_en_mwdt_bbe_ot_intr    : 1;  /* bit[17]   : BBE16 watchdog的超时中断 */
        unsigned int  sc_secondary_int_en_mnoc_fault0         : 1;  /* bit[18]   : MODEMNOC Fault信号observer_Error_mainFault_0 */
        unsigned int  sc_secondary_int_en_mnoc_fault1         : 1;  /* bit[19]   : MODEMNOC Fault信号observer_Error_mainFault_1 */
        unsigned int  sc_secondary_int_en_comm_32k_int        : 1;  /* bit[20]   : comm_32k_int中断 */
        unsigned int  sc_secondary_int_en_ccpu_sftfiq_intr    : 1;  /* bit[21]   : ccpu_sftfiq_intr中断 */
        unsigned int  sc_secondary_newint_en_bbpmst_error_int : 1;  /* bit[22]   : bbpmst_error_int中断 */
        unsigned int  sc_secondary_int_en_arremap_error_flag  : 1;  /* bit[23]   : 读操作REMAP错误指示送给CCPU的二级中断 */
        unsigned int  sc_secondary_int_en_awremap_error_flag  : 1;  /* bit[24]   : 写操作REMAP错误指示送给CCPU的二级中断 */
        unsigned int  sc_secondary_int_en_usim0_detect_int    : 1;  /* bit[25]   : usim0热插拔检测中断送给CCPU的二级中断 */
        unsigned int  sc_secondary_int_en_usim1_detect_int    : 1;  /* bit[26]   : usim1热插拔检测中断送给CCPU的二级中断 */
        unsigned int  reserved_1                              : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_axierrirq_n_START          (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_axierrirq_n_END            (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mwdt_bbe_ot_intr_START     (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mwdt_bbe_ot_intr_END       (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mnoc_fault0_START          (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mnoc_fault0_END            (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mnoc_fault1_START          (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_mnoc_fault1_END            (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_comm_32k_int_START         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_comm_32k_int_END           (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_ccpu_sftfiq_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_ccpu_sftfiq_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_newint_en_bbpmst_error_int_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_newint_en_bbpmst_error_int_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_arremap_error_flag_START   (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_arremap_error_flag_END     (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_awremap_error_flag_START   (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_awremap_error_flag_END     (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_usim0_detect_int_START     (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_usim0_detect_int_END       (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_usim1_detect_int_START     (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_EN_sc_secondary_int_en_usim1_detect_int_END       (26)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_UNION
 结构说明  : MDMSC_SECONDARY_NEWINT1_STATRAW 寄存器结构定义。地址偏移量:0x01F4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                               : 16; /* bit[0-15] : 保留 */
        unsigned int  sc_secondary_int_raw_axierrirq_n         : 1;  /* bit[16]   : 局部总线写操作时B通道返回的error中断 */
        unsigned int  sc_secondary_int_raw_mwdt_bbe_ot_intr    : 1;  /* bit[17]   : BBE16 watchdog的超时中断 */
        unsigned int  sc_secondary_int_raw_mnoc_fault0         : 1;  /* bit[18]   : MODEMNOC Fault信号observer_Error_mainFault_0 */
        unsigned int  sc_secondary_int_raw_mnoc_fault1         : 1;  /* bit[19]   : MODEMNOC Fault信号observer_Error_mainFault_1 */
        unsigned int  sc_secondary_int_raw_comm_32k_int        : 1;  /* bit[20]   : comm_32k_int中断 */
        unsigned int  sc_secondary_int_raw_ccpu_sftfiq_intr    : 1;  /* bit[21]   : ccpu_sftfiq_intr中断 */
        unsigned int  sc_secondary_newint_raw_bbpmst_error_int : 1;  /* bit[22]   : bbpmst_error_int中断 */
        unsigned int  sc_secondary_int_raw_arremap_error_flag  : 1;  /* bit[23]   : 读操作REMAP错误指示送给CCPU的二级中断 */
        unsigned int  sc_secondary_int_raw_awremap_error_flag  : 1;  /* bit[24]   : 写操作REMAP错误指示送给CCPU的二级中断 */
        unsigned int  sc_secondary_int_raw_usim0_detect_int    : 1;  /* bit[25]   : usim0热插拔检测中断送给CCPU的二级中断 */
        unsigned int  sc_secondary_int_raw_usim1_detect_int    : 1;  /* bit[26]   : usim1热插拔检测中断送给CCPU的二级中断 */
        unsigned int  reserved_1                               : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_axierrirq_n_START          (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_axierrirq_n_END            (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mwdt_bbe_ot_intr_START     (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mwdt_bbe_ot_intr_END       (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mnoc_fault0_START          (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mnoc_fault0_END            (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mnoc_fault1_START          (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_mnoc_fault1_END            (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_comm_32k_int_START         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_comm_32k_int_END           (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_ccpu_sftfiq_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_ccpu_sftfiq_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_newint_raw_bbpmst_error_int_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_newint_raw_bbpmst_error_int_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_arremap_error_flag_START   (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_arremap_error_flag_END     (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_awremap_error_flag_START   (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_awremap_error_flag_END     (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_usim0_detect_int_START     (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_usim0_detect_int_END       (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_usim1_detect_int_START     (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATRAW_sc_secondary_int_raw_usim1_detect_int_END       (26)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_UNION
 结构说明  : MDMSC_SECONDARY_NEWINT1_STATMSK 寄存器结构定义。地址偏移量:0x01F8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                                : 16; /* bit[0-15] : 保留 */
        unsigned int  sc_secondary_int_mask_axierrirq_n         : 1;  /* bit[16]   : 局部总线写操作时B通道返回的error中断 */
        unsigned int  sc_secondary_int_mask_mwdt_bbe_ot_intr    : 1;  /* bit[17]   : BBE16 watchdog的超时中断 */
        unsigned int  sc_secondary_int_mask_mnoc_fault0         : 1;  /* bit[18]   : MODEMNOC Fault信号observer_Error_mainFault_0 */
        unsigned int  sc_secondary_int_mask_mnoc_fault1         : 1;  /* bit[19]   : MODEMNOC Fault信号observer_Error_mainFault_1 */
        unsigned int  sc_secondary_int_mask_comm_32k_int        : 1;  /* bit[20]   : comm_32k_int中断 */
        unsigned int  sc_secondary_int_mask_ccpu_sftfiq_intr    : 1;  /* bit[21]   : ccpu_sftfiq_intr中断 */
        unsigned int  sc_secondary_newint_mask_bbpmst_error_int : 1;  /* bit[22]   : bbpmst_error_int中断 */
        unsigned int  sc_secondary_int_mask_arremap_error_flag  : 1;  /* bit[23]   : 读操作REMAP错误指示送给CCPU的二级中断 */
        unsigned int  sc_secondary_int_mask_awremap_error_flag  : 1;  /* bit[24]   : 写操作REMAP错误指示送给CCPU的二级中断 */
        unsigned int  sc_secondary_int_mask_usim0_detect_int    : 1;  /* bit[25]   : usim0热插拔检测中断送给CCPU的二级中断 */
        unsigned int  sc_secondary_int_mask_usim1_detect_int    : 1;  /* bit[26]   : usim1热插拔检测中断送给CCPU的二级中断 */
        unsigned int  reserved_1                                : 5;  /* bit[27-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_axierrirq_n_START          (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_axierrirq_n_END            (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mwdt_bbe_ot_intr_START     (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mwdt_bbe_ot_intr_END       (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mnoc_fault0_START          (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mnoc_fault0_END            (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mnoc_fault1_START          (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_mnoc_fault1_END            (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_comm_32k_int_START         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_comm_32k_int_END           (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_ccpu_sftfiq_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_ccpu_sftfiq_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_newint_mask_bbpmst_error_int_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_newint_mask_bbpmst_error_int_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_arremap_error_flag_START   (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_arremap_error_flag_END     (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_awremap_error_flag_START   (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_awremap_error_flag_END     (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_usim0_detect_int_START     (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_usim0_detect_int_END       (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_usim1_detect_int_START     (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_NEWINT1_STATMSK_sc_secondary_int_mask_usim1_detect_int_END       (26)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_UNION
 结构说明  : MDMSC_SECONDARY_INT_EN 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: 系统二级中断使能寄存器。用于对系统二级中断进行屏蔽设置。对应bit为1表示使能相应中断，为0表示屏蔽中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_en_wbbp_otdoa_int2bbe        : 1;  /* bit[0] : wbbp_otdoa_int2bbe送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_bbpslot_bbe16_in14        : 1;  /* bit[1] : bbpslot_bbe16_in14送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_bbpslot_bbe16_in13        : 1;  /* bit[2] : bbpslot_bbe16_in13送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_upacc_dsp_int             : 1;  /* bit[3] : UPACC中断（upacc_dsp_int） */
        unsigned int  sc_secondary_int_en_upacc_arm_int             : 1;  /* bit[4] : UPACC中断（upacc_arm_int） */
        unsigned int  sc_secondary_int_en_g1_int_bbp_to_dsp_32k     : 1;  /* bit[5] : g1_int_bbp_to_dsp_32k送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_g1_int_bbp_to_dsp         : 1;  /* bit[6] : g1_int_bbp_to_dsp送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_g2_int_bbp_to_dsp_32k     : 1;  /* bit[7] : g2_int_bbp_to_dsp_32k送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_g2_int_bbp_to_dsp         : 1;  /* bit[8] : g2_int_bbp_to_dsp送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_bbpcom_ctu_g1_arm_intr    : 1;  /* bit[9] : bbpcom_ctu_g1_arm_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_bbpcom_ctu_g2_arm_intr    : 1;  /* bit[10]: bbpcom_ctu_g2_arm_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_bbpcom_ctu_w_arm_intr     : 1;  /* bit[11]: bbpcom_ctu_w_arm_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_card1_0ms_intr       : 1;  /* bit[12]: wbbp_card1_0ms_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_wdrx_slp_awk_sw_intr : 1;  /* bit[13]: wbbp_wdrx_slp_awk_sw_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_clk_sw_intr          : 1;  /* bit[14]: wbbp_clk_sw_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_card2_0ms_intr       : 1;  /* bit[15]: wbbp_card2_0ms_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_search_intr          : 1;  /* bit[16]: wbbp_search_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_rake_intr            : 1;  /* bit[17]: wbbp_rake_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_decode_intr          : 1;  /* bit[18]: wbbp_decode_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_card1_time_intr      : 1;  /* bit[19]: wbbp_card1_time_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_card2_time_intr      : 1;  /* bit[20]: wbbp_card2_time_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_multi_search_intr    : 1;  /* bit[21]: wbbp_multi_search_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_wbbp_bbpmst_intr          : 1;  /* bit[22]: wbbp_bbpmst_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_lte_dsp_warn_intr         : 1;  /* bit[23]: lte_dsp_warn_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_mwdt_bbe_intr             : 1;  /* bit[24]: mwdt_bbe_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_bbpmst_error_int          : 1;  /* bit[25]: bbpmst_error_int送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_mtimer8_intc              : 1;  /* bit[26]: mtimer8_intc送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_mtimer9_intc              : 1;  /* bit[27]: mtimer9_intc送给BBE16的中断 */
        unsigned int  sc_secondary_int_en_muart0_intr               : 1;  /* bit[28]: Modem侧uart0(CCPU/BBE16复用)中断 */
        unsigned int  sc_secondary_int_en_uart3_intr                : 1;  /* bit[29]: AP侧uart3（LTE/Connectivity共存复用）中断 */
        unsigned int  sc_secondary_int_en_uart0_intr                : 1;  /* bit[30]: AP侧uart0(用于产线校准、软件调测) 中断 */
        unsigned int  reserved                                      : 1;  /* bit[31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_otdoa_int2bbe_START         (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_otdoa_int2bbe_END           (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpslot_bbe16_in14_START         (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpslot_bbe16_in14_END           (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpslot_bbe16_in13_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpslot_bbe16_in13_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_upacc_dsp_int_START              (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_upacc_dsp_int_END                (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_upacc_arm_int_START              (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_upacc_arm_int_END                (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g1_int_bbp_to_dsp_32k_START      (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g1_int_bbp_to_dsp_32k_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g1_int_bbp_to_dsp_START          (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g1_int_bbp_to_dsp_END            (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g2_int_bbp_to_dsp_32k_START      (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g2_int_bbp_to_dsp_32k_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g2_int_bbp_to_dsp_START          (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_g2_int_bbp_to_dsp_END            (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_g1_arm_intr_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_g1_arm_intr_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_g2_arm_intr_START     (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_g2_arm_intr_END       (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_w_arm_intr_START      (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpcom_ctu_w_arm_intr_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card1_0ms_intr_START        (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card1_0ms_intr_END          (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_wdrx_slp_awk_sw_intr_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_wdrx_slp_awk_sw_intr_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_clk_sw_intr_START           (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_clk_sw_intr_END             (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card2_0ms_intr_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card2_0ms_intr_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_search_intr_START           (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_search_intr_END             (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_rake_intr_START             (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_rake_intr_END               (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_decode_intr_START           (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_decode_intr_END             (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card1_time_intr_START       (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card1_time_intr_END         (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card2_time_intr_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_card2_time_intr_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_multi_search_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_multi_search_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_bbpmst_intr_START           (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_wbbp_bbpmst_intr_END             (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_lte_dsp_warn_intr_START          (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_lte_dsp_warn_intr_END            (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mwdt_bbe_intr_START              (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mwdt_bbe_intr_END                (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpmst_error_int_START           (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_bbpmst_error_int_END             (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mtimer8_intc_START               (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mtimer8_intc_END                 (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mtimer9_intc_START               (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_mtimer9_intc_END                 (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_muart0_intr_START                (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_muart0_intr_END                  (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_uart3_intr_START                 (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_uart3_intr_END                   (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_uart0_intr_START                 (30)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_EN_sc_secondary_int_en_uart0_intr_END                   (30)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_UNION
 结构说明  : MDMSC_SECONDARY_INT_STATRAW 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: 系统二级中断中断寄存器。用于指示系统二级原始中断状态（屏蔽前）。对应bit为1表示有中断，为0表示无中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_raw_wbbp_otdoa_int2bbe        : 1;  /* bit[0] : wbbp_otdoa_int2bbe送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_bbpslot_bbe16_in14        : 1;  /* bit[1] : bbpslot_bbe16_int14送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_bbpslot_bbe16_in13        : 1;  /* bit[2] : bbpslot_bbe16_int13送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_upacc_dsp_int             : 1;  /* bit[3] : UPACC中断（upacc_dsp_int） */
        unsigned int  sc_secondary_int_raw_upacc_arm_int             : 1;  /* bit[4] : UPACC中断（upacc_arm_int） */
        unsigned int  sc_secondary_int_raw_g1_int_bbp_to_dsp_32k     : 1;  /* bit[5] : g1_int_bbp_to_dsp_32k送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_g1_int_bbp_to_dsp         : 1;  /* bit[6] : g1_int_bbp_to_dsp送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_g2_int_bbp_to_dsp_32k     : 1;  /* bit[7] : g2_int_bbp_to_dsp_32k送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_g2_int_bbp_to_dsp         : 1;  /* bit[8] : g2_int_bbp_to_dsp送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_bbpcom_ctu_g1_arm_intr    : 1;  /* bit[9] : bbpcom_ctu_g1_arm_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_bbpcom_ctu_g2_arm_intr    : 1;  /* bit[10]: bbpcom_ctu_g2_arm_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_bbpcom_ctu_w_arm_intr     : 1;  /* bit[11]: bbpcom_ctu_w_arm_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_card1_0ms_intr       : 1;  /* bit[12]: wbbp_card1_0ms_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_wdrx_slp_awk_sw_intr : 1;  /* bit[13]: wbbp_wdrx_slp_awk_sw_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_clk_sw_intr          : 1;  /* bit[14]: wbbp_clk_sw_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_card2_0ms_intr       : 1;  /* bit[15]: wbbp_card2_0ms_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_search_intr          : 1;  /* bit[16]: wbbp_search_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_rake_intr            : 1;  /* bit[17]: wbbp_rake_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_decode_intr          : 1;  /* bit[18]: wbbp_decode_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_card1_time_intr      : 1;  /* bit[19]: wbbp_card1_time_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_card2_time_intr      : 1;  /* bit[20]: wbbp_card2_time_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_multi_search_intr    : 1;  /* bit[21]: wbbp_multi_search_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_wbbp_bbpmst_intr          : 1;  /* bit[22]: wbbp_bbpmst_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_lte_dsp_warn_intr         : 1;  /* bit[23]: lte_dsp_warn_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_mwdt_bbe_intr             : 1;  /* bit[24]: mwdt_bbe_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_bbpmst_error_int          : 1;  /* bit[25]: bbpmst_error_int送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_mtimer8_intc              : 1;  /* bit[26]: mtimer8_intc送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_mtimer9_intc              : 1;  /* bit[27]: mtimer9_intc送给BBE16的中断 */
        unsigned int  sc_secondary_int_raw_muart0_intr               : 1;  /* bit[28]: Modem侧uart0(CCPU/BBE16复用)中断 */
        unsigned int  sc_secondary_int_raw_uart3_intr                : 1;  /* bit[29]: AP侧uart3（LTE/Connectivity共存复用）中断 */
        unsigned int  sc_secondary_int_raw_uart0_intr                : 1;  /* bit[30]: AP侧uart0(用于产线校准、软件调测) 中断 */
        unsigned int  reserved                                       : 1;  /* bit[31]: 保留
                                                                                       
                                                                                         */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_otdoa_int2bbe_START         (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_otdoa_int2bbe_END           (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpslot_bbe16_in14_START         (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpslot_bbe16_in14_END           (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpslot_bbe16_in13_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpslot_bbe16_in13_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_upacc_dsp_int_START              (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_upacc_dsp_int_END                (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_upacc_arm_int_START              (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_upacc_arm_int_END                (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g1_int_bbp_to_dsp_32k_START      (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g1_int_bbp_to_dsp_32k_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g1_int_bbp_to_dsp_START          (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g1_int_bbp_to_dsp_END            (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g2_int_bbp_to_dsp_32k_START      (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g2_int_bbp_to_dsp_32k_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g2_int_bbp_to_dsp_START          (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_g2_int_bbp_to_dsp_END            (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_g1_arm_intr_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_g1_arm_intr_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_g2_arm_intr_START     (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_g2_arm_intr_END       (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_w_arm_intr_START      (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpcom_ctu_w_arm_intr_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card1_0ms_intr_START        (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card1_0ms_intr_END          (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_wdrx_slp_awk_sw_intr_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_wdrx_slp_awk_sw_intr_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_clk_sw_intr_START           (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_clk_sw_intr_END             (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card2_0ms_intr_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card2_0ms_intr_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_search_intr_START           (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_search_intr_END             (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_rake_intr_START             (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_rake_intr_END               (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_decode_intr_START           (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_decode_intr_END             (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card1_time_intr_START       (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card1_time_intr_END         (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card2_time_intr_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_card2_time_intr_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_multi_search_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_multi_search_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_bbpmst_intr_START           (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_wbbp_bbpmst_intr_END             (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_lte_dsp_warn_intr_START          (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_lte_dsp_warn_intr_END            (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mwdt_bbe_intr_START              (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mwdt_bbe_intr_END                (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpmst_error_int_START           (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_bbpmst_error_int_END             (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mtimer8_intc_START               (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mtimer8_intc_END                 (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mtimer9_intc_START               (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_mtimer9_intc_END                 (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_muart0_intr_START                (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_muart0_intr_END                  (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_uart3_intr_START                 (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_uart3_intr_END                   (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_uart0_intr_START                 (30)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATRAW_sc_secondary_int_raw_uart0_intr_END                   (30)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_UNION
 结构说明  : MDMSC_SECONDARY_INT_STATMSK 寄存器结构定义。地址偏移量:0x0208，初值:0x00000000，宽度:32
 寄存器说明: 系统二级中断屏蔽后寄存器。用于指示系统二级中断状态（屏蔽后）。对应bit为1表示有中断，为0表示无中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_secondary_int_mask_wbbp_otdoa_int2bbe        : 1;  /* bit[0] : wbbp_otdoa_int2bbe送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_bbpslot_bbe16_in14        : 1;  /* bit[1] : bbpslot_bbe16_in14送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_bbpslot_bbe16_in13        : 1;  /* bit[2] : bbpslot_bbe16_in13送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_upacc_dsp_int             : 1;  /* bit[3] : UPACC中断（upacc_dsp_int） */
        unsigned int  sc_secondary_int_mask_upacc_arm_int             : 1;  /* bit[4] : UPACC中断（upacc_arm_int） */
        unsigned int  sc_secondary_int_mask_g1_int_bbp_to_dsp_32k     : 1;  /* bit[5] : g1_int_bbp_to_dsp_32k送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_g1_int_bbp_to_dsp         : 1;  /* bit[6] : g1_int_bbp_to_dsp送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_g2_int_bbp_to_dsp_32k     : 1;  /* bit[7] : g2_int_bbp_to_dsp_32k送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_g2_int_bbp_to_dsp         : 1;  /* bit[8] : g2_int_bbp_to_dsp送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_bbpcom_ctu_g1_arm_intr    : 1;  /* bit[9] : bbpcom_ctu_g1_arm_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_bbpcom_ctu_g2_arm_intr    : 1;  /* bit[10]: bbpcom_ctu_g2_arm_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_bbpcom_ctu_w_arm_intr     : 1;  /* bit[11]: bbpcom_ctu_w_arm_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_card1_0ms_intr       : 1;  /* bit[12]: wbbp_card1_0ms_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_wdrx_slp_awk_sw_intr : 1;  /* bit[13]: wbbp_wdrx_slp_awk_sw_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_clk_sw_intr          : 1;  /* bit[14]: wbbp_clk_sw_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_card2_0ms_intr       : 1;  /* bit[15]: wbbp_card2_0ms_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_search_intr          : 1;  /* bit[16]: wbbp_search_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_rake_intr            : 1;  /* bit[17]: wbbp_rake_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_decode_intr          : 1;  /* bit[18]: wbbp_decode_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_card1_time_intr      : 1;  /* bit[19]: wbbp_card1_time_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_card2_time_intr      : 1;  /* bit[20]: wbbp_card2_time_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_multi_search_intr    : 1;  /* bit[21]: wbbp_multi_search_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_wbbp_bbpmst_intr          : 1;  /* bit[22]: wbbp_bbpmst_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_lte_dsp_warn_intr         : 1;  /* bit[23]: lte_dsp_warn_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_mwdt_bbe_intr             : 1;  /* bit[24]: mwdt_bbe_intr送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_bbpmst_error_int          : 1;  /* bit[25]: bbpmst_error_int送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_mtimer8_intc              : 1;  /* bit[26]: mtimer8_intc送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_mtimer9_intc              : 1;  /* bit[27]: mtimer9_intc送给BBE16的中断 */
        unsigned int  sc_secondary_int_mask_muart0_intr               : 1;  /* bit[28]: Modem侧uart0(CCPU/BBE16复用)中断 */
        unsigned int  sc_secondary_int_mask_uart3_intr                : 1;  /* bit[29]: AP侧uart3（LTE/Connectivity共存复用）中断 */
        unsigned int  sc_secondary_int_mask_uart0_intr                : 1;  /* bit[30]: AP侧uart0(用于产线校准、软件调测) 中断 */
        unsigned int  reserved                                        : 1;  /* bit[31]: 保留。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_otdoa_int2bbe_START         (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_otdoa_int2bbe_END           (0)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpslot_bbe16_in14_START         (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpslot_bbe16_in14_END           (1)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpslot_bbe16_in13_START         (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpslot_bbe16_in13_END           (2)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_upacc_dsp_int_START              (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_upacc_dsp_int_END                (3)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_upacc_arm_int_START              (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_upacc_arm_int_END                (4)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g1_int_bbp_to_dsp_32k_START      (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g1_int_bbp_to_dsp_32k_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g1_int_bbp_to_dsp_START          (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g1_int_bbp_to_dsp_END            (6)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g2_int_bbp_to_dsp_32k_START      (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g2_int_bbp_to_dsp_32k_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g2_int_bbp_to_dsp_START          (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_g2_int_bbp_to_dsp_END            (8)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_g1_arm_intr_START     (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_g1_arm_intr_END       (9)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_g2_arm_intr_START     (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_g2_arm_intr_END       (10)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_w_arm_intr_START      (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpcom_ctu_w_arm_intr_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card1_0ms_intr_START        (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card1_0ms_intr_END          (12)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_wdrx_slp_awk_sw_intr_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_wdrx_slp_awk_sw_intr_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_clk_sw_intr_START           (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_clk_sw_intr_END             (14)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card2_0ms_intr_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card2_0ms_intr_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_search_intr_START           (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_search_intr_END             (16)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_rake_intr_START             (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_rake_intr_END               (17)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_decode_intr_START           (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_decode_intr_END             (18)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card1_time_intr_START       (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card1_time_intr_END         (19)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card2_time_intr_START       (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_card2_time_intr_END         (20)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_multi_search_intr_START     (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_multi_search_intr_END       (21)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_bbpmst_intr_START           (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_wbbp_bbpmst_intr_END             (22)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_lte_dsp_warn_intr_START          (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_lte_dsp_warn_intr_END            (23)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mwdt_bbe_intr_START              (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mwdt_bbe_intr_END                (24)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpmst_error_int_START           (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_bbpmst_error_int_END             (25)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mtimer8_intc_START               (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mtimer8_intc_END                 (26)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mtimer9_intc_START               (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_mtimer9_intc_END                 (27)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_muart0_intr_START                (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_muart0_intr_END                  (28)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_uart3_intr_START                 (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_uart3_intr_END                   (29)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_uart0_intr_START                 (30)
#define SOC_MODEM_SCTRL_MDMSC_SECONDARY_INT_STATMSK_sc_secondary_int_mask_uart0_intr_END                   (30)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_UNION
 结构说明  : MDMSC_CCPU_WKUP_INT_EN0 寄存器结构定义。地址偏移量:0x020C，初值:0x00000000，宽度:32
 寄存器说明: ccpu唤醒中断送给mcu的中断使能寄存器0。用于对mcu的唤醒中断进行屏蔽设置。对应bit为1表示使能相应中断，为0表示屏蔽中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_en0_usim0_detect_int   : 1;  /* bit[0] : [0] ：usim0热插拔检测中断 */
        unsigned int  ccpu_wakeup_int_en0_usim1_detect_int   : 1;  /* bit[1] : [1] ：usim1热插拔检测中断 */
        unsigned int  ccpu_wakeup_int_en0_GPIO2              : 1;  /* bit[2] : [2] ：GPIO2  */
        unsigned int  ccpu_wakeup_int_en0_mdmnoc_fault0_intr : 1;  /* bit[3] : [3] ：mdmnoc_fault0_intr */
        unsigned int  ccpu_wakeup_int_en0_mdmnoc_fault1_intr : 1;  /* bit[4] : [4] ：mdmnoc_fault1_intr */
        unsigned int  ccpu_wakeup_int_en0_ccpu_sftfiq_intr   : 1;  /* bit[5] : [5] ：ccpu_sftfiq_intr */
        unsigned int  reserved_0                             : 1;  /* bit[6] : [6] ：保留 */
        unsigned int  ccpu_wakeup_int_en0_GPIO7              : 1;  /* bit[7] : [7] ：GPIO7  */
        unsigned int  reserved_1                             : 1;  /* bit[8] : [8] ：保留 */
        unsigned int  ccpu_wakeup_int_en0_GPIO9              : 1;  /* bit[9] : [9] ：GPIO9 */
        unsigned int  reserved_2                             : 1;  /* bit[10]: [10]：保留 */
        unsigned int  reserved_3                             : 1;  /* bit[11]: [11]：保留 */
        unsigned int  reserved_4                             : 1;  /* bit[12]: [12]：保留 */
        unsigned int  reserved_5                             : 1;  /* bit[13]: [13]：保留 */
        unsigned int  ccpu_wakeup_int_en0_CSYSPWRUPREQ       : 1;  /* bit[14]: [14]：CSYSPWRUPREQ CoreSight system power up请求状态信号，高表示请求有效； */
        unsigned int  ccpu_wakeup_int_en0_CDBGPWRUPREQ       : 1;  /* bit[15]: [15]：CDBGPWRUPREQ CoreSight debug power up请求状态信号，高表示请求有效； */
        unsigned int  ccpu_wakeup_int_en0_OTG_WKP_STS        : 1;  /* bit[16]: [16]：OTG_WKP_STS  */
        unsigned int  ccpu_wakeup_int_en0_cbbp_intr01        : 1;  /* bit[17]: [17]：CDMA1x或CDMA EVDO睡眠/唤醒中断(32K) */
        unsigned int  ccpu_wakeup_int_en0_RTC_INT            : 1;  /* bit[18]: [18]：RTC_INT  */
        unsigned int  ccpu_wakeup_int_en0_MTimer0            : 1;  /* bit[19]: [19]：MTimer0 */
        unsigned int  ccpu_wakeup_int_en0_MTimer1            : 1;  /* bit[20]: [20]：MTimer1 */
        unsigned int  ccpu_wakeup_int_en0_MTimer2            : 1;  /* bit[21]: [21]：MTimer2 */
        unsigned int  ccpu_wakeup_int_en0_MTimer3            : 1;  /* bit[22]: [22]：MTimer3 */
        unsigned int  ccpu_wakeup_int_en0_MTimer4            : 1;  /* bit[23]: [23]：MTimer4 */
        unsigned int  ccpu_wakeup_int_en0_MTimer5            : 1;  /* bit[24]: [24]：MTimer5 */
        unsigned int  ccpu_wakeup_int_en0_MTimer6            : 1;  /* bit[25]: [25]：MTimer6 */
        unsigned int  ccpu_wakeup_int_en0_MTimer7            : 1;  /* bit[26]: [26]：MTimer7 */
        unsigned int  ccpu_wakeup_int_en0_MTimer8            : 1;  /* bit[27]: [27]：MTimer8 */
        unsigned int  ccpu_wakeup_int_en0_MTimer9            : 1;  /* bit[28]: [28]：MTimer9 */
        unsigned int  ccpu_wakeup_int_en0_MTimer10           : 1;  /* bit[29]: [29]：MTimer10 */
        unsigned int  ccpu_wakeup_int_en0_MTimer11           : 1;  /* bit[30]: [30]：MTimer11  */
        unsigned int  ccpu_wakeup_int_en0_MTimer12           : 1;  /* bit[31]: 对应CCPU的唤醒中断bit0～31： 
                                                                               [31]：MTimer12  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_usim0_detect_int_START    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_usim0_detect_int_END      (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_usim1_detect_int_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_usim1_detect_int_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO2_START               (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO2_END                 (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_mdmnoc_fault0_intr_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_mdmnoc_fault0_intr_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_mdmnoc_fault1_intr_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_mdmnoc_fault1_intr_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_ccpu_sftfiq_intr_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_ccpu_sftfiq_intr_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO7_START               (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO7_END                 (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO9_START               (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_GPIO9_END                 (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_CSYSPWRUPREQ_START        (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_CSYSPWRUPREQ_END          (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_CDBGPWRUPREQ_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_CDBGPWRUPREQ_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_OTG_WKP_STS_START         (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_OTG_WKP_STS_END           (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_cbbp_intr01_START         (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_cbbp_intr01_END           (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_RTC_INT_START             (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_RTC_INT_END               (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer0_START             (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer0_END               (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer1_START             (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer1_END               (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer2_START             (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer2_END               (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer3_START             (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer3_END               (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer4_START             (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer4_END               (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer5_START             (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer5_END               (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer6_START             (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer6_END               (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer7_START             (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer7_END               (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer8_START             (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer8_END               (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer9_START             (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer9_END               (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer10_START            (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer10_END              (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer11_START            (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer11_END              (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer12_START            (31)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN0_ccpu_wakeup_int_en0_MTimer12_END              (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_UNION
 结构说明  : MDMSC_CCPU_WKUP_INT_STATRAW0 寄存器结构定义。地址偏移量:0x0210，初值:0x00000000，宽度:32
 寄存器说明: mcpu唤醒中断送给mcu的原始唤醒中断寄存器。用于指示mcu的原始唤醒中断状态（屏蔽前）。对应bit为1表示有中断，为0表示无中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_raw0_usim0_detect_int   : 1;  /* bit[0] : [0] ：usim0热插拔检测中断 */
        unsigned int  ccpu_wakeup_int_raw0_usim1_detect_int   : 1;  /* bit[1] : [1] ：usim1热插拔检测中断 */
        unsigned int  ccpu_wakeup_int_raw0_GPIO2              : 1;  /* bit[2] : [2] ：GPIO2  */
        unsigned int  ccpu_wakeup_int_raw0_mdmnoc_fault0_intr : 1;  /* bit[3] : [3] ：mdmnoc_fault0_intr */
        unsigned int  ccpu_wakeup_int_raw0_mdmnoc_fault1_intr : 1;  /* bit[4] : [4] ：mdmnoc_fault1_intr */
        unsigned int  ccpu_wakeup_int_raw0_ccpu_sftfiq_intr   : 1;  /* bit[5] : [5] ：ccpu_sftfiq_intr */
        unsigned int  reserved_0                              : 1;  /* bit[6] : [6] ：保留 */
        unsigned int  ccpu_wakeup_int_raw0_GPIO7              : 1;  /* bit[7] : [7] ：GPIO7  */
        unsigned int  reserved_1                              : 1;  /* bit[8] : [8] ：保留 */
        unsigned int  ccpu_wakeup_int_raw0_GPIO9              : 1;  /* bit[9] : [9] ：GPIO9 */
        unsigned int  reserved_2                              : 1;  /* bit[10]: [10]：保留 */
        unsigned int  reserved_3                              : 1;  /* bit[11]: [11]：保留 */
        unsigned int  reserved_4                              : 1;  /* bit[12]: [12]：保留 */
        unsigned int  reserved_5                              : 1;  /* bit[13]: [13]：保留 */
        unsigned int  ccpu_wakeup_int_raw0_CSYSPWRUPREQ       : 1;  /* bit[14]: [14]：CSYSPWRUPREQ CoreSight system power up请求状态信号，高表示请求有效； */
        unsigned int  ccpu_wakeup_int_raw0_CDBGPWRUPREQ       : 1;  /* bit[15]: [15]：CDBGPWRUPREQ CoreSight debug power up请求状态信号，高表示请求有效； */
        unsigned int  ccpu_wakeup_int_raw0_OTG_WKP_STS        : 1;  /* bit[16]: [16]：OTG_WKP_STS  */
        unsigned int  ccpu_wakeup_int_raw0_cbbp_intr01        : 1;  /* bit[17]: [17]：CDMA1x或CDMA EVDO睡眠/唤醒中断(32K) */
        unsigned int  ccpu_wakeup_int_raw0_RTC_INT            : 1;  /* bit[18]: [18]：RTC_INT  */
        unsigned int  ccpu_wakeup_int_raw0_MTimer0            : 1;  /* bit[19]: [19]：MTimer0 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer1            : 1;  /* bit[20]: [20]：MTimer1 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer2            : 1;  /* bit[21]: [21]：MTimer2 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer3            : 1;  /* bit[22]: [22]：MTimer3 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer4            : 1;  /* bit[23]: [23]：MTimer4 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer5            : 1;  /* bit[24]: [24]：MTimer5 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer6            : 1;  /* bit[25]: [25]：MTimer6 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer7            : 1;  /* bit[26]: [26]：MTimer7 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer8            : 1;  /* bit[27]: [27]：MTimer8 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer9            : 1;  /* bit[28]: [28]：MTimer9 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer10           : 1;  /* bit[29]: [29]：MTimer10 */
        unsigned int  ccpu_wakeup_int_raw0_MTimer11           : 1;  /* bit[30]: [30]：MTimer11  */
        unsigned int  ccpu_wakeup_int_raw0_MTimer12           : 1;  /* bit[31]: 对应CCPU的唤醒中断bit0～31： 
                                                                                [31]：MTimer12  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_usim0_detect_int_START    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_usim0_detect_int_END      (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_usim1_detect_int_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_usim1_detect_int_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO2_START               (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO2_END                 (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_mdmnoc_fault0_intr_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_mdmnoc_fault0_intr_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_mdmnoc_fault1_intr_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_mdmnoc_fault1_intr_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_ccpu_sftfiq_intr_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_ccpu_sftfiq_intr_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO7_START               (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO7_END                 (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO9_START               (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_GPIO9_END                 (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_CSYSPWRUPREQ_START        (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_CSYSPWRUPREQ_END          (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_CDBGPWRUPREQ_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_CDBGPWRUPREQ_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_OTG_WKP_STS_START         (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_OTG_WKP_STS_END           (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_cbbp_intr01_START         (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_cbbp_intr01_END           (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_RTC_INT_START             (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_RTC_INT_END               (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer0_START             (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer0_END               (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer1_START             (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer1_END               (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer2_START             (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer2_END               (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer3_START             (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer3_END               (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer4_START             (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer4_END               (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer5_START             (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer5_END               (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer6_START             (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer6_END               (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer7_START             (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer7_END               (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer8_START             (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer8_END               (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer9_START             (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer9_END               (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer10_START            (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer10_END              (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer11_START            (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer11_END              (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer12_START            (31)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW0_ccpu_wakeup_int_raw0_MTimer12_END              (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_UNION
 结构说明  : MDMSC_CCPU_WKUP_INT_STATMSK0 寄存器结构定义。地址偏移量:0x0214，初值:0x00000000，宽度:32
 寄存器说明: mcpu唤醒中断送给mcu的屏蔽后唤醒中断寄存器。用于指示mcu的当前唤醒中断状态（屏蔽后）。对应bit为1表示有中断，为0表示无中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_mask0_usim0_detect_int   : 1;  /* bit[0] : [0] ：usim0热插拔检测中断 */
        unsigned int  ccpu_wakeup_int_mask0_usim1_detect_int   : 1;  /* bit[1] : [1] ：usim1热插拔检测中断 */
        unsigned int  ccpu_wakeup_int_mask0_GPIO2              : 1;  /* bit[2] : [2] ：GPIO2  */
        unsigned int  ccpu_wakeup_int_mask0_mdmnoc_fault0_intr : 1;  /* bit[3] : [3] ：mdmnoc_fault0_intr */
        unsigned int  ccpu_wakeup_int_mask0_mdmnoc_fault1_intr : 1;  /* bit[4] : [4] ：mdmnoc_fault1_intr */
        unsigned int  ccpu_wakeup_int_mask0_ccpu_sftfiq_intr   : 1;  /* bit[5] : [5] ：ccpu_sftfiq_intr */
        unsigned int  reserved_0                               : 1;  /* bit[6] : [6] ：保留 */
        unsigned int  ccpu_wakeup_int_mask0_GPIO7              : 1;  /* bit[7] : [7] ：GPIO7  */
        unsigned int  reserved_1                               : 1;  /* bit[8] : [8] ：保留 */
        unsigned int  ccpu_wakeup_int_mask0_GPIO9              : 1;  /* bit[9] : [9] ：GPIO9 */
        unsigned int  reserved_2                               : 1;  /* bit[10]: [10]：保留 */
        unsigned int  reserved_3                               : 1;  /* bit[11]: [11]：保留 */
        unsigned int  reserved_4                               : 1;  /* bit[12]: [12]：保留 */
        unsigned int  reserved_5                               : 1;  /* bit[13]: [13]：保留 */
        unsigned int  ccpu_wakeup_int_mask0_CSYSPWRUPREQ       : 1;  /* bit[14]: [14]：CSYSPWRUPREQ CoreSight system power up请求状态信号，高表示请求有效； */
        unsigned int  ccpu_wakeup_int_mask0_CDBGPWRUPREQ       : 1;  /* bit[15]: [15]：CDBGPWRUPREQ CoreSight debug power up请求状态信号，高表示请求有效； */
        unsigned int  ccpu_wakeup_int_mask0_OTG_WKP_STS        : 1;  /* bit[16]: [16]：OTG_WKP_STS  */
        unsigned int  ccpu_wakeup_int_mask0_cbbp_intr01        : 1;  /* bit[17]: [17]：CDMA1x或CDMA EVDO睡眠/唤醒中断(32K) */
        unsigned int  ccpu_wakeup_int_mask0_RTC_INT            : 1;  /* bit[18]: [18]：RTC_INT  */
        unsigned int  ccpu_wakeup_int_mask0_MTimer0            : 1;  /* bit[19]: [19]：MTimer0 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer1            : 1;  /* bit[20]: [20]：MTimer1 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer2            : 1;  /* bit[21]: [21]：MTimer2 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer3            : 1;  /* bit[22]: [22]：MTimer3 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer4            : 1;  /* bit[23]: [23]：MTimer4 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer5            : 1;  /* bit[24]: [24]：MTimer5 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer6            : 1;  /* bit[25]: [25]：MTimer6 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer7            : 1;  /* bit[26]: [26]：MTimer7 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer8            : 1;  /* bit[27]: [27]：MTimer8 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer9            : 1;  /* bit[28]: [28]：MTimer9 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer10           : 1;  /* bit[29]: [29]：MTimer10 */
        unsigned int  ccpu_wakeup_int_mask0_MTimer11           : 1;  /* bit[30]: [30]：MTimer11  */
        unsigned int  ccpu_wakeup_int_mask0_MTimer12           : 1;  /* bit[31]: 对应CCPU的唤醒中断bit0～31： 
                                                                                 [31]：MTimer12  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_usim0_detect_int_START    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_usim0_detect_int_END      (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_usim1_detect_int_START    (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_usim1_detect_int_END      (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO2_START               (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO2_END                 (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_mdmnoc_fault0_intr_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_mdmnoc_fault0_intr_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_mdmnoc_fault1_intr_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_mdmnoc_fault1_intr_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_ccpu_sftfiq_intr_START    (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_ccpu_sftfiq_intr_END      (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO7_START               (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO7_END                 (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO9_START               (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_GPIO9_END                 (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_CSYSPWRUPREQ_START        (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_CSYSPWRUPREQ_END          (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_CDBGPWRUPREQ_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_CDBGPWRUPREQ_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_OTG_WKP_STS_START         (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_OTG_WKP_STS_END           (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_cbbp_intr01_START         (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_cbbp_intr01_END           (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_RTC_INT_START             (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_RTC_INT_END               (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer0_START             (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer0_END               (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer1_START             (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer1_END               (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer2_START             (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer2_END               (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer3_START             (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer3_END               (22)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer4_START             (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer4_END               (23)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer5_START             (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer5_END               (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer6_START             (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer6_END               (25)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer7_START             (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer7_END               (26)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer8_START             (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer8_END               (27)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer9_START             (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer9_END               (28)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer10_START            (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer10_END              (29)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer11_START            (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer11_END              (30)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer12_START            (31)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK0_ccpu_wakeup_int_mask0_MTimer12_END              (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_UNION
 结构说明  : MDMSC_CCPU_WKUP_INT_EN1 寄存器结构定义。地址偏移量:0x0218，初值:0x00000000，宽度:32
 寄存器说明: mcpu唤醒中断送给mcu的唤醒中断使能寄存器。用于对mcu的唤醒中断进行屏蔽设置。对应bit为1表示使能相应中断，为0表示屏蔽中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_en1_MTimer13           : 1;  /* bit[0]    : [0] ：MTimer13 */
        unsigned int  ccpu_wakeup_int_en1_MTimer14           : 1;  /* bit[1]    : [1] ：MTimer14  */
        unsigned int  ccpu_wakeup_int_en1_MTimer15           : 1;  /* bit[2]    : [2] ：MTimer15  */
        unsigned int  ccpu_wakeup_int_en1_MTimer16           : 1;  /* bit[3]    : [3] ：MTimer16  */
        unsigned int  ccpu_wakeup_int_en1_MTimer17           : 1;  /* bit[4]    : [4] ：MTimer17  */
        unsigned int  ccpu_wakeup_int_en1_MTimer18           : 1;  /* bit[5]    : [5] ：MTimer18  */
        unsigned int  ccpu_wakeup_int_en1_MTimer19           : 1;  /* bit[6]    : [6] ：MTimer19 */
        unsigned int  ccpu_wakeup_int_en1_MWatchDog          : 1;  /* bit[7]    : [7] ：MWatchDog */
        unsigned int  ccpu_wakeup_int_en1_CCPU_WKUP_VOTE     : 1;  /* bit[8]    : [8] ：MCPU_WKUP_VOTE */
        unsigned int  ccpu_wakeup_int_en1_GBBP1WKUP          : 1;  /* bit[9]    : [9] ：GSM1 DRX唤醒中断 */
        unsigned int  ccpu_wakeup_int_en1_GBBP2WKUP          : 1;  /* bit[10]   : [10]：GSM2 DRX唤醒中断 */
        unsigned int  ccpu_wakeup_int_en1_WBBP1WKUP          : 1;  /* bit[11]   : [11]：WBBP唤醒中断1  */
        unsigned int  ccpu_wakeup_int_en1_lte_arm_wakeup_int : 1;  /* bit[12]   : [12]：lte_arm_wakeup_int  */
        unsigned int  ccpu_wakeup_int_en1_tds_drx_arm_int1   : 1;  /* bit[13]   : [13]：tds_drx_arm_int1  */
        unsigned int  ccpu_wakeup_int_en1_IPC2CCPU_01        : 1;  /* bit[14]   : 非安全IPC输出给CCPU的核间中断0（ns_ipc_cpu_intr0[1]） */
        unsigned int  ccpu_wakeup_int_en1_IPF_0              : 1;  /* bit[15]   : [15]：IPF_0 */
        unsigned int  ccpu_wakeup_int_en1_IPF_1              : 1;  /* bit[16]   : [16]：IPF_1 */
        unsigned int  ccpu_wakeup_int_en1_SOCP_0             : 1;  /* bit[17]   : [17]：SOCP_0 */
        unsigned int  ccpu_wakeup_int_en1_SOCP_1             : 1;  /* bit[18]   : [18]：SOCP_1 */
        unsigned int  ccpu_wakeup_int_en1_IPC2CCPU_06        : 1;  /* bit[19]   : 非安全IPC输出给CCPU的核间中断1（ns_ipc_cpu_intr0[6]） */
        unsigned int  ccpu_wakeup_int_en1_SEC_IPC2CCPU_01    : 1;  /* bit[20]   : 安全IPC输出给CCPU的核间中断（s_ipc_cpu_intr0[1]） */
        unsigned int  reserved                               : 11; /* bit[21-31]: 对应CCPU的唤醒中断bit32～52：
                                                                                  其他：保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer13_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer13_END              (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer14_START            (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer14_END              (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer15_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer15_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer16_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer16_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer17_START            (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer17_END              (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer18_START            (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer18_END              (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer19_START            (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MTimer19_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MWatchDog_START           (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_MWatchDog_END             (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_CCPU_WKUP_VOTE_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_CCPU_WKUP_VOTE_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_GBBP1WKUP_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_GBBP1WKUP_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_GBBP2WKUP_START           (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_GBBP2WKUP_END             (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_WBBP1WKUP_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_WBBP1WKUP_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_lte_arm_wakeup_int_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_lte_arm_wakeup_int_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_tds_drx_arm_int1_START    (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_tds_drx_arm_int1_END      (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPC2CCPU_01_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPC2CCPU_01_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPF_0_START               (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPF_0_END                 (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPF_1_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPF_1_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SOCP_0_START              (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SOCP_0_END                (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SOCP_1_START              (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SOCP_1_END                (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPC2CCPU_06_START         (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_IPC2CCPU_06_END           (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SEC_IPC2CCPU_01_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_EN1_ccpu_wakeup_int_en1_SEC_IPC2CCPU_01_END       (20)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_UNION
 结构说明  : MDMSC_CCPU_WKUP_INT_STATRAW1 寄存器结构定义。地址偏移量:0x021C，初值:0x00000000，宽度:32
 寄存器说明: mcpu唤醒中断送给mcu的原始唤醒中断寄存器。用于指示mcu的原始唤醒中断状态（屏蔽前）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_raw1_MTimer13           : 1;  /* bit[0]    : [0] ：MTimer13 */
        unsigned int  ccpu_wakeup_int_raw1_MTimer14           : 1;  /* bit[1]    : [1] ：MTimer14  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer15           : 1;  /* bit[2]    : [2] ：MTimer15  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer16           : 1;  /* bit[3]    : [3] ：MTimer16  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer17           : 1;  /* bit[4]    : [4] ：MTimer17  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer18           : 1;  /* bit[5]    : [5] ：MTimer18  */
        unsigned int  ccpu_wakeup_int_raw1_MTimer19           : 1;  /* bit[6]    : [6] ：MTimer19 */
        unsigned int  ccpu_wakeup_int_raw1_MWatchDog          : 1;  /* bit[7]    : [7] ：MWatchDog */
        unsigned int  ccpu_wakeup_int_raw1_CCPU_WKUP_VOTE     : 1;  /* bit[8]    : [8] ：MCPU_WKUP_VOTE */
        unsigned int  ccpu_wakeup_int_raw1_GBBP1WKUP          : 1;  /* bit[9]    : [9] ：GSM1 DRX唤醒中断 */
        unsigned int  ccpu_wakeup_int_raw1_GBBP2WKUP          : 1;  /* bit[10]   : [10]：GSM2 DRX唤醒中断 */
        unsigned int  ccpu_wakeup_int_raw1_WBBP1WKUP          : 1;  /* bit[11]   : [11]：WBBP唤醒中断1  */
        unsigned int  ccpu_wakeup_int_raw1_lte_arm_wakeup_int : 1;  /* bit[12]   : [12]：lte_arm_wakeup_int  */
        unsigned int  ccpu_wakeup_int_raw1_tds_drx_arm_int1   : 1;  /* bit[13]   : [13]：tds_drx_arm_int1  */
        unsigned int  ccpu_wakeup_int_raw1_IPC2CCPU_01        : 1;  /* bit[14]   : 非安全IPC输出给CCPU的核间中断0（ns_ipc_cpu_intr0[1]） */
        unsigned int  ccpu_wakeup_int_raw1_IPF_0              : 1;  /* bit[15]   : [15]：IPF_0 */
        unsigned int  ccpu_wakeup_int_raw1_IPF_1              : 1;  /* bit[16]   : [16]：IPF_1 */
        unsigned int  ccpu_wakeup_int_raw1_SOCP_0             : 1;  /* bit[17]   : [17]：SOCP_0 */
        unsigned int  ccpu_wakeup_int_raw1_SOCP_1             : 1;  /* bit[18]   : [18]：SOCP_1 */
        unsigned int  ccpu_wakeup_int_raw1_IPC2CCPU_06        : 1;  /* bit[19]   : 非安全IPC输出给CCPU的核间中断1（ns_ipc_cpu_intr0[6]） */
        unsigned int  ccpu_wakeup_int_raw1_SEC_IPC2CCPU_01    : 1;  /* bit[20]   : 安全IPC输出给CCPU的核间中断（s_ipc_cpu_intr0[1]） */
        unsigned int  reserved                                : 11; /* bit[21-31]: 对应CCPU的唤醒中断bit32～52：
                                                                                   其他：保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer13_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer13_END              (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer14_START            (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer14_END              (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer15_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer15_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer16_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer16_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer17_START            (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer17_END              (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer18_START            (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer18_END              (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer19_START            (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MTimer19_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MWatchDog_START           (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_MWatchDog_END             (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_CCPU_WKUP_VOTE_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_CCPU_WKUP_VOTE_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_GBBP1WKUP_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_GBBP1WKUP_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_GBBP2WKUP_START           (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_GBBP2WKUP_END             (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_WBBP1WKUP_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_WBBP1WKUP_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_lte_arm_wakeup_int_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_lte_arm_wakeup_int_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_tds_drx_arm_int1_START    (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_tds_drx_arm_int1_END      (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPC2CCPU_01_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPC2CCPU_01_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPF_0_START               (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPF_0_END                 (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPF_1_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPF_1_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SOCP_0_START              (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SOCP_0_END                (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SOCP_1_START              (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SOCP_1_END                (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPC2CCPU_06_START         (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_IPC2CCPU_06_END           (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SEC_IPC2CCPU_01_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATRAW1_ccpu_wakeup_int_raw1_SEC_IPC2CCPU_01_END       (20)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_UNION
 结构说明  : MDMSC_CCPU_WKUP_INT_STATMSK1 寄存器结构定义。地址偏移量:0x0220，初值:0x00000000，宽度:32
 寄存器说明: mcpu唤醒中断送给mcu的屏蔽后唤醒中断寄存器。用于指示mcu的当前唤醒中断状态（屏蔽后）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_wakeup_int_mask1_MTimer13           : 1;  /* bit[0]    : [0] ：MTimer13 */
        unsigned int  ccpu_wakeup_int_mask1_MTimer14           : 1;  /* bit[1]    : [1] ：MTimer14  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer15           : 1;  /* bit[2]    : [2] ：MTimer15  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer16           : 1;  /* bit[3]    : [3] ：MTimer16  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer17           : 1;  /* bit[4]    : [4] ：MTimer17  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer18           : 1;  /* bit[5]    : [5] ：MTimer18  */
        unsigned int  ccpu_wakeup_int_mask1_MTimer19           : 1;  /* bit[6]    : [6] ：MTimer19 */
        unsigned int  ccpu_wakeup_int_mask1_MWatchDog          : 1;  /* bit[7]    : [7] ：MWatchDog */
        unsigned int  ccpu_wakeup_int_mask1_CCPU_WKUP_VOTE     : 1;  /* bit[8]    : [8] ：CCPU_WKUP_VOTE */
        unsigned int  ccpu_wakeup_int_mask1_GBBP1WKUP          : 1;  /* bit[9]    : [9] ：GSM1 DRX唤醒中断 */
        unsigned int  ccpu_wakeup_int_mask1_GBBP2WKUP          : 1;  /* bit[10]   : [10]：GSM2 DRX唤醒中断 */
        unsigned int  ccpu_wakeup_int_mask1_WBBP1WKUP          : 1;  /* bit[11]   : [11]：WBBP唤醒中断1  */
        unsigned int  ccpu_wakeup_int_mask1_lte_arm_wakeup_int : 1;  /* bit[12]   : [12]：lte_arm_wakeup_int  */
        unsigned int  ccpu_wakeup_int_mask1_tds_drx_arm_int1   : 1;  /* bit[13]   : [13]：tds_drx_arm_int1  */
        unsigned int  ccpu_wakeup_int_mask1_IPC2CCPU_01        : 1;  /* bit[14]   : 非安全IPC输出给CCPU的核间中断0（ns_ipc_cpu_intr0[1]） */
        unsigned int  ccpu_wakeup_int_mask1_IPF_0              : 1;  /* bit[15]   : [15]：IPF_0 */
        unsigned int  ccpu_wakeup_int_mask1_IPF_1              : 1;  /* bit[16]   : [16]：IPF_1 */
        unsigned int  ccpu_wakeup_int_mask1_SOCP_0             : 1;  /* bit[17]   : [17]：SOCP_0 */
        unsigned int  ccpu_wakeup_int_mask1_SOCP_1             : 1;  /* bit[18]   : [18]：SOCP_1 */
        unsigned int  ccpu_wakeup_int_mask1_IPC2CCPU_06        : 1;  /* bit[19]   : 非安全IPC输出给CCPU的核间中断1（ns_ipc_cpu_intr0[6]） */
        unsigned int  ccpu_wakeup_int_mask1_SEC_IPC2CCPU_01    : 1;  /* bit[20]   : 安全IPC输出给CCPU的核间中断（s_ipc_cpu_intr0[1]） */
        unsigned int  ccpu_wakeup_int_mask1                    : 11; /* bit[21-31]: 对应CCPU的唤醒中断bit32～52：
                                                                                    其他：保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer13_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer13_END              (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer14_START            (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer14_END              (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer15_START            (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer15_END              (2)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer16_START            (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer16_END              (3)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer17_START            (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer17_END              (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer18_START            (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer18_END              (5)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer19_START            (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MTimer19_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MWatchDog_START           (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_MWatchDog_END             (7)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_CCPU_WKUP_VOTE_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_CCPU_WKUP_VOTE_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_GBBP1WKUP_START           (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_GBBP1WKUP_END             (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_GBBP2WKUP_START           (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_GBBP2WKUP_END             (10)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_WBBP1WKUP_START           (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_WBBP1WKUP_END             (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_lte_arm_wakeup_int_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_lte_arm_wakeup_int_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_tds_drx_arm_int1_START    (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_tds_drx_arm_int1_END      (13)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPC2CCPU_01_START         (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPC2CCPU_01_END           (14)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPF_0_START               (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPF_0_END                 (15)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPF_1_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPF_1_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SOCP_0_START              (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SOCP_0_END                (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SOCP_1_START              (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SOCP_1_END                (18)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPC2CCPU_06_START         (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_IPC2CCPU_06_END           (19)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SEC_IPC2CCPU_01_START     (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_SEC_IPC2CCPU_01_END       (20)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_START                     (21)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_WKUP_INT_STATMSK1_ccpu_wakeup_int_mask1_END                       (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_UNION
 结构说明  : MDMSC_INT_RAW_STAT 寄存器结构定义。地址偏移量:0x0224，初值:0x00000000，宽度:32
 寄存器说明: 原始内部中断寄存器，用于指示SC内部的原始中断状态(屏蔽前)。对应bit为1表示有中断，为0表示无中断
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_statr_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog 复位请求中断，送给CCPU */
        unsigned int  mdmsc_int_statr_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog 复位请求中断，送给MCU/ACPU */
        unsigned int  reserved                            : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_mdmsc_int_statr_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_mdmsc_int_statr_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_mdmsc_int_statr_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_RAW_STAT_mdmsc_int_statr_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_UNION
 结构说明  : MDMSC_INT_MASK_STAT 寄存器结构定义。地址偏移量:0x0228，初值:0x00000000，宽度:32
 寄存器说明: 屏蔽后内部中断寄存器。用于指示SC当前内部中断状态(屏蔽后)，对应bit为1表示有中断，为0表示无中断
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_statm_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog 复位请求中断，送给CCPU */
        unsigned int  mdmsc_int_statm_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog 复位请求中断，送给MCU/ACPU */
        unsigned int  reserved                            : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_mdmsc_int_statm_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_mdmsc_int_statm_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_mdmsc_int_statm_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_MASK_STAT_mdmsc_int_statm_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_UNION
 结构说明  : MDMSC_INT_CLEAR 寄存器结构定义。地址偏移量:0x022C，初值:0x00000000，宽度:32
 寄存器说明: 内部中断清除寄存器。给相应中断比特位写1，表示清除对应的中断状态，包括原始内部中断寄存器和屏蔽后内部中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_clear_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog 复位请求中断，送给CCPU */
        unsigned int  mdmsc_int_clear_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog 复位请求中断，送给MCU/ACPU */
        unsigned int  reserved                            : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_mdmsc_int_clear_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_mdmsc_int_clear_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_mdmsc_int_clear_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_CLEAR_mdmsc_int_clear_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_EN_UNION
 结构说明  : MDMSC_INT_EN 寄存器结构定义。地址偏移量:0x0230，初值:0x00000000，宽度:32
 寄存器说明: 内部中断屏蔽寄存器。对比特写1，打开屏蔽；写0不影响屏蔽的状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_en_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog 复位请求中断，送给CCPU */
        unsigned int  mdmsc_int_en_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog 复位请求中断，送给MCU/ACPU */
        unsigned int  reserved                         : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_EN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_mdmsc_int_en_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_mdmsc_int_en_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_mdmsc_int_en_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_mdmsc_int_en_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_DIS_UNION
 结构说明  : MDMSC_INT_DIS 寄存器结构定义。地址偏移量:0x0234，初值:0x00000000，宽度:32
 寄存器说明: 内部中断屏蔽寄存器，对比特写1，禁止屏蔽；写0不影响时钟屏蔽的状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_dis_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog 复位请求中断，送给CCPU */
        unsigned int  mdmsc_int_dis_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog 复位请求中断，送给MCU/ACPU */
        unsigned int  reserved                          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_DIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_mdmsc_int_dis_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_mdmsc_int_dis_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_mdmsc_int_dis_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_DIS_mdmsc_int_dis_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_UNION
 结构说明  : MDMSC_INT_EN_STAT 寄存器结构定义。地址偏移量:0x0238，初值:0x00000000，宽度:32
 寄存器说明: 内部中断使能寄存器，用于SC内部中断的屏蔽设置。对应bit为1表示使能相应中断，为0表示屏蔽中断
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_int_en_sta_bbe16_mwtd_intr_req : 1;  /* bit[0]   : BBE16 watchdog 复位请求中断，送给CCPU */
        unsigned int  mdmsc_int_en_sta_ccpu_mwtd_intr_req  : 1;  /* bit[1]   : ccpu watchdog 复位请求中断，送给MCU/ACPU */
        unsigned int  reserved                             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_mdmsc_int_en_sta_bbe16_mwtd_intr_req_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_mdmsc_int_en_sta_bbe16_mwtd_intr_req_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_mdmsc_int_en_sta_ccpu_mwtd_intr_req_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_EN_STAT_mdmsc_int_en_sta_ccpu_mwtd_intr_req_END     (1)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_UNION
 结构说明  : MDMSC_INT_COUNT_EN0 寄存器结构定义。地址偏移量:0x0250，初值:0x00000000，宽度:32
 寄存器说明: 中断计数使能寄存器，软件调试使用
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_en0  : 1;  /* bit[0] : GUBBP VOMOS中断 count enable 1:enable 0:disable */
        unsigned int  sc_int_count_en1  : 1;  /* bit[1] : WBBP中断10 count enable
                                                          （wbbp_bbpmst_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en2  : 1;  /* bit[2] : WBBP中断9 count enable
                                                          （wbbp_multi_search_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en3  : 1;  /* bit[3] : WBBP中断8 count enable
                                                          （wbbp_card2_time_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en4  : 1;  /* bit[4] : WBBP中断7 count enable
                                                          （wbbp_card1_time_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en5  : 1;  /* bit[5] : WBBP中断6 count enable
                                                          （wbbp_decode_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en6  : 1;  /* bit[6] : WBBP中断5 count enable
                                                          （wbbp_rake_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en7  : 1;  /* bit[7] : WBBP中断4 count enable
                                                          （wbbp_search_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en8  : 1;  /* bit[8] : WBBP中断3 count enable
                                                          （wbbp_card2_0ms_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en9  : 1;  /* bit[9] : WBBP中断2 count enable
                                                          （wbbp_clk_sw_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en10 : 1;  /* bit[10]: WBBP中断1 count enable
                                                          （wbbp_wdrx_slp_awk_sw_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en11 : 1;  /* bit[11]: WBBP中断0 count enable
                                                          （wbbp_card1_0ms_intr）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en12 : 1;  /* bit[12]: GBBP中断3 count enable
                                                          （g1_int_bbp_to_dsp_32k）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en13 : 1;  /* bit[13]: GBBP中断2 count enable
                                                          （g1_int_bbp_to_dsp）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en14 : 1;  /* bit[14]: GBBP中断1 count enable
                                                          （g1_int_bbp_to_cpu_32k）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en15 : 1;  /* bit[15]: GBBP中断0 count enable
                                                          （g1_int_bbp_to_cpu）
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en16 : 1;  /* bit[16]: CTU_W2ARM中断 count enable 
                                                          (bbpcom_ctu_w_arm_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en17 : 1;  /* bit[17]: CTU_G2ARM中断 count enable 
                                                          (bbpcom_ctu_g1_arm_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en18 : 1;  /* bit[18]: GU_Cipher_intr[1] count enable 
                                                          (gucipher0_arm_dl_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en19 : 1;  /* bit[19]: GU_Cipher_intr[0] count enable 
                                                          (gucipher0_arm_ul_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en20 : 1;  /* bit[20]: UPACC_intr[1] count enable
                                                          (upacc_dsp_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en21 : 1;  /* bit[21]: UPACC_intr[0] count enable
                                                          (upacc_arm_intr)
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en22 : 1;  /* bit[22]: IPC2CCPU_1 count enable 
                                                          (ipc_ns_lock_intr[1])
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en23 : 1;  /* bit[23]: IPC2CCPU_0 count enable 
                                                          (ipc_ns_inner_core_intr[1])
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en24 : 1;  /* bit[24]: MEDMAC1 count enable 
                                                          (mdmdmac_s_intr[1])
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en25 : 1;  /* bit[25]: SOCP_intr[1] count enable 
                                                          (socp_intr[1])
                                                          1:enable 0:disable */
        unsigned int  sc_int_count_en26 : 1;  /* bit[26]: SOCP_intr[0] count enable 
                                                          (socp_intr[0])
                                                          1:enable 0:disable  */
        unsigned int  reserved_0        : 1;  /* bit[27]: 保留 */
        unsigned int  reserved_1        : 1;  /* bit[28]: 保留 */
        unsigned int  sc_int_count_en29 : 1;  /* bit[29]: GBBP2中断3 GSM2 DRX中断(g2_int_bbp_to_dsp_32k) */
        unsigned int  sc_int_count_en30 : 1;  /* bit[30]: GBBP2中断2 GSM2非DRX中断1(g2_int_bbp_to_dsp) */
        unsigned int  sc_int_count_en31 : 1;  /* bit[31]: GBBP2中断1 GSM2预留
                                                          (g2_int_bbp_to_cpu_32k) */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en0_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en0_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en1_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en1_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en2_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en2_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en3_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en3_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en4_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en4_END     (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en5_START   (5)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en5_END     (5)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en6_START   (6)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en6_END     (6)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en7_START   (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en7_END     (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en8_START   (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en8_END     (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en9_START   (9)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en9_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en10_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en10_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en11_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en11_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en12_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en12_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en13_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en13_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en14_START  (14)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en14_END    (14)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en15_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en15_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en16_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en16_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en17_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en17_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en18_START  (18)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en18_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en19_START  (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en19_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en20_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en20_END    (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en21_START  (21)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en21_END    (21)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en22_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en22_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en23_START  (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en23_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en24_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en24_END    (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en25_START  (25)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en25_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en26_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en26_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en29_START  (29)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en29_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en30_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en30_END    (30)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en31_START  (31)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN0_sc_int_count_en31_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_UNION
 结构说明  : MDMSC_INT_COUNT_EN1 寄存器结构定义。地址偏移量:0x0254，初值:0x00000000，宽度:32
 寄存器说明: 中断计数使能寄存器，软件调试使用
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_en32 : 1;  /* bit[0] : GBBP2中断0 GSM2非DRX中断0(g2_int_bbp_to_cpu) */
        unsigned int  sc_int_count_en33 : 1;  /* bit[1] : CTU_G2toARM中断 BBP COMMON CTU_GBBP2 to ARM中断
                                                          (bbpcom_ctu_g2_arm_intr) */
        unsigned int  sc_int_count_en34 : 1;  /* bit[2] : IPC2CCPU_2 IPC输出给CCPU的核间中断1（ipc_ns_inner_core_intr[6]） */
        unsigned int  sc_int_count_en35 : 1;  /* bit[3] : 安全IPC输出给CCPU的资源锁中断（ipc_s_lock_intr[1]） */
        unsigned int  sc_int_count_en36 : 1;  /* bit[4] : 安全IPC输出给CCPU的核间中断(ipc_s_inner_core_intr[1]） */
        unsigned int  sc_int_count_en37 : 1;  /* bit[5] : TDS模时：表示tds hsupa模块完成中断tds_hsupa_intr；C模时：表示CDMA1x或CDMA EVDO睡眠/唤醒中断(32K)cbbp_intr01.
                                                          (tcbbp_intr01) */
        unsigned int  sc_int_count_en38 : 1;  /* bit[6] : TDS模时：表示tds harq模块完成中断tds_harq_intr；C模时：表示CDMA1x或CDMA EVDO时钟切换中断(imi时钟)cbbp_intr02.
                                                          (tcbbp_intr02) */
        unsigned int  sc_int_count_en39 : 1;  /* bit[7] : TDS模时：表示tds turbo模块完成中断tds_turbo_intr；C模时：表示CDMA1x或CDMA EVDO多径搜索/小区测量中断cbbp_intr03.
                                                          (tcbbp_intr03) */
        unsigned int  sc_int_count_en40 : 1;  /* bit[8] : TDS模时：表示tds viterbi模块完成中断tds_viterbi_intr；C模时：表示CDMA1x或CDMA EVDO定时中断cbbp_intr04.
                                                          (tcbbp_intr04) */
        unsigned int  sc_int_count_en41 : 1;  /* bit[9] : TDS模时：表示tds前端模块中断tds_fpu_intr；C模时：表示CDMA1x或CDMA EVDO编码/译码中断cbbp_intr05.
                                                          (tcbbp_intr05) */
        unsigned int  sc_int_count_en42 : 1;  /* bit[10]: TDS模时：表示tds射频前端中断tds_rfc_intr；C模时：表示CDMA1x或CDMA EVDO射频上报/数据搬移中断cbbp_intr06.
                                                          (tcbbp_intr06) */
        unsigned int  sc_int_count_en43 : 1;  /* bit[11]: 保留。 */
        unsigned int  sc_int_count_en44 : 1;  /* bit[12]: 保留。 */
        unsigned int  sc_int_count_en45 : 1;  /* bit[13]: 保留。 */
        unsigned int  sc_int_count_en46 : 1;  /* bit[14]: 保留。 */
        unsigned int  sc_int_count_en47 : 1;  /* bit[15]: 保留。 */
        unsigned int  sc_int_count_en48 : 1;  /* bit[16]: 保留。 */
        unsigned int  sc_int_count_en49 : 1;  /* bit[17]: 保留。 */
        unsigned int  sc_int_count_en50 : 1;  /* bit[18]: 保留。 */
        unsigned int  sc_int_count_en51 : 1;  /* bit[19]: 保留。 */
        unsigned int  sc_int_count_en52 : 1;  /* bit[20]: 保留。 */
        unsigned int  sc_int_count_en53 : 1;  /* bit[21]: 保留。 */
        unsigned int  sc_int_count_en54 : 1;  /* bit[22]: 保留。 */
        unsigned int  sc_int_count_en55 : 1;  /* bit[23]: 保留。 */
        unsigned int  sc_int_count_en56 : 1;  /* bit[24]: 保留。 */
        unsigned int  sc_int_count_en57 : 1;  /* bit[25]: 保留。 */
        unsigned int  sc_int_count_en58 : 1;  /* bit[26]: 保留。 */
        unsigned int  sc_int_count_en59 : 1;  /* bit[27]: 保留。 */
        unsigned int  sc_int_count_en60 : 1;  /* bit[28]: 保留。 */
        unsigned int  sc_int_count_en61 : 1;  /* bit[29]: 保留。 */
        unsigned int  sc_int_count_en62 : 1;  /* bit[30]: 保留。 */
        unsigned int  sc_int_count_en63 : 1;  /* bit[31]: 保留。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en32_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en32_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en33_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en33_END    (1)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en34_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en34_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en35_START  (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en35_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en36_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en36_END    (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en37_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en37_END    (5)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en38_START  (6)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en38_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en39_START  (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en39_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en40_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en40_END    (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en41_START  (9)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en41_END    (9)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en42_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en42_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en43_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en43_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en44_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en44_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en45_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en45_END    (13)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en46_START  (14)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en46_END    (14)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en47_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en47_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en48_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en48_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en49_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en49_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en50_START  (18)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en50_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en51_START  (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en51_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en52_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en52_END    (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en53_START  (21)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en53_END    (21)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en54_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en54_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en55_START  (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en55_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en56_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en56_END    (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en57_START  (25)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en57_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en58_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en58_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en59_START  (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en59_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en60_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en60_END    (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en61_START  (29)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en61_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en62_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en62_END    (30)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en63_START  (31)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_EN1_sc_int_count_en63_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_UNION
 结构说明  : MDMSC_INT_COUNT_STAT0 寄存器结构定义。地址偏移量:0x0258，初值:0x00000000，宽度:32
 寄存器说明: 中断计数状态寄存器0。用于软件调试。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta0 : 4;  /* bit[0-3]  : GUBBP VOMOS中断 count number */
        unsigned int  sc_int_count_sta1 : 4;  /* bit[4-7]  : WBBP中断10 count number */
        unsigned int  sc_int_count_sta2 : 4;  /* bit[8-11] : WBBP中断9 count number */
        unsigned int  sc_int_count_sta3 : 4;  /* bit[12-15]: WBBP中断8 count number */
        unsigned int  sc_int_count_sta4 : 4;  /* bit[16-19]: WBBP中断7 count number */
        unsigned int  sc_int_count_sta5 : 4;  /* bit[20-23]: WBBP中断6 count number */
        unsigned int  sc_int_count_sta6 : 4;  /* bit[24-27]: WBBP中断5 count number */
        unsigned int  sc_int_count_sta7 : 4;  /* bit[28-31]: WBBP中断4 count number */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta0_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta0_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta1_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta1_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta2_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta2_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta3_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta3_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta4_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta4_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta5_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta5_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta6_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta6_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta7_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT0_sc_int_count_sta7_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_UNION
 结构说明  : MDMSC_INT_COUNT_STAT1 寄存器结构定义。地址偏移量:0x025C，初值:0x00000000，宽度:32
 寄存器说明: 中断计数状态寄存器1。用于软件调试。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta8  : 4;  /* bit[0-3]  : WBBP中断3 count number */
        unsigned int  sc_int_count_sta9  : 4;  /* bit[4-7]  : WBBP中断2 count number */
        unsigned int  sc_int_count_sta10 : 4;  /* bit[8-11] : WBBP中断1 count number */
        unsigned int  sc_int_count_sta11 : 4;  /* bit[12-15]: WBBP中断0 count number */
        unsigned int  sc_int_count_sta12 : 4;  /* bit[16-19]: GBBP中断3 count number */
        unsigned int  sc_int_count_sta13 : 4;  /* bit[20-23]: GBBP中断2 count number */
        unsigned int  sc_int_count_sta14 : 4;  /* bit[24-27]: GBBP中断1 count number */
        unsigned int  sc_int_count_sta15 : 4;  /* bit[28-31]: GBBP中断0 count number */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta8_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta8_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta9_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta9_END     (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta10_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta10_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta11_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta11_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta12_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta12_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta13_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta13_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta14_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta14_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta15_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT1_sc_int_count_sta15_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_UNION
 结构说明  : MDMSC_INT_COUNT_STAT2 寄存器结构定义。地址偏移量:0x0260，初值:0x00000000，宽度:32
 寄存器说明: 中断计数状态寄存器2。用于软件调试。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta16 : 4;  /* bit[0-3]  : CTU_W2ARM中断 count number */
        unsigned int  sc_int_count_sta17 : 4;  /* bit[4-7]  : CTU_G2ARM中断 count number */
        unsigned int  sc_int_count_sta18 : 4;  /* bit[8-11] : GU_Cipher_intr[1] count number */
        unsigned int  sc_int_count_sta19 : 4;  /* bit[12-15]: GU_Cipher_intr[0] count number */
        unsigned int  sc_int_count_sta20 : 4;  /* bit[16-19]: UPACC_intr[1] count number */
        unsigned int  sc_int_count_sta21 : 4;  /* bit[20-23]: UPACC_intr[0] count number */
        unsigned int  sc_int_count_sta22 : 4;  /* bit[24-27]: IPC2CCPU_1 count number */
        unsigned int  sc_int_count_sta23 : 4;  /* bit[28-31]: IPC2CCPU_0 count number */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta16_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta16_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta17_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta17_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta18_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta18_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta19_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta19_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta20_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta20_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta21_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta21_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta22_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta22_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta23_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT2_sc_int_count_sta23_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_UNION
 结构说明  : MDMSC_INT_COUNT_STAT3 寄存器结构定义。地址偏移量:0x0264，初值:0x00000000，宽度:32
 寄存器说明: 中断计数状态寄存器3。用于软件调试。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta24 : 4;  /* bit[0-3]  : MEDMAC1 count number */
        unsigned int  sc_int_count_sta25 : 4;  /* bit[4-7]  : SOCP_intr[1] count number */
        unsigned int  sc_int_count_sta26 : 4;  /* bit[8-11] : SOCP_intr[0] count number  */
        unsigned int  sc_int_count_sta27 : 4;  /* bit[12-15]: GU Cipher1下行中断(arm_int_dl) count number  */
        unsigned int  sc_int_count_sta28 : 4;  /* bit[16-19]: GU Cipher1上行中断(arm_int_ul) count number  */
        unsigned int  sc_int_count_sta29 : 4;  /* bit[20-23]: GBBP2中断3 GSM2 DRX中断(g2_int_bbp_to_dsp_32k) count number  */
        unsigned int  sc_int_count_sta30 : 4;  /* bit[24-27]: GBBP2中断2 GSM2非DRX中断1(g2_int_bbp_to_dsp) count number  */
        unsigned int  sc_int_count_sta31 : 4;  /* bit[28-31]: GBBP2中断1 GSM2预留（g2_int_bbp_to_cpu_32k） count number  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta24_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta24_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta25_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta25_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta26_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta26_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta27_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta27_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta28_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta28_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta29_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta29_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta30_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta30_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta31_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT3_sc_int_count_sta31_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_UNION
 结构说明  : MDMSC_INT_COUNT_STAT4 寄存器结构定义。地址偏移量:0x0268，初值:0x00000000，宽度:32
 寄存器说明: 中断计数状态寄存器4。用于软件调试。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta32 : 4;  /* bit[0-3]  : GBBP2中断0 GSM2非DRX中断0(g2_int_bbp_to_cpu) */
        unsigned int  sc_int_count_sta33 : 4;  /* bit[4-7]  : CTU_G2toARM中断 BBP COMMON CTU_GBBP2 to ARM中断 */
        unsigned int  sc_int_count_sta34 : 4;  /* bit[8-11] : IPC2CCPU_2 IPC输出给CCPU的核间中断1（ipc_cpu_intr0[6]） */
        unsigned int  sc_int_count_sta35 : 4;  /* bit[12-15]: 安全IPC输出给CCPU的资源锁中断（s_ipc_cpu_intr1[1]） */
        unsigned int  sc_int_count_sta36 : 4;  /* bit[16-19]: 安全IPC输出给CCPU的核间中断（s_ipc_cpu_intr0[1]） */
        unsigned int  sc_int_count_sta37 : 4;  /* bit[20-23]: TDS模时：表示tds hsupa模块完成中断tds_hsupa_intr；C模时：表示CDMA1x或CDMA EVDO睡眠/唤醒中断(32K)cbbp_intr01.
                                                              (tcbbp_intr01) */
        unsigned int  sc_int_count_sta38 : 4;  /* bit[24-27]: TDS模时：表示tds harq模块完成中断tds_harq_intr；C模时：表示CDMA1x或CDMA EVDO时钟切换中断(imi时钟)cbbp_intr02.
                                                              (tcbbp_intr02) */
        unsigned int  sc_int_count_sta39 : 4;  /* bit[28-31]: TDS模时：表示tds turbo模块完成中断tds_turbo_intr；C模时：表示CDMA1x或CDMA EVDO多径搜索/小区测量中断cbbp_intr03.
                                                              (tcbbp_intr03) */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta32_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta32_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta33_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta33_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta34_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta34_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta35_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta35_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta36_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta36_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta37_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta37_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta38_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta38_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta39_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT4_sc_int_count_sta39_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_UNION
 结构说明  : MDMSC_INT_COUNT_STAT5 寄存器结构定义。地址偏移量:0x026C，初值:0x00000000，宽度:32
 寄存器说明: 中断计数状态寄存器5。用于软件调试。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_int_count_sta40 : 4;  /* bit[0-3]  : TDS模时：表示tds viterbi模块完成中断tds_viterbi_intr；C模时：表示CDMA1x或CDMA EVDO定时中断cbbp_intr04
                                                              （tcbbp_intr04） */
        unsigned int  sc_int_count_sta41 : 4;  /* bit[4-7]  : TDS模时：表示tds前端模块中断tds_fpu_intr；C模时：表示CDMA1x或CDMA EVDO编码/译码中断cbbp_intr05.
                                                              （tcbbp_intr05） */
        unsigned int  sc_int_count_sta42 : 4;  /* bit[8-11] : TDS模时：表示tds射频前端中断tds_rfc_intr；C模时：表示CDMA1x或CDMA EVDO射频上报/数据搬移中断cbbp_intr06.
                                                              (tcbbp_intr06) */
        unsigned int  sc_int_count_sta43 : 4;  /* bit[12-15]: 保留。 */
        unsigned int  sc_int_count_sta44 : 4;  /* bit[16-19]: 保留。 */
        unsigned int  sc_int_count_sta45 : 4;  /* bit[20-23]: 保留。 */
        unsigned int  sc_int_count_sta46 : 4;  /* bit[24-27]: 保留。 */
        unsigned int  sc_int_count_sta47 : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta40_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta40_END    (3)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta41_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta41_END    (7)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta42_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta42_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta43_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta43_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta44_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta44_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta45_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta45_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta46_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta46_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta47_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_INT_COUNT_STAT5_sc_int_count_sta47_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_UNION
 结构说明  : MDMSC_BBPCLK_SEL_CTRL 寄存器结构定义。地址偏移量:0x0270，初值:0x00000000，宽度:32
 寄存器说明: BBP 单双TCXO时钟选择控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbp_clk_sel : 6;  /* bit[0-5] : BBP 时钟源选择信号
                                                      bbp_clk_sel[0]控制BBP主时钟的选择
                                                      bbp_clk_sel[1]控制BBP ABB时钟的选择
                                                      bbp_clk_sel[2]控制G1时钟的选择
                                                      bbp_clk_sel[3]控制G2时钟的选择
                                                      bbp_clk_sel[4]控制tcxo ch0时钟的选择
                                                      bbp_clk_sel[5]控制tcxo ch1时钟的选择 */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_bbp_clk_sel_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBPCLK_SEL_CTRL_bbp_clk_sel_END    (5)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_UNION
 结构说明  : MDMSC_BBE16_DEBUG_RSTCTRL 寄存器结构定义。地址偏移量:0x0274，初值:0x00000001，宽度:32
 寄存器说明: BBE16 debug reset控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_debug_reset : 1;  /* bit[0]   : bbe16 APB debug复位值，默认为1'b1 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_bbe16_debug_reset_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEBUG_RSTCTRL_bbe16_debug_reset_END    (0)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_UNION
 结构说明  : MDMSC_TIMER_EN0 寄存器结构定义。地址偏移量:0x02A0，初值:0x00000000，宽度:32
 寄存器说明: timer使能寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timer_en0_ccpu_dualtimer0_en0     : 2;  /* bit[0-1]  : [1:0] ccpu dualtimer0 的en0，对应ccpu timer0
                                                                             时钟使能控制含义：
                                                                             x0：系统模式处于Normal时计数频率为19.2MHz，系统模式进入SLOW和Sleep后，计数频率为系统时钟；
                                                                             x1：参考时钟选择32KHz。 */
        unsigned int  timer_en0_ccpu_dualtimer0_en1     : 2;  /* bit[2-3]  : [3:2] ccpu dualtimer0 的en1 ，对应ccpu timer1 */
        unsigned int  timer_en0_ccpu_dualtimer1_en0     : 2;  /* bit[4-5]  : [5:4] ccpu dualtimer1 的en0，对应ccpu timer2 */
        unsigned int  timer_en0_ccpu_dualtimer1_en1     : 2;  /* bit[6-7]  : [7:6] ccpu dualtimer1 的en1 ，对应ccpu timer3 */
        unsigned int  timer_en0_ccpu_dualtimer2_en0     : 2;  /* bit[8-9]  : [9:8] ccpu dualtimer2 的en0，对应ccpu timer4 */
        unsigned int  timer_en0_ccpu_dualtimer2_en1     : 2;  /* bit[10-11]: [11:10] ccpu dualtimer2 的en1，对应ccpu timer5 */
        unsigned int  timer_en0_ccpu_dualtimer3_en0     : 2;  /* bit[12-13]: [13:12] ccpu dualtimer3 的en0，对应ccpu timer6 */
        unsigned int  timer_en0_ccpu_dualtimer3_en1     : 2;  /* bit[14-15]: [15:14] ccpu dualtimer3 的en1，对应ccpu timer7  */
        unsigned int  timer_en0_msk_ccpu_dualtimer0_en0 : 2;  /* bit[16-17]: [17:16] ccpu timer0 */
        unsigned int  timer_en0_msk_ccpu_dualtimer0_en1 : 2;  /* bit[18-19]: [19:18] ccpu timer1 */
        unsigned int  timer_en0_msk_ccpu_dualtimer1_en0 : 2;  /* bit[20-21]: [21:20] ccpu timer2 */
        unsigned int  timer_en0_msk_ccpu_dualtimer1_en1 : 2;  /* bit[22-23]: [23:22] ccpu timer3 */
        unsigned int  timer_en0_msk_ccpu_dualtimer2_en0 : 2;  /* bit[24-25]: [25:24] ccpu timer4 */
        unsigned int  timer_en0_msk_ccpu_dualtimer2_en1 : 2;  /* bit[26-27]: [27:26] ccpu timer5 */
        unsigned int  timer_en0_msk_ccpu_dualtimer3_en0 : 2;  /* bit[28-29]: [29:28] ccpu timer6 */
        unsigned int  timer_en0_msk_ccpu_dualtimer3_en1 : 2;  /* bit[30-31]: [31:16]：每一bit顺序对应bit15～bit0，仅当bit31～16的bit写1的同时，配置bit15～0才能生效；当bit31～16的bit写0时，配置bit15～0保持不变；
                                                                             [30:30] ccpu timer7 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer0_en0_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer0_en0_END        (1)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer0_en1_START      (2)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer0_en1_END        (3)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer1_en0_START      (4)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer1_en0_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer1_en1_START      (6)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer1_en1_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer2_en0_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer2_en0_END        (9)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer2_en1_START      (10)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer2_en1_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer3_en0_START      (12)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer3_en0_END        (13)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer3_en1_START      (14)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_ccpu_dualtimer3_en1_END        (15)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer0_en0_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer0_en0_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer0_en1_START  (18)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer0_en1_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer1_en0_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer1_en0_END    (21)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer1_en1_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer1_en1_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer2_en0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer2_en0_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer2_en1_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer2_en1_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer3_en0_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer3_en0_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer3_en1_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN0_timer_en0_msk_ccpu_dualtimer3_en1_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_UNION
 结构说明  : MDMSC_TIMER_EN1 寄存器结构定义。地址偏移量:0x02A4，初值:0x00000000，宽度:32
 寄存器说明: timer使能寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timer_en1_ccpu_dualtimer4_en0     : 2;  /* bit[0-1]  : [1:0] ccpu dualtimer0 的en0，对应ccpu timer0
                                                                             时钟使能控制含义：
                                                                             x0：系统模式处于Normal时计数频率为19.2MHz，系统模式进入SLOW和Sleep后，计数频率为系统时钟；
                                                                             x1：参考时钟选择32KHz。 */
        unsigned int  timer_en1_ccpu_dualtimer4_en1     : 2;  /* bit[2-3]  : [3:2] ccpu dualtimer4 的en1 ，对应ccpu timer9 */
        unsigned int  timer_en1_ccpu_dualtimer5_en0     : 2;  /* bit[4-5]  : [5:4] ccpu dualtimer5 的en0，对应ccpu timer10 */
        unsigned int  timer_en1_ccpu_dualtimer5_en1     : 2;  /* bit[6-7]  : [7:6] ccpu dualtimer5 的en1 ，对应ccpu timer11 */
        unsigned int  timer_en1_ccpu_dualtimer6_en0     : 2;  /* bit[8-9]  : [9:8] ccpu dualtimer6 的en0，对应ccpu timer12 */
        unsigned int  timer_en1_ccpu_dualtimer6_en1     : 2;  /* bit[10-11]: [11:10] ccpu dualtimer6 的en1，对应ccpu timer13 */
        unsigned int  timer_en1_ccpu_dualtimer7_en0     : 2;  /* bit[12-13]: [13:12] ccpu dualtimer7 的en0，对应ccpu timer14 */
        unsigned int  timer_en1_ccpu_dualtimer7_en1     : 2;  /* bit[14-15]: [15:14] ccpu dualtimer7 的en1，对应ccpu timer15 */
        unsigned int  timer_en1_msk_ccpu_dualtimer4_en0 : 2;  /* bit[16-17]: [17:16] ccpu timer8 */
        unsigned int  timer_en1_msk_ccpu_dualtimer4_en1 : 2;  /* bit[18-19]: [19:18] ccpu timer9 */
        unsigned int  timer_en1_msk_ccpu_dualtimer5_en0 : 2;  /* bit[20-21]: [21:20] ccpu timer10 */
        unsigned int  timer_en1_msk_ccpu_dualtimer5_en1 : 2;  /* bit[22-23]: [23:22] ccpu timer11 */
        unsigned int  timer_en1_msk_ccpu_dualtimer6_en0 : 2;  /* bit[24-25]: [25:24] ccpu timer12 */
        unsigned int  timer_en1_msk_ccpu_dualtimer6_en1 : 2;  /* bit[26-27]: [27:26] ccpu timer13 */
        unsigned int  timer_en1_msk_ccpu_dualtimer7_en0 : 2;  /* bit[28-29]: [29:28] ccpu timer14 */
        unsigned int  timer_en1_msk_ccpu_dualtimer7_en1 : 2;  /* bit[30-31]: [31:16]：每一bit顺序对应bit15～bit0，仅当bit31～16的bit写1的同时，配置bit15～0才能生效；当bit31～16的bit写0时，配置bit15～0保持不变；
                                                                             [30:30] ccpu timer15 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer4_en0_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer4_en0_END        (1)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer4_en1_START      (2)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer4_en1_END        (3)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer5_en0_START      (4)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer5_en0_END        (5)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer5_en1_START      (6)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer5_en1_END        (7)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer6_en0_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer6_en0_END        (9)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer6_en1_START      (10)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer6_en1_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer7_en0_START      (12)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer7_en0_END        (13)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer7_en1_START      (14)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_ccpu_dualtimer7_en1_END        (15)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer4_en0_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer4_en0_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer4_en1_START  (18)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer4_en1_END    (19)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer5_en0_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer5_en0_END    (21)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer5_en1_START  (22)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer5_en1_END    (23)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer6_en0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer6_en0_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer6_en1_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer6_en1_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer7_en0_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer7_en0_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer7_en1_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN1_timer_en1_msk_ccpu_dualtimer7_en1_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_UNION
 结构说明  : MDMSC_TIMER_EN2 寄存器结构定义。地址偏移量:0x02A8，初值:0x00000000，宽度:32
 寄存器说明: timer使能寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                        : 8;  /* bit[0-7]  : reserved */
        unsigned int  timer_en2_ccpu_dualtimer8_en0     : 2;  /* bit[8-9]  : [9:8] ccpu dualtimer8 的en0，对应ccpu timer16 */
        unsigned int  timer_en2_ccpu_dualtimer8_en1     : 2;  /* bit[10-11]: [11:10] ccpu dualtimer8 的en1，对应ccpu timer17 */
        unsigned int  timer_en2_ccpu_dualtimer9_en0     : 2;  /* bit[12-13]: [13:12] ccpu dualtimer9 的en0，对应ccpu timer18 */
        unsigned int  timer_en2_ccpu_dualtimer9_en1     : 2;  /* bit[14-15]: [1:0] ccpu dualtimer0 的en0，对应ccpu timer0
                                                                             时钟使能控制含义：
                                                                             x0：系统模式处于Normal时计数频率为19.2MHz，系统模式进入SLOW和Sleep后，计数频率为系统时钟；
                                                                             x1：参考时钟选择32KHz。 */
        unsigned int  reserved_1                        : 8;  /* bit[16-23]: reserved */
        unsigned int  timer_en2_msk_ccpu_dualtimer8_en0 : 2;  /* bit[24-25]: [25:24] ccpu timer16 */
        unsigned int  timer_en2_msk_ccpu_dualtimer8_en1 : 2;  /* bit[26-27]: [27:26] ccpu timer17 */
        unsigned int  timer_en2_msk_ccpu_dualtimer9_en0 : 2;  /* bit[28-29]: [29:28] ccpu timer18 */
        unsigned int  timer_en2_msk_ccpu_dualtimer9_en1 : 2;  /* bit[30-31]: [31:16]：每一bit顺序对应bit15～bit0，仅当bit31～16的bit写1的同时，配置bit15～0才能生效；当bit31～16的bit写0时，配置bit15～0保持不变；
                                                                             [30:30] ccpu timer19 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer8_en0_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer8_en0_END        (9)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer8_en1_START      (10)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer8_en1_END        (11)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer9_en0_START      (12)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer9_en0_END        (13)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer9_en1_START      (14)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_ccpu_dualtimer9_en1_END        (15)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer8_en0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer8_en0_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer8_en1_START  (26)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer8_en1_END    (27)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer9_en0_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer9_en0_END    (29)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer9_en1_START  (30)
#define SOC_MODEM_SCTRL_MDMSC_TIMER_EN2_timer_en2_msk_ccpu_dualtimer9_en1_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_UNION
 结构说明  : MDMSC_CCPU_DEFCTRL4 寄存器结构定义。地址偏移量:0x02AC，初值:0x00000000，宽度:32
 寄存器说明: Modem子系统自定义CCPU remap冗错上报控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_error_clr : 1;  /* bit[0]   : REMAP 错误信号的清零，配置1清除aw/arremap_error_flag信号的，脉冲信号 */
        unsigned int  reserved        : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_remap_error_clr_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL4_remap_error_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_UNION
 结构说明  : MDMSC_CCPU_DEFCTRL_RPT 寄存器结构定义。地址偏移量:0x02B0，初值:0x00000000，宽度:32
 寄存器说明: Modem子系统自定义CCPU remap状态上报
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arremap_error_flag : 1;  /* bit[0]   : 读操作REMAP的低20bit是否映射到reserved空间,0表示没有，1表示有（则为错误映射） */
        unsigned int  awremap_error_flag : 1;  /* bit[1]   : 写操作REMAP的低20bit是否映射到reserved空间,0表示没有，1表示有（则为错误映射） */
        unsigned int  reserved           : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_arremap_error_flag_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_arremap_error_flag_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_awremap_error_flag_START  (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL_RPT_awremap_error_flag_END    (1)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_UNION
 结构说明  : MDMSC_CCPU_DEFCTRL3 寄存器结构定义。地址偏移量:0x02B4，初值:0xE0000FFB，宽度:32
 寄存器说明: Modem子系统自定义CCPU功 remap SRAM地址配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sram_addr_cfg_value : 12; /* bit[0-11] : BBE16 SRAM的访问地址空间的高12bit */
        unsigned int  sram_addr_boundary  : 20; /* bit[12-31]: BBE16 SRAM的地址边界，默认值为0xE0000（896K） */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_sram_addr_cfg_value_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_sram_addr_cfg_value_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_sram_addr_boundary_START   (12)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL3_sram_addr_boundary_END     (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_UNION
 结构说明  : MDMSC_CCPU_DEFCTRL2 寄存器结构定义。地址偏移量:0x02B8，初值:0x00000000，宽度:32
 寄存器说明: Modem子系统自定义CCPU功能remap使能配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_remap_en : 1;  /* bit[0]   : ccpu remap使能信号，高有效 */
        unsigned int  reserved      : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_ccpu_remap_en_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL2_ccpu_remap_en_END    (0)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_UNION
 结构说明  : MDMSC_CCPU_DEFCTRL0 寄存器结构定义。地址偏移量:0x02BC，初值:0x00000000，宽度:32
 寄存器说明: Modem子系统自定义CCPU功能控制remap 基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_remap_cfg_value : 12; /* bit[0-11] : ccpu remap高12bit基址,先配置基址再配置ccpu_remap_en使能信号生效 */
        unsigned int  reserved             : 20; /* bit[12-31]: reserved */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_ccpu_remap_cfg_value_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL0_ccpu_remap_cfg_value_END    (11)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_UNION
 结构说明  : MDMSC_CCPU_DEFCTRL1 寄存器结构定义。地址偏移量:0x02C0，初值:0x00000000，宽度:32
 寄存器说明: Modem子系统自定义CCPU功能控制，debug相关
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cs_ccpu_dbg_rst_ctrl : 1;  /* bit[0]   : CCPU Coresight Debug复位请求信号的控制。
                                                               0，表示不允许Coresight复位请求；
                                                               1，表示允许Coresight复位请求； */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_cs_ccpu_dbg_rst_ctrl_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_DEFCTRL1_cs_ccpu_dbg_rst_ctrl_END    (0)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_UNION
 结构说明  : MDMSC_ALWAYSON_SYS_CTRL 寄存器结构定义。地址偏移量:0x02C4，初值:0x000000E4，宽度:32
 寄存器说明: ALWAYSON和外设系统控制寄存器，功能包含SCI控制、NOC Timeout控制、TCXO AFC高阻控制、modem给sysnoc门控的投票
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gbbp_gps_restrain_sel                  : 1;  /* bit[0]    : G模GPS抑制，GBBP输出默认高有效，根据外部器件进行配置
                                                                                  0：器件抑制高有效，对GBBP输出抑制信号进行直通
                                                                                  1：器件抑制低有效，对GBBP输出抑制信号进行取反 */
        unsigned int  gbbp_led_restrain_sel                  : 1;  /* bit[1]    : G模闪光灯抑制，GBBP输出默认高有效，根据外部器件进行配置
                                                                                  0：器件抑制高有效，对GBBP输出抑制信号进行直通
                                                                                  1：器件抑制低有效，对GBBP输出抑制信号进行取反 */
        unsigned int  clk_en_sysnoc_mdm                      : 1;  /* bit[2]    : modem输出给sysnoc用于时钟门控
                                                                                  0：modem子系统投票sysnoc时钟门控
                                                                                  1：modem子系统投票sysnoc时钟有效 */
        unsigned int  reserved_0                             : 2;  /* bit[3-4]  : reserved */
        unsigned int  modemnoc_timeout_en                    : 1;  /* bit[5]    : modemnoc_timeout_en
                                                                                  0:disable timeout
                                                                                  1:enable timeout */
        unsigned int  tcxo0_afc_high_z                       : 1;  /* bit[6]    : [6]：TCXO_0 AFC的输出高阻控制。
                                                                                  0：输出使能；
                                                                                  1：输出高阻。 */
        unsigned int  tcxo1_afc_high_z                       : 1;  /* bit[7]    : [7]：TCXO_1 AFC的输出高阻控制。
                                                                                  0：输出使能；
                                                                                  1：输出高阻。 */
        unsigned int  alwayson_and_periph_sys_ctrl0_sci0     : 1;  /* bit[8]    : SCI0输出buffer控制。默认0
                                                                                  0：open-drain；
                                                                                  1：offchip buffer。 */
        unsigned int  alwayson_and_periph_sys_ctrl0_sci1     : 1;  /* bit[9]    : SCI1输出buffer控制。默认0
                                                                                  0：open-drain；
                                                                                  1：offchip buffer。 */
        unsigned int  reserved_1                             : 6;  /* bit[10-15]: reserved */
        unsigned int  gbbp_gps_restrain_sel_msk              : 1;  /* bit[16]   : G模GPS抑制，GBBP输出默认高有效，根据外部器件进行配置 */
        unsigned int  gbbp_led_restrain_sel_msk              : 1;  /* bit[17]   : G模闪光灯抑制，GBBP输出默认高有效，根据外部器件进行配置 */
        unsigned int  clk_en_sysnoc_mdm_msk                  : 1;  /* bit[18]   : modem输出给sysnoc用于时钟门控MSK配置位 */
        unsigned int  reserved_2                             : 2;  /* bit[19-20]: reserved */
        unsigned int  modemnoc_timeout_en_msk                : 1;  /* bit[21]   : modemnoc_timeout_en
                                                                                  0:disable timeout
                                                                                  1:enable timeout */
        unsigned int  tcxo0_afc_high_z_msk                   : 1;  /* bit[22]   : TCXO_0 AFC的输出高阻控制。 */
        unsigned int  tcxo1_afc_high_z_msk                   : 1;  /* bit[23]   : TCXO_1 AFC的输出高阻控制。 */
        unsigned int  alwayson_and_periph_sys_ctrl0_msk_sci0 : 1;  /* bit[24]   : SCI0输出buffer控制。默认0 */
        unsigned int  alwayson_and_periph_sys_ctrl0_msk_sci1 : 1;  /* bit[25]   : SCI1输出buffer控制。默认0 */
        unsigned int  reserved_3                             : 6;  /* bit[26-31]: [31:16]：每一bit顺序对应bit15～bit0，仅当bit31～16的bit写1的同时，配置bit15～0才能生效；当bit31～16的bit写0时，配置bit15～0保持不变；
                                                                                  [31]保留  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_gps_restrain_sel_START                   (0)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_gps_restrain_sel_END                     (0)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_led_restrain_sel_START                   (1)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_led_restrain_sel_END                     (1)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_clk_en_sysnoc_mdm_START                       (2)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_clk_en_sysnoc_mdm_END                         (2)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_modemnoc_timeout_en_START                     (5)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_modemnoc_timeout_en_END                       (5)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo0_afc_high_z_START                        (6)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo0_afc_high_z_END                          (6)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo1_afc_high_z_START                        (7)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo1_afc_high_z_END                          (7)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_sci0_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_sci0_END        (8)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_sci1_START      (9)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_sci1_END        (9)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_gps_restrain_sel_msk_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_gps_restrain_sel_msk_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_led_restrain_sel_msk_START               (17)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_gbbp_led_restrain_sel_msk_END                 (17)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_clk_en_sysnoc_mdm_msk_START                   (18)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_clk_en_sysnoc_mdm_msk_END                     (18)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_modemnoc_timeout_en_msk_START                 (21)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_modemnoc_timeout_en_msk_END                   (21)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo0_afc_high_z_msk_START                    (22)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo0_afc_high_z_msk_END                      (22)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo1_afc_high_z_msk_START                    (23)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_tcxo1_afc_high_z_msk_END                      (23)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_msk_sci0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_msk_sci0_END    (24)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_msk_sci1_START  (25)
#define SOC_MODEM_SCTRL_MDMSC_ALWAYSON_SYS_CTRL_alwayson_and_periph_sys_ctrl0_msk_sci1_END    (25)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UNION
 结构说明  : MDMSC_PERIPH_CTRL 寄存器结构定义。地址偏移量:0x02C8，初值:0x000004D2，宽度:32
 寄存器说明: 外设控制寄存器。功能包含UPACC、CICOM、CICOM模式选择、DMAC
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gucicom0sel_mode                  : 1;  /* bit[0] : gucicom0sel_mode
                                                                          0：WCDMA加解密模式
                                                                          1：GSM加解密模式 */
        unsigned int  gucicom0soft_auto_clk_gate_en     : 1;  /* bit[1] : gucicom0auto_clk_gate_en
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  gucicom0soft_gate_clk_en          : 1;  /* bit[2] : gucicom0soft_gate_clk_en
                                                                          1'b0:软件门控不使能
                                                                          1'b1:软件门控使能 */
        unsigned int  reserved_0                        : 1;  /* bit[3] : gucicom1sel_mode(保留)
                                                                          0：WCDMA加解密模式
                                                                          1：GSM加解密模式 */
        unsigned int  reserved_1                        : 1;  /* bit[4] : gucicom1auto_clk_gate_en(保留)
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  reserved_2                        : 1;  /* bit[5] : gucicom11soft_gate_clk_en(保留)
                                                                          1'b0:软件门控不使能
                                                                          1'b1:软件门控使能 */
        unsigned int  mdmdmac_auto_clken0_sel           : 1;  /* bit[6] : mdmdmac_auto_clken0_selPERIPH_MISC
                                                                          0:autoclkgatedisable
                                                                          1:autoclkgageenable */
        unsigned int  mdmdmac_auto_clken1_sel           : 1;  /* bit[7] : mdmdmac_auto_clken1_selPERIPH_MISC
                                                                          0:autoclkgatedisable
                                                                          1:autoclkgageenable */
        unsigned int  dw_x2x_auto_clk_gate_en           : 1;  /* bit[8] : ccpu分区的x2x桥的自动门控使能
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  dw_axi_auto_clk_gate_en           : 1;  /* bit[9] : ccpu分区的axi总线的自动门控使能
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  UPACC_auto_clk_gate_en            : 1;  /* bit[10]: (UPACC)auto_clk_gate_en
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  upacc_soft_gate_clk_en            : 1;  /* bit[11]: (UPACC)soft_gate_clk_en
                                                                          1'b0:软件门控不使能
                                                                          1'b1:软件门控使能 */
        unsigned int  bbe16_axi_auto_clk_gate_en        : 1;  /* bit[12]: BBE16分区的axi总线的自动门控使能
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  ddr_x2x_auto_clk_gate_en          : 1;  /* bit[13]: CCPU到DDR的X2X桥的自动门控使能
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  reserved_3                        : 1;  /* bit[14]: reserved */
        unsigned int  reserved_4                        : 1;  /* bit[15]: reserved */
        unsigned int  gucicom0sel_mode_msk              : 1;  /* bit[16]: gucicom0sel_mode */
        unsigned int  gucicom0soft_auto_clk_gate_en_msk : 1;  /* bit[17]: gucicom0auto_clk_gate_en */
        unsigned int  gucicom0soft_gate_clk_en_msk      : 1;  /* bit[18]: gucicom0soft_gate_clk_en */
        unsigned int  reserved_5                        : 1;  /* bit[19]: gucicom1sel_mode(保留) */
        unsigned int  reserved_6                        : 1;  /* bit[20]: gucicom1auto_clk_gate_en(保留) */
        unsigned int  reserved_7                        : 1;  /* bit[21]: gucicom1soft_gate_clk_en(保留) */
        unsigned int  mdmdmac_auto_clken0_sel_msk       : 1;  /* bit[22]: mdmdmac_auto_clken0_selPERIPH_MISC */
        unsigned int  mdmdmac_auto_clken1_sel_msk       : 1;  /* bit[23]: mdmdmac_auto_clken1_selPERIPH_MISC */
        unsigned int  dw_x2x_auto_clk_gate_en_msk       : 1;  /* bit[24]: ccpu分区的x2x桥的自动门控使能
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  dw_axi_auto_clk_gate_en_msk       : 1;  /* bit[25]: ccpu分区的axi总线的自动门控使能
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  UPACC_auto_clk_gate_en_msk        : 1;  /* bit[26]: (UPACC)auto_clk_gate_en */
        unsigned int  upacc_soft_gate_clk_en_msk        : 1;  /* bit[27]: (UPACC)soft_gate_clk_en */
        unsigned int  bbe16_axi_auto_clk_gate_en_msk    : 1;  /* bit[28]: BBE16分区的axi总线的自动门控使能
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  ddr_x2x_auto_clk_gate_en_msk      : 1;  /* bit[29]: ccpu分区的axi总线的自动门控使能
                                                                          1'b0:硬件自动门控不使能
                                                                          1'b1:硬件自动门控使能 */
        unsigned int  reserved_8                        : 1;  /* bit[30]: reserved */
        unsigned int  reserved_9                        : 1;  /* bit[31]: [31:16]：每一bit顺序对应bit15～bit0，仅当bit31～16的bit写1的同时，配置bit15～0才能生效；当bit31～16的bit写0时，配置bit15～0保持不变；
                                                                          [31:28]：保留。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0sel_mode_START                   (0)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0sel_mode_END                     (0)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_auto_clk_gate_en_START      (1)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_auto_clk_gate_en_END        (1)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_gate_clk_en_START           (2)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_gate_clk_en_END             (2)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken0_sel_START            (6)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken0_sel_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken1_sel_START            (7)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken1_sel_END              (7)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_x2x_auto_clk_gate_en_START            (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_x2x_auto_clk_gate_en_END              (8)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_axi_auto_clk_gate_en_START            (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_axi_auto_clk_gate_en_END              (9)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UPACC_auto_clk_gate_en_START             (10)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UPACC_auto_clk_gate_en_END               (10)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_upacc_soft_gate_clk_en_START             (11)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_upacc_soft_gate_clk_en_END               (11)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_bbe16_axi_auto_clk_gate_en_START         (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_bbe16_axi_auto_clk_gate_en_END           (12)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ddr_x2x_auto_clk_gate_en_START           (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ddr_x2x_auto_clk_gate_en_END             (13)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0sel_mode_msk_START               (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0sel_mode_msk_END                 (16)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_auto_clk_gate_en_msk_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_auto_clk_gate_en_msk_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_gate_clk_en_msk_START       (18)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_gucicom0soft_gate_clk_en_msk_END         (18)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken0_sel_msk_START        (22)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken0_sel_msk_END          (22)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken1_sel_msk_START        (23)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_mdmdmac_auto_clken1_sel_msk_END          (23)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_x2x_auto_clk_gate_en_msk_START        (24)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_x2x_auto_clk_gate_en_msk_END          (24)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_axi_auto_clk_gate_en_msk_START        (25)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_dw_axi_auto_clk_gate_en_msk_END          (25)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UPACC_auto_clk_gate_en_msk_START         (26)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_UPACC_auto_clk_gate_en_msk_END           (26)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_upacc_soft_gate_clk_en_msk_START         (27)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_upacc_soft_gate_clk_en_msk_END           (27)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_bbe16_axi_auto_clk_gate_en_msk_START     (28)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_bbe16_axi_auto_clk_gate_en_msk_END       (28)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ddr_x2x_auto_clk_gate_en_msk_START       (29)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_CTRL_ddr_x2x_auto_clk_gate_en_msk_END         (29)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_UNION
 结构说明  : MDMSC_PERIPH_STAT 寄存器结构定义。地址偏移量:0x02CC，初值:0x00000001，宽度:32
 寄存器说明: 外设状态寄存器，功能包含CICOM状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gucipher0_clk_state : 1;  /* bit[0]   : gucipher0_clk_state时钟门控指示
                                                              0：时钟关闭；
                                                              1：时钟打开。 */
        unsigned int  reserved_0          : 1;  /* bit[1]   : gucipher1_clk_state时钟门控指示(保留)
                                                              0：时钟关闭；
                                                              1：时钟打开。 */
        unsigned int  reserved_1          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_gucipher0_clk_state_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PERIPH_STAT_gucipher0_clk_state_END    (0)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_UNION
 结构说明  : MDMSC_MNOC_QOSCTRL0 寄存器结构定义。地址偏移量:0x02D0，初值:0x00000000，宽度:32
 寄存器说明: MDM_NOC总线上Master设备的优先级控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_edmac   : 3;  /* bit[0-2]  : MDM NOC Master设备EDMAC的总线PRESS优先级设置，可配置值0～7 */
        unsigned int  reserved_0                     : 1;  /* bit[3]    : 保留 */
        unsigned int  modem_noc_master_hurry_edmac   : 3;  /* bit[4-6]  : MDM NOC Master设备EDMAC的总线HURRY优先级设置，可配置值0～7 */
        unsigned int  reserved_1                     : 1;  /* bit[7]    : 保留 */
        unsigned int  modem_noc_master_awqos_edmac   : 3;  /* bit[8-10] : MDM NOC Master设备EDMAC的总线AWQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_2                     : 1;  /* bit[11]   : 保留 */
        unsigned int  modem_noc_master_arqos_edmac   : 3;  /* bit[12-14]: MDM NOC Master设备EDMAC的总线ARQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_3                     : 1;  /* bit[15]   : 保留 */
        unsigned int  modem_noc_master_press_lcipher : 3;  /* bit[16-18]: MDM NOC Master设备LCIPHER的总线PRESS优先级设置，可配置值0～7 */
        unsigned int  reserved_4                     : 1;  /* bit[19]   : 保留 */
        unsigned int  modem_noc_master_hurry_lcipher : 3;  /* bit[20-22]: MDM NOC Master设备LCIPHER的总线HURRY优先级设置，可配置值0～7 */
        unsigned int  reserved_5                     : 1;  /* bit[23]   : 保留 */
        unsigned int  modem_noc_master_awqos_lcipher : 3;  /* bit[24-26]: MDM NOC Master设备LCIPHER的总线AWQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_6                     : 1;  /* bit[27]   : 保留 */
        unsigned int  modem_noc_master_arqos_lcipher : 3;  /* bit[28-30]: MDM NOC Master设备LCIPHER的总线ARQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_7                     : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_press_edmac_START    (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_press_edmac_END      (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_hurry_edmac_START    (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_hurry_edmac_END      (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_awqos_edmac_START    (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_awqos_edmac_END      (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_arqos_edmac_START    (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_arqos_edmac_END      (14)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_press_lcipher_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_press_lcipher_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_hurry_lcipher_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_hurry_lcipher_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_awqos_lcipher_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_awqos_lcipher_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_arqos_lcipher_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL0_modem_noc_master_arqos_lcipher_END    (30)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_UNION
 结构说明  : MDMSC_MNOC_QOSCTRL1 寄存器结构定义。地址偏移量:0x02D4，初值:0x00000000，宽度:32
 寄存器说明: MDM_NOC总线上Master设备的优先级控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_upacc    : 3;  /* bit[0-2]  : MDM NOC Master设备UPACC的总线PRESS优先级设置，可配置值0～7 */
        unsigned int  reserved_0                      : 1;  /* bit[3]    : 保留 */
        unsigned int  modem_noc_master_hurry_upacc    : 3;  /* bit[4-6]  : MDM NOC Master设备UPACC的总线HURRY优先级设置，可配置值0～7 */
        unsigned int  reserved_1                      : 1;  /* bit[7]    : 保留 */
        unsigned int  modem_noc_master_awqos_upacc    : 3;  /* bit[8-10] : MDM NOC Master设备UPACC的总线AWQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_2                      : 1;  /* bit[11]   : 保留 */
        unsigned int  modem_noc_master_arqos_upacc    : 3;  /* bit[12-14]: MDM NOC Master设备UPACC的总线ARQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_3                      : 1;  /* bit[15]   : 保留 */
        unsigned int  modem_noc_master_press_gucipher : 3;  /* bit[16-18]: MDM NOC Master设备GUCIPHER的总线PRESS优先级设置，可配置值0～7 */
        unsigned int  reserved_4                      : 1;  /* bit[19]   : 保留 */
        unsigned int  modem_noc_master_hurry_gucipher : 3;  /* bit[20-22]: MDM NOC Master设备GUCIPHER的总线HURRY优先级设置，可配置值0～7 */
        unsigned int  reserved_5                      : 1;  /* bit[23]   : 保留 */
        unsigned int  modem_noc_master_awqos_gucipher : 3;  /* bit[24-26]: MDM NOC Master设备GUCIPHER的总线AWQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_6                      : 1;  /* bit[27]   : 保留 */
        unsigned int  modem_noc_master_arqos_gucipher : 3;  /* bit[28-30]: MDM NOC Master设备GUCIPHER的总线ARQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_7                      : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_press_upacc_START     (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_press_upacc_END       (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_hurry_upacc_START     (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_hurry_upacc_END       (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_awqos_upacc_START     (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_awqos_upacc_END       (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_arqos_upacc_START     (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_arqos_upacc_END       (14)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_press_gucipher_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_press_gucipher_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_hurry_gucipher_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_hurry_gucipher_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_awqos_gucipher_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_awqos_gucipher_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_arqos_gucipher_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL1_modem_noc_master_arqos_gucipher_END    (30)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_UNION
 结构说明  : MDMSC_MNOC_QOSCTRL2 寄存器结构定义。地址偏移量:0x02D8，初值:0x00000000，宽度:32
 寄存器说明: MDM_NOC总线上Master设备的优先级控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_lbbp0  : 3;  /* bit[0-2]  : MDM NOC Master设备LBBP的总线PRESS优先级设置，可配置值0～7 */
        unsigned int  reserved_0                    : 1;  /* bit[3]    : 保留 */
        unsigned int  modem_noc_master_hurry_lbbp0  : 3;  /* bit[4-6]  : MDM NOC Master设备LBBP的总线HURRY优先级设置，可配置值0～7 */
        unsigned int  reserved_1                    : 1;  /* bit[7]    : 保留 */
        unsigned int  modem_noc_master_awqos_lbbp0  : 3;  /* bit[8-10] : MDM NOC Master设备LBBP的总线AWQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_2                    : 1;  /* bit[11]   : 保留 */
        unsigned int  modem_noc_master_arqos_lbbp0  : 3;  /* bit[12-14]: MDM NOC Master设备LBBP的总线ARQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_3                    : 1;  /* bit[15]   : 保留 */
        unsigned int  modem_noc_master_press_gubbp0 : 3;  /* bit[16-18]: MDM NOC Master设备GUBBP的总线PRESS优先级设置，可配置值0～7 */
        unsigned int  reserved_4                    : 1;  /* bit[19]   : 保留 */
        unsigned int  modem_noc_master_hurry_gubbp0 : 3;  /* bit[20-22]: MDM NOC Master设备GUBBP的总线HURRY优先级设置，可配置值0～7 */
        unsigned int  reserved_5                    : 1;  /* bit[23]   : 保留 */
        unsigned int  modem_noc_master_awqos_gubbp0 : 3;  /* bit[24-26]: MDM NOC Master设备GUBBP的总线AWQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_6                    : 1;  /* bit[27]   : 保留 */
        unsigned int  modem_noc_master_arqos_gubbp0 : 3;  /* bit[28-30]: MDM NOC Master设备GUBBP的总线ARQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_7                    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_press_lbbp0_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_press_lbbp0_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_hurry_lbbp0_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_hurry_lbbp0_END     (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_awqos_lbbp0_START   (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_awqos_lbbp0_END     (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_arqos_lbbp0_START   (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_arqos_lbbp0_END     (14)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_press_gubbp0_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_press_gubbp0_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_hurry_gubbp0_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_hurry_gubbp0_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_awqos_gubbp0_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_awqos_gubbp0_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_arqos_gubbp0_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL2_modem_noc_master_arqos_gubbp0_END    (30)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_UNION
 结构说明  : MDMSC_MNOC_QOSCTRL3 寄存器结构定义。地址偏移量:0x02DC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_ccpu : 3;  /* bit[0-2]  : MDM NOC Master设备CCPU的总线PRESS优先级设置，可配置值0～7 */
        unsigned int  reserved_0                  : 1;  /* bit[3]    : 保留 */
        unsigned int  modem_noc_master_hurry_ccpu : 3;  /* bit[4-6]  : MDM NOC Master设备CCPU的总线HURRY优先级设置，可配置值0～7 */
        unsigned int  reserved_1                  : 1;  /* bit[7]    : 保留 */
        unsigned int  modem_noc_master_awqos_ccpu : 3;  /* bit[8-10] : MDM NOC Master设备CCPU的总线AWQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_2                  : 1;  /* bit[11]   : 保留 */
        unsigned int  modem_noc_master_arqos_ccpu : 3;  /* bit[12-14]: MDM NOC Master设备CCPU的总线ARQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_3                  : 1;  /* bit[15]   : 保留 */
        unsigned int  reserved_4                  : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_press_ccpu_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_press_ccpu_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_hurry_ccpu_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_hurry_ccpu_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_awqos_ccpu_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_awqos_ccpu_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_arqos_ccpu_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL3_modem_noc_master_arqos_ccpu_END    (14)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_MEMCTRL_UNION
 结构说明  : MDMSC_MEMCTRL 寄存器结构定义。地址偏移量:0x02E0，初值:0x0C9B0C9B，宽度:32
 寄存器说明: 外设控制寄存器。功能包含mdmsys_ramctrl_s和mdmsys_ramctrl_d1w2r控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsys_ramctrl_d1w2r : 16; /* bit[0-15] : Modem子系统EDMAC的Memory控制 */
        unsigned int  mdmsys_ramctrl_s     : 16; /* bit[16-31]: Modem子系统的Memory控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MEMCTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_mdmsys_ramctrl_d1w2r_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_mdmsys_ramctrl_d1w2r_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_mdmsys_ramctrl_s_START      (16)
#define SOC_MODEM_SCTRL_MDMSC_MEMCTRL_mdmsys_ramctrl_s_END        (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_UNION
 结构说明  : MDMSC_BBE16_MEMCTRL 寄存器结构定义。地址偏移量:0x02E4，初值:0x0C9B0C9B，宽度:32
 寄存器说明: BBE16配置寄存器。功能包含BBE16的trace和notrace memory控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_notrace_mem_ctrl : 16; /* bit[0-15] : DSPBBE中notrace memory的控制 */
        unsigned int  bbe16_trace_mem_ctrl   : 16; /* bit[16-31]: DSPBBE中trace memory的控制 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_bbe16_notrace_mem_ctrl_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_bbe16_notrace_mem_ctrl_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_bbe16_trace_mem_ctrl_START    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_MEMCTRL_bbe16_trace_mem_ctrl_END      (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_UNION
 结构说明  : MDMSC_BBE16_DEFCTRL 寄存器结构定义。地址偏移量:0x02E8，初值:0x00000008，宽度:32
 寄存器说明: Modem子系统自定义BBE16的控制。功能包括BBE16地址保护功能指示,BBE16分区即将下电请求，BBE16时钟树低功耗使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_lowpower_en             : 1;  /* bit[0]    : bbe16 进入sleepmode状态后工作时钟选择低频时钟，切换到时钟树的低功耗模式的控制使能；
                                                                         0，不使能（默认）；
                                                                         1，使能 */
        unsigned int  bbe16_pwrdwn_req              : 1;  /* bit[1]    : bbe16分区即将下电请求信号，在BBE16分区下电前配置此信号为1；在分区上电后再配置此信号为0 */
        unsigned int  bbe16_overaddr_prot_rev       : 1;  /* bit[2]    : BBE16访问DDR地址防越界保护地址反转指示。
                                                                         0：指定地址范围内的地址为有效访问地址段；（默认）
                                                                         1：指定地址范围外的地址为有效指定地址段； */
        unsigned int  bbe16_overaddr_prot_bypass    : 1;  /* bit[3]    : BBE16访问DDR地址防越界保护功能旁路指示。
                                                                         0：不旁路,功能有效
                                                                         1：旁路，功能无效(默认) */
        unsigned int  reserved_0                    : 12; /* bit[4-15] : 保留 */
        unsigned int  bbe16_lowpower_en_msk         : 1;  /* bit[16]   : bbe16_lowpower_en MSK配置位 */
        unsigned int  bbe16_pwrdwn_req_msk          : 1;  /* bit[17]   : bbe16_pwrdwn_req MSK配置位 */
        unsigned int  bbe16_ddraddr_prot_rev_msk    : 1;  /* bit[18]   : bbe16_ddraddr_prot_rev MSK配置位 */
        unsigned int  bbe16_ddraddr_prot_bypass_msk : 1;  /* bit[19]   : bbe16_ddraddr_prot_bypass MSK配置位 */
        unsigned int  reserved_1                    : 12; /* bit[20-31]: [31:16]：每一bit顺序对应bit15～bit0，仅当bit31～16的bit写1的同时，配置bit15～0才能生效；当bit31～16的bit写0时，配置bit15～0保持不变； */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_lowpower_en_START              (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_lowpower_en_END                (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_pwrdwn_req_START               (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_pwrdwn_req_END                 (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_overaddr_prot_rev_START        (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_overaddr_prot_rev_END          (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_overaddr_prot_bypass_START     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_overaddr_prot_bypass_END       (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_lowpower_en_msk_START          (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_lowpower_en_msk_END            (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_pwrdwn_req_msk_START           (17)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_pwrdwn_req_msk_END             (17)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_ddraddr_prot_rev_msk_START     (18)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_ddraddr_prot_rev_msk_END       (18)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_ddraddr_prot_bypass_msk_START  (19)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DEFCTRL_bbe16_ddraddr_prot_bypass_msk_END    (19)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_UNION
 结构说明  : MDMSC_BBE16_TCM_SEL 寄存器结构定义。地址偏移量:0x02EC，初值:0x00000000，宽度:32
 寄存器说明: BBE16 TCM 的BBE16和外部复用选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_tcm_sel0  : 1;  /* bit[0]    : bbe16_tcm_sel[0]对应SRAM 0xFFB0_XXXX和BBE16 指令IRAM0 0xFF20_XXXX； */
        unsigned int  bbe16_tcm_sel1  : 1;  /* bit[1]    : bbe16_tcm_sel[1]对应SRAM 0xFFB1_XXXX和BBE16 指令IRAM0 0xFF21_XXXX； */
        unsigned int  bbe16_tcm_sel2  : 1;  /* bit[2]    : bbe16_tcm_sel[2]对应SRAM 0xFFB2_XXXX和BBE16 指令IRAM0 0xFF22_XXXX； */
        unsigned int  bbe16_tcm_sel3  : 1;  /* bit[3]    : bbe16_tcm_sel[3]对应SRAM 0xFFB3_XXXX和BBE16 指令IRAM0 0xFF23_XXXX； */
        unsigned int  bbe16_tcm_sel4  : 1;  /* bit[4]    : bbe16_tcm_sel[4]对应SRAM 0xFFB4_XXXX和BBE16 指令IRAM1 0xFF24_XXXX； */
        unsigned int  bbe16_tcm_sel5  : 1;  /* bit[5]    : bbe16_tcm_sel[5]对应SRAM 0xFFB5_XXXX和BBE16 指令IRAM1 0xFF25_XXXX； */
        unsigned int  bbe16_tcm_sel6  : 1;  /* bit[6]    : bbe16_tcm_sel[6]对应SRAM 0xFFB6_XXXX和BBE16 指令IRAM1 0xFF26_XXXX； */
        unsigned int  bbe16_tcm_sel7  : 1;  /* bit[7]    : bbe16_tcm_sel[7]对应SRAM 0xFFB7_XXXX和BBE16 数据DRAM0 0xFF28_XXXX； */
        unsigned int  bbe16_tcm_sel8  : 1;  /* bit[8]    : bbe16_tcm_sel[8]对应SRAM 0xFFB8_XXXX和BBE16 数据DRAM0 0xFF29_XXXX； */
        unsigned int  bbe16_tcm_sel9  : 1;  /* bit[9]    : bbe16_tcm_sel[9]对应SRAM 0xFFB9_XXXX和BBE16 数据DRAM0 0xFF2A_XXXX； */
        unsigned int  bbe16_tcm_sel10 : 1;  /* bit[10]   : bbe16_tcm_sel[10]对应SRAM 0xFFBA_XXXX和BBE16 数据DRAM0 0xFF2B_XXXX； */
        unsigned int  bbe16_tcm_sel11 : 1;  /* bit[11]   : bbe16_tcm_sel[11]对应SRAM 0xFFBB_XXXX和BBE16 数据DRAM1 0xFF2C_XXXX； */
        unsigned int  bbe16_tcm_sel12 : 1;  /* bit[12]   : bbe16_tcm_sel[12]对应SRAM 0xFFBC_XXXX和BBE16 数据DRAM1 0xFF2D_XXXX； */
        unsigned int  bbe16_tcm_sel13 : 1;  /* bit[13]   : bbe16_tcm_sel[13]对应SRAM 0xFFBD_XXXX和BBE16 数据DRAM1 0xFF2E_XXXX； */
        unsigned int  reserved        : 18; /* bit[14-31]: bbe16_tcm_sel是BBE16和外部复用memory的选择指示信号，为0表示memory分配给BBE16使用，为1标识复位为SRAM。以64KB为颗粒度复用，一共有12个复用单元。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel0_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel0_END     (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel1_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel1_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel2_START   (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel2_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel3_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel3_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel4_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel4_END     (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel5_START   (5)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel5_END     (5)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel6_START   (6)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel6_END     (6)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel7_START   (7)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel7_END     (7)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel8_START   (8)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel8_END     (8)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel9_START   (9)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel9_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel10_START  (10)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel10_END    (10)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel11_START  (11)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel11_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel12_START  (12)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel12_END    (12)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel13_START  (13)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_TCM_SEL_bbe16_tcm_sel13_END    (13)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_UNION
 结构说明  : MDMSC_BBE16_CTRL0 寄存器结构定义。地址偏移量:0x02F0，初值:0x00000031，宽度:32
 寄存器说明: BBE16控制寄存器，功能包含LTE总线优先级、LTEDSP控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_runstall       : 1;  /* bit[0]   : bbe16运行/停止。
                                                               0：运行；
                                                               1：停止。（默认值） */
        unsigned int  bbe16_statvectorsel  : 1;  /* bit[1]   : bbe16_statvectorsel必须配置为0。 */
        unsigned int  bbe16_ocdhaltonreset : 1;  /* bit[2]   : bbe16在解复位时强行进入OCDHalt模式。
                                                               0：正常模式（默认值）；
                                                               1：OCDHalt模式。
                                                               该bit在解复位前6个周期及后10个周期不能修改。
                                                               在解复位完成后，改变该bit没有影响。 */
        unsigned int  reserved_0           : 1;  /* bit[3]   : reserved */
        unsigned int  bbe16_pireqpriority  : 2;  /* bit[4-5] : 外部和core访问TCM优先级选择信号，默认值为3，表示外部访问优先级最高 */
        unsigned int  reserved_1           : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_runstall_START        (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_runstall_END          (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_statvectorsel_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_statvectorsel_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_ocdhaltonreset_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_ocdhaltonreset_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_pireqpriority_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL0_bbe16_pireqpriority_END     (5)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_UNION
 结构说明  : MDMSC_BBE16_CTRL1 寄存器结构定义。地址偏移量:0x02F4，初值:0x00000000，宽度:32
 寄存器说明: BBP子系统控制寄存器，功能包含LTEDSP NMI中断请求
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_nmi_irq     : 16; /* bit[0-15] : BBENMI中断配置信号。配置任一比特均可对DSP发出中断。
                                                             对BBE发出中断。 */
        unsigned int  bbe16_nmi_irq_msk : 16; /* bit[16-31]: [31:16]：每一bit顺序对应bit15～bit0，仅当bit31～16的bit写1的同时，配置bit15～0才能生效；当bit31～16的bit写0时，配置bit15～0保持不变； */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_bbe16_nmi_irq_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_bbe16_nmi_irq_END        (15)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_bbe16_nmi_irq_msk_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_CTRL1_bbe16_nmi_irq_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_UNION
 结构说明  : MDMSC_BBE16_STAT0 寄存器结构定义。地址偏移量:0x02F8，初值:0x00000000，宽度:32
 寄存器说明: BBE16状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_tie_expstate : 32; /* bit[0-31]: bbe16_tie_expstate[31:0] */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_bbe16_tie_expstate_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT0_bbe16_tie_expstate_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_UNION
 结构说明  : MDMSC_BBE16_STAT1 寄存器结构定义。地址偏移量:0x02FC，初值:0x00000000，宽度:32
 寄存器说明: BBP子系统状态寄存器，功能包含LTEDSP状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2] : 保留 */
        unsigned int  bbe16_xocdmode  : 1;  /* bit[3]   : 处理器OCDhaltmode状态指示信号，高有效。 */
        unsigned int  bbe16_pwaitmode : 1;  /* bit[4]   : 处理器sleepmode状态指示信号，高有效。指示当前处理器通过执行WAITI指令进入sleepmode（clockgating）并等待未屏蔽中断唤醒。 */
        unsigned int  reserved_1      : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_bbe16_xocdmode_START   (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_bbe16_xocdmode_END     (3)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_bbe16_pwaitmode_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_STAT1_bbe16_pwaitmode_END    (4)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_UNION
 结构说明  : MDMSC_BBE16_DDRADDR_PROT 寄存器结构定义。地址偏移量:0x0300，初值:0x0FFF0000，宽度:32
 寄存器说明: BBE16 访问DDR保护地址段配置，地址配置精度为1M
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_2ddr_valid_laddr : 12; /* bit[0-11] : BBE16 访问DDR有效地址段起始地址高12bit */
        unsigned int  reserved_0             : 4;  /* bit[12-15]: 保留 */
        unsigned int  bbe16_2ddr_valid_haddr : 12; /* bit[16-27]: BBE16 访问DDR有效地址段结束地址高12bit */
        unsigned int  reserved_1             : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_bbe16_2ddr_valid_laddr_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_bbe16_2ddr_valid_laddr_END    (11)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_bbe16_2ddr_valid_haddr_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_DDRADDR_PROT_bbe16_2ddr_valid_haddr_END    (27)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_UNION
 结构说明  : MDMSC_MDMNOC_POWER_DOMAIN_CTRL 寄存器结构定义。地址偏移量:0x0304，初值:0x00000000，宽度:32
 寄存器说明: MDMNOC power domain 控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe_domain_idlereq     : 1;  /* bit[0]    : bbe16 powerdomain idlereq
                                                                  0：normal mode
                                                                  1：idle req when this domain idle,power down or rst */
        unsigned int  bbp_domain_idlereq     : 1;  /* bit[1]    : bbp powerdomain idlereq
                                                                  0：normal mode
                                                                  1：idle req when this domain idle,power down or rst */
        unsigned int  reserved_0             : 14; /* bit[2-15] : 保留 */
        unsigned int  bbe_domain_idlereq_msk : 1;  /* bit[16]   : bbe_domain_idlereq MSK配置位 */
        unsigned int  bbp_domain_idlereq_msk : 1;  /* bit[17]   : bbp_domain_idlereq MSK配置位 */
        unsigned int  reserved_1             : 14; /* bit[18-31]: [31:16]：每一bit顺序对应bit15～bit0，仅当bit31～16的bit写1的同时，配置bit15～0才能生效；当bit31～16的bit写0时，配置bit15～0保持不变； */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbe_domain_idlereq_START      (0)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbe_domain_idlereq_END        (0)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbp_domain_idlereq_START      (1)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbp_domain_idlereq_END        (1)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbe_domain_idlereq_msk_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbe_domain_idlereq_msk_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbp_domain_idlereq_msk_START  (17)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_CTRL_bbp_domain_idlereq_msk_END    (17)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_UNION
 结构说明  : MDMSC_MDMNOC_POWER_DOMAIN_RPT 寄存器结构定义。地址偏移量:0x0308，初值:0x00000000，宽度:32
 寄存器说明: MDMNOC power domain上报寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe_domain_idleack : 1;  /* bit[0]   : bbe16 powerdomain状态上报信号(bbe_domain_idle_ack)
                                                             0：idle req not ack
                                                             1：idle req ack
                                                             when this domain pwdn or rst,it still can be accessed if idleack and idle both valid */
        unsigned int  bbe_domain_idle    : 1;  /* bit[1]   : bbe16 powerdomain状态上报信号（bbe_domain_idle）
                                                             0：domain not idle
                                                             1：domain in idle
                                                             when this domain pwdn or rst,it still can be accessed if idleack and idle both valid */
        unsigned int  bbp_domain_idleack : 1;  /* bit[2]   : BBP powerdomain状态上报信号(bbp_domain_idle_ack)
                                                             0：idle req not ack
                                                             1：idle req ack
                                                             when this domain pwdn or rst,it still can be accessed if idleack and idle both valid */
        unsigned int  bbp_domain_idle    : 1;  /* bit[3]   : BBP powerdomain状态上报信号（bbp_domain_idle）
                                                             0：domain not idle
                                                             1：domain in idle
                                                             when this domain pwdn or rst,it still can be accessed if idleack and idle both valid */
        unsigned int  reserved           : 28; /* bit[4-31]:  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbe_domain_idleack_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbe_domain_idleack_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbe_domain_idle_START     (1)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbe_domain_idle_END       (1)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbp_domain_idleack_START  (2)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbp_domain_idleack_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbp_domain_idle_START     (3)
#define SOC_MODEM_SCTRL_MDMSC_MDMNOC_POWER_DOMAIN_RPT_bbp_domain_idle_END       (3)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_UNION
 结构说明  : MDMSC_MNOC_QOSCTRL4 寄存器结构定义。地址偏移量:0x030C，初值:0x00000000，宽度:32
 寄存器说明: MDM_NOC总线上Master设备的优先级控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_noc_master_press_lbbp1  : 3;  /* bit[0-2]  : MDM NOC Master设备LBBP的总线PRESS优先级设置，可配置值0～7 */
        unsigned int  reserved_0                    : 1;  /* bit[3]    : 保留 */
        unsigned int  modem_noc_master_hurry_lbbp1  : 3;  /* bit[4-6]  : MDM NOC Master设备LBBP的总线HURRY优先级设置，可配置值0～7 */
        unsigned int  reserved_1                    : 1;  /* bit[7]    : 保留 */
        unsigned int  modem_noc_master_awqos_lbbp1  : 3;  /* bit[8-10] : MDM NOC Master设备LBBP的总线AWQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_2                    : 1;  /* bit[11]   : 保留 */
        unsigned int  modem_noc_master_arqos_lbbp1  : 3;  /* bit[12-14]: MDM NOC Master设备LBBP的总线ARQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_3                    : 1;  /* bit[15]   : 保留 */
        unsigned int  modem_noc_master_press_gubbp1 : 3;  /* bit[16-18]: MDM NOC Master设备GUBBP的总线PRESS优先级设置，可配置值0～7 */
        unsigned int  reserved_4                    : 1;  /* bit[19]   : 保留 */
        unsigned int  modem_noc_master_hurry_gubbp1 : 3;  /* bit[20-22]: MDM NOC Master设备GUBBP的总线HURRY优先级设置，可配置值0～7 */
        unsigned int  reserved_5                    : 1;  /* bit[23]   : 保留 */
        unsigned int  modem_noc_master_awqos_gubbp1 : 3;  /* bit[24-26]: MDM NOC Master设备GUBBP的总线AWQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_6                    : 1;  /* bit[27]   : 保留 */
        unsigned int  modem_noc_master_arqos_gubbp1 : 3;  /* bit[28-30]: MDM NOC Master设备GUBBP的总线ARQOS优先级设置，可配置值为0～7 */
        unsigned int  reserved_7                    : 1;  /* bit[31]   : 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_press_lbbp1_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_press_lbbp1_END     (2)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_hurry_lbbp1_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_hurry_lbbp1_END     (6)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_awqos_lbbp1_START   (8)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_awqos_lbbp1_END     (10)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_arqos_lbbp1_START   (12)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_arqos_lbbp1_END     (14)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_press_gubbp1_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_press_gubbp1_END    (18)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_hurry_gubbp1_START  (20)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_hurry_gubbp1_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_awqos_gubbp1_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_awqos_gubbp1_END    (26)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_arqos_gubbp1_START  (28)
#define SOC_MODEM_SCTRL_MDMSC_MNOC_QOSCTRL4_modem_noc_master_arqos_gubbp1_END    (30)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_UNION
 结构说明  : MDMSC_BBP_LBUS_CTRL 寄存器结构定义。地址偏移量:0x0310，初值:0x0C9B0000，宽度:32
 寄存器说明: BBP控制寄存器，功能包含BBP Local总线控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbpaxi_priority_set  : 2;  /* bit[0-1]  : bbp总线有效级设置
                                                                00:优先级dma>axi
                                                                01:优先级dma<axi
                                                                others:reserved */
        unsigned int  bbp_axi_bsi_cg_en    : 1;  /* bit[2]    : bbp_axi_lbuscg_en自动门控使能
                                                                0:clknotgate
                                                                1:clkgateenable */
        unsigned int  bbp_axi_rs_cg_en     : 1;  /* bit[3]    : bbp_axi_rs_cg_en自动门控使能。
                                                                0:clknotgate
                                                                1:clkgateenable */
        unsigned int  bbp_axi_gs_cg_en     : 1;  /* bit[4]    : bbp_axi_gs_cg_en自动门控使能
                                                                0:clknotgate
                                                                1:clkgateenable */
        unsigned int  bus_lockdown_protect : 2;  /* bit[5-6]  : 总线防止挂死保护
                                                                00:关闭防挂死保护
                                                                01:使能防挂死保护，超时时间512cycles
                                                                10:使能防挂死保护，超时时间1024cycles
                                                                11:使能防挂死保护，超时时间2048cycles */
        unsigned int  reserved             : 9;  /* bit[7-15] : reserved */
        unsigned int  atpram_ctrl          : 16; /* bit[16-31]: bbp接口信号atpramctrl */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbpaxi_priority_set_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbpaxi_priority_set_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_bsi_cg_en_START     (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_bsi_cg_en_END       (2)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_rs_cg_en_START      (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_rs_cg_en_END        (3)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_gs_cg_en_START      (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bbp_axi_gs_cg_en_END        (4)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bus_lockdown_protect_START  (5)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_bus_lockdown_protect_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_atpram_ctrl_START           (16)
#define SOC_MODEM_SCTRL_MDMSC_BBP_LBUS_CTRL_atpram_ctrl_END             (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_UNION
 结构说明  : MDMSC_CCPU_LAXI_STAT 寄存器结构定义。地址偏移量:0x0314，初值:0x00000000，宽度:32
 寄存器说明: CCPU分区局部AXI总线状态上报
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ccpu_localaxi_dlock_irq : 1;  /* bit[0]    : CCPU local axi总线锁存指示,状态不随系统复位改变,dlock_irq上升沿锁存
                                                                   0:不锁存总线状态
                                                                   1:锁存总线状态 */
        unsigned int  ccpu_localaxi_dlock_wr  : 1;  /* bit[1]    : CCPU local axi总线读写指示,状态不随系统复位改变,dlock_irq上升沿锁存
                                                                   0:总线读指示
                                                                   1:总线写指示 */
        unsigned int  reserved_0              : 2;  /* bit[2-3]  : 保留 */
        unsigned int  ccpu_localaxi_dlock_id  : 6;  /* bit[4-9]  : CCPU local axi总线操作id指示,状态不随系统复位改变,dlock_irq上升沿锁存 */
        unsigned int  reserved_1              : 6;  /* bit[10-15]: 保留 */
        unsigned int  ccpu_localaxi_dlock_slv : 2;  /* bit[16-17]: CCPU local axi总线slave端口指示,对应端口0～1,状态不随系统复位改变,dlock_irq上升沿锁存 */
        unsigned int  reserved_2              : 6;  /* bit[18-23]: 保留 */
        unsigned int  ccpu_localaxi_dlock_mst : 1;  /* bit[24]   : CCPU local axi总线master端口指示,对应端口0～1,状态不随系统复位改变,dlock_irq上升沿锁存 */
        unsigned int  reserved_3              : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_irq_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_irq_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_wr_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_wr_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_id_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_id_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_slv_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_slv_END    (17)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_mst_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_CCPU_LAXI_STAT_ccpu_localaxi_dlock_mst_END    (24)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_UNION
 结构说明  : MDMSC_BBE16_LAXI_STAT 寄存器结构定义。地址偏移量:0x0318，初值:0x00000000，宽度:32
 寄存器说明: BBE16分区局部AXI总线状态上报
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_localaxi_dlock_irq : 1;  /* bit[0]    : BBE16 local axi总线锁存指示,状态不随系统复位改变,dlock_irq上升沿锁存
                                                                    0:不锁存总线状态
                                                                    1:锁存总线状态 */
        unsigned int  bbe16_localaxi_dlock_wr  : 1;  /* bit[1]    : BBE16 local axi总线读写指示,状态不随系统复位改变,dlock_irq上升沿锁存
                                                                    0:总线读指示
                                                                    1:总线写指示 */
        unsigned int  reserved_0               : 2;  /* bit[2-3]  : 保留 */
        unsigned int  bbe16_localaxi_dlock_id  : 6;  /* bit[4-9]  : BBE16 local axi总线操作id指示,状态不随系统复位改变,dlock_irq上升沿锁存 */
        unsigned int  reserved_1               : 6;  /* bit[10-15]: 保留 */
        unsigned int  bbe16_localaxi_dlock_slv : 1;  /* bit[16]   : BBE16 local axi总线slave端口指示,状态不随系统复位改变,dlock_irq上升沿锁存 */
        unsigned int  reserved_2               : 7;  /* bit[17-23]: 保留 */
        unsigned int  bbe16_localaxi_dlock_mst : 1;  /* bit[24]   : BBE16 local axi总线master端口指示,对应端口0～1,状态不随系统复位改变,dlock_irq上升沿锁存 */
        unsigned int  reserved_3               : 7;  /* bit[25-31]: 保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_irq_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_irq_END    (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_wr_START   (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_wr_END     (1)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_id_START   (4)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_id_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_slv_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_slv_END    (16)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_mst_START  (24)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_LAXI_STAT_bbe16_localaxi_dlock_mst_END    (24)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_UNION
 结构说明  : MDMSC_NOC_LPOWER_CFG 寄存器结构定义。地址偏移量:0x031C，初值:0x00200020，宽度:32
 寄存器说明: MDM_NOC总线低功耗运行模式控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmnoc_in_lpower_pulse_width  : 10; /* bit[0-9]  : MDMNOC总线进入低功耗运行模式的脉冲高电平宽度门限值 */
        unsigned int  reserved_0                    : 6;  /* bit[10-15]: 保留 */
        unsigned int  mdmnoc_out_lpower_pulse_width : 10; /* bit[16-25]: MDMNOC总线退出低功耗运行模式的低电平宽度门限值 */
        unsigned int  reserved_1                    : 5;  /* bit[26-30]: 保留 */
        unsigned int  mdmnoc_lpower_en              : 1;  /* bit[31]   : MDMNOC总线低功耗运行模式使能信号，1为MDMNOC支持低功耗运行模式，0为MDMNOC不支持低功耗运行模式 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_in_lpower_pulse_width_START   (0)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_in_lpower_pulse_width_END     (9)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_out_lpower_pulse_width_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_out_lpower_pulse_width_END    (25)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_lpower_en_START               (31)
#define SOC_MODEM_SCTRL_MDMSC_NOC_LPOWER_CFG_mdmnoc_lpower_en_END                 (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_UNION
 结构说明  : MDMSC_DFS_DIVCFG0 寄存器结构定义。地址偏移量:0x0320，初值:0x00000700，宽度:32
 寄存器说明: 时钟参数配置寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_div0_ccpu_cfg_value           : 7;  /* bit[0-6]  : 时钟参数。
                                                                             [6:4]:保留
                                                                             [3:0]:CCPU时钟的分频参数配置; */
        unsigned int  clk_div0_ccpu_cfg_vld             : 1;  /* bit[7]    : 时钟参数有效指示。 */
        unsigned int  clk_div0_bbe16_lowpower_cfg_value : 7;  /* bit[8-14] : 时钟参数。
                                                                             [14:12]:保留
                                                                             [11:8]: BBE16 低功耗时钟的分频参数配置 */
        unsigned int  clk_div0_bbe16_lowpower_cfg_vld   : 1;  /* bit[15]   : 时钟参数有效指示。 */
        unsigned int  reserved_0                        : 7;  /* bit[16-22]: 时钟参数。 */
        unsigned int  reserved_1                        : 1;  /* bit[23]   : 时钟参数有效指示。 */
        unsigned int  reserved_2                        : 7;  /* bit[24-30]: 时钟参数。 */
        unsigned int  reserved_3                        : 1;  /* bit[31]   : 时钟参数有效指示。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_ccpu_cfg_value_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_ccpu_cfg_value_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_ccpu_cfg_vld_START              (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_ccpu_cfg_vld_END                (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_bbe16_lowpower_cfg_value_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_bbe16_lowpower_cfg_value_END    (14)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_bbe16_lowpower_cfg_vld_START    (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG0_clk_div0_bbe16_lowpower_cfg_vld_END      (15)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_UNION
 结构说明  : MDMSC_DFS_DIVCFG1 寄存器结构定义。地址偏移量:0x0324，初值:0x000B0300，宽度:32
 寄存器说明: 时钟参数配置寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_div1_bbe16_cfg_value       : 7;  /* bit[0-6]  : 时钟参数。
                                                                          [6:4]:保留
                                                                          [3:0]:BBE16时钟的分频参数配置; */
        unsigned int  clk_div1_bbe16_cfg_value_vld   : 1;  /* bit[7]    : 时钟参数有效指示。 */
        unsigned int  clk_div1_ccpuatb_cfg_value     : 7;  /* bit[8-14] : 时钟参数。
                                                                          [14:12]:保留
                                                                          [11:8]:MCPU ATB时钟的分频参数配置; */
        unsigned int  clk_div1_ccpuatb_cfg_value_vld : 1;  /* bit[15]   : 时钟参数有效指示。 */
        unsigned int  clk_div1_ccpuapb_cfg_value     : 7;  /* bit[16-22]: 时钟参数。
                                                                          [22:20]:保留
                                                                          [19:16]:MCPU APB时钟的分频参数配置; */
        unsigned int  clk_div1_ccpuapb_cfg_value_vld : 1;  /* bit[23]   : 时钟参数有效指示。 */
        unsigned int  reserved_0                     : 7;  /* bit[24-30]: 时钟参数。 */
        unsigned int  reserved_1                     : 1;  /* bit[31]   : 时钟参数有效指示。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_bbe16_cfg_value_START        (0)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_bbe16_cfg_value_END          (6)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_bbe16_cfg_value_vld_START    (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_bbe16_cfg_value_vld_END      (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuatb_cfg_value_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuatb_cfg_value_END        (14)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuatb_cfg_value_vld_START  (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuatb_cfg_value_vld_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuapb_cfg_value_START      (16)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuapb_cfg_value_END        (22)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuapb_cfg_value_vld_START  (23)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG1_clk_div1_ccpuapb_cfg_value_vld_END    (23)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_UNION
 结构说明  : MDMSC_DFS_DIVCFG2 寄存器结构定义。地址偏移量:0x0328，初值:0x00050101，宽度:32
 寄存器说明: 时钟参数配置寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_div2_noc_cfg_value           : 7;  /* bit[0-6]  : 时钟参数。
                                                                            [6:4]:保留
                                                                            [3:0]:Modem NOC 时钟的分频参数配置; */
        unsigned int  clk_div2_noc_cfg_vld             : 1;  /* bit[7]    : 时钟参数有效指示。 */
        unsigned int  clk_div2_ccpu_lbus_cfg_value     : 7;  /* bit[8-14] : 时钟参数。
                                                                            [14:12]:保留
                                                                            [11:8]:CCPU LBUS时钟的分频参数配置; */
        unsigned int  clk_div2_ccpu_lbus_cfg_vld       : 1;  /* bit[15]   : 时钟参数有效指示。 */
        unsigned int  clk_div2_mdmnoc_lpower_cfg_value : 7;  /* bit[16-22]: 时钟参数。
                                                                            [22:20]:保留
                                                                            [19:16]:Modem NOC低功耗运行模式下的时钟分频参数配置 */
        unsigned int  clk_div2_mdmnoc_lpower_cfg_vld   : 1;  /* bit[23]   : 时钟参数有效指示。 */
        unsigned int  reserved_0                       : 7;  /* bit[24-30]: 时钟参数。 */
        unsigned int  reserved_1                       : 1;  /* bit[31]   : 时钟参数有效指示。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_noc_cfg_value_START            (0)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_noc_cfg_value_END              (6)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_noc_cfg_vld_START              (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_noc_cfg_vld_END                (7)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_ccpu_lbus_cfg_value_START      (8)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_ccpu_lbus_cfg_value_END        (14)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_ccpu_lbus_cfg_vld_START        (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_ccpu_lbus_cfg_vld_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_mdmnoc_lpower_cfg_value_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_mdmnoc_lpower_cfg_value_END    (22)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_mdmnoc_lpower_cfg_vld_START    (23)
#define SOC_MODEM_SCTRL_MDMSC_DFS_DIVCFG2_clk_div2_mdmnoc_lpower_cfg_vld_END      (23)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_UNION
 结构说明  : MDMSC_PWUP_TIME0 寄存器结构定义。地址偏移量:0x0330，初值:0x00C800C8，宽度:32
 寄存器说明: 掉电区电源稳定计数器1。用于指示各掉电区电源调整后电压稳定所需的时间。该寄存器只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwup_time_dspbbe : 16; /* bit[0-15] : [15:0]: 指示DSPBBE下电区电压调整后电压稳定时间，采用TCXO时钟递减计数。 */
        unsigned int  pwup_time_lte    : 16; /* bit[16-31]: [31:16]: 指示LTE下电区电压调整后电压稳定时间，采用TCXO时钟递减计数。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_pwup_time_dspbbe_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_pwup_time_dspbbe_END    (15)
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_pwup_time_lte_START     (16)
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME0_pwup_time_lte_END       (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_UNION
 结构说明  : MDMSC_PWUP_TIME1 寄存器结构定义。地址偏移量:0x0334，初值:0x00C800C8，宽度:32
 寄存器说明: 掉电区电源稳定计数器1。用于指示各掉电区电源调整后电压稳定所需的时间。该寄存器只在上电复位时被复位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwup_time_bbp_cs : 16; /* bit[0-15] : [15:0]: 指示BBP_CS下电区 电压调整后电压稳定时间，采用TCXO时钟递减计数。 */
        unsigned int  reserved         : 16; /* bit[16-31]: [31:16]: 指示BBP_PS下电区电压调整后电压稳定时间，采用TCXO时钟递减计数。(harq mem共享后，ps分区控制外移，保留) */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_pwup_time_bbp_cs_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_PWUP_TIME1_pwup_time_bbp_cs_END    (15)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_UNION
 结构说明  : MDMSC_BBEPWDN_SRAM_CTRL 寄存器结构定义。地址偏移量:0x0340，初值:0xFF280000，宽度:32
 寄存器说明: BBE16分区下电后SRAM地址控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16pwrdn_sram_remap_addr : 32; /* bit[0-31]: BBE16分区下电后CCPU访问SRAM的地址映射到TCM地址段，默认值为TCM起始地址（0xFF280000） */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_bbe16pwrdn_sram_remap_addr_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBEPWDN_SRAM_CTRL_bbe16pwrdn_sram_remap_addr_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_UNION
 结构说明  : MDMSC_BBE16_OVERADDR_PROT 寄存器结构定义。地址偏移量:0x0344，初值:0xFE000000，宽度:32
 寄存器说明: BBE16访问DDR越界保护的映射地址值配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbe16_overaddr_prot_value : 32; /* bit[0-31]: BBE16防越界保护的地址值，映射到MEMORYMAP的reserved空间，默认值为0xFE00_0000 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_bbe16_overaddr_prot_value_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBE16_OVERADDR_PROT_bbe16_overaddr_prot_value_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_UNION
 结构说明  : MDMSC_SLICER_COUNT0 寄存器结构定义。地址偏移量:0x0350，初值:0x00000000，宽度:32
 寄存器说明: slicer count0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count : 32; /* bit[0-31]: slicer count 32k时钟戳 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_sc_slicer_count_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT0_sc_slicer_count_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_UNION
 结构说明  : MDMSC_SLICER_COUNT1 寄存器结构定义。地址偏移量:0x0354，初值:0x00000000，宽度:32
 寄存器说明: slicer count1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_gbbp1_int : 32; /* bit[0-31]: sc_slicer_count由gbbp1_int中断锁定值 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_sc_slicer_count_gbbp1_int_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT1_sc_slicer_count_gbbp1_int_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_UNION
 结构说明  : MDMSC_SLICER_COUNT2 寄存器结构定义。地址偏移量:0x0358，初值:0x00000000，宽度:32
 寄存器说明: slicer count2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_gbbp1_int_32k : 32; /* bit[0-31]: sc_slicer_count由gbbp1_int_32k中断锁定值 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_sc_slicer_count_gbbp1_int_32k_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT2_sc_slicer_count_gbbp1_int_32k_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_UNION
 结构说明  : MDMSC_SLICER_COUNT3 寄存器结构定义。地址偏移量:0x035C，初值:0x00000000，宽度:32
 寄存器说明: slicer count3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_gbbp2_int : 32; /* bit[0-31]: sc_slicer_count由gbbp2_int中断锁定值 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_sc_slicer_count_gbbp2_int_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT3_sc_slicer_count_gbbp2_int_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_UNION
 结构说明  : MDMSC_SLICER_COUNT4 寄存器结构定义。地址偏移量:0x0360，初值:0x00000000，宽度:32
 寄存器说明: slicer count4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_gbbp2_int_32k : 32; /* bit[0-31]: sc_slicer_count由gbbp2_int_32k中断锁定值 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_sc_slicer_count_gbbp2_int_32k_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT4_sc_slicer_count_gbbp2_int_32k_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_UNION
 结构说明  : MDMSC_SLICER_COUNT5 寄存器结构定义。地址偏移量:0x0364，初值:0x00000000，宽度:32
 寄存器说明: slicer count5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_wbbp_clksw : 32; /* bit[0-31]: sc_slicer_count由wbbp2_int中断锁定值 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_sc_slicer_count_wbbp_clksw_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT5_sc_slicer_count_wbbp_clksw_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_UNION
 结构说明  : MDMSC_SLICER_COUNT6 寄存器结构定义。地址偏移量:0x0368，初值:0x00000000，宽度:32
 寄存器说明: slicer count6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_wbbp_int_32k : 32; /* bit[0-31]: sc_slicer_count由wbbp1_int_32k中断锁定值 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_sc_slicer_count_wbbp_int_32k_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT6_sc_slicer_count_wbbp_int_32k_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_UNION
 结构说明  : MDMSC_SLICER_COUNT7 寄存器结构定义。地址偏移量:0x036C，初值:0x00000000，宽度:32
 寄存器说明: slicer count7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_slicer_count_1x_evdo_int_32k : 32; /* bit[0-31]: sc_slicer_count由1x和evdo的wakeup中断锁定值 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_sc_slicer_count_1x_evdo_int_32k_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SLICER_COUNT7_sc_slicer_count_1x_evdo_int_32k_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_WBBPID_UNION
 结构说明  : MDMSC_WBBPID 寄存器结构定义。地址偏移量:0x0380，初值:0x48690001，宽度:32
 寄存器说明: WBBPID寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wbbp_id       : 16; /* bit[0-15] : 16'h0001。 */
        unsigned int  wbbp_designer : 16; /* bit[16-31]: 16'h4869,”H”的ASCII码是0x48，”i”的ASCII码是0x69。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_WBBPID_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_wbbp_id_START        (0)
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_wbbp_id_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_wbbp_designer_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_WBBPID_wbbp_designer_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_GBBPID_UNION
 结构说明  : MDMSC_GBBPID 寄存器结构定义。地址偏移量:0x0384，初值:0x48690002，宽度:32
 寄存器说明: GBBPID寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gbbp_id       : 16; /* bit[0-15] : 16'h0002。 */
        unsigned int  gbbp_designer : 16; /* bit[16-31]: 16'h4869,”H”的ASCII码是0x48，”i”的ASCII码是0x69。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_GBBPID_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_gbbp_id_START        (0)
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_gbbp_id_END          (15)
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_gbbp_designer_START  (16)
#define SOC_MODEM_SCTRL_MDMSC_GBBPID_gbbp_designer_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_UNION
 结构说明  : MDMSC_LTEBBP_DRX_TIMER0 寄存器结构定义。地址偏移量:0x0388，初值:0x00000000，宽度:32
 寄存器说明: BBP可维可测读次数计数器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx_abs_timer_low : 32; /* bit[0-31]: lteabstimerpub[31;0]
                                                             BBP可维可测读次数计数器低32bit计数 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_ldrx_abs_timer_low_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER0_ldrx_abs_timer_low_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_UNION
 结构说明  : MDMSC_LTEBBP_DRX_TIMER1 寄存器结构定义。地址偏移量:0x038C，初值:0x00000000，宽度:32
 寄存器说明: BBP可维可测读次数计数器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx_abs_timer_high : 32; /* bit[0-31]: lteabstimerpub[63;32]
                                                              BBP可维可测读次数计数器高32bit计数 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_ldrx_abs_timer_high_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_LTEBBP_DRX_TIMER1_ldrx_abs_timer_high_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_UNION
 结构说明  : MDMSC_SOC_VERSION 寄存器结构定义。地址偏移量:0x0394，初值:0x20130808，宽度:32
 寄存器说明: Modem 版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_soc_version : 32; /* bit[0-31]: Modem 版本寄存器 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_modem_soc_version_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_SOC_VERSION_modem_soc_version_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_RESERVED01_UNION
 结构说明  : MDMSC_RESERVED01 寄存器结构定义。地址偏移量:0x0398，初值:0x00000000，宽度:32
 寄存器说明: 保留寄存器，提供软件测试或调试使用。寄存器数值随系统复位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved01 : 32; /* bit[0-31]: 保留寄存器，寄存器数值随系统复位 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED01_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED01_mdmsc_reserved01_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED01_mdmsc_reserved01_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_RESERVED02_UNION
 结构说明  : MDMSC_RESERVED02 寄存器结构定义。地址偏移量:0x039C，初值:0x00000000，宽度:32
 寄存器说明: 保留寄存器，提供软件测试或调试使用。寄存器数值随系统复位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved02 : 32; /* bit[0-31]: 保留寄存器，寄存器数值随系统复位 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED02_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED02_mdmsc_reserved02_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED02_mdmsc_reserved02_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_RESERVED03_UNION
 结构说明  : MDMSC_RESERVED03 寄存器结构定义。地址偏移量:0x03A0，初值:0x00000000，宽度:32
 寄存器说明: 保留上报寄存器，提供芯片ECO使用。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved03 : 32; /* bit[0-31]: 保留上报寄存器 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED03_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED03_mdmsc_reserved03_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED03_mdmsc_reserved03_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_RESERVED04_UNION
 结构说明  : MDMSC_RESERVED04 寄存器结构定义。地址偏移量:0x03A4，初值:0x00000000，宽度:32
 寄存器说明: 保留寄存器，提供软件测试或调试使用。寄存器数值不随系统复位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved04 : 32; /* bit[0-31]: 保留寄存器，寄存器数值不随系统复位 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED04_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED04_mdmsc_reserved04_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED04_mdmsc_reserved04_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_RESERVED05_UNION
 结构说明  : MDMSC_RESERVED05 寄存器结构定义。地址偏移量:0x03A8，初值:0x00000000，宽度:32
 寄存器说明: 保留寄存器，提供软件测试或调试使用。寄存器数值不随系统复位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved05 : 32; /* bit[0-31]: 保留寄存器，寄存器数值不随系统复位 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED05_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED05_mdmsc_reserved05_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED05_mdmsc_reserved05_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_RESERVED06_UNION
 结构说明  : MDMSC_RESERVED06 寄存器结构定义。地址偏移量:0x03AC，初值:0x00000000，宽度:32
 寄存器说明: 保留寄存器，提供软件测试或调试使用。寄存器数值不随系统复位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_reserved06 : 32; /* bit[0-31]: 保留寄存器，寄存器数值不随系统复位 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_RESERVED06_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_RESERVED06_mdmsc_reserved06_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_RESERVED06_mdmsc_reserved06_END    (31)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_UNION
 结构说明  : MDMSC_FPGA_BBP_DRX_FLAG 寄存器结构定义。地址偏移量:0x03B0，初值:0x00000000，宽度:32
 寄存器说明: BBP中G/W/C送给ARM的唤醒指示(此寄存器只用于FPGA调试)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_gcudrx_deepsleep_flag : 8;  /* bit[0-7] : [7:5]保留
                                                                     [4]:cdrx_deepsleep_flag_1x
                                                                     [3]:cdrx_deepsleep_flag_evdo
                                                                     [2]:g2drx_deepsleep_flag
                                                                     [1]:g1drx_deepsleep_flag
                                                                     [0]:wdrx_deepsleep_flag */
        unsigned int  reserved                   : 24; /* bit[8-31]: BBP中G/W/C送给ARM的唤醒指示,在唤醒前提前一段时间给ARM指示，时间提前量可配置，ARM使用该信号判断是否进行深睡眠，高有效(只用于FPGA调试) */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_fpga_gcudrx_deepsleep_flag_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_BBP_DRX_FLAG_fpga_gcudrx_deepsleep_flag_END    (7)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_UNION
 结构说明  : MDMSC_FPGA_PMUSSI_CNT 寄存器结构定义。地址偏移量:0x03B4，初值:0x00000000，宽度:32
 寄存器说明: PMU SSI cnt计数上报(仅用于FPGA调试)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_pmussi0_mst_cnt : 3;  /* bit[0-2]  : fpga_pmussi0_mst_cnt */
        unsigned int  reserved_0           : 1;  /* bit[3]    : 保留 */
        unsigned int  fpga_pmussi1_mst_cnt : 3;  /* bit[4-6]  : fpga_pmussi1_mst_cnt */
        unsigned int  reserved_1           : 1;  /* bit[7]    : 保留 */
        unsigned int  fpga_pmussi2_mst_cnt : 3;  /* bit[8-10] : fpga_pmussi2_mst_cnt */
        unsigned int  reserved_2           : 21; /* bit[11-31]: PMU SSI cnt计数上报(仅用于FPGA调试)
                                                                保留 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi0_mst_cnt_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi0_mst_cnt_END    (2)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi1_mst_cnt_START  (4)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi1_mst_cnt_END    (6)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi2_mst_cnt_START  (8)
#define SOC_MODEM_SCTRL_MDMSC_FPGA_PMUSSI_CNT_fpga_pmussi2_mst_cnt_END    (10)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_UNION
 结构说明  : MDMSC_TESTPIN_SEL 寄存器结构定义。地址偏移量:0x03B8，初值:0x00000000，宽度:32
 寄存器说明: Modem子系统Modem_SC TESTPIN信号选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mdmsc_testpin_sel : 5;  /* bit[0-4] : Modem SC testpin选择输出信号 */
        unsigned int  reserved          : 27; /* bit[5-31]:  */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_mdmsc_testpin_sel_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_TESTPIN_SEL_mdmsc_testpin_sel_END    (4)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_UNION
 结构说明  : MODEM_TESTPIN_SEL 寄存器结构定义。地址偏移量:0x03BC，初值:0x00000000，宽度:32
 寄存器说明: Modem子系统TESTPIN信号选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_testpin_sel : 5;  /* bit[0-4] : Modem子系统testpin选择输出信号 */
        unsigned int  reserved          : 27; /* bit[5-31]:  */
    } reg;
} SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_UNION;
#endif
#define SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_modem_testpin_sel_START  (0)
#define SOC_MODEM_SCTRL_MODEM_TESTPIN_SEL_modem_testpin_sel_END    (4)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_UNION
 结构说明  : MDMSC_BBIT_GLB_RSTEN 寄存器结构定义。地址偏移量:0x03D0，初值:0x00000000，宽度:32
 寄存器说明: BBIT MODEM子系统全局复位使能寄存器。用于使能外设复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_bbit_modem_glb_rsten : 1;  /* bit[0]   : 仅用于FPGA BBIT平台Modem全局软复位 */
        unsigned int  reserved                  : 31; /* bit[1-31]: 复位使能定义如下（写1复位使能）。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_fpga_bbit_modem_glb_rsten_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_fpga_bbit_modem_glb_rsten_END    (0)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_UNION
 结构说明  : MDMSC_BBIT_GLB_RSTDIS 寄存器结构定义。地址偏移量:0x03D4，初值:0x00000000，宽度:32
 寄存器说明: BBIT MODEM子系统全局复位禁止寄存器。用于禁止外设复位。对比特写1，对应外设解除复位；写0不影响复位使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_bbit_modem_glb_rstdis : 1;  /* bit[0]   : 仅用于FPGA BBIT平台Modem全局软复位 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 复位禁止定义如下（写1复位解除）。 */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_fpga_bbit_modem_glb_rstdis_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTDIS_fpga_bbit_modem_glb_rstdis_END    (0)


/*****************************************************************************
 结构名    : SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_UNION
 结构说明  : MDMSC_BBIT_GLB_RSTEN_STAT 寄存器结构定义。地址偏移量:0x03D8，初值:0x00000000，宽度:32
 寄存器说明: BBIT MODEM子系统全局复位状态寄存器。用于回读各外设复位的状态。外设复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpga_bbit_modem_glb_rsten_stat : 1;  /* bit[0]   : 仅用于FPGA BBIT平台Modem全局软复位 */
        unsigned int  reserved                       : 31; /* bit[1-31]: 复位状态定义如下（高电平表示处于复位） */
    } reg;
} SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_UNION;
#endif
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_fpga_bbit_modem_glb_rsten_stat_START  (0)
#define SOC_MODEM_SCTRL_MDMSC_BBIT_GLB_RSTEN_STAT_fpga_bbit_modem_glb_rsten_stat_END    (0)






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

#endif /* end of soc_modem_sctrl_interface.h */
