/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_iomcu_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:19
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_IOMCU.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_IOMCU_INTERFACE_H__
#define __SOC_IOMCU_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* 寄存器说明：IOMCU时钟选择寄存器，用于选择时钟。
   位域定义UNION结构:  SOC_IOMCU_CLK_SEL_UNION */
#define SOC_IOMCU_CLK_SEL_ADDR(base)                  ((base) + (0x000))

/* 寄存器说明：IOMCU分频寄存器0
   位域定义UNION结构:  SOC_IOMCU_CFG_DIV0_UNION */
#define SOC_IOMCU_CFG_DIV0_ADDR(base)                 ((base) + (0x004))

/* 寄存器说明：IOMCU分频寄存器1
   位域定义UNION结构:  SOC_IOMCU_CFG_DIV1_UNION */
#define SOC_IOMCU_CFG_DIV1_ADDR(base)                 ((base) + (0x008))

/* 寄存器说明：RTC时钟配置寄存器
   位域定义UNION结构:  SOC_IOMCU_RTC_CFG_UNION */
#define SOC_IOMCU_RTC_CFG_ADDR(base)                  ((base) + (0x00C))

/* 寄存器说明：IOMCU分区时钟使能寄存器0。对比特写1，使能IOMCU_CLKSTAT0对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_IOMCU_CLKEN0_UNION */
#define SOC_IOMCU_CLKEN0_ADDR(base)                   ((base) + (0x010))

/* 寄存器说明：IOMCU分区时钟使能寄存器0。对比特写1，使能IOMCU_CLKSTAT0对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_IOMCU_CLKDIS0_UNION */
#define SOC_IOMCU_CLKDIS0_ADDR(base)                  ((base) + (0x014))

/* 寄存器说明：IOMCU分区时钟状态寄存器0。由IOMCU_CLKEN0和IOMCU_CLKDIS0配置进行状态修改。
            外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
            此寄存器还影响到防挂死逻辑，当时钟关闭时且防挂死不bypass情况下，防挂死逻辑生效，内部总线返回pslverr信号。
            每个Bit含义：
            0：时钟关闭；
            1：时钟打开。
   位域定义UNION结构:  SOC_IOMCU_CLKSTAT0_UNION */
#define SOC_IOMCU_CLKSTAT0_ADDR(base)                 ((base) + (0x018))

/* 寄存器说明：IOMCU分区复位使能寄存器0。用于使能IOMCU_RSTSTAT0复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
   位域定义UNION结构:  SOC_IOMCU_RSTEN0_UNION */
#define SOC_IOMCU_RSTEN0_ADDR(base)                   ((base) + (0x020))

/* 寄存器说明：IOMCU分区复位使能寄存器0。用于使能IOMCU_RSTSTAT0复位。对比特写1，对应IP进入解复位状态；写0不影响复位状态。
   位域定义UNION结构:  SOC_IOMCU_RSTDIS0_UNION */
#define SOC_IOMCU_RSTDIS0_ADDR(base)                  ((base) + (0x024))

/* 寄存器说明：ALWAYSON分区设复位状态寄存器4。由SC_PERIPH_RSTEN4和SC_PERIPH_RSTDIS4配置进行状态修改。解复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
            此寄存器还影响到防挂死逻辑，当相关逻辑处于复位状态时且防挂死不bypass情况下，防挂死逻辑生效，内部总线返回pslverr信号。
            每个Bit含义：
            0：复位不使能；
            1：复位使能。
   位域定义UNION结构:  SOC_IOMCU_RSTSTAT0_UNION */
#define SOC_IOMCU_RSTSTAT0_ADDR(base)                 ((base) + (0x028))

/* 寄存器说明：IOMCU M7配置寄存器
   位域定义UNION结构:  SOC_IOMCU_M7_CFG0_UNION */
#define SOC_IOMCU_M7_CFG0_ADDR(base)                  ((base) + (0x030))

/* 寄存器说明：IOMCU M7配置寄存器
   位域定义UNION结构:  SOC_IOMCU_M7_CFG1_UNION */
#define SOC_IOMCU_M7_CFG1_ADDR(base)                  ((base) + (0x034))

/* 寄存器说明：IOMCU M7状态寄存器
   位域定义UNION结构:  SOC_IOMCU_M7_STAT0_UNION */
#define SOC_IOMCU_M7_STAT0_ADDR(base)                 ((base) + (0x038))

/* 寄存器说明：IOMCU M7状态寄存器
   位域定义UNION结构:  SOC_IOMCU_M7_STAT1_UNION */
#define SOC_IOMCU_M7_STAT1_ADDR(base)                 ((base) + (0x03C))

/* 寄存器说明：M3访问DDR的滑动窗口设置寄存器
   位域定义UNION结构:  SOC_IOMCU_DDR_ACCESS_WINDOW_UNION */
#define SOC_IOMCU_DDR_ACCESS_WINDOW_ADDR(base)        ((base) + (0x040))

/* 寄存器说明：M3访问MMBUF的滑动窗口设置寄存器
   位域定义UNION结构:  SOC_IOMCU_MMBUF_ACCESS_WINDOW_UNION */
#define SOC_IOMCU_MMBUF_ACCESS_WINDOW_ADDR(base)      ((base) + (0x044))

/* 寄存器说明：M3访问HACK的滑动窗口设置寄存器
   位域定义UNION结构:  SOC_IOMCU_HACK_ACCESS_WINDOW_UNION */
#define SOC_IOMCU_HACK_ACCESS_WINDOW_ADDR(base)       ((base) + (0x048))

/* 寄存器说明：防死锁逻辑bypass控制寄存器
   位域定义UNION结构:  SOC_IOMCU_DLOCK_BYPASS_UNION */
#define SOC_IOMCU_DLOCK_BYPASS_ADDR(base)             ((base) + (0x04C))

/* 寄存器说明：mem功耗控制寄存器
   位域定义UNION结构:  SOC_IOMCU_MEM_CTRL_PGT_UNION */
#define SOC_IOMCU_MEM_CTRL_PGT_ADDR(base)             ((base) + (0x050))

/* 寄存器说明：mem参数控制寄存器
   位域定义UNION结构:  SOC_IOMCU_MEM_CTRL_UNION */
#define SOC_IOMCU_MEM_CTRL_ADDR(base)                 ((base) + (0x054))

/* 寄存器说明：IOMCU状态查询寄存器
   位域定义UNION结构:  SOC_IOMCU_SYS_STAT_UNION */
#define SOC_IOMCU_SYS_STAT_ADDR(base)                 ((base) + (0x058))

/* 寄存器说明：IOMCU配置控制寄存器
   位域定义UNION结构:  SOC_IOMCU_SYS_CONFIG_UNION */
#define SOC_IOMCU_SYS_CONFIG_ADDR(base)               ((base) + (0x05C))

/* 寄存器说明：IOMCU子系统唤醒中断寄存器
   位域定义UNION结构:  SOC_IOMCU_WAKEUP_EN_UNION */
#define SOC_IOMCU_WAKEUP_EN_ADDR(base)                ((base) + (0x060))

/* 寄存器说明：IOMCU子系统唤醒中断清除寄存器
   位域定义UNION结构:  SOC_IOMCU_WAKEUP_CLR_UNION */
#define SOC_IOMCU_WAKEUP_CLR_ADDR(base)               ((base) + (0x064))

/* 寄存器说明：IOMCU子系统唤醒中断清除寄存器
   位域定义UNION结构:  SOC_IOMCU_WAKEUP_STAT_UNION */
#define SOC_IOMCU_WAKEUP_STAT_ADDR(base)              ((base) + (0x068))

/* 寄存器说明：IOMCU输出的原始组合中断状态
   位域定义UNION结构:  SOC_IOMCU_COMB_INT_RAW_UNION */
#define SOC_IOMCU_COMB_INT_RAW_ADDR(base)             ((base) + (0x070))

/* 寄存器说明：IOMCU输出的组合中断状态
   位域定义UNION结构:  SOC_IOMCU_COMB_INT_MSK_UNION */
#define SOC_IOMCU_COMB_INT_MSK_ADDR(base)             ((base) + (0x074))

/* 寄存器说明：IOMCU输出的屏蔽后组合中断状态
   位域定义UNION结构:  SOC_IOMCU_COMB_INT_STAT_UNION */
#define SOC_IOMCU_COMB_INT_STAT_ADDR(base)            ((base) + (0x078))

/* 寄存器说明：IOMCU总线自动降频/关时钟寄存器
   位域定义UNION结构:  SOC_IOMCU_BUS_AUTO_FREQ_UNION */
#define SOC_IOMCU_BUS_AUTO_FREQ_ADDR(base)            ((base) + (0x080))

/* 寄存器说明：MISC逻辑里面的控制寄存器
   位域定义UNION结构:  SOC_IOMCU_MISC_CTRL_UNION */
#define SOC_IOMCU_MISC_CTRL_ADDR(base)                ((base) + (0x084))

/* 寄存器说明：NOC 相关信号的控制
   位域定义UNION结构:  SOC_IOMCU_NOC_CTRL_UNION */
#define SOC_IOMCU_NOC_CTRL_ADDR(base)                 ((base) + (0x088))

/* 寄存器说明：IOMCU M7配置寄存器2
   位域定义UNION结构:  SOC_IOMCU_M7_CFG2_UNION */
#define SOC_IOMCU_M7_CFG2_ADDR(base)                  ((base) + (0x08C))

/* 寄存器说明：IOMCU分区时钟使能寄存器1。对比特写1，使能IOMCU_CLKSTAT0对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_IOMCU_CLKEN1_UNION */
#define SOC_IOMCU_CLKEN1_ADDR(base)                   ((base) + (0x090))

/* 寄存器说明：IOMCU分区时钟使能寄存器1。对比特写1，使能IOMCU_CLKSTAT0对应的时钟；写0不影响时钟使能的状态。
   位域定义UNION结构:  SOC_IOMCU_CLKDIS1_UNION */
#define SOC_IOMCU_CLKDIS1_ADDR(base)                  ((base) + (0x094))

/* 寄存器说明：IOMCU分区时钟状态寄存器1。由IOMCU_CLKEN0和IOMCU_CLKDIS0配置进行状态修改。
            外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
            每个Bit含义：
            0：时钟关闭；
            1：时钟打开。
   位域定义UNION结构:  SOC_IOMCU_CLKSTAT1_UNION */
#define SOC_IOMCU_CLKSTAT1_ADDR(base)                 ((base) + (0x098))

/* 寄存器说明：安全TZPC位（绝对安全区域）0表示安全，1表示非安全。
   位域定义UNION结构:  SOC_IOMCU_SEC_TZPC_UNION */
#define SOC_IOMCU_SEC_TZPC_ADDR(base)                 ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_IOMCU_SEC_RES_UNION */
#define SOC_IOMCU_SEC_RES_ADDR(base)                  ((base) + (0x104))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_IOMCU_CLK_SEL_UNION
 结构说明  : CLK_SEL 寄存器结构定义。地址偏移量:0x000，初值:0x055558C5，宽度:32
 寄存器说明: IOMCU时钟选择寄存器，用于选择时钟。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clk_mcu_sel         : 2;  /* bit[0-1]  : Cortex M7时钟源选择：
                                                               2'b00:32K；
                                                               2'b01:TCX0；
                                                               2'b10:PPLL0；
                                                               2'b11:FLL */
        unsigned int  clk_mcu_sel_stat    : 2;  /* bit[2-3]  : Cortex M7时钟源状态：
                                                               2'b00:32K；
                                                               2'b01:TCX0；
                                                               2'b10:PPLL0；
                                                               2'b11:FLL */
        unsigned int  clk_mmbuf_sel       : 2;  /* bit[4-5]  : MMBUF的时钟切换 
                                                               00：TCXO
                                                               01：FPLL
                                                               1x: PPLL0 */
        unsigned int  clk_mmbuf_sel_stat  : 2;  /* bit[6-7]  : MMBUF的时钟切换状态
                                                               00：TCXO
                                                               01：FPLL
                                                               1x: PPLL0 */
        unsigned int  clk_nocbus_sel      : 2;  /* bit[8-9]  : AO_BUS的时钟切换
                                                               00：TCXO
                                                               01：FPLL
                                                               10：DDRPLL
                                                               11: PPLL0 */
        unsigned int  clk_nocbus_sel_stat : 2;  /* bit[10-11]: AO_BUS的时钟切换状态
                                                               00：TCXO
                                                               01：FPLL
                                                               10：DDRPLL
                                                               11: PPLL0 */
        unsigned int  clk_peri0_sel       : 2;  /* bit[12-13]: IOMCU Peir0(UART)时钟源选择：
                                                               2'b00:FLL；
                                                               2'b01:TCXO；
                                                               2'b10:PPLL0；
                                                               2'b11:Reserved */
        unsigned int  clk_peri1_sel       : 2;  /* bit[14-15]: IOMCU Peir1(SPI)时钟源选择：
                                                               2'b00:FLL；
                                                               2'b01:TCXO；
                                                               2'b10:PPLL0；
                                                               2'b11:Reserved */
        unsigned int  clk_peri2_sel       : 2;  /* bit[16-17]: IOMCU Peir2(I2C)时钟源选择：
                                                               2'b00:FLL；
                                                               2'b01:TCXO；
                                                               2'b10:PPLL0；
                                                               2'b11:Reserved */
        unsigned int  clk_peri3_sel       : 2;  /* bit[18-19]: IOMCU Peir3(BLPWM)时钟源选择：
                                                               2'b00:FLL；
                                                               2'b01:TCXO；
                                                               2'b10:PPLL0；
                                                               2'b11:Reserved */
        unsigned int  clk_peri0_sel_stat  : 2;  /* bit[20-21]: IOMCU Peir0(UART)时钟源状态：
                                                               2'b00:FLL；
                                                               2'b01:TCXO；
                                                               2'b10:PPLL0；
                                                               2'b11:Reserved */
        unsigned int  clk_peri1_sel_stat  : 2;  /* bit[22-23]: IOMCU Peir1(SPI)时钟源状态：
                                                               2'b00:FLL；
                                                               2'b01:TCXO；
                                                               2'b10:PPLL0；
                                                               2'b11:Reserved */
        unsigned int  clk_peri2_sel_stat  : 2;  /* bit[24-25]: IOMCU Peir2(I2C)时钟源状态：
                                                               2'b00:FLL；
                                                               2'b01:TCXO；
                                                               2'b10:PPLL0；
                                                               2'b11:Reserved */
        unsigned int  clk_peri3_sel_stat  : 2;  /* bit[26-27]: IOMCU Peir3(BLPWM)时钟源状态：
                                                               2'b00:FLL；
                                                               2'b01:TCXO；
                                                               2'b10:PPLL0；
                                                               2'b11:Reserved */
        unsigned int  clk_pll_stable      : 1;  /* bit[28]   : IOMCU外部PLL稳定信号 */
        unsigned int  clk_fll_stable      : 1;  /* bit[29]   : IOMCU外部FLL稳定信号 */
        unsigned int  reserved            : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_IOMCU_CLK_SEL_UNION;
