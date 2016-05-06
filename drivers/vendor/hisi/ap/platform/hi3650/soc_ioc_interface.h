/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_ioc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:03
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_IOC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_IOC_INTERFACE_H__
#define __SOC_IOC_INTERFACE_H__

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
/* 寄存器说明：TEST_MODE管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_000_UNION */
#define SOC_IOC_IOMG_000_ADDR(base)                   ((base) + (0x000))

/* 寄存器说明：PMU0_SSI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_001_UNION */
#define SOC_IOC_IOMG_001_ADDR(base)                   ((base) + (0x004))

/* 寄存器说明：PMU1_SSI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_002_UNION */
#define SOC_IOC_IOMG_002_ADDR(base)                   ((base) + (0x008))

/* 寄存器说明：JTAG_TRST_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_003_UNION */
#define SOC_IOC_IOMG_003_ADDR(base)                   ((base) + (0x00C))

/* 寄存器说明：JTAG_TDI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_004_UNION */
#define SOC_IOC_IOMG_004_ADDR(base)                   ((base) + (0x010))

/* 寄存器说明：JTAG_TDO管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_005_UNION */
#define SOC_IOC_IOMG_005_ADDR(base)                   ((base) + (0x014))

/* 寄存器说明：I2C3_SCL管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_006_UNION */
#define SOC_IOC_IOMG_006_ADDR(base)                   ((base) + (0x018))

/* 寄存器说明：I2C3_SDA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_007_UNION */
#define SOC_IOC_IOMG_007_ADDR(base)                   ((base) + (0x01C))

/* 寄存器说明：SPI1_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_008_UNION */
#define SOC_IOC_IOMG_008_ADDR(base)                   ((base) + (0x020))

/* 寄存器说明：SPI1_DI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_009_UNION */
#define SOC_IOC_IOMG_009_ADDR(base)                   ((base) + (0x024))

/* 寄存器说明：SPI1_DO管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_010_UNION */
#define SOC_IOC_IOMG_010_ADDR(base)                   ((base) + (0x028))

/* 寄存器说明：SPI1_CS_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_011_UNION */
#define SOC_IOC_IOMG_011_ADDR(base)                   ((base) + (0x02C))

/* 寄存器说明：SPDIF管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_012_UNION */
#define SOC_IOC_IOMG_012_ADDR(base)                   ((base) + (0x030))

/* 寄存器说明：GPS_REF管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_013_UNION */
#define SOC_IOC_IOMG_013_ADDR(base)                   ((base) + (0x034))

/* 寄存器说明：ISP_GPIO00_FTRSTN管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_014_UNION */
#define SOC_IOC_IOMG_014_ADDR(base)                   ((base) + (0x038))

/* 寄存器说明：ISP_GPIO01_BKRSTN管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_015_UNION */
#define SOC_IOC_IOMG_015_ADDR(base)                   ((base) + (0x03C))

/* 寄存器说明：ISP_GPIO02_MNTRB管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_016_UNION */
#define SOC_IOC_IOMG_016_ADDR(base)                   ((base) + (0x040))

/* 寄存器说明：ISP_GPIO06_FSYNC管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_017_UNION */
#define SOC_IOC_IOMG_017_ADDR(base)                   ((base) + (0x044))

/* 寄存器说明：ISP_GPIO10_SBPWM管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_018_UNION */
#define SOC_IOC_IOMG_018_ADDR(base)                   ((base) + (0x048))

/* 寄存器说明：ISP_CLK0管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_019_UNION */
#define SOC_IOC_IOMG_019_ADDR(base)                   ((base) + (0x04C))

/* 寄存器说明：ISP_CLK1管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_020_UNION */
#define SOC_IOC_IOMG_020_ADDR(base)                   ((base) + (0x050))

/* 寄存器说明：ISP_CLK2管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_021_UNION */
#define SOC_IOC_IOMG_021_ADDR(base)                   ((base) + (0x054))

/* 寄存器说明：ISP_SCL0管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_022_UNION */
#define SOC_IOC_IOMG_022_ADDR(base)                   ((base) + (0x058))

/* 寄存器说明：ISP_SDA0管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_023_UNION */
#define SOC_IOC_IOMG_023_ADDR(base)                   ((base) + (0x05C))

/* 寄存器说明：ISP_SCL1管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_024_UNION */
#define SOC_IOC_IOMG_024_ADDR(base)                   ((base) + (0x060))

/* 寄存器说明：ISP_SDA1管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_025_UNION */
#define SOC_IOC_IOMG_025_ADDR(base)                   ((base) + (0x064))

/* 寄存器说明：ISP_SCL2管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_026_UNION */
#define SOC_IOC_IOMG_026_ADDR(base)                   ((base) + (0x068))

/* 寄存器说明：ISP_SDA2管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_027_UNION */
#define SOC_IOC_IOMG_027_ADDR(base)                   ((base) + (0x06C))

/* 寄存器说明：SDIO1_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_028_UNION */
#define SOC_IOC_IOMG_028_ADDR(base)                   ((base) + (0x070))

/* 寄存器说明：SDIO1_CMD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_029_UNION */
#define SOC_IOC_IOMG_029_ADDR(base)                   ((base) + (0x074))

/* 寄存器说明：SDIO1_DATA0管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_030_UNION */
#define SOC_IOC_IOMG_030_ADDR(base)                   ((base) + (0x078))

/* 寄存器说明：SDIO1_DATA1管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_031_UNION */
#define SOC_IOC_IOMG_031_ADDR(base)                   ((base) + (0x07C))

/* 寄存器说明：SDIO1_DATA2管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_032_UNION */
#define SOC_IOC_IOMG_032_ADDR(base)                   ((base) + (0x080))

/* 寄存器说明：SDIO1_DATA3管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_033_UNION */
#define SOC_IOC_IOMG_033_ADDR(base)                   ((base) + (0x084))

/* 寄存器说明：I2C4_SCL管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_034_UNION */
#define SOC_IOC_IOMG_034_ADDR(base)                   ((base) + (0x088))

/* 寄存器说明：I2C4_SDA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_035_UNION */
#define SOC_IOC_IOMG_035_ADDR(base)                   ((base) + (0x08C))

/* 寄存器说明：I2C5_SCL管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_036_UNION */
#define SOC_IOC_IOMG_036_ADDR(base)                   ((base) + (0x090))

/* 寄存器说明：I2C5_SDA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_037_UNION */
#define SOC_IOC_IOMG_037_ADDR(base)                   ((base) + (0x094))

/* 寄存器说明：SD_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_038_UNION */
#define SOC_IOC_IOMG_038_ADDR(base)                   ((base) + (0x098))

/* 寄存器说明：SD_CMD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_039_UNION */
#define SOC_IOC_IOMG_039_ADDR(base)                   ((base) + (0x09C))

/* 寄存器说明：SD_DATA0管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_040_UNION */
#define SOC_IOC_IOMG_040_ADDR(base)                   ((base) + (0x0A0))

/* 寄存器说明：SD_DATA1管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_041_UNION */
#define SOC_IOC_IOMG_041_ADDR(base)                   ((base) + (0x0A4))

/* 寄存器说明：SD_DATA2管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_042_UNION */
#define SOC_IOC_IOMG_042_ADDR(base)                   ((base) + (0x0A8))

/* 寄存器说明：SD_DATA3管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_043_UNION */
#define SOC_IOC_IOMG_043_ADDR(base)                   ((base) + (0x0AC))

/* 寄存器说明：SPI0_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_044_UNION */
#define SOC_IOC_IOMG_044_ADDR(base)                   ((base) + (0x0B0))

/* 寄存器说明：SPI0_DI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_045_UNION */
#define SOC_IOC_IOMG_045_ADDR(base)                   ((base) + (0x0B4))

/* 寄存器说明：SPI0_DO管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_046_UNION */
#define SOC_IOC_IOMG_046_ADDR(base)                   ((base) + (0x0B8))

/* 寄存器说明：SPI0_CS0_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_047_UNION */
#define SOC_IOC_IOMG_047_ADDR(base)                   ((base) + (0x0BC))

/* 寄存器说明：SPI0_CS1_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_048_UNION */
#define SOC_IOC_IOMG_048_ADDR(base)                   ((base) + (0x0C0))

/* 寄存器说明：SPI0_CS2_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_049_UNION */
#define SOC_IOC_IOMG_049_ADDR(base)                   ((base) + (0x0C4))

/* 寄存器说明：SPI0_CS3_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_050_UNION */
#define SOC_IOC_IOMG_050_ADDR(base)                   ((base) + (0x0C8))

/* 寄存器说明：GPIO_054管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_051_UNION */
#define SOC_IOC_IOMG_051_ADDR(base)                   ((base) + (0x0CC))

/* 寄存器说明：GPIO_055管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_052_UNION */
#define SOC_IOC_IOMG_052_ADDR(base)                   ((base) + (0x0D0))

/* 寄存器说明：EMMC50_RST_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_053_UNION */
#define SOC_IOC_IOMG_053_ADDR(base)                   ((base) + (0x0D4))

/* 寄存器说明：UART1_CTS_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_054_UNION */
#define SOC_IOC_IOMG_054_ADDR(base)                   ((base) + (0x0D8))

/* 寄存器说明：UART1_RTS_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_055_UNION */
#define SOC_IOC_IOMG_055_ADDR(base)                   ((base) + (0x0DC))

/* 寄存器说明：UART1_RXD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_056_UNION */
#define SOC_IOC_IOMG_056_ADDR(base)                   ((base) + (0x0E0))

/* 寄存器说明：UART1_TXD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_057_UNION */
#define SOC_IOC_IOMG_057_ADDR(base)                   ((base) + (0x0E4))

/* 寄存器说明：SDIO0_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_058_UNION */
#define SOC_IOC_IOMG_058_ADDR(base)                   ((base) + (0x0E8))

/* 寄存器说明：SDIO0_CMD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_059_UNION */
#define SOC_IOC_IOMG_059_ADDR(base)                   ((base) + (0x0EC))

/* 寄存器说明：SDIO0_DATA0管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_060_UNION */
#define SOC_IOC_IOMG_060_ADDR(base)                   ((base) + (0x0F0))

/* 寄存器说明：SDIO0_DATA1管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_061_UNION */
#define SOC_IOC_IOMG_061_ADDR(base)                   ((base) + (0x0F4))

/* 寄存器说明：SDIO0_DATA2管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_062_UNION */
#define SOC_IOC_IOMG_062_ADDR(base)                   ((base) + (0x0F8))

/* 寄存器说明：SDIO0_DATA3管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_063_UNION */
#define SOC_IOC_IOMG_063_ADDR(base)                   ((base) + (0x0FC))

/* 寄存器说明：UART6_CTS_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_064_UNION */
#define SOC_IOC_IOMG_064_ADDR(base)                   ((base) + (0x100))

/* 寄存器说明：UART6_RTS_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_065_UNION */
#define SOC_IOC_IOMG_065_ADDR(base)                   ((base) + (0x104))

/* 寄存器说明：UART6_RXD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_066_UNION */
#define SOC_IOC_IOMG_066_ADDR(base)                   ((base) + (0x108))

/* 寄存器说明：UART6_TXD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_067_UNION */
#define SOC_IOC_IOMG_067_ADDR(base)                   ((base) + (0x10C))

/* 寄存器说明：UART3_CTS_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_068_UNION */
#define SOC_IOC_IOMG_068_ADDR(base)                   ((base) + (0x110))

/* 寄存器说明：UART3_RTS_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_069_UNION */
#define SOC_IOC_IOMG_069_ADDR(base)                   ((base) + (0x114))

/* 寄存器说明：UART3_RXD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_070_UNION */
#define SOC_IOC_IOMG_070_ADDR(base)                   ((base) + (0x118))

/* 寄存器说明：UART3_TXD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_071_UNION */
#define SOC_IOC_IOMG_071_ADDR(base)                   ((base) + (0x11C))

/* 寄存器说明：UART4_CTS_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_072_UNION */
#define SOC_IOC_IOMG_072_ADDR(base)                   ((base) + (0x120))

/* 寄存器说明：UART4_RTS_N管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_073_UNION */
#define SOC_IOC_IOMG_073_ADDR(base)                   ((base) + (0x124))

/* 寄存器说明：UART4_RXD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_074_UNION */
#define SOC_IOC_IOMG_074_ADDR(base)                   ((base) + (0x128))

/* 寄存器说明：UART4_TXD管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_075_UNION */
#define SOC_IOC_IOMG_075_ADDR(base)                   ((base) + (0x12C))

/* 寄存器说明：PWM_OUT1管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_076_UNION */
#define SOC_IOC_IOMG_076_ADDR(base)                   ((base) + (0x130))

/* 寄存器说明：PMU_HKADC_SSI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_077_UNION */
#define SOC_IOC_IOMG_077_ADDR(base)                   ((base) + (0x134))

/* 寄存器说明：PMU_AUXDAC0_SSI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_078_UNION */
#define SOC_IOC_IOMG_078_ADDR(base)                   ((base) + (0x138))

/* 寄存器说明：PMU_AUXDAC1_SSI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_079_UNION */
#define SOC_IOC_IOMG_079_ADDR(base)                   ((base) + (0x13C))

/* 寄存器说明：USIM0_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_080_UNION */
#define SOC_IOC_IOMG_080_ADDR(base)                   ((base) + (0x140))

/* 寄存器说明：USIM0_RST管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_081_UNION */
#define SOC_IOC_IOMG_081_ADDR(base)                   ((base) + (0x144))

/* 寄存器说明：USIM0_DATA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_082_UNION */
#define SOC_IOC_IOMG_082_ADDR(base)                   ((base) + (0x148))

/* 寄存器说明：USIM1_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_083_UNION */
#define SOC_IOC_IOMG_083_ADDR(base)                   ((base) + (0x14C))

/* 寄存器说明：USIM1_RST管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_084_UNION */
#define SOC_IOC_IOMG_084_ADDR(base)                   ((base) + (0x150))

/* 寄存器说明：USIM1_DATA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_085_UNION */
#define SOC_IOC_IOMG_085_ADDR(base)                   ((base) + (0x154))

/* 寄存器说明：LTE_INACTIVE管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_086_UNION */
#define SOC_IOC_IOMG_086_ADDR(base)                   ((base) + (0x158))

/* 寄存器说明：LTE_RX_ACTIVE管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_087_UNION */
#define SOC_IOC_IOMG_087_ADDR(base)                   ((base) + (0x15C))

/* 寄存器说明：LTE_TX_ACTIVE管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_088_UNION */
#define SOC_IOC_IOMG_088_ADDR(base)                   ((base) + (0x160))

/* 寄存器说明：ISM_PRIORITY管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_089_UNION */
#define SOC_IOC_IOMG_089_ADDR(base)                   ((base) + (0x164))

/* 寄存器说明：CH0_AFC_PDM管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_090_UNION */
#define SOC_IOC_IOMG_090_ADDR(base)                   ((base) + (0x168))

/* 寄存器说明：CH0_APT_PDM管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_091_UNION */
#define SOC_IOC_IOMG_091_ADDR(base)                   ((base) + (0x16C))

/* 寄存器说明：CH0_RF_RESETN管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_092_UNION */
#define SOC_IOC_IOMG_092_ADDR(base)                   ((base) + (0x170))

/* 寄存器说明：CH0_RF_SSI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_093_UNION */
#define SOC_IOC_IOMG_093_ADDR(base)                   ((base) + (0x174))

/* 寄存器说明：CH0_RF_TCVR_ON管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_094_UNION */
#define SOC_IOC_IOMG_094_ADDR(base)                   ((base) + (0x178))

/* 寄存器说明：CH2_AFC_PDM管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_095_UNION */
#define SOC_IOC_IOMG_095_ADDR(base)                   ((base) + (0x17C))

/* 寄存器说明：CH1_APT_PDM管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_096_UNION */
#define SOC_IOC_IOMG_096_ADDR(base)                   ((base) + (0x180))

/* 寄存器说明：CH1_RF_RESETN管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_097_UNION */
#define SOC_IOC_IOMG_097_ADDR(base)                   ((base) + (0x184))

/* 寄存器说明：CH1_RF_SSI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_098_UNION */
#define SOC_IOC_IOMG_098_ADDR(base)                   ((base) + (0x188))

/* 寄存器说明：CH1_RF_TCVR_ON管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_099_UNION */
#define SOC_IOC_IOMG_099_ADDR(base)                   ((base) + (0x18C))

/* 寄存器说明：CH2_RF_RESETN管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_100_UNION */
#define SOC_IOC_IOMG_100_ADDR(base)                   ((base) + (0x190))

/* 寄存器说明：CH2_RF_SSI管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_101_UNION */
#define SOC_IOC_IOMG_101_ADDR(base)                   ((base) + (0x194))

/* 寄存器说明：CH2_RF_TCVR_ON管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_102_UNION */
#define SOC_IOC_IOMG_102_ADDR(base)                   ((base) + (0x198))

/* 寄存器说明：FE0_MIPI_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_103_UNION */
#define SOC_IOC_IOMG_103_ADDR(base)                   ((base) + (0x19C))

/* 寄存器说明：FE0_MIPI_DATA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_104_UNION */
#define SOC_IOC_IOMG_104_ADDR(base)                   ((base) + (0x1A0))

/* 寄存器说明：FE1_MIPI_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_105_UNION */
#define SOC_IOC_IOMG_105_ADDR(base)                   ((base) + (0x1A4))

/* 寄存器说明：FE1_MIPI_DATA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_106_UNION */
#define SOC_IOC_IOMG_106_ADDR(base)                   ((base) + (0x1A8))

/* 寄存器说明：FLASH_MASK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_107_UNION */
#define SOC_IOC_IOMG_107_ADDR(base)                   ((base) + (0x1AC))

/* 寄存器说明：GPS_BLANKING管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_108_UNION */
#define SOC_IOC_IOMG_108_ADDR(base)                   ((base) + (0x1B0))

/* 寄存器说明：ANTPA_SEL00管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_109_UNION */
#define SOC_IOC_IOMG_109_ADDR(base)                   ((base) + (0x1B4))

/* 寄存器说明：ANTPA_SEL01管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_110_UNION */
#define SOC_IOC_IOMG_110_ADDR(base)                   ((base) + (0x1B8))

/* 寄存器说明：ANTPA_SEL02管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_111_UNION */
#define SOC_IOC_IOMG_111_ADDR(base)                   ((base) + (0x1BC))

/* 寄存器说明：ANTPA_SEL03管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_112_UNION */
#define SOC_IOC_IOMG_112_ADDR(base)                   ((base) + (0x1C0))

/* 寄存器说明：ANTPA_SEL04管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_113_UNION */
#define SOC_IOC_IOMG_113_ADDR(base)                   ((base) + (0x1C4))

/* 寄存器说明：ANTPA_SEL05管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_114_UNION */
#define SOC_IOC_IOMG_114_ADDR(base)                   ((base) + (0x1C8))

/* 寄存器说明：ANTPA_SEL06管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_115_UNION */
#define SOC_IOC_IOMG_115_ADDR(base)                   ((base) + (0x1CC))

/* 寄存器说明：ANTPA_SEL07管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_116_UNION */
#define SOC_IOC_IOMG_116_ADDR(base)                   ((base) + (0x1D0))

/* 寄存器说明：ANTPA_SEL08管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_117_UNION */
#define SOC_IOC_IOMG_117_ADDR(base)                   ((base) + (0x1D4))

/* 寄存器说明：ANTPA_SEL09管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_118_UNION */
#define SOC_IOC_IOMG_118_ADDR(base)                   ((base) + (0x1D8))

/* 寄存器说明：ANTPA_SEL10管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_119_UNION */
#define SOC_IOC_IOMG_119_ADDR(base)                   ((base) + (0x1DC))

/* 寄存器说明：ANTPA_SEL11管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_120_UNION */
#define SOC_IOC_IOMG_120_ADDR(base)                   ((base) + (0x1E0))

/* 寄存器说明：ANTPA_SEL12管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_121_UNION */
#define SOC_IOC_IOMG_121_ADDR(base)                   ((base) + (0x1E4))

/* 寄存器说明：ANTPA_SEL13管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_122_UNION */
#define SOC_IOC_IOMG_122_ADDR(base)                   ((base) + (0x1E8))

/* 寄存器说明：ANTPA_SEL14管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_123_UNION */
#define SOC_IOC_IOMG_123_ADDR(base)                   ((base) + (0x1EC))

/* 寄存器说明：ANTPA_SEL15管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_124_UNION */
#define SOC_IOC_IOMG_124_ADDR(base)                   ((base) + (0x1F0))

/* 寄存器说明：ANTPA_SEL16管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_125_UNION */
#define SOC_IOC_IOMG_125_ADDR(base)                   ((base) + (0x1F4))

/* 寄存器说明：ANTPA_SEL17管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_126_UNION */
#define SOC_IOC_IOMG_126_ADDR(base)                   ((base) + (0x1F8))

/* 寄存器说明：ANTPA_SEL18管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_127_UNION */
#define SOC_IOC_IOMG_127_ADDR(base)                   ((base) + (0x1FC))

/* 寄存器说明：ANTPA_SEL19管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_128_UNION */
#define SOC_IOC_IOMG_128_ADDR(base)                   ((base) + (0x200))

/* 寄存器说明：ANTPA_SEL20管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_129_UNION */
#define SOC_IOC_IOMG_129_ADDR(base)                   ((base) + (0x204))

/* 寄存器说明：ANTPA_SEL21管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_130_UNION */
#define SOC_IOC_IOMG_130_ADDR(base)                   ((base) + (0x208))

/* 寄存器说明：ANTPA_SEL22管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_131_UNION */
#define SOC_IOC_IOMG_131_ADDR(base)                   ((base) + (0x20C))

/* 寄存器说明：ANTPA_SEL23管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_132_UNION */
#define SOC_IOC_IOMG_132_ADDR(base)                   ((base) + (0x210))

/* 寄存器说明：ANTPA_SEL24管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_133_UNION */
#define SOC_IOC_IOMG_133_ADDR(base)                   ((base) + (0x214))

/* 寄存器说明：ANTPA_SEL25管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_134_UNION */
#define SOC_IOC_IOMG_134_ADDR(base)                   ((base) + (0x218))

/* 寄存器说明：ANTPA_SEL26管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_135_UNION */
#define SOC_IOC_IOMG_135_ADDR(base)                   ((base) + (0x21C))

/* 寄存器说明：ANTPA_SEL27管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_136_UNION */
#define SOC_IOC_IOMG_136_ADDR(base)                   ((base) + (0x220))

/* 寄存器说明：GPIO_140管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOMG_137_UNION */
#define SOC_IOC_IOMG_137_ADDR(base)                   ((base) + (0x224))

/* 寄存器说明：BOOT_MODE功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_000_UNION */
#define SOC_IOC_IOCG_000_ADDR(base)                   ((base) + (0x800))

/* 寄存器说明：TEST_MODE功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_001_UNION */
#define SOC_IOC_IOCG_001_ADDR(base)                   ((base) + (0x804))

/* 寄存器说明：PMU0_SSI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_002_UNION */
#define SOC_IOC_IOCG_002_ADDR(base)                   ((base) + (0x808))

/* 寄存器说明：PMU1_SSI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_003_UNION */
#define SOC_IOC_IOCG_003_ADDR(base)                   ((base) + (0x80C))

/* 寄存器说明：JTAG_TCK_SWCLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_004_UNION */
#define SOC_IOC_IOCG_004_ADDR(base)                   ((base) + (0x810))

/* 寄存器说明：JTAG_TMS_SWDIO功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_005_UNION */
#define SOC_IOC_IOCG_005_ADDR(base)                   ((base) + (0x814))

/* 寄存器说明：JTAG_TRST_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_006_UNION */
#define SOC_IOC_IOCG_006_ADDR(base)                   ((base) + (0x818))

/* 寄存器说明：JTAG_TDI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_007_UNION */
#define SOC_IOC_IOCG_007_ADDR(base)                   ((base) + (0x81C))

/* 寄存器说明：JTAG_TDO功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_008_UNION */
#define SOC_IOC_IOCG_008_ADDR(base)                   ((base) + (0x820))

/* 寄存器说明：I2C3_SCL功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_009_UNION */
#define SOC_IOC_IOCG_009_ADDR(base)                   ((base) + (0x824))

/* 寄存器说明：I2C3_SDA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_010_UNION */
#define SOC_IOC_IOCG_010_ADDR(base)                   ((base) + (0x828))

/* 寄存器说明：SPI1_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_011_UNION */
#define SOC_IOC_IOCG_011_ADDR(base)                   ((base) + (0x82C))

/* 寄存器说明：SPI1_DI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_012_UNION */
#define SOC_IOC_IOCG_012_ADDR(base)                   ((base) + (0x830))

/* 寄存器说明：SPI1_DO功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_013_UNION */
#define SOC_IOC_IOCG_013_ADDR(base)                   ((base) + (0x834))

/* 寄存器说明：SPI1_CS_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_014_UNION */
#define SOC_IOC_IOCG_014_ADDR(base)                   ((base) + (0x838))

/* 寄存器说明：SPDIF功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_015_UNION */
#define SOC_IOC_IOCG_015_ADDR(base)                   ((base) + (0x83C))

/* 寄存器说明：GPS_REF功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_016_UNION */
#define SOC_IOC_IOCG_016_ADDR(base)                   ((base) + (0x840))

/* 寄存器说明：ISP_GPIO00_FTRSTN功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_017_UNION */
#define SOC_IOC_IOCG_017_ADDR(base)                   ((base) + (0x844))

/* 寄存器说明：ISP_GPIO01_BKRSTN功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_018_UNION */
#define SOC_IOC_IOCG_018_ADDR(base)                   ((base) + (0x848))

/* 寄存器说明：ISP_GPIO02_MNTRB功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_019_UNION */
#define SOC_IOC_IOCG_019_ADDR(base)                   ((base) + (0x84C))

/* 寄存器说明：ISP_GPIO06_FSYNC功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_020_UNION */
#define SOC_IOC_IOCG_020_ADDR(base)                   ((base) + (0x850))

/* 寄存器说明：ISP_GPIO10_SBPWM功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_021_UNION */
#define SOC_IOC_IOCG_021_ADDR(base)                   ((base) + (0x854))

/* 寄存器说明：ISP_CLK0功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_022_UNION */
#define SOC_IOC_IOCG_022_ADDR(base)                   ((base) + (0x858))

/* 寄存器说明：ISP_CLK1功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_023_UNION */
#define SOC_IOC_IOCG_023_ADDR(base)                   ((base) + (0x85C))

/* 寄存器说明：ISP_CLK2功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_024_UNION */
#define SOC_IOC_IOCG_024_ADDR(base)                   ((base) + (0x860))

/* 寄存器说明：ISP_SCL0功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_025_UNION */
#define SOC_IOC_IOCG_025_ADDR(base)                   ((base) + (0x864))

/* 寄存器说明：ISP_SDA0功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_026_UNION */
#define SOC_IOC_IOCG_026_ADDR(base)                   ((base) + (0x868))

/* 寄存器说明：ISP_SCL1功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_027_UNION */
#define SOC_IOC_IOCG_027_ADDR(base)                   ((base) + (0x86C))

/* 寄存器说明：ISP_SDA1功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_028_UNION */
#define SOC_IOC_IOCG_028_ADDR(base)                   ((base) + (0x870))

/* 寄存器说明：ISP_SCL2功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_029_UNION */
#define SOC_IOC_IOCG_029_ADDR(base)                   ((base) + (0x874))

/* 寄存器说明：ISP_SDA2功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_030_UNION */
#define SOC_IOC_IOCG_030_ADDR(base)                   ((base) + (0x878))

/* 寄存器说明：SDIO1_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_031_UNION */
#define SOC_IOC_IOCG_031_ADDR(base)                   ((base) + (0x87C))

/* 寄存器说明：SDIO1_CMD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_032_UNION */
#define SOC_IOC_IOCG_032_ADDR(base)                   ((base) + (0x880))

/* 寄存器说明：SDIO1_DATA0功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_033_UNION */
#define SOC_IOC_IOCG_033_ADDR(base)                   ((base) + (0x884))

/* 寄存器说明：SDIO1_DATA1功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_034_UNION */
#define SOC_IOC_IOCG_034_ADDR(base)                   ((base) + (0x888))

/* 寄存器说明：SDIO1_DATA2功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_035_UNION */
#define SOC_IOC_IOCG_035_ADDR(base)                   ((base) + (0x88C))

/* 寄存器说明：SDIO1_DATA3功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_036_UNION */
#define SOC_IOC_IOCG_036_ADDR(base)                   ((base) + (0x890))

/* 寄存器说明：I2C4_SCL功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_037_UNION */
#define SOC_IOC_IOCG_037_ADDR(base)                   ((base) + (0x894))

/* 寄存器说明：I2C4_SDA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_038_UNION */
#define SOC_IOC_IOCG_038_ADDR(base)                   ((base) + (0x898))

/* 寄存器说明：I2C5_SCL功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_039_UNION */
#define SOC_IOC_IOCG_039_ADDR(base)                   ((base) + (0x89C))

/* 寄存器说明：I2C5_SDA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_040_UNION */
#define SOC_IOC_IOCG_040_ADDR(base)                   ((base) + (0x8A0))

/* 寄存器说明：SD_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_041_UNION */
#define SOC_IOC_IOCG_041_ADDR(base)                   ((base) + (0x8A4))

/* 寄存器说明：SD_CMD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_042_UNION */
#define SOC_IOC_IOCG_042_ADDR(base)                   ((base) + (0x8A8))

/* 寄存器说明：SD_DATA0功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_043_UNION */
#define SOC_IOC_IOCG_043_ADDR(base)                   ((base) + (0x8AC))

/* 寄存器说明：SD_DATA1功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_044_UNION */
#define SOC_IOC_IOCG_044_ADDR(base)                   ((base) + (0x8B0))

/* 寄存器说明：SD_DATA2功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_045_UNION */
#define SOC_IOC_IOCG_045_ADDR(base)                   ((base) + (0x8B4))

/* 寄存器说明：SD_DATA3功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_046_UNION */
#define SOC_IOC_IOCG_046_ADDR(base)                   ((base) + (0x8B8))

/* 寄存器说明：SPI0_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_047_UNION */
#define SOC_IOC_IOCG_047_ADDR(base)                   ((base) + (0x8BC))

/* 寄存器说明：SPI0_DI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_048_UNION */
#define SOC_IOC_IOCG_048_ADDR(base)                   ((base) + (0x8C0))

/* 寄存器说明：SPI0_DO功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_049_UNION */
#define SOC_IOC_IOCG_049_ADDR(base)                   ((base) + (0x8C4))

/* 寄存器说明：SPI0_CS0_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_050_UNION */
#define SOC_IOC_IOCG_050_ADDR(base)                   ((base) + (0x8C8))

/* 寄存器说明：SPI0_CS1_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_051_UNION */
#define SOC_IOC_IOCG_051_ADDR(base)                   ((base) + (0x8CC))

/* 寄存器说明：SPI0_CS2_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_052_UNION */
#define SOC_IOC_IOCG_052_ADDR(base)                   ((base) + (0x8D0))

/* 寄存器说明：SPI0_CS3_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_053_UNION */
#define SOC_IOC_IOCG_053_ADDR(base)                   ((base) + (0x8D4))

/* 寄存器说明：GPIO_054功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_054_UNION */
#define SOC_IOC_IOCG_054_ADDR(base)                   ((base) + (0x8D8))

/* 寄存器说明：GPIO_055功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_055_UNION */
#define SOC_IOC_IOCG_055_ADDR(base)                   ((base) + (0x8DC))

/* 寄存器说明：EMMC50_RST_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_056_UNION */
#define SOC_IOC_IOCG_056_ADDR(base)                   ((base) + (0x8E0))

/* 寄存器说明：UART1_CTS_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_057_UNION */
#define SOC_IOC_IOCG_057_ADDR(base)                   ((base) + (0x8E4))

/* 寄存器说明：UART1_RTS_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_058_UNION */
#define SOC_IOC_IOCG_058_ADDR(base)                   ((base) + (0x8E8))

/* 寄存器说明：UART1_RXD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_059_UNION */
#define SOC_IOC_IOCG_059_ADDR(base)                   ((base) + (0x8EC))

/* 寄存器说明：UART1_TXD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_060_UNION */
#define SOC_IOC_IOCG_060_ADDR(base)                   ((base) + (0x8F0))

/* 寄存器说明：SDIO0_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_061_UNION */
#define SOC_IOC_IOCG_061_ADDR(base)                   ((base) + (0x8F4))

/* 寄存器说明：SDIO0_CMD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_062_UNION */
#define SOC_IOC_IOCG_062_ADDR(base)                   ((base) + (0x8F8))

/* 寄存器说明：SDIO0_DATA0功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_063_UNION */
#define SOC_IOC_IOCG_063_ADDR(base)                   ((base) + (0x8FC))

/* 寄存器说明：SDIO0_DATA1功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_064_UNION */
#define SOC_IOC_IOCG_064_ADDR(base)                   ((base) + (0x900))

/* 寄存器说明：SDIO0_DATA2功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_065_UNION */
#define SOC_IOC_IOCG_065_ADDR(base)                   ((base) + (0x904))

/* 寄存器说明：SDIO0_DATA3功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_066_UNION */
#define SOC_IOC_IOCG_066_ADDR(base)                   ((base) + (0x908))

/* 寄存器说明：UART6_CTS_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_067_UNION */
#define SOC_IOC_IOCG_067_ADDR(base)                   ((base) + (0x90C))

/* 寄存器说明：UART6_RTS_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_068_UNION */
#define SOC_IOC_IOCG_068_ADDR(base)                   ((base) + (0x910))

/* 寄存器说明：UART6_RXD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_069_UNION */
#define SOC_IOC_IOCG_069_ADDR(base)                   ((base) + (0x914))

/* 寄存器说明：UART6_TXD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_070_UNION */
#define SOC_IOC_IOCG_070_ADDR(base)                   ((base) + (0x918))

/* 寄存器说明：UART3_CTS_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_071_UNION */
#define SOC_IOC_IOCG_071_ADDR(base)                   ((base) + (0x91C))

/* 寄存器说明：UART3_RTS_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_072_UNION */
#define SOC_IOC_IOCG_072_ADDR(base)                   ((base) + (0x920))

/* 寄存器说明：UART3_RXD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_073_UNION */
#define SOC_IOC_IOCG_073_ADDR(base)                   ((base) + (0x924))

/* 寄存器说明：UART3_TXD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_074_UNION */
#define SOC_IOC_IOCG_074_ADDR(base)                   ((base) + (0x928))

/* 寄存器说明：UART4_CTS_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_075_UNION */
#define SOC_IOC_IOCG_075_ADDR(base)                   ((base) + (0x92C))

/* 寄存器说明：UART4_RTS_N功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_076_UNION */
#define SOC_IOC_IOCG_076_ADDR(base)                   ((base) + (0x930))

/* 寄存器说明：UART4_RXD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_077_UNION */
#define SOC_IOC_IOCG_077_ADDR(base)                   ((base) + (0x934))

/* 寄存器说明：UART4_TXD功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_078_UNION */
#define SOC_IOC_IOCG_078_ADDR(base)                   ((base) + (0x938))

/* 寄存器说明：PWM_OUT1功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_079_UNION */
#define SOC_IOC_IOCG_079_ADDR(base)                   ((base) + (0x93C))

/* 寄存器说明：PMU_HKADC_SSI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_080_UNION */
#define SOC_IOC_IOCG_080_ADDR(base)                   ((base) + (0x940))

/* 寄存器说明：PMU_AUXDAC0_SSI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_081_UNION */
#define SOC_IOC_IOCG_081_ADDR(base)                   ((base) + (0x944))

/* 寄存器说明：PMU_AUXDAC1_SSI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_082_UNION */
#define SOC_IOC_IOCG_082_ADDR(base)                   ((base) + (0x948))

/* 寄存器说明：USIM0_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_083_UNION */
#define SOC_IOC_IOCG_083_ADDR(base)                   ((base) + (0x94C))

/* 寄存器说明：USIM0_RST功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_084_UNION */
#define SOC_IOC_IOCG_084_ADDR(base)                   ((base) + (0x950))

/* 寄存器说明：USIM0_DATA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_085_UNION */
#define SOC_IOC_IOCG_085_ADDR(base)                   ((base) + (0x954))

/* 寄存器说明：USIM1_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_086_UNION */
#define SOC_IOC_IOCG_086_ADDR(base)                   ((base) + (0x958))

/* 寄存器说明：USIM1_RST功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_087_UNION */
#define SOC_IOC_IOCG_087_ADDR(base)                   ((base) + (0x95C))

/* 寄存器说明：USIM1_DATA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_088_UNION */
#define SOC_IOC_IOCG_088_ADDR(base)                   ((base) + (0x960))

/* 寄存器说明：LTE_INACTIVE功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_089_UNION */
#define SOC_IOC_IOCG_089_ADDR(base)                   ((base) + (0x964))

/* 寄存器说明：LTE_RX_ACTIVE功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_090_UNION */
#define SOC_IOC_IOCG_090_ADDR(base)                   ((base) + (0x968))

/* 寄存器说明：LTE_TX_ACTIVE功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_091_UNION */
#define SOC_IOC_IOCG_091_ADDR(base)                   ((base) + (0x96C))

/* 寄存器说明：ISM_PRIORITY功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_092_UNION */
#define SOC_IOC_IOCG_092_ADDR(base)                   ((base) + (0x970))

/* 寄存器说明：CH0_AFC_PDM功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_093_UNION */
#define SOC_IOC_IOCG_093_ADDR(base)                   ((base) + (0x974))

/* 寄存器说明：CH0_APT_PDM功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_094_UNION */
#define SOC_IOC_IOCG_094_ADDR(base)                   ((base) + (0x978))

/* 寄存器说明：CH0_RF_RESETN功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_095_UNION */
#define SOC_IOC_IOCG_095_ADDR(base)                   ((base) + (0x97C))

/* 寄存器说明：CH0_RF_SSI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_096_UNION */
#define SOC_IOC_IOCG_096_ADDR(base)                   ((base) + (0x980))

/* 寄存器说明：CH0_RF_TCVR_ON功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_097_UNION */
#define SOC_IOC_IOCG_097_ADDR(base)                   ((base) + (0x984))

/* 寄存器说明：CH2_AFC_PDM功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_098_UNION */
#define SOC_IOC_IOCG_098_ADDR(base)                   ((base) + (0x988))

/* 寄存器说明：CH1_APT_PDM功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_099_UNION */
#define SOC_IOC_IOCG_099_ADDR(base)                   ((base) + (0x98C))

/* 寄存器说明：CH1_RF_RESETN功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_100_UNION */
#define SOC_IOC_IOCG_100_ADDR(base)                   ((base) + (0x990))

/* 寄存器说明：CH1_RF_SSI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_101_UNION */
#define SOC_IOC_IOCG_101_ADDR(base)                   ((base) + (0x994))

/* 寄存器说明：CH1_RF_TCVR_ON功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_102_UNION */
#define SOC_IOC_IOCG_102_ADDR(base)                   ((base) + (0x998))

/* 寄存器说明：CH2_RF_RESETN功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_103_UNION */
#define SOC_IOC_IOCG_103_ADDR(base)                   ((base) + (0x99C))

/* 寄存器说明：CH2_RF_SSI功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_104_UNION */
#define SOC_IOC_IOCG_104_ADDR(base)                   ((base) + (0x9A0))

/* 寄存器说明：CH2_RF_TCVR_ON功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_105_UNION */
#define SOC_IOC_IOCG_105_ADDR(base)                   ((base) + (0x9A4))

/* 寄存器说明：FE0_MIPI_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_106_UNION */
#define SOC_IOC_IOCG_106_ADDR(base)                   ((base) + (0x9A8))

/* 寄存器说明：FE0_MIPI_DATA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_107_UNION */
#define SOC_IOC_IOCG_107_ADDR(base)                   ((base) + (0x9AC))

/* 寄存器说明：FE1_MIPI_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_108_UNION */
#define SOC_IOC_IOCG_108_ADDR(base)                   ((base) + (0x9B0))

/* 寄存器说明：FE1_MIPI_DATA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_109_UNION */
#define SOC_IOC_IOCG_109_ADDR(base)                   ((base) + (0x9B4))

/* 寄存器说明：FLASH_MASK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_110_UNION */
#define SOC_IOC_IOCG_110_ADDR(base)                   ((base) + (0x9B8))

/* 寄存器说明：GPS_BLANKING功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_111_UNION */
#define SOC_IOC_IOCG_111_ADDR(base)                   ((base) + (0x9BC))

/* 寄存器说明：ANTPA_SEL00功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_112_UNION */
#define SOC_IOC_IOCG_112_ADDR(base)                   ((base) + (0x9C0))

/* 寄存器说明：ANTPA_SEL01功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_113_UNION */
#define SOC_IOC_IOCG_113_ADDR(base)                   ((base) + (0x9C4))

/* 寄存器说明：ANTPA_SEL02功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_114_UNION */
#define SOC_IOC_IOCG_114_ADDR(base)                   ((base) + (0x9C8))

/* 寄存器说明：ANTPA_SEL03功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_115_UNION */
#define SOC_IOC_IOCG_115_ADDR(base)                   ((base) + (0x9CC))

/* 寄存器说明：ANTPA_SEL04功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_116_UNION */
#define SOC_IOC_IOCG_116_ADDR(base)                   ((base) + (0x9D0))

/* 寄存器说明：ANTPA_SEL05功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_117_UNION */
#define SOC_IOC_IOCG_117_ADDR(base)                   ((base) + (0x9D4))

/* 寄存器说明：ANTPA_SEL06功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_118_UNION */
#define SOC_IOC_IOCG_118_ADDR(base)                   ((base) + (0x9D8))

/* 寄存器说明：ANTPA_SEL07功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_119_UNION */
#define SOC_IOC_IOCG_119_ADDR(base)                   ((base) + (0x9DC))

/* 寄存器说明：ANTPA_SEL08功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_120_UNION */
#define SOC_IOC_IOCG_120_ADDR(base)                   ((base) + (0x9E0))

/* 寄存器说明：ANTPA_SEL09功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_121_UNION */
#define SOC_IOC_IOCG_121_ADDR(base)                   ((base) + (0x9E4))

/* 寄存器说明：ANTPA_SEL10功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_122_UNION */
#define SOC_IOC_IOCG_122_ADDR(base)                   ((base) + (0x9E8))

/* 寄存器说明：ANTPA_SEL11功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_123_UNION */
#define SOC_IOC_IOCG_123_ADDR(base)                   ((base) + (0x9EC))

/* 寄存器说明：ANTPA_SEL12功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_124_UNION */
#define SOC_IOC_IOCG_124_ADDR(base)                   ((base) + (0x9F0))

/* 寄存器说明：ANTPA_SEL13功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_125_UNION */
#define SOC_IOC_IOCG_125_ADDR(base)                   ((base) + (0x9F4))

/* 寄存器说明：ANTPA_SEL14功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_126_UNION */
#define SOC_IOC_IOCG_126_ADDR(base)                   ((base) + (0x9F8))

/* 寄存器说明：ANTPA_SEL15功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_127_UNION */
#define SOC_IOC_IOCG_127_ADDR(base)                   ((base) + (0x9FC))

/* 寄存器说明：ANTPA_SEL16功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_128_UNION */
#define SOC_IOC_IOCG_128_ADDR(base)                   ((base) + (0xA00))

/* 寄存器说明：ANTPA_SEL17功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_129_UNION */
#define SOC_IOC_IOCG_129_ADDR(base)                   ((base) + (0xA04))

/* 寄存器说明：ANTPA_SEL18功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_130_UNION */
#define SOC_IOC_IOCG_130_ADDR(base)                   ((base) + (0xA08))

/* 寄存器说明：ANTPA_SEL19功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_131_UNION */
#define SOC_IOC_IOCG_131_ADDR(base)                   ((base) + (0xA0C))

/* 寄存器说明：ANTPA_SEL20功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_132_UNION */
#define SOC_IOC_IOCG_132_ADDR(base)                   ((base) + (0xA10))

/* 寄存器说明：ANTPA_SEL21功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_133_UNION */
#define SOC_IOC_IOCG_133_ADDR(base)                   ((base) + (0xA14))

/* 寄存器说明：ANTPA_SEL22功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_134_UNION */
#define SOC_IOC_IOCG_134_ADDR(base)                   ((base) + (0xA18))

/* 寄存器说明：ANTPA_SEL23功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_135_UNION */
#define SOC_IOC_IOCG_135_ADDR(base)                   ((base) + (0xA1C))

/* 寄存器说明：ANTPA_SEL24功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_136_UNION */
#define SOC_IOC_IOCG_136_ADDR(base)                   ((base) + (0xA20))

/* 寄存器说明：ANTPA_SEL25功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_137_UNION */
#define SOC_IOC_IOCG_137_ADDR(base)                   ((base) + (0xA24))

/* 寄存器说明：ANTPA_SEL26功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_138_UNION */
#define SOC_IOC_IOCG_138_ADDR(base)                   ((base) + (0xA28))

/* 寄存器说明：ANTPA_SEL27功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_139_UNION */
#define SOC_IOC_IOCG_139_ADDR(base)                   ((base) + (0xA2C))

/* 寄存器说明：GPIO_140功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_140_UNION */
#define SOC_IOC_IOCG_140_ADDR(base)                   ((base) + (0xA30))

/* 寄存器说明：GPIO_141功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_141_UNION */
#define SOC_IOC_IOCG_141_ADDR(base)                   ((base) + (0xA34))

/* 寄存器说明：GPIO_142功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_142_UNION */
#define SOC_IOC_IOCG_142_ADDR(base)                   ((base) + (0xA38))

/* 寄存器说明：GPIO_143功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_143_UNION */
#define SOC_IOC_IOCG_143_ADDR(base)                   ((base) + (0xA3C))

/* 寄存器说明：GPIO_144功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_144_UNION */
#define SOC_IOC_IOCG_144_ADDR(base)                   ((base) + (0xA40))

/* 寄存器说明：GPIO_145功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_145_UNION */
#define SOC_IOC_IOCG_145_ADDR(base)                   ((base) + (0xA44))

/* 寄存器说明：GPIO_146功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_146_UNION */
#define SOC_IOC_IOCG_146_ADDR(base)                   ((base) + (0xA48))

/* 寄存器说明：GPIO_147功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_147_UNION */
#define SOC_IOC_IOCG_147_ADDR(base)                   ((base) + (0xA4C))

/* 寄存器说明：GPIO_148功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_148_UNION */
#define SOC_IOC_IOCG_148_ADDR(base)                   ((base) + (0xA50))

/* 寄存器说明：GPIO_149功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_149_UNION */
#define SOC_IOC_IOCG_149_ADDR(base)                   ((base) + (0xA54))

/* 寄存器说明：GPIO_150功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_150_UNION */
#define SOC_IOC_IOCG_150_ADDR(base)                   ((base) + (0xA58))

/* 寄存器说明：GPIO_151功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_151_UNION */
#define SOC_IOC_IOCG_151_ADDR(base)                   ((base) + (0xA5C))

/* 寄存器说明：GPIO_152功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_152_UNION */
#define SOC_IOC_IOCG_152_ADDR(base)                   ((base) + (0xA60))

/* 寄存器说明：GPIO_153功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_153_UNION */
#define SOC_IOC_IOCG_153_ADDR(base)                   ((base) + (0xA64))

/* 寄存器说明：GPIO_154功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_154_UNION */
#define SOC_IOC_IOCG_154_ADDR(base)                   ((base) + (0xA68))

/* 寄存器说明：GPIO_155功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_155_UNION */
#define SOC_IOC_IOCG_155_ADDR(base)                   ((base) + (0xA6C))

/* 寄存器说明：GPIO_156功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_156_UNION */
#define SOC_IOC_IOCG_156_ADDR(base)                   ((base) + (0xA70))

/* 寄存器说明：GPIO_157功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_157_UNION */
#define SOC_IOC_IOCG_157_ADDR(base)                   ((base) + (0xA74))

/* 寄存器说明：GPIO_158功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_158_UNION */
#define SOC_IOC_IOCG_158_ADDR(base)                   ((base) + (0xA78))

/* 寄存器说明：GPIO_159功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_159_UNION */
#define SOC_IOC_IOCG_159_ADDR(base)                   ((base) + (0xA7C))

/* 寄存器说明：GPIO_160功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_160_UNION */
#define SOC_IOC_IOCG_160_ADDR(base)                   ((base) + (0xA80))

/* 寄存器说明：GPIO_161功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_161_UNION */
#define SOC_IOC_IOCG_161_ADDR(base)                   ((base) + (0xA84))

/* 寄存器说明：GPIO_162功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_162_UNION */
#define SOC_IOC_IOCG_162_ADDR(base)                   ((base) + (0xA88))

/* 寄存器说明：GPIO_163功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_163_UNION */
#define SOC_IOC_IOCG_163_ADDR(base)                   ((base) + (0xA8C))

/* 寄存器说明：GPIO_164功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_164_UNION */
#define SOC_IOC_IOCG_164_ADDR(base)                   ((base) + (0xA90))

/* 寄存器说明：GPIO_165功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_165_UNION */
#define SOC_IOC_IOCG_165_ADDR(base)                   ((base) + (0xA94))

/* 寄存器说明：GPIO_166功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_166_UNION */
#define SOC_IOC_IOCG_166_ADDR(base)                   ((base) + (0xA98))

/* 寄存器说明：GPIO_167功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_167_UNION */
#define SOC_IOC_IOCG_167_ADDR(base)                   ((base) + (0xA9C))

/* 寄存器说明：GPIO_168功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_168_UNION */
#define SOC_IOC_IOCG_168_ADDR(base)                   ((base) + (0xAA0))

/* 寄存器说明：GPIO_169功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_169_UNION */
#define SOC_IOC_IOCG_169_ADDR(base)                   ((base) + (0xAA4))

/* 寄存器说明：GPIO_170功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_170_UNION */
#define SOC_IOC_IOCG_170_ADDR(base)                   ((base) + (0xAA8))

/* 寄存器说明：GPIO_171功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_171_UNION */
#define SOC_IOC_IOCG_171_ADDR(base)                   ((base) + (0xAAC))

/* 寄存器说明：GPIO_172功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_172_UNION */
#define SOC_IOC_IOCG_172_ADDR(base)                   ((base) + (0xAB0))

/* 寄存器说明：GPIO_173功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_173_UNION */
#define SOC_IOC_IOCG_173_ADDR(base)                   ((base) + (0xAB4))

/* 寄存器说明：GPIO_174功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_174_UNION */
#define SOC_IOC_IOCG_174_ADDR(base)                   ((base) + (0xAB8))

/* 寄存器说明：GPIO_175功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_IOCG_175_UNION */
#define SOC_IOC_IOCG_175_ADDR(base)                   ((base) + (0xABC))





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
 结构名    : SOC_IOC_IOMG_000_UNION
 结构说明  : IOMG_000 寄存器结构定义。地址偏移量:0x000，初值:0x00000001，宽度:32
 寄存器说明: TEST_MODE管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_000 : 1;  /* bit[0]   : TEST_MODE管脚的具体复用情况。
                                                   0：GPIO_001；
                                                   1：TEST_MODE。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_000_UNION;
#endif
#define SOC_IOC_IOMG_000_iomg_000_START  (0)
#define SOC_IOC_IOMG_000_iomg_000_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_001_UNION
 结构说明  : IOMG_001 寄存器结构定义。地址偏移量:0x004，初值:0x00000001，宽度:32
 寄存器说明: PMU0_SSI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_001 : 1;  /* bit[0]   : PMU0_SSI管脚的具体复用情况。
                                                   0：GPIO_002；
                                                   1：PMU0_SSI。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_001_UNION;
#endif
#define SOC_IOC_IOMG_001_iomg_001_START  (0)
#define SOC_IOC_IOMG_001_iomg_001_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_002_UNION
 结构说明  : IOMG_002 寄存器结构定义。地址偏移量:0x008，初值:0x00000001，宽度:32
 寄存器说明: PMU1_SSI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_002 : 2;  /* bit[0-1] : PMU1_SSI管脚的具体复用情况。
                                                   00：GPIO_003；
                                                   01：PMU1_SSI；
                                                   11：GPIO_028_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_002_UNION;
#endif
#define SOC_IOC_IOMG_002_iomg_002_START  (0)
#define SOC_IOC_IOMG_002_iomg_002_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_003_UNION
 结构说明  : IOMG_003 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: JTAG_TRST_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_003 : 2;  /* bit[0-1] : JTAG_TRST_N管脚的具体复用情况。
                                                   00：GPIO_006；
                                                   01：JTAG_TRST_N；
                                                   10：JTAG_TRST_N；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_003_UNION;
#endif
#define SOC_IOC_IOMG_003_iomg_003_START  (0)
#define SOC_IOC_IOMG_003_iomg_003_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_004_UNION
 结构说明  : IOMG_004 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: JTAG_TDI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_004 : 2;  /* bit[0-1] : JTAG_TDI管脚的具体复用情况。
                                                   00：GPIO_007；
                                                   01：JTAG_TDI；
                                                   10：JTAG_TDI；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_004_UNION;
#endif
#define SOC_IOC_IOMG_004_iomg_004_START  (0)
#define SOC_IOC_IOMG_004_iomg_004_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_005_UNION
 结构说明  : IOMG_005 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: JTAG_TDO管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_005 : 2;  /* bit[0-1] : JTAG_TDO管脚的具体复用情况。
                                                   00：GPIO_008；
                                                   01：JTAG_TDO；
                                                   10：JTAG_TDO；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_005_UNION;
#endif
#define SOC_IOC_IOMG_005_iomg_005_START  (0)
#define SOC_IOC_IOMG_005_iomg_005_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_006_UNION
 结构说明  : IOMG_006 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: I2C3_SCL管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_006 : 3;  /* bit[0-2] : I2C3_SCL管脚的具体复用情况。
                                                   000：GPIO_009；
                                                   001：I2C3_SCL；
                                                   010：UART0_RTS_N；
                                                   011：GPIO_029_SH；
                                                   111：TEST_000；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_006_UNION;
#endif
#define SOC_IOC_IOMG_006_iomg_006_START  (0)
#define SOC_IOC_IOMG_006_iomg_006_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_007_UNION
 结构说明  : IOMG_007 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: I2C3_SDA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_007 : 3;  /* bit[0-2] : I2C3_SDA管脚的具体复用情况。
                                                   000：GPIO_010；
                                                   001：I2C3_SDA；
                                                   010：UART0_CTS_N；
                                                   011：GPIO_030_SH；
                                                   111：TEST_001；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_007_UNION;
#endif
#define SOC_IOC_IOMG_007_iomg_007_START  (0)
#define SOC_IOC_IOMG_007_iomg_007_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_008_UNION
 结构说明  : IOMG_008 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: SPI1_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_008 : 3;  /* bit[0-2] : SPI1_CLK管脚的具体复用情况。
                                                   000：GPIO_011；
                                                   001：SPI1_CLK；
                                                   010：UART2_CTS_N；
                                                   011：I2S1_DI；
                                                   111：TEST_002；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_008_UNION;
#endif
#define SOC_IOC_IOMG_008_iomg_008_START  (0)
#define SOC_IOC_IOMG_008_iomg_008_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_009_UNION
 结构说明  : IOMG_009 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: SPI1_DI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_009 : 3;  /* bit[0-2] : SPI1_DI管脚的具体复用情况。
                                                   000：GPIO_012；
                                                   001：SPI1_DI；
                                                   010：UART2_RTS_N；
                                                   011：I2S1_DO；
                                                   111：TEST_003；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_009_UNION;
#endif
#define SOC_IOC_IOMG_009_iomg_009_START  (0)
#define SOC_IOC_IOMG_009_iomg_009_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_010_UNION
 结构说明  : IOMG_010 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: SPI1_DO管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_010 : 3;  /* bit[0-2] : SPI1_DO管脚的具体复用情况。
                                                   000：GPIO_013；
                                                   001：SPI1_DO；
                                                   010：UART2_RXD；
                                                   011：I2S1_XCLK；
                                                   111：TEST_004；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_010_UNION;
#endif
#define SOC_IOC_IOMG_010_iomg_010_START  (0)
#define SOC_IOC_IOMG_010_iomg_010_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_011_UNION
 结构说明  : IOMG_011 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: SPI1_CS_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_011 : 3;  /* bit[0-2] : SPI1_CS_N管脚的具体复用情况。
                                                   000：GPIO_014；
                                                   001：SPI1_CS_N；
                                                   010：UART2_TXD；
                                                   011：I2S1_XFS；
                                                   111：TEST_005；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_011_UNION;
#endif
#define SOC_IOC_IOMG_011_iomg_011_START  (0)
#define SOC_IOC_IOMG_011_iomg_011_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_012_UNION
 结构说明  : IOMG_012 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: SPDIF管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_012 : 3;  /* bit[0-2] : SPDIF管脚的具体复用情况。
                                                   000：GPIO_015；
                                                   001：SPDIF；
                                                   111：TEST_006；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_012_UNION;
#endif
#define SOC_IOC_IOMG_012_iomg_012_START  (0)
#define SOC_IOC_IOMG_012_iomg_012_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_013_UNION
 结构说明  : IOMG_013 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: GPS_REF管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_013 : 3;  /* bit[0-2] : GPS_REF管脚的具体复用情况。
                                                   000：GPIO_016；
                                                   001：GPS_REF；
                                                   010：GPS_PWM；
                                                   101：TRACECLK；
                                                   111：TEST_007；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_013_UNION;
#endif
#define SOC_IOC_IOMG_013_iomg_013_START  (0)
#define SOC_IOC_IOMG_013_iomg_013_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_014_UNION
 结构说明  : IOMG_014 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO00_FTRSTN管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_014 : 3;  /* bit[0-2] : ISP_GPIO00_FTRSTN管脚的具体复用情况。
                                                   000：GPIO_017；
                                                   001：ISP_GPIO00_FTRSTN；
                                                   011：I2S1_DI；
                                                   111：TEST_008；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_014_UNION;
#endif
#define SOC_IOC_IOMG_014_iomg_014_START  (0)
#define SOC_IOC_IOMG_014_iomg_014_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_015_UNION
 结构说明  : IOMG_015 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO01_BKRSTN管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_015 : 3;  /* bit[0-2] : ISP_GPIO01_BKRSTN管脚的具体复用情况。
                                                   000：GPIO_018；
                                                   001：ISP_GPIO01_BKRSTN；
                                                   011：I2S1_DO；
                                                   111：TEST_009；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_015_UNION;
#endif
#define SOC_IOC_IOMG_015_iomg_015_START  (0)
#define SOC_IOC_IOMG_015_iomg_015_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_016_UNION
 结构说明  : IOMG_016 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO02_MNTRB管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_016 : 3;  /* bit[0-2] : ISP_GPIO02_MNTRB管脚的具体复用情况。
                                                   000：GPIO_019；
                                                   001：ISP_GPIO02_MNTRB；
                                                   010：LCD_TE1；
                                                   011：I2S1_XCLK；
                                                   111：TEST_010；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_016_UNION;
#endif
#define SOC_IOC_IOMG_016_iomg_016_START  (0)
#define SOC_IOC_IOMG_016_iomg_016_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_017_UNION
 结构说明  : IOMG_017 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO06_FSYNC管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_017 : 3;  /* bit[0-2] : ISP_GPIO06_FSYNC管脚的具体复用情况。
                                                   000：GPIO_020；
                                                   001：ISP_GPIO06_FSYNC；
                                                   011：I2S1_XFS；
                                                   111：TEST_011；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_017_UNION;
#endif
#define SOC_IOC_IOMG_017_iomg_017_START  (0)
#define SOC_IOC_IOMG_017_iomg_017_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_018_UNION
 结构说明  : IOMG_018 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO10_SBPWM管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_018 : 3;  /* bit[0-2] : ISP_GPIO10_SBPWM管脚的具体复用情况。
                                                   000：GPIO_021；
                                                   001：ISP_GPIO10_SBPWM；
                                                   010：LCD_TE0；
                                                   111：TEST_012；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_018_UNION;
#endif
#define SOC_IOC_IOMG_018_iomg_018_START  (0)
#define SOC_IOC_IOMG_018_iomg_018_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_019_UNION
 结构说明  : IOMG_019 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: ISP_CLK0管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_019 : 3;  /* bit[0-2] : ISP_CLK0管脚的具体复用情况。
                                                   000：GPIO_022；
                                                   001：ISP_CLK0；
                                                   101：TRACEDATA00；
                                                   111：TEST_013；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_019_UNION;
#endif
#define SOC_IOC_IOMG_019_iomg_019_START  (0)
#define SOC_IOC_IOMG_019_iomg_019_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_020_UNION
 结构说明  : IOMG_020 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: ISP_CLK1管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_020 : 3;  /* bit[0-2] : ISP_CLK1管脚的具体复用情况。
                                                   000：GPIO_023；
                                                   001：ISP_CLK1；
                                                   101：TRACEDATA01；
                                                   111：TEST_014；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_020_UNION;
#endif
#define SOC_IOC_IOMG_020_iomg_020_START  (0)
#define SOC_IOC_IOMG_020_iomg_020_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_021_UNION
 结构说明  : IOMG_021 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: ISP_CLK2管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_021 : 3;  /* bit[0-2] : ISP_CLK2管脚的具体复用情况。
                                                   000：GPIO_024；
                                                   001：ISP_CLK2；
                                                   101：TRACEDATA02；
                                                   111：TEST_015；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_021_UNION;
#endif
#define SOC_IOC_IOMG_021_iomg_021_START  (0)
#define SOC_IOC_IOMG_021_iomg_021_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_022_UNION
 结构说明  : IOMG_022 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: ISP_SCL0管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_022 : 3;  /* bit[0-2] : ISP_SCL0管脚的具体复用情况。
                                                   000：GPIO_025；
                                                   001：ISP_SCL0；
                                                   101：TRACEDATA03；
                                                   111：TEST_016；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_022_UNION;
#endif
#define SOC_IOC_IOMG_022_iomg_022_START  (0)
#define SOC_IOC_IOMG_022_iomg_022_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_023_UNION
 结构说明  : IOMG_023 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: ISP_SDA0管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_023 : 3;  /* bit[0-2] : ISP_SDA0管脚的具体复用情况。
                                                   000：GPIO_026；
                                                   001：ISP_SDA0；
                                                   101：TRACEDATA04；
                                                   111：TEST_017；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_023_UNION;
#endif
#define SOC_IOC_IOMG_023_iomg_023_START  (0)
#define SOC_IOC_IOMG_023_iomg_023_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_024_UNION
 结构说明  : IOMG_024 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: ISP_SCL1管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_024 : 3;  /* bit[0-2] : ISP_SCL1管脚的具体复用情况。
                                                   000：GPIO_027；
                                                   001：ISP_SCL1；
                                                   101：TRACEDATA05；
                                                   111：TEST_018；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_024_UNION;
#endif
#define SOC_IOC_IOMG_024_iomg_024_START  (0)
#define SOC_IOC_IOMG_024_iomg_024_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_025_UNION
 结构说明  : IOMG_025 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: ISP_SDA1管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_025 : 3;  /* bit[0-2] : ISP_SDA1管脚的具体复用情况。
                                                   000：GPIO_028；
                                                   001：ISP_SDA1；
                                                   101：TRACEDATA06；
                                                   111：TEST_019；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_025_UNION;
#endif
#define SOC_IOC_IOMG_025_iomg_025_START  (0)
#define SOC_IOC_IOMG_025_iomg_025_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_026_UNION
 结构说明  : IOMG_026 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: ISP_SCL2管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_026 : 3;  /* bit[0-2] : ISP_SCL2管脚的具体复用情况。
                                                   000：GPIO_029；
                                                   001：ISP_SCL2；
                                                   011：GPIO_028_SH；
                                                   100：I2C3_SCL；
                                                   111：TEST_020；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_026_UNION;
#endif
#define SOC_IOC_IOMG_026_iomg_026_START  (0)
#define SOC_IOC_IOMG_026_iomg_026_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_027_UNION
 结构说明  : IOMG_027 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: ISP_SDA2管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_027 : 3;  /* bit[0-2] : ISP_SDA2管脚的具体复用情况。
                                                   000：GPIO_030；
                                                   001：ISP_SDA2；
                                                   010：ONEWIRE；
                                                   011：GPIO_029_SH；
                                                   100：I2C3_SDA；
                                                   111：TEST_021；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_027_UNION;
#endif
#define SOC_IOC_IOMG_027_iomg_027_START  (0)
#define SOC_IOC_IOMG_027_iomg_027_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_028_UNION
 结构说明  : IOMG_028 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: SDIO1_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_028 : 3;  /* bit[0-2] : SDIO1_CLK管脚的具体复用情况。
                                                   000：GPIO_031；
                                                   001：SDIO1_CLK；
                                                   111：TEST_022；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_028_UNION;
#endif
#define SOC_IOC_IOMG_028_iomg_028_START  (0)
#define SOC_IOC_IOMG_028_iomg_028_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_029_UNION
 结构说明  : IOMG_029 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: SDIO1_CMD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_029 : 3;  /* bit[0-2] : SDIO1_CMD管脚的具体复用情况。
                                                   000：GPIO_032；
                                                   001：SDIO1_CMD；
                                                   111：TEST_023；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_029_UNION;
#endif
#define SOC_IOC_IOMG_029_iomg_029_START  (0)
#define SOC_IOC_IOMG_029_iomg_029_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_030_UNION
 结构说明  : IOMG_030 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: SDIO1_DATA0管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_030 : 3;  /* bit[0-2] : SDIO1_DATA0管脚的具体复用情况。
                                                   000：GPIO_033；
                                                   001：SDIO1_DATA0；
                                                   010：UART0_RXD；
                                                   111：TEST_024；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_030_UNION;
#endif
#define SOC_IOC_IOMG_030_iomg_030_START  (0)
#define SOC_IOC_IOMG_030_iomg_030_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_031_UNION
 结构说明  : IOMG_031 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: SDIO1_DATA1管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_031 : 3;  /* bit[0-2] : SDIO1_DATA1管脚的具体复用情况。
                                                   000：GPIO_034；
                                                   001：SDIO1_DATA1；
                                                   010：UART0_TXD；
                                                   111：TEST_025；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_031_UNION;
#endif
#define SOC_IOC_IOMG_031_iomg_031_START  (0)
#define SOC_IOC_IOMG_031_iomg_031_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_032_UNION
 结构说明  : IOMG_032 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: SDIO1_DATA2管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_032 : 3;  /* bit[0-2] : SDIO1_DATA2管脚的具体复用情况。
                                                   000：GPIO_035；
                                                   001：SDIO1_DATA2；
                                                   010：UART0_RTS_N；
                                                   111：TEST_026；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_032_UNION;
#endif
#define SOC_IOC_IOMG_032_iomg_032_START  (0)
#define SOC_IOC_IOMG_032_iomg_032_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_033_UNION
 结构说明  : IOMG_033 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: SDIO1_DATA3管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_033 : 3;  /* bit[0-2] : SDIO1_DATA3管脚的具体复用情况。
                                                   000：GPIO_036；
                                                   001：SDIO1_DATA3；
                                                   010：UART0_CTS_N；
                                                   111：TEST_027；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_033_UNION;
#endif
#define SOC_IOC_IOMG_033_iomg_033_START  (0)
#define SOC_IOC_IOMG_033_iomg_033_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_034_UNION
 结构说明  : IOMG_034 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: I2C4_SCL管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_034 : 3;  /* bit[0-2] : I2C4_SCL管脚的具体复用情况。
                                                   000：GPIO_037；
                                                   001：I2C4_SCL；
                                                   111：TEST_028；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_034_UNION;
#endif
#define SOC_IOC_IOMG_034_iomg_034_START  (0)
#define SOC_IOC_IOMG_034_iomg_034_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_035_UNION
 结构说明  : IOMG_035 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: I2C4_SDA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_035 : 3;  /* bit[0-2] : I2C4_SDA管脚的具体复用情况。
                                                   000：GPIO_038；
                                                   001：I2C4_SDA；
                                                   111：TEST_029；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_035_UNION;
#endif
#define SOC_IOC_IOMG_035_iomg_035_START  (0)
#define SOC_IOC_IOMG_035_iomg_035_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_036_UNION
 结构说明  : IOMG_036 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: I2C5_SCL管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_036 : 3;  /* bit[0-2] : I2C5_SCL管脚的具体复用情况。
                                                   000：GPIO_039；
                                                   001：I2C5_SCL；
                                                   111：TEST_030；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_036_UNION;
#endif
#define SOC_IOC_IOMG_036_iomg_036_START  (0)
#define SOC_IOC_IOMG_036_iomg_036_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_037_UNION
 结构说明  : IOMG_037 寄存器结构定义。地址偏移量:0x094，初值:0x00000000，宽度:32
 寄存器说明: I2C5_SDA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_037 : 3;  /* bit[0-2] : I2C5_SDA管脚的具体复用情况。
                                                   000：GPIO_040；
                                                   001：I2C5_SDA；
                                                   111：TEST_031；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_037_UNION;
#endif
#define SOC_IOC_IOMG_037_iomg_037_START  (0)
#define SOC_IOC_IOMG_037_iomg_037_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_038_UNION
 结构说明  : IOMG_038 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: SD_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_038 : 3;  /* bit[0-2] : SD_CLK管脚的具体复用情况。
                                                   000：GPIO_041；
                                                   001：SD_CLK；
                                                   111：TEST_032；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_038_UNION;
#endif
#define SOC_IOC_IOMG_038_iomg_038_START  (0)
#define SOC_IOC_IOMG_038_iomg_038_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_039_UNION
 结构说明  : IOMG_039 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: SD_CMD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_039 : 3;  /* bit[0-2] : SD_CMD管脚的具体复用情况。
                                                   000：GPIO_042；
                                                   001：SD_CMD；
                                                   010：JTAG_TMS_SD；
                                                   011：JTAG_TMS_M；
                                                   111：TEST_033；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_039_UNION;
#endif
#define SOC_IOC_IOMG_039_iomg_039_START  (0)
#define SOC_IOC_IOMG_039_iomg_039_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_040_UNION
 结构说明  : IOMG_040 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: SD_DATA0管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_040 : 3;  /* bit[0-2] : SD_DATA0管脚的具体复用情况。
                                                   000：GPIO_043；
                                                   001：SD_DATA0；
                                                   010：JTAG_TCK_SD；
                                                   011：JTAG_TCK_M；
                                                   111：TEST_034；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_040_UNION;
#endif
#define SOC_IOC_IOMG_040_iomg_040_START  (0)
#define SOC_IOC_IOMG_040_iomg_040_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_041_UNION
 结构说明  : IOMG_041 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: SD_DATA1管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_041 : 3;  /* bit[0-2] : SD_DATA1管脚的具体复用情况。
                                                   000：GPIO_044；
                                                   001：SD_DATA1；
                                                   010：JTAG_TDI_SD；
                                                   011：JTAG_TDI_M；
                                                   111：TEST_035；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_041_UNION;
#endif
#define SOC_IOC_IOMG_041_iomg_041_START  (0)
#define SOC_IOC_IOMG_041_iomg_041_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_042_UNION
 结构说明  : IOMG_042 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: SD_DATA2管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_042 : 3;  /* bit[0-2] : SD_DATA2管脚的具体复用情况。
                                                   000：GPIO_045；
                                                   001：SD_DATA2；
                                                   010：JTAG_TDO_SD；
                                                   011：JTAG_TDO_M；
                                                   111：TEST_036；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_042_UNION;
#endif
#define SOC_IOC_IOMG_042_iomg_042_START  (0)
#define SOC_IOC_IOMG_042_iomg_042_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_043_UNION
 结构说明  : IOMG_043 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: SD_DATA3管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_043 : 3;  /* bit[0-2] : SD_DATA3管脚的具体复用情况。
                                                   000：GPIO_046；
                                                   001：SD_DATA3；
                                                   010：JTAG_TRST_N_SD；
                                                   011：JTAG_TRST_N_M；
                                                   111：TEST_037；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_043_UNION;
#endif
#define SOC_IOC_IOMG_043_iomg_043_START  (0)
#define SOC_IOC_IOMG_043_iomg_043_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_044_UNION
 结构说明  : IOMG_044 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: SPI0_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_044 : 3;  /* bit[0-2] : SPI0_CLK管脚的具体复用情况。
                                                   000：GPIO_047；
                                                   001：SPI0_CLK；
                                                   111：TEST_038；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_044_UNION;
#endif
#define SOC_IOC_IOMG_044_iomg_044_START  (0)
#define SOC_IOC_IOMG_044_iomg_044_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_045_UNION
 结构说明  : IOMG_045 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: SPI0_DI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_045 : 3;  /* bit[0-2] : SPI0_DI管脚的具体复用情况。
                                                   000：GPIO_048；
                                                   001：SPI0_DI；
                                                   111：TEST_039；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_045_UNION;
#endif
#define SOC_IOC_IOMG_045_iomg_045_START  (0)
#define SOC_IOC_IOMG_045_iomg_045_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_046_UNION
 结构说明  : IOMG_046 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: SPI0_DO管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_046 : 3;  /* bit[0-2] : SPI0_DO管脚的具体复用情况。
                                                   000：GPIO_049；
                                                   001：SPI0_DO；
                                                   111：TEST_040；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_046_UNION;
#endif
#define SOC_IOC_IOMG_046_iomg_046_START  (0)
#define SOC_IOC_IOMG_046_iomg_046_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_047_UNION
 结构说明  : IOMG_047 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: SPI0_CS0_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_047 : 3;  /* bit[0-2] : SPI0_CS0_N管脚的具体复用情况。
                                                   000：GPIO_050；
                                                   001：SPI0_CS0_N；
                                                   111：TEST_041；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_047_UNION;
#endif
#define SOC_IOC_IOMG_047_iomg_047_START  (0)
#define SOC_IOC_IOMG_047_iomg_047_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_048_UNION
 结构说明  : IOMG_048 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: SPI0_CS1_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_048 : 3;  /* bit[0-2] : SPI0_CS1_N管脚的具体复用情况。
                                                   000：GPIO_051；
                                                   001：SPI0_CS1_N；
                                                   111：TEST_042；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_048_UNION;
#endif
#define SOC_IOC_IOMG_048_iomg_048_START  (0)
#define SOC_IOC_IOMG_048_iomg_048_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_049_UNION
 结构说明  : IOMG_049 寄存器结构定义。地址偏移量:0x0C4，初值:0x00000000，宽度:32
 寄存器说明: SPI0_CS2_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_049 : 3;  /* bit[0-2] : SPI0_CS2_N管脚的具体复用情况。
                                                   000：GPIO_052；
                                                   001：SPI0_CS2_N；
                                                   010：UART2_CTS_N；
                                                   011：UART5_RXD；
                                                   111：TEST_043；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_049_UNION;
#endif
#define SOC_IOC_IOMG_049_iomg_049_START  (0)
#define SOC_IOC_IOMG_049_iomg_049_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_050_UNION
 结构说明  : IOMG_050 寄存器结构定义。地址偏移量:0x0C8，初值:0x00000000，宽度:32
 寄存器说明: SPI0_CS3_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_050 : 3;  /* bit[0-2] : SPI0_CS3_N管脚的具体复用情况。
                                                   000：GPIO_053；
                                                   001：SPI0_CS3_N；
                                                   010：UART2_RTS_N；
                                                   011：UART5_TXD；
                                                   100：UART5_RXD；
                                                   111：TEST_044；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_050_UNION;
#endif
#define SOC_IOC_IOMG_050_iomg_050_START  (0)
#define SOC_IOC_IOMG_050_iomg_050_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_051_UNION
 结构说明  : IOMG_051 寄存器结构定义。地址偏移量:0x0CC，初值:0x00000000，宽度:32
 寄存器说明: GPIO_054管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_051 : 3;  /* bit[0-2] : GPIO_054管脚的具体复用情况。
                                                   000：GPIO_054；
                                                   010：UART2_TXD；
                                                   011：UART5_CTS_N；
                                                   100：UART2_RXD；
                                                   111：TEST_045；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_051_UNION;
#endif
#define SOC_IOC_IOMG_051_iomg_051_START  (0)
#define SOC_IOC_IOMG_051_iomg_051_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_052_UNION
 结构说明  : IOMG_052 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000000，宽度:32
 寄存器说明: GPIO_055管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_052 : 3;  /* bit[0-2] : GPIO_055管脚的具体复用情况。
                                                   000：GPIO_055；
                                                   010：UART2_RXD；
                                                   011：UART5_RTS_N；
                                                   111：TEST_046；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_052_UNION;
#endif
#define SOC_IOC_IOMG_052_iomg_052_START  (0)
#define SOC_IOC_IOMG_052_iomg_052_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_053_UNION
 结构说明  : IOMG_053 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000000，宽度:32
 寄存器说明: EMMC50_RST_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_053 : 3;  /* bit[0-2] : EMMC50_RST_N管脚的具体复用情况。
                                                   000：GPIO_056；
                                                   001：EMMC50_RST_N；
                                                   010：EMMC45_RST_N；
                                                   111：TEST_047；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_053_UNION;
#endif
#define SOC_IOC_IOMG_053_iomg_053_START  (0)
#define SOC_IOC_IOMG_053_iomg_053_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_054_UNION
 结构说明  : IOMG_054 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000000，宽度:32
 寄存器说明: UART1_CTS_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_054 : 3;  /* bit[0-2] : UART1_CTS_N管脚的具体复用情况。
                                                   000：GPIO_057；
                                                   001：UART1_CTS_N；
                                                   010：SDIO1_DATA4；
                                                   111：TEST_048；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_054_UNION;
#endif
#define SOC_IOC_IOMG_054_iomg_054_START  (0)
#define SOC_IOC_IOMG_054_iomg_054_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_055_UNION
 结构说明  : IOMG_055 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000000，宽度:32
 寄存器说明: UART1_RTS_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_055 : 3;  /* bit[0-2] : UART1_RTS_N管脚的具体复用情况。
                                                   000：GPIO_058；
                                                   001：UART1_RTS_N；
                                                   010：SDIO1_DATA5；
                                                   111：TEST_049；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_055_UNION;
#endif
#define SOC_IOC_IOMG_055_iomg_055_START  (0)
#define SOC_IOC_IOMG_055_iomg_055_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_056_UNION
 结构说明  : IOMG_056 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: UART1_RXD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_056 : 3;  /* bit[0-2] : UART1_RXD管脚的具体复用情况。
                                                   000：GPIO_059；
                                                   001：UART1_RXD；
                                                   010：SDIO1_DATA6；
                                                   111：TEST_050；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_056_UNION;
#endif
#define SOC_IOC_IOMG_056_iomg_056_START  (0)
#define SOC_IOC_IOMG_056_iomg_056_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_057_UNION
 结构说明  : IOMG_057 寄存器结构定义。地址偏移量:0x0E4，初值:0x00000000，宽度:32
 寄存器说明: UART1_TXD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_057 : 3;  /* bit[0-2] : UART1_TXD管脚的具体复用情况。
                                                   000：GPIO_060；
                                                   001：UART1_TXD；
                                                   010：SDIO1_DATA7；
                                                   111：TEST_051；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_057_UNION;
#endif
#define SOC_IOC_IOMG_057_iomg_057_START  (0)
#define SOC_IOC_IOMG_057_iomg_057_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_058_UNION
 结构说明  : IOMG_058 寄存器结构定义。地址偏移量:0x0E8，初值:0x00000000，宽度:32
 寄存器说明: SDIO0_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_058 : 3;  /* bit[0-2] : SDIO0_CLK管脚的具体复用情况。
                                                   000：GPIO_061；
                                                   001：SDIO0_CLK；
                                                   111：TEST_052；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_058_UNION;
#endif
#define SOC_IOC_IOMG_058_iomg_058_START  (0)
#define SOC_IOC_IOMG_058_iomg_058_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_059_UNION
 结构说明  : IOMG_059 寄存器结构定义。地址偏移量:0x0EC，初值:0x00000000，宽度:32
 寄存器说明: SDIO0_CMD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_059 : 3;  /* bit[0-2] : SDIO0_CMD管脚的具体复用情况。
                                                   000：GPIO_062；
                                                   001：SDIO0_CMD；
                                                   111：TEST_053；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_059_UNION;
#endif
#define SOC_IOC_IOMG_059_iomg_059_START  (0)
#define SOC_IOC_IOMG_059_iomg_059_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_060_UNION
 结构说明  : IOMG_060 寄存器结构定义。地址偏移量:0x0F0，初值:0x00000000，宽度:32
 寄存器说明: SDIO0_DATA0管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_060 : 3;  /* bit[0-2] : SDIO0_DATA0管脚的具体复用情况。
                                                   000：GPIO_063；
                                                   001：SDIO0_DATA0；
                                                   111：TEST_054；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_060_UNION;
#endif
#define SOC_IOC_IOMG_060_iomg_060_START  (0)
#define SOC_IOC_IOMG_060_iomg_060_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_061_UNION
 结构说明  : IOMG_061 寄存器结构定义。地址偏移量:0x0F4，初值:0x00000000，宽度:32
 寄存器说明: SDIO0_DATA1管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_061 : 3;  /* bit[0-2] : SDIO0_DATA1管脚的具体复用情况。
                                                   000：GPIO_064；
                                                   001：SDIO0_DATA1；
                                                   111：TEST_055；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_061_UNION;
#endif
#define SOC_IOC_IOMG_061_iomg_061_START  (0)
#define SOC_IOC_IOMG_061_iomg_061_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_062_UNION
 结构说明  : IOMG_062 寄存器结构定义。地址偏移量:0x0F8，初值:0x00000000，宽度:32
 寄存器说明: SDIO0_DATA2管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_062 : 3;  /* bit[0-2] : SDIO0_DATA2管脚的具体复用情况。
                                                   000：GPIO_065；
                                                   001：SDIO0_DATA2；
                                                   111：TEST_056；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_062_UNION;
#endif
#define SOC_IOC_IOMG_062_iomg_062_START  (0)
#define SOC_IOC_IOMG_062_iomg_062_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_063_UNION
 结构说明  : IOMG_063 寄存器结构定义。地址偏移量:0x0FC，初值:0x00000000，宽度:32
 寄存器说明: SDIO0_DATA3管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_063 : 3;  /* bit[0-2] : SDIO0_DATA3管脚的具体复用情况。
                                                   000：GPIO_066；
                                                   001：SDIO0_DATA3；
                                                   111：TEST_057；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_063_UNION;
#endif
#define SOC_IOC_IOMG_063_iomg_063_START  (0)
#define SOC_IOC_IOMG_063_iomg_063_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_064_UNION
 结构说明  : IOMG_064 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: UART6_CTS_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_064 : 3;  /* bit[0-2] : UART6_CTS_N管脚的具体复用情况。
                                                   000：GPIO_067；
                                                   001：UART6_CTS_N；
                                                   010：UART0_RXD；
                                                   111：TEST_058；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_064_UNION;
#endif
#define SOC_IOC_IOMG_064_iomg_064_START  (0)
#define SOC_IOC_IOMG_064_iomg_064_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_065_UNION
 结构说明  : IOMG_065 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: UART6_RTS_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_065 : 3;  /* bit[0-2] : UART6_RTS_N管脚的具体复用情况。
                                                   000：GPIO_068；
                                                   001：UART6_RTS_N；
                                                   010：UART0_TXD；
                                                   111：TEST_059；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_065_UNION;
#endif
#define SOC_IOC_IOMG_065_iomg_065_START  (0)
#define SOC_IOC_IOMG_065_iomg_065_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_066_UNION
 结构说明  : IOMG_066 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: UART6_RXD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_066 : 3;  /* bit[0-2] : UART6_RXD管脚的具体复用情况。
                                                   000：GPIO_069；
                                                   001：UART6_RXD；
                                                   010：UART0_RXD_M；
                                                   111：TEST_060；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_066_UNION;
#endif
#define SOC_IOC_IOMG_066_iomg_066_START  (0)
#define SOC_IOC_IOMG_066_iomg_066_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_067_UNION
 结构说明  : IOMG_067 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: UART6_TXD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_067 : 3;  /* bit[0-2] : UART6_TXD管脚的具体复用情况。
                                                   000：GPIO_070；
                                                   001：UART6_TXD；
                                                   010：UART0_TXD_M；
                                                   111：TEST_061；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_067_UNION;
#endif
#define SOC_IOC_IOMG_067_iomg_067_START  (0)
#define SOC_IOC_IOMG_067_iomg_067_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_068_UNION
 结构说明  : IOMG_068 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: UART3_CTS_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_068 : 3;  /* bit[0-2] : UART3_CTS_N管脚的具体复用情况。
                                                   000：GPIO_071；
                                                   001：UART3_CTS_N；
                                                   111：TEST_062；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_068_UNION;
#endif
#define SOC_IOC_IOMG_068_iomg_068_START  (0)
#define SOC_IOC_IOMG_068_iomg_068_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_069_UNION
 结构说明  : IOMG_069 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: UART3_RTS_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_069 : 3;  /* bit[0-2] : UART3_RTS_N管脚的具体复用情况。
                                                   000：GPIO_072；
                                                   001：UART3_RTS_N；
                                                   111：TEST_063；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_069_UNION;
#endif
#define SOC_IOC_IOMG_069_iomg_069_START  (0)
#define SOC_IOC_IOMG_069_iomg_069_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_070_UNION
 结构说明  : IOMG_070 寄存器结构定义。地址偏移量:0x118，初值:0x00000000，宽度:32
 寄存器说明: UART3_RXD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_070 : 3;  /* bit[0-2] : UART3_RXD管脚的具体复用情况。
                                                   000：GPIO_073；
                                                   001：UART3_RXD；
                                                   111：TEST_064；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_070_UNION;
#endif
#define SOC_IOC_IOMG_070_iomg_070_START  (0)
#define SOC_IOC_IOMG_070_iomg_070_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_071_UNION
 结构说明  : IOMG_071 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: UART3_TXD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_071 : 3;  /* bit[0-2] : UART3_TXD管脚的具体复用情况。
                                                   000：GPIO_074；
                                                   001：UART3_TXD；
                                                   111：TEST_065；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_071_UNION;
#endif
#define SOC_IOC_IOMG_071_iomg_071_START  (0)
#define SOC_IOC_IOMG_071_iomg_071_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_072_UNION
 结构说明  : IOMG_072 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: UART4_CTS_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_072 : 3;  /* bit[0-2] : UART4_CTS_N管脚的具体复用情况。
                                                   000：GPIO_075；
                                                   001：UART4_CTS_N；
                                                   101：TRACECTL；
                                                   111：TEST_066；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_072_UNION;
#endif
#define SOC_IOC_IOMG_072_iomg_072_START  (0)
#define SOC_IOC_IOMG_072_iomg_072_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_073_UNION
 结构说明  : IOMG_073 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: UART4_RTS_N管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_073 : 3;  /* bit[0-2] : UART4_RTS_N管脚的具体复用情况。
                                                   000：GPIO_076；
                                                   001：UART4_RTS_N；
                                                   101：TRACEDATA07；
                                                   111：TEST_067；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_073_UNION;
#endif
#define SOC_IOC_IOMG_073_iomg_073_START  (0)
#define SOC_IOC_IOMG_073_iomg_073_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_074_UNION
 结构说明  : IOMG_074 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: UART4_RXD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_074 : 3;  /* bit[0-2] : UART4_RXD管脚的具体复用情况。
                                                   000：GPIO_077；
                                                   001：UART4_RXD；
                                                   101：TRACEDATA08；
                                                   111：TEST_068；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_074_UNION;
#endif
#define SOC_IOC_IOMG_074_iomg_074_START  (0)
#define SOC_IOC_IOMG_074_iomg_074_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_075_UNION
 结构说明  : IOMG_075 寄存器结构定义。地址偏移量:0x12C，初值:0x00000000，宽度:32
 寄存器说明: UART4_TXD管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_075 : 3;  /* bit[0-2] : UART4_TXD管脚的具体复用情况。
                                                   000：GPIO_078；
                                                   001：UART4_TXD；
                                                   101：TRACEDATA09；
                                                   111：TEST_069；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_075_UNION;
#endif
#define SOC_IOC_IOMG_075_iomg_075_START  (0)
#define SOC_IOC_IOMG_075_iomg_075_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_076_UNION
 结构说明  : IOMG_076 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: PWM_OUT1管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_076 : 3;  /* bit[0-2] : PWM_OUT1管脚的具体复用情况。
                                                   000：GPIO_079；
                                                   001：PWM_OUT1；
                                                   111：TEST_070；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_076_UNION;
#endif
#define SOC_IOC_IOMG_076_iomg_076_START  (0)
#define SOC_IOC_IOMG_076_iomg_076_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_077_UNION
 结构说明  : IOMG_077 寄存器结构定义。地址偏移量:0x134，初值:0x00000001，宽度:32
 寄存器说明: PMU_HKADC_SSI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_077 : 3;  /* bit[0-2] : PMU_HKADC_SSI管脚的具体复用情况。
                                                   000：GPIO_080；
                                                   001：PMU_HKADC_SSI；
                                                   111：TEST_071；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_077_UNION;
#endif
#define SOC_IOC_IOMG_077_iomg_077_START  (0)
#define SOC_IOC_IOMG_077_iomg_077_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_078_UNION
 结构说明  : IOMG_078 寄存器结构定义。地址偏移量:0x138，初值:0x00000001，宽度:32
 寄存器说明: PMU_AUXDAC0_SSI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_078 : 3;  /* bit[0-2] : PMU_AUXDAC0_SSI管脚的具体复用情况。
                                                   000：GPIO_081；
                                                   001：PMU_AUXDAC0_SSI；
                                                   010：PMU_AUXDAC1_SSI；
                                                   111：TEST_072；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_078_UNION;
#endif
#define SOC_IOC_IOMG_078_iomg_078_START  (0)
#define SOC_IOC_IOMG_078_iomg_078_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_079_UNION
 结构说明  : IOMG_079 寄存器结构定义。地址偏移量:0x13C，初值:0x00000001，宽度:32
 寄存器说明: PMU_AUXDAC1_SSI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_079 : 3;  /* bit[0-2] : PMU_AUXDAC1_SSI管脚的具体复用情况。
                                                   000：GPIO_082；
                                                   001：PMU_AUXDAC1_SSI；
                                                   111：TEST_073；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_079_UNION;
#endif
#define SOC_IOC_IOMG_079_iomg_079_START  (0)
#define SOC_IOC_IOMG_079_iomg_079_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_080_UNION
 结构说明  : IOMG_080 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: USIM0_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_080 : 3;  /* bit[0-2] : USIM0_CLK管脚的具体复用情况。
                                                   000：GPIO_083；
                                                   001：USIM0_CLK；
                                                   010：UICC_DP；
                                                   011：GROUND；
                                                   111：TEST_074；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_080_UNION;
#endif
#define SOC_IOC_IOMG_080_iomg_080_START  (0)
#define SOC_IOC_IOMG_080_iomg_080_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_081_UNION
 结构说明  : IOMG_081 寄存器结构定义。地址偏移量:0x144，初值:0x00000000，宽度:32
 寄存器说明: USIM0_RST管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_081 : 3;  /* bit[0-2] : USIM0_RST管脚的具体复用情况。
                                                   000：GPIO_084；
                                                   001：USIM0_RST；
                                                   010：UICC_DM；
                                                   011：GROUND；
                                                   111：TEST_075；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_081_UNION;
#endif
#define SOC_IOC_IOMG_081_iomg_081_START  (0)
#define SOC_IOC_IOMG_081_iomg_081_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_082_UNION
 结构说明  : IOMG_082 寄存器结构定义。地址偏移量:0x148，初值:0x00000000，宽度:32
 寄存器说明: USIM0_DATA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_082 : 3;  /* bit[0-2] : USIM0_DATA管脚的具体复用情况。
                                                   000：GPIO_085；
                                                   001：USIM0_DATA；
                                                   011：GROUND；
                                                   111：TEST_076；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_082_UNION;
#endif
#define SOC_IOC_IOMG_082_iomg_082_START  (0)
#define SOC_IOC_IOMG_082_iomg_082_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_083_UNION
 结构说明  : IOMG_083 寄存器结构定义。地址偏移量:0x14C，初值:0x00000000，宽度:32
 寄存器说明: USIM1_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_083 : 3;  /* bit[0-2] : USIM1_CLK管脚的具体复用情况。
                                                   000：GPIO_086；
                                                   001：USIM1_CLK；
                                                   011：GROUND；
                                                   111：TEST_077；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_083_UNION;
#endif
#define SOC_IOC_IOMG_083_iomg_083_START  (0)
#define SOC_IOC_IOMG_083_iomg_083_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_084_UNION
 结构说明  : IOMG_084 寄存器结构定义。地址偏移量:0x150，初值:0x00000000，宽度:32
 寄存器说明: USIM1_RST管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_084 : 3;  /* bit[0-2] : USIM1_RST管脚的具体复用情况。
                                                   000：GPIO_087；
                                                   001：USIM1_RST；
                                                   011：GROUND；
                                                   111：TEST_078；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_084_UNION;
#endif
#define SOC_IOC_IOMG_084_iomg_084_START  (0)
#define SOC_IOC_IOMG_084_iomg_084_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_085_UNION
 结构说明  : IOMG_085 寄存器结构定义。地址偏移量:0x154，初值:0x00000000，宽度:32
 寄存器说明: USIM1_DATA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_085 : 3;  /* bit[0-2] : USIM1_DATA管脚的具体复用情况。
                                                   000：GPIO_088；
                                                   001：USIM1_DATA；
                                                   011：GROUND；
                                                   111：TEST_079；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_085_UNION;
#endif
#define SOC_IOC_IOMG_085_iomg_085_START  (0)
#define SOC_IOC_IOMG_085_iomg_085_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_086_UNION
 结构说明  : IOMG_086 寄存器结构定义。地址偏移量:0x158，初值:0x00000000，宽度:32
 寄存器说明: LTE_INACTIVE管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_086 : 3;  /* bit[0-2] : LTE_INACTIVE管脚的具体复用情况。
                                                   000：GPIO_089；
                                                   001：LTE_INACTIVE；
                                                   010：FRAME_SYNC；
                                                   011：UART_RXD_MHS；
                                                   100：UART_CTS_N_MHS；
                                                   101：TRACEDATA10；
                                                   111：TEST_080；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_086_UNION;
#endif
#define SOC_IOC_IOMG_086_iomg_086_START  (0)
#define SOC_IOC_IOMG_086_iomg_086_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_087_UNION
 结构说明  : IOMG_087 寄存器结构定义。地址偏移量:0x15C，初值:0x00000000，宽度:32
 寄存器说明: LTE_RX_ACTIVE管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_087 : 3;  /* bit[0-2] : LTE_RX_ACTIVE管脚的具体复用情况。
                                                   000：GPIO_090；
                                                   001：LTE_RX_ACTIVE；
                                                   011：UART_RXD_MHS；
                                                   101：TRACEDATA11；
                                                   111：TEST_081；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_087_UNION;
#endif
#define SOC_IOC_IOMG_087_iomg_087_START  (0)
#define SOC_IOC_IOMG_087_iomg_087_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_088_UNION
 结构说明  : IOMG_088 寄存器结构定义。地址偏移量:0x160，初值:0x00000000，宽度:32
 寄存器说明: LTE_TX_ACTIVE管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_088 : 3;  /* bit[0-2] : LTE_TX_ACTIVE管脚的具体复用情况。
                                                   000：GPIO_091；
                                                   001：LTE_TX_ACTIVE；
                                                   010：ANTPA_SEL24；
                                                   011：UART_TXD_MHS；
                                                   101：TRACEDATA12；
                                                   111：TEST_082；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_088_UNION;
#endif
#define SOC_IOC_IOMG_088_iomg_088_START  (0)
#define SOC_IOC_IOMG_088_iomg_088_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_089_UNION
 结构说明  : IOMG_089 寄存器结构定义。地址偏移量:0x164，初值:0x00000000，宽度:32
 寄存器说明: ISM_PRIORITY管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_089 : 3;  /* bit[0-2] : ISM_PRIORITY管脚的具体复用情况。
                                                   000：GPIO_092；
                                                   001：ISM_PRIORITY；
                                                   011：UART_RTS_N_MHS；
                                                   101：TRACEDATA13；
                                                   111：TEST_083；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_089_UNION;
#endif
#define SOC_IOC_IOMG_089_iomg_089_START  (0)
#define SOC_IOC_IOMG_089_iomg_089_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_090_UNION
 结构说明  : IOMG_090 寄存器结构定义。地址偏移量:0x168，初值:0x00000000，宽度:32
 寄存器说明: CH0_AFC_PDM管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_090 : 3;  /* bit[0-2] : CH0_AFC_PDM管脚的具体复用情况。
                                                   000：GPIO_093；
                                                   001：CH0_AFC_PDM；
                                                   010：ANTPA_SEL24；
                                                   011：COM2RF_CH0_AFC_PDM；
                                                   100：CH1_AFC_PDM；
                                                   111：TEST_084；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_090_UNION;
#endif
#define SOC_IOC_IOMG_090_iomg_090_START  (0)
#define SOC_IOC_IOMG_090_iomg_090_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_091_UNION
 结构说明  : IOMG_091 寄存器结构定义。地址偏移量:0x16C，初值:0x00000000，宽度:32
 寄存器说明: CH0_APT_PDM管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_091 : 3;  /* bit[0-2] : CH0_APT_PDM管脚的具体复用情况。
                                                   000：GPIO_094；
                                                   001：CH0_APT_PDM；
                                                   010：ANTPA_SEL25；
                                                   100：CH1_APT_PDM；
                                                   111：TEST_085；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_091_UNION;
#endif
#define SOC_IOC_IOMG_091_iomg_091_START  (0)
#define SOC_IOC_IOMG_091_iomg_091_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_092_UNION
 结构说明  : IOMG_092 寄存器结构定义。地址偏移量:0x170，初值:0x00000000，宽度:32
 寄存器说明: CH0_RF_RESETN管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_092 : 3;  /* bit[0-2] : CH0_RF_RESETN管脚的具体复用情况。
                                                   000：GPIO_095；
                                                   001：CH0_RF_RESETN；
                                                   111：TEST_086；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_092_UNION;
#endif
#define SOC_IOC_IOMG_092_iomg_092_START  (0)
#define SOC_IOC_IOMG_092_iomg_092_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_093_UNION
 结构说明  : IOMG_093 寄存器结构定义。地址偏移量:0x174，初值:0x00000000，宽度:32
 寄存器说明: CH0_RF_SSI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_093 : 3;  /* bit[0-2] : CH0_RF_SSI管脚的具体复用情况。
                                                   000：GPIO_096；
                                                   001：CH0_RF_SSI；
                                                   111：TEST_087；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_093_UNION;
#endif
#define SOC_IOC_IOMG_093_iomg_093_START  (0)
#define SOC_IOC_IOMG_093_iomg_093_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_094_UNION
 结构说明  : IOMG_094 寄存器结构定义。地址偏移量:0x178，初值:0x00000000，宽度:32
 寄存器说明: CH0_RF_TCVR_ON管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_094 : 3;  /* bit[0-2] : CH0_RF_TCVR_ON管脚的具体复用情况。
                                                   000：GPIO_097；
                                                   001：CH0_RF_TCVR_ON；
                                                   111：TEST_088；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_094_UNION;
#endif
#define SOC_IOC_IOMG_094_iomg_094_START  (0)
#define SOC_IOC_IOMG_094_iomg_094_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_095_UNION
 结构说明  : IOMG_095 寄存器结构定义。地址偏移量:0x17C，初值:0x00000000，宽度:32
 寄存器说明: CH2_AFC_PDM管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_095 : 3;  /* bit[0-2] : CH2_AFC_PDM管脚的具体复用情况。
                                                   000：GPIO_098；
                                                   001：CH1_AFC_PDM；
                                                   010：CH2_AFC_PDM；
                                                   011：COM2RF_CH0_AFC_PDM；
                                                   111：TEST_089；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_095_UNION;
#endif
#define SOC_IOC_IOMG_095_iomg_095_START  (0)
#define SOC_IOC_IOMG_095_iomg_095_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_096_UNION
 结构说明  : IOMG_096 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: CH1_APT_PDM管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_096 : 3;  /* bit[0-2] : CH1_APT_PDM管脚的具体复用情况。
                                                   000：GPIO_099；
                                                   001：CH1_APT_PDM；
                                                   010：ANTPA_SEL28；
                                                   111：TEST_090；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_096_UNION;
#endif
#define SOC_IOC_IOMG_096_iomg_096_START  (0)
#define SOC_IOC_IOMG_096_iomg_096_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_097_UNION
 结构说明  : IOMG_097 寄存器结构定义。地址偏移量:0x184，初值:0x00000000，宽度:32
 寄存器说明: CH1_RF_RESETN管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_097 : 3;  /* bit[0-2] : CH1_RF_RESETN管脚的具体复用情况。
                                                   000：GPIO_100；
                                                   001：CH1_RF_RESETN；
                                                   010：ANTPA_SEL28；
                                                   111：TEST_091；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_097_UNION;
#endif
#define SOC_IOC_IOMG_097_iomg_097_START  (0)
#define SOC_IOC_IOMG_097_iomg_097_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_098_UNION
 结构说明  : IOMG_098 寄存器结构定义。地址偏移量:0x188，初值:0x00000000，宽度:32
 寄存器说明: CH1_RF_SSI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_098 : 3;  /* bit[0-2] : CH1_RF_SSI管脚的具体复用情况。
                                                   000：GPIO_101；
                                                   001：CH1_RF_SSI；
                                                   010：ANTPA_SEL29；
                                                   111：TEST_092；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_098_UNION;
#endif
#define SOC_IOC_IOMG_098_iomg_098_START  (0)
#define SOC_IOC_IOMG_098_iomg_098_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_099_UNION
 结构说明  : IOMG_099 寄存器结构定义。地址偏移量:0x18C，初值:0x00000000，宽度:32
 寄存器说明: CH1_RF_TCVR_ON管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_099 : 3;  /* bit[0-2] : CH1_RF_TCVR_ON管脚的具体复用情况。
                                                   000：GPIO_102；
                                                   001：CH1_RF_TCVR_ON；
                                                   010：ANTPA_SEL30；
                                                   111：TEST_093；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_099_UNION;
#endif
#define SOC_IOC_IOMG_099_iomg_099_START  (0)
#define SOC_IOC_IOMG_099_iomg_099_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_100_UNION
 结构说明  : IOMG_100 寄存器结构定义。地址偏移量:0x190，初值:0x00000000，宽度:32
 寄存器说明: CH2_RF_RESETN管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_100 : 3;  /* bit[0-2] : CH2_RF_RESETN管脚的具体复用情况。
                                                   000：GPIO_103；
                                                   001：CH2_RF_RESETN；
                                                   111：TEST_094；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_100_UNION;
#endif
#define SOC_IOC_IOMG_100_iomg_100_START  (0)
#define SOC_IOC_IOMG_100_iomg_100_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_101_UNION
 结构说明  : IOMG_101 寄存器结构定义。地址偏移量:0x194，初值:0x00000000，宽度:32
 寄存器说明: CH2_RF_SSI管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_101 : 3;  /* bit[0-2] : CH2_RF_SSI管脚的具体复用情况。
                                                   000：GPIO_104；
                                                   001：CH2_RF_SSI；
                                                   111：TEST_095；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_101_UNION;
#endif
#define SOC_IOC_IOMG_101_iomg_101_START  (0)
#define SOC_IOC_IOMG_101_iomg_101_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_102_UNION
 结构说明  : IOMG_102 寄存器结构定义。地址偏移量:0x198，初值:0x00000000，宽度:32
 寄存器说明: CH2_RF_TCVR_ON管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_102 : 3;  /* bit[0-2] : CH2_RF_TCVR_ON管脚的具体复用情况。
                                                   000：GPIO_105；
                                                   001：CH2_RF_TCVR_ON；
                                                   111：TEST_096；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_102_UNION;
#endif
#define SOC_IOC_IOMG_102_iomg_102_START  (0)
#define SOC_IOC_IOMG_102_iomg_102_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_103_UNION
 结构说明  : IOMG_103 寄存器结构定义。地址偏移量:0x19C，初值:0x00000000，宽度:32
 寄存器说明: FE0_MIPI_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_103 : 3;  /* bit[0-2] : FE0_MIPI_CLK管脚的具体复用情况。
                                                   000：GPIO_106；
                                                   001：FE0_MIPI_CLK；
                                                   111：TEST_097；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_103_UNION;
#endif
#define SOC_IOC_IOMG_103_iomg_103_START  (0)
#define SOC_IOC_IOMG_103_iomg_103_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_104_UNION
 结构说明  : IOMG_104 寄存器结构定义。地址偏移量:0x1A0，初值:0x00000000，宽度:32
 寄存器说明: FE0_MIPI_DATA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_104 : 3;  /* bit[0-2] : FE0_MIPI_DATA管脚的具体复用情况。
                                                   000：GPIO_107；
                                                   001：FE0_MIPI_DATA；
                                                   111：TEST_098；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_104_UNION;
#endif
#define SOC_IOC_IOMG_104_iomg_104_START  (0)
#define SOC_IOC_IOMG_104_iomg_104_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_105_UNION
 结构说明  : IOMG_105 寄存器结构定义。地址偏移量:0x1A4，初值:0x00000000，宽度:32
 寄存器说明: FE1_MIPI_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_105 : 3;  /* bit[0-2] : FE1_MIPI_CLK管脚的具体复用情况。
                                                   000：GPIO_108；
                                                   001：FE1_MIPI_CLK；
                                                   010：ANTPA_SEL26；
                                                   100：FE0_MIPI_CLK；
                                                   111：TEST_099；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_105_UNION;
#endif
#define SOC_IOC_IOMG_105_iomg_105_START  (0)
#define SOC_IOC_IOMG_105_iomg_105_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_106_UNION
 结构说明  : IOMG_106 寄存器结构定义。地址偏移量:0x1A8，初值:0x00000000，宽度:32
 寄存器说明: FE1_MIPI_DATA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_106 : 3;  /* bit[0-2] : FE1_MIPI_DATA管脚的具体复用情况。
                                                   000：GPIO_109；
                                                   001：FE1_MIPI_DATA；
                                                   010：ANTPA_SEL27；
                                                   100：FE0_MIPI_DATA；
                                                   111：TEST_100；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_106_UNION;
#endif
#define SOC_IOC_IOMG_106_iomg_106_START  (0)
#define SOC_IOC_IOMG_106_iomg_106_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_107_UNION
 结构说明  : IOMG_107 寄存器结构定义。地址偏移量:0x1AC，初值:0x00000000，宽度:32
 寄存器说明: FLASH_MASK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_107 : 3;  /* bit[0-2] : FLASH_MASK管脚的具体复用情况。
                                                   000：GPIO_110；
                                                   001：FLASH_MASK；
                                                   101：TRACEDATA14；
                                                   111：TEST_101；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_107_UNION;
#endif
#define SOC_IOC_IOMG_107_iomg_107_START  (0)
#define SOC_IOC_IOMG_107_iomg_107_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_108_UNION
 结构说明  : IOMG_108 寄存器结构定义。地址偏移量:0x1B0，初值:0x00000000，宽度:32
 寄存器说明: GPS_BLANKING管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_108 : 3;  /* bit[0-2] : GPS_BLANKING管脚的具体复用情况。
                                                   000：GPIO_111；
                                                   001：GPS_BLANKING；
                                                   010：ANTPA_SEL25；
                                                   101：TRACEDATA15；
                                                   111：TEST_102；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_108_UNION;
#endif
#define SOC_IOC_IOMG_108_iomg_108_START  (0)
#define SOC_IOC_IOMG_108_iomg_108_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_109_UNION
 结构说明  : IOMG_109 寄存器结构定义。地址偏移量:0x1B4，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL00管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_109 : 3;  /* bit[0-2] : ANTPA_SEL00管脚的具体复用情况。
                                                   000：GPIO_112；
                                                   001：ANTPA_SEL00；
                                                   111：TEST_103；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_109_UNION;
#endif
#define SOC_IOC_IOMG_109_iomg_109_START  (0)
#define SOC_IOC_IOMG_109_iomg_109_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_110_UNION
 结构说明  : IOMG_110 寄存器结构定义。地址偏移量:0x1B8，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL01管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_110 : 3;  /* bit[0-2] : ANTPA_SEL01管脚的具体复用情况。
                                                   000：GPIO_113；
                                                   001：ANTPA_SEL01；
                                                   111：TEST_104；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_110_UNION;
#endif
#define SOC_IOC_IOMG_110_iomg_110_START  (0)
#define SOC_IOC_IOMG_110_iomg_110_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_111_UNION
 结构说明  : IOMG_111 寄存器结构定义。地址偏移量:0x1BC，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL02管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_111 : 3;  /* bit[0-2] : ANTPA_SEL02管脚的具体复用情况。
                                                   000：GPIO_114；
                                                   001：ANTPA_SEL02；
                                                   111：TEST_105；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_111_UNION;
#endif
#define SOC_IOC_IOMG_111_iomg_111_START  (0)
#define SOC_IOC_IOMG_111_iomg_111_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_112_UNION
 结构说明  : IOMG_112 寄存器结构定义。地址偏移量:0x1C0，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL03管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_112 : 3;  /* bit[0-2] : ANTPA_SEL03管脚的具体复用情况。
                                                   000：GPIO_115；
                                                   001：ANTPA_SEL03；
                                                   111：TEST_106；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_112_UNION;
#endif
#define SOC_IOC_IOMG_112_iomg_112_START  (0)
#define SOC_IOC_IOMG_112_iomg_112_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_113_UNION
 结构说明  : IOMG_113 寄存器结构定义。地址偏移量:0x1C4，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL04管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_113 : 3;  /* bit[0-2] : ANTPA_SEL04管脚的具体复用情况。
                                                   000：GPIO_116；
                                                   001：ANTPA_SEL04；
                                                   111：TEST_107；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_113_UNION;
#endif
#define SOC_IOC_IOMG_113_iomg_113_START  (0)
#define SOC_IOC_IOMG_113_iomg_113_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_114_UNION
 结构说明  : IOMG_114 寄存器结构定义。地址偏移量:0x1C8，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL05管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_114 : 3;  /* bit[0-2] : ANTPA_SEL05管脚的具体复用情况。
                                                   000：GPIO_117；
                                                   001：ANTPA_SEL05；
                                                   111：TEST_108；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_114_UNION;
#endif
#define SOC_IOC_IOMG_114_iomg_114_START  (0)
#define SOC_IOC_IOMG_114_iomg_114_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_115_UNION
 结构说明  : IOMG_115 寄存器结构定义。地址偏移量:0x1CC，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL06管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_115 : 3;  /* bit[0-2] : ANTPA_SEL06管脚的具体复用情况。
                                                   000：GPIO_118；
                                                   001：ANTPA_SEL06；
                                                   111：TEST_109；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_115_UNION;
#endif
#define SOC_IOC_IOMG_115_iomg_115_START  (0)
#define SOC_IOC_IOMG_115_iomg_115_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_116_UNION
 结构说明  : IOMG_116 寄存器结构定义。地址偏移量:0x1D0，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL07管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_116 : 3;  /* bit[0-2] : ANTPA_SEL07管脚的具体复用情况。
                                                   000：GPIO_119；
                                                   001：ANTPA_SEL07；
                                                   111：TEST_110；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_116_UNION;
#endif
#define SOC_IOC_IOMG_116_iomg_116_START  (0)
#define SOC_IOC_IOMG_116_iomg_116_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_117_UNION
 结构说明  : IOMG_117 寄存器结构定义。地址偏移量:0x1D4，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL08管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_117 : 3;  /* bit[0-2] : ANTPA_SEL08管脚的具体复用情况。
                                                   000：GPIO_120；
                                                   001：ANTPA_SEL08；
                                                   111：TEST_111；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_117_UNION;
#endif
#define SOC_IOC_IOMG_117_iomg_117_START  (0)
#define SOC_IOC_IOMG_117_iomg_117_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_118_UNION
 结构说明  : IOMG_118 寄存器结构定义。地址偏移量:0x1D8，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL09管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_118 : 1;  /* bit[0]   : ANTPA_SEL09管脚的具体复用情况。
                                                   0：GPIO_121；
                                                   1：ANTPA_SEL09。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_118_UNION;
#endif
#define SOC_IOC_IOMG_118_iomg_118_START  (0)
#define SOC_IOC_IOMG_118_iomg_118_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_119_UNION
 结构说明  : IOMG_119 寄存器结构定义。地址偏移量:0x1DC，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL10管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_119 : 1;  /* bit[0]   : ANTPA_SEL10管脚的具体复用情况。
                                                   0：GPIO_122；
                                                   1：ANTPA_SEL10。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_119_UNION;
#endif
#define SOC_IOC_IOMG_119_iomg_119_START  (0)
#define SOC_IOC_IOMG_119_iomg_119_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_120_UNION
 结构说明  : IOMG_120 寄存器结构定义。地址偏移量:0x1E0，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL11管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_120 : 1;  /* bit[0]   : ANTPA_SEL11管脚的具体复用情况。
                                                   0：GPIO_123；
                                                   1：ANTPA_SEL11。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_120_UNION;
#endif
#define SOC_IOC_IOMG_120_iomg_120_START  (0)
#define SOC_IOC_IOMG_120_iomg_120_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_121_UNION
 结构说明  : IOMG_121 寄存器结构定义。地址偏移量:0x1E4，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL12管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_121 : 1;  /* bit[0]   : ANTPA_SEL12管脚的具体复用情况。
                                                   0：GPIO_124；
                                                   1：ANTPA_SEL12。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_121_UNION;
#endif
#define SOC_IOC_IOMG_121_iomg_121_START  (0)
#define SOC_IOC_IOMG_121_iomg_121_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_122_UNION
 结构说明  : IOMG_122 寄存器结构定义。地址偏移量:0x1E8，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL13管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_122 : 1;  /* bit[0]   : ANTPA_SEL13管脚的具体复用情况。
                                                   0：GPIO_125；
                                                   1：ANTPA_SEL13。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_122_UNION;
#endif
#define SOC_IOC_IOMG_122_iomg_122_START  (0)
#define SOC_IOC_IOMG_122_iomg_122_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_123_UNION
 结构说明  : IOMG_123 寄存器结构定义。地址偏移量:0x1EC，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL14管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_123 : 1;  /* bit[0]   : ANTPA_SEL14管脚的具体复用情况。
                                                   0：GPIO_126；
                                                   1：ANTPA_SEL14。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_123_UNION;
#endif
#define SOC_IOC_IOMG_123_iomg_123_START  (0)
#define SOC_IOC_IOMG_123_iomg_123_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_124_UNION
 结构说明  : IOMG_124 寄存器结构定义。地址偏移量:0x1F0，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL15管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_124 : 3;  /* bit[0-2] : ANTPA_SEL15管脚的具体复用情况。
                                                   000：GPIO_127；
                                                   001：ANTPA_SEL15；
                                                   111：TEST_MODE_MASK_N；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_124_UNION;
#endif
#define SOC_IOC_IOMG_124_iomg_124_START  (0)
#define SOC_IOC_IOMG_124_iomg_124_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_125_UNION
 结构说明  : IOMG_125 寄存器结构定义。地址偏移量:0x1F4，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL16管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_125 : 3;  /* bit[0-2] : ANTPA_SEL16管脚的具体复用情况。
                                                   000：GPIO_128；
                                                   001：ANTPA_SEL16；
                                                   111：ATE_MODE0；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_125_UNION;
#endif
#define SOC_IOC_IOMG_125_iomg_125_START  (0)
#define SOC_IOC_IOMG_125_iomg_125_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_126_UNION
 结构说明  : IOMG_126 寄存器结构定义。地址偏移量:0x1F8，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL17管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_126 : 3;  /* bit[0-2] : ANTPA_SEL17管脚的具体复用情况。
                                                   000：GPIO_129；
                                                   001：ANTPA_SEL17；
                                                   111：ATE_MODE1；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_126_UNION;
#endif
#define SOC_IOC_IOMG_126_iomg_126_START  (0)
#define SOC_IOC_IOMG_126_iomg_126_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_127_UNION
 结构说明  : IOMG_127 寄存器结构定义。地址偏移量:0x1FC，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL18管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_127 : 3;  /* bit[0-2] : ANTPA_SEL18管脚的具体复用情况。
                                                   000：GPIO_130；
                                                   001：ANTPA_SEL18；
                                                   111：ATE_MODE2；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_127_UNION;
#endif
#define SOC_IOC_IOMG_127_iomg_127_START  (0)
#define SOC_IOC_IOMG_127_iomg_127_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_128_UNION
 结构说明  : IOMG_128 寄存器结构定义。地址偏移量:0x200，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL19管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_128 : 3;  /* bit[0-2] : ANTPA_SEL19管脚的具体复用情况。
                                                   000：GPIO_131；
                                                   001：ANTPA_SEL19；
                                                   111：FACTEST_MODE0；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_128_UNION;
#endif
#define SOC_IOC_IOMG_128_iomg_128_START  (0)
#define SOC_IOC_IOMG_128_iomg_128_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_129_UNION
 结构说明  : IOMG_129 寄存器结构定义。地址偏移量:0x204，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL20管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_129 : 3;  /* bit[0-2] : ANTPA_SEL20管脚的具体复用情况。
                                                   000：GPIO_132；
                                                   001：ANTPA_SEL20；
                                                   111：FACTEST_MODE1；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_129_UNION;
#endif
#define SOC_IOC_IOMG_129_iomg_129_START  (0)
#define SOC_IOC_IOMG_129_iomg_129_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_130_UNION
 结构说明  : IOMG_130 寄存器结构定义。地址偏移量:0x208，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL21管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_130 : 3;  /* bit[0-2] : ANTPA_SEL21管脚的具体复用情况。
                                                   000：GPIO_133；
                                                   001：ANTPA_SEL21；
                                                   111：NAND_BUSY_N；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_130_UNION;
#endif
#define SOC_IOC_IOMG_130_iomg_130_START  (0)
#define SOC_IOC_IOMG_130_iomg_130_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_131_UNION
 结构说明  : IOMG_131 寄存器结构定义。地址偏移量:0x20C，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL22管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_131 : 3;  /* bit[0-2] : ANTPA_SEL22管脚的具体复用情况。
                                                   000：GPIO_134；
                                                   001：ANTPA_SEL22；
                                                   111：SD_CLK_TOEN；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_131_UNION;
#endif
#define SOC_IOC_IOMG_131_iomg_131_START  (0)
#define SOC_IOC_IOMG_131_iomg_131_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_132_UNION
 结构说明  : IOMG_132 寄存器结构定义。地址偏移量:0x210，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL23管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_132 : 2;  /* bit[0-1] : ANTPA_SEL23管脚的具体复用情况。
                                                   00：GPIO_135；
                                                   01：ANTPA_SEL23；
                                                   10：CH2_APT_PDM；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_132_UNION;
#endif
#define SOC_IOC_IOMG_132_iomg_132_START  (0)
#define SOC_IOC_IOMG_132_iomg_132_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_133_UNION
 结构说明  : IOMG_133 寄存器结构定义。地址偏移量:0x214，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL24管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_133 : 2;  /* bit[0-1] : ANTPA_SEL24管脚的具体复用情况。
                                                   00：GPIO_136；
                                                   01：ANTPA_SEL24；
                                                   10：FE2_MIPI_CLK；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_133_UNION;
#endif
#define SOC_IOC_IOMG_133_iomg_133_START  (0)
#define SOC_IOC_IOMG_133_iomg_133_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_134_UNION
 结构说明  : IOMG_134 寄存器结构定义。地址偏移量:0x218，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL25管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_134 : 2;  /* bit[0-1] : ANTPA_SEL25管脚的具体复用情况。
                                                   00：GPIO_137；
                                                   01：ANTPA_SEL25；
                                                   10：FE2_MIPI_DATA；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_134_UNION;
#endif
#define SOC_IOC_IOMG_134_iomg_134_START  (0)
#define SOC_IOC_IOMG_134_iomg_134_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_135_UNION
 结构说明  : IOMG_135 寄存器结构定义。地址偏移量:0x21C，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL26管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_135 : 2;  /* bit[0-1] : ANTPA_SEL26管脚的具体复用情况。
                                                   00：GPIO_138；
                                                   01：ANTPA_SEL26；
                                                   10：FE3_MIPI_CLK；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_135_UNION;
#endif
#define SOC_IOC_IOMG_135_iomg_135_START  (0)
#define SOC_IOC_IOMG_135_iomg_135_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_136_UNION
 结构说明  : IOMG_136 寄存器结构定义。地址偏移量:0x220，初值:0x00000000，宽度:32
 寄存器说明: ANTPA_SEL27管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_136 : 2;  /* bit[0-1] : ANTPA_SEL27管脚的具体复用情况。
                                                   00：GPIO_139；
                                                   01：ANTPA_SEL27；
                                                   10：FE3_MIPI_DATA；
                                                   11：GPIO_030_SH。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_136_UNION;
#endif
#define SOC_IOC_IOMG_136_iomg_136_START  (0)
#define SOC_IOC_IOMG_136_iomg_136_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOMG_137_UNION
 结构说明  : IOMG_137 寄存器结构定义。地址偏移量:0x224，初值:0x00000000，宽度:32
 寄存器说明: GPIO_140管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_137 : 2;  /* bit[0-1] : GPIO_140管脚的具体复用情况。
                                                   00：GPIO_140；
                                                   01：GPIO_031_SH；
                                                   10：USB_DRV_VBUS；
                                                   11：ONEWIRE。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_IOMG_137_UNION;
#endif
#define SOC_IOC_IOMG_137_iomg_137_START  (0)
#define SOC_IOC_IOMG_137_iomg_137_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_000_UNION
 结构说明  : IOCG_000 寄存器结构定义。地址偏移量:0x800，初值:0x00000001，宽度:32
 寄存器说明: BOOT_MODE功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_000_pu : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_000_UNION;
#endif
#define SOC_IOC_IOCG_000_iocg_000_pu_START  (0)
#define SOC_IOC_IOCG_000_iocg_000_pu_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_001_UNION
 结构说明  : IOCG_001 寄存器结构定义。地址偏移量:0x804，初值:0x00000002，宽度:32
 寄存器说明: TEST_MODE功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_001_pu : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_001_pd : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0  : 5;  /* bit[2-6] : 保留。 */
        unsigned int  iocg_001_sr : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1  : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_001_UNION;
#endif
#define SOC_IOC_IOCG_001_iocg_001_pu_START  (0)
#define SOC_IOC_IOCG_001_iocg_001_pu_END    (0)
#define SOC_IOC_IOCG_001_iocg_001_pd_START  (1)
#define SOC_IOC_IOCG_001_iocg_001_pd_END    (1)
#define SOC_IOC_IOCG_001_iocg_001_sr_START  (7)
#define SOC_IOC_IOCG_001_iocg_001_sr_END    (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_002_UNION
 结构说明  : IOCG_002 寄存器结构定义。地址偏移量:0x808，初值:0x00000012，宽度:32
 寄存器说明: PMU0_SSI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_002_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_002_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_002_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_002_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_002_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_002_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_002_UNION;
#endif
#define SOC_IOC_IOCG_002_iocg_002_pu_START   (0)
#define SOC_IOC_IOCG_002_iocg_002_pu_END     (0)
#define SOC_IOC_IOCG_002_iocg_002_pd_START   (1)
#define SOC_IOC_IOCG_002_iocg_002_pd_END     (1)
#define SOC_IOC_IOCG_002_iocg_002_ds0_START  (4)
#define SOC_IOC_IOCG_002_iocg_002_ds0_END    (4)
#define SOC_IOC_IOCG_002_iocg_002_ds1_START  (5)
#define SOC_IOC_IOCG_002_iocg_002_ds1_END    (5)
#define SOC_IOC_IOCG_002_iocg_002_ds2_START  (6)
#define SOC_IOC_IOCG_002_iocg_002_ds2_END    (6)
#define SOC_IOC_IOCG_002_iocg_002_sr_START   (7)
#define SOC_IOC_IOCG_002_iocg_002_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_003_UNION
 结构说明  : IOCG_003 寄存器结构定义。地址偏移量:0x80C，初值:0x00000012，宽度:32
 寄存器说明: PMU1_SSI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_003_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_003_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_003_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_003_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_003_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_003_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_003_UNION;
#endif
#define SOC_IOC_IOCG_003_iocg_003_pu_START   (0)
#define SOC_IOC_IOCG_003_iocg_003_pu_END     (0)
#define SOC_IOC_IOCG_003_iocg_003_pd_START   (1)
#define SOC_IOC_IOCG_003_iocg_003_pd_END     (1)
#define SOC_IOC_IOCG_003_iocg_003_ds0_START  (4)
#define SOC_IOC_IOCG_003_iocg_003_ds0_END    (4)
#define SOC_IOC_IOCG_003_iocg_003_ds1_START  (5)
#define SOC_IOC_IOCG_003_iocg_003_ds1_END    (5)
#define SOC_IOC_IOCG_003_iocg_003_ds2_START  (6)
#define SOC_IOC_IOCG_003_iocg_003_ds2_END    (6)
#define SOC_IOC_IOCG_003_iocg_003_sr_START   (7)
#define SOC_IOC_IOCG_003_iocg_003_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_004_UNION
 结构说明  : IOCG_004 寄存器结构定义。地址偏移量:0x810，初值:0x00000012，宽度:32
 寄存器说明: JTAG_TCK_SWCLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_004_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_004_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_004_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_004_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_004_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_004_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_004_UNION;
#endif
#define SOC_IOC_IOCG_004_iocg_004_pu_START   (0)
#define SOC_IOC_IOCG_004_iocg_004_pu_END     (0)
#define SOC_IOC_IOCG_004_iocg_004_pd_START   (1)
#define SOC_IOC_IOCG_004_iocg_004_pd_END     (1)
#define SOC_IOC_IOCG_004_iocg_004_ds0_START  (4)
#define SOC_IOC_IOCG_004_iocg_004_ds0_END    (4)
#define SOC_IOC_IOCG_004_iocg_004_ds1_START  (5)
#define SOC_IOC_IOCG_004_iocg_004_ds1_END    (5)
#define SOC_IOC_IOCG_004_iocg_004_ds2_START  (6)
#define SOC_IOC_IOCG_004_iocg_004_ds2_END    (6)
#define SOC_IOC_IOCG_004_iocg_004_sr_START   (7)
#define SOC_IOC_IOCG_004_iocg_004_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_005_UNION
 结构说明  : IOCG_005 寄存器结构定义。地址偏移量:0x814，初值:0x00000012，宽度:32
 寄存器说明: JTAG_TMS_SWDIO功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_005_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_005_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_005_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_005_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_005_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_005_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_005_UNION;
#endif
#define SOC_IOC_IOCG_005_iocg_005_pu_START   (0)
#define SOC_IOC_IOCG_005_iocg_005_pu_END     (0)
#define SOC_IOC_IOCG_005_iocg_005_pd_START   (1)
#define SOC_IOC_IOCG_005_iocg_005_pd_END     (1)
#define SOC_IOC_IOCG_005_iocg_005_ds0_START  (4)
#define SOC_IOC_IOCG_005_iocg_005_ds0_END    (4)
#define SOC_IOC_IOCG_005_iocg_005_ds1_START  (5)
#define SOC_IOC_IOCG_005_iocg_005_ds1_END    (5)
#define SOC_IOC_IOCG_005_iocg_005_ds2_START  (6)
#define SOC_IOC_IOCG_005_iocg_005_ds2_END    (6)
#define SOC_IOC_IOCG_005_iocg_005_sr_START   (7)
#define SOC_IOC_IOCG_005_iocg_005_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_006_UNION
 结构说明  : IOCG_006 寄存器结构定义。地址偏移量:0x818，初值:0x00000012，宽度:32
 寄存器说明: JTAG_TRST_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_006_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_006_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_006_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_006_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_006_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_006_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_006_UNION;
#endif
#define SOC_IOC_IOCG_006_iocg_006_pu_START   (0)
#define SOC_IOC_IOCG_006_iocg_006_pu_END     (0)
#define SOC_IOC_IOCG_006_iocg_006_pd_START   (1)
#define SOC_IOC_IOCG_006_iocg_006_pd_END     (1)
#define SOC_IOC_IOCG_006_iocg_006_ds0_START  (4)
#define SOC_IOC_IOCG_006_iocg_006_ds0_END    (4)
#define SOC_IOC_IOCG_006_iocg_006_ds1_START  (5)
#define SOC_IOC_IOCG_006_iocg_006_ds1_END    (5)
#define SOC_IOC_IOCG_006_iocg_006_ds2_START  (6)
#define SOC_IOC_IOCG_006_iocg_006_ds2_END    (6)
#define SOC_IOC_IOCG_006_iocg_006_sr_START   (7)
#define SOC_IOC_IOCG_006_iocg_006_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_007_UNION
 结构说明  : IOCG_007 寄存器结构定义。地址偏移量:0x81C，初值:0x00000012，宽度:32
 寄存器说明: JTAG_TDI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_007_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_007_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_007_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_007_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_007_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_007_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_007_UNION;
#endif
#define SOC_IOC_IOCG_007_iocg_007_pu_START   (0)
#define SOC_IOC_IOCG_007_iocg_007_pu_END     (0)
#define SOC_IOC_IOCG_007_iocg_007_pd_START   (1)
#define SOC_IOC_IOCG_007_iocg_007_pd_END     (1)
#define SOC_IOC_IOCG_007_iocg_007_ds0_START  (4)
#define SOC_IOC_IOCG_007_iocg_007_ds0_END    (4)
#define SOC_IOC_IOCG_007_iocg_007_ds1_START  (5)
#define SOC_IOC_IOCG_007_iocg_007_ds1_END    (5)
#define SOC_IOC_IOCG_007_iocg_007_ds2_START  (6)
#define SOC_IOC_IOCG_007_iocg_007_ds2_END    (6)
#define SOC_IOC_IOCG_007_iocg_007_sr_START   (7)
#define SOC_IOC_IOCG_007_iocg_007_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_008_UNION
 结构说明  : IOCG_008 寄存器结构定义。地址偏移量:0x820，初值:0x00000012，宽度:32
 寄存器说明: JTAG_TDO功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_008_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_008_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_008_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_008_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_008_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_008_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_008_UNION;
#endif
#define SOC_IOC_IOCG_008_iocg_008_pu_START   (0)
#define SOC_IOC_IOCG_008_iocg_008_pu_END     (0)
#define SOC_IOC_IOCG_008_iocg_008_pd_START   (1)
#define SOC_IOC_IOCG_008_iocg_008_pd_END     (1)
#define SOC_IOC_IOCG_008_iocg_008_ds0_START  (4)
#define SOC_IOC_IOCG_008_iocg_008_ds0_END    (4)
#define SOC_IOC_IOCG_008_iocg_008_ds1_START  (5)
#define SOC_IOC_IOCG_008_iocg_008_ds1_END    (5)
#define SOC_IOC_IOCG_008_iocg_008_ds2_START  (6)
#define SOC_IOC_IOCG_008_iocg_008_ds2_END    (6)
#define SOC_IOC_IOCG_008_iocg_008_sr_START   (7)
#define SOC_IOC_IOCG_008_iocg_008_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_009_UNION
 结构说明  : IOCG_009 寄存器结构定义。地址偏移量:0x824，初值:0x00000012，宽度:32
 寄存器说明: I2C3_SCL功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_009_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_009_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_009_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_009_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_009_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_009_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_009_UNION;
#endif
#define SOC_IOC_IOCG_009_iocg_009_pu_START   (0)
#define SOC_IOC_IOCG_009_iocg_009_pu_END     (0)
#define SOC_IOC_IOCG_009_iocg_009_pd_START   (1)
#define SOC_IOC_IOCG_009_iocg_009_pd_END     (1)
#define SOC_IOC_IOCG_009_iocg_009_ds0_START  (4)
#define SOC_IOC_IOCG_009_iocg_009_ds0_END    (4)
#define SOC_IOC_IOCG_009_iocg_009_ds1_START  (5)
#define SOC_IOC_IOCG_009_iocg_009_ds1_END    (5)
#define SOC_IOC_IOCG_009_iocg_009_ds2_START  (6)
#define SOC_IOC_IOCG_009_iocg_009_ds2_END    (6)
#define SOC_IOC_IOCG_009_iocg_009_sr_START   (7)
#define SOC_IOC_IOCG_009_iocg_009_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_010_UNION
 结构说明  : IOCG_010 寄存器结构定义。地址偏移量:0x828，初值:0x00000012，宽度:32
 寄存器说明: I2C3_SDA功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_010_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_010_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_010_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_010_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_010_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_010_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_010_UNION;
#endif
#define SOC_IOC_IOCG_010_iocg_010_pu_START   (0)
#define SOC_IOC_IOCG_010_iocg_010_pu_END     (0)
#define SOC_IOC_IOCG_010_iocg_010_pd_START   (1)
#define SOC_IOC_IOCG_010_iocg_010_pd_END     (1)
#define SOC_IOC_IOCG_010_iocg_010_ds0_START  (4)
#define SOC_IOC_IOCG_010_iocg_010_ds0_END    (4)
#define SOC_IOC_IOCG_010_iocg_010_ds1_START  (5)
#define SOC_IOC_IOCG_010_iocg_010_ds1_END    (5)
#define SOC_IOC_IOCG_010_iocg_010_ds2_START  (6)
#define SOC_IOC_IOCG_010_iocg_010_ds2_END    (6)
#define SOC_IOC_IOCG_010_iocg_010_sr_START   (7)
#define SOC_IOC_IOCG_010_iocg_010_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_011_UNION
 结构说明  : IOCG_011 寄存器结构定义。地址偏移量:0x82C，初值:0x00000012，宽度:32
 寄存器说明: SPI1_CLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_011_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_011_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_011_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_011_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_011_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_011_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_011_UNION;
#endif
#define SOC_IOC_IOCG_011_iocg_011_pu_START   (0)
#define SOC_IOC_IOCG_011_iocg_011_pu_END     (0)
#define SOC_IOC_IOCG_011_iocg_011_pd_START   (1)
#define SOC_IOC_IOCG_011_iocg_011_pd_END     (1)
#define SOC_IOC_IOCG_011_iocg_011_ds0_START  (4)
#define SOC_IOC_IOCG_011_iocg_011_ds0_END    (4)
#define SOC_IOC_IOCG_011_iocg_011_ds1_START  (5)
#define SOC_IOC_IOCG_011_iocg_011_ds1_END    (5)
#define SOC_IOC_IOCG_011_iocg_011_ds2_START  (6)
#define SOC_IOC_IOCG_011_iocg_011_ds2_END    (6)
#define SOC_IOC_IOCG_011_iocg_011_sr_START   (7)
#define SOC_IOC_IOCG_011_iocg_011_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_012_UNION
 结构说明  : IOCG_012 寄存器结构定义。地址偏移量:0x830，初值:0x00000012，宽度:32
 寄存器说明: SPI1_DI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_012_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_012_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_012_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_012_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_012_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_012_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_012_UNION;
#endif
#define SOC_IOC_IOCG_012_iocg_012_pu_START   (0)
#define SOC_IOC_IOCG_012_iocg_012_pu_END     (0)
#define SOC_IOC_IOCG_012_iocg_012_pd_START   (1)
#define SOC_IOC_IOCG_012_iocg_012_pd_END     (1)
#define SOC_IOC_IOCG_012_iocg_012_ds0_START  (4)
#define SOC_IOC_IOCG_012_iocg_012_ds0_END    (4)
#define SOC_IOC_IOCG_012_iocg_012_ds1_START  (5)
#define SOC_IOC_IOCG_012_iocg_012_ds1_END    (5)
#define SOC_IOC_IOCG_012_iocg_012_ds2_START  (6)
#define SOC_IOC_IOCG_012_iocg_012_ds2_END    (6)
#define SOC_IOC_IOCG_012_iocg_012_sr_START   (7)
#define SOC_IOC_IOCG_012_iocg_012_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_013_UNION
 结构说明  : IOCG_013 寄存器结构定义。地址偏移量:0x834，初值:0x00000012，宽度:32
 寄存器说明: SPI1_DO功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_013_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_013_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_013_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_013_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_013_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_013_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_013_UNION;
#endif
#define SOC_IOC_IOCG_013_iocg_013_pu_START   (0)
#define SOC_IOC_IOCG_013_iocg_013_pu_END     (0)
#define SOC_IOC_IOCG_013_iocg_013_pd_START   (1)
#define SOC_IOC_IOCG_013_iocg_013_pd_END     (1)
#define SOC_IOC_IOCG_013_iocg_013_ds0_START  (4)
#define SOC_IOC_IOCG_013_iocg_013_ds0_END    (4)
#define SOC_IOC_IOCG_013_iocg_013_ds1_START  (5)
#define SOC_IOC_IOCG_013_iocg_013_ds1_END    (5)
#define SOC_IOC_IOCG_013_iocg_013_ds2_START  (6)
#define SOC_IOC_IOCG_013_iocg_013_ds2_END    (6)
#define SOC_IOC_IOCG_013_iocg_013_sr_START   (7)
#define SOC_IOC_IOCG_013_iocg_013_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_014_UNION
 结构说明  : IOCG_014 寄存器结构定义。地址偏移量:0x838，初值:0x00000012，宽度:32
 寄存器说明: SPI1_CS_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_014_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_014_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_014_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_014_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_014_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_014_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_014_UNION;
#endif
#define SOC_IOC_IOCG_014_iocg_014_pu_START   (0)
#define SOC_IOC_IOCG_014_iocg_014_pu_END     (0)
#define SOC_IOC_IOCG_014_iocg_014_pd_START   (1)
#define SOC_IOC_IOCG_014_iocg_014_pd_END     (1)
#define SOC_IOC_IOCG_014_iocg_014_ds0_START  (4)
#define SOC_IOC_IOCG_014_iocg_014_ds0_END    (4)
#define SOC_IOC_IOCG_014_iocg_014_ds1_START  (5)
#define SOC_IOC_IOCG_014_iocg_014_ds1_END    (5)
#define SOC_IOC_IOCG_014_iocg_014_ds2_START  (6)
#define SOC_IOC_IOCG_014_iocg_014_ds2_END    (6)
#define SOC_IOC_IOCG_014_iocg_014_sr_START   (7)
#define SOC_IOC_IOCG_014_iocg_014_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_015_UNION
 结构说明  : IOCG_015 寄存器结构定义。地址偏移量:0x83C，初值:0x00000012，宽度:32
 寄存器说明: SPDIF功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_015_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_015_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_015_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_015_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_015_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_015_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_015_UNION;
#endif
#define SOC_IOC_IOCG_015_iocg_015_pu_START   (0)
#define SOC_IOC_IOCG_015_iocg_015_pu_END     (0)
#define SOC_IOC_IOCG_015_iocg_015_pd_START   (1)
#define SOC_IOC_IOCG_015_iocg_015_pd_END     (1)
#define SOC_IOC_IOCG_015_iocg_015_ds0_START  (4)
#define SOC_IOC_IOCG_015_iocg_015_ds0_END    (4)
#define SOC_IOC_IOCG_015_iocg_015_ds1_START  (5)
#define SOC_IOC_IOCG_015_iocg_015_ds1_END    (5)
#define SOC_IOC_IOCG_015_iocg_015_ds2_START  (6)
#define SOC_IOC_IOCG_015_iocg_015_ds2_END    (6)
#define SOC_IOC_IOCG_015_iocg_015_sr_START   (7)
#define SOC_IOC_IOCG_015_iocg_015_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_016_UNION
 结构说明  : IOCG_016 寄存器结构定义。地址偏移量:0x840，初值:0x00000012，宽度:32
 寄存器说明: GPS_REF功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_016_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_016_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_016_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_016_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_016_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_016_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_016_UNION;
#endif
#define SOC_IOC_IOCG_016_iocg_016_pu_START   (0)
#define SOC_IOC_IOCG_016_iocg_016_pu_END     (0)
#define SOC_IOC_IOCG_016_iocg_016_pd_START   (1)
#define SOC_IOC_IOCG_016_iocg_016_pd_END     (1)
#define SOC_IOC_IOCG_016_iocg_016_ds0_START  (4)
#define SOC_IOC_IOCG_016_iocg_016_ds0_END    (4)
#define SOC_IOC_IOCG_016_iocg_016_ds1_START  (5)
#define SOC_IOC_IOCG_016_iocg_016_ds1_END    (5)
#define SOC_IOC_IOCG_016_iocg_016_ds2_START  (6)
#define SOC_IOC_IOCG_016_iocg_016_ds2_END    (6)
#define SOC_IOC_IOCG_016_iocg_016_sr_START   (7)
#define SOC_IOC_IOCG_016_iocg_016_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_017_UNION
 结构说明  : IOCG_017 寄存器结构定义。地址偏移量:0x844，初值:0x00000012，宽度:32
 寄存器说明: ISP_GPIO00_FTRSTN功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_017_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_017_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_017_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_017_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_017_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_017_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_017_UNION;
#endif
#define SOC_IOC_IOCG_017_iocg_017_pu_START   (0)
#define SOC_IOC_IOCG_017_iocg_017_pu_END     (0)
#define SOC_IOC_IOCG_017_iocg_017_pd_START   (1)
#define SOC_IOC_IOCG_017_iocg_017_pd_END     (1)
#define SOC_IOC_IOCG_017_iocg_017_ds0_START  (4)
#define SOC_IOC_IOCG_017_iocg_017_ds0_END    (4)
#define SOC_IOC_IOCG_017_iocg_017_ds1_START  (5)
#define SOC_IOC_IOCG_017_iocg_017_ds1_END    (5)
#define SOC_IOC_IOCG_017_iocg_017_ds2_START  (6)
#define SOC_IOC_IOCG_017_iocg_017_ds2_END    (6)
#define SOC_IOC_IOCG_017_iocg_017_sr_START   (7)
#define SOC_IOC_IOCG_017_iocg_017_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_018_UNION
 结构说明  : IOCG_018 寄存器结构定义。地址偏移量:0x848，初值:0x00000012，宽度:32
 寄存器说明: ISP_GPIO01_BKRSTN功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_018_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_018_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_018_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_018_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_018_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_018_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_018_UNION;
#endif
#define SOC_IOC_IOCG_018_iocg_018_pu_START   (0)
#define SOC_IOC_IOCG_018_iocg_018_pu_END     (0)
#define SOC_IOC_IOCG_018_iocg_018_pd_START   (1)
#define SOC_IOC_IOCG_018_iocg_018_pd_END     (1)
#define SOC_IOC_IOCG_018_iocg_018_ds0_START  (4)
#define SOC_IOC_IOCG_018_iocg_018_ds0_END    (4)
#define SOC_IOC_IOCG_018_iocg_018_ds1_START  (5)
#define SOC_IOC_IOCG_018_iocg_018_ds1_END    (5)
#define SOC_IOC_IOCG_018_iocg_018_ds2_START  (6)
#define SOC_IOC_IOCG_018_iocg_018_ds2_END    (6)
#define SOC_IOC_IOCG_018_iocg_018_sr_START   (7)
#define SOC_IOC_IOCG_018_iocg_018_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_019_UNION
 结构说明  : IOCG_019 寄存器结构定义。地址偏移量:0x84C，初值:0x00000012，宽度:32
 寄存器说明: ISP_GPIO02_MNTRB功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_019_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_019_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_019_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_019_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_019_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_019_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_019_UNION;
#endif
#define SOC_IOC_IOCG_019_iocg_019_pu_START   (0)
#define SOC_IOC_IOCG_019_iocg_019_pu_END     (0)
#define SOC_IOC_IOCG_019_iocg_019_pd_START   (1)
#define SOC_IOC_IOCG_019_iocg_019_pd_END     (1)
#define SOC_IOC_IOCG_019_iocg_019_ds0_START  (4)
#define SOC_IOC_IOCG_019_iocg_019_ds0_END    (4)
#define SOC_IOC_IOCG_019_iocg_019_ds1_START  (5)
#define SOC_IOC_IOCG_019_iocg_019_ds1_END    (5)
#define SOC_IOC_IOCG_019_iocg_019_ds2_START  (6)
#define SOC_IOC_IOCG_019_iocg_019_ds2_END    (6)
#define SOC_IOC_IOCG_019_iocg_019_sr_START   (7)
#define SOC_IOC_IOCG_019_iocg_019_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_020_UNION
 结构说明  : IOCG_020 寄存器结构定义。地址偏移量:0x850，初值:0x00000012，宽度:32
 寄存器说明: ISP_GPIO06_FSYNC功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_020_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_020_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_020_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_020_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_020_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_020_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_020_UNION;
#endif
#define SOC_IOC_IOCG_020_iocg_020_pu_START   (0)
#define SOC_IOC_IOCG_020_iocg_020_pu_END     (0)
#define SOC_IOC_IOCG_020_iocg_020_pd_START   (1)
#define SOC_IOC_IOCG_020_iocg_020_pd_END     (1)
#define SOC_IOC_IOCG_020_iocg_020_ds0_START  (4)
#define SOC_IOC_IOCG_020_iocg_020_ds0_END    (4)
#define SOC_IOC_IOCG_020_iocg_020_ds1_START  (5)
#define SOC_IOC_IOCG_020_iocg_020_ds1_END    (5)
#define SOC_IOC_IOCG_020_iocg_020_ds2_START  (6)
#define SOC_IOC_IOCG_020_iocg_020_ds2_END    (6)
#define SOC_IOC_IOCG_020_iocg_020_sr_START   (7)
#define SOC_IOC_IOCG_020_iocg_020_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_021_UNION
 结构说明  : IOCG_021 寄存器结构定义。地址偏移量:0x854，初值:0x00000012，宽度:32
 寄存器说明: ISP_GPIO10_SBPWM功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_021_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_021_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_021_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_021_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_021_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_021_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_021_UNION;
#endif
#define SOC_IOC_IOCG_021_iocg_021_pu_START   (0)
#define SOC_IOC_IOCG_021_iocg_021_pu_END     (0)
#define SOC_IOC_IOCG_021_iocg_021_pd_START   (1)
#define SOC_IOC_IOCG_021_iocg_021_pd_END     (1)
#define SOC_IOC_IOCG_021_iocg_021_ds0_START  (4)
#define SOC_IOC_IOCG_021_iocg_021_ds0_END    (4)
#define SOC_IOC_IOCG_021_iocg_021_ds1_START  (5)
#define SOC_IOC_IOCG_021_iocg_021_ds1_END    (5)
#define SOC_IOC_IOCG_021_iocg_021_ds2_START  (6)
#define SOC_IOC_IOCG_021_iocg_021_ds2_END    (6)
#define SOC_IOC_IOCG_021_iocg_021_sr_START   (7)
#define SOC_IOC_IOCG_021_iocg_021_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_022_UNION
 结构说明  : IOCG_022 寄存器结构定义。地址偏移量:0x858，初值:0x00000012，宽度:32
 寄存器说明: ISP_CLK0功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_022_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_022_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_022_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_022_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_022_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_022_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_022_UNION;
#endif
#define SOC_IOC_IOCG_022_iocg_022_pu_START   (0)
#define SOC_IOC_IOCG_022_iocg_022_pu_END     (0)
#define SOC_IOC_IOCG_022_iocg_022_pd_START   (1)
#define SOC_IOC_IOCG_022_iocg_022_pd_END     (1)
#define SOC_IOC_IOCG_022_iocg_022_ds0_START  (4)
#define SOC_IOC_IOCG_022_iocg_022_ds0_END    (4)
#define SOC_IOC_IOCG_022_iocg_022_ds1_START  (5)
#define SOC_IOC_IOCG_022_iocg_022_ds1_END    (5)
#define SOC_IOC_IOCG_022_iocg_022_ds2_START  (6)
#define SOC_IOC_IOCG_022_iocg_022_ds2_END    (6)
#define SOC_IOC_IOCG_022_iocg_022_sr_START   (7)
#define SOC_IOC_IOCG_022_iocg_022_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_023_UNION
 结构说明  : IOCG_023 寄存器结构定义。地址偏移量:0x85C，初值:0x00000012，宽度:32
 寄存器说明: ISP_CLK1功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_023_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_023_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_023_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_023_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_023_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_023_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_023_UNION;
#endif
#define SOC_IOC_IOCG_023_iocg_023_pu_START   (0)
#define SOC_IOC_IOCG_023_iocg_023_pu_END     (0)
#define SOC_IOC_IOCG_023_iocg_023_pd_START   (1)
#define SOC_IOC_IOCG_023_iocg_023_pd_END     (1)
#define SOC_IOC_IOCG_023_iocg_023_ds0_START  (4)
#define SOC_IOC_IOCG_023_iocg_023_ds0_END    (4)
#define SOC_IOC_IOCG_023_iocg_023_ds1_START  (5)
#define SOC_IOC_IOCG_023_iocg_023_ds1_END    (5)
#define SOC_IOC_IOCG_023_iocg_023_ds2_START  (6)
#define SOC_IOC_IOCG_023_iocg_023_ds2_END    (6)
#define SOC_IOC_IOCG_023_iocg_023_sr_START   (7)
#define SOC_IOC_IOCG_023_iocg_023_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_024_UNION
 结构说明  : IOCG_024 寄存器结构定义。地址偏移量:0x860，初值:0x00000012，宽度:32
 寄存器说明: ISP_CLK2功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_024_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_024_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_024_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_024_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_024_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_024_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_024_UNION;
#endif
#define SOC_IOC_IOCG_024_iocg_024_pu_START   (0)
#define SOC_IOC_IOCG_024_iocg_024_pu_END     (0)
#define SOC_IOC_IOCG_024_iocg_024_pd_START   (1)
#define SOC_IOC_IOCG_024_iocg_024_pd_END     (1)
#define SOC_IOC_IOCG_024_iocg_024_ds0_START  (4)
#define SOC_IOC_IOCG_024_iocg_024_ds0_END    (4)
#define SOC_IOC_IOCG_024_iocg_024_ds1_START  (5)
#define SOC_IOC_IOCG_024_iocg_024_ds1_END    (5)
#define SOC_IOC_IOCG_024_iocg_024_ds2_START  (6)
#define SOC_IOC_IOCG_024_iocg_024_ds2_END    (6)
#define SOC_IOC_IOCG_024_iocg_024_sr_START   (7)
#define SOC_IOC_IOCG_024_iocg_024_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_025_UNION
 结构说明  : IOCG_025 寄存器结构定义。地址偏移量:0x864，初值:0x00000012，宽度:32
 寄存器说明: ISP_SCL0功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_025_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_025_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_025_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_025_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_025_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_025_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_025_UNION;
#endif
#define SOC_IOC_IOCG_025_iocg_025_pu_START   (0)
#define SOC_IOC_IOCG_025_iocg_025_pu_END     (0)
#define SOC_IOC_IOCG_025_iocg_025_pd_START   (1)
#define SOC_IOC_IOCG_025_iocg_025_pd_END     (1)
#define SOC_IOC_IOCG_025_iocg_025_ds0_START  (4)
#define SOC_IOC_IOCG_025_iocg_025_ds0_END    (4)
#define SOC_IOC_IOCG_025_iocg_025_ds1_START  (5)
#define SOC_IOC_IOCG_025_iocg_025_ds1_END    (5)
#define SOC_IOC_IOCG_025_iocg_025_ds2_START  (6)
#define SOC_IOC_IOCG_025_iocg_025_ds2_END    (6)
#define SOC_IOC_IOCG_025_iocg_025_sr_START   (7)
#define SOC_IOC_IOCG_025_iocg_025_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_026_UNION
 结构说明  : IOCG_026 寄存器结构定义。地址偏移量:0x868，初值:0x00000012，宽度:32
 寄存器说明: ISP_SDA0功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_026_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_026_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_026_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_026_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_026_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_026_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_026_UNION;
#endif
#define SOC_IOC_IOCG_026_iocg_026_pu_START   (0)
#define SOC_IOC_IOCG_026_iocg_026_pu_END     (0)
#define SOC_IOC_IOCG_026_iocg_026_pd_START   (1)
#define SOC_IOC_IOCG_026_iocg_026_pd_END     (1)
#define SOC_IOC_IOCG_026_iocg_026_ds0_START  (4)
#define SOC_IOC_IOCG_026_iocg_026_ds0_END    (4)
#define SOC_IOC_IOCG_026_iocg_026_ds1_START  (5)
#define SOC_IOC_IOCG_026_iocg_026_ds1_END    (5)
#define SOC_IOC_IOCG_026_iocg_026_ds2_START  (6)
#define SOC_IOC_IOCG_026_iocg_026_ds2_END    (6)
#define SOC_IOC_IOCG_026_iocg_026_sr_START   (7)
#define SOC_IOC_IOCG_026_iocg_026_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_027_UNION
 结构说明  : IOCG_027 寄存器结构定义。地址偏移量:0x86C，初值:0x00000012，宽度:32
 寄存器说明: ISP_SCL1功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_027_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_027_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_027_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_027_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_027_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_027_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_027_UNION;
#endif
#define SOC_IOC_IOCG_027_iocg_027_pu_START   (0)
#define SOC_IOC_IOCG_027_iocg_027_pu_END     (0)
#define SOC_IOC_IOCG_027_iocg_027_pd_START   (1)
#define SOC_IOC_IOCG_027_iocg_027_pd_END     (1)
#define SOC_IOC_IOCG_027_iocg_027_ds0_START  (4)
#define SOC_IOC_IOCG_027_iocg_027_ds0_END    (4)
#define SOC_IOC_IOCG_027_iocg_027_ds1_START  (5)
#define SOC_IOC_IOCG_027_iocg_027_ds1_END    (5)
#define SOC_IOC_IOCG_027_iocg_027_ds2_START  (6)
#define SOC_IOC_IOCG_027_iocg_027_ds2_END    (6)
#define SOC_IOC_IOCG_027_iocg_027_sr_START   (7)
#define SOC_IOC_IOCG_027_iocg_027_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_028_UNION
 结构说明  : IOCG_028 寄存器结构定义。地址偏移量:0x870，初值:0x00000012，宽度:32
 寄存器说明: ISP_SDA1功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_028_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_028_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_028_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_028_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_028_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_028_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_028_UNION;
#endif
#define SOC_IOC_IOCG_028_iocg_028_pu_START   (0)
#define SOC_IOC_IOCG_028_iocg_028_pu_END     (0)
#define SOC_IOC_IOCG_028_iocg_028_pd_START   (1)
#define SOC_IOC_IOCG_028_iocg_028_pd_END     (1)
#define SOC_IOC_IOCG_028_iocg_028_ds0_START  (4)
#define SOC_IOC_IOCG_028_iocg_028_ds0_END    (4)
#define SOC_IOC_IOCG_028_iocg_028_ds1_START  (5)
#define SOC_IOC_IOCG_028_iocg_028_ds1_END    (5)
#define SOC_IOC_IOCG_028_iocg_028_ds2_START  (6)
#define SOC_IOC_IOCG_028_iocg_028_ds2_END    (6)
#define SOC_IOC_IOCG_028_iocg_028_sr_START   (7)
#define SOC_IOC_IOCG_028_iocg_028_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_029_UNION
 结构说明  : IOCG_029 寄存器结构定义。地址偏移量:0x874，初值:0x00000012，宽度:32
 寄存器说明: ISP_SCL2功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_029_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_029_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_029_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_029_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_029_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_029_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_029_UNION;
#endif
#define SOC_IOC_IOCG_029_iocg_029_pu_START   (0)
#define SOC_IOC_IOCG_029_iocg_029_pu_END     (0)
#define SOC_IOC_IOCG_029_iocg_029_pd_START   (1)
#define SOC_IOC_IOCG_029_iocg_029_pd_END     (1)
#define SOC_IOC_IOCG_029_iocg_029_ds0_START  (4)
#define SOC_IOC_IOCG_029_iocg_029_ds0_END    (4)
#define SOC_IOC_IOCG_029_iocg_029_ds1_START  (5)
#define SOC_IOC_IOCG_029_iocg_029_ds1_END    (5)
#define SOC_IOC_IOCG_029_iocg_029_ds2_START  (6)
#define SOC_IOC_IOCG_029_iocg_029_ds2_END    (6)
#define SOC_IOC_IOCG_029_iocg_029_sr_START   (7)
#define SOC_IOC_IOCG_029_iocg_029_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_030_UNION
 结构说明  : IOCG_030 寄存器结构定义。地址偏移量:0x878，初值:0x00000012，宽度:32
 寄存器说明: ISP_SDA2功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_030_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_030_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_030_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_030_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_030_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_030_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_030_UNION;
#endif
#define SOC_IOC_IOCG_030_iocg_030_pu_START   (0)
#define SOC_IOC_IOCG_030_iocg_030_pu_END     (0)
#define SOC_IOC_IOCG_030_iocg_030_pd_START   (1)
#define SOC_IOC_IOCG_030_iocg_030_pd_END     (1)
#define SOC_IOC_IOCG_030_iocg_030_ds0_START  (4)
#define SOC_IOC_IOCG_030_iocg_030_ds0_END    (4)
#define SOC_IOC_IOCG_030_iocg_030_ds1_START  (5)
#define SOC_IOC_IOCG_030_iocg_030_ds1_END    (5)
#define SOC_IOC_IOCG_030_iocg_030_ds2_START  (6)
#define SOC_IOC_IOCG_030_iocg_030_ds2_END    (6)
#define SOC_IOC_IOCG_030_iocg_030_sr_START   (7)
#define SOC_IOC_IOCG_030_iocg_030_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_031_UNION
 结构说明  : IOCG_031 寄存器结构定义。地址偏移量:0x87C，初值:0x00000012，宽度:32
 寄存器说明: SDIO1_CLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_031_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_031_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_031_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_031_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_031_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_031_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_031_UNION;
#endif
#define SOC_IOC_IOCG_031_iocg_031_pu_START   (0)
#define SOC_IOC_IOCG_031_iocg_031_pu_END     (0)
#define SOC_IOC_IOCG_031_iocg_031_pd_START   (1)
#define SOC_IOC_IOCG_031_iocg_031_pd_END     (1)
#define SOC_IOC_IOCG_031_iocg_031_ds0_START  (4)
#define SOC_IOC_IOCG_031_iocg_031_ds0_END    (4)
#define SOC_IOC_IOCG_031_iocg_031_ds1_START  (5)
#define SOC_IOC_IOCG_031_iocg_031_ds1_END    (5)
#define SOC_IOC_IOCG_031_iocg_031_ds2_START  (6)
#define SOC_IOC_IOCG_031_iocg_031_ds2_END    (6)
#define SOC_IOC_IOCG_031_iocg_031_sr_START   (7)
#define SOC_IOC_IOCG_031_iocg_031_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_032_UNION
 结构说明  : IOCG_032 寄存器结构定义。地址偏移量:0x880，初值:0x00000012，宽度:32
 寄存器说明: SDIO1_CMD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_032_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_032_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_032_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_032_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_032_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_032_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_032_UNION;
#endif
#define SOC_IOC_IOCG_032_iocg_032_pu_START   (0)
#define SOC_IOC_IOCG_032_iocg_032_pu_END     (0)
#define SOC_IOC_IOCG_032_iocg_032_pd_START   (1)
#define SOC_IOC_IOCG_032_iocg_032_pd_END     (1)
#define SOC_IOC_IOCG_032_iocg_032_ds0_START  (4)
#define SOC_IOC_IOCG_032_iocg_032_ds0_END    (4)
#define SOC_IOC_IOCG_032_iocg_032_ds1_START  (5)
#define SOC_IOC_IOCG_032_iocg_032_ds1_END    (5)
#define SOC_IOC_IOCG_032_iocg_032_ds2_START  (6)
#define SOC_IOC_IOCG_032_iocg_032_ds2_END    (6)
#define SOC_IOC_IOCG_032_iocg_032_sr_START   (7)
#define SOC_IOC_IOCG_032_iocg_032_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_033_UNION
 结构说明  : IOCG_033 寄存器结构定义。地址偏移量:0x884，初值:0x00000012，宽度:32
 寄存器说明: SDIO1_DATA0功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_033_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_033_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_033_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_033_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_033_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_033_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_033_UNION;
#endif
#define SOC_IOC_IOCG_033_iocg_033_pu_START   (0)
#define SOC_IOC_IOCG_033_iocg_033_pu_END     (0)
#define SOC_IOC_IOCG_033_iocg_033_pd_START   (1)
#define SOC_IOC_IOCG_033_iocg_033_pd_END     (1)
#define SOC_IOC_IOCG_033_iocg_033_ds0_START  (4)
#define SOC_IOC_IOCG_033_iocg_033_ds0_END    (4)
#define SOC_IOC_IOCG_033_iocg_033_ds1_START  (5)
#define SOC_IOC_IOCG_033_iocg_033_ds1_END    (5)
#define SOC_IOC_IOCG_033_iocg_033_ds2_START  (6)
#define SOC_IOC_IOCG_033_iocg_033_ds2_END    (6)
#define SOC_IOC_IOCG_033_iocg_033_sr_START   (7)
#define SOC_IOC_IOCG_033_iocg_033_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_034_UNION
 结构说明  : IOCG_034 寄存器结构定义。地址偏移量:0x888，初值:0x00000012，宽度:32
 寄存器说明: SDIO1_DATA1功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_034_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_034_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_034_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_034_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_034_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_034_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_034_UNION;
#endif
#define SOC_IOC_IOCG_034_iocg_034_pu_START   (0)
#define SOC_IOC_IOCG_034_iocg_034_pu_END     (0)
#define SOC_IOC_IOCG_034_iocg_034_pd_START   (1)
#define SOC_IOC_IOCG_034_iocg_034_pd_END     (1)
#define SOC_IOC_IOCG_034_iocg_034_ds0_START  (4)
#define SOC_IOC_IOCG_034_iocg_034_ds0_END    (4)
#define SOC_IOC_IOCG_034_iocg_034_ds1_START  (5)
#define SOC_IOC_IOCG_034_iocg_034_ds1_END    (5)
#define SOC_IOC_IOCG_034_iocg_034_ds2_START  (6)
#define SOC_IOC_IOCG_034_iocg_034_ds2_END    (6)
#define SOC_IOC_IOCG_034_iocg_034_sr_START   (7)
#define SOC_IOC_IOCG_034_iocg_034_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_035_UNION
 结构说明  : IOCG_035 寄存器结构定义。地址偏移量:0x88C，初值:0x00000012，宽度:32
 寄存器说明: SDIO1_DATA2功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_035_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_035_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_035_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_035_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_035_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_035_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_035_UNION;
#endif
#define SOC_IOC_IOCG_035_iocg_035_pu_START   (0)
#define SOC_IOC_IOCG_035_iocg_035_pu_END     (0)
#define SOC_IOC_IOCG_035_iocg_035_pd_START   (1)
#define SOC_IOC_IOCG_035_iocg_035_pd_END     (1)
#define SOC_IOC_IOCG_035_iocg_035_ds0_START  (4)
#define SOC_IOC_IOCG_035_iocg_035_ds0_END    (4)
#define SOC_IOC_IOCG_035_iocg_035_ds1_START  (5)
#define SOC_IOC_IOCG_035_iocg_035_ds1_END    (5)
#define SOC_IOC_IOCG_035_iocg_035_ds2_START  (6)
#define SOC_IOC_IOCG_035_iocg_035_ds2_END    (6)
#define SOC_IOC_IOCG_035_iocg_035_sr_START   (7)
#define SOC_IOC_IOCG_035_iocg_035_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_036_UNION
 结构说明  : IOCG_036 寄存器结构定义。地址偏移量:0x890，初值:0x00000012，宽度:32
 寄存器说明: SDIO1_DATA3功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_036_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_036_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_036_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_036_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_036_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_036_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_036_UNION;
#endif
#define SOC_IOC_IOCG_036_iocg_036_pu_START   (0)
#define SOC_IOC_IOCG_036_iocg_036_pu_END     (0)
#define SOC_IOC_IOCG_036_iocg_036_pd_START   (1)
#define SOC_IOC_IOCG_036_iocg_036_pd_END     (1)
#define SOC_IOC_IOCG_036_iocg_036_ds0_START  (4)
#define SOC_IOC_IOCG_036_iocg_036_ds0_END    (4)
#define SOC_IOC_IOCG_036_iocg_036_ds1_START  (5)
#define SOC_IOC_IOCG_036_iocg_036_ds1_END    (5)
#define SOC_IOC_IOCG_036_iocg_036_ds2_START  (6)
#define SOC_IOC_IOCG_036_iocg_036_ds2_END    (6)
#define SOC_IOC_IOCG_036_iocg_036_sr_START   (7)
#define SOC_IOC_IOCG_036_iocg_036_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_037_UNION
 结构说明  : IOCG_037 寄存器结构定义。地址偏移量:0x894，初值:0x00000012，宽度:32
 寄存器说明: I2C4_SCL功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_037_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_037_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_037_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_037_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_037_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_037_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_037_UNION;
#endif
#define SOC_IOC_IOCG_037_iocg_037_pu_START   (0)
#define SOC_IOC_IOCG_037_iocg_037_pu_END     (0)
#define SOC_IOC_IOCG_037_iocg_037_pd_START   (1)
#define SOC_IOC_IOCG_037_iocg_037_pd_END     (1)
#define SOC_IOC_IOCG_037_iocg_037_ds0_START  (4)
#define SOC_IOC_IOCG_037_iocg_037_ds0_END    (4)
#define SOC_IOC_IOCG_037_iocg_037_ds1_START  (5)
#define SOC_IOC_IOCG_037_iocg_037_ds1_END    (5)
#define SOC_IOC_IOCG_037_iocg_037_ds2_START  (6)
#define SOC_IOC_IOCG_037_iocg_037_ds2_END    (6)
#define SOC_IOC_IOCG_037_iocg_037_sr_START   (7)
#define SOC_IOC_IOCG_037_iocg_037_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_038_UNION
 结构说明  : IOCG_038 寄存器结构定义。地址偏移量:0x898，初值:0x00000012，宽度:32
 寄存器说明: I2C4_SDA功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_038_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_038_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_038_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_038_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_038_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_038_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_038_UNION;
#endif
#define SOC_IOC_IOCG_038_iocg_038_pu_START   (0)
#define SOC_IOC_IOCG_038_iocg_038_pu_END     (0)
#define SOC_IOC_IOCG_038_iocg_038_pd_START   (1)
#define SOC_IOC_IOCG_038_iocg_038_pd_END     (1)
#define SOC_IOC_IOCG_038_iocg_038_ds0_START  (4)
#define SOC_IOC_IOCG_038_iocg_038_ds0_END    (4)
#define SOC_IOC_IOCG_038_iocg_038_ds1_START  (5)
#define SOC_IOC_IOCG_038_iocg_038_ds1_END    (5)
#define SOC_IOC_IOCG_038_iocg_038_ds2_START  (6)
#define SOC_IOC_IOCG_038_iocg_038_ds2_END    (6)
#define SOC_IOC_IOCG_038_iocg_038_sr_START   (7)
#define SOC_IOC_IOCG_038_iocg_038_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_039_UNION
 结构说明  : IOCG_039 寄存器结构定义。地址偏移量:0x89C，初值:0x00000012，宽度:32
 寄存器说明: I2C5_SCL功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_039_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_039_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_039_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_039_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_039_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_039_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_039_UNION;
#endif
#define SOC_IOC_IOCG_039_iocg_039_pu_START   (0)
#define SOC_IOC_IOCG_039_iocg_039_pu_END     (0)
#define SOC_IOC_IOCG_039_iocg_039_pd_START   (1)
#define SOC_IOC_IOCG_039_iocg_039_pd_END     (1)
#define SOC_IOC_IOCG_039_iocg_039_ds0_START  (4)
#define SOC_IOC_IOCG_039_iocg_039_ds0_END    (4)
#define SOC_IOC_IOCG_039_iocg_039_ds1_START  (5)
#define SOC_IOC_IOCG_039_iocg_039_ds1_END    (5)
#define SOC_IOC_IOCG_039_iocg_039_ds2_START  (6)
#define SOC_IOC_IOCG_039_iocg_039_ds2_END    (6)
#define SOC_IOC_IOCG_039_iocg_039_sr_START   (7)
#define SOC_IOC_IOCG_039_iocg_039_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_040_UNION
 结构说明  : IOCG_040 寄存器结构定义。地址偏移量:0x8A0，初值:0x00000012，宽度:32
 寄存器说明: I2C5_SDA功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_040_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_040_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_040_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_040_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_040_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_040_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_040_UNION;
#endif
#define SOC_IOC_IOCG_040_iocg_040_pu_START   (0)
#define SOC_IOC_IOCG_040_iocg_040_pu_END     (0)
#define SOC_IOC_IOCG_040_iocg_040_pd_START   (1)
#define SOC_IOC_IOCG_040_iocg_040_pd_END     (1)
#define SOC_IOC_IOCG_040_iocg_040_ds0_START  (4)
#define SOC_IOC_IOCG_040_iocg_040_ds0_END    (4)
#define SOC_IOC_IOCG_040_iocg_040_ds1_START  (5)
#define SOC_IOC_IOCG_040_iocg_040_ds1_END    (5)
#define SOC_IOC_IOCG_040_iocg_040_ds2_START  (6)
#define SOC_IOC_IOCG_040_iocg_040_ds2_END    (6)
#define SOC_IOC_IOCG_040_iocg_040_sr_START   (7)
#define SOC_IOC_IOCG_040_iocg_040_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_041_UNION
 结构说明  : IOCG_041 寄存器结构定义。地址偏移量:0x8A4，初值:0x00000012，宽度:32
 寄存器说明: SD_CLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_041_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_041_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 1;  /* bit[2]   : 保留。 */
        unsigned int  iocg_041_st  : 1;  /* bit[3]   : 施密特触发使能 */
        unsigned int  iocg_041_ds0 : 1;  /* bit[4]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_041_ds1 : 1;  /* bit[5]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_041_ds2 : 1;  /* bit[6]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_041_ds3 : 1;  /* bit[7]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_041_UNION;
#endif
#define SOC_IOC_IOCG_041_iocg_041_pu_START   (0)
#define SOC_IOC_IOCG_041_iocg_041_pu_END     (0)
#define SOC_IOC_IOCG_041_iocg_041_pd_START   (1)
#define SOC_IOC_IOCG_041_iocg_041_pd_END     (1)
#define SOC_IOC_IOCG_041_iocg_041_st_START   (3)
#define SOC_IOC_IOCG_041_iocg_041_st_END     (3)
#define SOC_IOC_IOCG_041_iocg_041_ds0_START  (4)
#define SOC_IOC_IOCG_041_iocg_041_ds0_END    (4)
#define SOC_IOC_IOCG_041_iocg_041_ds1_START  (5)
#define SOC_IOC_IOCG_041_iocg_041_ds1_END    (5)
#define SOC_IOC_IOCG_041_iocg_041_ds2_START  (6)
#define SOC_IOC_IOCG_041_iocg_041_ds2_END    (6)
#define SOC_IOC_IOCG_041_iocg_041_ds3_START  (7)
#define SOC_IOC_IOCG_041_iocg_041_ds3_END    (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_042_UNION
 结构说明  : IOCG_042 寄存器结构定义。地址偏移量:0x8A8，初值:0x00000012，宽度:32
 寄存器说明: SD_CMD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_042_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_042_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 1;  /* bit[2]   : 保留。 */
        unsigned int  iocg_042_st  : 1;  /* bit[3]   : 施密特触发使能 */
        unsigned int  iocg_042_ds0 : 1;  /* bit[4]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_042_ds1 : 1;  /* bit[5]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_042_ds2 : 1;  /* bit[6]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_042_ds3 : 1;  /* bit[7]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_042_UNION;
#endif
#define SOC_IOC_IOCG_042_iocg_042_pu_START   (0)
#define SOC_IOC_IOCG_042_iocg_042_pu_END     (0)
#define SOC_IOC_IOCG_042_iocg_042_pd_START   (1)
#define SOC_IOC_IOCG_042_iocg_042_pd_END     (1)
#define SOC_IOC_IOCG_042_iocg_042_st_START   (3)
#define SOC_IOC_IOCG_042_iocg_042_st_END     (3)
#define SOC_IOC_IOCG_042_iocg_042_ds0_START  (4)
#define SOC_IOC_IOCG_042_iocg_042_ds0_END    (4)
#define SOC_IOC_IOCG_042_iocg_042_ds1_START  (5)
#define SOC_IOC_IOCG_042_iocg_042_ds1_END    (5)
#define SOC_IOC_IOCG_042_iocg_042_ds2_START  (6)
#define SOC_IOC_IOCG_042_iocg_042_ds2_END    (6)
#define SOC_IOC_IOCG_042_iocg_042_ds3_START  (7)
#define SOC_IOC_IOCG_042_iocg_042_ds3_END    (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_043_UNION
 结构说明  : IOCG_043 寄存器结构定义。地址偏移量:0x8AC，初值:0x00000012，宽度:32
 寄存器说明: SD_DATA0功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_043_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_043_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 1;  /* bit[2]   : 保留。 */
        unsigned int  iocg_043_st  : 1;  /* bit[3]   : 施密特触发使能 */
        unsigned int  iocg_043_ds0 : 1;  /* bit[4]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_043_ds1 : 1;  /* bit[5]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_043_ds2 : 1;  /* bit[6]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_043_ds3 : 1;  /* bit[7]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_043_UNION;
#endif
#define SOC_IOC_IOCG_043_iocg_043_pu_START   (0)
#define SOC_IOC_IOCG_043_iocg_043_pu_END     (0)
#define SOC_IOC_IOCG_043_iocg_043_pd_START   (1)
#define SOC_IOC_IOCG_043_iocg_043_pd_END     (1)
#define SOC_IOC_IOCG_043_iocg_043_st_START   (3)
#define SOC_IOC_IOCG_043_iocg_043_st_END     (3)
#define SOC_IOC_IOCG_043_iocg_043_ds0_START  (4)
#define SOC_IOC_IOCG_043_iocg_043_ds0_END    (4)
#define SOC_IOC_IOCG_043_iocg_043_ds1_START  (5)
#define SOC_IOC_IOCG_043_iocg_043_ds1_END    (5)
#define SOC_IOC_IOCG_043_iocg_043_ds2_START  (6)
#define SOC_IOC_IOCG_043_iocg_043_ds2_END    (6)
#define SOC_IOC_IOCG_043_iocg_043_ds3_START  (7)
#define SOC_IOC_IOCG_043_iocg_043_ds3_END    (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_044_UNION
 结构说明  : IOCG_044 寄存器结构定义。地址偏移量:0x8B0，初值:0x00000012，宽度:32
 寄存器说明: SD_DATA1功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_044_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_044_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 1;  /* bit[2]   : 保留。 */
        unsigned int  iocg_044_st  : 1;  /* bit[3]   : 施密特触发使能 */
        unsigned int  iocg_044_ds0 : 1;  /* bit[4]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_044_ds1 : 1;  /* bit[5]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_044_ds2 : 1;  /* bit[6]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_044_ds3 : 1;  /* bit[7]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_044_UNION;
#endif
#define SOC_IOC_IOCG_044_iocg_044_pu_START   (0)
#define SOC_IOC_IOCG_044_iocg_044_pu_END     (0)
#define SOC_IOC_IOCG_044_iocg_044_pd_START   (1)
#define SOC_IOC_IOCG_044_iocg_044_pd_END     (1)
#define SOC_IOC_IOCG_044_iocg_044_st_START   (3)
#define SOC_IOC_IOCG_044_iocg_044_st_END     (3)
#define SOC_IOC_IOCG_044_iocg_044_ds0_START  (4)
#define SOC_IOC_IOCG_044_iocg_044_ds0_END    (4)
#define SOC_IOC_IOCG_044_iocg_044_ds1_START  (5)
#define SOC_IOC_IOCG_044_iocg_044_ds1_END    (5)
#define SOC_IOC_IOCG_044_iocg_044_ds2_START  (6)
#define SOC_IOC_IOCG_044_iocg_044_ds2_END    (6)
#define SOC_IOC_IOCG_044_iocg_044_ds3_START  (7)
#define SOC_IOC_IOCG_044_iocg_044_ds3_END    (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_045_UNION
 结构说明  : IOCG_045 寄存器结构定义。地址偏移量:0x8B4，初值:0x00000012，宽度:32
 寄存器说明: SD_DATA2功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_045_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_045_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 1;  /* bit[2]   : 保留。 */
        unsigned int  iocg_045_st  : 1;  /* bit[3]   : 施密特触发使能 */
        unsigned int  iocg_045_ds0 : 1;  /* bit[4]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_045_ds1 : 1;  /* bit[5]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_045_ds2 : 1;  /* bit[6]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_045_ds3 : 1;  /* bit[7]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_045_UNION;
#endif
#define SOC_IOC_IOCG_045_iocg_045_pu_START   (0)
#define SOC_IOC_IOCG_045_iocg_045_pu_END     (0)
#define SOC_IOC_IOCG_045_iocg_045_pd_START   (1)
#define SOC_IOC_IOCG_045_iocg_045_pd_END     (1)
#define SOC_IOC_IOCG_045_iocg_045_st_START   (3)
#define SOC_IOC_IOCG_045_iocg_045_st_END     (3)
#define SOC_IOC_IOCG_045_iocg_045_ds0_START  (4)
#define SOC_IOC_IOCG_045_iocg_045_ds0_END    (4)
#define SOC_IOC_IOCG_045_iocg_045_ds1_START  (5)
#define SOC_IOC_IOCG_045_iocg_045_ds1_END    (5)
#define SOC_IOC_IOCG_045_iocg_045_ds2_START  (6)
#define SOC_IOC_IOCG_045_iocg_045_ds2_END    (6)
#define SOC_IOC_IOCG_045_iocg_045_ds3_START  (7)
#define SOC_IOC_IOCG_045_iocg_045_ds3_END    (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_046_UNION
 结构说明  : IOCG_046 寄存器结构定义。地址偏移量:0x8B8，初值:0x00000012，宽度:32
 寄存器说明: SD_DATA3功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_046_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_046_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 1;  /* bit[2]   : 保留。 */
        unsigned int  iocg_046_st  : 1;  /* bit[3]   : 施密特触发使能 */
        unsigned int  iocg_046_ds0 : 1;  /* bit[4]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_046_ds1 : 1;  /* bit[5]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_046_ds2 : 1;  /* bit[6]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_046_ds3 : 1;  /* bit[7]   : DS3,DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_046_UNION;
#endif
#define SOC_IOC_IOCG_046_iocg_046_pu_START   (0)
#define SOC_IOC_IOCG_046_iocg_046_pu_END     (0)
#define SOC_IOC_IOCG_046_iocg_046_pd_START   (1)
#define SOC_IOC_IOCG_046_iocg_046_pd_END     (1)
#define SOC_IOC_IOCG_046_iocg_046_st_START   (3)
#define SOC_IOC_IOCG_046_iocg_046_st_END     (3)
#define SOC_IOC_IOCG_046_iocg_046_ds0_START  (4)
#define SOC_IOC_IOCG_046_iocg_046_ds0_END    (4)
#define SOC_IOC_IOCG_046_iocg_046_ds1_START  (5)
#define SOC_IOC_IOCG_046_iocg_046_ds1_END    (5)
#define SOC_IOC_IOCG_046_iocg_046_ds2_START  (6)
#define SOC_IOC_IOCG_046_iocg_046_ds2_END    (6)
#define SOC_IOC_IOCG_046_iocg_046_ds3_START  (7)
#define SOC_IOC_IOCG_046_iocg_046_ds3_END    (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_047_UNION
 结构说明  : IOCG_047 寄存器结构定义。地址偏移量:0x8BC，初值:0x00000012，宽度:32
 寄存器说明: SPI0_CLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_047_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_047_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_047_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_047_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_047_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_047_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_047_UNION;
#endif
#define SOC_IOC_IOCG_047_iocg_047_pu_START   (0)
#define SOC_IOC_IOCG_047_iocg_047_pu_END     (0)
#define SOC_IOC_IOCG_047_iocg_047_pd_START   (1)
#define SOC_IOC_IOCG_047_iocg_047_pd_END     (1)
#define SOC_IOC_IOCG_047_iocg_047_ds0_START  (4)
#define SOC_IOC_IOCG_047_iocg_047_ds0_END    (4)
#define SOC_IOC_IOCG_047_iocg_047_ds1_START  (5)
#define SOC_IOC_IOCG_047_iocg_047_ds1_END    (5)
#define SOC_IOC_IOCG_047_iocg_047_ds2_START  (6)
#define SOC_IOC_IOCG_047_iocg_047_ds2_END    (6)
#define SOC_IOC_IOCG_047_iocg_047_sr_START   (7)
#define SOC_IOC_IOCG_047_iocg_047_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_048_UNION
 结构说明  : IOCG_048 寄存器结构定义。地址偏移量:0x8C0，初值:0x00000012，宽度:32
 寄存器说明: SPI0_DI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_048_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_048_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_048_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_048_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_048_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_048_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_048_UNION;
#endif
#define SOC_IOC_IOCG_048_iocg_048_pu_START   (0)
#define SOC_IOC_IOCG_048_iocg_048_pu_END     (0)
#define SOC_IOC_IOCG_048_iocg_048_pd_START   (1)
#define SOC_IOC_IOCG_048_iocg_048_pd_END     (1)
#define SOC_IOC_IOCG_048_iocg_048_ds0_START  (4)
#define SOC_IOC_IOCG_048_iocg_048_ds0_END    (4)
#define SOC_IOC_IOCG_048_iocg_048_ds1_START  (5)
#define SOC_IOC_IOCG_048_iocg_048_ds1_END    (5)
#define SOC_IOC_IOCG_048_iocg_048_ds2_START  (6)
#define SOC_IOC_IOCG_048_iocg_048_ds2_END    (6)
#define SOC_IOC_IOCG_048_iocg_048_sr_START   (7)
#define SOC_IOC_IOCG_048_iocg_048_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_049_UNION
 结构说明  : IOCG_049 寄存器结构定义。地址偏移量:0x8C4，初值:0x00000012，宽度:32
 寄存器说明: SPI0_DO功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_049_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_049_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_049_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_049_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_049_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_049_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_049_UNION;
#endif
#define SOC_IOC_IOCG_049_iocg_049_pu_START   (0)
#define SOC_IOC_IOCG_049_iocg_049_pu_END     (0)
#define SOC_IOC_IOCG_049_iocg_049_pd_START   (1)
#define SOC_IOC_IOCG_049_iocg_049_pd_END     (1)
#define SOC_IOC_IOCG_049_iocg_049_ds0_START  (4)
#define SOC_IOC_IOCG_049_iocg_049_ds0_END    (4)
#define SOC_IOC_IOCG_049_iocg_049_ds1_START  (5)
#define SOC_IOC_IOCG_049_iocg_049_ds1_END    (5)
#define SOC_IOC_IOCG_049_iocg_049_ds2_START  (6)
#define SOC_IOC_IOCG_049_iocg_049_ds2_END    (6)
#define SOC_IOC_IOCG_049_iocg_049_sr_START   (7)
#define SOC_IOC_IOCG_049_iocg_049_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_050_UNION
 结构说明  : IOCG_050 寄存器结构定义。地址偏移量:0x8C8，初值:0x00000012，宽度:32
 寄存器说明: SPI0_CS0_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_050_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_050_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_050_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_050_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_050_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_050_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_050_UNION;
#endif
#define SOC_IOC_IOCG_050_iocg_050_pu_START   (0)
#define SOC_IOC_IOCG_050_iocg_050_pu_END     (0)
#define SOC_IOC_IOCG_050_iocg_050_pd_START   (1)
#define SOC_IOC_IOCG_050_iocg_050_pd_END     (1)
#define SOC_IOC_IOCG_050_iocg_050_ds0_START  (4)
#define SOC_IOC_IOCG_050_iocg_050_ds0_END    (4)
#define SOC_IOC_IOCG_050_iocg_050_ds1_START  (5)
#define SOC_IOC_IOCG_050_iocg_050_ds1_END    (5)
#define SOC_IOC_IOCG_050_iocg_050_ds2_START  (6)
#define SOC_IOC_IOCG_050_iocg_050_ds2_END    (6)
#define SOC_IOC_IOCG_050_iocg_050_sr_START   (7)
#define SOC_IOC_IOCG_050_iocg_050_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_051_UNION
 结构说明  : IOCG_051 寄存器结构定义。地址偏移量:0x8CC，初值:0x00000012，宽度:32
 寄存器说明: SPI0_CS1_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_051_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_051_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_051_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_051_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_051_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_051_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_051_UNION;
#endif
#define SOC_IOC_IOCG_051_iocg_051_pu_START   (0)
#define SOC_IOC_IOCG_051_iocg_051_pu_END     (0)
#define SOC_IOC_IOCG_051_iocg_051_pd_START   (1)
#define SOC_IOC_IOCG_051_iocg_051_pd_END     (1)
#define SOC_IOC_IOCG_051_iocg_051_ds0_START  (4)
#define SOC_IOC_IOCG_051_iocg_051_ds0_END    (4)
#define SOC_IOC_IOCG_051_iocg_051_ds1_START  (5)
#define SOC_IOC_IOCG_051_iocg_051_ds1_END    (5)
#define SOC_IOC_IOCG_051_iocg_051_ds2_START  (6)
#define SOC_IOC_IOCG_051_iocg_051_ds2_END    (6)
#define SOC_IOC_IOCG_051_iocg_051_sr_START   (7)
#define SOC_IOC_IOCG_051_iocg_051_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_052_UNION
 结构说明  : IOCG_052 寄存器结构定义。地址偏移量:0x8D0，初值:0x00000012，宽度:32
 寄存器说明: SPI0_CS2_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_052_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_052_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_052_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_052_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_052_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_052_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_052_UNION;
#endif
#define SOC_IOC_IOCG_052_iocg_052_pu_START   (0)
#define SOC_IOC_IOCG_052_iocg_052_pu_END     (0)
#define SOC_IOC_IOCG_052_iocg_052_pd_START   (1)
#define SOC_IOC_IOCG_052_iocg_052_pd_END     (1)
#define SOC_IOC_IOCG_052_iocg_052_ds0_START  (4)
#define SOC_IOC_IOCG_052_iocg_052_ds0_END    (4)
#define SOC_IOC_IOCG_052_iocg_052_ds1_START  (5)
#define SOC_IOC_IOCG_052_iocg_052_ds1_END    (5)
#define SOC_IOC_IOCG_052_iocg_052_ds2_START  (6)
#define SOC_IOC_IOCG_052_iocg_052_ds2_END    (6)
#define SOC_IOC_IOCG_052_iocg_052_sr_START   (7)
#define SOC_IOC_IOCG_052_iocg_052_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_053_UNION
 结构说明  : IOCG_053 寄存器结构定义。地址偏移量:0x8D4，初值:0x00000012，宽度:32
 寄存器说明: SPI0_CS3_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_053_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_053_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_053_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_053_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_053_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_053_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_053_UNION;
#endif
#define SOC_IOC_IOCG_053_iocg_053_pu_START   (0)
#define SOC_IOC_IOCG_053_iocg_053_pu_END     (0)
#define SOC_IOC_IOCG_053_iocg_053_pd_START   (1)
#define SOC_IOC_IOCG_053_iocg_053_pd_END     (1)
#define SOC_IOC_IOCG_053_iocg_053_ds0_START  (4)
#define SOC_IOC_IOCG_053_iocg_053_ds0_END    (4)
#define SOC_IOC_IOCG_053_iocg_053_ds1_START  (5)
#define SOC_IOC_IOCG_053_iocg_053_ds1_END    (5)
#define SOC_IOC_IOCG_053_iocg_053_ds2_START  (6)
#define SOC_IOC_IOCG_053_iocg_053_ds2_END    (6)
#define SOC_IOC_IOCG_053_iocg_053_sr_START   (7)
#define SOC_IOC_IOCG_053_iocg_053_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_054_UNION
 结构说明  : IOCG_054 寄存器结构定义。地址偏移量:0x8D8，初值:0x00000012，宽度:32
 寄存器说明: GPIO_054功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_054_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_054_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_054_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_054_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_054_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_054_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_054_UNION;
#endif
#define SOC_IOC_IOCG_054_iocg_054_pu_START   (0)
#define SOC_IOC_IOCG_054_iocg_054_pu_END     (0)
#define SOC_IOC_IOCG_054_iocg_054_pd_START   (1)
#define SOC_IOC_IOCG_054_iocg_054_pd_END     (1)
#define SOC_IOC_IOCG_054_iocg_054_ds0_START  (4)
#define SOC_IOC_IOCG_054_iocg_054_ds0_END    (4)
#define SOC_IOC_IOCG_054_iocg_054_ds1_START  (5)
#define SOC_IOC_IOCG_054_iocg_054_ds1_END    (5)
#define SOC_IOC_IOCG_054_iocg_054_ds2_START  (6)
#define SOC_IOC_IOCG_054_iocg_054_ds2_END    (6)
#define SOC_IOC_IOCG_054_iocg_054_sr_START   (7)
#define SOC_IOC_IOCG_054_iocg_054_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_055_UNION
 结构说明  : IOCG_055 寄存器结构定义。地址偏移量:0x8DC，初值:0x00000012，宽度:32
 寄存器说明: GPIO_055功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_055_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_055_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_055_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_055_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_055_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_055_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_055_UNION;
#endif
#define SOC_IOC_IOCG_055_iocg_055_pu_START   (0)
#define SOC_IOC_IOCG_055_iocg_055_pu_END     (0)
#define SOC_IOC_IOCG_055_iocg_055_pd_START   (1)
#define SOC_IOC_IOCG_055_iocg_055_pd_END     (1)
#define SOC_IOC_IOCG_055_iocg_055_ds0_START  (4)
#define SOC_IOC_IOCG_055_iocg_055_ds0_END    (4)
#define SOC_IOC_IOCG_055_iocg_055_ds1_START  (5)
#define SOC_IOC_IOCG_055_iocg_055_ds1_END    (5)
#define SOC_IOC_IOCG_055_iocg_055_ds2_START  (6)
#define SOC_IOC_IOCG_055_iocg_055_ds2_END    (6)
#define SOC_IOC_IOCG_055_iocg_055_sr_START   (7)
#define SOC_IOC_IOCG_055_iocg_055_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_056_UNION
 结构说明  : IOCG_056 寄存器结构定义。地址偏移量:0x8E0，初值:0x00000012，宽度:32
 寄存器说明: EMMC50_RST_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_056_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_056_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_056_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_056_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_056_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_056_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_056_UNION;
#endif
#define SOC_IOC_IOCG_056_iocg_056_pu_START   (0)
#define SOC_IOC_IOCG_056_iocg_056_pu_END     (0)
#define SOC_IOC_IOCG_056_iocg_056_pd_START   (1)
#define SOC_IOC_IOCG_056_iocg_056_pd_END     (1)
#define SOC_IOC_IOCG_056_iocg_056_ds0_START  (4)
#define SOC_IOC_IOCG_056_iocg_056_ds0_END    (4)
#define SOC_IOC_IOCG_056_iocg_056_ds1_START  (5)
#define SOC_IOC_IOCG_056_iocg_056_ds1_END    (5)
#define SOC_IOC_IOCG_056_iocg_056_ds2_START  (6)
#define SOC_IOC_IOCG_056_iocg_056_ds2_END    (6)
#define SOC_IOC_IOCG_056_iocg_056_sr_START   (7)
#define SOC_IOC_IOCG_056_iocg_056_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_057_UNION
 结构说明  : IOCG_057 寄存器结构定义。地址偏移量:0x8E4，初值:0x00000012，宽度:32
 寄存器说明: UART1_CTS_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_057_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_057_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_057_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_057_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_057_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_057_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_057_UNION;
#endif
#define SOC_IOC_IOCG_057_iocg_057_pu_START   (0)
#define SOC_IOC_IOCG_057_iocg_057_pu_END     (0)
#define SOC_IOC_IOCG_057_iocg_057_pd_START   (1)
#define SOC_IOC_IOCG_057_iocg_057_pd_END     (1)
#define SOC_IOC_IOCG_057_iocg_057_ds0_START  (4)
#define SOC_IOC_IOCG_057_iocg_057_ds0_END    (4)
#define SOC_IOC_IOCG_057_iocg_057_ds1_START  (5)
#define SOC_IOC_IOCG_057_iocg_057_ds1_END    (5)
#define SOC_IOC_IOCG_057_iocg_057_ds2_START  (6)
#define SOC_IOC_IOCG_057_iocg_057_ds2_END    (6)
#define SOC_IOC_IOCG_057_iocg_057_sr_START   (7)
#define SOC_IOC_IOCG_057_iocg_057_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_058_UNION
 结构说明  : IOCG_058 寄存器结构定义。地址偏移量:0x8E8，初值:0x00000012，宽度:32
 寄存器说明: UART1_RTS_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_058_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_058_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_058_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_058_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_058_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_058_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_058_UNION;
#endif
#define SOC_IOC_IOCG_058_iocg_058_pu_START   (0)
#define SOC_IOC_IOCG_058_iocg_058_pu_END     (0)
#define SOC_IOC_IOCG_058_iocg_058_pd_START   (1)
#define SOC_IOC_IOCG_058_iocg_058_pd_END     (1)
#define SOC_IOC_IOCG_058_iocg_058_ds0_START  (4)
#define SOC_IOC_IOCG_058_iocg_058_ds0_END    (4)
#define SOC_IOC_IOCG_058_iocg_058_ds1_START  (5)
#define SOC_IOC_IOCG_058_iocg_058_ds1_END    (5)
#define SOC_IOC_IOCG_058_iocg_058_ds2_START  (6)
#define SOC_IOC_IOCG_058_iocg_058_ds2_END    (6)
#define SOC_IOC_IOCG_058_iocg_058_sr_START   (7)
#define SOC_IOC_IOCG_058_iocg_058_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_059_UNION
 结构说明  : IOCG_059 寄存器结构定义。地址偏移量:0x8EC，初值:0x00000012，宽度:32
 寄存器说明: UART1_RXD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_059_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_059_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_059_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_059_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_059_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_059_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_059_UNION;
#endif
#define SOC_IOC_IOCG_059_iocg_059_pu_START   (0)
#define SOC_IOC_IOCG_059_iocg_059_pu_END     (0)
#define SOC_IOC_IOCG_059_iocg_059_pd_START   (1)
#define SOC_IOC_IOCG_059_iocg_059_pd_END     (1)
#define SOC_IOC_IOCG_059_iocg_059_ds0_START  (4)
#define SOC_IOC_IOCG_059_iocg_059_ds0_END    (4)
#define SOC_IOC_IOCG_059_iocg_059_ds1_START  (5)
#define SOC_IOC_IOCG_059_iocg_059_ds1_END    (5)
#define SOC_IOC_IOCG_059_iocg_059_ds2_START  (6)
#define SOC_IOC_IOCG_059_iocg_059_ds2_END    (6)
#define SOC_IOC_IOCG_059_iocg_059_sr_START   (7)
#define SOC_IOC_IOCG_059_iocg_059_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_060_UNION
 结构说明  : IOCG_060 寄存器结构定义。地址偏移量:0x8F0，初值:0x00000012，宽度:32
 寄存器说明: UART1_TXD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_060_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_060_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_060_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_060_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_060_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_060_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_060_UNION;
#endif
#define SOC_IOC_IOCG_060_iocg_060_pu_START   (0)
#define SOC_IOC_IOCG_060_iocg_060_pu_END     (0)
#define SOC_IOC_IOCG_060_iocg_060_pd_START   (1)
#define SOC_IOC_IOCG_060_iocg_060_pd_END     (1)
#define SOC_IOC_IOCG_060_iocg_060_ds0_START  (4)
#define SOC_IOC_IOCG_060_iocg_060_ds0_END    (4)
#define SOC_IOC_IOCG_060_iocg_060_ds1_START  (5)
#define SOC_IOC_IOCG_060_iocg_060_ds1_END    (5)
#define SOC_IOC_IOCG_060_iocg_060_ds2_START  (6)
#define SOC_IOC_IOCG_060_iocg_060_ds2_END    (6)
#define SOC_IOC_IOCG_060_iocg_060_sr_START   (7)
#define SOC_IOC_IOCG_060_iocg_060_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_061_UNION
 结构说明  : IOCG_061 寄存器结构定义。地址偏移量:0x8F4，初值:0x00000012，宽度:32
 寄存器说明: SDIO0_CLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_061_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_061_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_061_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_061_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_061_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_061_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_061_UNION;
#endif
#define SOC_IOC_IOCG_061_iocg_061_pu_START   (0)
#define SOC_IOC_IOCG_061_iocg_061_pu_END     (0)
#define SOC_IOC_IOCG_061_iocg_061_pd_START   (1)
#define SOC_IOC_IOCG_061_iocg_061_pd_END     (1)
#define SOC_IOC_IOCG_061_iocg_061_ds0_START  (4)
#define SOC_IOC_IOCG_061_iocg_061_ds0_END    (4)
#define SOC_IOC_IOCG_061_iocg_061_ds1_START  (5)
#define SOC_IOC_IOCG_061_iocg_061_ds1_END    (5)
#define SOC_IOC_IOCG_061_iocg_061_ds2_START  (6)
#define SOC_IOC_IOCG_061_iocg_061_ds2_END    (6)
#define SOC_IOC_IOCG_061_iocg_061_sr_START   (7)
#define SOC_IOC_IOCG_061_iocg_061_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_062_UNION
 结构说明  : IOCG_062 寄存器结构定义。地址偏移量:0x8F8，初值:0x00000012，宽度:32
 寄存器说明: SDIO0_CMD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_062_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_062_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_062_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_062_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_062_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_062_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_062_UNION;
#endif
#define SOC_IOC_IOCG_062_iocg_062_pu_START   (0)
#define SOC_IOC_IOCG_062_iocg_062_pu_END     (0)
#define SOC_IOC_IOCG_062_iocg_062_pd_START   (1)
#define SOC_IOC_IOCG_062_iocg_062_pd_END     (1)
#define SOC_IOC_IOCG_062_iocg_062_ds0_START  (4)
#define SOC_IOC_IOCG_062_iocg_062_ds0_END    (4)
#define SOC_IOC_IOCG_062_iocg_062_ds1_START  (5)
#define SOC_IOC_IOCG_062_iocg_062_ds1_END    (5)
#define SOC_IOC_IOCG_062_iocg_062_ds2_START  (6)
#define SOC_IOC_IOCG_062_iocg_062_ds2_END    (6)
#define SOC_IOC_IOCG_062_iocg_062_sr_START   (7)
#define SOC_IOC_IOCG_062_iocg_062_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_063_UNION
 结构说明  : IOCG_063 寄存器结构定义。地址偏移量:0x8FC，初值:0x00000012，宽度:32
 寄存器说明: SDIO0_DATA0功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_063_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_063_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_063_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_063_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_063_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_063_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_063_UNION;
#endif
#define SOC_IOC_IOCG_063_iocg_063_pu_START   (0)
#define SOC_IOC_IOCG_063_iocg_063_pu_END     (0)
#define SOC_IOC_IOCG_063_iocg_063_pd_START   (1)
#define SOC_IOC_IOCG_063_iocg_063_pd_END     (1)
#define SOC_IOC_IOCG_063_iocg_063_ds0_START  (4)
#define SOC_IOC_IOCG_063_iocg_063_ds0_END    (4)
#define SOC_IOC_IOCG_063_iocg_063_ds1_START  (5)
#define SOC_IOC_IOCG_063_iocg_063_ds1_END    (5)
#define SOC_IOC_IOCG_063_iocg_063_ds2_START  (6)
#define SOC_IOC_IOCG_063_iocg_063_ds2_END    (6)
#define SOC_IOC_IOCG_063_iocg_063_sr_START   (7)
#define SOC_IOC_IOCG_063_iocg_063_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_064_UNION
 结构说明  : IOCG_064 寄存器结构定义。地址偏移量:0x900，初值:0x00000012，宽度:32
 寄存器说明: SDIO0_DATA1功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_064_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_064_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_064_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_064_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_064_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_064_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_064_UNION;
#endif
#define SOC_IOC_IOCG_064_iocg_064_pu_START   (0)
#define SOC_IOC_IOCG_064_iocg_064_pu_END     (0)
#define SOC_IOC_IOCG_064_iocg_064_pd_START   (1)
#define SOC_IOC_IOCG_064_iocg_064_pd_END     (1)
#define SOC_IOC_IOCG_064_iocg_064_ds0_START  (4)
#define SOC_IOC_IOCG_064_iocg_064_ds0_END    (4)
#define SOC_IOC_IOCG_064_iocg_064_ds1_START  (5)
#define SOC_IOC_IOCG_064_iocg_064_ds1_END    (5)
#define SOC_IOC_IOCG_064_iocg_064_ds2_START  (6)
#define SOC_IOC_IOCG_064_iocg_064_ds2_END    (6)
#define SOC_IOC_IOCG_064_iocg_064_sr_START   (7)
#define SOC_IOC_IOCG_064_iocg_064_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_065_UNION
 结构说明  : IOCG_065 寄存器结构定义。地址偏移量:0x904，初值:0x00000012，宽度:32
 寄存器说明: SDIO0_DATA2功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_065_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_065_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_065_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_065_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_065_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_065_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_065_UNION;
#endif
#define SOC_IOC_IOCG_065_iocg_065_pu_START   (0)
#define SOC_IOC_IOCG_065_iocg_065_pu_END     (0)
#define SOC_IOC_IOCG_065_iocg_065_pd_START   (1)
#define SOC_IOC_IOCG_065_iocg_065_pd_END     (1)
#define SOC_IOC_IOCG_065_iocg_065_ds0_START  (4)
#define SOC_IOC_IOCG_065_iocg_065_ds0_END    (4)
#define SOC_IOC_IOCG_065_iocg_065_ds1_START  (5)
#define SOC_IOC_IOCG_065_iocg_065_ds1_END    (5)
#define SOC_IOC_IOCG_065_iocg_065_ds2_START  (6)
#define SOC_IOC_IOCG_065_iocg_065_ds2_END    (6)
#define SOC_IOC_IOCG_065_iocg_065_sr_START   (7)
#define SOC_IOC_IOCG_065_iocg_065_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_066_UNION
 结构说明  : IOCG_066 寄存器结构定义。地址偏移量:0x908，初值:0x00000012，宽度:32
 寄存器说明: SDIO0_DATA3功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_066_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_066_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_066_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_066_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_066_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_066_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_066_UNION;
#endif
#define SOC_IOC_IOCG_066_iocg_066_pu_START   (0)
#define SOC_IOC_IOCG_066_iocg_066_pu_END     (0)
#define SOC_IOC_IOCG_066_iocg_066_pd_START   (1)
#define SOC_IOC_IOCG_066_iocg_066_pd_END     (1)
#define SOC_IOC_IOCG_066_iocg_066_ds0_START  (4)
#define SOC_IOC_IOCG_066_iocg_066_ds0_END    (4)
#define SOC_IOC_IOCG_066_iocg_066_ds1_START  (5)
#define SOC_IOC_IOCG_066_iocg_066_ds1_END    (5)
#define SOC_IOC_IOCG_066_iocg_066_ds2_START  (6)
#define SOC_IOC_IOCG_066_iocg_066_ds2_END    (6)
#define SOC_IOC_IOCG_066_iocg_066_sr_START   (7)
#define SOC_IOC_IOCG_066_iocg_066_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_067_UNION
 结构说明  : IOCG_067 寄存器结构定义。地址偏移量:0x90C，初值:0x00000012，宽度:32
 寄存器说明: UART6_CTS_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_067_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_067_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_067_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_067_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_067_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_067_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_067_UNION;
#endif
#define SOC_IOC_IOCG_067_iocg_067_pu_START   (0)
#define SOC_IOC_IOCG_067_iocg_067_pu_END     (0)
#define SOC_IOC_IOCG_067_iocg_067_pd_START   (1)
#define SOC_IOC_IOCG_067_iocg_067_pd_END     (1)
#define SOC_IOC_IOCG_067_iocg_067_ds0_START  (4)
#define SOC_IOC_IOCG_067_iocg_067_ds0_END    (4)
#define SOC_IOC_IOCG_067_iocg_067_ds1_START  (5)
#define SOC_IOC_IOCG_067_iocg_067_ds1_END    (5)
#define SOC_IOC_IOCG_067_iocg_067_ds2_START  (6)
#define SOC_IOC_IOCG_067_iocg_067_ds2_END    (6)
#define SOC_IOC_IOCG_067_iocg_067_sr_START   (7)
#define SOC_IOC_IOCG_067_iocg_067_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_068_UNION
 结构说明  : IOCG_068 寄存器结构定义。地址偏移量:0x910，初值:0x00000012，宽度:32
 寄存器说明: UART6_RTS_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_068_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_068_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_068_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_068_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_068_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_068_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_068_UNION;
#endif
#define SOC_IOC_IOCG_068_iocg_068_pu_START   (0)
#define SOC_IOC_IOCG_068_iocg_068_pu_END     (0)
#define SOC_IOC_IOCG_068_iocg_068_pd_START   (1)
#define SOC_IOC_IOCG_068_iocg_068_pd_END     (1)
#define SOC_IOC_IOCG_068_iocg_068_ds0_START  (4)
#define SOC_IOC_IOCG_068_iocg_068_ds0_END    (4)
#define SOC_IOC_IOCG_068_iocg_068_ds1_START  (5)
#define SOC_IOC_IOCG_068_iocg_068_ds1_END    (5)
#define SOC_IOC_IOCG_068_iocg_068_ds2_START  (6)
#define SOC_IOC_IOCG_068_iocg_068_ds2_END    (6)
#define SOC_IOC_IOCG_068_iocg_068_sr_START   (7)
#define SOC_IOC_IOCG_068_iocg_068_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_069_UNION
 结构说明  : IOCG_069 寄存器结构定义。地址偏移量:0x914，初值:0x00000012，宽度:32
 寄存器说明: UART6_RXD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_069_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_069_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_069_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_069_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_069_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_069_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_069_UNION;
#endif
#define SOC_IOC_IOCG_069_iocg_069_pu_START   (0)
#define SOC_IOC_IOCG_069_iocg_069_pu_END     (0)
#define SOC_IOC_IOCG_069_iocg_069_pd_START   (1)
#define SOC_IOC_IOCG_069_iocg_069_pd_END     (1)
#define SOC_IOC_IOCG_069_iocg_069_ds0_START  (4)
#define SOC_IOC_IOCG_069_iocg_069_ds0_END    (4)
#define SOC_IOC_IOCG_069_iocg_069_ds1_START  (5)
#define SOC_IOC_IOCG_069_iocg_069_ds1_END    (5)
#define SOC_IOC_IOCG_069_iocg_069_ds2_START  (6)
#define SOC_IOC_IOCG_069_iocg_069_ds2_END    (6)
#define SOC_IOC_IOCG_069_iocg_069_sr_START   (7)
#define SOC_IOC_IOCG_069_iocg_069_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_070_UNION
 结构说明  : IOCG_070 寄存器结构定义。地址偏移量:0x918，初值:0x00000012，宽度:32
 寄存器说明: UART6_TXD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_070_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_070_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_070_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_070_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_070_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_070_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_070_UNION;
#endif
#define SOC_IOC_IOCG_070_iocg_070_pu_START   (0)
#define SOC_IOC_IOCG_070_iocg_070_pu_END     (0)
#define SOC_IOC_IOCG_070_iocg_070_pd_START   (1)
#define SOC_IOC_IOCG_070_iocg_070_pd_END     (1)
#define SOC_IOC_IOCG_070_iocg_070_ds0_START  (4)
#define SOC_IOC_IOCG_070_iocg_070_ds0_END    (4)
#define SOC_IOC_IOCG_070_iocg_070_ds1_START  (5)
#define SOC_IOC_IOCG_070_iocg_070_ds1_END    (5)
#define SOC_IOC_IOCG_070_iocg_070_ds2_START  (6)
#define SOC_IOC_IOCG_070_iocg_070_ds2_END    (6)
#define SOC_IOC_IOCG_070_iocg_070_sr_START   (7)
#define SOC_IOC_IOCG_070_iocg_070_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_071_UNION
 结构说明  : IOCG_071 寄存器结构定义。地址偏移量:0x91C，初值:0x00000012，宽度:32
 寄存器说明: UART3_CTS_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_071_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_071_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_071_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_071_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_071_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_071_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_071_UNION;
#endif
#define SOC_IOC_IOCG_071_iocg_071_pu_START   (0)
#define SOC_IOC_IOCG_071_iocg_071_pu_END     (0)
#define SOC_IOC_IOCG_071_iocg_071_pd_START   (1)
#define SOC_IOC_IOCG_071_iocg_071_pd_END     (1)
#define SOC_IOC_IOCG_071_iocg_071_ds0_START  (4)
#define SOC_IOC_IOCG_071_iocg_071_ds0_END    (4)
#define SOC_IOC_IOCG_071_iocg_071_ds1_START  (5)
#define SOC_IOC_IOCG_071_iocg_071_ds1_END    (5)
#define SOC_IOC_IOCG_071_iocg_071_ds2_START  (6)
#define SOC_IOC_IOCG_071_iocg_071_ds2_END    (6)
#define SOC_IOC_IOCG_071_iocg_071_sr_START   (7)
#define SOC_IOC_IOCG_071_iocg_071_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_072_UNION
 结构说明  : IOCG_072 寄存器结构定义。地址偏移量:0x920，初值:0x00000012，宽度:32
 寄存器说明: UART3_RTS_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_072_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_072_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_072_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_072_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_072_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_072_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_072_UNION;
#endif
#define SOC_IOC_IOCG_072_iocg_072_pu_START   (0)
#define SOC_IOC_IOCG_072_iocg_072_pu_END     (0)
#define SOC_IOC_IOCG_072_iocg_072_pd_START   (1)
#define SOC_IOC_IOCG_072_iocg_072_pd_END     (1)
#define SOC_IOC_IOCG_072_iocg_072_ds0_START  (4)
#define SOC_IOC_IOCG_072_iocg_072_ds0_END    (4)
#define SOC_IOC_IOCG_072_iocg_072_ds1_START  (5)
#define SOC_IOC_IOCG_072_iocg_072_ds1_END    (5)
#define SOC_IOC_IOCG_072_iocg_072_ds2_START  (6)
#define SOC_IOC_IOCG_072_iocg_072_ds2_END    (6)
#define SOC_IOC_IOCG_072_iocg_072_sr_START   (7)
#define SOC_IOC_IOCG_072_iocg_072_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_073_UNION
 结构说明  : IOCG_073 寄存器结构定义。地址偏移量:0x924，初值:0x00000012，宽度:32
 寄存器说明: UART3_RXD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_073_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_073_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_073_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_073_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_073_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_073_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_073_UNION;
#endif
#define SOC_IOC_IOCG_073_iocg_073_pu_START   (0)
#define SOC_IOC_IOCG_073_iocg_073_pu_END     (0)
#define SOC_IOC_IOCG_073_iocg_073_pd_START   (1)
#define SOC_IOC_IOCG_073_iocg_073_pd_END     (1)
#define SOC_IOC_IOCG_073_iocg_073_ds0_START  (4)
#define SOC_IOC_IOCG_073_iocg_073_ds0_END    (4)
#define SOC_IOC_IOCG_073_iocg_073_ds1_START  (5)
#define SOC_IOC_IOCG_073_iocg_073_ds1_END    (5)
#define SOC_IOC_IOCG_073_iocg_073_ds2_START  (6)
#define SOC_IOC_IOCG_073_iocg_073_ds2_END    (6)
#define SOC_IOC_IOCG_073_iocg_073_sr_START   (7)
#define SOC_IOC_IOCG_073_iocg_073_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_074_UNION
 结构说明  : IOCG_074 寄存器结构定义。地址偏移量:0x928，初值:0x00000012，宽度:32
 寄存器说明: UART3_TXD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_074_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_074_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_074_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_074_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_074_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_074_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_074_UNION;
#endif
#define SOC_IOC_IOCG_074_iocg_074_pu_START   (0)
#define SOC_IOC_IOCG_074_iocg_074_pu_END     (0)
#define SOC_IOC_IOCG_074_iocg_074_pd_START   (1)
#define SOC_IOC_IOCG_074_iocg_074_pd_END     (1)
#define SOC_IOC_IOCG_074_iocg_074_ds0_START  (4)
#define SOC_IOC_IOCG_074_iocg_074_ds0_END    (4)
#define SOC_IOC_IOCG_074_iocg_074_ds1_START  (5)
#define SOC_IOC_IOCG_074_iocg_074_ds1_END    (5)
#define SOC_IOC_IOCG_074_iocg_074_ds2_START  (6)
#define SOC_IOC_IOCG_074_iocg_074_ds2_END    (6)
#define SOC_IOC_IOCG_074_iocg_074_sr_START   (7)
#define SOC_IOC_IOCG_074_iocg_074_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_075_UNION
 结构说明  : IOCG_075 寄存器结构定义。地址偏移量:0x92C，初值:0x00000012，宽度:32
 寄存器说明: UART4_CTS_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_075_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_075_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_075_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_075_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_075_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_075_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_075_UNION;
#endif
#define SOC_IOC_IOCG_075_iocg_075_pu_START   (0)
#define SOC_IOC_IOCG_075_iocg_075_pu_END     (0)
#define SOC_IOC_IOCG_075_iocg_075_pd_START   (1)
#define SOC_IOC_IOCG_075_iocg_075_pd_END     (1)
#define SOC_IOC_IOCG_075_iocg_075_ds0_START  (4)
#define SOC_IOC_IOCG_075_iocg_075_ds0_END    (4)
#define SOC_IOC_IOCG_075_iocg_075_ds1_START  (5)
#define SOC_IOC_IOCG_075_iocg_075_ds1_END    (5)
#define SOC_IOC_IOCG_075_iocg_075_ds2_START  (6)
#define SOC_IOC_IOCG_075_iocg_075_ds2_END    (6)
#define SOC_IOC_IOCG_075_iocg_075_sr_START   (7)
#define SOC_IOC_IOCG_075_iocg_075_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_076_UNION
 结构说明  : IOCG_076 寄存器结构定义。地址偏移量:0x930，初值:0x00000012，宽度:32
 寄存器说明: UART4_RTS_N功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_076_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_076_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_076_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_076_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_076_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_076_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_076_UNION;
#endif
#define SOC_IOC_IOCG_076_iocg_076_pu_START   (0)
#define SOC_IOC_IOCG_076_iocg_076_pu_END     (0)
#define SOC_IOC_IOCG_076_iocg_076_pd_START   (1)
#define SOC_IOC_IOCG_076_iocg_076_pd_END     (1)
#define SOC_IOC_IOCG_076_iocg_076_ds0_START  (4)
#define SOC_IOC_IOCG_076_iocg_076_ds0_END    (4)
#define SOC_IOC_IOCG_076_iocg_076_ds1_START  (5)
#define SOC_IOC_IOCG_076_iocg_076_ds1_END    (5)
#define SOC_IOC_IOCG_076_iocg_076_ds2_START  (6)
#define SOC_IOC_IOCG_076_iocg_076_ds2_END    (6)
#define SOC_IOC_IOCG_076_iocg_076_sr_START   (7)
#define SOC_IOC_IOCG_076_iocg_076_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_077_UNION
 结构说明  : IOCG_077 寄存器结构定义。地址偏移量:0x934，初值:0x00000012，宽度:32
 寄存器说明: UART4_RXD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_077_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_077_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_077_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_077_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_077_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_077_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_077_UNION;
#endif
#define SOC_IOC_IOCG_077_iocg_077_pu_START   (0)
#define SOC_IOC_IOCG_077_iocg_077_pu_END     (0)
#define SOC_IOC_IOCG_077_iocg_077_pd_START   (1)
#define SOC_IOC_IOCG_077_iocg_077_pd_END     (1)
#define SOC_IOC_IOCG_077_iocg_077_ds0_START  (4)
#define SOC_IOC_IOCG_077_iocg_077_ds0_END    (4)
#define SOC_IOC_IOCG_077_iocg_077_ds1_START  (5)
#define SOC_IOC_IOCG_077_iocg_077_ds1_END    (5)
#define SOC_IOC_IOCG_077_iocg_077_ds2_START  (6)
#define SOC_IOC_IOCG_077_iocg_077_ds2_END    (6)
#define SOC_IOC_IOCG_077_iocg_077_sr_START   (7)
#define SOC_IOC_IOCG_077_iocg_077_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_078_UNION
 结构说明  : IOCG_078 寄存器结构定义。地址偏移量:0x938，初值:0x00000012，宽度:32
 寄存器说明: UART4_TXD功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_078_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_078_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_078_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_078_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_078_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_078_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_078_UNION;
#endif
#define SOC_IOC_IOCG_078_iocg_078_pu_START   (0)
#define SOC_IOC_IOCG_078_iocg_078_pu_END     (0)
#define SOC_IOC_IOCG_078_iocg_078_pd_START   (1)
#define SOC_IOC_IOCG_078_iocg_078_pd_END     (1)
#define SOC_IOC_IOCG_078_iocg_078_ds0_START  (4)
#define SOC_IOC_IOCG_078_iocg_078_ds0_END    (4)
#define SOC_IOC_IOCG_078_iocg_078_ds1_START  (5)
#define SOC_IOC_IOCG_078_iocg_078_ds1_END    (5)
#define SOC_IOC_IOCG_078_iocg_078_ds2_START  (6)
#define SOC_IOC_IOCG_078_iocg_078_ds2_END    (6)
#define SOC_IOC_IOCG_078_iocg_078_sr_START   (7)
#define SOC_IOC_IOCG_078_iocg_078_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_079_UNION
 结构说明  : IOCG_079 寄存器结构定义。地址偏移量:0x93C，初值:0x00000012，宽度:32
 寄存器说明: PWM_OUT1功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_079_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_079_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_079_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_079_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_079_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_079_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_079_UNION;
#endif
#define SOC_IOC_IOCG_079_iocg_079_pu_START   (0)
#define SOC_IOC_IOCG_079_iocg_079_pu_END     (0)
#define SOC_IOC_IOCG_079_iocg_079_pd_START   (1)
#define SOC_IOC_IOCG_079_iocg_079_pd_END     (1)
#define SOC_IOC_IOCG_079_iocg_079_ds0_START  (4)
#define SOC_IOC_IOCG_079_iocg_079_ds0_END    (4)
#define SOC_IOC_IOCG_079_iocg_079_ds1_START  (5)
#define SOC_IOC_IOCG_079_iocg_079_ds1_END    (5)
#define SOC_IOC_IOCG_079_iocg_079_ds2_START  (6)
#define SOC_IOC_IOCG_079_iocg_079_ds2_END    (6)
#define SOC_IOC_IOCG_079_iocg_079_sr_START   (7)
#define SOC_IOC_IOCG_079_iocg_079_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_080_UNION
 结构说明  : IOCG_080 寄存器结构定义。地址偏移量:0x940，初值:0x00000012，宽度:32
 寄存器说明: PMU_HKADC_SSI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_080_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_080_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_080_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_080_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_080_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_080_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_080_UNION;
#endif
#define SOC_IOC_IOCG_080_iocg_080_pu_START   (0)
#define SOC_IOC_IOCG_080_iocg_080_pu_END     (0)
#define SOC_IOC_IOCG_080_iocg_080_pd_START   (1)
#define SOC_IOC_IOCG_080_iocg_080_pd_END     (1)
#define SOC_IOC_IOCG_080_iocg_080_ds0_START  (4)
#define SOC_IOC_IOCG_080_iocg_080_ds0_END    (4)
#define SOC_IOC_IOCG_080_iocg_080_ds1_START  (5)
#define SOC_IOC_IOCG_080_iocg_080_ds1_END    (5)
#define SOC_IOC_IOCG_080_iocg_080_ds2_START  (6)
#define SOC_IOC_IOCG_080_iocg_080_ds2_END    (6)
#define SOC_IOC_IOCG_080_iocg_080_sr_START   (7)
#define SOC_IOC_IOCG_080_iocg_080_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_081_UNION
 结构说明  : IOCG_081 寄存器结构定义。地址偏移量:0x944，初值:0x00000010，宽度:32
 寄存器说明: PMU_AUXDAC0_SSI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_081_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_081_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_081_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_081_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_081_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_081_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_081_UNION;
#endif
#define SOC_IOC_IOCG_081_iocg_081_pu_START   (0)
#define SOC_IOC_IOCG_081_iocg_081_pu_END     (0)
#define SOC_IOC_IOCG_081_iocg_081_pd_START   (1)
#define SOC_IOC_IOCG_081_iocg_081_pd_END     (1)
#define SOC_IOC_IOCG_081_iocg_081_ds0_START  (4)
#define SOC_IOC_IOCG_081_iocg_081_ds0_END    (4)
#define SOC_IOC_IOCG_081_iocg_081_ds1_START  (5)
#define SOC_IOC_IOCG_081_iocg_081_ds1_END    (5)
#define SOC_IOC_IOCG_081_iocg_081_ds2_START  (6)
#define SOC_IOC_IOCG_081_iocg_081_ds2_END    (6)
#define SOC_IOC_IOCG_081_iocg_081_sr_START   (7)
#define SOC_IOC_IOCG_081_iocg_081_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_082_UNION
 结构说明  : IOCG_082 寄存器结构定义。地址偏移量:0x948，初值:0x00000010，宽度:32
 寄存器说明: PMU_AUXDAC1_SSI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_082_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_082_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_082_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_082_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_082_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_082_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_082_UNION;
#endif
#define SOC_IOC_IOCG_082_iocg_082_pu_START   (0)
#define SOC_IOC_IOCG_082_iocg_082_pu_END     (0)
#define SOC_IOC_IOCG_082_iocg_082_pd_START   (1)
#define SOC_IOC_IOCG_082_iocg_082_pd_END     (1)
#define SOC_IOC_IOCG_082_iocg_082_ds0_START  (4)
#define SOC_IOC_IOCG_082_iocg_082_ds0_END    (4)
#define SOC_IOC_IOCG_082_iocg_082_ds1_START  (5)
#define SOC_IOC_IOCG_082_iocg_082_ds1_END    (5)
#define SOC_IOC_IOCG_082_iocg_082_ds2_START  (6)
#define SOC_IOC_IOCG_082_iocg_082_ds2_END    (6)
#define SOC_IOC_IOCG_082_iocg_082_sr_START   (7)
#define SOC_IOC_IOCG_082_iocg_082_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_083_UNION
 结构说明  : IOCG_083 寄存器结构定义。地址偏移量:0x94C，初值:0x00000012，宽度:32
 寄存器说明: USIM0_CLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_083_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_083_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_083_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_083_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_083_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_083_UNION;
#endif
#define SOC_IOC_IOCG_083_iocg_083_pu_START   (0)
#define SOC_IOC_IOCG_083_iocg_083_pu_END     (0)
#define SOC_IOC_IOCG_083_iocg_083_pd_START   (1)
#define SOC_IOC_IOCG_083_iocg_083_pd_END     (1)
#define SOC_IOC_IOCG_083_iocg_083_ds0_START  (4)
#define SOC_IOC_IOCG_083_iocg_083_ds0_END    (4)
#define SOC_IOC_IOCG_083_iocg_083_ds1_START  (5)
#define SOC_IOC_IOCG_083_iocg_083_ds1_END    (5)
#define SOC_IOC_IOCG_083_iocg_083_ds2_START  (6)
#define SOC_IOC_IOCG_083_iocg_083_ds2_END    (6)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_084_UNION
 结构说明  : IOCG_084 寄存器结构定义。地址偏移量:0x950，初值:0x00000012，宽度:32
 寄存器说明: USIM0_RST功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_084_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_084_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_084_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_084_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_084_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_084_UNION;
#endif
#define SOC_IOC_IOCG_084_iocg_084_pu_START   (0)
#define SOC_IOC_IOCG_084_iocg_084_pu_END     (0)
#define SOC_IOC_IOCG_084_iocg_084_pd_START   (1)
#define SOC_IOC_IOCG_084_iocg_084_pd_END     (1)
#define SOC_IOC_IOCG_084_iocg_084_ds0_START  (4)
#define SOC_IOC_IOCG_084_iocg_084_ds0_END    (4)
#define SOC_IOC_IOCG_084_iocg_084_ds1_START  (5)
#define SOC_IOC_IOCG_084_iocg_084_ds1_END    (5)
#define SOC_IOC_IOCG_084_iocg_084_ds2_START  (6)
#define SOC_IOC_IOCG_084_iocg_084_ds2_END    (6)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_085_UNION
 结构说明  : IOCG_085 寄存器结构定义。地址偏移量:0x954，初值:0x00000012，宽度:32
 寄存器说明: USIM0_DATA功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_085_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_085_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_085_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_085_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_085_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_085_UNION;
#endif
#define SOC_IOC_IOCG_085_iocg_085_pu_START   (0)
#define SOC_IOC_IOCG_085_iocg_085_pu_END     (0)
#define SOC_IOC_IOCG_085_iocg_085_pd_START   (1)
#define SOC_IOC_IOCG_085_iocg_085_pd_END     (1)
#define SOC_IOC_IOCG_085_iocg_085_ds0_START  (4)
#define SOC_IOC_IOCG_085_iocg_085_ds0_END    (4)
#define SOC_IOC_IOCG_085_iocg_085_ds1_START  (5)
#define SOC_IOC_IOCG_085_iocg_085_ds1_END    (5)
#define SOC_IOC_IOCG_085_iocg_085_ds2_START  (6)
#define SOC_IOC_IOCG_085_iocg_085_ds2_END    (6)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_086_UNION
 结构说明  : IOCG_086 寄存器结构定义。地址偏移量:0x958，初值:0x00000012，宽度:32
 寄存器说明: USIM1_CLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_086_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_086_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_086_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_086_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_086_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_086_UNION;
#endif
#define SOC_IOC_IOCG_086_iocg_086_pu_START   (0)
#define SOC_IOC_IOCG_086_iocg_086_pu_END     (0)
#define SOC_IOC_IOCG_086_iocg_086_pd_START   (1)
#define SOC_IOC_IOCG_086_iocg_086_pd_END     (1)
#define SOC_IOC_IOCG_086_iocg_086_ds0_START  (4)
#define SOC_IOC_IOCG_086_iocg_086_ds0_END    (4)
#define SOC_IOC_IOCG_086_iocg_086_ds1_START  (5)
#define SOC_IOC_IOCG_086_iocg_086_ds1_END    (5)
#define SOC_IOC_IOCG_086_iocg_086_ds2_START  (6)
#define SOC_IOC_IOCG_086_iocg_086_ds2_END    (6)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_087_UNION
 结构说明  : IOCG_087 寄存器结构定义。地址偏移量:0x95C，初值:0x00000012，宽度:32
 寄存器说明: USIM1_RST功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_087_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_087_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_087_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_087_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_087_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_087_UNION;
#endif
#define SOC_IOC_IOCG_087_iocg_087_pu_START   (0)
#define SOC_IOC_IOCG_087_iocg_087_pu_END     (0)
#define SOC_IOC_IOCG_087_iocg_087_pd_START   (1)
#define SOC_IOC_IOCG_087_iocg_087_pd_END     (1)
#define SOC_IOC_IOCG_087_iocg_087_ds0_START  (4)
#define SOC_IOC_IOCG_087_iocg_087_ds0_END    (4)
#define SOC_IOC_IOCG_087_iocg_087_ds1_START  (5)
#define SOC_IOC_IOCG_087_iocg_087_ds1_END    (5)
#define SOC_IOC_IOCG_087_iocg_087_ds2_START  (6)
#define SOC_IOC_IOCG_087_iocg_087_ds2_END    (6)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_088_UNION
 结构说明  : IOCG_088 寄存器结构定义。地址偏移量:0x960，初值:0x00000012，宽度:32
 寄存器说明: USIM1_DATA功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_088_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_088_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_088_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_088_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_088_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  reserved_1   : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_088_UNION;
#endif
#define SOC_IOC_IOCG_088_iocg_088_pu_START   (0)
#define SOC_IOC_IOCG_088_iocg_088_pu_END     (0)
#define SOC_IOC_IOCG_088_iocg_088_pd_START   (1)
#define SOC_IOC_IOCG_088_iocg_088_pd_END     (1)
#define SOC_IOC_IOCG_088_iocg_088_ds0_START  (4)
#define SOC_IOC_IOCG_088_iocg_088_ds0_END    (4)
#define SOC_IOC_IOCG_088_iocg_088_ds1_START  (5)
#define SOC_IOC_IOCG_088_iocg_088_ds1_END    (5)
#define SOC_IOC_IOCG_088_iocg_088_ds2_START  (6)
#define SOC_IOC_IOCG_088_iocg_088_ds2_END    (6)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_089_UNION
 结构说明  : IOCG_089 寄存器结构定义。地址偏移量:0x964，初值:0x00000012，宽度:32
 寄存器说明: LTE_INACTIVE功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_089_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_089_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_089_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_089_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_089_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_089_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_089_UNION;
#endif
#define SOC_IOC_IOCG_089_iocg_089_pu_START   (0)
#define SOC_IOC_IOCG_089_iocg_089_pu_END     (0)
#define SOC_IOC_IOCG_089_iocg_089_pd_START   (1)
#define SOC_IOC_IOCG_089_iocg_089_pd_END     (1)
#define SOC_IOC_IOCG_089_iocg_089_ds0_START  (4)
#define SOC_IOC_IOCG_089_iocg_089_ds0_END    (4)
#define SOC_IOC_IOCG_089_iocg_089_ds1_START  (5)
#define SOC_IOC_IOCG_089_iocg_089_ds1_END    (5)
#define SOC_IOC_IOCG_089_iocg_089_ds2_START  (6)
#define SOC_IOC_IOCG_089_iocg_089_ds2_END    (6)
#define SOC_IOC_IOCG_089_iocg_089_sr_START   (7)
#define SOC_IOC_IOCG_089_iocg_089_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_090_UNION
 结构说明  : IOCG_090 寄存器结构定义。地址偏移量:0x968，初值:0x00000012，宽度:32
 寄存器说明: LTE_RX_ACTIVE功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_090_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_090_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_090_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_090_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_090_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_090_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_090_UNION;
#endif
#define SOC_IOC_IOCG_090_iocg_090_pu_START   (0)
#define SOC_IOC_IOCG_090_iocg_090_pu_END     (0)
#define SOC_IOC_IOCG_090_iocg_090_pd_START   (1)
#define SOC_IOC_IOCG_090_iocg_090_pd_END     (1)
#define SOC_IOC_IOCG_090_iocg_090_ds0_START  (4)
#define SOC_IOC_IOCG_090_iocg_090_ds0_END    (4)
#define SOC_IOC_IOCG_090_iocg_090_ds1_START  (5)
#define SOC_IOC_IOCG_090_iocg_090_ds1_END    (5)
#define SOC_IOC_IOCG_090_iocg_090_ds2_START  (6)
#define SOC_IOC_IOCG_090_iocg_090_ds2_END    (6)
#define SOC_IOC_IOCG_090_iocg_090_sr_START   (7)
#define SOC_IOC_IOCG_090_iocg_090_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_091_UNION
 结构说明  : IOCG_091 寄存器结构定义。地址偏移量:0x96C，初值:0x00000012，宽度:32
 寄存器说明: LTE_TX_ACTIVE功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_091_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_091_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_091_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_091_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_091_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_091_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_091_UNION;
#endif
#define SOC_IOC_IOCG_091_iocg_091_pu_START   (0)
#define SOC_IOC_IOCG_091_iocg_091_pu_END     (0)
#define SOC_IOC_IOCG_091_iocg_091_pd_START   (1)
#define SOC_IOC_IOCG_091_iocg_091_pd_END     (1)
#define SOC_IOC_IOCG_091_iocg_091_ds0_START  (4)
#define SOC_IOC_IOCG_091_iocg_091_ds0_END    (4)
#define SOC_IOC_IOCG_091_iocg_091_ds1_START  (5)
#define SOC_IOC_IOCG_091_iocg_091_ds1_END    (5)
#define SOC_IOC_IOCG_091_iocg_091_ds2_START  (6)
#define SOC_IOC_IOCG_091_iocg_091_ds2_END    (6)
#define SOC_IOC_IOCG_091_iocg_091_sr_START   (7)
#define SOC_IOC_IOCG_091_iocg_091_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_092_UNION
 结构说明  : IOCG_092 寄存器结构定义。地址偏移量:0x970，初值:0x00000012，宽度:32
 寄存器说明: ISM_PRIORITY功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_092_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_092_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_092_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_092_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_092_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_092_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_092_UNION;
#endif
#define SOC_IOC_IOCG_092_iocg_092_pu_START   (0)
#define SOC_IOC_IOCG_092_iocg_092_pu_END     (0)
#define SOC_IOC_IOCG_092_iocg_092_pd_START   (1)
#define SOC_IOC_IOCG_092_iocg_092_pd_END     (1)
#define SOC_IOC_IOCG_092_iocg_092_ds0_START  (4)
#define SOC_IOC_IOCG_092_iocg_092_ds0_END    (4)
#define SOC_IOC_IOCG_092_iocg_092_ds1_START  (5)
#define SOC_IOC_IOCG_092_iocg_092_ds1_END    (5)
#define SOC_IOC_IOCG_092_iocg_092_ds2_START  (6)
#define SOC_IOC_IOCG_092_iocg_092_ds2_END    (6)
#define SOC_IOC_IOCG_092_iocg_092_sr_START   (7)
#define SOC_IOC_IOCG_092_iocg_092_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_093_UNION
 结构说明  : IOCG_093 寄存器结构定义。地址偏移量:0x974，初值:0x00000012，宽度:32
 寄存器说明: CH0_AFC_PDM功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_093_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_093_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_093_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_093_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_093_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_093_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_093_UNION;
#endif
#define SOC_IOC_IOCG_093_iocg_093_pu_START   (0)
#define SOC_IOC_IOCG_093_iocg_093_pu_END     (0)
#define SOC_IOC_IOCG_093_iocg_093_pd_START   (1)
#define SOC_IOC_IOCG_093_iocg_093_pd_END     (1)
#define SOC_IOC_IOCG_093_iocg_093_ds0_START  (4)
#define SOC_IOC_IOCG_093_iocg_093_ds0_END    (4)
#define SOC_IOC_IOCG_093_iocg_093_ds1_START  (5)
#define SOC_IOC_IOCG_093_iocg_093_ds1_END    (5)
#define SOC_IOC_IOCG_093_iocg_093_ds2_START  (6)
#define SOC_IOC_IOCG_093_iocg_093_ds2_END    (6)
#define SOC_IOC_IOCG_093_iocg_093_sr_START   (7)
#define SOC_IOC_IOCG_093_iocg_093_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_094_UNION
 结构说明  : IOCG_094 寄存器结构定义。地址偏移量:0x978，初值:0x00000012，宽度:32
 寄存器说明: CH0_APT_PDM功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_094_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_094_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_094_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_094_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_094_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_094_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_094_UNION;
#endif
#define SOC_IOC_IOCG_094_iocg_094_pu_START   (0)
#define SOC_IOC_IOCG_094_iocg_094_pu_END     (0)
#define SOC_IOC_IOCG_094_iocg_094_pd_START   (1)
#define SOC_IOC_IOCG_094_iocg_094_pd_END     (1)
#define SOC_IOC_IOCG_094_iocg_094_ds0_START  (4)
#define SOC_IOC_IOCG_094_iocg_094_ds0_END    (4)
#define SOC_IOC_IOCG_094_iocg_094_ds1_START  (5)
#define SOC_IOC_IOCG_094_iocg_094_ds1_END    (5)
#define SOC_IOC_IOCG_094_iocg_094_ds2_START  (6)
#define SOC_IOC_IOCG_094_iocg_094_ds2_END    (6)
#define SOC_IOC_IOCG_094_iocg_094_sr_START   (7)
#define SOC_IOC_IOCG_094_iocg_094_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_095_UNION
 结构说明  : IOCG_095 寄存器结构定义。地址偏移量:0x97C，初值:0x00000012，宽度:32
 寄存器说明: CH0_RF_RESETN功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_095_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_095_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_095_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_095_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_095_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_095_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_095_UNION;
#endif
#define SOC_IOC_IOCG_095_iocg_095_pu_START   (0)
#define SOC_IOC_IOCG_095_iocg_095_pu_END     (0)
#define SOC_IOC_IOCG_095_iocg_095_pd_START   (1)
#define SOC_IOC_IOCG_095_iocg_095_pd_END     (1)
#define SOC_IOC_IOCG_095_iocg_095_ds0_START  (4)
#define SOC_IOC_IOCG_095_iocg_095_ds0_END    (4)
#define SOC_IOC_IOCG_095_iocg_095_ds1_START  (5)
#define SOC_IOC_IOCG_095_iocg_095_ds1_END    (5)
#define SOC_IOC_IOCG_095_iocg_095_ds2_START  (6)
#define SOC_IOC_IOCG_095_iocg_095_ds2_END    (6)
#define SOC_IOC_IOCG_095_iocg_095_sr_START   (7)
#define SOC_IOC_IOCG_095_iocg_095_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_096_UNION
 结构说明  : IOCG_096 寄存器结构定义。地址偏移量:0x980，初值:0x00000012，宽度:32
 寄存器说明: CH0_RF_SSI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_096_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_096_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_096_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_096_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_096_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_096_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_096_UNION;
#endif
#define SOC_IOC_IOCG_096_iocg_096_pu_START   (0)
#define SOC_IOC_IOCG_096_iocg_096_pu_END     (0)
#define SOC_IOC_IOCG_096_iocg_096_pd_START   (1)
#define SOC_IOC_IOCG_096_iocg_096_pd_END     (1)
#define SOC_IOC_IOCG_096_iocg_096_ds0_START  (4)
#define SOC_IOC_IOCG_096_iocg_096_ds0_END    (4)
#define SOC_IOC_IOCG_096_iocg_096_ds1_START  (5)
#define SOC_IOC_IOCG_096_iocg_096_ds1_END    (5)
#define SOC_IOC_IOCG_096_iocg_096_ds2_START  (6)
#define SOC_IOC_IOCG_096_iocg_096_ds2_END    (6)
#define SOC_IOC_IOCG_096_iocg_096_sr_START   (7)
#define SOC_IOC_IOCG_096_iocg_096_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_097_UNION
 结构说明  : IOCG_097 寄存器结构定义。地址偏移量:0x984，初值:0x00000012，宽度:32
 寄存器说明: CH0_RF_TCVR_ON功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_097_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_097_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_097_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_097_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_097_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_097_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_097_UNION;
#endif
#define SOC_IOC_IOCG_097_iocg_097_pu_START   (0)
#define SOC_IOC_IOCG_097_iocg_097_pu_END     (0)
#define SOC_IOC_IOCG_097_iocg_097_pd_START   (1)
#define SOC_IOC_IOCG_097_iocg_097_pd_END     (1)
#define SOC_IOC_IOCG_097_iocg_097_ds0_START  (4)
#define SOC_IOC_IOCG_097_iocg_097_ds0_END    (4)
#define SOC_IOC_IOCG_097_iocg_097_ds1_START  (5)
#define SOC_IOC_IOCG_097_iocg_097_ds1_END    (5)
#define SOC_IOC_IOCG_097_iocg_097_ds2_START  (6)
#define SOC_IOC_IOCG_097_iocg_097_ds2_END    (6)
#define SOC_IOC_IOCG_097_iocg_097_sr_START   (7)
#define SOC_IOC_IOCG_097_iocg_097_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_098_UNION
 结构说明  : IOCG_098 寄存器结构定义。地址偏移量:0x988，初值:0x00000012，宽度:32
 寄存器说明: CH2_AFC_PDM功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_098_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_098_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_098_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_098_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_098_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_098_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_098_UNION;
#endif
#define SOC_IOC_IOCG_098_iocg_098_pu_START   (0)
#define SOC_IOC_IOCG_098_iocg_098_pu_END     (0)
#define SOC_IOC_IOCG_098_iocg_098_pd_START   (1)
#define SOC_IOC_IOCG_098_iocg_098_pd_END     (1)
#define SOC_IOC_IOCG_098_iocg_098_ds0_START  (4)
#define SOC_IOC_IOCG_098_iocg_098_ds0_END    (4)
#define SOC_IOC_IOCG_098_iocg_098_ds1_START  (5)
#define SOC_IOC_IOCG_098_iocg_098_ds1_END    (5)
#define SOC_IOC_IOCG_098_iocg_098_ds2_START  (6)
#define SOC_IOC_IOCG_098_iocg_098_ds2_END    (6)
#define SOC_IOC_IOCG_098_iocg_098_sr_START   (7)
#define SOC_IOC_IOCG_098_iocg_098_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_099_UNION
 结构说明  : IOCG_099 寄存器结构定义。地址偏移量:0x98C，初值:0x00000012，宽度:32
 寄存器说明: CH1_APT_PDM功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_099_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_099_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_099_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_099_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_099_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_099_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_099_UNION;
#endif
#define SOC_IOC_IOCG_099_iocg_099_pu_START   (0)
#define SOC_IOC_IOCG_099_iocg_099_pu_END     (0)
#define SOC_IOC_IOCG_099_iocg_099_pd_START   (1)
#define SOC_IOC_IOCG_099_iocg_099_pd_END     (1)
#define SOC_IOC_IOCG_099_iocg_099_ds0_START  (4)
#define SOC_IOC_IOCG_099_iocg_099_ds0_END    (4)
#define SOC_IOC_IOCG_099_iocg_099_ds1_START  (5)
#define SOC_IOC_IOCG_099_iocg_099_ds1_END    (5)
#define SOC_IOC_IOCG_099_iocg_099_ds2_START  (6)
#define SOC_IOC_IOCG_099_iocg_099_ds2_END    (6)
#define SOC_IOC_IOCG_099_iocg_099_sr_START   (7)
#define SOC_IOC_IOCG_099_iocg_099_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_100_UNION
 结构说明  : IOCG_100 寄存器结构定义。地址偏移量:0x990，初值:0x00000012，宽度:32
 寄存器说明: CH1_RF_RESETN功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_100_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_100_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_100_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_100_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_100_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_100_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_100_UNION;
#endif
#define SOC_IOC_IOCG_100_iocg_100_pu_START   (0)
#define SOC_IOC_IOCG_100_iocg_100_pu_END     (0)
#define SOC_IOC_IOCG_100_iocg_100_pd_START   (1)
#define SOC_IOC_IOCG_100_iocg_100_pd_END     (1)
#define SOC_IOC_IOCG_100_iocg_100_ds0_START  (4)
#define SOC_IOC_IOCG_100_iocg_100_ds0_END    (4)
#define SOC_IOC_IOCG_100_iocg_100_ds1_START  (5)
#define SOC_IOC_IOCG_100_iocg_100_ds1_END    (5)
#define SOC_IOC_IOCG_100_iocg_100_ds2_START  (6)
#define SOC_IOC_IOCG_100_iocg_100_ds2_END    (6)
#define SOC_IOC_IOCG_100_iocg_100_sr_START   (7)
#define SOC_IOC_IOCG_100_iocg_100_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_101_UNION
 结构说明  : IOCG_101 寄存器结构定义。地址偏移量:0x994，初值:0x00000012，宽度:32
 寄存器说明: CH1_RF_SSI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_101_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_101_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_101_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_101_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_101_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_101_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_101_UNION;
#endif
#define SOC_IOC_IOCG_101_iocg_101_pu_START   (0)
#define SOC_IOC_IOCG_101_iocg_101_pu_END     (0)
#define SOC_IOC_IOCG_101_iocg_101_pd_START   (1)
#define SOC_IOC_IOCG_101_iocg_101_pd_END     (1)
#define SOC_IOC_IOCG_101_iocg_101_ds0_START  (4)
#define SOC_IOC_IOCG_101_iocg_101_ds0_END    (4)
#define SOC_IOC_IOCG_101_iocg_101_ds1_START  (5)
#define SOC_IOC_IOCG_101_iocg_101_ds1_END    (5)
#define SOC_IOC_IOCG_101_iocg_101_ds2_START  (6)
#define SOC_IOC_IOCG_101_iocg_101_ds2_END    (6)
#define SOC_IOC_IOCG_101_iocg_101_sr_START   (7)
#define SOC_IOC_IOCG_101_iocg_101_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_102_UNION
 结构说明  : IOCG_102 寄存器结构定义。地址偏移量:0x998，初值:0x00000012，宽度:32
 寄存器说明: CH1_RF_TCVR_ON功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_102_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_102_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_102_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_102_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_102_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_102_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_102_UNION;
#endif
#define SOC_IOC_IOCG_102_iocg_102_pu_START   (0)
#define SOC_IOC_IOCG_102_iocg_102_pu_END     (0)
#define SOC_IOC_IOCG_102_iocg_102_pd_START   (1)
#define SOC_IOC_IOCG_102_iocg_102_pd_END     (1)
#define SOC_IOC_IOCG_102_iocg_102_ds0_START  (4)
#define SOC_IOC_IOCG_102_iocg_102_ds0_END    (4)
#define SOC_IOC_IOCG_102_iocg_102_ds1_START  (5)
#define SOC_IOC_IOCG_102_iocg_102_ds1_END    (5)
#define SOC_IOC_IOCG_102_iocg_102_ds2_START  (6)
#define SOC_IOC_IOCG_102_iocg_102_ds2_END    (6)
#define SOC_IOC_IOCG_102_iocg_102_sr_START   (7)
#define SOC_IOC_IOCG_102_iocg_102_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_103_UNION
 结构说明  : IOCG_103 寄存器结构定义。地址偏移量:0x99C，初值:0x00000012，宽度:32
 寄存器说明: CH2_RF_RESETN功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_103_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_103_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_103_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_103_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_103_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_103_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_103_UNION;
#endif
#define SOC_IOC_IOCG_103_iocg_103_pu_START   (0)
#define SOC_IOC_IOCG_103_iocg_103_pu_END     (0)
#define SOC_IOC_IOCG_103_iocg_103_pd_START   (1)
#define SOC_IOC_IOCG_103_iocg_103_pd_END     (1)
#define SOC_IOC_IOCG_103_iocg_103_ds0_START  (4)
#define SOC_IOC_IOCG_103_iocg_103_ds0_END    (4)
#define SOC_IOC_IOCG_103_iocg_103_ds1_START  (5)
#define SOC_IOC_IOCG_103_iocg_103_ds1_END    (5)
#define SOC_IOC_IOCG_103_iocg_103_ds2_START  (6)
#define SOC_IOC_IOCG_103_iocg_103_ds2_END    (6)
#define SOC_IOC_IOCG_103_iocg_103_sr_START   (7)
#define SOC_IOC_IOCG_103_iocg_103_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_104_UNION
 结构说明  : IOCG_104 寄存器结构定义。地址偏移量:0x9A0，初值:0x00000012，宽度:32
 寄存器说明: CH2_RF_SSI功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_104_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_104_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_104_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_104_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_104_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_104_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_104_UNION;
#endif
#define SOC_IOC_IOCG_104_iocg_104_pu_START   (0)
#define SOC_IOC_IOCG_104_iocg_104_pu_END     (0)
#define SOC_IOC_IOCG_104_iocg_104_pd_START   (1)
#define SOC_IOC_IOCG_104_iocg_104_pd_END     (1)
#define SOC_IOC_IOCG_104_iocg_104_ds0_START  (4)
#define SOC_IOC_IOCG_104_iocg_104_ds0_END    (4)
#define SOC_IOC_IOCG_104_iocg_104_ds1_START  (5)
#define SOC_IOC_IOCG_104_iocg_104_ds1_END    (5)
#define SOC_IOC_IOCG_104_iocg_104_ds2_START  (6)
#define SOC_IOC_IOCG_104_iocg_104_ds2_END    (6)
#define SOC_IOC_IOCG_104_iocg_104_sr_START   (7)
#define SOC_IOC_IOCG_104_iocg_104_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_105_UNION
 结构说明  : IOCG_105 寄存器结构定义。地址偏移量:0x9A4，初值:0x00000012，宽度:32
 寄存器说明: CH2_RF_TCVR_ON功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_105_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_105_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_105_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_105_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_105_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_105_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_105_UNION;
#endif
#define SOC_IOC_IOCG_105_iocg_105_pu_START   (0)
#define SOC_IOC_IOCG_105_iocg_105_pu_END     (0)
#define SOC_IOC_IOCG_105_iocg_105_pd_START   (1)
#define SOC_IOC_IOCG_105_iocg_105_pd_END     (1)
#define SOC_IOC_IOCG_105_iocg_105_ds0_START  (4)
#define SOC_IOC_IOCG_105_iocg_105_ds0_END    (4)
#define SOC_IOC_IOCG_105_iocg_105_ds1_START  (5)
#define SOC_IOC_IOCG_105_iocg_105_ds1_END    (5)
#define SOC_IOC_IOCG_105_iocg_105_ds2_START  (6)
#define SOC_IOC_IOCG_105_iocg_105_ds2_END    (6)
#define SOC_IOC_IOCG_105_iocg_105_sr_START   (7)
#define SOC_IOC_IOCG_105_iocg_105_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_106_UNION
 结构说明  : IOCG_106 寄存器结构定义。地址偏移量:0x9A8，初值:0x00000012，宽度:32
 寄存器说明: FE0_MIPI_CLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_106_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_106_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_106_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_106_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_106_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_106_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_106_UNION;
#endif
#define SOC_IOC_IOCG_106_iocg_106_pu_START   (0)
#define SOC_IOC_IOCG_106_iocg_106_pu_END     (0)
#define SOC_IOC_IOCG_106_iocg_106_pd_START   (1)
#define SOC_IOC_IOCG_106_iocg_106_pd_END     (1)
#define SOC_IOC_IOCG_106_iocg_106_ds0_START  (4)
#define SOC_IOC_IOCG_106_iocg_106_ds0_END    (4)
#define SOC_IOC_IOCG_106_iocg_106_ds1_START  (5)
#define SOC_IOC_IOCG_106_iocg_106_ds1_END    (5)
#define SOC_IOC_IOCG_106_iocg_106_ds2_START  (6)
#define SOC_IOC_IOCG_106_iocg_106_ds2_END    (6)
#define SOC_IOC_IOCG_106_iocg_106_sr_START   (7)
#define SOC_IOC_IOCG_106_iocg_106_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_107_UNION
 结构说明  : IOCG_107 寄存器结构定义。地址偏移量:0x9AC，初值:0x00000012，宽度:32
 寄存器说明: FE0_MIPI_DATA功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_107_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_107_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_107_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_107_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_107_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_107_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_107_UNION;
#endif
#define SOC_IOC_IOCG_107_iocg_107_pu_START   (0)
#define SOC_IOC_IOCG_107_iocg_107_pu_END     (0)
#define SOC_IOC_IOCG_107_iocg_107_pd_START   (1)
#define SOC_IOC_IOCG_107_iocg_107_pd_END     (1)
#define SOC_IOC_IOCG_107_iocg_107_ds0_START  (4)
#define SOC_IOC_IOCG_107_iocg_107_ds0_END    (4)
#define SOC_IOC_IOCG_107_iocg_107_ds1_START  (5)
#define SOC_IOC_IOCG_107_iocg_107_ds1_END    (5)
#define SOC_IOC_IOCG_107_iocg_107_ds2_START  (6)
#define SOC_IOC_IOCG_107_iocg_107_ds2_END    (6)
#define SOC_IOC_IOCG_107_iocg_107_sr_START   (7)
#define SOC_IOC_IOCG_107_iocg_107_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_108_UNION
 结构说明  : IOCG_108 寄存器结构定义。地址偏移量:0x9B0，初值:0x00000012，宽度:32
 寄存器说明: FE1_MIPI_CLK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_108_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_108_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_108_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_108_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_108_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_108_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_108_UNION;
#endif
#define SOC_IOC_IOCG_108_iocg_108_pu_START   (0)
#define SOC_IOC_IOCG_108_iocg_108_pu_END     (0)
#define SOC_IOC_IOCG_108_iocg_108_pd_START   (1)
#define SOC_IOC_IOCG_108_iocg_108_pd_END     (1)
#define SOC_IOC_IOCG_108_iocg_108_ds0_START  (4)
#define SOC_IOC_IOCG_108_iocg_108_ds0_END    (4)
#define SOC_IOC_IOCG_108_iocg_108_ds1_START  (5)
#define SOC_IOC_IOCG_108_iocg_108_ds1_END    (5)
#define SOC_IOC_IOCG_108_iocg_108_ds2_START  (6)
#define SOC_IOC_IOCG_108_iocg_108_ds2_END    (6)
#define SOC_IOC_IOCG_108_iocg_108_sr_START   (7)
#define SOC_IOC_IOCG_108_iocg_108_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_109_UNION
 结构说明  : IOCG_109 寄存器结构定义。地址偏移量:0x9B4，初值:0x00000012，宽度:32
 寄存器说明: FE1_MIPI_DATA功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_109_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_109_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_109_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_109_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_109_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_109_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_109_UNION;
#endif
#define SOC_IOC_IOCG_109_iocg_109_pu_START   (0)
#define SOC_IOC_IOCG_109_iocg_109_pu_END     (0)
#define SOC_IOC_IOCG_109_iocg_109_pd_START   (1)
#define SOC_IOC_IOCG_109_iocg_109_pd_END     (1)
#define SOC_IOC_IOCG_109_iocg_109_ds0_START  (4)
#define SOC_IOC_IOCG_109_iocg_109_ds0_END    (4)
#define SOC_IOC_IOCG_109_iocg_109_ds1_START  (5)
#define SOC_IOC_IOCG_109_iocg_109_ds1_END    (5)
#define SOC_IOC_IOCG_109_iocg_109_ds2_START  (6)
#define SOC_IOC_IOCG_109_iocg_109_ds2_END    (6)
#define SOC_IOC_IOCG_109_iocg_109_sr_START   (7)
#define SOC_IOC_IOCG_109_iocg_109_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_110_UNION
 结构说明  : IOCG_110 寄存器结构定义。地址偏移量:0x9B8，初值:0x00000012，宽度:32
 寄存器说明: FLASH_MASK功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_110_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_110_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_110_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_110_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_110_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_110_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_110_UNION;
#endif
#define SOC_IOC_IOCG_110_iocg_110_pu_START   (0)
#define SOC_IOC_IOCG_110_iocg_110_pu_END     (0)
#define SOC_IOC_IOCG_110_iocg_110_pd_START   (1)
#define SOC_IOC_IOCG_110_iocg_110_pd_END     (1)
#define SOC_IOC_IOCG_110_iocg_110_ds0_START  (4)
#define SOC_IOC_IOCG_110_iocg_110_ds0_END    (4)
#define SOC_IOC_IOCG_110_iocg_110_ds1_START  (5)
#define SOC_IOC_IOCG_110_iocg_110_ds1_END    (5)
#define SOC_IOC_IOCG_110_iocg_110_ds2_START  (6)
#define SOC_IOC_IOCG_110_iocg_110_ds2_END    (6)
#define SOC_IOC_IOCG_110_iocg_110_sr_START   (7)
#define SOC_IOC_IOCG_110_iocg_110_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_111_UNION
 结构说明  : IOCG_111 寄存器结构定义。地址偏移量:0x9BC，初值:0x00000012，宽度:32
 寄存器说明: GPS_BLANKING功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_111_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_111_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_111_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_111_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_111_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_111_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_111_UNION;
#endif
#define SOC_IOC_IOCG_111_iocg_111_pu_START   (0)
#define SOC_IOC_IOCG_111_iocg_111_pu_END     (0)
#define SOC_IOC_IOCG_111_iocg_111_pd_START   (1)
#define SOC_IOC_IOCG_111_iocg_111_pd_END     (1)
#define SOC_IOC_IOCG_111_iocg_111_ds0_START  (4)
#define SOC_IOC_IOCG_111_iocg_111_ds0_END    (4)
#define SOC_IOC_IOCG_111_iocg_111_ds1_START  (5)
#define SOC_IOC_IOCG_111_iocg_111_ds1_END    (5)
#define SOC_IOC_IOCG_111_iocg_111_ds2_START  (6)
#define SOC_IOC_IOCG_111_iocg_111_ds2_END    (6)
#define SOC_IOC_IOCG_111_iocg_111_sr_START   (7)
#define SOC_IOC_IOCG_111_iocg_111_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_112_UNION
 结构说明  : IOCG_112 寄存器结构定义。地址偏移量:0x9C0，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL00功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_112_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_112_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_112_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_112_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_112_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_112_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_112_UNION;
#endif
#define SOC_IOC_IOCG_112_iocg_112_pu_START   (0)
#define SOC_IOC_IOCG_112_iocg_112_pu_END     (0)
#define SOC_IOC_IOCG_112_iocg_112_pd_START   (1)
#define SOC_IOC_IOCG_112_iocg_112_pd_END     (1)
#define SOC_IOC_IOCG_112_iocg_112_ds0_START  (4)
#define SOC_IOC_IOCG_112_iocg_112_ds0_END    (4)
#define SOC_IOC_IOCG_112_iocg_112_ds1_START  (5)
#define SOC_IOC_IOCG_112_iocg_112_ds1_END    (5)
#define SOC_IOC_IOCG_112_iocg_112_ds2_START  (6)
#define SOC_IOC_IOCG_112_iocg_112_ds2_END    (6)
#define SOC_IOC_IOCG_112_iocg_112_sr_START   (7)
#define SOC_IOC_IOCG_112_iocg_112_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_113_UNION
 结构说明  : IOCG_113 寄存器结构定义。地址偏移量:0x9C4，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL01功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_113_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_113_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_113_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_113_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_113_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_113_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_113_UNION;
#endif
#define SOC_IOC_IOCG_113_iocg_113_pu_START   (0)
#define SOC_IOC_IOCG_113_iocg_113_pu_END     (0)
#define SOC_IOC_IOCG_113_iocg_113_pd_START   (1)
#define SOC_IOC_IOCG_113_iocg_113_pd_END     (1)
#define SOC_IOC_IOCG_113_iocg_113_ds0_START  (4)
#define SOC_IOC_IOCG_113_iocg_113_ds0_END    (4)
#define SOC_IOC_IOCG_113_iocg_113_ds1_START  (5)
#define SOC_IOC_IOCG_113_iocg_113_ds1_END    (5)
#define SOC_IOC_IOCG_113_iocg_113_ds2_START  (6)
#define SOC_IOC_IOCG_113_iocg_113_ds2_END    (6)
#define SOC_IOC_IOCG_113_iocg_113_sr_START   (7)
#define SOC_IOC_IOCG_113_iocg_113_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_114_UNION
 结构说明  : IOCG_114 寄存器结构定义。地址偏移量:0x9C8，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL02功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_114_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_114_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_114_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_114_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_114_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_114_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_114_UNION;
#endif
#define SOC_IOC_IOCG_114_iocg_114_pu_START   (0)
#define SOC_IOC_IOCG_114_iocg_114_pu_END     (0)
#define SOC_IOC_IOCG_114_iocg_114_pd_START   (1)
#define SOC_IOC_IOCG_114_iocg_114_pd_END     (1)
#define SOC_IOC_IOCG_114_iocg_114_ds0_START  (4)
#define SOC_IOC_IOCG_114_iocg_114_ds0_END    (4)
#define SOC_IOC_IOCG_114_iocg_114_ds1_START  (5)
#define SOC_IOC_IOCG_114_iocg_114_ds1_END    (5)
#define SOC_IOC_IOCG_114_iocg_114_ds2_START  (6)
#define SOC_IOC_IOCG_114_iocg_114_ds2_END    (6)
#define SOC_IOC_IOCG_114_iocg_114_sr_START   (7)
#define SOC_IOC_IOCG_114_iocg_114_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_115_UNION
 结构说明  : IOCG_115 寄存器结构定义。地址偏移量:0x9CC，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL03功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_115_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_115_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_115_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_115_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_115_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_115_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_115_UNION;
#endif
#define SOC_IOC_IOCG_115_iocg_115_pu_START   (0)
#define SOC_IOC_IOCG_115_iocg_115_pu_END     (0)
#define SOC_IOC_IOCG_115_iocg_115_pd_START   (1)
#define SOC_IOC_IOCG_115_iocg_115_pd_END     (1)
#define SOC_IOC_IOCG_115_iocg_115_ds0_START  (4)
#define SOC_IOC_IOCG_115_iocg_115_ds0_END    (4)
#define SOC_IOC_IOCG_115_iocg_115_ds1_START  (5)
#define SOC_IOC_IOCG_115_iocg_115_ds1_END    (5)
#define SOC_IOC_IOCG_115_iocg_115_ds2_START  (6)
#define SOC_IOC_IOCG_115_iocg_115_ds2_END    (6)
#define SOC_IOC_IOCG_115_iocg_115_sr_START   (7)
#define SOC_IOC_IOCG_115_iocg_115_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_116_UNION
 结构说明  : IOCG_116 寄存器结构定义。地址偏移量:0x9D0，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL04功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_116_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_116_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_116_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_116_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_116_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_116_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_116_UNION;
#endif
#define SOC_IOC_IOCG_116_iocg_116_pu_START   (0)
#define SOC_IOC_IOCG_116_iocg_116_pu_END     (0)
#define SOC_IOC_IOCG_116_iocg_116_pd_START   (1)
#define SOC_IOC_IOCG_116_iocg_116_pd_END     (1)
#define SOC_IOC_IOCG_116_iocg_116_ds0_START  (4)
#define SOC_IOC_IOCG_116_iocg_116_ds0_END    (4)
#define SOC_IOC_IOCG_116_iocg_116_ds1_START  (5)
#define SOC_IOC_IOCG_116_iocg_116_ds1_END    (5)
#define SOC_IOC_IOCG_116_iocg_116_ds2_START  (6)
#define SOC_IOC_IOCG_116_iocg_116_ds2_END    (6)
#define SOC_IOC_IOCG_116_iocg_116_sr_START   (7)
#define SOC_IOC_IOCG_116_iocg_116_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_117_UNION
 结构说明  : IOCG_117 寄存器结构定义。地址偏移量:0x9D4，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL05功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_117_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_117_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_117_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_117_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_117_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_117_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_117_UNION;
#endif
#define SOC_IOC_IOCG_117_iocg_117_pu_START   (0)
#define SOC_IOC_IOCG_117_iocg_117_pu_END     (0)
#define SOC_IOC_IOCG_117_iocg_117_pd_START   (1)
#define SOC_IOC_IOCG_117_iocg_117_pd_END     (1)
#define SOC_IOC_IOCG_117_iocg_117_ds0_START  (4)
#define SOC_IOC_IOCG_117_iocg_117_ds0_END    (4)
#define SOC_IOC_IOCG_117_iocg_117_ds1_START  (5)
#define SOC_IOC_IOCG_117_iocg_117_ds1_END    (5)
#define SOC_IOC_IOCG_117_iocg_117_ds2_START  (6)
#define SOC_IOC_IOCG_117_iocg_117_ds2_END    (6)
#define SOC_IOC_IOCG_117_iocg_117_sr_START   (7)
#define SOC_IOC_IOCG_117_iocg_117_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_118_UNION
 结构说明  : IOCG_118 寄存器结构定义。地址偏移量:0x9D8，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL06功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_118_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_118_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_118_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_118_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_118_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_118_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_118_UNION;
#endif
#define SOC_IOC_IOCG_118_iocg_118_pu_START   (0)
#define SOC_IOC_IOCG_118_iocg_118_pu_END     (0)
#define SOC_IOC_IOCG_118_iocg_118_pd_START   (1)
#define SOC_IOC_IOCG_118_iocg_118_pd_END     (1)
#define SOC_IOC_IOCG_118_iocg_118_ds0_START  (4)
#define SOC_IOC_IOCG_118_iocg_118_ds0_END    (4)
#define SOC_IOC_IOCG_118_iocg_118_ds1_START  (5)
#define SOC_IOC_IOCG_118_iocg_118_ds1_END    (5)
#define SOC_IOC_IOCG_118_iocg_118_ds2_START  (6)
#define SOC_IOC_IOCG_118_iocg_118_ds2_END    (6)
#define SOC_IOC_IOCG_118_iocg_118_sr_START   (7)
#define SOC_IOC_IOCG_118_iocg_118_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_119_UNION
 结构说明  : IOCG_119 寄存器结构定义。地址偏移量:0x9DC，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL07功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_119_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_119_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_119_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_119_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_119_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_119_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_119_UNION;
#endif
#define SOC_IOC_IOCG_119_iocg_119_pu_START   (0)
#define SOC_IOC_IOCG_119_iocg_119_pu_END     (0)
#define SOC_IOC_IOCG_119_iocg_119_pd_START   (1)
#define SOC_IOC_IOCG_119_iocg_119_pd_END     (1)
#define SOC_IOC_IOCG_119_iocg_119_ds0_START  (4)
#define SOC_IOC_IOCG_119_iocg_119_ds0_END    (4)
#define SOC_IOC_IOCG_119_iocg_119_ds1_START  (5)
#define SOC_IOC_IOCG_119_iocg_119_ds1_END    (5)
#define SOC_IOC_IOCG_119_iocg_119_ds2_START  (6)
#define SOC_IOC_IOCG_119_iocg_119_ds2_END    (6)
#define SOC_IOC_IOCG_119_iocg_119_sr_START   (7)
#define SOC_IOC_IOCG_119_iocg_119_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_120_UNION
 结构说明  : IOCG_120 寄存器结构定义。地址偏移量:0x9E0，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL08功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_120_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_120_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_120_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_120_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_120_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_120_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_120_UNION;
#endif
#define SOC_IOC_IOCG_120_iocg_120_pu_START   (0)
#define SOC_IOC_IOCG_120_iocg_120_pu_END     (0)
#define SOC_IOC_IOCG_120_iocg_120_pd_START   (1)
#define SOC_IOC_IOCG_120_iocg_120_pd_END     (1)
#define SOC_IOC_IOCG_120_iocg_120_ds0_START  (4)
#define SOC_IOC_IOCG_120_iocg_120_ds0_END    (4)
#define SOC_IOC_IOCG_120_iocg_120_ds1_START  (5)
#define SOC_IOC_IOCG_120_iocg_120_ds1_END    (5)
#define SOC_IOC_IOCG_120_iocg_120_ds2_START  (6)
#define SOC_IOC_IOCG_120_iocg_120_ds2_END    (6)
#define SOC_IOC_IOCG_120_iocg_120_sr_START   (7)
#define SOC_IOC_IOCG_120_iocg_120_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_121_UNION
 结构说明  : IOCG_121 寄存器结构定义。地址偏移量:0x9E4，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL09功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_121_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_121_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_121_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_121_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_121_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_121_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_121_UNION;
#endif
#define SOC_IOC_IOCG_121_iocg_121_pu_START   (0)
#define SOC_IOC_IOCG_121_iocg_121_pu_END     (0)
#define SOC_IOC_IOCG_121_iocg_121_pd_START   (1)
#define SOC_IOC_IOCG_121_iocg_121_pd_END     (1)
#define SOC_IOC_IOCG_121_iocg_121_ds0_START  (4)
#define SOC_IOC_IOCG_121_iocg_121_ds0_END    (4)
#define SOC_IOC_IOCG_121_iocg_121_ds1_START  (5)
#define SOC_IOC_IOCG_121_iocg_121_ds1_END    (5)
#define SOC_IOC_IOCG_121_iocg_121_ds2_START  (6)
#define SOC_IOC_IOCG_121_iocg_121_ds2_END    (6)
#define SOC_IOC_IOCG_121_iocg_121_sr_START   (7)
#define SOC_IOC_IOCG_121_iocg_121_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_122_UNION
 结构说明  : IOCG_122 寄存器结构定义。地址偏移量:0x9E8，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL10功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_122_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_122_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_122_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_122_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_122_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_122_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_122_UNION;
#endif
#define SOC_IOC_IOCG_122_iocg_122_pu_START   (0)
#define SOC_IOC_IOCG_122_iocg_122_pu_END     (0)
#define SOC_IOC_IOCG_122_iocg_122_pd_START   (1)
#define SOC_IOC_IOCG_122_iocg_122_pd_END     (1)
#define SOC_IOC_IOCG_122_iocg_122_ds0_START  (4)
#define SOC_IOC_IOCG_122_iocg_122_ds0_END    (4)
#define SOC_IOC_IOCG_122_iocg_122_ds1_START  (5)
#define SOC_IOC_IOCG_122_iocg_122_ds1_END    (5)
#define SOC_IOC_IOCG_122_iocg_122_ds2_START  (6)
#define SOC_IOC_IOCG_122_iocg_122_ds2_END    (6)
#define SOC_IOC_IOCG_122_iocg_122_sr_START   (7)
#define SOC_IOC_IOCG_122_iocg_122_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_123_UNION
 结构说明  : IOCG_123 寄存器结构定义。地址偏移量:0x9EC，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL11功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_123_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_123_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_123_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_123_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_123_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_123_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_123_UNION;
#endif
#define SOC_IOC_IOCG_123_iocg_123_pu_START   (0)
#define SOC_IOC_IOCG_123_iocg_123_pu_END     (0)
#define SOC_IOC_IOCG_123_iocg_123_pd_START   (1)
#define SOC_IOC_IOCG_123_iocg_123_pd_END     (1)
#define SOC_IOC_IOCG_123_iocg_123_ds0_START  (4)
#define SOC_IOC_IOCG_123_iocg_123_ds0_END    (4)
#define SOC_IOC_IOCG_123_iocg_123_ds1_START  (5)
#define SOC_IOC_IOCG_123_iocg_123_ds1_END    (5)
#define SOC_IOC_IOCG_123_iocg_123_ds2_START  (6)
#define SOC_IOC_IOCG_123_iocg_123_ds2_END    (6)
#define SOC_IOC_IOCG_123_iocg_123_sr_START   (7)
#define SOC_IOC_IOCG_123_iocg_123_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_124_UNION
 结构说明  : IOCG_124 寄存器结构定义。地址偏移量:0x9F0，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL12功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_124_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_124_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_124_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_124_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_124_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_124_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_124_UNION;
#endif
#define SOC_IOC_IOCG_124_iocg_124_pu_START   (0)
#define SOC_IOC_IOCG_124_iocg_124_pu_END     (0)
#define SOC_IOC_IOCG_124_iocg_124_pd_START   (1)
#define SOC_IOC_IOCG_124_iocg_124_pd_END     (1)
#define SOC_IOC_IOCG_124_iocg_124_ds0_START  (4)
#define SOC_IOC_IOCG_124_iocg_124_ds0_END    (4)
#define SOC_IOC_IOCG_124_iocg_124_ds1_START  (5)
#define SOC_IOC_IOCG_124_iocg_124_ds1_END    (5)
#define SOC_IOC_IOCG_124_iocg_124_ds2_START  (6)
#define SOC_IOC_IOCG_124_iocg_124_ds2_END    (6)
#define SOC_IOC_IOCG_124_iocg_124_sr_START   (7)
#define SOC_IOC_IOCG_124_iocg_124_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_125_UNION
 结构说明  : IOCG_125 寄存器结构定义。地址偏移量:0x9F4，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL13功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_125_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_125_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_125_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_125_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_125_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_125_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_125_UNION;
#endif
#define SOC_IOC_IOCG_125_iocg_125_pu_START   (0)
#define SOC_IOC_IOCG_125_iocg_125_pu_END     (0)
#define SOC_IOC_IOCG_125_iocg_125_pd_START   (1)
#define SOC_IOC_IOCG_125_iocg_125_pd_END     (1)
#define SOC_IOC_IOCG_125_iocg_125_ds0_START  (4)
#define SOC_IOC_IOCG_125_iocg_125_ds0_END    (4)
#define SOC_IOC_IOCG_125_iocg_125_ds1_START  (5)
#define SOC_IOC_IOCG_125_iocg_125_ds1_END    (5)
#define SOC_IOC_IOCG_125_iocg_125_ds2_START  (6)
#define SOC_IOC_IOCG_125_iocg_125_ds2_END    (6)
#define SOC_IOC_IOCG_125_iocg_125_sr_START   (7)
#define SOC_IOC_IOCG_125_iocg_125_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_126_UNION
 结构说明  : IOCG_126 寄存器结构定义。地址偏移量:0x9F8，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL14功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_126_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_126_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_126_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_126_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_126_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_126_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_126_UNION;
#endif
#define SOC_IOC_IOCG_126_iocg_126_pu_START   (0)
#define SOC_IOC_IOCG_126_iocg_126_pu_END     (0)
#define SOC_IOC_IOCG_126_iocg_126_pd_START   (1)
#define SOC_IOC_IOCG_126_iocg_126_pd_END     (1)
#define SOC_IOC_IOCG_126_iocg_126_ds0_START  (4)
#define SOC_IOC_IOCG_126_iocg_126_ds0_END    (4)
#define SOC_IOC_IOCG_126_iocg_126_ds1_START  (5)
#define SOC_IOC_IOCG_126_iocg_126_ds1_END    (5)
#define SOC_IOC_IOCG_126_iocg_126_ds2_START  (6)
#define SOC_IOC_IOCG_126_iocg_126_ds2_END    (6)
#define SOC_IOC_IOCG_126_iocg_126_sr_START   (7)
#define SOC_IOC_IOCG_126_iocg_126_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_127_UNION
 结构说明  : IOCG_127 寄存器结构定义。地址偏移量:0x9FC，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL15功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_127_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_127_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_127_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_127_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_127_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_127_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_127_UNION;
#endif
#define SOC_IOC_IOCG_127_iocg_127_pu_START   (0)
#define SOC_IOC_IOCG_127_iocg_127_pu_END     (0)
#define SOC_IOC_IOCG_127_iocg_127_pd_START   (1)
#define SOC_IOC_IOCG_127_iocg_127_pd_END     (1)
#define SOC_IOC_IOCG_127_iocg_127_ds0_START  (4)
#define SOC_IOC_IOCG_127_iocg_127_ds0_END    (4)
#define SOC_IOC_IOCG_127_iocg_127_ds1_START  (5)
#define SOC_IOC_IOCG_127_iocg_127_ds1_END    (5)
#define SOC_IOC_IOCG_127_iocg_127_ds2_START  (6)
#define SOC_IOC_IOCG_127_iocg_127_ds2_END    (6)
#define SOC_IOC_IOCG_127_iocg_127_sr_START   (7)
#define SOC_IOC_IOCG_127_iocg_127_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_128_UNION
 结构说明  : IOCG_128 寄存器结构定义。地址偏移量:0xA00，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL16功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_128_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_128_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_128_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_128_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_128_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_128_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_128_UNION;
#endif
#define SOC_IOC_IOCG_128_iocg_128_pu_START   (0)
#define SOC_IOC_IOCG_128_iocg_128_pu_END     (0)
#define SOC_IOC_IOCG_128_iocg_128_pd_START   (1)
#define SOC_IOC_IOCG_128_iocg_128_pd_END     (1)
#define SOC_IOC_IOCG_128_iocg_128_ds0_START  (4)
#define SOC_IOC_IOCG_128_iocg_128_ds0_END    (4)
#define SOC_IOC_IOCG_128_iocg_128_ds1_START  (5)
#define SOC_IOC_IOCG_128_iocg_128_ds1_END    (5)
#define SOC_IOC_IOCG_128_iocg_128_ds2_START  (6)
#define SOC_IOC_IOCG_128_iocg_128_ds2_END    (6)
#define SOC_IOC_IOCG_128_iocg_128_sr_START   (7)
#define SOC_IOC_IOCG_128_iocg_128_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_129_UNION
 结构说明  : IOCG_129 寄存器结构定义。地址偏移量:0xA04，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL17功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_129_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_129_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_129_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_129_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_129_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_129_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_129_UNION;
#endif
#define SOC_IOC_IOCG_129_iocg_129_pu_START   (0)
#define SOC_IOC_IOCG_129_iocg_129_pu_END     (0)
#define SOC_IOC_IOCG_129_iocg_129_pd_START   (1)
#define SOC_IOC_IOCG_129_iocg_129_pd_END     (1)
#define SOC_IOC_IOCG_129_iocg_129_ds0_START  (4)
#define SOC_IOC_IOCG_129_iocg_129_ds0_END    (4)
#define SOC_IOC_IOCG_129_iocg_129_ds1_START  (5)
#define SOC_IOC_IOCG_129_iocg_129_ds1_END    (5)
#define SOC_IOC_IOCG_129_iocg_129_ds2_START  (6)
#define SOC_IOC_IOCG_129_iocg_129_ds2_END    (6)
#define SOC_IOC_IOCG_129_iocg_129_sr_START   (7)
#define SOC_IOC_IOCG_129_iocg_129_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_130_UNION
 结构说明  : IOCG_130 寄存器结构定义。地址偏移量:0xA08，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL18功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_130_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_130_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_130_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_130_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_130_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_130_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_130_UNION;
#endif
#define SOC_IOC_IOCG_130_iocg_130_pu_START   (0)
#define SOC_IOC_IOCG_130_iocg_130_pu_END     (0)
#define SOC_IOC_IOCG_130_iocg_130_pd_START   (1)
#define SOC_IOC_IOCG_130_iocg_130_pd_END     (1)
#define SOC_IOC_IOCG_130_iocg_130_ds0_START  (4)
#define SOC_IOC_IOCG_130_iocg_130_ds0_END    (4)
#define SOC_IOC_IOCG_130_iocg_130_ds1_START  (5)
#define SOC_IOC_IOCG_130_iocg_130_ds1_END    (5)
#define SOC_IOC_IOCG_130_iocg_130_ds2_START  (6)
#define SOC_IOC_IOCG_130_iocg_130_ds2_END    (6)
#define SOC_IOC_IOCG_130_iocg_130_sr_START   (7)
#define SOC_IOC_IOCG_130_iocg_130_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_131_UNION
 结构说明  : IOCG_131 寄存器结构定义。地址偏移量:0xA0C，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL19功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_131_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_131_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_131_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_131_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_131_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_131_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_131_UNION;
#endif
#define SOC_IOC_IOCG_131_iocg_131_pu_START   (0)
#define SOC_IOC_IOCG_131_iocg_131_pu_END     (0)
#define SOC_IOC_IOCG_131_iocg_131_pd_START   (1)
#define SOC_IOC_IOCG_131_iocg_131_pd_END     (1)
#define SOC_IOC_IOCG_131_iocg_131_ds0_START  (4)
#define SOC_IOC_IOCG_131_iocg_131_ds0_END    (4)
#define SOC_IOC_IOCG_131_iocg_131_ds1_START  (5)
#define SOC_IOC_IOCG_131_iocg_131_ds1_END    (5)
#define SOC_IOC_IOCG_131_iocg_131_ds2_START  (6)
#define SOC_IOC_IOCG_131_iocg_131_ds2_END    (6)
#define SOC_IOC_IOCG_131_iocg_131_sr_START   (7)
#define SOC_IOC_IOCG_131_iocg_131_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_132_UNION
 结构说明  : IOCG_132 寄存器结构定义。地址偏移量:0xA10，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL20功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_132_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_132_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_132_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_132_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_132_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_132_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_132_UNION;
#endif
#define SOC_IOC_IOCG_132_iocg_132_pu_START   (0)
#define SOC_IOC_IOCG_132_iocg_132_pu_END     (0)
#define SOC_IOC_IOCG_132_iocg_132_pd_START   (1)
#define SOC_IOC_IOCG_132_iocg_132_pd_END     (1)
#define SOC_IOC_IOCG_132_iocg_132_ds0_START  (4)
#define SOC_IOC_IOCG_132_iocg_132_ds0_END    (4)
#define SOC_IOC_IOCG_132_iocg_132_ds1_START  (5)
#define SOC_IOC_IOCG_132_iocg_132_ds1_END    (5)
#define SOC_IOC_IOCG_132_iocg_132_ds2_START  (6)
#define SOC_IOC_IOCG_132_iocg_132_ds2_END    (6)
#define SOC_IOC_IOCG_132_iocg_132_sr_START   (7)
#define SOC_IOC_IOCG_132_iocg_132_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_133_UNION
 结构说明  : IOCG_133 寄存器结构定义。地址偏移量:0xA14，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL21功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_133_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_133_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_133_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_133_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_133_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_133_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_133_UNION;
#endif
#define SOC_IOC_IOCG_133_iocg_133_pu_START   (0)
#define SOC_IOC_IOCG_133_iocg_133_pu_END     (0)
#define SOC_IOC_IOCG_133_iocg_133_pd_START   (1)
#define SOC_IOC_IOCG_133_iocg_133_pd_END     (1)
#define SOC_IOC_IOCG_133_iocg_133_ds0_START  (4)
#define SOC_IOC_IOCG_133_iocg_133_ds0_END    (4)
#define SOC_IOC_IOCG_133_iocg_133_ds1_START  (5)
#define SOC_IOC_IOCG_133_iocg_133_ds1_END    (5)
#define SOC_IOC_IOCG_133_iocg_133_ds2_START  (6)
#define SOC_IOC_IOCG_133_iocg_133_ds2_END    (6)
#define SOC_IOC_IOCG_133_iocg_133_sr_START   (7)
#define SOC_IOC_IOCG_133_iocg_133_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_134_UNION
 结构说明  : IOCG_134 寄存器结构定义。地址偏移量:0xA18，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL22功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_134_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_134_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_134_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_134_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_134_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_134_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_134_UNION;
#endif
#define SOC_IOC_IOCG_134_iocg_134_pu_START   (0)
#define SOC_IOC_IOCG_134_iocg_134_pu_END     (0)
#define SOC_IOC_IOCG_134_iocg_134_pd_START   (1)
#define SOC_IOC_IOCG_134_iocg_134_pd_END     (1)
#define SOC_IOC_IOCG_134_iocg_134_ds0_START  (4)
#define SOC_IOC_IOCG_134_iocg_134_ds0_END    (4)
#define SOC_IOC_IOCG_134_iocg_134_ds1_START  (5)
#define SOC_IOC_IOCG_134_iocg_134_ds1_END    (5)
#define SOC_IOC_IOCG_134_iocg_134_ds2_START  (6)
#define SOC_IOC_IOCG_134_iocg_134_ds2_END    (6)
#define SOC_IOC_IOCG_134_iocg_134_sr_START   (7)
#define SOC_IOC_IOCG_134_iocg_134_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_135_UNION
 结构说明  : IOCG_135 寄存器结构定义。地址偏移量:0xA1C，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL23功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_135_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_135_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_135_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_135_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_135_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_135_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_135_UNION;
#endif
#define SOC_IOC_IOCG_135_iocg_135_pu_START   (0)
#define SOC_IOC_IOCG_135_iocg_135_pu_END     (0)
#define SOC_IOC_IOCG_135_iocg_135_pd_START   (1)
#define SOC_IOC_IOCG_135_iocg_135_pd_END     (1)
#define SOC_IOC_IOCG_135_iocg_135_ds0_START  (4)
#define SOC_IOC_IOCG_135_iocg_135_ds0_END    (4)
#define SOC_IOC_IOCG_135_iocg_135_ds1_START  (5)
#define SOC_IOC_IOCG_135_iocg_135_ds1_END    (5)
#define SOC_IOC_IOCG_135_iocg_135_ds2_START  (6)
#define SOC_IOC_IOCG_135_iocg_135_ds2_END    (6)
#define SOC_IOC_IOCG_135_iocg_135_sr_START   (7)
#define SOC_IOC_IOCG_135_iocg_135_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_136_UNION
 结构说明  : IOCG_136 寄存器结构定义。地址偏移量:0xA20，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL24功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_136_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_136_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_136_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_136_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_136_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_136_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_136_UNION;
#endif
#define SOC_IOC_IOCG_136_iocg_136_pu_START   (0)
#define SOC_IOC_IOCG_136_iocg_136_pu_END     (0)
#define SOC_IOC_IOCG_136_iocg_136_pd_START   (1)
#define SOC_IOC_IOCG_136_iocg_136_pd_END     (1)
#define SOC_IOC_IOCG_136_iocg_136_ds0_START  (4)
#define SOC_IOC_IOCG_136_iocg_136_ds0_END    (4)
#define SOC_IOC_IOCG_136_iocg_136_ds1_START  (5)
#define SOC_IOC_IOCG_136_iocg_136_ds1_END    (5)
#define SOC_IOC_IOCG_136_iocg_136_ds2_START  (6)
#define SOC_IOC_IOCG_136_iocg_136_ds2_END    (6)
#define SOC_IOC_IOCG_136_iocg_136_sr_START   (7)
#define SOC_IOC_IOCG_136_iocg_136_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_137_UNION
 结构说明  : IOCG_137 寄存器结构定义。地址偏移量:0xA24，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL25功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_137_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_137_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_137_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_137_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_137_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_137_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_137_UNION;
#endif
#define SOC_IOC_IOCG_137_iocg_137_pu_START   (0)
#define SOC_IOC_IOCG_137_iocg_137_pu_END     (0)
#define SOC_IOC_IOCG_137_iocg_137_pd_START   (1)
#define SOC_IOC_IOCG_137_iocg_137_pd_END     (1)
#define SOC_IOC_IOCG_137_iocg_137_ds0_START  (4)
#define SOC_IOC_IOCG_137_iocg_137_ds0_END    (4)
#define SOC_IOC_IOCG_137_iocg_137_ds1_START  (5)
#define SOC_IOC_IOCG_137_iocg_137_ds1_END    (5)
#define SOC_IOC_IOCG_137_iocg_137_ds2_START  (6)
#define SOC_IOC_IOCG_137_iocg_137_ds2_END    (6)
#define SOC_IOC_IOCG_137_iocg_137_sr_START   (7)
#define SOC_IOC_IOCG_137_iocg_137_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_138_UNION
 结构说明  : IOCG_138 寄存器结构定义。地址偏移量:0xA28，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL26功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_138_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_138_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_138_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_138_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_138_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_138_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_138_UNION;
#endif
#define SOC_IOC_IOCG_138_iocg_138_pu_START   (0)
#define SOC_IOC_IOCG_138_iocg_138_pu_END     (0)
#define SOC_IOC_IOCG_138_iocg_138_pd_START   (1)
#define SOC_IOC_IOCG_138_iocg_138_pd_END     (1)
#define SOC_IOC_IOCG_138_iocg_138_ds0_START  (4)
#define SOC_IOC_IOCG_138_iocg_138_ds0_END    (4)
#define SOC_IOC_IOCG_138_iocg_138_ds1_START  (5)
#define SOC_IOC_IOCG_138_iocg_138_ds1_END    (5)
#define SOC_IOC_IOCG_138_iocg_138_ds2_START  (6)
#define SOC_IOC_IOCG_138_iocg_138_ds2_END    (6)
#define SOC_IOC_IOCG_138_iocg_138_sr_START   (7)
#define SOC_IOC_IOCG_138_iocg_138_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_139_UNION
 结构说明  : IOCG_139 寄存器结构定义。地址偏移量:0xA2C，初值:0x00000012，宽度:32
 寄存器说明: ANTPA_SEL27功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_139_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_139_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_139_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_139_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_139_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_139_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_139_UNION;
#endif
#define SOC_IOC_IOCG_139_iocg_139_pu_START   (0)
#define SOC_IOC_IOCG_139_iocg_139_pu_END     (0)
#define SOC_IOC_IOCG_139_iocg_139_pd_START   (1)
#define SOC_IOC_IOCG_139_iocg_139_pd_END     (1)
#define SOC_IOC_IOCG_139_iocg_139_ds0_START  (4)
#define SOC_IOC_IOCG_139_iocg_139_ds0_END    (4)
#define SOC_IOC_IOCG_139_iocg_139_ds1_START  (5)
#define SOC_IOC_IOCG_139_iocg_139_ds1_END    (5)
#define SOC_IOC_IOCG_139_iocg_139_ds2_START  (6)
#define SOC_IOC_IOCG_139_iocg_139_ds2_END    (6)
#define SOC_IOC_IOCG_139_iocg_139_sr_START   (7)
#define SOC_IOC_IOCG_139_iocg_139_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_140_UNION
 结构说明  : IOCG_140 寄存器结构定义。地址偏移量:0xA30，初值:0x00000012，宽度:32
 寄存器说明: GPIO_140功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_140_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_140_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_140_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_140_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_140_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_140_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_140_UNION;
#endif
#define SOC_IOC_IOCG_140_iocg_140_pu_START   (0)
#define SOC_IOC_IOCG_140_iocg_140_pu_END     (0)
#define SOC_IOC_IOCG_140_iocg_140_pd_START   (1)
#define SOC_IOC_IOCG_140_iocg_140_pd_END     (1)
#define SOC_IOC_IOCG_140_iocg_140_ds0_START  (4)
#define SOC_IOC_IOCG_140_iocg_140_ds0_END    (4)
#define SOC_IOC_IOCG_140_iocg_140_ds1_START  (5)
#define SOC_IOC_IOCG_140_iocg_140_ds1_END    (5)
#define SOC_IOC_IOCG_140_iocg_140_ds2_START  (6)
#define SOC_IOC_IOCG_140_iocg_140_ds2_END    (6)
#define SOC_IOC_IOCG_140_iocg_140_sr_START   (7)
#define SOC_IOC_IOCG_140_iocg_140_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_141_UNION
 结构说明  : IOCG_141 寄存器结构定义。地址偏移量:0xA34，初值:0x00000012，宽度:32
 寄存器说明: GPIO_141功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_141_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_141_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_141_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_141_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_141_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_141_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_141_UNION;
#endif
#define SOC_IOC_IOCG_141_iocg_141_pu_START   (0)
#define SOC_IOC_IOCG_141_iocg_141_pu_END     (0)
#define SOC_IOC_IOCG_141_iocg_141_pd_START   (1)
#define SOC_IOC_IOCG_141_iocg_141_pd_END     (1)
#define SOC_IOC_IOCG_141_iocg_141_ds0_START  (4)
#define SOC_IOC_IOCG_141_iocg_141_ds0_END    (4)
#define SOC_IOC_IOCG_141_iocg_141_ds1_START  (5)
#define SOC_IOC_IOCG_141_iocg_141_ds1_END    (5)
#define SOC_IOC_IOCG_141_iocg_141_ds2_START  (6)
#define SOC_IOC_IOCG_141_iocg_141_ds2_END    (6)
#define SOC_IOC_IOCG_141_iocg_141_sr_START   (7)
#define SOC_IOC_IOCG_141_iocg_141_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_142_UNION
 结构说明  : IOCG_142 寄存器结构定义。地址偏移量:0xA38，初值:0x00000012，宽度:32
 寄存器说明: GPIO_142功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_142_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_142_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_142_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_142_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_142_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_142_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_142_UNION;
#endif
#define SOC_IOC_IOCG_142_iocg_142_pu_START   (0)
#define SOC_IOC_IOCG_142_iocg_142_pu_END     (0)
#define SOC_IOC_IOCG_142_iocg_142_pd_START   (1)
#define SOC_IOC_IOCG_142_iocg_142_pd_END     (1)
#define SOC_IOC_IOCG_142_iocg_142_ds0_START  (4)
#define SOC_IOC_IOCG_142_iocg_142_ds0_END    (4)
#define SOC_IOC_IOCG_142_iocg_142_ds1_START  (5)
#define SOC_IOC_IOCG_142_iocg_142_ds1_END    (5)
#define SOC_IOC_IOCG_142_iocg_142_ds2_START  (6)
#define SOC_IOC_IOCG_142_iocg_142_ds2_END    (6)
#define SOC_IOC_IOCG_142_iocg_142_sr_START   (7)
#define SOC_IOC_IOCG_142_iocg_142_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_143_UNION
 结构说明  : IOCG_143 寄存器结构定义。地址偏移量:0xA3C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_143功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_143_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_143_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_143_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_143_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_143_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_143_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_143_UNION;
#endif
#define SOC_IOC_IOCG_143_iocg_143_pu_START   (0)
#define SOC_IOC_IOCG_143_iocg_143_pu_END     (0)
#define SOC_IOC_IOCG_143_iocg_143_pd_START   (1)
#define SOC_IOC_IOCG_143_iocg_143_pd_END     (1)
#define SOC_IOC_IOCG_143_iocg_143_ds0_START  (4)
#define SOC_IOC_IOCG_143_iocg_143_ds0_END    (4)
#define SOC_IOC_IOCG_143_iocg_143_ds1_START  (5)
#define SOC_IOC_IOCG_143_iocg_143_ds1_END    (5)
#define SOC_IOC_IOCG_143_iocg_143_ds2_START  (6)
#define SOC_IOC_IOCG_143_iocg_143_ds2_END    (6)
#define SOC_IOC_IOCG_143_iocg_143_sr_START   (7)
#define SOC_IOC_IOCG_143_iocg_143_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_144_UNION
 结构说明  : IOCG_144 寄存器结构定义。地址偏移量:0xA40，初值:0x00000012，宽度:32
 寄存器说明: GPIO_144功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_144_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_144_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_144_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_144_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_144_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_144_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_144_UNION;
#endif
#define SOC_IOC_IOCG_144_iocg_144_pu_START   (0)
#define SOC_IOC_IOCG_144_iocg_144_pu_END     (0)
#define SOC_IOC_IOCG_144_iocg_144_pd_START   (1)
#define SOC_IOC_IOCG_144_iocg_144_pd_END     (1)
#define SOC_IOC_IOCG_144_iocg_144_ds0_START  (4)
#define SOC_IOC_IOCG_144_iocg_144_ds0_END    (4)
#define SOC_IOC_IOCG_144_iocg_144_ds1_START  (5)
#define SOC_IOC_IOCG_144_iocg_144_ds1_END    (5)
#define SOC_IOC_IOCG_144_iocg_144_ds2_START  (6)
#define SOC_IOC_IOCG_144_iocg_144_ds2_END    (6)
#define SOC_IOC_IOCG_144_iocg_144_sr_START   (7)
#define SOC_IOC_IOCG_144_iocg_144_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_145_UNION
 结构说明  : IOCG_145 寄存器结构定义。地址偏移量:0xA44，初值:0x00000012，宽度:32
 寄存器说明: GPIO_145功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_145_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_145_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_145_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_145_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_145_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_145_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_145_UNION;
#endif
#define SOC_IOC_IOCG_145_iocg_145_pu_START   (0)
#define SOC_IOC_IOCG_145_iocg_145_pu_END     (0)
#define SOC_IOC_IOCG_145_iocg_145_pd_START   (1)
#define SOC_IOC_IOCG_145_iocg_145_pd_END     (1)
#define SOC_IOC_IOCG_145_iocg_145_ds0_START  (4)
#define SOC_IOC_IOCG_145_iocg_145_ds0_END    (4)
#define SOC_IOC_IOCG_145_iocg_145_ds1_START  (5)
#define SOC_IOC_IOCG_145_iocg_145_ds1_END    (5)
#define SOC_IOC_IOCG_145_iocg_145_ds2_START  (6)
#define SOC_IOC_IOCG_145_iocg_145_ds2_END    (6)
#define SOC_IOC_IOCG_145_iocg_145_sr_START   (7)
#define SOC_IOC_IOCG_145_iocg_145_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_146_UNION
 结构说明  : IOCG_146 寄存器结构定义。地址偏移量:0xA48，初值:0x00000012，宽度:32
 寄存器说明: GPIO_146功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_146_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_146_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_146_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_146_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_146_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_146_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_146_UNION;
#endif
#define SOC_IOC_IOCG_146_iocg_146_pu_START   (0)
#define SOC_IOC_IOCG_146_iocg_146_pu_END     (0)
#define SOC_IOC_IOCG_146_iocg_146_pd_START   (1)
#define SOC_IOC_IOCG_146_iocg_146_pd_END     (1)
#define SOC_IOC_IOCG_146_iocg_146_ds0_START  (4)
#define SOC_IOC_IOCG_146_iocg_146_ds0_END    (4)
#define SOC_IOC_IOCG_146_iocg_146_ds1_START  (5)
#define SOC_IOC_IOCG_146_iocg_146_ds1_END    (5)
#define SOC_IOC_IOCG_146_iocg_146_ds2_START  (6)
#define SOC_IOC_IOCG_146_iocg_146_ds2_END    (6)
#define SOC_IOC_IOCG_146_iocg_146_sr_START   (7)
#define SOC_IOC_IOCG_146_iocg_146_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_147_UNION
 结构说明  : IOCG_147 寄存器结构定义。地址偏移量:0xA4C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_147功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_147_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_147_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_147_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_147_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_147_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_147_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_147_UNION;
#endif
#define SOC_IOC_IOCG_147_iocg_147_pu_START   (0)
#define SOC_IOC_IOCG_147_iocg_147_pu_END     (0)
#define SOC_IOC_IOCG_147_iocg_147_pd_START   (1)
#define SOC_IOC_IOCG_147_iocg_147_pd_END     (1)
#define SOC_IOC_IOCG_147_iocg_147_ds0_START  (4)
#define SOC_IOC_IOCG_147_iocg_147_ds0_END    (4)
#define SOC_IOC_IOCG_147_iocg_147_ds1_START  (5)
#define SOC_IOC_IOCG_147_iocg_147_ds1_END    (5)
#define SOC_IOC_IOCG_147_iocg_147_ds2_START  (6)
#define SOC_IOC_IOCG_147_iocg_147_ds2_END    (6)
#define SOC_IOC_IOCG_147_iocg_147_sr_START   (7)
#define SOC_IOC_IOCG_147_iocg_147_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_148_UNION
 结构说明  : IOCG_148 寄存器结构定义。地址偏移量:0xA50，初值:0x00000012，宽度:32
 寄存器说明: GPIO_148功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_148_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_148_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_148_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_148_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_148_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_148_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_148_UNION;
#endif
#define SOC_IOC_IOCG_148_iocg_148_pu_START   (0)
#define SOC_IOC_IOCG_148_iocg_148_pu_END     (0)
#define SOC_IOC_IOCG_148_iocg_148_pd_START   (1)
#define SOC_IOC_IOCG_148_iocg_148_pd_END     (1)
#define SOC_IOC_IOCG_148_iocg_148_ds0_START  (4)
#define SOC_IOC_IOCG_148_iocg_148_ds0_END    (4)
#define SOC_IOC_IOCG_148_iocg_148_ds1_START  (5)
#define SOC_IOC_IOCG_148_iocg_148_ds1_END    (5)
#define SOC_IOC_IOCG_148_iocg_148_ds2_START  (6)
#define SOC_IOC_IOCG_148_iocg_148_ds2_END    (6)
#define SOC_IOC_IOCG_148_iocg_148_sr_START   (7)
#define SOC_IOC_IOCG_148_iocg_148_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_149_UNION
 结构说明  : IOCG_149 寄存器结构定义。地址偏移量:0xA54，初值:0x00000012，宽度:32
 寄存器说明: GPIO_149功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_149_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_149_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_149_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_149_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_149_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_149_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_149_UNION;
#endif
#define SOC_IOC_IOCG_149_iocg_149_pu_START   (0)
#define SOC_IOC_IOCG_149_iocg_149_pu_END     (0)
#define SOC_IOC_IOCG_149_iocg_149_pd_START   (1)
#define SOC_IOC_IOCG_149_iocg_149_pd_END     (1)
#define SOC_IOC_IOCG_149_iocg_149_ds0_START  (4)
#define SOC_IOC_IOCG_149_iocg_149_ds0_END    (4)
#define SOC_IOC_IOCG_149_iocg_149_ds1_START  (5)
#define SOC_IOC_IOCG_149_iocg_149_ds1_END    (5)
#define SOC_IOC_IOCG_149_iocg_149_ds2_START  (6)
#define SOC_IOC_IOCG_149_iocg_149_ds2_END    (6)
#define SOC_IOC_IOCG_149_iocg_149_sr_START   (7)
#define SOC_IOC_IOCG_149_iocg_149_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_150_UNION
 结构说明  : IOCG_150 寄存器结构定义。地址偏移量:0xA58，初值:0x00000012，宽度:32
 寄存器说明: GPIO_150功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_150_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_150_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_150_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_150_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_150_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_150_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_150_UNION;
#endif
#define SOC_IOC_IOCG_150_iocg_150_pu_START   (0)
#define SOC_IOC_IOCG_150_iocg_150_pu_END     (0)
#define SOC_IOC_IOCG_150_iocg_150_pd_START   (1)
#define SOC_IOC_IOCG_150_iocg_150_pd_END     (1)
#define SOC_IOC_IOCG_150_iocg_150_ds0_START  (4)
#define SOC_IOC_IOCG_150_iocg_150_ds0_END    (4)
#define SOC_IOC_IOCG_150_iocg_150_ds1_START  (5)
#define SOC_IOC_IOCG_150_iocg_150_ds1_END    (5)
#define SOC_IOC_IOCG_150_iocg_150_ds2_START  (6)
#define SOC_IOC_IOCG_150_iocg_150_ds2_END    (6)
#define SOC_IOC_IOCG_150_iocg_150_sr_START   (7)
#define SOC_IOC_IOCG_150_iocg_150_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_151_UNION
 结构说明  : IOCG_151 寄存器结构定义。地址偏移量:0xA5C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_151功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_151_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_151_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_151_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_151_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_151_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_151_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_151_UNION;
#endif
#define SOC_IOC_IOCG_151_iocg_151_pu_START   (0)
#define SOC_IOC_IOCG_151_iocg_151_pu_END     (0)
#define SOC_IOC_IOCG_151_iocg_151_pd_START   (1)
#define SOC_IOC_IOCG_151_iocg_151_pd_END     (1)
#define SOC_IOC_IOCG_151_iocg_151_ds0_START  (4)
#define SOC_IOC_IOCG_151_iocg_151_ds0_END    (4)
#define SOC_IOC_IOCG_151_iocg_151_ds1_START  (5)
#define SOC_IOC_IOCG_151_iocg_151_ds1_END    (5)
#define SOC_IOC_IOCG_151_iocg_151_ds2_START  (6)
#define SOC_IOC_IOCG_151_iocg_151_ds2_END    (6)
#define SOC_IOC_IOCG_151_iocg_151_sr_START   (7)
#define SOC_IOC_IOCG_151_iocg_151_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_152_UNION
 结构说明  : IOCG_152 寄存器结构定义。地址偏移量:0xA60，初值:0x00000012，宽度:32
 寄存器说明: GPIO_152功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_152_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_152_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_152_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_152_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_152_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_152_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_152_UNION;
#endif
#define SOC_IOC_IOCG_152_iocg_152_pu_START   (0)
#define SOC_IOC_IOCG_152_iocg_152_pu_END     (0)
#define SOC_IOC_IOCG_152_iocg_152_pd_START   (1)
#define SOC_IOC_IOCG_152_iocg_152_pd_END     (1)
#define SOC_IOC_IOCG_152_iocg_152_ds0_START  (4)
#define SOC_IOC_IOCG_152_iocg_152_ds0_END    (4)
#define SOC_IOC_IOCG_152_iocg_152_ds1_START  (5)
#define SOC_IOC_IOCG_152_iocg_152_ds1_END    (5)
#define SOC_IOC_IOCG_152_iocg_152_ds2_START  (6)
#define SOC_IOC_IOCG_152_iocg_152_ds2_END    (6)
#define SOC_IOC_IOCG_152_iocg_152_sr_START   (7)
#define SOC_IOC_IOCG_152_iocg_152_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_153_UNION
 结构说明  : IOCG_153 寄存器结构定义。地址偏移量:0xA64，初值:0x00000012，宽度:32
 寄存器说明: GPIO_153功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_153_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_153_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_153_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_153_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_153_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_153_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_153_UNION;
#endif
#define SOC_IOC_IOCG_153_iocg_153_pu_START   (0)
#define SOC_IOC_IOCG_153_iocg_153_pu_END     (0)
#define SOC_IOC_IOCG_153_iocg_153_pd_START   (1)
#define SOC_IOC_IOCG_153_iocg_153_pd_END     (1)
#define SOC_IOC_IOCG_153_iocg_153_ds0_START  (4)
#define SOC_IOC_IOCG_153_iocg_153_ds0_END    (4)
#define SOC_IOC_IOCG_153_iocg_153_ds1_START  (5)
#define SOC_IOC_IOCG_153_iocg_153_ds1_END    (5)
#define SOC_IOC_IOCG_153_iocg_153_ds2_START  (6)
#define SOC_IOC_IOCG_153_iocg_153_ds2_END    (6)
#define SOC_IOC_IOCG_153_iocg_153_sr_START   (7)
#define SOC_IOC_IOCG_153_iocg_153_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_154_UNION
 结构说明  : IOCG_154 寄存器结构定义。地址偏移量:0xA68，初值:0x00000012，宽度:32
 寄存器说明: GPIO_154功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_154_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_154_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_154_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_154_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_154_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_154_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_154_UNION;
#endif
#define SOC_IOC_IOCG_154_iocg_154_pu_START   (0)
#define SOC_IOC_IOCG_154_iocg_154_pu_END     (0)
#define SOC_IOC_IOCG_154_iocg_154_pd_START   (1)
#define SOC_IOC_IOCG_154_iocg_154_pd_END     (1)
#define SOC_IOC_IOCG_154_iocg_154_ds0_START  (4)
#define SOC_IOC_IOCG_154_iocg_154_ds0_END    (4)
#define SOC_IOC_IOCG_154_iocg_154_ds1_START  (5)
#define SOC_IOC_IOCG_154_iocg_154_ds1_END    (5)
#define SOC_IOC_IOCG_154_iocg_154_ds2_START  (6)
#define SOC_IOC_IOCG_154_iocg_154_ds2_END    (6)
#define SOC_IOC_IOCG_154_iocg_154_sr_START   (7)
#define SOC_IOC_IOCG_154_iocg_154_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_155_UNION
 结构说明  : IOCG_155 寄存器结构定义。地址偏移量:0xA6C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_155功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_155_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_155_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_155_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_155_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_155_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_155_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_155_UNION;
#endif
#define SOC_IOC_IOCG_155_iocg_155_pu_START   (0)
#define SOC_IOC_IOCG_155_iocg_155_pu_END     (0)
#define SOC_IOC_IOCG_155_iocg_155_pd_START   (1)
#define SOC_IOC_IOCG_155_iocg_155_pd_END     (1)
#define SOC_IOC_IOCG_155_iocg_155_ds0_START  (4)
#define SOC_IOC_IOCG_155_iocg_155_ds0_END    (4)
#define SOC_IOC_IOCG_155_iocg_155_ds1_START  (5)
#define SOC_IOC_IOCG_155_iocg_155_ds1_END    (5)
#define SOC_IOC_IOCG_155_iocg_155_ds2_START  (6)
#define SOC_IOC_IOCG_155_iocg_155_ds2_END    (6)
#define SOC_IOC_IOCG_155_iocg_155_sr_START   (7)
#define SOC_IOC_IOCG_155_iocg_155_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_156_UNION
 结构说明  : IOCG_156 寄存器结构定义。地址偏移量:0xA70，初值:0x00000012，宽度:32
 寄存器说明: GPIO_156功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_156_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_156_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_156_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_156_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_156_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_156_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_156_UNION;
#endif
#define SOC_IOC_IOCG_156_iocg_156_pu_START   (0)
#define SOC_IOC_IOCG_156_iocg_156_pu_END     (0)
#define SOC_IOC_IOCG_156_iocg_156_pd_START   (1)
#define SOC_IOC_IOCG_156_iocg_156_pd_END     (1)
#define SOC_IOC_IOCG_156_iocg_156_ds0_START  (4)
#define SOC_IOC_IOCG_156_iocg_156_ds0_END    (4)
#define SOC_IOC_IOCG_156_iocg_156_ds1_START  (5)
#define SOC_IOC_IOCG_156_iocg_156_ds1_END    (5)
#define SOC_IOC_IOCG_156_iocg_156_ds2_START  (6)
#define SOC_IOC_IOCG_156_iocg_156_ds2_END    (6)
#define SOC_IOC_IOCG_156_iocg_156_sr_START   (7)
#define SOC_IOC_IOCG_156_iocg_156_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_157_UNION
 结构说明  : IOCG_157 寄存器结构定义。地址偏移量:0xA74，初值:0x00000012，宽度:32
 寄存器说明: GPIO_157功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_157_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_157_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_157_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_157_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_157_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_157_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_157_UNION;
#endif
#define SOC_IOC_IOCG_157_iocg_157_pu_START   (0)
#define SOC_IOC_IOCG_157_iocg_157_pu_END     (0)
#define SOC_IOC_IOCG_157_iocg_157_pd_START   (1)
#define SOC_IOC_IOCG_157_iocg_157_pd_END     (1)
#define SOC_IOC_IOCG_157_iocg_157_ds0_START  (4)
#define SOC_IOC_IOCG_157_iocg_157_ds0_END    (4)
#define SOC_IOC_IOCG_157_iocg_157_ds1_START  (5)
#define SOC_IOC_IOCG_157_iocg_157_ds1_END    (5)
#define SOC_IOC_IOCG_157_iocg_157_ds2_START  (6)
#define SOC_IOC_IOCG_157_iocg_157_ds2_END    (6)
#define SOC_IOC_IOCG_157_iocg_157_sr_START   (7)
#define SOC_IOC_IOCG_157_iocg_157_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_158_UNION
 结构说明  : IOCG_158 寄存器结构定义。地址偏移量:0xA78，初值:0x00000012，宽度:32
 寄存器说明: GPIO_158功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_158_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_158_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_158_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_158_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_158_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_158_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_158_UNION;
#endif
#define SOC_IOC_IOCG_158_iocg_158_pu_START   (0)
#define SOC_IOC_IOCG_158_iocg_158_pu_END     (0)
#define SOC_IOC_IOCG_158_iocg_158_pd_START   (1)
#define SOC_IOC_IOCG_158_iocg_158_pd_END     (1)
#define SOC_IOC_IOCG_158_iocg_158_ds0_START  (4)
#define SOC_IOC_IOCG_158_iocg_158_ds0_END    (4)
#define SOC_IOC_IOCG_158_iocg_158_ds1_START  (5)
#define SOC_IOC_IOCG_158_iocg_158_ds1_END    (5)
#define SOC_IOC_IOCG_158_iocg_158_ds2_START  (6)
#define SOC_IOC_IOCG_158_iocg_158_ds2_END    (6)
#define SOC_IOC_IOCG_158_iocg_158_sr_START   (7)
#define SOC_IOC_IOCG_158_iocg_158_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_159_UNION
 结构说明  : IOCG_159 寄存器结构定义。地址偏移量:0xA7C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_159功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_159_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_159_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_159_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_159_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_159_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_159_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_159_UNION;
#endif
#define SOC_IOC_IOCG_159_iocg_159_pu_START   (0)
#define SOC_IOC_IOCG_159_iocg_159_pu_END     (0)
#define SOC_IOC_IOCG_159_iocg_159_pd_START   (1)
#define SOC_IOC_IOCG_159_iocg_159_pd_END     (1)
#define SOC_IOC_IOCG_159_iocg_159_ds0_START  (4)
#define SOC_IOC_IOCG_159_iocg_159_ds0_END    (4)
#define SOC_IOC_IOCG_159_iocg_159_ds1_START  (5)
#define SOC_IOC_IOCG_159_iocg_159_ds1_END    (5)
#define SOC_IOC_IOCG_159_iocg_159_ds2_START  (6)
#define SOC_IOC_IOCG_159_iocg_159_ds2_END    (6)
#define SOC_IOC_IOCG_159_iocg_159_sr_START   (7)
#define SOC_IOC_IOCG_159_iocg_159_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_160_UNION
 结构说明  : IOCG_160 寄存器结构定义。地址偏移量:0xA80，初值:0x00000012，宽度:32
 寄存器说明: GPIO_160功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_160_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_160_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_160_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_160_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_160_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_160_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_160_UNION;
#endif
#define SOC_IOC_IOCG_160_iocg_160_pu_START   (0)
#define SOC_IOC_IOCG_160_iocg_160_pu_END     (0)
#define SOC_IOC_IOCG_160_iocg_160_pd_START   (1)
#define SOC_IOC_IOCG_160_iocg_160_pd_END     (1)
#define SOC_IOC_IOCG_160_iocg_160_ds0_START  (4)
#define SOC_IOC_IOCG_160_iocg_160_ds0_END    (4)
#define SOC_IOC_IOCG_160_iocg_160_ds1_START  (5)
#define SOC_IOC_IOCG_160_iocg_160_ds1_END    (5)
#define SOC_IOC_IOCG_160_iocg_160_ds2_START  (6)
#define SOC_IOC_IOCG_160_iocg_160_ds2_END    (6)
#define SOC_IOC_IOCG_160_iocg_160_sr_START   (7)
#define SOC_IOC_IOCG_160_iocg_160_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_161_UNION
 结构说明  : IOCG_161 寄存器结构定义。地址偏移量:0xA84，初值:0x00000012，宽度:32
 寄存器说明: GPIO_161功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_161_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_161_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_161_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_161_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_161_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_161_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_161_UNION;
#endif
#define SOC_IOC_IOCG_161_iocg_161_pu_START   (0)
#define SOC_IOC_IOCG_161_iocg_161_pu_END     (0)
#define SOC_IOC_IOCG_161_iocg_161_pd_START   (1)
#define SOC_IOC_IOCG_161_iocg_161_pd_END     (1)
#define SOC_IOC_IOCG_161_iocg_161_ds0_START  (4)
#define SOC_IOC_IOCG_161_iocg_161_ds0_END    (4)
#define SOC_IOC_IOCG_161_iocg_161_ds1_START  (5)
#define SOC_IOC_IOCG_161_iocg_161_ds1_END    (5)
#define SOC_IOC_IOCG_161_iocg_161_ds2_START  (6)
#define SOC_IOC_IOCG_161_iocg_161_ds2_END    (6)
#define SOC_IOC_IOCG_161_iocg_161_sr_START   (7)
#define SOC_IOC_IOCG_161_iocg_161_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_162_UNION
 结构说明  : IOCG_162 寄存器结构定义。地址偏移量:0xA88，初值:0x00000012，宽度:32
 寄存器说明: GPIO_162功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_162_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_162_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_162_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_162_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_162_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_162_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_162_UNION;
#endif
#define SOC_IOC_IOCG_162_iocg_162_pu_START   (0)
#define SOC_IOC_IOCG_162_iocg_162_pu_END     (0)
#define SOC_IOC_IOCG_162_iocg_162_pd_START   (1)
#define SOC_IOC_IOCG_162_iocg_162_pd_END     (1)
#define SOC_IOC_IOCG_162_iocg_162_ds0_START  (4)
#define SOC_IOC_IOCG_162_iocg_162_ds0_END    (4)
#define SOC_IOC_IOCG_162_iocg_162_ds1_START  (5)
#define SOC_IOC_IOCG_162_iocg_162_ds1_END    (5)
#define SOC_IOC_IOCG_162_iocg_162_ds2_START  (6)
#define SOC_IOC_IOCG_162_iocg_162_ds2_END    (6)
#define SOC_IOC_IOCG_162_iocg_162_sr_START   (7)
#define SOC_IOC_IOCG_162_iocg_162_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_163_UNION
 结构说明  : IOCG_163 寄存器结构定义。地址偏移量:0xA8C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_163功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_163_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_163_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_163_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_163_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_163_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_163_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_163_UNION;
#endif
#define SOC_IOC_IOCG_163_iocg_163_pu_START   (0)
#define SOC_IOC_IOCG_163_iocg_163_pu_END     (0)
#define SOC_IOC_IOCG_163_iocg_163_pd_START   (1)
#define SOC_IOC_IOCG_163_iocg_163_pd_END     (1)
#define SOC_IOC_IOCG_163_iocg_163_ds0_START  (4)
#define SOC_IOC_IOCG_163_iocg_163_ds0_END    (4)
#define SOC_IOC_IOCG_163_iocg_163_ds1_START  (5)
#define SOC_IOC_IOCG_163_iocg_163_ds1_END    (5)
#define SOC_IOC_IOCG_163_iocg_163_ds2_START  (6)
#define SOC_IOC_IOCG_163_iocg_163_ds2_END    (6)
#define SOC_IOC_IOCG_163_iocg_163_sr_START   (7)
#define SOC_IOC_IOCG_163_iocg_163_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_164_UNION
 结构说明  : IOCG_164 寄存器结构定义。地址偏移量:0xA90，初值:0x00000012，宽度:32
 寄存器说明: GPIO_164功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_164_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_164_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_164_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_164_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_164_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_164_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_164_UNION;
#endif
#define SOC_IOC_IOCG_164_iocg_164_pu_START   (0)
#define SOC_IOC_IOCG_164_iocg_164_pu_END     (0)
#define SOC_IOC_IOCG_164_iocg_164_pd_START   (1)
#define SOC_IOC_IOCG_164_iocg_164_pd_END     (1)
#define SOC_IOC_IOCG_164_iocg_164_ds0_START  (4)
#define SOC_IOC_IOCG_164_iocg_164_ds0_END    (4)
#define SOC_IOC_IOCG_164_iocg_164_ds1_START  (5)
#define SOC_IOC_IOCG_164_iocg_164_ds1_END    (5)
#define SOC_IOC_IOCG_164_iocg_164_ds2_START  (6)
#define SOC_IOC_IOCG_164_iocg_164_ds2_END    (6)
#define SOC_IOC_IOCG_164_iocg_164_sr_START   (7)
#define SOC_IOC_IOCG_164_iocg_164_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_165_UNION
 结构说明  : IOCG_165 寄存器结构定义。地址偏移量:0xA94，初值:0x00000012，宽度:32
 寄存器说明: GPIO_165功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_165_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_165_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_165_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_165_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_165_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_165_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_165_UNION;
#endif
#define SOC_IOC_IOCG_165_iocg_165_pu_START   (0)
#define SOC_IOC_IOCG_165_iocg_165_pu_END     (0)
#define SOC_IOC_IOCG_165_iocg_165_pd_START   (1)
#define SOC_IOC_IOCG_165_iocg_165_pd_END     (1)
#define SOC_IOC_IOCG_165_iocg_165_ds0_START  (4)
#define SOC_IOC_IOCG_165_iocg_165_ds0_END    (4)
#define SOC_IOC_IOCG_165_iocg_165_ds1_START  (5)
#define SOC_IOC_IOCG_165_iocg_165_ds1_END    (5)
#define SOC_IOC_IOCG_165_iocg_165_ds2_START  (6)
#define SOC_IOC_IOCG_165_iocg_165_ds2_END    (6)
#define SOC_IOC_IOCG_165_iocg_165_sr_START   (7)
#define SOC_IOC_IOCG_165_iocg_165_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_166_UNION
 结构说明  : IOCG_166 寄存器结构定义。地址偏移量:0xA98，初值:0x00000012，宽度:32
 寄存器说明: GPIO_166功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_166_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_166_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_166_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_166_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_166_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_166_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_166_UNION;
#endif
#define SOC_IOC_IOCG_166_iocg_166_pu_START   (0)
#define SOC_IOC_IOCG_166_iocg_166_pu_END     (0)
#define SOC_IOC_IOCG_166_iocg_166_pd_START   (1)
#define SOC_IOC_IOCG_166_iocg_166_pd_END     (1)
#define SOC_IOC_IOCG_166_iocg_166_ds0_START  (4)
#define SOC_IOC_IOCG_166_iocg_166_ds0_END    (4)
#define SOC_IOC_IOCG_166_iocg_166_ds1_START  (5)
#define SOC_IOC_IOCG_166_iocg_166_ds1_END    (5)
#define SOC_IOC_IOCG_166_iocg_166_ds2_START  (6)
#define SOC_IOC_IOCG_166_iocg_166_ds2_END    (6)
#define SOC_IOC_IOCG_166_iocg_166_sr_START   (7)
#define SOC_IOC_IOCG_166_iocg_166_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_167_UNION
 结构说明  : IOCG_167 寄存器结构定义。地址偏移量:0xA9C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_167功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_167_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_167_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_167_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_167_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_167_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_167_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_167_UNION;
#endif
#define SOC_IOC_IOCG_167_iocg_167_pu_START   (0)
#define SOC_IOC_IOCG_167_iocg_167_pu_END     (0)
#define SOC_IOC_IOCG_167_iocg_167_pd_START   (1)
#define SOC_IOC_IOCG_167_iocg_167_pd_END     (1)
#define SOC_IOC_IOCG_167_iocg_167_ds0_START  (4)
#define SOC_IOC_IOCG_167_iocg_167_ds0_END    (4)
#define SOC_IOC_IOCG_167_iocg_167_ds1_START  (5)
#define SOC_IOC_IOCG_167_iocg_167_ds1_END    (5)
#define SOC_IOC_IOCG_167_iocg_167_ds2_START  (6)
#define SOC_IOC_IOCG_167_iocg_167_ds2_END    (6)
#define SOC_IOC_IOCG_167_iocg_167_sr_START   (7)
#define SOC_IOC_IOCG_167_iocg_167_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_168_UNION
 结构说明  : IOCG_168 寄存器结构定义。地址偏移量:0xAA0，初值:0x00000012，宽度:32
 寄存器说明: GPIO_168功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_168_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_168_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_168_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_168_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_168_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_168_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_168_UNION;
#endif
#define SOC_IOC_IOCG_168_iocg_168_pu_START   (0)
#define SOC_IOC_IOCG_168_iocg_168_pu_END     (0)
#define SOC_IOC_IOCG_168_iocg_168_pd_START   (1)
#define SOC_IOC_IOCG_168_iocg_168_pd_END     (1)
#define SOC_IOC_IOCG_168_iocg_168_ds0_START  (4)
#define SOC_IOC_IOCG_168_iocg_168_ds0_END    (4)
#define SOC_IOC_IOCG_168_iocg_168_ds1_START  (5)
#define SOC_IOC_IOCG_168_iocg_168_ds1_END    (5)
#define SOC_IOC_IOCG_168_iocg_168_ds2_START  (6)
#define SOC_IOC_IOCG_168_iocg_168_ds2_END    (6)
#define SOC_IOC_IOCG_168_iocg_168_sr_START   (7)
#define SOC_IOC_IOCG_168_iocg_168_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_169_UNION
 结构说明  : IOCG_169 寄存器结构定义。地址偏移量:0xAA4，初值:0x00000012，宽度:32
 寄存器说明: GPIO_169功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_169_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_169_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_169_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_169_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_169_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_169_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_169_UNION;
#endif
#define SOC_IOC_IOCG_169_iocg_169_pu_START   (0)
#define SOC_IOC_IOCG_169_iocg_169_pu_END     (0)
#define SOC_IOC_IOCG_169_iocg_169_pd_START   (1)
#define SOC_IOC_IOCG_169_iocg_169_pd_END     (1)
#define SOC_IOC_IOCG_169_iocg_169_ds0_START  (4)
#define SOC_IOC_IOCG_169_iocg_169_ds0_END    (4)
#define SOC_IOC_IOCG_169_iocg_169_ds1_START  (5)
#define SOC_IOC_IOCG_169_iocg_169_ds1_END    (5)
#define SOC_IOC_IOCG_169_iocg_169_ds2_START  (6)
#define SOC_IOC_IOCG_169_iocg_169_ds2_END    (6)
#define SOC_IOC_IOCG_169_iocg_169_sr_START   (7)
#define SOC_IOC_IOCG_169_iocg_169_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_170_UNION
 结构说明  : IOCG_170 寄存器结构定义。地址偏移量:0xAA8，初值:0x00000012，宽度:32
 寄存器说明: GPIO_170功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_170_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_170_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_170_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_170_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_170_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_170_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_170_UNION;
#endif
#define SOC_IOC_IOCG_170_iocg_170_pu_START   (0)
#define SOC_IOC_IOCG_170_iocg_170_pu_END     (0)
#define SOC_IOC_IOCG_170_iocg_170_pd_START   (1)
#define SOC_IOC_IOCG_170_iocg_170_pd_END     (1)
#define SOC_IOC_IOCG_170_iocg_170_ds0_START  (4)
#define SOC_IOC_IOCG_170_iocg_170_ds0_END    (4)
#define SOC_IOC_IOCG_170_iocg_170_ds1_START  (5)
#define SOC_IOC_IOCG_170_iocg_170_ds1_END    (5)
#define SOC_IOC_IOCG_170_iocg_170_ds2_START  (6)
#define SOC_IOC_IOCG_170_iocg_170_ds2_END    (6)
#define SOC_IOC_IOCG_170_iocg_170_sr_START   (7)
#define SOC_IOC_IOCG_170_iocg_170_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_171_UNION
 结构说明  : IOCG_171 寄存器结构定义。地址偏移量:0xAAC，初值:0x00000012，宽度:32
 寄存器说明: GPIO_171功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_171_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_171_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_171_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_171_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_171_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_171_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_171_UNION;
#endif
#define SOC_IOC_IOCG_171_iocg_171_pu_START   (0)
#define SOC_IOC_IOCG_171_iocg_171_pu_END     (0)
#define SOC_IOC_IOCG_171_iocg_171_pd_START   (1)
#define SOC_IOC_IOCG_171_iocg_171_pd_END     (1)
#define SOC_IOC_IOCG_171_iocg_171_ds0_START  (4)
#define SOC_IOC_IOCG_171_iocg_171_ds0_END    (4)
#define SOC_IOC_IOCG_171_iocg_171_ds1_START  (5)
#define SOC_IOC_IOCG_171_iocg_171_ds1_END    (5)
#define SOC_IOC_IOCG_171_iocg_171_ds2_START  (6)
#define SOC_IOC_IOCG_171_iocg_171_ds2_END    (6)
#define SOC_IOC_IOCG_171_iocg_171_sr_START   (7)
#define SOC_IOC_IOCG_171_iocg_171_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_172_UNION
 结构说明  : IOCG_172 寄存器结构定义。地址偏移量:0xAB0，初值:0x00000012，宽度:32
 寄存器说明: GPIO_172功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_172_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_172_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_172_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_172_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_172_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_172_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_172_UNION;
#endif
#define SOC_IOC_IOCG_172_iocg_172_pu_START   (0)
#define SOC_IOC_IOCG_172_iocg_172_pu_END     (0)
#define SOC_IOC_IOCG_172_iocg_172_pd_START   (1)
#define SOC_IOC_IOCG_172_iocg_172_pd_END     (1)
#define SOC_IOC_IOCG_172_iocg_172_ds0_START  (4)
#define SOC_IOC_IOCG_172_iocg_172_ds0_END    (4)
#define SOC_IOC_IOCG_172_iocg_172_ds1_START  (5)
#define SOC_IOC_IOCG_172_iocg_172_ds1_END    (5)
#define SOC_IOC_IOCG_172_iocg_172_ds2_START  (6)
#define SOC_IOC_IOCG_172_iocg_172_ds2_END    (6)
#define SOC_IOC_IOCG_172_iocg_172_sr_START   (7)
#define SOC_IOC_IOCG_172_iocg_172_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_173_UNION
 结构说明  : IOCG_173 寄存器结构定义。地址偏移量:0xAB4，初值:0x00000012，宽度:32
 寄存器说明: GPIO_173功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_173_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_173_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_173_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_173_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_173_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_173_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_173_UNION;
#endif
#define SOC_IOC_IOCG_173_iocg_173_pu_START   (0)
#define SOC_IOC_IOCG_173_iocg_173_pu_END     (0)
#define SOC_IOC_IOCG_173_iocg_173_pd_START   (1)
#define SOC_IOC_IOCG_173_iocg_173_pd_END     (1)
#define SOC_IOC_IOCG_173_iocg_173_ds0_START  (4)
#define SOC_IOC_IOCG_173_iocg_173_ds0_END    (4)
#define SOC_IOC_IOCG_173_iocg_173_ds1_START  (5)
#define SOC_IOC_IOCG_173_iocg_173_ds1_END    (5)
#define SOC_IOC_IOCG_173_iocg_173_ds2_START  (6)
#define SOC_IOC_IOCG_173_iocg_173_ds2_END    (6)
#define SOC_IOC_IOCG_173_iocg_173_sr_START   (7)
#define SOC_IOC_IOCG_173_iocg_173_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_174_UNION
 结构说明  : IOCG_174 寄存器结构定义。地址偏移量:0xAB8，初值:0x00000012，宽度:32
 寄存器说明: GPIO_174功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_174_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_174_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_174_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_174_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_174_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_174_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_174_UNION;
#endif
#define SOC_IOC_IOCG_174_iocg_174_pu_START   (0)
#define SOC_IOC_IOCG_174_iocg_174_pu_END     (0)
#define SOC_IOC_IOCG_174_iocg_174_pd_START   (1)
#define SOC_IOC_IOCG_174_iocg_174_pd_END     (1)
#define SOC_IOC_IOCG_174_iocg_174_ds0_START  (4)
#define SOC_IOC_IOCG_174_iocg_174_ds0_END    (4)
#define SOC_IOC_IOCG_174_iocg_174_ds1_START  (5)
#define SOC_IOC_IOCG_174_iocg_174_ds1_END    (5)
#define SOC_IOC_IOCG_174_iocg_174_ds2_START  (6)
#define SOC_IOC_IOCG_174_iocg_174_ds2_END    (6)
#define SOC_IOC_IOCG_174_iocg_174_sr_START   (7)
#define SOC_IOC_IOCG_174_iocg_174_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_IOCG_175_UNION
 结构说明  : IOCG_175 寄存器结构定义。地址偏移量:0xABC，初值:0x00000012，宽度:32
 寄存器说明: GPIO_175功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_175_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_175_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_175_ds0 : 1;  /* bit[4]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_175_ds1 : 1;  /* bit[5]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_175_ds2 : 1;  /* bit[6]   : DS2,DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_175_sr  : 1;  /* bit[7]   : Slew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_IOCG_175_UNION;
#endif
#define SOC_IOC_IOCG_175_iocg_175_pu_START   (0)
#define SOC_IOC_IOCG_175_iocg_175_pu_END     (0)
#define SOC_IOC_IOCG_175_iocg_175_pd_START   (1)
#define SOC_IOC_IOCG_175_iocg_175_pd_END     (1)
#define SOC_IOC_IOCG_175_iocg_175_ds0_START  (4)
#define SOC_IOC_IOCG_175_iocg_175_ds0_END    (4)
#define SOC_IOC_IOCG_175_iocg_175_ds1_START  (5)
#define SOC_IOC_IOCG_175_iocg_175_ds1_END    (5)
#define SOC_IOC_IOCG_175_iocg_175_ds2_START  (6)
#define SOC_IOC_IOCG_175_iocg_175_ds2_END    (6)
#define SOC_IOC_IOCG_175_iocg_175_sr_START   (7)
#define SOC_IOC_IOCG_175_iocg_175_sr_END     (7)






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

#endif /* end of soc_ioc_interface.h */
