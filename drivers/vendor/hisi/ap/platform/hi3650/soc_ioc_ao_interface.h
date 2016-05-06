/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_ioc_ao_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:17
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_IOC_AO.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_IOC_AO_INTERFACE_H__
#define __SOC_IOC_AO_INTERFACE_H__

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
/* 寄存器说明：SYSCLK_EN管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_000_UNION */
#define SOC_IOC_AO_IOMG_000_ADDR(base)                ((base) + (0x000))

/* 寄存器说明：CLK_OUT0管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_001_UNION */
#define SOC_IOC_AO_IOMG_001_ADDR(base)                ((base) + (0x004))

/* 寄存器说明：CLK_OUT1管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_002_UNION */
#define SOC_IOC_AO_IOMG_002_ADDR(base)                ((base) + (0x008))

/* 寄存器说明：BLPWM_CABC管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_003_UNION */
#define SOC_IOC_AO_IOMG_003_ADDR(base)                ((base) + (0x00C))

/* 寄存器说明：BLPWM_BL管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_004_UNION */
#define SOC_IOC_AO_IOMG_004_ADDR(base)                ((base) + (0x010))

/* 寄存器说明：I2C0_SCL管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_005_UNION */
#define SOC_IOC_AO_IOMG_005_ADDR(base)                ((base) + (0x014))

/* 寄存器说明：I2C0_SDA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_006_UNION */
#define SOC_IOC_AO_IOMG_006_ADDR(base)                ((base) + (0x018))

/* 寄存器说明：I2C1_SCL管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_007_UNION */
#define SOC_IOC_AO_IOMG_007_ADDR(base)                ((base) + (0x01C))

/* 寄存器说明：I2C1_SDA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_008_UNION */
#define SOC_IOC_AO_IOMG_008_ADDR(base)                ((base) + (0x020))

/* 寄存器说明：I2C2_SCL管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_009_UNION */
#define SOC_IOC_AO_IOMG_009_ADDR(base)                ((base) + (0x024))

/* 寄存器说明：I2C2_SDA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_010_UNION */
#define SOC_IOC_AO_IOMG_010_ADDR(base)                ((base) + (0x028))

/* 寄存器说明：SLIMBUS_CLK管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_011_UNION */
#define SOC_IOC_AO_IOMG_011_ADDR(base)                ((base) + (0x02C))

/* 寄存器说明：SLIMBUS_DATA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_012_UNION */
#define SOC_IOC_AO_IOMG_012_ADDR(base)                ((base) + (0x030))

/* 寄存器说明：GPIO_192管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_013_UNION */
#define SOC_IOC_AO_IOMG_013_ADDR(base)                ((base) + (0x034))

/* 寄存器说明：GPIO_193管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_014_UNION */
#define SOC_IOC_AO_IOMG_014_ADDR(base)                ((base) + (0x038))

/* 寄存器说明：GPIO_194管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_015_UNION */
#define SOC_IOC_AO_IOMG_015_ADDR(base)                ((base) + (0x03C))

/* 寄存器说明：GPIO_195管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_016_UNION */
#define SOC_IOC_AO_IOMG_016_ADDR(base)                ((base) + (0x040))

/* 寄存器说明：GPIO_196管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_017_UNION */
#define SOC_IOC_AO_IOMG_017_ADDR(base)                ((base) + (0x044))

/* 寄存器说明：GPIO_197管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_018_UNION */
#define SOC_IOC_AO_IOMG_018_ADDR(base)                ((base) + (0x048))

/* 寄存器说明：GPIO_198管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_019_UNION */
#define SOC_IOC_AO_IOMG_019_ADDR(base)                ((base) + (0x04C))

/* 寄存器说明：GPIO_199管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_020_UNION */
#define SOC_IOC_AO_IOMG_020_ADDR(base)                ((base) + (0x050))

/* 寄存器说明：GPIO_200管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_021_UNION */
#define SOC_IOC_AO_IOMG_021_ADDR(base)                ((base) + (0x054))

/* 寄存器说明：GPIO_201管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_022_UNION */
#define SOC_IOC_AO_IOMG_022_ADDR(base)                ((base) + (0x058))

/* 寄存器说明：GPIO_202管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_023_UNION */
#define SOC_IOC_AO_IOMG_023_ADDR(base)                ((base) + (0x05C))

/* 寄存器说明：GPIO_203管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_024_UNION */
#define SOC_IOC_AO_IOMG_024_ADDR(base)                ((base) + (0x060))

/* 寄存器说明：GPIO_205管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_025_UNION */
#define SOC_IOC_AO_IOMG_025_ADDR(base)                ((base) + (0x064))

/* 寄存器说明：GPIO_206管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_026_UNION */
#define SOC_IOC_AO_IOMG_026_ADDR(base)                ((base) + (0x068))

/* 寄存器说明：GPIO_207管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_027_UNION */
#define SOC_IOC_AO_IOMG_027_ADDR(base)                ((base) + (0x06C))

/* 寄存器说明：GPIO_208管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_028_UNION */
#define SOC_IOC_AO_IOMG_028_ADDR(base)                ((base) + (0x070))

/* 寄存器说明：GPIO_209管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_029_UNION */
#define SOC_IOC_AO_IOMG_029_ADDR(base)                ((base) + (0x074))

/* 寄存器说明：GPIO_210管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_030_UNION */
#define SOC_IOC_AO_IOMG_030_ADDR(base)                ((base) + (0x078))

/* 寄存器说明：GPIO_211管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_031_UNION */
#define SOC_IOC_AO_IOMG_031_ADDR(base)                ((base) + (0x07C))

/* 寄存器说明：GPIO_212管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_032_UNION */
#define SOC_IOC_AO_IOMG_032_ADDR(base)                ((base) + (0x080))

/* 寄存器说明：GPIO_213管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_033_UNION */
#define SOC_IOC_AO_IOMG_033_ADDR(base)                ((base) + (0x084))

/* 寄存器说明：GPIO_214管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_034_UNION */
#define SOC_IOC_AO_IOMG_034_ADDR(base)                ((base) + (0x088))

/* 寄存器说明：ISP_GPIO03_PRTRB管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_035_UNION */
#define SOC_IOC_AO_IOMG_035_ADDR(base)                ((base) + (0x08C))

/* 寄存器说明：ISP_GPIO04_FTPWM管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_036_UNION */
#define SOC_IOC_AO_IOMG_036_ADDR(base)                ((base) + (0x090))

/* 寄存器说明：ISP_GPIO05_BKPWM管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_037_UNION */
#define SOC_IOC_AO_IOMG_037_ADDR(base)                ((base) + (0x094))

/* 寄存器说明：ISP_GPIO09_ENC管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_038_UNION */
#define SOC_IOC_AO_IOMG_038_ADDR(base)                ((base) + (0x098))

/* 寄存器说明：ISP_GPIO07_ENA管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_039_UNION */
#define SOC_IOC_AO_IOMG_039_ADDR(base)                ((base) + (0x09C))

/* 寄存器说明：ISP_GPIO08_ENB管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_040_UNION */
#define SOC_IOC_AO_IOMG_040_ADDR(base)                ((base) + (0x0A0))

/* 寄存器说明：ISP_GPIO11管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_041_UNION */
#define SOC_IOC_AO_IOMG_041_ADDR(base)                ((base) + (0x0A4))

/* 寄存器说明：ISP_GPIO12管脚复用控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOMG_042_UNION */
#define SOC_IOC_AO_IOMG_042_ADDR(base)                ((base) + (0x0A8))

/* 寄存器说明：GPIO_176功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_000_UNION */
#define SOC_IOC_AO_IOCG_000_ADDR(base)                ((base) + (0x800))

/* 寄存器说明：GPIO_177功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_001_UNION */
#define SOC_IOC_AO_IOCG_001_ADDR(base)                ((base) + (0x804))

/* 寄存器说明：SYSCLK_EN功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_002_UNION */
#define SOC_IOC_AO_IOCG_002_ADDR(base)                ((base) + (0x808))

/* 寄存器说明：CLK_OUT0功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_003_UNION */
#define SOC_IOC_AO_IOCG_003_ADDR(base)                ((base) + (0x80C))

/* 寄存器说明：CLK_OUT1功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_004_UNION */
#define SOC_IOC_AO_IOCG_004_ADDR(base)                ((base) + (0x810))

/* 寄存器说明：BLPWM_CABC功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_005_UNION */
#define SOC_IOC_AO_IOCG_005_ADDR(base)                ((base) + (0x814))

/* 寄存器说明：BLPWM_BL功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_006_UNION */
#define SOC_IOC_AO_IOCG_006_ADDR(base)                ((base) + (0x818))

/* 寄存器说明：I2C0_SCL功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_007_UNION */
#define SOC_IOC_AO_IOCG_007_ADDR(base)                ((base) + (0x81C))

/* 寄存器说明：I2C0_SDA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_008_UNION */
#define SOC_IOC_AO_IOCG_008_ADDR(base)                ((base) + (0x820))

/* 寄存器说明：I2C1_SCL功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_009_UNION */
#define SOC_IOC_AO_IOCG_009_ADDR(base)                ((base) + (0x824))

/* 寄存器说明：I2C1_SDA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_010_UNION */
#define SOC_IOC_AO_IOCG_010_ADDR(base)                ((base) + (0x828))

/* 寄存器说明：I2C2_SCL功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_011_UNION */
#define SOC_IOC_AO_IOCG_011_ADDR(base)                ((base) + (0x82C))

/* 寄存器说明：I2C2_SDA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_012_UNION */
#define SOC_IOC_AO_IOCG_012_ADDR(base)                ((base) + (0x830))

/* 寄存器说明：SLIMBUS_CLK功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_013_UNION */
#define SOC_IOC_AO_IOCG_013_ADDR(base)                ((base) + (0x834))

/* 寄存器说明：SLIMBUS_DATA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_014_UNION */
#define SOC_IOC_AO_IOCG_014_ADDR(base)                ((base) + (0x838))