#endif
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_START          (0)
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_END            (1)
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_stat_START     (2)
#define SOC_IOMCU_CLK_SEL_clk_mcu_sel_stat_END       (3)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_START        (4)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_END          (5)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_stat_START   (6)
#define SOC_IOMCU_CLK_SEL_clk_mmbuf_sel_stat_END     (7)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_START       (8)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_END         (9)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_stat_START  (10)
#define SOC_IOMCU_CLK_SEL_clk_nocbus_sel_stat_END    (11)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_START        (12)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_END          (13)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_START        (14)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_END          (15)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_START        (16)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_END          (17)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_START        (18)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_END          (19)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_stat_START   (20)
#define SOC_IOMCU_CLK_SEL_clk_peri0_sel_stat_END     (21)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_stat_START   (22)
#define SOC_IOMCU_CLK_SEL_clk_peri1_sel_stat_END     (23)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_stat_START   (24)
#define SOC_IOMCU_CLK_SEL_clk_peri2_sel_stat_END     (25)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_stat_START   (26)
#define SOC_IOMCU_CLK_SEL_clk_peri3_sel_stat_END     (27)
#define SOC_IOMCU_CLK_SEL_clk_pll_stable_START       (28)
#define SOC_IOMCU_CLK_SEL_clk_pll_stable_END         (28)
#define SOC_IOMCU_CLK_SEL_clk_fll_stable_START       (29)
#define SOC_IOMCU_CLK_SEL_clk_fll_stable_END         (29)


/*****************************************************************************
 结构名    : SOC_IOMCU_CFG_DIV0_UNION
 结构说明  : CFG_DIV0 寄存器结构定义。地址偏移量:0x004，初值:0x07151515，宽度:32
 寄存器说明: IOMCU分频寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_mcu0_div        : 2;  /* bit[0-1]  : Cortex M7主时钟分频器双层分频第一层的分频系数 */
        unsigned int  iomcu_apb_l_div_pre   : 2;  /* bit[2-3]  : IOMCU子系统内低速APB总时钟双层分频器第一层的分频系数 */
        unsigned int  iomcu_apb_l_div       : 2;  /* bit[4-5]  : IOMCU子系统内低速APB总时钟双层分频器第二层的分频系数 */
        unsigned int  reserved_0            : 1;  /* bit[6]    : reserved */
        unsigned int  iomcu_apb_l_div_en    : 1;  /* bit[7]    : 前0~6位的使能 */
        unsigned int  iomcu_apb_h_div       : 2;  /* bit[8-9]  : IOMCU子系统内高速APB总时钟分频器分频系数 */
        unsigned int  iomcu_mcu1_div        : 2;  /* bit[10-11]: Cortex M7主时钟分频器双层分频中第二层的分频系数 */
        unsigned int  iomcu_peri0_div       : 2;  /* bit[12-13]: IOMCU子系统内PERI0（UART）外设时钟分频器分频系数 */
        unsigned int  reserved_1            : 1;  /* bit[14]   : reserved */
        unsigned int  iomcu_peri_ahb_div_en : 1;  /* bit[15]   : 前7~14bit位的使能 */
        unsigned int  iomcu_peri1_div       : 2;  /* bit[16-17]: IOMCU子系统内PERI1(SPI)外设时钟分频器分频系数 */
        unsigned int  iomcu_peri2_div       : 2;  /* bit[18-19]: IOMCU子系统内PERI2(I2C)外设时钟分频器分频系数 */
        unsigned int  iomcu_peri3_div       : 2;  /* bit[20-21]: IOMCU子系统内PERI3(BLPWM)外设时钟分频器分频系数 */
        unsigned int  reserved_2            : 1;  /* bit[22]   : reserved */
        unsigned int  iomcu_peri_div_en     : 1;  /* bit[23]   : 前15~22bit位的使能 */
        unsigned int  iomcu_div             : 6;  /* bit[24-29]: IOMCU子系统内输入PPLL0时钟分频器分频系数 */
        unsigned int  reserved_3            : 1;  /* bit[30]   : reserved */
        unsigned int  iomcu_div_en          : 1;  /* bit[31]   : IOMCU子系统内输入PPLL0时钟分频器分频系数使能 */
    } reg;
} SOC_IOMCU_CFG_DIV0_UNION;
#endif
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu0_div_START         (0)
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu0_div_END           (1)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_pre_START    (2)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_pre_END      (3)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_START        (4)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_END          (5)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_en_START     (7)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_l_div_en_END       (7)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_h_div_START        (8)
#define SOC_IOMCU_CFG_DIV0_iomcu_apb_h_div_END          (9)
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu1_div_START         (10)
#define SOC_IOMCU_CFG_DIV0_iomcu_mcu1_div_END           (11)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri0_div_START        (12)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri0_div_END          (13)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_ahb_div_en_START  (15)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_ahb_div_en_END    (15)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri1_div_START        (16)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri1_div_END          (17)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri2_div_START        (18)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri2_div_END          (19)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri3_div_START        (20)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri3_div_END          (21)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_div_en_START      (23)
#define SOC_IOMCU_CFG_DIV0_iomcu_peri_div_en_END        (23)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_START              (24)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_END                (29)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_en_START           (31)
#define SOC_IOMCU_CFG_DIV0_iomcu_div_en_END             (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_CFG_DIV1_UNION
 结构说明  : CFG_DIV1 寄存器结构定义。地址偏移量:0x008，初值:0x0000000F，宽度:32
 寄存器说明: IOMCU分频寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_mcu0_div_nopending : 2;  /* bit[0-1]  : Cortex M7主时钟在总线idle态双层分频器第一次分频系数 */
        unsigned int  iomcu_mcu1_div_nopending : 2;  /* bit[2-3]  : Cortex M7主时钟在总线idle态双层分频器第二层分频系数 */
        unsigned int  reserved_0               : 3;  /* bit[4-6]  : reserved */
        unsigned int  reserved_1               : 1;  /* bit[7]    : Cortex M7主时钟在总线idle态分频器分频系数配置使能 */
        unsigned int  reserved_2               : 7;  /* bit[8-14] : reserved */
        unsigned int  reserved_3               : 1;  /* bit[15]   : reserved */
        unsigned int  reserved_4               : 7;  /* bit[16-22]: reserved */
        unsigned int  reserved_5               : 1;  /* bit[23]   : reserved */
        unsigned int  reserved_6               : 7;  /* bit[24-30]: reserved */
        unsigned int  reserved_7               : 1;  /* bit[31]   : reserved */
    } reg;
} SOC_IOMCU_CFG_DIV1_UNION;
#endif
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu0_div_nopending_START  (0)
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu0_div_nopending_END    (1)
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu1_div_nopending_START  (2)
#define SOC_IOMCU_CFG_DIV1_iomcu_mcu1_div_nopending_END    (3)


/*****************************************************************************
 结构名    : SOC_IOMCU_RTC_CFG_UNION
 结构说明  : RTC_CFG 寄存器结构定义。地址偏移量:0x00C，初值:0x000024A2，宽度:32
 寄存器说明: RTC时钟配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtc_clk_sel       : 1;  /* bit[0]    : RTC时钟源选择：
                                                             0：19.2MHz/586
                                                             1：32768Hz */
        unsigned int  rtc_crc_clken     : 1;  /* bit[1]    : CRC模块的时钟使能 */
        unsigned int  reserved_0        : 2;  /* bit[2-3]  : reserved */
        unsigned int  rtc_div_quotient  : 11; /* bit[4-14] : RTC分频器的商数 */
        unsigned int  reserved_1        : 1;  /* bit[15]   : reserved */
        unsigned int  rtc_div_remainder : 10; /* bit[16-25]: RTC分频器的余数 */
        unsigned int  reserved_2        : 6;  /* bit[26-31]: reserved */
    } reg;
} SOC_IOMCU_RTC_CFG_UNION;
#endif
#define SOC_IOMCU_RTC_CFG_rtc_clk_sel_START        (0)
#define SOC_IOMCU_RTC_CFG_rtc_clk_sel_END          (0)
#define SOC_IOMCU_RTC_CFG_rtc_crc_clken_START      (1)
#define SOC_IOMCU_RTC_CFG_rtc_crc_clken_END        (1)
#define SOC_IOMCU_RTC_CFG_rtc_div_quotient_START   (4)
#define SOC_IOMCU_RTC_CFG_rtc_div_quotient_END     (14)
#define SOC_IOMCU_RTC_CFG_rtc_div_remainder_START  (16)
#define SOC_IOMCU_RTC_CFG_rtc_div_remainder_END    (25)


/*****************************************************************************
 结构名    : SOC_IOMCU_CLKEN0_UNION
 结构说明  : CLKEN0 寄存器结构定义。地址偏移量:0x010，初值:0x0367C000，宽度:32
 寄存器说明: IOMCU分区时钟使能寄存器0。对比特写1，使能IOMCU_CLKSTAT0对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clken0_0dmac         : 1;  /* bit[0] : 0dmac */
        unsigned int  iomcu_clken0_lwdt          : 1;  /* bit[1] : lwdt */
        unsigned int  iomcu_clken0_2timer        : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_clken0_3i2c0         : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_clken0_4i2c1         : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_clken0_5i2c2         : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_clken0_6gpio0        : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_clken0_7gpio1        : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_clken0_8gpio2        : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_clken0_9gpio3        : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_clken0_10spi0        : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_clken0_11uart3       : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_clken0_12uart7       : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_clken0_13blpwm       : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_clken0_14fclk_mcu    : 1;  /* bit[14]: 14fclk_mcu */
        unsigned int  iomcu_clken0_15clk_mcu     : 1;  /* bit[15]: 15clk_mcu */
        unsigned int  iomcu_clken0_16clk_etm     : 1;  /* bit[16]: 16clk_etm */
        unsigned int  iomcu_clken0_17aclk_mcu    : 1;  /* bit[17]: 17aclk_mcu */
        unsigned int  iomcu_clken0_18hclk_mcu    : 1;  /* bit[18]: 18hclk_mcu */
        unsigned int  iomcu_clken0_19clk_fll     : 1;  /* bit[19]: 19clk_fll */
        unsigned int  iomcu_clken0_20clk_ppll0   : 1;  /* bit[20]: 20clk_ppll0 */
        unsigned int  iomcu_clken0_21clk_dapb    : 1;  /* bit[21]: 21clk_dapb */
        unsigned int  iomcu_clken0_22clk_atb     : 1;  /* bit[22]: 22clk_atb */
        unsigned int  iomcu_clken0_23pclk_rtc    : 1;  /* bit[23]: 23pclk_rtc */
        unsigned int  iomcu_clken0_24clk_ctm     : 1;  /* bit[24]: 24clk_ctm */
        unsigned int  iomcu_clken0_25clk_tcxo_in : 1;  /* bit[25]: 25clk_tcxo_in */
        unsigned int  iomcu_clken0_26tcm         : 1;  /* bit[26]: 26tcm */
        unsigned int  iomcu_clken0_27i2c6        : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_clken0_28mmbuf       : 1;  /* bit[28]: 此位暂时不能配置 */
        unsigned int  iomcu_clken0_29ao_bus      : 1;  /* bit[29]: 此位暂时不能配置 */
        unsigned int  iomcu_clken0_30spi2        : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_clken0_31uart8       : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_CLKEN0_UNION;
