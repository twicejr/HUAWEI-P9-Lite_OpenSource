/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_lpm3_cfg_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:15
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_LPM3_CFG.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_LPM3_CFG_INTERFACE_H__
#define __SOC_LPM3_CFG_INTERFACE_H__

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
/* 寄存器说明：M3访问DDR的滑动窗口设置寄存器
   位域定义UNION结构:  SOC_LPM3_CFG_ACCESS_WIN_UNION */
#define SOC_LPM3_CFG_ACCESS_WIN_ADDR(base)            ((base) + (0x000))

/* 寄存器说明：M3 halt状态bypass控制寄存器
   位域定义UNION结构:  SOC_LPM3_CFG_HALT_BYPASS_UNION */
#define SOC_LPM3_CFG_HALT_BYPASS_ADDR(base)           ((base) + (0x004))

/* 寄存器说明：Lp_ram multi-cycle控制寄存器
   位域定义UNION结构:  SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION */
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_ADDR(base)      ((base) + (0x008))

/* 寄存器说明：防死锁逻辑bypass控制寄存器
   位域定义UNION结构:  SOC_LPM3_CFG_DLOCK_BYPASS_UNION */
#define SOC_LPM3_CFG_DLOCK_BYPASS_ADDR(base)          ((base) + (0x00C))

/* 寄存器说明：Timer和Wdog计数时钟使能bypass控制寄存器
   位域定义UNION结构:  SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION */
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_ADDR(base)       ((base) + (0x010))

/* 寄存器说明：test pin脚使能输出寄存器
   位域定义UNION结构:  SOC_LPM3_CFG_TESTPIN_EN_UNION */
#define SOC_LPM3_CFG_TESTPIN_EN_ADDR(base)            ((base) + (0x014))

/* 寄存器说明：Harq memory控制寄存器0
   位域定义UNION结构:  SOC_LPM3_CFG_HARQMEM_CTRL0_UNION */
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ADDR(base)         ((base) + (0x020))

/* 寄存器说明：Harq memory控制寄存器1
   位域定义UNION结构:  SOC_LPM3_CFG_HARQMEM_CTRL1_UNION */
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ADDR(base)         ((base) + (0x024))

/* 寄存器说明：NMI软中断寄存器
   位域定义UNION结构:  SOC_LPM3_CFG_NMI_SOFT_UNION */
#define SOC_LPM3_CFG_NMI_SOFT_ADDR(base)              ((base) + (0x028))





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
 结构名    : SOC_LPM3_CFG_ACCESS_WIN_UNION
 结构说明  : ACCESS_WIN 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: M3访问DDR的滑动窗口设置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 28; /* bit[0-27] : Reserved */
        unsigned int  access_window : 4;  /* bit[28-31]: M3对256MB DDR空间访问时，所加的滑动访问窗口。取值范围为0x0~0xD */
    } reg;
} SOC_LPM3_CFG_ACCESS_WIN_UNION;
#endif
#define SOC_LPM3_CFG_ACCESS_WIN_access_window_START  (28)
#define SOC_LPM3_CFG_ACCESS_WIN_access_window_END    (31)


/*****************************************************************************
 结构名    : SOC_LPM3_CFG_HALT_BYPASS_UNION
 结构说明  : HALT_BYPASS 寄存器结构定义。地址偏移量:0x004，初值:0x00000001，宽度:32
 寄存器说明: M3 halt状态bypass控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  halt_bypass : 1;  /* bit[0]   : 是否bypass掉M3debug状态对内部timer、watchdog的计数影响
                                                      0：halt状态会影响计数，即debug状态下停止计数
                                                      1：bypass halt状态，即debug状态下不停止计数 */
        unsigned int  reserved    : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_HALT_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_HALT_BYPASS_halt_bypass_START  (0)
#define SOC_LPM3_CFG_HALT_BYPASS_halt_bypass_END    (0)


/*****************************************************************************
 结构名    : SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION
 结构说明  : LPRAM_MULTI_CTRL 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: Lp_ram multi-cycle控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpram_multi_ctrl : 1;  /* bit[0]   : AO区LP_RAM multi-cycle控制寄存器
                                                           0：正常ram时序，读数据2 cycle返回
                                                           1：ram访问接口的fready反压一拍，读数据3 cycle返回 */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION;
#endif
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_lpram_multi_ctrl_START  (0)
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_lpram_multi_ctrl_END    (0)