/* 寄存器说明：GPIO_191功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_015_UNION */
#define SOC_IOC_AO_IOCG_015_ADDR(base)                ((base) + (0x83C))

/* 寄存器说明：GPIO_192功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_016_UNION */
#define SOC_IOC_AO_IOCG_016_ADDR(base)                ((base) + (0x840))

/* 寄存器说明：GPIO_193功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_017_UNION */
#define SOC_IOC_AO_IOCG_017_ADDR(base)                ((base) + (0x844))

/* 寄存器说明：GPIO_194功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_018_UNION */
#define SOC_IOC_AO_IOCG_018_ADDR(base)                ((base) + (0x848))

/* 寄存器说明：GPIO_195功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_019_UNION */
#define SOC_IOC_AO_IOCG_019_ADDR(base)                ((base) + (0x84C))

/* 寄存器说明：GPIO_196功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_020_UNION */
#define SOC_IOC_AO_IOCG_020_ADDR(base)                ((base) + (0x850))

/* 寄存器说明：GPIO_197功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_021_UNION */
#define SOC_IOC_AO_IOCG_021_ADDR(base)                ((base) + (0x854))

/* 寄存器说明：GPIO_198功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_022_UNION */
#define SOC_IOC_AO_IOCG_022_ADDR(base)                ((base) + (0x858))

/* 寄存器说明：GPIO_199功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_023_UNION */
#define SOC_IOC_AO_IOCG_023_ADDR(base)                ((base) + (0x85C))

/* 寄存器说明：GPIO_200功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_024_UNION */
#define SOC_IOC_AO_IOCG_024_ADDR(base)                ((base) + (0x860))

/* 寄存器说明：GPIO_201功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_025_UNION */
#define SOC_IOC_AO_IOCG_025_ADDR(base)                ((base) + (0x864))

/* 寄存器说明：GPIO_202功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_026_UNION */
#define SOC_IOC_AO_IOCG_026_ADDR(base)                ((base) + (0x868))

/* 寄存器说明：GPIO_203功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_027_UNION */
#define SOC_IOC_AO_IOCG_027_ADDR(base)                ((base) + (0x86C))

/* 寄存器说明：GPIO_204功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_028_UNION */
#define SOC_IOC_AO_IOCG_028_ADDR(base)                ((base) + (0x870))

/* 寄存器说明：GPIO_205功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_029_UNION */
#define SOC_IOC_AO_IOCG_029_ADDR(base)                ((base) + (0x874))

/* 寄存器说明：GPIO_206功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_030_UNION */
#define SOC_IOC_AO_IOCG_030_ADDR(base)                ((base) + (0x878))

/* 寄存器说明：GPIO_207功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_031_UNION */
#define SOC_IOC_AO_IOCG_031_ADDR(base)                ((base) + (0x87C))

/* 寄存器说明：GPIO_208功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_032_UNION */
#define SOC_IOC_AO_IOCG_032_ADDR(base)                ((base) + (0x880))

/* 寄存器说明：GPIO_209功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_033_UNION */
#define SOC_IOC_AO_IOCG_033_ADDR(base)                ((base) + (0x884))

/* 寄存器说明：GPIO_210功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_034_UNION */
#define SOC_IOC_AO_IOCG_034_ADDR(base)                ((base) + (0x888))

/* 寄存器说明：GPIO_211功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_035_UNION */
#define SOC_IOC_AO_IOCG_035_ADDR(base)                ((base) + (0x88C))

/* 寄存器说明：GPIO_212功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_036_UNION */
#define SOC_IOC_AO_IOCG_036_ADDR(base)                ((base) + (0x890))

/* 寄存器说明：GPIO_213功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_037_UNION */
#define SOC_IOC_AO_IOCG_037_ADDR(base)                ((base) + (0x894))

/* 寄存器说明：GPIO_214功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_038_UNION */
#define SOC_IOC_AO_IOCG_038_ADDR(base)                ((base) + (0x898))

/* 寄存器说明：ISP_GPIO03_PRTRB功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_039_UNION */
#define SOC_IOC_AO_IOCG_039_ADDR(base)                ((base) + (0x89C))

/* 寄存器说明：ISP_GPIO04_FTPWM功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_040_UNION */
#define SOC_IOC_AO_IOCG_040_ADDR(base)                ((base) + (0x8A0))

/* 寄存器说明：ISP_GPIO05_BKPWM功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_041_UNION */
#define SOC_IOC_AO_IOCG_041_ADDR(base)                ((base) + (0x8A4))

/* 寄存器说明：ISP_GPIO09_ENC功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_042_UNION */
#define SOC_IOC_AO_IOCG_042_ADDR(base)                ((base) + (0x8A8))

/* 寄存器说明：ISP_GPIO07_ENA功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_043_UNION */
#define SOC_IOC_AO_IOCG_043_ADDR(base)                ((base) + (0x8AC))

/* 寄存器说明：ISP_GPIO08_ENB功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_044_UNION */
#define SOC_IOC_AO_IOCG_044_ADDR(base)                ((base) + (0x8B0))

/* 寄存器说明：ISP_GPIO11功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_045_UNION */
#define SOC_IOC_AO_IOCG_045_ADDR(base)                ((base) + (0x8B4))

/* 寄存器说明：ISP_GPIO12功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_046_UNION */
#define SOC_IOC_AO_IOCG_046_ADDR(base)                ((base) + (0x8B8))

/* 寄存器说明：GPIO_223功能管脚控制寄存器。&#13;
   位域定义UNION结构:  SOC_IOC_AO_IOCG_047_UNION */