#endif
#define SOC_IOMCU_CLKEN0_iomcu_clken0_0dmac_START          (0)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_0dmac_END            (0)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_lwdt_START           (1)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_lwdt_END             (1)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_2timer_START         (2)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_2timer_END           (2)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_3i2c0_START          (3)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_3i2c0_END            (3)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_4i2c1_START          (4)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_4i2c1_END            (4)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_5i2c2_START          (5)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_5i2c2_END            (5)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_6gpio0_START         (6)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_6gpio0_END           (6)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_7gpio1_START         (7)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_7gpio1_END           (7)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_8gpio2_START         (8)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_8gpio2_END           (8)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_9gpio3_START         (9)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_9gpio3_END           (9)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_10spi0_START         (10)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_10spi0_END           (10)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_11uart3_START        (11)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_11uart3_END          (11)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_12uart7_START        (12)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_12uart7_END          (12)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_13blpwm_START        (13)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_13blpwm_END          (13)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_14fclk_mcu_START     (14)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_14fclk_mcu_END       (14)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_15clk_mcu_START      (15)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_15clk_mcu_END        (15)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_16clk_etm_START      (16)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_16clk_etm_END        (16)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_17aclk_mcu_START     (17)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_17aclk_mcu_END       (17)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_18hclk_mcu_START     (18)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_18hclk_mcu_END       (18)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_19clk_fll_START      (19)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_19clk_fll_END        (19)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_20clk_ppll0_START    (20)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_20clk_ppll0_END      (20)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_21clk_dapb_START     (21)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_21clk_dapb_END       (21)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_22clk_atb_START      (22)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_22clk_atb_END        (22)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_23pclk_rtc_START     (23)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_23pclk_rtc_END       (23)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_24clk_ctm_START      (24)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_24clk_ctm_END        (24)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_25clk_tcxo_in_START  (25)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_25clk_tcxo_in_END    (25)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_26tcm_START          (26)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_26tcm_END            (26)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_27i2c6_START         (27)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_27i2c6_END           (27)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_28mmbuf_START        (28)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_28mmbuf_END          (28)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_29ao_bus_START       (29)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_29ao_bus_END         (29)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_30spi2_START         (30)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_30spi2_END           (30)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_31uart8_START        (31)
#define SOC_IOMCU_CLKEN0_iomcu_clken0_31uart8_END          (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_CLKDIS0_UNION
 结构说明  : CLKDIS0 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: IOMCU分区时钟使能寄存器0。对比特写1，使能IOMCU_CLKSTAT0对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clkdis0_0dmac         : 1;  /* bit[0] : 0dmac */
        unsigned int  iomcu_clkdis0_lwdt          : 1;  /* bit[1] : lwdt */
        unsigned int  iomcu_clkdis0_2timer        : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_clkdis0_3i2c0         : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_clkdis0_4i2c1         : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_clkdis0_5i2c2         : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_clkdis0_6gpio0        : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_clkdis0_7gpio1        : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_clkdis0_8gpio2        : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_clkdis0_9gpio3        : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_clkdis0_10spi0        : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_clkdis0_11uart3       : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_clkdis0_12uart7       : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_clkdis0_13blpwm       : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_clkdis0_14fclk_mcu    : 1;  /* bit[14]: 14fclk_mcu */
        unsigned int  iomcu_clkdis0_15clk_mcu     : 1;  /* bit[15]: 15clk_mcu */
        unsigned int  iomcu_clkdis0_16clk_etm     : 1;  /* bit[16]: 16clk_etm */
        unsigned int  iomcu_clkdis0_17aclk_mcu    : 1;  /* bit[17]: 17aclk_mcu */
        unsigned int  iomcu_clkdis0_18hclk_mcu    : 1;  /* bit[18]: 18hclk_mcu */
        unsigned int  iomcu_clkdis0_19clk_fll     : 1;  /* bit[19]: 19clk_fll */
        unsigned int  iomcu_clkdis0_20clk_ppll0   : 1;  /* bit[20]: 20clk_ppll0 */
        unsigned int  iomcu_clkdis0_21clk_dapb    : 1;  /* bit[21]: 21clk_dapb */
        unsigned int  iomcu_clkdis0_22clk_atb     : 1;  /* bit[22]: 22clk_atb */
        unsigned int  iomcu_clkdis0_23pclk_rtc    : 1;  /* bit[23]: 23pclk_rtc */
        unsigned int  iomcu_clkdis0_24clk_ctm     : 1;  /* bit[24]: 24clk_ctm */
        unsigned int  iomcu_clkdis0_25clk_tcxo_in : 1;  /* bit[25]: 25clk_tcxo_in */
        unsigned int  iomcu_clkdis0_26tcm         : 1;  /* bit[26]: 26tcm */
        unsigned int  iomcu_clkdis0_27i2c6        : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_clkdis0_28mmbuf       : 1;  /* bit[28]: 此位暂时不能配置 */
        unsigned int  iomcu_clkdis0_29ao_bus      : 1;  /* bit[29]: 此位暂时不能配置 */
        unsigned int  iomcu_clkdis0_30spi2        : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_clkdis0_31uart8       : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_CLKDIS0_UNION;
#endif
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_0dmac_START          (0)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_0dmac_END            (0)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_lwdt_START           (1)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_lwdt_END             (1)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_2timer_START         (2)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_2timer_END           (2)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_3i2c0_START          (3)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_3i2c0_END            (3)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_4i2c1_START          (4)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_4i2c1_END            (4)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_5i2c2_START          (5)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_5i2c2_END            (5)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_6gpio0_START         (6)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_6gpio0_END           (6)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_7gpio1_START         (7)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_7gpio1_END           (7)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_8gpio2_START         (8)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_8gpio2_END           (8)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_9gpio3_START         (9)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_9gpio3_END           (9)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_10spi0_START         (10)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_10spi0_END           (10)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_11uart3_START        (11)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_11uart3_END          (11)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_12uart7_START        (12)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_12uart7_END          (12)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_13blpwm_START        (13)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_13blpwm_END          (13)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_14fclk_mcu_START     (14)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_14fclk_mcu_END       (14)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_15clk_mcu_START      (15)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_15clk_mcu_END        (15)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_16clk_etm_START      (16)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_16clk_etm_END        (16)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_17aclk_mcu_START     (17)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_17aclk_mcu_END       (17)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_18hclk_mcu_START     (18)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_18hclk_mcu_END       (18)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_19clk_fll_START      (19)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_19clk_fll_END        (19)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_20clk_ppll0_START    (20)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_20clk_ppll0_END      (20)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_21clk_dapb_START     (21)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_21clk_dapb_END       (21)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_22clk_atb_START      (22)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_22clk_atb_END        (22)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_23pclk_rtc_START     (23)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_23pclk_rtc_END       (23)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_24clk_ctm_START      (24)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_24clk_ctm_END        (24)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_25clk_tcxo_in_START  (25)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_25clk_tcxo_in_END    (25)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_26tcm_START          (26)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_26tcm_END            (26)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_27i2c6_START         (27)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_27i2c6_END           (27)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_28mmbuf_START        (28)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_28mmbuf_END          (28)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_29ao_bus_START       (29)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_29ao_bus_END         (29)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_30spi2_START         (30)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_30spi2_END           (30)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_31uart8_START        (31)
#define SOC_IOMCU_CLKDIS0_iomcu_clkdis0_31uart8_END          (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_CLKSTAT0_UNION
 结构说明  : CLKSTAT0 寄存器结构定义。地址偏移量:0x018，初值:0x0367C000，宽度:32
 寄存器说明: IOMCU分区时钟状态寄存器0。由IOMCU_CLKEN0和IOMCU_CLKDIS0配置进行状态修改。
            外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
            此寄存器还影响到防挂死逻辑，当时钟关闭时且防挂死不bypass情况下，防挂死逻辑生效，内部总线返回pslverr信号。
            每个Bit含义：
            0：时钟关闭；
            1：时钟打开。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clkstat0_0dmac         : 1;  /* bit[0] : 0dmac */
        unsigned int  iomcu_clkstat0_lwdt          : 1;  /* bit[1] : lwdt */
        unsigned int  iomcu_clkstat0_2timer        : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_clkstat0_3i2c0         : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_clkstat0_4i2c1         : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_clkstat0_5i2c2         : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_clkstat0_6gpio0        : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_clkstat0_7gpio1        : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_clkstat0_8gpio2        : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_clkstat0_9gpio3        : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_clkstat0_10spi0        : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_clkstat0_11uart3       : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_clkstat0_12uart7       : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_clkstat0_13blpwm       : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_clkstat0_14fclk_mcu    : 1;  /* bit[14]: 14fclk_mcu */
        unsigned int  iomcu_clkstat0_15clk_mcu     : 1;  /* bit[15]: 15clk_mcu */
        unsigned int  iomcu_clkstat0_16clk_etm     : 1;  /* bit[16]: 16clk_etm */
        unsigned int  iomcu_clkstat0_17aclk_mcu    : 1;  /* bit[17]: 17aclk_mcu */
        unsigned int  iomcu_clkstat0_18hclk_mcu    : 1;  /* bit[18]: 18hclk_mcu */
        unsigned int  iomcu_clkstat0_19clk_fll     : 1;  /* bit[19]: 19clk_fll */
        unsigned int  iomcu_clkstat0_20clk_ppll0   : 1;  /* bit[20]: 20clk_ppll0 */
        unsigned int  iomcu_clkstat0_21clk_dapb    : 1;  /* bit[21]: 21clk_dapb */
        unsigned int  iomcu_clkstat0_22clk_atb     : 1;  /* bit[22]: 22clk_atb */
        unsigned int  iomcu_clkstat0_23pclk_rtc    : 1;  /* bit[23]: 23pclk_rtc */
        unsigned int  iomcu_clkstat0_24clk_ctm     : 1;  /* bit[24]: 24clk_ctm */
        unsigned int  iomcu_clkstat0_25clk_tcxo_in : 1;  /* bit[25]: 25clk_tcxo_in */
        unsigned int  iomcu_clkstat0_26tcm         : 1;  /* bit[26]: 26tcm */
        unsigned int  iomcu_clkstat0_27i2c6        : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_clkstat0_28mmbuf       : 1;  /* bit[28]: 此位暂时不能配置 */
        unsigned int  iomcu_clkstat0_29ao_bus      : 1;  /* bit[29]: 此位暂时不能配置 */
        unsigned int  iomcu_clkstat0_30spi2        : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_clkstat0_31uart8       : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_CLKSTAT0_UNION;
#endif
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_0dmac_START          (0)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_0dmac_END            (0)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_lwdt_START           (1)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_lwdt_END             (1)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_2timer_START         (2)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_2timer_END           (2)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_3i2c0_START          (3)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_3i2c0_END            (3)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_4i2c1_START          (4)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_4i2c1_END            (4)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_5i2c2_START          (5)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_5i2c2_END            (5)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_6gpio0_START         (6)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_6gpio0_END           (6)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_7gpio1_START         (7)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_7gpio1_END           (7)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_8gpio2_START         (8)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_8gpio2_END           (8)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_9gpio3_START         (9)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_9gpio3_END           (9)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_10spi0_START         (10)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_10spi0_END           (10)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_11uart3_START        (11)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_11uart3_END          (11)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_12uart7_START        (12)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_12uart7_END          (12)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_13blpwm_START        (13)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_13blpwm_END          (13)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_14fclk_mcu_START     (14)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_14fclk_mcu_END       (14)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_15clk_mcu_START      (15)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_15clk_mcu_END        (15)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_16clk_etm_START      (16)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_16clk_etm_END        (16)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_17aclk_mcu_START     (17)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_17aclk_mcu_END       (17)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_18hclk_mcu_START     (18)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_18hclk_mcu_END       (18)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_19clk_fll_START      (19)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_19clk_fll_END        (19)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_20clk_ppll0_START    (20)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_20clk_ppll0_END      (20)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_21clk_dapb_START     (21)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_21clk_dapb_END       (21)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_22clk_atb_START      (22)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_22clk_atb_END        (22)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_23pclk_rtc_START     (23)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_23pclk_rtc_END       (23)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_24clk_ctm_START      (24)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_24clk_ctm_END        (24)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_25clk_tcxo_in_START  (25)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_25clk_tcxo_in_END    (25)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_26tcm_START          (26)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_26tcm_END            (26)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_27i2c6_START         (27)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_27i2c6_END           (27)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_28mmbuf_START        (28)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_28mmbuf_END          (28)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_29ao_bus_START       (29)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_29ao_bus_END         (29)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_30spi2_START         (30)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_30spi2_END           (30)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_31uart8_START        (31)
#define SOC_IOMCU_CLKSTAT0_iomcu_clkstat0_31uart8_END          (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_RSTEN0_UNION
 结构说明  : RSTEN0 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: IOMCU分区复位使能寄存器0。用于使能IOMCU_RSTSTAT0复位。对比特写1，对应IP进入复位状态；写0不影响复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_rsten0_0dma       : 1;  /* bit[0] : 0dma */
        unsigned int  iomcu_rsten0_1wdt       : 1;  /* bit[1] : 1wdt */
        unsigned int  iomcu_rsten0_2timer     : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_rsten0_3i2c0      : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_rsten0_4i2c1      : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_rsten0_5i2c2      : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_rsten0_6gpio0     : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_rsten0_7gpio1     : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_rsten0_8gpio2     : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_rsten0_9gpio3     : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_rsten0_10spi0     : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_rsten0_11uart3    : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_rsten0_12uart7    : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_rsten0_13blpwm    : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_rsten0_14mcu_sys  : 1;  /* bit[14]: 14mcu_sys */
        unsigned int  iomcu_rsten0_15mcu_etm  : 1;  /* bit[15]: 15mcu_etm */
        unsigned int  iomcu_rsten0_16reserved : 1;  /* bit[16]: 16reserved */
        unsigned int  iomcu_rsten0_17reserved : 1;  /* bit[17]: 17reserved */
        unsigned int  iomcu_rsten0_18tcm      : 1;  /* bit[18]: 18tcm */
        unsigned int  iomcu_rsten0_19reserved : 1;  /* bit[19]: 19reserved */
        unsigned int  iomcu_rsten0_20reserved : 1;  /* bit[20]: 20reserved */
        unsigned int  iomcu_rsten0_21dapb     : 1;  /* bit[21]: 21dapb */
        unsigned int  iomcu_rsten0_22atb      : 1;  /* bit[22]: 22atb */
        unsigned int  iomcu_rsten0_23rtc      : 1;  /* bit[23]: 23rtc */
        unsigned int  iomcu_rsten0_24ctm      : 1;  /* bit[24]: 24ctm */
        unsigned int  iomcu_rsten0_25reserved : 1;  /* bit[25]: 25reserved */
        unsigned int  iomcu_rsten0_26reserved : 1;  /* bit[26]: 26reserved */
        unsigned int  iomcu_rsten0_27i2c6     : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_rsten0_28reserved : 1;  /* bit[28]: 28reserved */
        unsigned int  iomcu_rsten0_29reserved : 1;  /* bit[29]: 29reserved */
        unsigned int  iomcu_rsten0_30spi2     : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_rsten0_31uart8    : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_RSTEN0_UNION;