/*****************************************************************************
 结构名    : SOC_LPM3_CFG_DLOCK_BYPASS_UNION
 结构说明  : DLOCK_BYPASS 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 防死锁逻辑bypass控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass_for_ssi1  : 1;  /* bit[0]    : pmussi1配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_ddrc  : 1;  /* bit[1]    : ddrc配置接口防挂死逻辑旁路控制，有效时，旁路逻辑输出被强制拉高为1，bypass控制默认为0，即不旁路。 */
        unsigned int  bypass_for_tsen  : 1;  /* bit[2]    : tsensorc配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_pmc   : 1;  /* bit[3]    : pmc配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_uart  : 1;  /* bit[4]    : uart配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_i2c   : 1;  /* bit[5]    : pmui2c配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_ssi0  : 1;  /* bit[6]    : pmussi0配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_pcrg  : 1;  /* bit[7]    : peri CRG配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_wdog  : 1;  /* bit[8]    : Watchdog配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_timer : 1;  /* bit[9]    : Timer配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  reserved_0       : 1;  /* bit[10]   : Unused */
        unsigned int  bypass_for_cssys : 1;  /* bit[11]   : Cssys配置接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_pwm   : 1;  /* bit[12]   : PWM访问接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_rom   : 1;  /* bit[13]   : ROM访问接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_ram   : 1;  /* bit[14]   : RAM访问接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  bypass_for_nandc : 1;  /* bit[15]   : Nandc访问接口防挂死逻辑旁路控制，默认为0 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_DLOCK_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi1_START   (0)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi1_END     (0)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ddrc_START   (1)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ddrc_END     (1)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_tsen_START   (2)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_tsen_END     (2)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pmc_START    (3)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pmc_END      (3)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_uart_START   (4)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_uart_END     (4)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_i2c_START    (5)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_i2c_END      (5)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi0_START   (6)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi0_END     (6)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pcrg_START   (7)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pcrg_END     (7)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_wdog_START   (8)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_wdog_END     (8)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_timer_START  (9)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_timer_END    (9)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_cssys_START  (11)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_cssys_END    (11)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pwm_START    (12)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pwm_END      (12)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_rom_START    (13)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_rom_END      (13)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ram_START    (14)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ram_END      (14)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_nandc_START  (15)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_nandc_END    (15)


/*****************************************************************************
 结构名    : SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION
 结构说明  : TIMCLKEN_BYPASS 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: Timer和Wdog计数时钟使能bypass控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timclken_bypass : 1;  /* bit[0]   : bypass M3子系统内部Timer和Wdog的计数时钟使能，默认值为0。该位有效时，计数时钟使能将被强制拉高为1，以保证M3工作在32KHz时钟时，Timer和Wdog仍可正常计数。 */
        unsigned int  reserved        : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_timclken_bypass_START  (0)
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_timclken_bypass_END    (0)


/*****************************************************************************
 结构名    : SOC_LPM3_CFG_TESTPIN_EN_UNION
 结构说明  : TESTPIN_EN 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: test pin脚使能输出寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  testpin_en : 1;  /* bit[0]   : tp_m3lp_hclk test pin脚输出使能控制位：
                                                     0：test pin脚输出为0
                                                     1：test pin脚输出为tp_m3lp_hclk */
        unsigned int  reserved   : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_TESTPIN_EN_UNION;
#endif
#define SOC_LPM3_CFG_TESTPIN_EN_testpin_en_START  (0)
#define SOC_LPM3_CFG_TESTPIN_EN_testpin_en_END    (0)