#define SOC_IOC_AO_IOCG_047_ADDR(base)                ((base) + (0x8BC))





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
 结构名    : SOC_IOC_AO_IOMG_000_UNION
 结构说明  : IOMG_000 寄存器结构定义。地址偏移量:0x000，初值:0x00000001，宽度:32
 寄存器说明: SYSCLK_EN管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_000 : 1;  /* bit[0]   : SYSCLK_EN管脚的具体复用情况。
                                                   0：GPIO_178；
                                                   1：SYSCLK_EN。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_000_UNION;
#endif
#define SOC_IOC_AO_IOMG_000_iomg_000_START  (0)
#define SOC_IOC_AO_IOMG_000_iomg_000_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_001_UNION
 结构说明  : IOMG_001 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: CLK_OUT0管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_001 : 1;  /* bit[0]   : CLK_OUT0管脚的具体复用情况。
                                                   0：GPIO_179；
                                                   1：CLK_OUT0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_001_UNION;
#endif
#define SOC_IOC_AO_IOMG_001_iomg_001_START  (0)
#define SOC_IOC_AO_IOMG_001_iomg_001_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_002_UNION
 结构说明  : IOMG_002 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: CLK_OUT1管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_002 : 2;  /* bit[0-1] : CLK_OUT1管脚的具体复用情况。
                                                   00：GPIO_180；
                                                   01：CLK_OUT1；
                                                   10：GPIO_000_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_002_UNION;
#endif
#define SOC_IOC_AO_IOMG_002_iomg_002_START  (0)
#define SOC_IOC_AO_IOMG_002_iomg_002_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_003_UNION
 结构说明  : IOMG_003 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: BLPWM_CABC管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_003 : 2;  /* bit[0-1] : BLPWM_CABC管脚的具体复用情况。
                                                   00：GPIO_181；
                                                   01：BLPWM_CABC；
                                                   10：GPIO_000_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_003_UNION;
#endif
#define SOC_IOC_AO_IOMG_003_iomg_003_START  (0)
#define SOC_IOC_AO_IOMG_003_iomg_003_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_004_UNION
 结构说明  : IOMG_004 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: BLPWM_BL管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_004 : 2;  /* bit[0-1] : BLPWM_BL管脚的具体复用情况。
                                                   00：GPIO_182；
                                                   01：BLPWM_BL；
                                                   10：GPIO_001_SH；
                                                   11：PWM_OUT0。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_004_UNION;
#endif
#define SOC_IOC_AO_IOMG_004_iomg_004_START  (0)
#define SOC_IOC_AO_IOMG_004_iomg_004_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_005_UNION
 结构说明  : IOMG_005 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: I2C0_SCL管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_005 : 1;  /* bit[0]   : I2C0_SCL管脚的具体复用情况。
                                                   0：GPIO_183；
                                                   1：I2C0_SCL。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_005_UNION;
#endif
#define SOC_IOC_AO_IOMG_005_iomg_005_START  (0)
#define SOC_IOC_AO_IOMG_005_iomg_005_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_006_UNION
 结构说明  : IOMG_006 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: I2C0_SDA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_006 : 1;  /* bit[0]   : I2C0_SDA管脚的具体复用情况。
                                                   0：GPIO_184；
                                                   1：I2C0_SDA。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_006_UNION;
#endif
#define SOC_IOC_AO_IOMG_006_iomg_006_START  (0)
#define SOC_IOC_AO_IOMG_006_iomg_006_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_007_UNION
 结构说明  : IOMG_007 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: I2C1_SCL管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_007 : 2;  /* bit[0-1] : I2C1_SCL管脚的具体复用情况。
                                                   00：GPIO_185；
                                                   01：I2C1_SCL；
                                                   10：GPIO_001_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_007_UNION;
#endif
#define SOC_IOC_AO_IOMG_007_iomg_007_START  (0)
#define SOC_IOC_AO_IOMG_007_iomg_007_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_008_UNION
 结构说明  : IOMG_008 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: I2C1_SDA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_008 : 2;  /* bit[0-1] : I2C1_SDA管脚的具体复用情况。
                                                   00：GPIO_186；
                                                   01：I2C1_SDA；
                                                   11：CODEC_SSI；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_008_UNION;
#endif
#define SOC_IOC_AO_IOMG_008_iomg_008_START  (0)
#define SOC_IOC_AO_IOMG_008_iomg_008_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_009_UNION
 结构说明  : IOMG_009 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: I2C2_SCL管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_009 : 1;  /* bit[0]   : I2C2_SCL管脚的具体复用情况。
                                                   0：GPIO_187；
                                                   1：I2C2_SCL。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_009_UNION;
#endif
#define SOC_IOC_AO_IOMG_009_iomg_009_START  (0)
#define SOC_IOC_AO_IOMG_009_iomg_009_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_010_UNION
 结构说明  : IOMG_010 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: I2C2_SDA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_010 : 1;  /* bit[0]   : I2C2_SDA管脚的具体复用情况。
                                                   0：GPIO_188；
                                                   1：I2C2_SDA。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_010_UNION;
#endif
#define SOC_IOC_AO_IOMG_010_iomg_010_START  (0)
#define SOC_IOC_AO_IOMG_010_iomg_010_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_011_UNION
 结构说明  : IOMG_011 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: SLIMBUS_CLK管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_011 : 3;  /* bit[0-2] : SLIMBUS_CLK管脚的具体复用情况。
                                                   000：GPIO_189；
                                                   001：SLIMBUS_CLK；
                                                   011：I2S0_DI；
                                                   100：UART7_RXD；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_011_UNION;
#endif
#define SOC_IOC_AO_IOMG_011_iomg_011_START  (0)
#define SOC_IOC_AO_IOMG_011_iomg_011_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_012_UNION
 结构说明  : IOMG_012 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: SLIMBUS_DATA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_012 : 3;  /* bit[0-2] : SLIMBUS_DATA管脚的具体复用情况。
                                                   000：GPIO_190；
                                                   001：SLIMBUS_DATA；
                                                   011：I2S0_DO；
                                                   100：UART7_TXD；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_012_UNION;
#endif
#define SOC_IOC_AO_IOMG_012_iomg_012_START  (0)
#define SOC_IOC_AO_IOMG_012_iomg_012_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_013_UNION
 结构说明  : IOMG_013 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: GPIO_192管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_013 : 2;  /* bit[0-1] : GPIO_192管脚的具体复用情况。
                                                   00：GPIO_192；
                                                   01：I2S0_XCLK；
                                                   10：GPIO_002_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_013_UNION;
#endif
#define SOC_IOC_AO_IOMG_013_iomg_013_START  (0)
#define SOC_IOC_AO_IOMG_013_iomg_013_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_014_UNION
 结构说明  : IOMG_014 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: GPIO_193管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_014 : 2;  /* bit[0-1] : GPIO_193管脚的具体复用情况。
                                                   00：GPIO_193；
                                                   01：I2S0_XFS；
                                                   10：GPIO_003_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_014_UNION;
#endif
#define SOC_IOC_AO_IOMG_014_iomg_014_START  (0)
#define SOC_IOC_AO_IOMG_014_iomg_014_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_015_UNION
 结构说明  : IOMG_015 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: GPIO_194管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_015 : 1;  /* bit[0]   : GPIO_194管脚的具体复用情况。
                                                   0：GPIO_194；
                                                   1：I2S2_DI。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_015_UNION;
#endif
#define SOC_IOC_AO_IOMG_015_iomg_015_START  (0)
#define SOC_IOC_AO_IOMG_015_iomg_015_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_016_UNION
 结构说明  : IOMG_016 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: GPIO_195管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_016 : 1;  /* bit[0]   : GPIO_195管脚的具体复用情况。
                                                   0：GPIO_195；
                                                   1：I2S2_DO。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_016_UNION;
#endif
#define SOC_IOC_AO_IOMG_016_iomg_016_START  (0)
#define SOC_IOC_AO_IOMG_016_iomg_016_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_017_UNION
 结构说明  : IOMG_017 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: GPIO_196管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_017 : 1;  /* bit[0]   : GPIO_196管脚的具体复用情况。
                                                   0：GPIO_196；
                                                   1：I2S2_XCLK。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_017_UNION;
#endif
#define SOC_IOC_AO_IOMG_017_iomg_017_START  (0)
#define SOC_IOC_AO_IOMG_017_iomg_017_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_018_UNION
 结构说明  : IOMG_018 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: GPIO_197管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_018 : 1;  /* bit[0]   : GPIO_197管脚的具体复用情况。
                                                   0：GPIO_197；
                                                   1：I2S2_XFS。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_018_UNION;
#endif
#define SOC_IOC_AO_IOMG_018_iomg_018_START  (0)
#define SOC_IOC_AO_IOMG_018_iomg_018_END    (0)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_019_UNION
 结构说明  : IOMG_019 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: GPIO_198管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_019 : 2;  /* bit[0-1] : GPIO_198管脚的具体复用情况。
                                                   00：GPIO_198；
                                                   10：GPIO_004_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_019_UNION;
#endif
#define SOC_IOC_AO_IOMG_019_iomg_019_START  (0)
#define SOC_IOC_AO_IOMG_019_iomg_019_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_020_UNION
 结构说明  : IOMG_020 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: GPIO_199管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_020 : 2;  /* bit[0-1] : GPIO_199管脚的具体复用情况。
                                                   00：GPIO_199；
                                                   10：GPIO_005_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_020_UNION;
#endif
#define SOC_IOC_AO_IOMG_020_iomg_020_START  (0)
#define SOC_IOC_AO_IOMG_020_iomg_020_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_021_UNION
 结构说明  : IOMG_021 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: GPIO_200管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_021 : 2;  /* bit[0-1] : GPIO_200管脚的具体复用情况。
                                                   00：GPIO_200；
                                                   10：GPIO_006_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_021_UNION;
#endif
#define SOC_IOC_AO_IOMG_021_iomg_021_START  (0)
#define SOC_IOC_AO_IOMG_021_iomg_021_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_022_UNION
 结构说明  : IOMG_022 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: GPIO_201管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_022 : 2;  /* bit[0-1] : GPIO_201管脚的具体复用情况。
                                                   00：GPIO_201；
                                                   10：GPIO_007_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_022_UNION;
#endif
#define SOC_IOC_AO_IOMG_022_iomg_022_START  (0)
#define SOC_IOC_AO_IOMG_022_iomg_022_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_023_UNION
 结构说明  : IOMG_023 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: GPIO_202管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_023 : 2;  /* bit[0-1] : GPIO_202管脚的具体复用情况。
                                                   00：GPIO_202；
                                                   10：GPIO_008_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_023_UNION;
#endif
#define SOC_IOC_AO_IOMG_023_iomg_023_START  (0)
#define SOC_IOC_AO_IOMG_023_iomg_023_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_024_UNION
 结构说明  : IOMG_024 寄存器结构定义。地址偏移量:0x060，初值:0x00000001，宽度:32
 寄存器说明: GPIO_203管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_024 : 2;  /* bit[0-1] : GPIO_203管脚的具体复用情况。
                                                   00：GPIO_203；
                                                   01：CLKIN_AUX；
                                                   10：GPIO_009_SH；
                                                   其它：保留。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_024_UNION;
#endif
#define SOC_IOC_AO_IOMG_024_iomg_024_START  (0)
#define SOC_IOC_AO_IOMG_024_iomg_024_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_025_UNION
 结构说明  : IOMG_025 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: GPIO_205管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_025 : 3;  /* bit[0-2] : GPIO_205管脚的具体复用情况。
                                                   000：GPIO_205；
                                                   001：I2S3_DI；
                                                   010：GPIO_010_SH；
                                                   110：FAC_TEST16；
                                                   111：FAC_TEST16；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_025_UNION;
#endif
#define SOC_IOC_AO_IOMG_025_iomg_025_START  (0)
#define SOC_IOC_AO_IOMG_025_iomg_025_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_026_UNION
 结构说明  : IOMG_026 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: GPIO_206管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_026 : 3;  /* bit[0-2] : GPIO_206管脚的具体复用情况。
                                                   000：GPIO_206；
                                                   001：I2S3_DO；
                                                   010：GPIO_011_SH；
                                                   110：FAC_TEST17；
                                                   111：FAC_TEST17；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_026_UNION;
#endif
#define SOC_IOC_AO_IOMG_026_iomg_026_START  (0)
#define SOC_IOC_AO_IOMG_026_iomg_026_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_027_UNION
 结构说明  : IOMG_027 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: GPIO_207管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_027 : 3;  /* bit[0-2] : GPIO_207管脚的具体复用情况。
                                                   000：GPIO_207；
                                                   001：I2S3_XCLK；
                                                   010：GPIO_012_SH；
                                                   110：FAC_TEST18；
                                                   111：FAC_TEST18；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_027_UNION;
#endif
#define SOC_IOC_AO_IOMG_027_iomg_027_START  (0)
#define SOC_IOC_AO_IOMG_027_iomg_027_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_028_UNION
 结构说明  : IOMG_028 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: GPIO_208管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_028 : 3;  /* bit[0-2] : GPIO_208管脚的具体复用情况。
                                                   000：GPIO_208；
                                                   001：I2S3_XFS；
                                                   010：GPIO_013_SH；
                                                   110：FAC_TEST19；
                                                   111：FAC_TEST19；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_028_UNION;
#endif
#define SOC_IOC_AO_IOMG_028_iomg_028_START  (0)
#define SOC_IOC_AO_IOMG_028_iomg_028_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_029_UNION
 结构说明  : IOMG_029 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: GPIO_209管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_029 : 3;  /* bit[0-2] : GPIO_209管脚的具体复用情况。
                                                   000：GPIO_209；
                                                   001：GPIO_ASP1；
                                                   010：GPIO_014_SH；
                                                   110：FAC_TEST20；
                                                   111：FAC_TEST20；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_029_UNION;
#endif
#define SOC_IOC_AO_IOMG_029_iomg_029_START  (0)
#define SOC_IOC_AO_IOMG_029_iomg_029_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_030_UNION
 结构说明  : IOMG_030 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: GPIO_210管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_030 : 3;  /* bit[0-2] : GPIO_210管脚的具体复用情况。
                                                   000：GPIO_210；
                                                   001：GPIO_ASP2；
                                                   010：GPIO_015_SH；
                                                   110：FAC_TEST21；
                                                   111：FAC_TEST21；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_030_UNION;
#endif
#define SOC_IOC_AO_IOMG_030_iomg_030_START  (0)
#define SOC_IOC_AO_IOMG_030_iomg_030_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_031_UNION
 结构说明  : IOMG_031 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: GPIO_211管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_031 : 3;  /* bit[0-2] : GPIO_211管脚的具体复用情况。
                                                   000：GPIO_211；
                                                   001：GPIO_ASP0；
                                                   010：GPIO_016_SH；
                                                   110：FAC_TEST22；
                                                   111：FAC_TEST22；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_031_UNION;
#endif
#define SOC_IOC_AO_IOMG_031_iomg_031_START  (0)
#define SOC_IOC_AO_IOMG_031_iomg_031_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_032_UNION
 结构说明  : IOMG_032 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: GPIO_212管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_032 : 3;  /* bit[0-2] : GPIO_212管脚的具体复用情况。
                                                   000：GPIO_212；
                                                   001：GPIO_ASP3；
                                                   010：GPIO_017_SH；
                                                   110：FAC_TEST23；
                                                   111：FAC_TEST23；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_032_UNION;
#endif
#define SOC_IOC_AO_IOMG_032_iomg_032_START  (0)
#define SOC_IOC_AO_IOMG_032_iomg_032_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_033_UNION
 结构说明  : IOMG_033 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: GPIO_213管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_033 : 3;  /* bit[0-2] : GPIO_213管脚的具体复用情况。
                                                   000：GPIO_213；
                                                   001：GPIO_ASP4；
                                                   010：GPIO_018_SH；
                                                   110：FAC_TEST24；
                                                   111：FAC_TEST24；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_033_UNION;
#endif
#define SOC_IOC_AO_IOMG_033_iomg_033_START  (0)
#define SOC_IOC_AO_IOMG_033_iomg_033_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_034_UNION
 结构说明  : IOMG_034 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: GPIO_214管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_034 : 3;  /* bit[0-2] : GPIO_214管脚的具体复用情况。
                                                   000：GPIO_214；
                                                   010：GPIO_019_SH；
                                                   110：FAC_TEST25；
                                                   111：FAC_TEST25；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_034_UNION;
#endif
#define SOC_IOC_AO_IOMG_034_iomg_034_START  (0)
#define SOC_IOC_AO_IOMG_034_iomg_034_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_035_UNION
 结构说明  : IOMG_035 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO03_PRTRB管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_035 : 2;  /* bit[0-1] : ISP_GPIO03_PRTRB管脚的具体复用情况。
                                                   00：GPIO_215；
                                                   01：SPI2_CLK；
                                                   10：GPIO_020_SH；
                                                   11：ISP_GPIO03_PRTRB。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_035_UNION;
#endif
#define SOC_IOC_AO_IOMG_035_iomg_035_START  (0)
#define SOC_IOC_AO_IOMG_035_iomg_035_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_036_UNION
 结构说明  : IOMG_036 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO04_FTPWM管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_036 : 2;  /* bit[0-1] : ISP_GPIO04_FTPWM管脚的具体复用情况。
                                                   00：GPIO_216；
                                                   01：SPI2_DI；
                                                   10：GPIO_021_SH；
                                                   11：ISP_GPIO04_FTPWM。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_036_UNION;
#endif
#define SOC_IOC_AO_IOMG_036_iomg_036_START  (0)
#define SOC_IOC_AO_IOMG_036_iomg_036_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_037_UNION
 结构说明  : IOMG_037 寄存器结构定义。地址偏移量:0x094，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO05_BKPWM管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_037 : 2;  /* bit[0-1] : ISP_GPIO05_BKPWM管脚的具体复用情况。
                                                   00：GPIO_217；
                                                   01：SPI2_DO；
                                                   10：GPIO_022_SH；
                                                   11：ISP_GPIO05_BKPWM。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_037_UNION;
#endif
#define SOC_IOC_AO_IOMG_037_iomg_037_START  (0)
#define SOC_IOC_AO_IOMG_037_iomg_037_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_038_UNION
 结构说明  : IOMG_038 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO09_ENC管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_038 : 2;  /* bit[0-1] : ISP_GPIO09_ENC管脚的具体复用情况。
                                                   00：GPIO_218；
                                                   01：SPI2_CS_N；
                                                   10：GPIO_023_SH；
                                                   11：ISP_GPIO09_ENC。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_038_UNION;
#endif
#define SOC_IOC_AO_IOMG_038_iomg_038_START  (0)
#define SOC_IOC_AO_IOMG_038_iomg_038_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_039_UNION
 结构说明  : IOMG_039 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO07_ENA管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_039 : 3;  /* bit[0-2] : ISP_GPIO07_ENA管脚的具体复用情况。
                                                   000：GPIO_219；
                                                   001：UART8_CTS_N；
                                                   010：GPIO_024_SH；
                                                   011：ISP_GPIO07_ENA；
                                                   100：I2C6_SDA；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_039_UNION;
#endif
#define SOC_IOC_AO_IOMG_039_iomg_039_START  (0)
#define SOC_IOC_AO_IOMG_039_iomg_039_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_040_UNION
 结构说明  : IOMG_040 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO08_ENB管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_040 : 3;  /* bit[0-2] : ISP_GPIO08_ENB管脚的具体复用情况。
                                                   000：GPIO_220；
                                                   001：UART8_RTS_N；
                                                   010：GPIO_025_SH；
                                                   011：ISP_GPIO08_ENB；
                                                   100：I2C6_SCL；
                                                   其它：保留。 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_040_UNION;
#endif
#define SOC_IOC_AO_IOMG_040_iomg_040_START  (0)
#define SOC_IOC_AO_IOMG_040_iomg_040_END    (2)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_041_UNION
 结构说明  : IOMG_041 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO11管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_041 : 2;  /* bit[0-1] : ISP_GPIO11管脚的具体复用情况。
                                                   00：GPIO_221；
                                                   01：UART8_RXD；
                                                   10：GPIO_026_SH；
                                                   11：ISP_GPIO11。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_041_UNION;
#endif
#define SOC_IOC_AO_IOMG_041_iomg_041_START  (0)
#define SOC_IOC_AO_IOMG_041_iomg_041_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOMG_042_UNION
 结构说明  : IOMG_042 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: ISP_GPIO12管脚复用控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_042 : 2;  /* bit[0-1] : ISP_GPIO12管脚的具体复用情况。
                                                   00：GPIO_222；
                                                   01：UART8_TXD；
                                                   10：GPIO_027_SH；
                                                   11：ISP_GPIO12。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOMG_042_UNION;
#endif
#define SOC_IOC_AO_IOMG_042_iomg_042_START  (0)
#define SOC_IOC_AO_IOMG_042_iomg_042_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_000_UNION
 结构说明  : IOCG_000 寄存器结构定义。地址偏移量:0x800，初值:0x00000002，宽度:32
 寄存器说明: GPIO_176功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_000_pu : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_000_pd : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_000_UNION;
#endif
#define SOC_IOC_AO_IOCG_000_iocg_000_pu_START  (0)
#define SOC_IOC_AO_IOCG_000_iocg_000_pu_END    (0)
#define SOC_IOC_AO_IOCG_000_iocg_000_pd_START  (1)
#define SOC_IOC_AO_IOCG_000_iocg_000_pd_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_001_UNION
 结构说明  : IOCG_001 寄存器结构定义。地址偏移量:0x804，初值:0x00000001，宽度:32
 寄存器说明: GPIO_177功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_001_pu : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_001_pd : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_001_UNION;
#endif
#define SOC_IOC_AO_IOCG_001_iocg_001_pu_START  (0)
#define SOC_IOC_AO_IOCG_001_iocg_001_pu_END    (0)
#define SOC_IOC_AO_IOCG_001_iocg_001_pd_START  (1)
#define SOC_IOC_AO_IOCG_001_iocg_001_pd_END    (1)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_002_UNION
 结构说明  : IOCG_002 寄存器结构定义。地址偏移量:0x808，初值:0x00000010，宽度:32
 寄存器说明: SYSCLK_EN功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_002_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_002_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_002_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_002_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_002_UNION;
#endif
#define SOC_IOC_AO_IOCG_002_iocg_002_pu_START   (0)
#define SOC_IOC_AO_IOCG_002_iocg_002_pu_END     (0)
#define SOC_IOC_AO_IOCG_002_iocg_002_pd_START   (1)
#define SOC_IOC_AO_IOCG_002_iocg_002_pd_END     (1)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds0_START  (4)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds0_END    (4)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds1_START  (5)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds1_END    (5)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds2_START  (6)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds2_END    (6)
#define SOC_IOC_AO_IOCG_002_iocg_002_sr_START   (7)
#define SOC_IOC_AO_IOCG_002_iocg_002_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_003_UNION
 结构说明  : IOCG_003 寄存器结构定义。地址偏移量:0x80C，初值:0x00000012，宽度:32
 寄存器说明: CLK_OUT0功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_003_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_003_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_003_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_003_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_003_UNION;
#endif
#define SOC_IOC_AO_IOCG_003_iocg_003_pu_START   (0)
#define SOC_IOC_AO_IOCG_003_iocg_003_pu_END     (0)
#define SOC_IOC_AO_IOCG_003_iocg_003_pd_START   (1)
#define SOC_IOC_AO_IOCG_003_iocg_003_pd_END     (1)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds0_START  (4)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds0_END    (4)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds1_START  (5)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds1_END    (5)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds2_START  (6)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds2_END    (6)
#define SOC_IOC_AO_IOCG_003_iocg_003_sr_START   (7)
#define SOC_IOC_AO_IOCG_003_iocg_003_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_004_UNION
 结构说明  : IOCG_004 寄存器结构定义。地址偏移量:0x810，初值:0x00000012，宽度:32
 寄存器说明: CLK_OUT1功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_004_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_004_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_004_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_004_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_004_UNION;
#endif
#define SOC_IOC_AO_IOCG_004_iocg_004_pu_START   (0)
#define SOC_IOC_AO_IOCG_004_iocg_004_pu_END     (0)
#define SOC_IOC_AO_IOCG_004_iocg_004_pd_START   (1)
#define SOC_IOC_AO_IOCG_004_iocg_004_pd_END     (1)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds0_START  (4)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds0_END    (4)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds1_START  (5)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds1_END    (5)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds2_START  (6)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds2_END    (6)
#define SOC_IOC_AO_IOCG_004_iocg_004_sr_START   (7)
#define SOC_IOC_AO_IOCG_004_iocg_004_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_005_UNION
 结构说明  : IOCG_005 寄存器结构定义。地址偏移量:0x814，初值:0x00000012，宽度:32
 寄存器说明: BLPWM_CABC功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_005_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_005_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_005_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_005_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_005_UNION;
#endif
#define SOC_IOC_AO_IOCG_005_iocg_005_pu_START   (0)
#define SOC_IOC_AO_IOCG_005_iocg_005_pu_END     (0)
#define SOC_IOC_AO_IOCG_005_iocg_005_pd_START   (1)
#define SOC_IOC_AO_IOCG_005_iocg_005_pd_END     (1)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds0_START  (4)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds0_END    (4)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds1_START  (5)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds1_END    (5)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds2_START  (6)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds2_END    (6)
#define SOC_IOC_AO_IOCG_005_iocg_005_sr_START   (7)
#define SOC_IOC_AO_IOCG_005_iocg_005_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_006_UNION
 结构说明  : IOCG_006 寄存器结构定义。地址偏移量:0x818，初值:0x00000012，宽度:32
 寄存器说明: BLPWM_BL功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_006_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_006_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_006_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_006_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_006_UNION;
#endif
#define SOC_IOC_AO_IOCG_006_iocg_006_pu_START   (0)
#define SOC_IOC_AO_IOCG_006_iocg_006_pu_END     (0)
#define SOC_IOC_AO_IOCG_006_iocg_006_pd_START   (1)
#define SOC_IOC_AO_IOCG_006_iocg_006_pd_END     (1)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds0_START  (4)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds0_END    (4)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds1_START  (5)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds1_END    (5)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds2_START  (6)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds2_END    (6)
#define SOC_IOC_AO_IOCG_006_iocg_006_sr_START   (7)
#define SOC_IOC_AO_IOCG_006_iocg_006_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_007_UNION
 结构说明  : IOCG_007 寄存器结构定义。地址偏移量:0x81C，初值:0x00000012，宽度:32
 寄存器说明: I2C0_SCL功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_007_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_007_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_007_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_007_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_007_UNION;
#endif
#define SOC_IOC_AO_IOCG_007_iocg_007_pu_START   (0)
#define SOC_IOC_AO_IOCG_007_iocg_007_pu_END     (0)
#define SOC_IOC_AO_IOCG_007_iocg_007_pd_START   (1)
#define SOC_IOC_AO_IOCG_007_iocg_007_pd_END     (1)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds0_START  (4)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds0_END    (4)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds1_START  (5)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds1_END    (5)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds2_START  (6)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds2_END    (6)
#define SOC_IOC_AO_IOCG_007_iocg_007_sr_START   (7)
#define SOC_IOC_AO_IOCG_007_iocg_007_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_008_UNION
 结构说明  : IOCG_008 寄存器结构定义。地址偏移量:0x820，初值:0x00000012，宽度:32
 寄存器说明: I2C0_SDA功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_008_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_008_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_008_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_008_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_008_UNION;
#endif
#define SOC_IOC_AO_IOCG_008_iocg_008_pu_START   (0)
#define SOC_IOC_AO_IOCG_008_iocg_008_pu_END     (0)
#define SOC_IOC_AO_IOCG_008_iocg_008_pd_START   (1)
#define SOC_IOC_AO_IOCG_008_iocg_008_pd_END     (1)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds0_START  (4)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds0_END    (4)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds1_START  (5)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds1_END    (5)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds2_START  (6)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds2_END    (6)
#define SOC_IOC_AO_IOCG_008_iocg_008_sr_START   (7)
#define SOC_IOC_AO_IOCG_008_iocg_008_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_009_UNION
 结构说明  : IOCG_009 寄存器结构定义。地址偏移量:0x824，初值:0x00000012，宽度:32
 寄存器说明: I2C1_SCL功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_009_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_009_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_009_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_009_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_009_UNION;
#endif
#define SOC_IOC_AO_IOCG_009_iocg_009_pu_START   (0)
#define SOC_IOC_AO_IOCG_009_iocg_009_pu_END     (0)
#define SOC_IOC_AO_IOCG_009_iocg_009_pd_START   (1)
#define SOC_IOC_AO_IOCG_009_iocg_009_pd_END     (1)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds0_START  (4)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds0_END    (4)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds1_START  (5)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds1_END    (5)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds2_START  (6)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds2_END    (6)
#define SOC_IOC_AO_IOCG_009_iocg_009_sr_START   (7)
#define SOC_IOC_AO_IOCG_009_iocg_009_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_010_UNION
 结构说明  : IOCG_010 寄存器结构定义。地址偏移量:0x828，初值:0x00000012，宽度:32
 寄存器说明: I2C1_SDA功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_010_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_010_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_010_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_010_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_010_UNION;
#endif
#define SOC_IOC_AO_IOCG_010_iocg_010_pu_START   (0)
#define SOC_IOC_AO_IOCG_010_iocg_010_pu_END     (0)
#define SOC_IOC_AO_IOCG_010_iocg_010_pd_START   (1)
#define SOC_IOC_AO_IOCG_010_iocg_010_pd_END     (1)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds0_START  (4)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds0_END    (4)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds1_START  (5)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds1_END    (5)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds2_START  (6)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds2_END    (6)
#define SOC_IOC_AO_IOCG_010_iocg_010_sr_START   (7)
#define SOC_IOC_AO_IOCG_010_iocg_010_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_011_UNION
 结构说明  : IOCG_011 寄存器结构定义。地址偏移量:0x82C，初值:0x00000012，宽度:32
 寄存器说明: I2C2_SCL功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_011_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_011_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_011_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_011_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_011_UNION;
#endif
#define SOC_IOC_AO_IOCG_011_iocg_011_pu_START   (0)
#define SOC_IOC_AO_IOCG_011_iocg_011_pu_END     (0)
#define SOC_IOC_AO_IOCG_011_iocg_011_pd_START   (1)
#define SOC_IOC_AO_IOCG_011_iocg_011_pd_END     (1)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds0_START  (4)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds0_END    (4)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds1_START  (5)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds1_END    (5)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds2_START  (6)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds2_END    (6)
#define SOC_IOC_AO_IOCG_011_iocg_011_sr_START   (7)
#define SOC_IOC_AO_IOCG_011_iocg_011_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_012_UNION
 结构说明  : IOCG_012 寄存器结构定义。地址偏移量:0x830，初值:0x00000012，宽度:32
 寄存器说明: I2C2_SDA功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_012_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_012_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_012_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_012_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_012_UNION;
#endif
#define SOC_IOC_AO_IOCG_012_iocg_012_pu_START   (0)
#define SOC_IOC_AO_IOCG_012_iocg_012_pu_END     (0)
#define SOC_IOC_AO_IOCG_012_iocg_012_pd_START   (1)
#define SOC_IOC_AO_IOCG_012_iocg_012_pd_END     (1)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds0_START  (4)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds0_END    (4)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds1_START  (5)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds1_END    (5)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds2_START  (6)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds2_END    (6)
#define SOC_IOC_AO_IOCG_012_iocg_012_sr_START   (7)
#define SOC_IOC_AO_IOCG_012_iocg_012_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_013_UNION
 结构说明  : IOCG_013 寄存器结构定义。地址偏移量:0x834，初值:0x00000012，宽度:32
 寄存器说明: SLIMBUS_CLK功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_013_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_013_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_013_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_013_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_013_UNION;
#endif
#define SOC_IOC_AO_IOCG_013_iocg_013_pu_START   (0)
#define SOC_IOC_AO_IOCG_013_iocg_013_pu_END     (0)
#define SOC_IOC_AO_IOCG_013_iocg_013_pd_START   (1)
#define SOC_IOC_AO_IOCG_013_iocg_013_pd_END     (1)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds0_START  (4)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds0_END    (4)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds1_START  (5)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds1_END    (5)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds2_START  (6)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds2_END    (6)
#define SOC_IOC_AO_IOCG_013_iocg_013_sr_START   (7)
#define SOC_IOC_AO_IOCG_013_iocg_013_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_014_UNION
 结构说明  : IOCG_014 寄存器结构定义。地址偏移量:0x838，初值:0x00000012，宽度:32
 寄存器说明: SLIMBUS_DATA功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_014_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_014_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_014_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_014_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_014_UNION;
#endif
#define SOC_IOC_AO_IOCG_014_iocg_014_pu_START   (0)
#define SOC_IOC_AO_IOCG_014_iocg_014_pu_END     (0)
#define SOC_IOC_AO_IOCG_014_iocg_014_pd_START   (1)
#define SOC_IOC_AO_IOCG_014_iocg_014_pd_END     (1)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds0_START  (4)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds0_END    (4)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds1_START  (5)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds1_END    (5)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds2_START  (6)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds2_END    (6)
#define SOC_IOC_AO_IOCG_014_iocg_014_sr_START   (7)
#define SOC_IOC_AO_IOCG_014_iocg_014_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_015_UNION
 结构说明  : IOCG_015 寄存器结构定义。地址偏移量:0x83C，初值:0x00000011，宽度:32
 寄存器说明: GPIO_191功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_015_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_015_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_015_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_015_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_015_UNION;
#endif
#define SOC_IOC_AO_IOCG_015_iocg_015_pu_START   (0)
#define SOC_IOC_AO_IOCG_015_iocg_015_pu_END     (0)
#define SOC_IOC_AO_IOCG_015_iocg_015_pd_START   (1)
#define SOC_IOC_AO_IOCG_015_iocg_015_pd_END     (1)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds0_START  (4)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds0_END    (4)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds1_START  (5)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds1_END    (5)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds2_START  (6)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds2_END    (6)
#define SOC_IOC_AO_IOCG_015_iocg_015_sr_START   (7)
#define SOC_IOC_AO_IOCG_015_iocg_015_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_016_UNION
 结构说明  : IOCG_016 寄存器结构定义。地址偏移量:0x840，初值:0x00000012，宽度:32
 寄存器说明: GPIO_192功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_016_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_016_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_016_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_016_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_016_UNION;
#endif
#define SOC_IOC_AO_IOCG_016_iocg_016_pu_START   (0)
#define SOC_IOC_AO_IOCG_016_iocg_016_pu_END     (0)
#define SOC_IOC_AO_IOCG_016_iocg_016_pd_START   (1)
#define SOC_IOC_AO_IOCG_016_iocg_016_pd_END     (1)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds0_START  (4)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds0_END    (4)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds1_START  (5)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds1_END    (5)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds2_START  (6)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds2_END    (6)
#define SOC_IOC_AO_IOCG_016_iocg_016_sr_START   (7)
#define SOC_IOC_AO_IOCG_016_iocg_016_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_017_UNION
 结构说明  : IOCG_017 寄存器结构定义。地址偏移量:0x844，初值:0x00000012，宽度:32
 寄存器说明: GPIO_193功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_017_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_017_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_017_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_017_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_017_UNION;
#endif
#define SOC_IOC_AO_IOCG_017_iocg_017_pu_START   (0)
#define SOC_IOC_AO_IOCG_017_iocg_017_pu_END     (0)
#define SOC_IOC_AO_IOCG_017_iocg_017_pd_START   (1)
#define SOC_IOC_AO_IOCG_017_iocg_017_pd_END     (1)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds0_START  (4)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds0_END    (4)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds1_START  (5)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds1_END    (5)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds2_START  (6)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds2_END    (6)
#define SOC_IOC_AO_IOCG_017_iocg_017_sr_START   (7)
#define SOC_IOC_AO_IOCG_017_iocg_017_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_018_UNION
 结构说明  : IOCG_018 寄存器结构定义。地址偏移量:0x848，初值:0x00000012，宽度:32
 寄存器说明: GPIO_194功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_018_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_018_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_018_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_018_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_018_UNION;
#endif
#define SOC_IOC_AO_IOCG_018_iocg_018_pu_START   (0)
#define SOC_IOC_AO_IOCG_018_iocg_018_pu_END     (0)
#define SOC_IOC_AO_IOCG_018_iocg_018_pd_START   (1)
#define SOC_IOC_AO_IOCG_018_iocg_018_pd_END     (1)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds0_START  (4)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds0_END    (4)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds1_START  (5)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds1_END    (5)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds2_START  (6)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds2_END    (6)
#define SOC_IOC_AO_IOCG_018_iocg_018_sr_START   (7)
#define SOC_IOC_AO_IOCG_018_iocg_018_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_019_UNION
 结构说明  : IOCG_019 寄存器结构定义。地址偏移量:0x84C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_195功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_019_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_019_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_019_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_019_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_019_UNION;
#endif
#define SOC_IOC_AO_IOCG_019_iocg_019_pu_START   (0)
#define SOC_IOC_AO_IOCG_019_iocg_019_pu_END     (0)
#define SOC_IOC_AO_IOCG_019_iocg_019_pd_START   (1)
#define SOC_IOC_AO_IOCG_019_iocg_019_pd_END     (1)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds0_START  (4)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds0_END    (4)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds1_START  (5)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds1_END    (5)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds2_START  (6)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds2_END    (6)
#define SOC_IOC_AO_IOCG_019_iocg_019_sr_START   (7)
#define SOC_IOC_AO_IOCG_019_iocg_019_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_020_UNION
 结构说明  : IOCG_020 寄存器结构定义。地址偏移量:0x850，初值:0x00000012，宽度:32
 寄存器说明: GPIO_196功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_020_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_020_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_020_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_020_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_020_UNION;
#endif
#define SOC_IOC_AO_IOCG_020_iocg_020_pu_START   (0)
#define SOC_IOC_AO_IOCG_020_iocg_020_pu_END     (0)
#define SOC_IOC_AO_IOCG_020_iocg_020_pd_START   (1)
#define SOC_IOC_AO_IOCG_020_iocg_020_pd_END     (1)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds0_START  (4)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds0_END    (4)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds1_START  (5)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds1_END    (5)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds2_START  (6)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds2_END    (6)
#define SOC_IOC_AO_IOCG_020_iocg_020_sr_START   (7)
#define SOC_IOC_AO_IOCG_020_iocg_020_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_021_UNION
 结构说明  : IOCG_021 寄存器结构定义。地址偏移量:0x854，初值:0x00000012，宽度:32
 寄存器说明: GPIO_197功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_021_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_021_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_021_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_021_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_021_UNION;
#endif
#define SOC_IOC_AO_IOCG_021_iocg_021_pu_START   (0)
#define SOC_IOC_AO_IOCG_021_iocg_021_pu_END     (0)
#define SOC_IOC_AO_IOCG_021_iocg_021_pd_START   (1)
#define SOC_IOC_AO_IOCG_021_iocg_021_pd_END     (1)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds0_START  (4)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds0_END    (4)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds1_START  (5)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds1_END    (5)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds2_START  (6)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds2_END    (6)
#define SOC_IOC_AO_IOCG_021_iocg_021_sr_START   (7)
#define SOC_IOC_AO_IOCG_021_iocg_021_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_022_UNION
 结构说明  : IOCG_022 寄存器结构定义。地址偏移量:0x858，初值:0x00000012，宽度:32
 寄存器说明: GPIO_198功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_022_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_022_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_022_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_022_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_022_UNION;
#endif
#define SOC_IOC_AO_IOCG_022_iocg_022_pu_START   (0)
#define SOC_IOC_AO_IOCG_022_iocg_022_pu_END     (0)
#define SOC_IOC_AO_IOCG_022_iocg_022_pd_START   (1)
#define SOC_IOC_AO_IOCG_022_iocg_022_pd_END     (1)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds0_START  (4)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds0_END    (4)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds1_START  (5)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds1_END    (5)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds2_START  (6)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds2_END    (6)
#define SOC_IOC_AO_IOCG_022_iocg_022_sr_START   (7)
#define SOC_IOC_AO_IOCG_022_iocg_022_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_023_UNION
 结构说明  : IOCG_023 寄存器结构定义。地址偏移量:0x85C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_199功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_023_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_023_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_023_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_023_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_023_UNION;
#endif
#define SOC_IOC_AO_IOCG_023_iocg_023_pu_START   (0)
#define SOC_IOC_AO_IOCG_023_iocg_023_pu_END     (0)
#define SOC_IOC_AO_IOCG_023_iocg_023_pd_START   (1)
#define SOC_IOC_AO_IOCG_023_iocg_023_pd_END     (1)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds0_START  (4)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds0_END    (4)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds1_START  (5)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds1_END    (5)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds2_START  (6)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds2_END    (6)
#define SOC_IOC_AO_IOCG_023_iocg_023_sr_START   (7)
#define SOC_IOC_AO_IOCG_023_iocg_023_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_024_UNION
 结构说明  : IOCG_024 寄存器结构定义。地址偏移量:0x860，初值:0x00000012，宽度:32
 寄存器说明: GPIO_200功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_024_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_024_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_024_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_024_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_024_UNION;
#endif
#define SOC_IOC_AO_IOCG_024_iocg_024_pu_START   (0)
#define SOC_IOC_AO_IOCG_024_iocg_024_pu_END     (0)
#define SOC_IOC_AO_IOCG_024_iocg_024_pd_START   (1)
#define SOC_IOC_AO_IOCG_024_iocg_024_pd_END     (1)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds0_START  (4)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds0_END    (4)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds1_START  (5)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds1_END    (5)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds2_START  (6)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds2_END    (6)
#define SOC_IOC_AO_IOCG_024_iocg_024_sr_START   (7)
#define SOC_IOC_AO_IOCG_024_iocg_024_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_025_UNION
 结构说明  : IOCG_025 寄存器结构定义。地址偏移量:0x864，初值:0x00000012，宽度:32
 寄存器说明: GPIO_201功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_025_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_025_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_025_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_025_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_025_UNION;
#endif
#define SOC_IOC_AO_IOCG_025_iocg_025_pu_START   (0)
#define SOC_IOC_AO_IOCG_025_iocg_025_pu_END     (0)
#define SOC_IOC_AO_IOCG_025_iocg_025_pd_START   (1)
#define SOC_IOC_AO_IOCG_025_iocg_025_pd_END     (1)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds0_START  (4)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds0_END    (4)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds1_START  (5)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds1_END    (5)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds2_START  (6)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds2_END    (6)
#define SOC_IOC_AO_IOCG_025_iocg_025_sr_START   (7)
#define SOC_IOC_AO_IOCG_025_iocg_025_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_026_UNION
 结构说明  : IOCG_026 寄存器结构定义。地址偏移量:0x868，初值:0x00000012，宽度:32
 寄存器说明: GPIO_202功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_026_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_026_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_026_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_026_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_026_UNION;
#endif
#define SOC_IOC_AO_IOCG_026_iocg_026_pu_START   (0)
#define SOC_IOC_AO_IOCG_026_iocg_026_pu_END     (0)
#define SOC_IOC_AO_IOCG_026_iocg_026_pd_START   (1)
#define SOC_IOC_AO_IOCG_026_iocg_026_pd_END     (1)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds0_START  (4)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds0_END    (4)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds1_START  (5)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds1_END    (5)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds2_START  (6)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds2_END    (6)
#define SOC_IOC_AO_IOCG_026_iocg_026_sr_START   (7)
#define SOC_IOC_AO_IOCG_026_iocg_026_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_027_UNION
 结构说明  : IOCG_027 寄存器结构定义。地址偏移量:0x86C，初值:0x00000000，宽度:32
 寄存器说明: GPIO_203功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_027_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_027_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_027_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_027_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_027_UNION;
#endif
#define SOC_IOC_AO_IOCG_027_iocg_027_pu_START   (0)
#define SOC_IOC_AO_IOCG_027_iocg_027_pu_END     (0)
#define SOC_IOC_AO_IOCG_027_iocg_027_pd_START   (1)
#define SOC_IOC_AO_IOCG_027_iocg_027_pd_END     (1)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds0_START  (4)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds0_END    (4)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds1_START  (5)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds1_END    (5)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds2_START  (6)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds2_END    (6)
#define SOC_IOC_AO_IOCG_027_iocg_027_sr_START   (7)
#define SOC_IOC_AO_IOCG_027_iocg_027_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_028_UNION
 结构说明  : IOCG_028 寄存器结构定义。地址偏移量:0x870，初值:0x00000012，宽度:32
 寄存器说明: GPIO_204功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_028_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_028_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_028_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_028_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_028_UNION;
#endif
#define SOC_IOC_AO_IOCG_028_iocg_028_pu_START   (0)
#define SOC_IOC_AO_IOCG_028_iocg_028_pu_END     (0)
#define SOC_IOC_AO_IOCG_028_iocg_028_pd_START   (1)
#define SOC_IOC_AO_IOCG_028_iocg_028_pd_END     (1)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds0_START  (4)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds0_END    (4)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds1_START  (5)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds1_END    (5)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds2_START  (6)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds2_END    (6)
#define SOC_IOC_AO_IOCG_028_iocg_028_sr_START   (7)
#define SOC_IOC_AO_IOCG_028_iocg_028_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_029_UNION
 结构说明  : IOCG_029 寄存器结构定义。地址偏移量:0x874，初值:0x00000012，宽度:32
 寄存器说明: GPIO_205功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_029_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_029_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_029_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_029_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_029_UNION;
#endif
#define SOC_IOC_AO_IOCG_029_iocg_029_pu_START   (0)
#define SOC_IOC_AO_IOCG_029_iocg_029_pu_END     (0)
#define SOC_IOC_AO_IOCG_029_iocg_029_pd_START   (1)
#define SOC_IOC_AO_IOCG_029_iocg_029_pd_END     (1)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds0_START  (4)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds0_END    (4)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds1_START  (5)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds1_END    (5)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds2_START  (6)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds2_END    (6)
#define SOC_IOC_AO_IOCG_029_iocg_029_sr_START   (7)
#define SOC_IOC_AO_IOCG_029_iocg_029_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_030_UNION
 结构说明  : IOCG_030 寄存器结构定义。地址偏移量:0x878，初值:0x00000012，宽度:32
 寄存器说明: GPIO_206功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_030_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_030_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_030_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_030_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_030_UNION;
#endif
#define SOC_IOC_AO_IOCG_030_iocg_030_pu_START   (0)
#define SOC_IOC_AO_IOCG_030_iocg_030_pu_END     (0)
#define SOC_IOC_AO_IOCG_030_iocg_030_pd_START   (1)
#define SOC_IOC_AO_IOCG_030_iocg_030_pd_END     (1)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds0_START  (4)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds0_END    (4)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds1_START  (5)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds1_END    (5)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds2_START  (6)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds2_END    (6)
#define SOC_IOC_AO_IOCG_030_iocg_030_sr_START   (7)
#define SOC_IOC_AO_IOCG_030_iocg_030_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_031_UNION
 结构说明  : IOCG_031 寄存器结构定义。地址偏移量:0x87C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_207功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_031_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_031_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_031_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_031_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_031_UNION;
#endif
#define SOC_IOC_AO_IOCG_031_iocg_031_pu_START   (0)
#define SOC_IOC_AO_IOCG_031_iocg_031_pu_END     (0)
#define SOC_IOC_AO_IOCG_031_iocg_031_pd_START   (1)
#define SOC_IOC_AO_IOCG_031_iocg_031_pd_END     (1)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds0_START  (4)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds0_END    (4)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds1_START  (5)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds1_END    (5)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds2_START  (6)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds2_END    (6)
#define SOC_IOC_AO_IOCG_031_iocg_031_sr_START   (7)
#define SOC_IOC_AO_IOCG_031_iocg_031_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_032_UNION
 结构说明  : IOCG_032 寄存器结构定义。地址偏移量:0x880，初值:0x00000012，宽度:32
 寄存器说明: GPIO_208功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_032_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_032_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_032_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_032_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_032_UNION;
#endif
#define SOC_IOC_AO_IOCG_032_iocg_032_pu_START   (0)
#define SOC_IOC_AO_IOCG_032_iocg_032_pu_END     (0)
#define SOC_IOC_AO_IOCG_032_iocg_032_pd_START   (1)
#define SOC_IOC_AO_IOCG_032_iocg_032_pd_END     (1)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds0_START  (4)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds0_END    (4)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds1_START  (5)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds1_END    (5)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds2_START  (6)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds2_END    (6)
#define SOC_IOC_AO_IOCG_032_iocg_032_sr_START   (7)
#define SOC_IOC_AO_IOCG_032_iocg_032_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_033_UNION
 结构说明  : IOCG_033 寄存器结构定义。地址偏移量:0x884，初值:0x00000012，宽度:32
 寄存器说明: GPIO_209功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_033_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_033_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_033_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_033_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_033_UNION;
#endif
#define SOC_IOC_AO_IOCG_033_iocg_033_pu_START   (0)
#define SOC_IOC_AO_IOCG_033_iocg_033_pu_END     (0)
#define SOC_IOC_AO_IOCG_033_iocg_033_pd_START   (1)
#define SOC_IOC_AO_IOCG_033_iocg_033_pd_END     (1)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds0_START  (4)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds0_END    (4)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds1_START  (5)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds1_END    (5)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds2_START  (6)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds2_END    (6)
#define SOC_IOC_AO_IOCG_033_iocg_033_sr_START   (7)
#define SOC_IOC_AO_IOCG_033_iocg_033_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_034_UNION
 结构说明  : IOCG_034 寄存器结构定义。地址偏移量:0x888，初值:0x00000012，宽度:32
 寄存器说明: GPIO_210功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_034_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_034_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_034_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_034_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_034_UNION;
#endif
#define SOC_IOC_AO_IOCG_034_iocg_034_pu_START   (0)
#define SOC_IOC_AO_IOCG_034_iocg_034_pu_END     (0)
#define SOC_IOC_AO_IOCG_034_iocg_034_pd_START   (1)
#define SOC_IOC_AO_IOCG_034_iocg_034_pd_END     (1)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds0_START  (4)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds0_END    (4)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds1_START  (5)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds1_END    (5)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds2_START  (6)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds2_END    (6)
#define SOC_IOC_AO_IOCG_034_iocg_034_sr_START   (7)
#define SOC_IOC_AO_IOCG_034_iocg_034_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_035_UNION
 结构说明  : IOCG_035 寄存器结构定义。地址偏移量:0x88C，初值:0x00000012，宽度:32
 寄存器说明: GPIO_211功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_035_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_035_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_035_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_035_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_035_UNION;
#endif
#define SOC_IOC_AO_IOCG_035_iocg_035_pu_START   (0)
#define SOC_IOC_AO_IOCG_035_iocg_035_pu_END     (0)
#define SOC_IOC_AO_IOCG_035_iocg_035_pd_START   (1)
#define SOC_IOC_AO_IOCG_035_iocg_035_pd_END     (1)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds0_START  (4)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds0_END    (4)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds1_START  (5)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds1_END    (5)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds2_START  (6)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds2_END    (6)
#define SOC_IOC_AO_IOCG_035_iocg_035_sr_START   (7)
#define SOC_IOC_AO_IOCG_035_iocg_035_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_036_UNION
 结构说明  : IOCG_036 寄存器结构定义。地址偏移量:0x890，初值:0x00000012，宽度:32
 寄存器说明: GPIO_212功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_036_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_036_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_036_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_036_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_036_UNION;
#endif
#define SOC_IOC_AO_IOCG_036_iocg_036_pu_START   (0)
#define SOC_IOC_AO_IOCG_036_iocg_036_pu_END     (0)
#define SOC_IOC_AO_IOCG_036_iocg_036_pd_START   (1)
#define SOC_IOC_AO_IOCG_036_iocg_036_pd_END     (1)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds0_START  (4)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds0_END    (4)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds1_START  (5)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds1_END    (5)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds2_START  (6)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds2_END    (6)
#define SOC_IOC_AO_IOCG_036_iocg_036_sr_START   (7)
#define SOC_IOC_AO_IOCG_036_iocg_036_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_037_UNION
 结构说明  : IOCG_037 寄存器结构定义。地址偏移量:0x894，初值:0x00000012，宽度:32
 寄存器说明: GPIO_213功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_037_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_037_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_037_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_037_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_037_UNION;
#endif
#define SOC_IOC_AO_IOCG_037_iocg_037_pu_START   (0)
#define SOC_IOC_AO_IOCG_037_iocg_037_pu_END     (0)
#define SOC_IOC_AO_IOCG_037_iocg_037_pd_START   (1)
#define SOC_IOC_AO_IOCG_037_iocg_037_pd_END     (1)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds0_START  (4)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds0_END    (4)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds1_START  (5)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds1_END    (5)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds2_START  (6)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds2_END    (6)
#define SOC_IOC_AO_IOCG_037_iocg_037_sr_START   (7)
#define SOC_IOC_AO_IOCG_037_iocg_037_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_038_UNION
 结构说明  : IOCG_038 寄存器结构定义。地址偏移量:0x898，初值:0x00000012，宽度:32
 寄存器说明: GPIO_214功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_038_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_038_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_038_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_038_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_038_UNION;
#endif
#define SOC_IOC_AO_IOCG_038_iocg_038_pu_START   (0)
#define SOC_IOC_AO_IOCG_038_iocg_038_pu_END     (0)
#define SOC_IOC_AO_IOCG_038_iocg_038_pd_START   (1)
#define SOC_IOC_AO_IOCG_038_iocg_038_pd_END     (1)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds0_START  (4)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds0_END    (4)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds1_START  (5)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds1_END    (5)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds2_START  (6)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds2_END    (6)
#define SOC_IOC_AO_IOCG_038_iocg_038_sr_START   (7)
#define SOC_IOC_AO_IOCG_038_iocg_038_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_039_UNION
 结构说明  : IOCG_039 寄存器结构定义。地址偏移量:0x89C，初值:0x00000002，宽度:32
 寄存器说明: ISP_GPIO03_PRTRB功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_039_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_039_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_039_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_039_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_039_UNION;
#endif
#define SOC_IOC_AO_IOCG_039_iocg_039_pu_START   (0)
#define SOC_IOC_AO_IOCG_039_iocg_039_pu_END     (0)
#define SOC_IOC_AO_IOCG_039_iocg_039_pd_START   (1)
#define SOC_IOC_AO_IOCG_039_iocg_039_pd_END     (1)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds0_START  (4)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds0_END    (4)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds1_START  (5)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds1_END    (5)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds2_START  (6)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds2_END    (6)
#define SOC_IOC_AO_IOCG_039_iocg_039_sr_START   (7)
#define SOC_IOC_AO_IOCG_039_iocg_039_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_040_UNION
 结构说明  : IOCG_040 寄存器结构定义。地址偏移量:0x8A0，初值:0x00000002，宽度:32
 寄存器说明: ISP_GPIO04_FTPWM功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_040_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_040_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_040_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_040_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_040_UNION;
#endif
#define SOC_IOC_AO_IOCG_040_iocg_040_pu_START   (0)
#define SOC_IOC_AO_IOCG_040_iocg_040_pu_END     (0)
#define SOC_IOC_AO_IOCG_040_iocg_040_pd_START   (1)
#define SOC_IOC_AO_IOCG_040_iocg_040_pd_END     (1)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds0_START  (4)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds0_END    (4)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds1_START  (5)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds1_END    (5)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds2_START  (6)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds2_END    (6)
#define SOC_IOC_AO_IOCG_040_iocg_040_sr_START   (7)
#define SOC_IOC_AO_IOCG_040_iocg_040_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_041_UNION
 结构说明  : IOCG_041 寄存器结构定义。地址偏移量:0x8A4，初值:0x00000002，宽度:32
 寄存器说明: ISP_GPIO05_BKPWM功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_041_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_041_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_041_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_041_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_041_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_041_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_041_UNION;
#endif
#define SOC_IOC_AO_IOCG_041_iocg_041_pu_START   (0)
#define SOC_IOC_AO_IOCG_041_iocg_041_pu_END     (0)
#define SOC_IOC_AO_IOCG_041_iocg_041_pd_START   (1)
#define SOC_IOC_AO_IOCG_041_iocg_041_pd_END     (1)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds0_START  (4)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds0_END    (4)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds1_START  (5)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds1_END    (5)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds2_START  (6)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds2_END    (6)
#define SOC_IOC_AO_IOCG_041_iocg_041_sr_START   (7)
#define SOC_IOC_AO_IOCG_041_iocg_041_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_042_UNION
 结构说明  : IOCG_042 寄存器结构定义。地址偏移量:0x8A8，初值:0x00000002，宽度:32
 寄存器说明: ISP_GPIO09_ENC功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_042_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_042_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_042_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_042_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_042_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_042_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_042_UNION;
#endif
#define SOC_IOC_AO_IOCG_042_iocg_042_pu_START   (0)
#define SOC_IOC_AO_IOCG_042_iocg_042_pu_END     (0)
#define SOC_IOC_AO_IOCG_042_iocg_042_pd_START   (1)
#define SOC_IOC_AO_IOCG_042_iocg_042_pd_END     (1)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds0_START  (4)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds0_END    (4)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds1_START  (5)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds1_END    (5)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds2_START  (6)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds2_END    (6)
#define SOC_IOC_AO_IOCG_042_iocg_042_sr_START   (7)
#define SOC_IOC_AO_IOCG_042_iocg_042_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_043_UNION
 结构说明  : IOCG_043 寄存器结构定义。地址偏移量:0x8AC，初值:0x00000002，宽度:32
 寄存器说明: ISP_GPIO07_ENA功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_043_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_043_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_043_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_043_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_043_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_043_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_043_UNION;
#endif
#define SOC_IOC_AO_IOCG_043_iocg_043_pu_START   (0)
#define SOC_IOC_AO_IOCG_043_iocg_043_pu_END     (0)
#define SOC_IOC_AO_IOCG_043_iocg_043_pd_START   (1)
#define SOC_IOC_AO_IOCG_043_iocg_043_pd_END     (1)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds0_START  (4)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds0_END    (4)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds1_START  (5)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds1_END    (5)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds2_START  (6)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds2_END    (6)
#define SOC_IOC_AO_IOCG_043_iocg_043_sr_START   (7)
#define SOC_IOC_AO_IOCG_043_iocg_043_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_044_UNION
 结构说明  : IOCG_044 寄存器结构定义。地址偏移量:0x8B0，初值:0x00000002，宽度:32
 寄存器说明: ISP_GPIO08_ENB功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_044_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_044_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_044_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_044_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_044_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_044_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_044_UNION;
#endif
#define SOC_IOC_AO_IOCG_044_iocg_044_pu_START   (0)
#define SOC_IOC_AO_IOCG_044_iocg_044_pu_END     (0)
#define SOC_IOC_AO_IOCG_044_iocg_044_pd_START   (1)
#define SOC_IOC_AO_IOCG_044_iocg_044_pd_END     (1)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds0_START  (4)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds0_END    (4)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds1_START  (5)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds1_END    (5)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds2_START  (6)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds2_END    (6)
#define SOC_IOC_AO_IOCG_044_iocg_044_sr_START   (7)
#define SOC_IOC_AO_IOCG_044_iocg_044_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_045_UNION
 结构说明  : IOCG_045 寄存器结构定义。地址偏移量:0x8B4，初值:0x00000002，宽度:32
 寄存器说明: ISP_GPIO11功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_045_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_045_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_045_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_045_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_045_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_045_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_045_UNION;
#endif
#define SOC_IOC_AO_IOCG_045_iocg_045_pu_START   (0)
#define SOC_IOC_AO_IOCG_045_iocg_045_pu_END     (0)
#define SOC_IOC_AO_IOCG_045_iocg_045_pd_START   (1)
#define SOC_IOC_AO_IOCG_045_iocg_045_pd_END     (1)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds0_START  (4)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds0_END    (4)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds1_START  (5)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds1_END    (5)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds2_START  (6)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds2_END    (6)
#define SOC_IOC_AO_IOCG_045_iocg_045_sr_START   (7)
#define SOC_IOC_AO_IOCG_045_iocg_045_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_046_UNION
 结构说明  : IOCG_046 寄存器结构定义。地址偏移量:0x8B8，初值:0x00000002，宽度:32
 寄存器说明: ISP_GPIO12功能管脚控制寄存器。&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_046_pu  : 1;  /* bit[0]   : 输入上拉控制，高有效 */
        unsigned int  iocg_046_pd  : 1;  /* bit[1]   : 输入下拉控制，高有效 */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : 保留。 */
        unsigned int  iocg_046_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_046_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_046_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_046_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_046_UNION;