#endif
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_0dma_START        (0)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_0dma_END          (0)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_1wdt_START        (1)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_1wdt_END          (1)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_2timer_START      (2)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_2timer_END        (2)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_3i2c0_START       (3)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_3i2c0_END         (3)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_4i2c1_START       (4)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_4i2c1_END         (4)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_5i2c2_START       (5)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_5i2c2_END         (5)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_6gpio0_START      (6)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_6gpio0_END        (6)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_7gpio1_START      (7)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_7gpio1_END        (7)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_8gpio2_START      (8)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_8gpio2_END        (8)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_9gpio3_START      (9)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_9gpio3_END        (9)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_10spi0_START      (10)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_10spi0_END        (10)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_11uart3_START     (11)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_11uart3_END       (11)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_12uart7_START     (12)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_12uart7_END       (12)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_13blpwm_START     (13)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_13blpwm_END       (13)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_14mcu_sys_START   (14)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_14mcu_sys_END     (14)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_15mcu_etm_START   (15)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_15mcu_etm_END     (15)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_16reserved_START  (16)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_16reserved_END    (16)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_17reserved_START  (17)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_17reserved_END    (17)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_18tcm_START       (18)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_18tcm_END         (18)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_19reserved_START  (19)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_19reserved_END    (19)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_20reserved_START  (20)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_20reserved_END    (20)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_21dapb_START      (21)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_21dapb_END        (21)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_22atb_START       (22)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_22atb_END         (22)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_23rtc_START       (23)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_23rtc_END         (23)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_24ctm_START       (24)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_24ctm_END         (24)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_25reserved_START  (25)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_25reserved_END    (25)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_26reserved_START  (26)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_26reserved_END    (26)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_27i2c6_START      (27)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_27i2c6_END        (27)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_28reserved_START  (28)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_28reserved_END    (28)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_29reserved_START  (29)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_29reserved_END    (29)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_30spi2_START      (30)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_30spi2_END        (30)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_31uart8_START     (31)
#define SOC_IOMCU_RSTEN0_iomcu_rsten0_31uart8_END       (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_RSTDIS0_UNION
 结构说明  : RSTDIS0 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: IOMCU分区复位使能寄存器0。用于使能IOMCU_RSTSTAT0复位。对比特写1，对应IP进入解复位状态；写0不影响复位状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_rstdis0_0dma       : 1;  /* bit[0] : 0dma */
        unsigned int  iomcu_rstdis0_1wdt       : 1;  /* bit[1] : 1wdt */
        unsigned int  iomcu_rstdis0_2timer     : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_rstdis0_3i2c0      : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_rstdis0_4i2c1      : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_rstdis0_5i2c2      : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_rstdis0_6gpio0     : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_rstdis0_7gpio1     : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_rstdis0_8gpio2     : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_rstdis0_9gpio3     : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_rstdis0_10spi0     : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_rstdis0_11uart3    : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_rstdis0_12uart7    : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_rstdis0_13blpwm    : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_rstdis0_14mcu_sys  : 1;  /* bit[14]: 14mcu_sys */
        unsigned int  iomcu_rstdis0_15mcu_etm  : 1;  /* bit[15]: 15mcu_etm */
        unsigned int  iomcu_rstdis0_16reserved : 1;  /* bit[16]: 16reserved */
        unsigned int  iomcu_rstdis0_17reserved : 1;  /* bit[17]: 17reserved */
        unsigned int  iomcu_rstdis0_18tcm      : 1;  /* bit[18]: 18tcm */
        unsigned int  iomcu_rstdis0_19reserved : 1;  /* bit[19]: 19reserved */
        unsigned int  iomcu_rstdis0_20reserved : 1;  /* bit[20]: 20reserved */
        unsigned int  iomcu_rstdis0_21dapb     : 1;  /* bit[21]: 21dapb */
        unsigned int  iomcu_rstdis0_22atb      : 1;  /* bit[22]: 22atb */
        unsigned int  iomcu_rstdis0_23rtc      : 1;  /* bit[23]: 23rtc */
        unsigned int  iomcu_rstdis0_24ctm      : 1;  /* bit[24]: 24ctm */
        unsigned int  iomcu_rstdis0_25reserved : 1;  /* bit[25]: 25reserved */
        unsigned int  iomcu_rstdis0_26reserved : 1;  /* bit[26]: 26reserved */
        unsigned int  iomcu_rstdis0_27i2c6     : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_rstdis0_28reserved : 1;  /* bit[28]: 28reserved */
        unsigned int  iomcu_rstdis0_29reserved : 1;  /* bit[29]: 29reserved */
        unsigned int  iomcu_rstdis0_30spi2     : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_rstdis0_31uart8    : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_RSTDIS0_UNION;
#endif
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_0dma_START        (0)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_0dma_END          (0)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_1wdt_START        (1)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_1wdt_END          (1)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_2timer_START      (2)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_2timer_END        (2)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_3i2c0_START       (3)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_3i2c0_END         (3)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_4i2c1_START       (4)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_4i2c1_END         (4)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_5i2c2_START       (5)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_5i2c2_END         (5)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_6gpio0_START      (6)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_6gpio0_END        (6)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_7gpio1_START      (7)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_7gpio1_END        (7)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_8gpio2_START      (8)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_8gpio2_END        (8)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_9gpio3_START      (9)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_9gpio3_END        (9)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_10spi0_START      (10)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_10spi0_END        (10)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_11uart3_START     (11)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_11uart3_END       (11)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_12uart7_START     (12)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_12uart7_END       (12)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_13blpwm_START     (13)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_13blpwm_END       (13)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_14mcu_sys_START   (14)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_14mcu_sys_END     (14)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_15mcu_etm_START   (15)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_15mcu_etm_END     (15)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_16reserved_START  (16)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_16reserved_END    (16)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_17reserved_START  (17)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_17reserved_END    (17)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_18tcm_START       (18)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_18tcm_END         (18)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_19reserved_START  (19)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_19reserved_END    (19)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_20reserved_START  (20)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_20reserved_END    (20)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_21dapb_START      (21)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_21dapb_END        (21)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_22atb_START       (22)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_22atb_END         (22)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_23rtc_START       (23)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_23rtc_END         (23)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_24ctm_START       (24)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_24ctm_END         (24)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_25reserved_START  (25)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_25reserved_END    (25)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_26reserved_START  (26)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_26reserved_END    (26)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_27i2c6_START      (27)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_27i2c6_END        (27)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_28reserved_START  (28)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_28reserved_END    (28)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_29reserved_START  (29)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_29reserved_END    (29)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_30spi2_START      (30)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_30spi2_END        (30)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_31uart8_START     (31)
#define SOC_IOMCU_RSTDIS0_iomcu_rstdis0_31uart8_END       (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_RSTSTAT0_UNION
 结构说明  : RSTSTAT0 寄存器结构定义。地址偏移量:0x028，初值:0xC9E4FFFF，宽度:32
 寄存器说明: ALWAYSON分区设复位状态寄存器4。由SC_PERIPH_RSTEN4和SC_PERIPH_RSTDIS4配置进行状态修改。解复位控制信号需经过同步处理，因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应解复位状态。
            此寄存器还影响到防挂死逻辑，当相关逻辑处于复位状态时且防挂死不bypass情况下，防挂死逻辑生效，内部总线返回pslverr信号。
            每个Bit含义：
            0：复位不使能；
            1：复位使能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_rststats0_0dma       : 1;  /* bit[0] : 0dma */
        unsigned int  iomcu_rststats0_1wdt       : 1;  /* bit[1] : 1wdt */
        unsigned int  iomcu_rststats0_2timer     : 1;  /* bit[2] : 2timer */
        unsigned int  iomcu_rststats0_3i2c0      : 1;  /* bit[3] : 3i2c0 */
        unsigned int  iomcu_rststats0_4i2c1      : 1;  /* bit[4] : 4i2c1 */
        unsigned int  iomcu_rststats0_5i2c2      : 1;  /* bit[5] : 5i2c2 */
        unsigned int  iomcu_rststats0_6gpio0     : 1;  /* bit[6] : 6gpio0 */
        unsigned int  iomcu_rststats0_7gpio1     : 1;  /* bit[7] : 7gpio1 */
        unsigned int  iomcu_rststats0_8gpio2     : 1;  /* bit[8] : 8gpio2 */
        unsigned int  iomcu_rststats0_9gpio3     : 1;  /* bit[9] : 9gpio3 */
        unsigned int  iomcu_rststats0_10spi0     : 1;  /* bit[10]: 10spi0 */
        unsigned int  iomcu_rststats0_11uart3    : 1;  /* bit[11]: 11uart3 */
        unsigned int  iomcu_rststats0_12uart7    : 1;  /* bit[12]: 12uart7 */
        unsigned int  iomcu_rststats0_13blpwm    : 1;  /* bit[13]: 13blpwm */
        unsigned int  iomcu_rststats0_14mcu_sys  : 1;  /* bit[14]: 14mcu_sys */
        unsigned int  iomcu_rststats0_15mcu_etm  : 1;  /* bit[15]: 15mcu_etm */
        unsigned int  iomcu_rststats0_16reserved : 1;  /* bit[16]: 16reserved */
        unsigned int  iomcu_rststats0_17reserved : 1;  /* bit[17]: 17reserved */
        unsigned int  iomcu_rststats0_18tcm      : 1;  /* bit[18]: 18tcm */
        unsigned int  iomcu_rststats0_19reserved : 1;  /* bit[19]: 19reserved */
        unsigned int  iomcu_rststats0_20reserved : 1;  /* bit[20]: 20reserved */
        unsigned int  iomcu_rststats0_21dapb     : 1;  /* bit[21]: 21dapb */
        unsigned int  iomcu_rststats0_22atb      : 1;  /* bit[22]: 22atb */
        unsigned int  iomcu_rststats0_23rtc      : 1;  /* bit[23]: 23rtc */
        unsigned int  iomcu_rststats0_24ctm      : 1;  /* bit[24]: 24ctm */
        unsigned int  iomcu_rststats0_25reserved : 1;  /* bit[25]: 25reserved */
        unsigned int  iomcu_rststats0_26reserved : 1;  /* bit[26]: 26reserved */
        unsigned int  iomcu_rststats0_27i2c6     : 1;  /* bit[27]: 27i2c6 */
        unsigned int  iomcu_rststats0_28reserved : 1;  /* bit[28]: 28reserved */
        unsigned int  iomcu_rststats0_29reserved : 1;  /* bit[29]: 29reserved */
        unsigned int  iomcu_rststats0_30spi2     : 1;  /* bit[30]: 30spi2 */
        unsigned int  iomcu_rststat0_31uart8     : 1;  /* bit[31]: 31uart8 */
    } reg;
} SOC_IOMCU_RSTSTAT0_UNION;
#endif
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_0dma_START        (0)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_0dma_END          (0)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_1wdt_START        (1)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_1wdt_END          (1)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_2timer_START      (2)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_2timer_END        (2)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_3i2c0_START       (3)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_3i2c0_END         (3)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_4i2c1_START       (4)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_4i2c1_END         (4)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_5i2c2_START       (5)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_5i2c2_END         (5)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_6gpio0_START      (6)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_6gpio0_END        (6)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_7gpio1_START      (7)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_7gpio1_END        (7)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_8gpio2_START      (8)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_8gpio2_END        (8)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_9gpio3_START      (9)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_9gpio3_END        (9)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_10spi0_START      (10)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_10spi0_END        (10)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_11uart3_START     (11)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_11uart3_END       (11)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_12uart7_START     (12)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_12uart7_END       (12)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_13blpwm_START     (13)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_13blpwm_END       (13)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_14mcu_sys_START   (14)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_14mcu_sys_END     (14)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_15mcu_etm_START   (15)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_15mcu_etm_END     (15)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_16reserved_START  (16)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_16reserved_END    (16)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_17reserved_START  (17)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_17reserved_END    (17)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_18tcm_START       (18)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_18tcm_END         (18)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_19reserved_START  (19)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_19reserved_END    (19)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_20reserved_START  (20)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_20reserved_END    (20)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_21dapb_START      (21)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_21dapb_END        (21)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_22atb_START       (22)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_22atb_END         (22)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_23rtc_START       (23)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_23rtc_END         (23)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_24ctm_START       (24)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_24ctm_END         (24)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_25reserved_START  (25)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_25reserved_END    (25)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_26reserved_START  (26)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_26reserved_END    (26)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_27i2c6_START      (27)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_27i2c6_END        (27)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_28reserved_START  (28)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_28reserved_END    (28)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_29reserved_START  (29)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_29reserved_END    (29)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_30spi2_START      (30)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststats0_30spi2_END        (30)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststat0_31uart8_START      (31)
#define SOC_IOMCU_RSTSTAT0_iomcu_rststat0_31uart8_END        (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_M7_CFG0_UNION
 结构说明  : M7_CFG0 寄存器结构定义。地址偏移量:0x030，初值:0x00000003，宽度:32
 寄存器说明: IOMCU M7配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_wait               : 1;  /* bit[0]   : CPU IDLE控制，在接复位之后，需要让CPU处于IDLE态进行代码加载，完成之后再撤消此信号
                                                                 0：撤离IDLE
                                                                 1：进入IDLE */
        unsigned int  hclken_sleeping_bypass : 1;  /* bit[1]   : 针对于hclk_en:当M7处于sleeping态时，是否自动关闭M7的hclk时钟
                                                                 0：自动关闭M7的hclk时钟
                                                                 1：不自动关闭M7的hclk时钟 */
        unsigned int  reserved_0             : 1;  /* bit[2]   : reserved */
        unsigned int  cpu_iadbgprot          : 1;  /* bit[3]   : ??? */
        unsigned int  cpu_initvtor           : 25; /* bit[4-28]: M7向量表基地址 */
        unsigned int  ahbs_ready_error_clr   : 1;  /* bit[29]  : AHBS总线READY信号为低时发生操作错误状态清除信号，状态在IOMCU_M7_STA0[29]查看 */
        unsigned int  cfg_bigend             : 1;  /* bit[30]  : M7大小端的配置 */
        unsigned int  reserved_1             : 1;  /* bit[31]  : reserved */
    } reg;
} SOC_IOMCU_M7_CFG0_UNION;
#endif
#define SOC_IOMCU_M7_CFG0_cpu_wait_START                (0)
#define SOC_IOMCU_M7_CFG0_cpu_wait_END                  (0)
#define SOC_IOMCU_M7_CFG0_hclken_sleeping_bypass_START  (1)
#define SOC_IOMCU_M7_CFG0_hclken_sleeping_bypass_END    (1)
#define SOC_IOMCU_M7_CFG0_cpu_iadbgprot_START           (3)
#define SOC_IOMCU_M7_CFG0_cpu_iadbgprot_END             (3)
#define SOC_IOMCU_M7_CFG0_cpu_initvtor_START            (4)
#define SOC_IOMCU_M7_CFG0_cpu_initvtor_END              (28)
#define SOC_IOMCU_M7_CFG0_ahbs_ready_error_clr_START    (29)
#define SOC_IOMCU_M7_CFG0_ahbs_ready_error_clr_END      (29)
#define SOC_IOMCU_M7_CFG0_cfg_bigend_START              (30)
#define SOC_IOMCU_M7_CFG0_cfg_bigend_END                (30)