/*****************************************************************************
 结构名    : SOC_LPM3_CFG_HARQMEM_CTRL0_UNION
 结构说明  : HARQMEM_CTRL0 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: Harq memory控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  soc_ap_occupy_grp1 : 2;  /* bit[0-1]  : 2'b0x：group 1被BBP占用
                                                              2'b11：group 1被SOC占用 */
        unsigned int  soc_ap_occupy_grp2 : 2;  /* bit[2-3]  : 2'b0x：group 2被BBP占用
                                                              2'b11：group 2被SOC占用 */
        unsigned int  soc_ap_occupy_grp3 : 2;  /* bit[4-5]  : 2'b0x：group 3被BBP占用
                                                              2'b11：group 3被SOC占用 */
        unsigned int  soc_ap_occupy_grp4 : 2;  /* bit[6-7]  : 2'b0x：group 4被BBP占用
                                                              2'b11：group 4被SOC占用 */
        unsigned int  soc_ap_occupy_grp5 : 2;  /* bit[8-9]  : 2'b0x：group 5被BBP占用
                                                              2'b11：group 5被SOC占用 */
        unsigned int  soc_ap_occupy_grp6 : 2;  /* bit[10-11]: 2'b0x：group 6被BBP占用
                                                              2'b11：group 6被SOC占用 */
        unsigned int  soc_ap_occupy_grp7 : 2;  /* bit[12-13]: 2'b0x：group 7被BBP占用
                                                              2'b11：group 7被SOC占用 */
        unsigned int  reserved           : 2;  /* bit[14-15]: Reserved */
        unsigned int  ram_ctrl_sd_grp1   : 1;  /* bit[16]   : group1 RAM 低功耗控制，SD接口，
                                                              1:表示shut down模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_sd_grp2   : 1;  /* bit[17]   : group2 RAM 低功耗控制，SD接口，
                                                              1:表示shut down模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_sd_grp3   : 1;  /* bit[18]   : group3 RAM 低功耗控制，SD接口，
                                                              1:表示shut down模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_sd_grp4   : 3;  /* bit[19-21]: group4 RAM 低功耗控制，SD接口，
                                                              bit[21:19] RAM2~RAM0 SD接口：
                                                              1:表示shut down模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_sd_grp5   : 2;  /* bit[22-23]: group5 RAM 低功耗控制，SD接口，
                                                              bit[23:22] RAM1~RAM0 SD接口：
                                                              1:表示shut down模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_dslp_grp1 : 1;  /* bit[24]   : group1 RAM 低功耗控制，DSLP接口，
                                                              1:表示deep sleep模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_dslp_grp2 : 1;  /* bit[25]   : group2 RAM 低功耗控制，DSLP接口，
                                                              1:表示deep sleep模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_dslp_grp3 : 1;  /* bit[26]   : group3 RAM 低功耗控制，DSLP接口，
                                                              1:表示deep sleep模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_dslp_grp4 : 3;  /* bit[27-29]: group4 RAM 低功耗控制，DSLP接口，
                                                              bit[29:27] RAM2~RAM0 DSLP接口：
                                                              1:表示deep sleep模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_dslp_grp5 : 2;  /* bit[30-31]: group5 RAM 低功耗控制，DSLP接口，
                                                              bit[31:30] RAM1~RAM0 DSLP接口：
                                                              1:表示deep sleep模式，
                                                              0:表示正常模式； */
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL0_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp1_START  (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp1_END    (1)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp2_START  (2)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp2_END    (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp3_START  (4)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp3_END    (5)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp4_START  (6)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp4_END    (7)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp5_START  (8)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp5_END    (9)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp6_START  (10)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp6_END    (11)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp7_START  (12)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_occupy_grp7_END    (13)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp1_START    (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp1_END      (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp2_START    (17)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp2_END      (17)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp3_START    (18)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp3_END      (18)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp4_START    (19)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp4_END      (21)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp5_START    (22)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_sd_grp5_END      (23)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp1_START  (24)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp1_END    (24)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp2_START  (25)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp2_END    (25)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp3_START  (26)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp3_END    (26)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp4_START  (27)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp4_END    (29)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp5_START  (30)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ram_ctrl_dslp_grp5_END    (31)


/*****************************************************************************
 结构名    : SOC_LPM3_CFG_HARQMEM_CTRL1_UNION
 结构说明  : HARQMEM_CTRL1 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: Harq memory控制寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ram_ctrl_sd_grp6   : 3;  /* bit[0-2]  : group6 RAM 低功耗控制，SD接口，
                                                              bit[2:0] RAM2~RAM0 SD接口：
                                                              1:表示shut down模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_sd_grp7   : 11; /* bit[3-13] : group7 RAM 低功耗控制，SD接口，
                                                              bit[13:3] RAM10~RAM0 SD接口：
                                                              1:表示shut down模式，
                                                              0:表示正常模式； */
        unsigned int  reserved_0         : 2;  /* bit[14-15]: Reserved */
        unsigned int  ram_ctrl_dslp_grp6 : 3;  /* bit[16-18]: group6 RAM 低功耗控制，DSLP接口，
                                                              bit[18:16] RAM2~RAM0 DSLP接口：
                                                              1:表示deep sleep low power模式，
                                                              0:表示正常模式； */
        unsigned int  ram_ctrl_dslp_grp7 : 11; /* bit[19-29]: group7 RAM 低功耗控制，DSLP接口，
                                                              bit[29:19] RAM10~RAM0 DSLP接口：
                                                              1:表示deep sleep low power模式，
                                                              0:表示正常模式； */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL1_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp6_START    (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp6_END      (2)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp7_START    (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_sd_grp7_END      (13)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp6_START  (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp6_END    (18)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp7_START  (19)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ram_ctrl_dslp_grp7_END    (29)


/*****************************************************************************
 结构名    : SOC_LPM3_CFG_NMI_SOFT_UNION
 结构说明  : NMI_SOFT 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: NMI软中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nmi_soft : 1;  /* bit[0]   : 产生去往IOMCU的nmi软中断 */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_NMI_SOFT_UNION;
#endif
#define SOC_LPM3_CFG_NMI_SOFT_nmi_soft_START  (0)
#define SOC_LPM3_CFG_NMI_SOFT_nmi_soft_END    (0)






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

#endif /* end of soc_lpm3_cfg_interface.h */