#endif
#define SOC_IOC_AO_IOCG_046_iocg_046_pu_START   (0)
#define SOC_IOC_AO_IOCG_046_iocg_046_pu_END     (0)
#define SOC_IOC_AO_IOCG_046_iocg_046_pd_START   (1)
#define SOC_IOC_AO_IOCG_046_iocg_046_pd_END     (1)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds0_START  (4)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds0_END    (4)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds1_START  (5)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds1_END    (5)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds2_START  (6)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds2_END    (6)
#define SOC_IOC_AO_IOCG_046_iocg_046_sr_START   (7)
#define SOC_IOC_AO_IOCG_046_iocg_046_sr_END     (7)


/*****************************************************************************
 结构名    : SOC_IOC_AO_IOCG_047_UNION
 结构说明  : IOCG_047 寄存器结构定义。地址偏移量:0x8BC，初值:0x00000002，宽度:32
 寄存器说明: GPIO_223功能管脚控制寄存器。&#13;
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
        unsigned int  iocg_047_ds0 : 1;  /* bit[4]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_047_ds1 : 1;  /* bit[5]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_047_ds2 : 1;  /* bit[6]   : DS1,DS0配置驱动力。000-2mA，001-4mA，010-6mA，011-8mA，100-10mA，101-12mA，110-14mA，111-16mA */
        unsigned int  iocg_047_sr  : 1;  /* bit[7]   : SRew rate控制使能，0：正常模式，1：增加输出端信号上升下降时间 */
        unsigned int  reserved_1   : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_IOC_AO_IOCG_047_UNION;
#endif
#define SOC_IOC_AO_IOCG_047_iocg_047_pu_START   (0)
#define SOC_IOC_AO_IOCG_047_iocg_047_pu_END     (0)
#define SOC_IOC_AO_IOCG_047_iocg_047_pd_START   (1)
#define SOC_IOC_AO_IOCG_047_iocg_047_pd_END     (1)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds0_START  (4)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds0_END    (4)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds1_START  (5)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds1_END    (5)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds2_START  (6)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds2_END    (6)
#define SOC_IOC_AO_IOCG_047_iocg_047_sr_START   (7)
#define SOC_IOC_AO_IOCG_047_iocg_047_sr_END     (7)






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

#endif /* end of soc_ioc_ao_interface.h */