/*****************************************************************************
 结构名    : SOC_IOMCU_M7_CFG1_UNION
 结构说明  : M7_CFG1 寄存器结构定义。地址偏移量:0x034，初值:0xF8000148，宽度:32
 寄存器说明: IOMCU M7配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfgstcalib_cycclecnt   : 24; /* bit[0-23]: M7 tick时钟计数周期（32K时钟计数），默认10ms一个周期 */
        unsigned int  cfgstcalib_precision   : 1;  /* bit[24]  : M7内部计数精度 */
        unsigned int  cfgstcalib_ticken      : 1;  /* bit[25]  : M7是否使用外部计数 */
        unsigned int  halt_bypass            : 1;  /* bit[26]  : 当M7处于halt态时，Timer是否计数
                                                                 0：不计数
                                                                 1：计数 */
        unsigned int  hack_remap_bypass      : 1;  /* bit[27]  : 对hack_mem访问的remap操作是否bypass
                                                                 0：不bypass,对hack_mem的访问remap到MMBuf/Harq。
                                                                 1：bypass,对hack_mem的访问remap到DDR。 */
        unsigned int  mmbuf_remap_bypass     : 1;  /* bit[28]  : 对mmbuf访问的remap操作是否bypass
                                                                 0：不bypass,对mmbuf的访问remap到MMBuf/Harq。
                                                                 1：bypass,对mmbuf的访问remap到DDR。 */
        unsigned int  aclken_sleeping_bypass : 1;  /* bit[29]  : 针对于aclk_en:当M7处于sleeping态时，是否自动关闭M7的AXI时钟
                                                                 0：自动关闭M7的AXI时钟
                                                                 1：不自动关闭M7的AXI时钟 */
        unsigned int  deepsleeping_bypass    : 1;  /* bit[30]  : 当M7处于deepsleeping态时，是否自动关闭FLL
                                                                 0：自动关闭FLL
                                                                 1：不自动关闭FLL */
        unsigned int  clken_sleeping_bypass  : 1;  /* bit[31]  : 针对于clk_en:当M7处于sleeping态时，是否自动关闭M7的主时钟
                                                                 0：自动关闭M7的主时钟
                                                                 1：不自动关闭M7的主时钟 */
    } reg;
} SOC_IOMCU_M7_CFG1_UNION;
#endif
#define SOC_IOMCU_M7_CFG1_cfgstcalib_cycclecnt_START    (0)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_cycclecnt_END      (23)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_precision_START    (24)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_precision_END      (24)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_ticken_START       (25)
#define SOC_IOMCU_M7_CFG1_cfgstcalib_ticken_END         (25)
#define SOC_IOMCU_M7_CFG1_halt_bypass_START             (26)
#define SOC_IOMCU_M7_CFG1_halt_bypass_END               (26)
#define SOC_IOMCU_M7_CFG1_hack_remap_bypass_START       (27)
#define SOC_IOMCU_M7_CFG1_hack_remap_bypass_END         (27)
#define SOC_IOMCU_M7_CFG1_mmbuf_remap_bypass_START      (28)
#define SOC_IOMCU_M7_CFG1_mmbuf_remap_bypass_END        (28)
#define SOC_IOMCU_M7_CFG1_aclken_sleeping_bypass_START  (29)
#define SOC_IOMCU_M7_CFG1_aclken_sleeping_bypass_END    (29)
#define SOC_IOMCU_M7_CFG1_deepsleeping_bypass_START     (30)
#define SOC_IOMCU_M7_CFG1_deepsleeping_bypass_END       (30)
#define SOC_IOMCU_M7_CFG1_clken_sleeping_bypass_START   (31)
#define SOC_IOMCU_M7_CFG1_clken_sleeping_bypass_END     (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_M7_STAT0_UNION
 结构说明  : M7_STAT0 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: IOMCU M7状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m7_iaddr_stat         : 29; /* bit[0-28]: M7指令DW地址 */
        unsigned int  ahbs_ready_error_stat : 1;  /* bit[29]  : AHBS总线READY信号为低时发生操作的错误状态指示，同时配置IOMCU_M7_CFG0[29]将此状态清除 */
        unsigned int  cpu_halt_stat         : 1;  /* bit[30]  : CPU HALT状态指示 */
        unsigned int  cpu_lockup            : 1;  /* bit[31]  : CPU死锁指示 */
    } reg;
} SOC_IOMCU_M7_STAT0_UNION;
#endif
#define SOC_IOMCU_M7_STAT0_m7_iaddr_stat_START          (0)
#define SOC_IOMCU_M7_STAT0_m7_iaddr_stat_END            (28)
#define SOC_IOMCU_M7_STAT0_ahbs_ready_error_stat_START  (29)
#define SOC_IOMCU_M7_STAT0_ahbs_ready_error_stat_END    (29)
#define SOC_IOMCU_M7_STAT0_cpu_halt_stat_START          (30)
#define SOC_IOMCU_M7_STAT0_cpu_halt_stat_END            (30)
#define SOC_IOMCU_M7_STAT0_cpu_lockup_START             (31)
#define SOC_IOMCU_M7_STAT0_cpu_lockup_END               (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_M7_STAT1_UNION
 结构说明  : M7_STAT1 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: IOMCU M7状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m7_sleeping_stat     : 1;  /* bit[0]    : M7处理器Sleeping状态指示 */
        unsigned int  m7_deepsleeping_stat : 1;  /* bit[1]    : M7处理器DeepSleeping状态指示 */
        unsigned int  m7_ahbs_ready_stat   : 1;  /* bit[2]    : M7处理器Slave接口ready指示信号，当此信号为0时不允许对M7内部进行访问 */
        unsigned int  m7_axi_bypass        : 1;  /* bit[3]    : m7 axi口投票给Sctrl决定是否关闭AO_BUS/MMBuf对应的bypass信号，0代表Bypass,即不使用Nopending信号，直接AO降频MMBUF关时钟。（此功能Austin中不实现） */
        unsigned int  m7_ahb_bypass        : 1;  /* bit[4]    : m7 ahb口投票给Sctrl决定是否关闭AO_BUS/MMBuf对应的bypass信号，0代表Bypass,即不使用Nopending信号，直接AO降频MMBUF关时钟。（此功能Austin中不实现） */
        unsigned int  m7_dma_bypass        : 1;  /* bit[5]    : m7 dma口投票给Sctrl决定是否关闭AO_BUS/MMBuf对应的bypass信号，0代表Bypass,即不使用Nopending信号，直接AO降频MMBUF关时钟。（此功能Austin中不实现） */
        unsigned int  m7_sc_stat           : 9;  /* bit[6-14] : M7与系统控制器对接接口
                                                                第[6]bit输出给Sctrl，表征目前M7的状态是否为deepsleep */
        unsigned int  m7_etmpwrupreq       : 1;  /* bit[15]   : M7内部etmpwrupreq指示信号 */
        unsigned int  reserved             : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_IOMCU_M7_STAT1_UNION;
#endif
#define SOC_IOMCU_M7_STAT1_m7_sleeping_stat_START      (0)
#define SOC_IOMCU_M7_STAT1_m7_sleeping_stat_END        (0)
#define SOC_IOMCU_M7_STAT1_m7_deepsleeping_stat_START  (1)
#define SOC_IOMCU_M7_STAT1_m7_deepsleeping_stat_END    (1)
#define SOC_IOMCU_M7_STAT1_m7_ahbs_ready_stat_START    (2)
#define SOC_IOMCU_M7_STAT1_m7_ahbs_ready_stat_END      (2)
#define SOC_IOMCU_M7_STAT1_m7_axi_bypass_START         (3)
#define SOC_IOMCU_M7_STAT1_m7_axi_bypass_END           (3)
#define SOC_IOMCU_M7_STAT1_m7_ahb_bypass_START         (4)
#define SOC_IOMCU_M7_STAT1_m7_ahb_bypass_END           (4)
#define SOC_IOMCU_M7_STAT1_m7_dma_bypass_START         (5)
#define SOC_IOMCU_M7_STAT1_m7_dma_bypass_END           (5)
#define SOC_IOMCU_M7_STAT1_m7_sc_stat_START            (6)
#define SOC_IOMCU_M7_STAT1_m7_sc_stat_END              (14)
#define SOC_IOMCU_M7_STAT1_m7_etmpwrupreq_START        (15)
#define SOC_IOMCU_M7_STAT1_m7_etmpwrupreq_END          (15)


/*****************************************************************************
 结构名    : SOC_IOMCU_DDR_ACCESS_WINDOW_UNION
 结构说明  : DDR_ACCESS_WINDOW 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: M3访问DDR的滑动窗口设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddr_access_window : 32; /* bit[0-31]: M7对512MB DDR空间访问时，所加的滑动访问窗口 */
    } reg;
} SOC_IOMCU_DDR_ACCESS_WINDOW_UNION;
#endif
#define SOC_IOMCU_DDR_ACCESS_WINDOW_ddr_access_window_START  (0)
#define SOC_IOMCU_DDR_ACCESS_WINDOW_ddr_access_window_END    (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_MMBUF_ACCESS_WINDOW_UNION
 结构说明  : MMBUF_ACCESS_WINDOW 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: M3访问MMBUF的滑动窗口设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmbuf_access_window : 32; /* bit[0-31]: M7对256KB MMBUF空间访问时，所加的滑动访问窗口，配置范围在0x6000_0000~0x7FFF_FFFF。 */
    } reg;
} SOC_IOMCU_MMBUF_ACCESS_WINDOW_UNION;
#endif
#define SOC_IOMCU_MMBUF_ACCESS_WINDOW_mmbuf_access_window_START  (0)
#define SOC_IOMCU_MMBUF_ACCESS_WINDOW_mmbuf_access_window_END    (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_HACK_ACCESS_WINDOW_UNION
 结构说明  : HACK_ACCESS_WINDOW 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: M3访问HACK的滑动窗口设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hack_access_window : 32; /* bit[0-31]: M7对2MB Hack Mem空间访问时，所加的滑动访问窗口，配置范围在0x6000_0000~0x7FFF_FFFF */
    } reg;
} SOC_IOMCU_HACK_ACCESS_WINDOW_UNION;
#endif
#define SOC_IOMCU_HACK_ACCESS_WINDOW_hack_access_window_START  (0)
#define SOC_IOMCU_HACK_ACCESS_WINDOW_hack_access_window_END    (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_DLOCK_BYPASS_UNION
 结构说明  : DLOCK_BYPASS 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: 防死锁逻辑bypass控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass_for_watchdog : 1;  /* bit[0]    : Watchdog配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_timer    : 1;  /* bit[1]    : Timer配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_spi      : 1;  /* bit[2]    : spi配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_gpio0    : 1;  /* bit[3]    : gpio0配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_gpio1    : 1;  /* bit[4]    : gpio1配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_gpio2    : 1;  /* bit[5]    : gpio2配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_gpio3    : 1;  /* bit[6]    : gpio3配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_i2c0     : 1;  /* bit[7]    : i2c0配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_i2c1     : 1;  /* bit[8]    : i2c1配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_i2c2     : 1;  /* bit[9]    : i2c2配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_uart3    : 1;  /* bit[10]   : uart3配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_blpwm    : 1;  /* bit[11]   : blpwm配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_uart7    : 1;  /* bit[12]   : uart7配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_dma      : 1;  /* bit[13]   : dma配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_rtc      : 1;  /* bit[14]   : rtc配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_i2c6     : 1;  /* bit[15]   : i2c6配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_uart8    : 1;  /* bit[16]   : uart8配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_spi2     : 1;  /* bit[17]   : spi2配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_tcm      : 1;  /* bit[18]   : tcm配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  reserved            : 13; /* bit[19-31]: Reserved */
    } reg;
} SOC_IOMCU_DLOCK_BYPASS_UNION;
#endif
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_watchdog_START  (0)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_watchdog_END    (0)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_timer_START     (1)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_timer_END       (1)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi_START       (2)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi_END         (2)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio0_START     (3)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio0_END       (3)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio1_START     (4)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio1_END       (4)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio2_START     (5)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio2_END       (5)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio3_START     (6)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_gpio3_END       (6)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c0_START      (7)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c0_END        (7)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c1_START      (8)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c1_END        (8)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c2_START      (9)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c2_END        (9)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart3_START     (10)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart3_END       (10)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_blpwm_START     (11)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_blpwm_END       (11)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart7_START     (12)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart7_END       (12)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_dma_START       (13)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_dma_END         (13)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_rtc_START       (14)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_rtc_END         (14)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c6_START      (15)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_i2c6_END        (15)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart8_START     (16)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_uart8_END       (16)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi2_START      (17)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_spi2_END        (17)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_tcm_START       (18)
#define SOC_IOMCU_DLOCK_BYPASS_bypass_for_tcm_END         (18)


/*****************************************************************************
 结构名    : SOC_IOMCU_MEM_CTRL_PGT_UNION
 结构说明  : MEM_CTRL_PGT 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: mem功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_bank0     : 3;  /* bit[0-2]  : bank0 mem功耗控制
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_0         : 1;  /* bit[3]    : reserved */
        unsigned int  mem_ctrl_bank1     : 3;  /* bit[4-6]  : bank1 mem功耗控制
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_1         : 1;  /* bit[7]    : reserved */
        unsigned int  mem_ctrl_bank2     : 3;  /* bit[8-10] : bank2 mem功耗控制
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_2         : 1;  /* bit[11]   : reserved */
        unsigned int  mem_ctrl_bank3     : 3;  /* bit[12-14]: bank3 mem功耗控制
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_3         : 1;  /* bit[15]   : reserved */
        unsigned int  mem_ctrl_bank4     : 3;  /* bit[16-18]: bank4 mem功耗控制
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_4         : 1;  /* bit[19]   : reserved */
        unsigned int  mem_ctrl_icache    : 3;  /* bit[20-22]: icache mem功耗控制
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_5         : 1;  /* bit[23]   : reserved */
        unsigned int  mem_ctrl_dcache    : 3;  /* bit[24-26]: dcache mem功耗控制
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_6         : 1;  /* bit[27]   : reserved */
        unsigned int  mem_ctrl_map_table : 3;  /* bit[28-30]: map_table mem功耗控制
                                                              [2]:SD
                                                              [1]:DSLP
                                                              [0]:SLP */
        unsigned int  reserved_7         : 1;  /* bit[31]   : reserved */
    } reg;
} SOC_IOMCU_MEM_CTRL_PGT_UNION;
#endif
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank0_START      (0)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank0_END        (2)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank1_START      (4)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank1_END        (6)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank2_START      (8)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank2_END        (10)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank3_START      (12)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank3_END        (14)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank4_START      (16)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_bank4_END        (18)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_icache_START     (20)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_icache_END       (22)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_dcache_START     (24)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_dcache_END       (26)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_map_table_START  (28)
#define SOC_IOMCU_MEM_CTRL_PGT_mem_ctrl_map_table_END    (30)


/*****************************************************************************
 结构名    : SOC_IOMCU_MEM_CTRL_UNION
 结构说明  : MEM_CTRL 寄存器结构定义。地址偏移量:0x054，初值:0x00003554，宽度:32
 寄存器说明: mem参数控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcm_wtsel   : 2;  /* bit[0-1]  : TCM memory写参数控制 */
        unsigned int  tcm_rtsel   : 2;  /* bit[2-3]  : TCM memory读参数控制 */
        unsigned int  cache_wtsel : 2;  /* bit[4-5]  : Cache memory写参数控制 */
        unsigned int  cache_rtsel : 2;  /* bit[6-7]  : Cache memory读参数控制 */
        unsigned int  tp_rct      : 2;  /* bit[8-9]  : Two Port memory参数控制 */
        unsigned int  tp_wct      : 2;  /* bit[10-11]: Two Port memory参数控制 */
        unsigned int  tp_kp       : 3;  /* bit[12-14]: Two Port memory参数控制 */
        unsigned int  reserved    : 17; /* bit[15-31]: Memory参数控制 */
    } reg;
} SOC_IOMCU_MEM_CTRL_UNION;
#endif
#define SOC_IOMCU_MEM_CTRL_tcm_wtsel_START    (0)
#define SOC_IOMCU_MEM_CTRL_tcm_wtsel_END      (1)
#define SOC_IOMCU_MEM_CTRL_tcm_rtsel_START    (2)
#define SOC_IOMCU_MEM_CTRL_tcm_rtsel_END      (3)
#define SOC_IOMCU_MEM_CTRL_cache_wtsel_START  (4)
#define SOC_IOMCU_MEM_CTRL_cache_wtsel_END    (5)
#define SOC_IOMCU_MEM_CTRL_cache_rtsel_START  (6)
#define SOC_IOMCU_MEM_CTRL_cache_rtsel_END    (7)
#define SOC_IOMCU_MEM_CTRL_tp_rct_START       (8)
#define SOC_IOMCU_MEM_CTRL_tp_rct_END         (9)
#define SOC_IOMCU_MEM_CTRL_tp_wct_START       (10)
#define SOC_IOMCU_MEM_CTRL_tp_wct_END         (11)
#define SOC_IOMCU_MEM_CTRL_tp_kp_START        (12)
#define SOC_IOMCU_MEM_CTRL_tp_kp_END          (14)


/*****************************************************************************
 结构名    : SOC_IOMCU_SYS_STAT_UNION
 结构说明  : SYS_STAT 寄存器结构定义。地址偏移量:0x058，初值:0x00000002，宽度:32
 寄存器说明: IOMCU状态查询寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sys_stat   : 4;  /* bit[0-3] : 用于指示系统状态 */
        unsigned int  xtal_ready : 2;  /* bit[4-5] : 用于分别指示两个晶振状态是否已经稳定 */
        unsigned int  reserved   : 26; /* bit[6-31]: reserved */
    } reg;
} SOC_IOMCU_SYS_STAT_UNION;
#endif
#define SOC_IOMCU_SYS_STAT_sys_stat_START    (0)
#define SOC_IOMCU_SYS_STAT_sys_stat_END      (3)
#define SOC_IOMCU_SYS_STAT_xtal_ready_START  (4)
#define SOC_IOMCU_SYS_STAT_xtal_ready_END    (5)


/*****************************************************************************
 结构名    : SOC_IOMCU_SYS_CONFIG_UNION
 结构说明  : SYS_CONFIG 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: IOMCU配置控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sleep_mode : 1;  /* bit[0]   : IOMCU在系统进入Sleep模式下进行配置。
                                                     1'b1:关闭TCXO
                                                     1'b0:不关闭TCXO */
        unsigned int  ppll0_en   : 1;  /* bit[1]   : 配置PPLL0的使能信号 */
        unsigned int  fll_en     : 1;  /* bit[2]   : 配置FLL的使能信号 */
        unsigned int  reserved   : 29; /* bit[3-31]: reserved */
    } reg;
} SOC_IOMCU_SYS_CONFIG_UNION;
#endif
#define SOC_IOMCU_SYS_CONFIG_sleep_mode_START  (0)
#define SOC_IOMCU_SYS_CONFIG_sleep_mode_END    (0)
#define SOC_IOMCU_SYS_CONFIG_ppll0_en_START    (1)
#define SOC_IOMCU_SYS_CONFIG_ppll0_en_END      (1)
#define SOC_IOMCU_SYS_CONFIG_fll_en_START      (2)
#define SOC_IOMCU_SYS_CONFIG_fll_en_END        (2)


/*****************************************************************************
 结构名    : SOC_IOMCU_WAKEUP_EN_UNION
 结构说明  : WAKEUP_EN 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: IOMCU子系统唤醒中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wakeup_en   : 1;  /* bit[0]   : IOMCU子系统唤醒中断使能 */
        unsigned int  soft_int_en : 1;  /* bit[1]   : TCXO组合唤醒中断中软件中断使能 */
        unsigned int  reserved    : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_IOMCU_WAKEUP_EN_UNION;
#endif
#define SOC_IOMCU_WAKEUP_EN_wakeup_en_START    (0)
#define SOC_IOMCU_WAKEUP_EN_wakeup_en_END      (0)
#define SOC_IOMCU_WAKEUP_EN_soft_int_en_START  (1)
#define SOC_IOMCU_WAKEUP_EN_soft_int_en_END    (1)


/*****************************************************************************
 结构名    : SOC_IOMCU_WAKEUP_CLR_UNION
 结构说明  : WAKEUP_CLR 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: IOMCU子系统唤醒中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wakeup_clr   : 1;  /* bit[0]   : IOMCU子系统唤醒中断清除 */
        unsigned int  soft_int_clr : 1;  /* bit[1]   : TCXO组合唤醒中断中软件中断清除 */
        unsigned int  reserved     : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_IOMCU_WAKEUP_CLR_UNION;
#endif
#define SOC_IOMCU_WAKEUP_CLR_wakeup_clr_START    (0)
#define SOC_IOMCU_WAKEUP_CLR_wakeup_clr_END      (0)
#define SOC_IOMCU_WAKEUP_CLR_soft_int_clr_START  (1)
#define SOC_IOMCU_WAKEUP_CLR_soft_int_clr_END    (1)


/*****************************************************************************
 结构名    : SOC_IOMCU_WAKEUP_STAT_UNION
 结构说明  : WAKEUP_STAT 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: IOMCU子系统唤醒中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wakeup_stat   : 1;  /* bit[0]   : IOMCU子系统唤醒中断状态 */
        unsigned int  soft_int_stat : 1;  /* bit[1]   : TCXO组合唤醒中断中软件中断状态 */
        unsigned int  reserved      : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_IOMCU_WAKEUP_STAT_UNION;
#endif
#define SOC_IOMCU_WAKEUP_STAT_wakeup_stat_START    (0)
#define SOC_IOMCU_WAKEUP_STAT_wakeup_stat_END      (0)
#define SOC_IOMCU_WAKEUP_STAT_soft_int_stat_START  (1)
#define SOC_IOMCU_WAKEUP_STAT_soft_int_stat_END    (1)


/*****************************************************************************
 结构名    : SOC_IOMCU_COMB_INT_RAW_UNION
 结构说明  : COMB_INT_RAW 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: IOMCU输出的原始组合中断状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio0_int_raw      : 1;  /* bit[0]    : 组合中断中的GPIO0的原始中断状态 */
        unsigned int  gpio1_int_raw      : 1;  /* bit[1]    : 组合中断中的GPIO1的原始中断状态 */
        unsigned int  gpio2_int_raw      : 1;  /* bit[2]    : 组合中断中的GPIO2的原始中断状态 */
        unsigned int  gpio3_int_raw      : 1;  /* bit[3]    : 组合中断中的GPIO3的原始中断状态 */
        unsigned int  timer1_int_raw     : 1;  /* bit[4]    : 组合中断中的timer的原始中断状态 */
        unsigned int  timer2_int_raw     : 1;  /* bit[5]    : 组合中断中的timer的原始中断状态 */
        unsigned int  soft_int_raw       : 1;  /* bit[6]    : 组合中断中的软件中断的原始中断状态 */
        unsigned int  dss_rise_int_raw   : 1;  /* bit[7]    : DSS中断的上升沿原始中断状态 */
        unsigned int  dss_down_int_raw   : 1;  /* bit[8]    : DSS中断的下降沿原始中断状态 */
        unsigned int  sys_wakeup_int_raw : 1;  /* bit[9]    : 外部系统从其他状态进入到Sleep状态的中断状态 */
        unsigned int  reserved           : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_IOMCU_COMB_INT_RAW_UNION;
#endif
#define SOC_IOMCU_COMB_INT_RAW_gpio0_int_raw_START       (0)
#define SOC_IOMCU_COMB_INT_RAW_gpio0_int_raw_END         (0)
#define SOC_IOMCU_COMB_INT_RAW_gpio1_int_raw_START       (1)
#define SOC_IOMCU_COMB_INT_RAW_gpio1_int_raw_END         (1)
#define SOC_IOMCU_COMB_INT_RAW_gpio2_int_raw_START       (2)
#define SOC_IOMCU_COMB_INT_RAW_gpio2_int_raw_END         (2)
#define SOC_IOMCU_COMB_INT_RAW_gpio3_int_raw_START       (3)
#define SOC_IOMCU_COMB_INT_RAW_gpio3_int_raw_END         (3)
#define SOC_IOMCU_COMB_INT_RAW_timer1_int_raw_START      (4)
#define SOC_IOMCU_COMB_INT_RAW_timer1_int_raw_END        (4)
#define SOC_IOMCU_COMB_INT_RAW_timer2_int_raw_START      (5)
#define SOC_IOMCU_COMB_INT_RAW_timer2_int_raw_END        (5)
#define SOC_IOMCU_COMB_INT_RAW_soft_int_raw_START        (6)
#define SOC_IOMCU_COMB_INT_RAW_soft_int_raw_END          (6)
#define SOC_IOMCU_COMB_INT_RAW_dss_rise_int_raw_START    (7)
#define SOC_IOMCU_COMB_INT_RAW_dss_rise_int_raw_END      (7)
#define SOC_IOMCU_COMB_INT_RAW_dss_down_int_raw_START    (8)
#define SOC_IOMCU_COMB_INT_RAW_dss_down_int_raw_END      (8)
#define SOC_IOMCU_COMB_INT_RAW_sys_wakeup_int_raw_START  (9)
#define SOC_IOMCU_COMB_INT_RAW_sys_wakeup_int_raw_END    (9)


/*****************************************************************************
 结构名    : SOC_IOMCU_COMB_INT_MSK_UNION
 结构说明  : COMB_INT_MSK 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: IOMCU输出的组合中断状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio0_int_msk      : 1;  /* bit[0]    : 组合中断中的GPIO0的中断屏蔽 */
        unsigned int  gpio1_int_msk      : 1;  /* bit[1]    : 组合中断中的GPIO1的中断屏蔽 */
        unsigned int  gpio2_int_msk      : 1;  /* bit[2]    : 组合中断中的GPIO2的中断屏蔽 */
        unsigned int  gpio3_int_msk      : 1;  /* bit[3]    : 组合中断中的GPIO3的中断屏蔽 */
        unsigned int  timer1_int_msk     : 1;  /* bit[4]    : 组合中断中的timer的中断屏蔽 */
        unsigned int  timer2_int_msk     : 1;  /* bit[5]    : 组合中断中的timer的中断屏蔽 */
        unsigned int  soft_int_msk       : 1;  /* bit[6]    : 组合中断中的软件中断的原始中断屏蔽 */
        unsigned int  dss_rise_int_msk   : 1;  /* bit[7]    : DSS中断的上升沿原始中断屏蔽 */
        unsigned int  dss_down_int_msk   : 1;  /* bit[8]    : DSS中断的下降沿原始中断屏蔽 */
        unsigned int  dss_rise_int_clr   : 1;  /* bit[9]    : DSS中断的上升沿原始中断清除 */
        unsigned int  dss_down_int_clr   : 1;  /* bit[10]   : DSS中断的下降沿原始中断清除 */
        unsigned int  sys_wakeup_int_msk : 1;  /* bit[11]   : 外部系统从其他状态进入到Sleep状态的中断屏蔽 */
        unsigned int  sys_wakeup_int_clr : 1;  /* bit[12]   : 外部系统从其他状态进入到Sleep状态的中断清除 */
        unsigned int  reserved           : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_IOMCU_COMB_INT_MSK_UNION;
#endif
#define SOC_IOMCU_COMB_INT_MSK_gpio0_int_msk_START       (0)
#define SOC_IOMCU_COMB_INT_MSK_gpio0_int_msk_END         (0)
#define SOC_IOMCU_COMB_INT_MSK_gpio1_int_msk_START       (1)
#define SOC_IOMCU_COMB_INT_MSK_gpio1_int_msk_END         (1)
#define SOC_IOMCU_COMB_INT_MSK_gpio2_int_msk_START       (2)
#define SOC_IOMCU_COMB_INT_MSK_gpio2_int_msk_END         (2)
#define SOC_IOMCU_COMB_INT_MSK_gpio3_int_msk_START       (3)
#define SOC_IOMCU_COMB_INT_MSK_gpio3_int_msk_END         (3)
#define SOC_IOMCU_COMB_INT_MSK_timer1_int_msk_START      (4)
#define SOC_IOMCU_COMB_INT_MSK_timer1_int_msk_END        (4)
#define SOC_IOMCU_COMB_INT_MSK_timer2_int_msk_START      (5)
#define SOC_IOMCU_COMB_INT_MSK_timer2_int_msk_END        (5)
#define SOC_IOMCU_COMB_INT_MSK_soft_int_msk_START        (6)
#define SOC_IOMCU_COMB_INT_MSK_soft_int_msk_END          (6)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_msk_START    (7)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_msk_END      (7)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_msk_START    (8)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_msk_END      (8)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_clr_START    (9)
#define SOC_IOMCU_COMB_INT_MSK_dss_rise_int_clr_END      (9)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_clr_START    (10)
#define SOC_IOMCU_COMB_INT_MSK_dss_down_int_clr_END      (10)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_msk_START  (11)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_msk_END    (11)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_clr_START  (12)
#define SOC_IOMCU_COMB_INT_MSK_sys_wakeup_int_clr_END    (12)


/*****************************************************************************
 结构名    : SOC_IOMCU_COMB_INT_STAT_UNION
 结构说明  : COMB_INT_STAT 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: IOMCU输出的屏蔽后组合中断状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio0_int_mskd      : 1;  /* bit[0]    : 组合中断中的GPIO0的屏蔽后中断状态 */
        unsigned int  gpio1_int_mskd      : 1;  /* bit[1]    : 组合中断中的GPIO1的屏蔽后中断状态 */
        unsigned int  gpio2_int_mskd      : 1;  /* bit[2]    : 组合中断中的GPIO2的屏蔽后中断状态 */
        unsigned int  gpio3_int_mskd      : 1;  /* bit[3]    : 组合中断中的GPIO3的屏蔽后中断状态 */
        unsigned int  timer1_int_mskd     : 1;  /* bit[4]    : 组合中断中的timer的屏蔽后中断状态 */
        unsigned int  timer2_int_mskd     : 1;  /* bit[5]    : 组合中断中的timer的屏蔽后中断状态 */
        unsigned int  soft_int_mskd       : 1;  /* bit[6]    : 组合中断中的软件中断的屏蔽后中断状态 */
        unsigned int  dss_rise_int_mskd   : 1;  /* bit[7]    : DSS中断的上升沿原始中断屏蔽后的中断状态 */
        unsigned int  dss_down_int_mskd   : 1;  /* bit[8]    : DSS中断的下降沿原始中断屏蔽后的中断状态 */
        unsigned int  sys_wakeup_int_mskd : 1;  /* bit[9]    : 外部系统从到其他状态进入Sleep屏蔽后的中断状态 */
        unsigned int  reserved            : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_IOMCU_COMB_INT_STAT_UNION;
#endif
#define SOC_IOMCU_COMB_INT_STAT_gpio0_int_mskd_START       (0)
#define SOC_IOMCU_COMB_INT_STAT_gpio0_int_mskd_END         (0)
#define SOC_IOMCU_COMB_INT_STAT_gpio1_int_mskd_START       (1)
#define SOC_IOMCU_COMB_INT_STAT_gpio1_int_mskd_END         (1)
#define SOC_IOMCU_COMB_INT_STAT_gpio2_int_mskd_START       (2)
#define SOC_IOMCU_COMB_INT_STAT_gpio2_int_mskd_END         (2)
#define SOC_IOMCU_COMB_INT_STAT_gpio3_int_mskd_START       (3)
#define SOC_IOMCU_COMB_INT_STAT_gpio3_int_mskd_END         (3)
#define SOC_IOMCU_COMB_INT_STAT_timer1_int_mskd_START      (4)
#define SOC_IOMCU_COMB_INT_STAT_timer1_int_mskd_END        (4)
#define SOC_IOMCU_COMB_INT_STAT_timer2_int_mskd_START      (5)
#define SOC_IOMCU_COMB_INT_STAT_timer2_int_mskd_END        (5)
#define SOC_IOMCU_COMB_INT_STAT_soft_int_mskd_START        (6)
#define SOC_IOMCU_COMB_INT_STAT_soft_int_mskd_END          (6)
#define SOC_IOMCU_COMB_INT_STAT_dss_rise_int_mskd_START    (7)
#define SOC_IOMCU_COMB_INT_STAT_dss_rise_int_mskd_END      (7)
#define SOC_IOMCU_COMB_INT_STAT_dss_down_int_mskd_START    (8)
#define SOC_IOMCU_COMB_INT_STAT_dss_down_int_mskd_END      (8)
#define SOC_IOMCU_COMB_INT_STAT_sys_wakeup_int_mskd_START  (9)
#define SOC_IOMCU_COMB_INT_STAT_sys_wakeup_int_mskd_END    (9)


/*****************************************************************************
 结构名    : SOC_IOMCU_BUS_AUTO_FREQ_UNION
 结构说明  : BUS_AUTO_FREQ 寄存器结构定义。地址偏移量:0x080，初值:0x08000003，宽度:32
 寄存器说明: IOMCU总线自动降频/关时钟寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  auto_m7_freq_bypass  : 1;  /* bit[0]    : M7判断自动降频功能是否bypass
                                                                0：不bypass，降频
                                                                1：bypass，不降频 */
        unsigned int  auto_cpu_freq_bypass : 1;  /* bit[1]    : 外部CPU判断自动降频功能是否bypass
                                                                0：不bypass，降频
                                                                1：bypass，不降频 */
        unsigned int  reserved_0           : 2;  /* bit[2-3]  : reserved */
        unsigned int  auto_num_in          : 10; /* bit[4-13] : 进入自动降频时，需要保持idle状态的周期数 */
        unsigned int  reserved_1           : 2;  /* bit[14-15]: reserved */
        unsigned int  auto_num_out         : 10; /* bit[16-25]: 退出自动降频时，需要保持非idle状态的周期数 */
        unsigned int  reserved_2           : 1;  /* bit[26]   : reserved */
        unsigned int  noc_clkgate_bypass   : 1;  /* bit[27]   : 是否对NOC总线时钟关闭的Bypass，默认为1，即进行Bypass,不自动关NOC时钟。 */
        unsigned int  reserved_3           : 4;  /* bit[28-31]: reserved */
    } reg;
} SOC_IOMCU_BUS_AUTO_FREQ_UNION;
#endif
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_m7_freq_bypass_START   (0)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_m7_freq_bypass_END     (0)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_cpu_freq_bypass_START  (1)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_cpu_freq_bypass_END    (1)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_in_START           (4)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_in_END             (13)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_out_START          (16)
#define SOC_IOMCU_BUS_AUTO_FREQ_auto_num_out_END            (25)
#define SOC_IOMCU_BUS_AUTO_FREQ_noc_clkgate_bypass_START    (27)
#define SOC_IOMCU_BUS_AUTO_FREQ_noc_clkgate_bypass_END      (27)


/*****************************************************************************
 结构名    : SOC_IOMCU_MISC_CTRL_UNION
 结构说明  : MISC_CTRL 寄存器结构定义。地址偏移量:0x084，初值:0x00003780，宽度:32
 寄存器说明: MISC逻辑里面的控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spi_cs        : 4;  /* bit[0-3]  : 四个SPI的选择寄存器，对应的每一bit可选一个寄存器。 */
        unsigned int  clk_tp_ctrl   : 1;  /* bit[4]    : 时钟TP信号的控制bit。
                                                         0：不进行TP观测。
                                                         1：进行TP观测。 */
        unsigned int  dmac_ckgt_dis : 1;  /* bit[5]    : dmac的硬件门控使能位，配置为1，表示去使能，0表示使能自动门控功能，默认值为0 */
        unsigned int  cfg_itcm_size : 4;  /* bit[6-9]  : ITCM SIZE配置
                                                         0KB noTCM 4'b0000
                                                         4KB 4'b0011
                                                         8KB 4'b0100
                                                         16KB 4'b0101
                                                         32KB 4'b0110
                                                         64KB 4'b0111
                                                         128KB 4'b1000
                                                         256KB 4'b1001
                                                         512KB 4'b1010
                                                         1MB 4'b1011
                                                         2MB 4'b1100
                                                         4MB 4'b1101
                                                         8MB 4'b1110
                                                         16MB 4'b1111  */
        unsigned int  cfg_dtcm_size : 4;  /* bit[10-13]: DCTCM SIZE配置
                                                         0KB noTCM 4'b0000
                                                         4KB 4'b0011
                                                         8KB 4'b0100
                                                         16KB 4'b0101
                                                         32KB 4'b0110
                                                         64KB 4'b0111
                                                         128KB 4'b1000
                                                         256KB 4'b1001
                                                         512KB 4'b1010
                                                         1MB 4'b1011
                                                         2MB 4'b1100
                                                         4MB 4'b1101
                                                         8MB 4'b1110
                                                         16MB 4'b1111  */
        unsigned int  reserved      : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_IOMCU_MISC_CTRL_UNION;
#endif
#define SOC_IOMCU_MISC_CTRL_spi_cs_START         (0)
#define SOC_IOMCU_MISC_CTRL_spi_cs_END           (3)
#define SOC_IOMCU_MISC_CTRL_clk_tp_ctrl_START    (4)
#define SOC_IOMCU_MISC_CTRL_clk_tp_ctrl_END      (4)
#define SOC_IOMCU_MISC_CTRL_dmac_ckgt_dis_START  (5)
#define SOC_IOMCU_MISC_CTRL_dmac_ckgt_dis_END    (5)
#define SOC_IOMCU_MISC_CTRL_cfg_itcm_size_START  (6)
#define SOC_IOMCU_MISC_CTRL_cfg_itcm_size_END    (9)
#define SOC_IOMCU_MISC_CTRL_cfg_dtcm_size_START  (10)
#define SOC_IOMCU_MISC_CTRL_cfg_dtcm_size_END    (13)


/*****************************************************************************
 结构名    : SOC_IOMCU_NOC_CTRL_UNION
 结构说明  : NOC_CTRL 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: NOC 相关信号的控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  noc_iomcu_dma_mst_awqos   : 2;  /* bit[0-1]  : NOC DMA AW通道QOS */
        unsigned int  noc_iomcu_dma_mst_arqos   : 2;  /* bit[2-3]  : NOC DMA AR通道QOS */
        unsigned int  noc_iomcu_axi_mst_awqos   : 2;  /* bit[4-5]  : NOC AXI AW通道QOS */
        unsigned int  noc_iomcu_axi_mst_arqos   : 2;  /* bit[6-7]  : NOC AXI AR通道QOS */
        unsigned int  noc_iomcu_ahb_mst_requser : 2;  /* bit[8-9]  : NOC AHB通道QOS */
        unsigned int  noc_ahb_mst_mid           : 5;  /* bit[10-14]: NOC AHB Master通道Mid */
        unsigned int  reserved                  : 17; /* bit[15-31]:  */
    } reg;
} SOC_IOMCU_NOC_CTRL_UNION;
#endif
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_awqos_START    (0)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_awqos_END      (1)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_arqos_START    (2)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_dma_mst_arqos_END      (3)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_awqos_START    (4)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_awqos_END      (5)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_arqos_START    (6)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_axi_mst_arqos_END      (7)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_ahb_mst_requser_START  (8)
#define SOC_IOMCU_NOC_CTRL_noc_iomcu_ahb_mst_requser_END    (9)
#define SOC_IOMCU_NOC_CTRL_noc_ahb_mst_mid_START            (10)
#define SOC_IOMCU_NOC_CTRL_noc_ahb_mst_mid_END              (14)


/*****************************************************************************
 结构名    : SOC_IOMCU_M7_CFG2_UNION
 结构说明  : M7_CFG2 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: IOMCU M7配置寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_reserved : 32; /* bit[0-31]: 预留 */
    } reg;
} SOC_IOMCU_M7_CFG2_UNION;
#endif
#define SOC_IOMCU_M7_CFG2_iomcu_reserved_START  (0)
#define SOC_IOMCU_M7_CFG2_iomcu_reserved_END    (31)


/*****************************************************************************
 结构名    : SOC_IOMCU_CLKEN1_UNION
 结构说明  : CLKEN1 寄存器结构定义。地址偏移量:0x090，初值:0x0000000F，宽度:32
 寄存器说明: IOMCU分区时钟使能寄存器1。对比特写1，使能IOMCU_CLKSTAT0对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clken1_0peri0 : 1;  /* bit[0]   : 0peri0 */
        unsigned int  iomcu_clken1_1peri1 : 1;  /* bit[1]   : 1peri1 */
        unsigned int  iomcu_clken1_2peri2 : 1;  /* bit[2]   : 2peri2 */
        unsigned int  iomcu_clken1_3peri3 : 1;  /* bit[3]   : 3peri3 */
        unsigned int  reserved            : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_IOMCU_CLKEN1_UNION;
#endif
#define SOC_IOMCU_CLKEN1_iomcu_clken1_0peri0_START  (0)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_0peri0_END    (0)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_1peri1_START  (1)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_1peri1_END    (1)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_2peri2_START  (2)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_2peri2_END    (2)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_3peri3_START  (3)
#define SOC_IOMCU_CLKEN1_iomcu_clken1_3peri3_END    (3)


/*****************************************************************************
 结构名    : SOC_IOMCU_CLKDIS1_UNION
 结构说明  : CLKDIS1 寄存器结构定义。地址偏移量:0x094，初值:0x00000000，宽度:32
 寄存器说明: IOMCU分区时钟使能寄存器1。对比特写1，使能IOMCU_CLKSTAT0对应的时钟；写0不影响时钟使能的状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clkdis1_0peri0 : 1;  /* bit[0]   : dis1_0peri0 */
        unsigned int  iomcu_clkdis1_1peri1 : 1;  /* bit[1]   : dis1_1peri1 */
        unsigned int  iomcu_clkdis1_2peri2 : 1;  /* bit[2]   : dis1_2peri2 */
        unsigned int  iomcu_clkdis1_3peri3 : 1;  /* bit[3]   : dis1_3peri3 */
        unsigned int  reserved             : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_IOMCU_CLKDIS1_UNION;
#endif
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_0peri0_START  (0)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_0peri0_END    (0)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_1peri1_START  (1)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_1peri1_END    (1)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_2peri2_START  (2)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_2peri2_END    (2)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_3peri3_START  (3)
#define SOC_IOMCU_CLKDIS1_iomcu_clkdis1_3peri3_END    (3)


/*****************************************************************************
 结构名    : SOC_IOMCU_CLKSTAT1_UNION
 结构说明  : CLKSTAT1 寄存器结构定义。地址偏移量:0x098，初值:0x0000000F，宽度:32
 寄存器说明: IOMCU分区时钟状态寄存器1。由IOMCU_CLKEN0和IOMCU_CLKDIS0配置进行状态修改。
            外设时钟控制信号需经过在CRG中进行同步处理。因此，这里的寄存器值在延迟相应时钟域的几个周期后才真正反应时钟状态。
            每个Bit含义：
            0：时钟关闭；
            1：时钟打开。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_clkstat1_0peri0 : 1;  /* bit[0]   : stat1_0peri0 */
        unsigned int  iomcu_clkstat1_1peri1 : 1;  /* bit[1]   : stat1_1peri1 */
        unsigned int  iomcu_clkstat1_2peri2 : 1;  /* bit[2]   : stat1_2peri2 */
        unsigned int  iomcu_clkstat1_3peri3 : 1;  /* bit[3]   : stat1_3peri3 */
        unsigned int  reserved              : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_IOMCU_CLKSTAT1_UNION;
#endif
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_0peri0_START  (0)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_0peri0_END    (0)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_1peri1_START  (1)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_1peri1_END    (1)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_2peri2_START  (2)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_2peri2_END    (2)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_3peri3_START  (3)
#define SOC_IOMCU_CLKSTAT1_iomcu_clkstat1_3peri3_END    (3)


/*****************************************************************************
 结构名    : SOC_IOMCU_SEC_TZPC_UNION
 结构说明  : SEC_TZPC 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 安全TZPC位（绝对安全区域）0表示安全，1表示非安全。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_AHB_tzpc   : 1;  /* bit[0]    : AHB总线安全控制bit */
        unsigned int  iomcu_AXI_tzpc   : 1;  /* bit[1]    : AXI总线安全控制bit */
        unsigned int  reserved_0       : 1;  /* bit[2]    : 安全控制bit */
        unsigned int  iomcu_i2c2_tzpc  : 1;  /* bit[3]    : I2C2安全控制bit */
        unsigned int  iomcu_i2c1_tzpc  : 1;  /* bit[4]    : I2C1安全控制bit */
        unsigned int  iomcu_spi2_tzpc  : 1;  /* bit[5]    : SPI2安全控制bit */
        unsigned int  iomcu_uart8_tzpc : 1;  /* bit[6]    : UART8安全控制bit */
        unsigned int  iomcu_i2c6_tzpc  : 1;  /* bit[7]    : i2c6安全控制bit */
        unsigned int  iomcu_tcm_tzpc   : 1;  /* bit[8]    : TCM安全控制bit（只控制TCM REMAP APB部分） */
        unsigned int  iomcu_spi_tzpc   : 1;  /* bit[9]    : SPI安全控制bit */
        unsigned int  iomcu_i2c0_tzpc  : 1;  /* bit[10]   : I2C0安全控制bit */
        unsigned int  iomcu_uart3_tzpc : 1;  /* bit[11]   : UART3安全控制bit */
        unsigned int  iomcu_blpwm_tzpc : 1;  /* bit[12]   : BLPWM安全控制bit */
        unsigned int  iomcu_uart7_tzpc : 1;  /* bit[13]   : UART7安全控制bit */
        unsigned int  reserved_1       : 1;  /* bit[14]   : reserved */
        unsigned int  iomcu_gpio0_tzpc : 1;  /* bit[15]   : GPIO0安全控制bit */
        unsigned int  iomcu_gpio1_tzpc : 1;  /* bit[16]   : GPIO1安全控制bit */
        unsigned int  iomcu_gpio2_tzpc : 1;  /* bit[17]   : GPIO2安全控制bit */
        unsigned int  iomcu_gpio3_tzpc : 1;  /* bit[18]   : GPIO3安全控制bit */
        unsigned int  iomcu_wdg_tzpc   : 1;  /* bit[19]   : WDG安全控制bit */
        unsigned int  iomcu_timer_tzpc : 1;  /* bit[20]   : TIMER安全控制bit */
        unsigned int  iomcu_sctrl_tzpc : 1;  /* bit[21]   : IO_CONFIG安全控制bit */
        unsigned int  iomcu_rtc_tzpc   : 1;  /* bit[22]   : RTC安全控制bit */
        unsigned int  iomcu_m7_tzpc    : 1;  /* bit[23]   : IOMCU_M7_AHB_SLV安全控制bit */
        unsigned int  reserved_2       : 8;  /* bit[24-31]:  */
    } reg;
} SOC_IOMCU_SEC_TZPC_UNION;
#endif
#define SOC_IOMCU_SEC_TZPC_iomcu_AHB_tzpc_START    (0)
#define SOC_IOMCU_SEC_TZPC_iomcu_AHB_tzpc_END      (0)
#define SOC_IOMCU_SEC_TZPC_iomcu_AXI_tzpc_START    (1)
#define SOC_IOMCU_SEC_TZPC_iomcu_AXI_tzpc_END      (1)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c2_tzpc_START   (3)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c2_tzpc_END     (3)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c1_tzpc_START   (4)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c1_tzpc_END     (4)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi2_tzpc_START   (5)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi2_tzpc_END     (5)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart8_tzpc_START  (6)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart8_tzpc_END    (6)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c6_tzpc_START   (7)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c6_tzpc_END     (7)
#define SOC_IOMCU_SEC_TZPC_iomcu_tcm_tzpc_START    (8)
#define SOC_IOMCU_SEC_TZPC_iomcu_tcm_tzpc_END      (8)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi_tzpc_START    (9)
#define SOC_IOMCU_SEC_TZPC_iomcu_spi_tzpc_END      (9)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c0_tzpc_START   (10)
#define SOC_IOMCU_SEC_TZPC_iomcu_i2c0_tzpc_END     (10)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart3_tzpc_START  (11)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart3_tzpc_END    (11)
#define SOC_IOMCU_SEC_TZPC_iomcu_blpwm_tzpc_START  (12)
#define SOC_IOMCU_SEC_TZPC_iomcu_blpwm_tzpc_END    (12)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart7_tzpc_START  (13)
#define SOC_IOMCU_SEC_TZPC_iomcu_uart7_tzpc_END    (13)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio0_tzpc_START  (15)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio0_tzpc_END    (15)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio1_tzpc_START  (16)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio1_tzpc_END    (16)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio2_tzpc_START  (17)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio2_tzpc_END    (17)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio3_tzpc_START  (18)
#define SOC_IOMCU_SEC_TZPC_iomcu_gpio3_tzpc_END    (18)
#define SOC_IOMCU_SEC_TZPC_iomcu_wdg_tzpc_START    (19)
#define SOC_IOMCU_SEC_TZPC_iomcu_wdg_tzpc_END      (19)
#define SOC_IOMCU_SEC_TZPC_iomcu_timer_tzpc_START  (20)
#define SOC_IOMCU_SEC_TZPC_iomcu_timer_tzpc_END    (20)
#define SOC_IOMCU_SEC_TZPC_iomcu_sctrl_tzpc_START  (21)
#define SOC_IOMCU_SEC_TZPC_iomcu_sctrl_tzpc_END    (21)
#define SOC_IOMCU_SEC_TZPC_iomcu_rtc_tzpc_START    (22)
#define SOC_IOMCU_SEC_TZPC_iomcu_rtc_tzpc_END      (22)
#define SOC_IOMCU_SEC_TZPC_iomcu_m7_tzpc_START     (23)
#define SOC_IOMCU_SEC_TZPC_iomcu_m7_tzpc_END       (23)


/*****************************************************************************
 结构名    : SOC_IOMCU_SEC_RES_UNION
 结构说明  : SEC_RES 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_se_reserved : 32; /* bit[0-31]: 预留 */
    } reg;
} SOC_IOMCU_SEC_RES_UNION;
#endif
#define SOC_IOMCU_SEC_RES_iomcu_se_reserved_START  (0)
#define SOC_IOMCU_SEC_RES_iomcu_se_reserved_END    (31)






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

#endif /* end of soc_iomcu_interface.h */
