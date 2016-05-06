/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_tzpc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:48:25
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_TZPC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_TZPC_INTERFACE_H__
#define __SOC_TZPC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) TZPC
 ****************************************************************************/
/* 寄存器说明：用于控制安全保护的区域大小
            接驳TZMA进行对secram的控制，以4KB为单位
            0x00000000 = no secure region
            0x00000001 = 4KB secure region
            0x00000002 = 8KB secure region
            …
            0x000001FF = 2044KB secure region
            0x00000200 或以上的配置将对整个secram空间分配成安全空间。
   位域定义UNION结构:  SOC_TZPC_R0SIZE_UNION */
#define SOC_TZPC_R0SIZE_ADDR(base)                    ((base) + (0x000))

/* 寄存器说明：IP安全属性状态寄存器0。
   位域定义UNION结构:  SOC_TZPC_DECPROT0STAT_UNION */
#define SOC_TZPC_DECPROT0STAT_ADDR(base)              ((base) + (0x800))

/* 寄存器说明：IP安全属性置位寄存器0。
   位域定义UNION结构:  SOC_TZPC_DECPROT0SET_UNION */
#define SOC_TZPC_DECPROT0SET_ADDR(base)               ((base) + (0x804))

/* 寄存器说明：IP安全属性清零寄存器0。
   位域定义UNION结构:  SOC_TZPC_DECPROT0CLR_UNION */
#define SOC_TZPC_DECPROT0CLR_ADDR(base)               ((base) + (0x808))

/* 寄存器说明：IP安全属性状态寄存器1。
   位域定义UNION结构:  SOC_TZPC_DECPROT1STAT_UNION */
#define SOC_TZPC_DECPROT1STAT_ADDR(base)              ((base) + (0x80C))

/* 寄存器说明：IP安全属性置位寄存器1。
   位域定义UNION结构:  SOC_TZPC_DECPROT1SET_UNION */
#define SOC_TZPC_DECPROT1SET_ADDR(base)               ((base) + (0x810))

/* 寄存器说明：IP安全属性清零寄存器1。
   位域定义UNION结构:  SOC_TZPC_DECPROT1CLR_UNION */
#define SOC_TZPC_DECPROT1CLR_ADDR(base)               ((base) + (0x814))

/* 寄存器说明：IP安全属性状态寄存器2。
   位域定义UNION结构:  SOC_TZPC_DECPROT2STAT_UNION */
#define SOC_TZPC_DECPROT2STAT_ADDR(base)              ((base) + (0x818))

/* 寄存器说明：IP安全属性置位寄存器2。
   位域定义UNION结构:  SOC_TZPC_DECPROT2SET_UNION */
#define SOC_TZPC_DECPROT2SET_ADDR(base)               ((base) + (0x81C))

/* 寄存器说明：IP安全属性清零寄存器2。
   位域定义UNION结构:  SOC_TZPC_DECPROT2CLR_UNION */
#define SOC_TZPC_DECPROT2CLR_ADDR(base)               ((base) + (0x820))

/* 寄存器说明：IP安全属性状态寄存器3。
   位域定义UNION结构:  SOC_TZPC_DECPROT3STAT_UNION */
#define SOC_TZPC_DECPROT3STAT_ADDR(base)              ((base) + (0x824))

/* 寄存器说明：IP安全属性置位寄存器3。
   位域定义UNION结构:  SOC_TZPC_DECPROT3SET_UNION */
#define SOC_TZPC_DECPROT3SET_ADDR(base)               ((base) + (0x828))

/* 寄存器说明：IP安全属性清零寄存器3。
   位域定义UNION结构:  SOC_TZPC_DECPROT3CLR_UNION */
#define SOC_TZPC_DECPROT3CLR_ADDR(base)               ((base) + (0x82C))

/* 寄存器说明：IP安全属性状态寄存器4。
   位域定义UNION结构:  SOC_TZPC_DECPROT4STAT_UNION */
#define SOC_TZPC_DECPROT4STAT_ADDR(base)              ((base) + (0x830))

/* 寄存器说明：IP安全属性置位寄存器4。
   位域定义UNION结构:  SOC_TZPC_DECPROT4SET_UNION */
#define SOC_TZPC_DECPROT4SET_ADDR(base)               ((base) + (0x834))

/* 寄存器说明：IP安全属性清零寄存器4。
   位域定义UNION结构:  SOC_TZPC_DECPROT4CLR_UNION */
#define SOC_TZPC_DECPROT4CLR_ADDR(base)               ((base) + (0x838))

/* 寄存器说明：IP安全属性状态寄存器5。
   位域定义UNION结构:  SOC_TZPC_DECPROT5STAT_UNION */
#define SOC_TZPC_DECPROT5STAT_ADDR(base)              ((base) + (0x83C))

/* 寄存器说明：IP安全属性置位寄存器5。
   位域定义UNION结构:  SOC_TZPC_DECPROT5SET_UNION */
#define SOC_TZPC_DECPROT5SET_ADDR(base)               ((base) + (0x840))

/* 寄存器说明：IP安全属性清零寄存器5。
   位域定义UNION结构:  SOC_TZPC_DECPROT5CLR_UNION */
#define SOC_TZPC_DECPROT5CLR_ADDR(base)               ((base) + (0x844))

/* 寄存器说明：IP安全属性状态寄存器6。
   位域定义UNION结构:  SOC_TZPC_DECPROT6STAT_UNION */
#define SOC_TZPC_DECPROT6STAT_ADDR(base)              ((base) + (0x848))

/* 寄存器说明：IP安全属性置位寄存器6。
   位域定义UNION结构:  SOC_TZPC_DECPROT6SET_UNION */
#define SOC_TZPC_DECPROT6SET_ADDR(base)               ((base) + (0x84C))

/* 寄存器说明：IP安全属性清零寄存器6。
   位域定义UNION结构:  SOC_TZPC_DECPROT6CLR_UNION */
#define SOC_TZPC_DECPROT6CLR_ADDR(base)               ((base) + (0x850))

/* 寄存器说明：IP安全属性状态寄存器7。
   位域定义UNION结构:  SOC_TZPC_DECPROT7STAT_UNION */
#define SOC_TZPC_DECPROT7STAT_ADDR(base)              ((base) + (0x854))

/* 寄存器说明：IP安全属性置位寄存器7。
   位域定义UNION结构:  SOC_TZPC_DECPROT7SET_UNION */
#define SOC_TZPC_DECPROT7SET_ADDR(base)               ((base) + (0x858))

/* 寄存器说明：IP安全属性清零寄存器7。
   位域定义UNION结构:  SOC_TZPC_DECPROT7CLR_UNION */
#define SOC_TZPC_DECPROT7CLR_ADDR(base)               ((base) + (0x85C))

/* 寄存器说明：IP安全属性状态寄存器8。
   位域定义UNION结构:  SOC_TZPC_DECPROT8STAT_UNION */
#define SOC_TZPC_DECPROT8STAT_ADDR(base)              ((base) + (0x860))

/* 寄存器说明：IP安全属性置位寄存器8。
   位域定义UNION结构:  SOC_TZPC_DECPROT8SET_UNION */
#define SOC_TZPC_DECPROT8SET_ADDR(base)               ((base) + (0x864))

/* 寄存器说明：IP安全属性清零寄存器8。
   位域定义UNION结构:  SOC_TZPC_DECPROT8CLR_UNION */
#define SOC_TZPC_DECPROT8CLR_ADDR(base)               ((base) + (0x868))

/* 寄存器说明：控制reg0寄存器的信息。
   位域定义UNION结构:  SOC_TZPC_REG0_STAT_UNION */
#define SOC_TZPC_REG0_STAT_ADDR(base)                 ((base) + (0x86C))

/* 寄存器说明：控制reg1寄存器的信息。
   位域定义UNION结构:  SOC_TZPC_REG1_STAT_UNION */
#define SOC_TZPC_REG1_STAT_ADDR(base)                 ((base) + (0x870))





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
                     (1/1) TZPC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_TZPC_R0SIZE_UNION
 结构说明  : R0SIZE 寄存器结构定义。地址偏移量:0x000，初值:0x000003FF，宽度:32
 寄存器说明: 用于控制安全保护的区域大小
            接驳TZMA进行对secram的控制，以4KB为单位
            0x00000000 = no secure region
            0x00000001 = 4KB secure region
            0x00000002 = 8KB secure region
            …
            0x000001FF = 2044KB secure region
            0x00000200 或以上的配置将对整个secram空间分配成安全空间。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 10; /* bit[0-9]  : 保留。 */
        unsigned int  reserved_1: 22; /* bit[10-31]: 保留。 */
    } reg;
} SOC_TZPC_R0SIZE_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT0STAT_UNION
 结构说明  : DECPROT0STAT 寄存器结构定义。地址偏移量:0x800，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec        : 1;  /* bit[0] : efusec slv上电默认为安全属性。 */
        unsigned int  rtc0          : 1;  /* bit[1] : rtc0 slv上电默认为安全属性。 */
        unsigned int  rtc1          : 1;  /* bit[2] : rtc1 slv上电默认为安全属性。 */
        unsigned int  sci0          : 1;  /* bit[3] : sci0 slv上电默认为安全属性。 */
        unsigned int  sci1          : 1;  /* bit[4] : sci1 slv上电默认为安全属性。 */
        unsigned int  syscnt        : 1;  /* bit[5] : syscnt slv上电默认为安全属性。 */
        unsigned int  sctrl_region1 : 1;  /* bit[6] : sctrl region1(0x4020A000~0x4020A7FF)上电默认为安全属性。  */
        unsigned int  sctrl_region2 : 1;  /* bit[7] : sctrl region2(0xA800~0xA9FF AC00~AFFF)上电默认为安全属性。 */
        unsigned int  sctrl_region3 : 1;  /* bit[8] : sctrl region3(0xAA00~0xAAFF)ASP子系统软复位的安全控制，上电默认为安全属性。 */
        unsigned int  sctrl_region4 : 1;  /* bit[9] : sctrl region4(0xAB00~0xABFF)Sensor_sub子系统软复位的安全控制，上电默认为安全属性。 */
        unsigned int  gpio22        : 1;  /* bit[10]: gpio22 slv上电默认为安全属性。 */
        unsigned int  gpio23        : 1;  /* bit[11]: gpio23 slv上电默认为安全属性。 */
        unsigned int  gpio24        : 1;  /* bit[12]: gpio24 slv上电默认为安全属性。 */
        unsigned int  gpio25        : 1;  /* bit[13]: gpio25 slv上电默认为安全属性。 */
        unsigned int  gpio26        : 1;  /* bit[14]: gpio26 slv上电默认为安全属性。 */
        unsigned int  gpio27        : 1;  /* bit[15]: gpio27 slv上电默认为安全属性。 */
        unsigned int  ao_ioc        : 1;  /* bit[16]: ao_ioc slv上电默认为安全属性。 */
        unsigned int  bb_drx        : 1;  /* bit[17]: bb_drx slv上电默认为安全属性。 */
        unsigned int  time0         : 1;  /* bit[18]: time0 slv上电默认为安全属性。 */
        unsigned int  time1         : 1;  /* bit[19]: time1 slv上电默认为安全属性。 */
        unsigned int  time2         : 1;  /* bit[20]: time2 slv上电默认为安全属性。 */
        unsigned int  time3         : 1;  /* bit[21]: time3 slv上电默认为安全属性。 */
        unsigned int  time4         : 1;  /* bit[22]: time4 slv上电默认为安全属性。 */
        unsigned int  time5         : 1;  /* bit[23]: time5 slv上电默认为安全属性。 */
        unsigned int  time6         : 1;  /* bit[24]: time6 slv上电默认为安全属性。 */
        unsigned int  time7         : 1;  /* bit[25]: time7 slv上电默认为安全属性。 */
        unsigned int  time8         : 1;  /* bit[26]: time8 slv上电默认为安全属性。 */
        unsigned int  mmbuf         : 1;  /* bit[27]: mmbuf slv上电默认为安全属性。 */
        unsigned int  asc           : 1;  /* bit[28]: asc slv上电默认为安全属性。 */
        unsigned int  reserved_0    : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_1    : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_2    : 1;  /* bit[31]: 保留。 */
    } reg;
} SOC_TZPC_DECPROT0STAT_UNION;
#endif
#define SOC_TZPC_DECPROT0STAT_efusec_START         (0)
#define SOC_TZPC_DECPROT0STAT_efusec_END           (0)
#define SOC_TZPC_DECPROT0STAT_rtc0_START           (1)
#define SOC_TZPC_DECPROT0STAT_rtc0_END             (1)
#define SOC_TZPC_DECPROT0STAT_rtc1_START           (2)
#define SOC_TZPC_DECPROT0STAT_rtc1_END             (2)
#define SOC_TZPC_DECPROT0STAT_sci0_START           (3)
#define SOC_TZPC_DECPROT0STAT_sci0_END             (3)
#define SOC_TZPC_DECPROT0STAT_sci1_START           (4)
#define SOC_TZPC_DECPROT0STAT_sci1_END             (4)
#define SOC_TZPC_DECPROT0STAT_syscnt_START         (5)
#define SOC_TZPC_DECPROT0STAT_syscnt_END           (5)
#define SOC_TZPC_DECPROT0STAT_sctrl_region1_START  (6)
#define SOC_TZPC_DECPROT0STAT_sctrl_region1_END    (6)
#define SOC_TZPC_DECPROT0STAT_sctrl_region2_START  (7)
#define SOC_TZPC_DECPROT0STAT_sctrl_region2_END    (7)
#define SOC_TZPC_DECPROT0STAT_sctrl_region3_START  (8)
#define SOC_TZPC_DECPROT0STAT_sctrl_region3_END    (8)
#define SOC_TZPC_DECPROT0STAT_sctrl_region4_START  (9)
#define SOC_TZPC_DECPROT0STAT_sctrl_region4_END    (9)
#define SOC_TZPC_DECPROT0STAT_gpio22_START         (10)
#define SOC_TZPC_DECPROT0STAT_gpio22_END           (10)
#define SOC_TZPC_DECPROT0STAT_gpio23_START         (11)
#define SOC_TZPC_DECPROT0STAT_gpio23_END           (11)
#define SOC_TZPC_DECPROT0STAT_gpio24_START         (12)
#define SOC_TZPC_DECPROT0STAT_gpio24_END           (12)
#define SOC_TZPC_DECPROT0STAT_gpio25_START         (13)
#define SOC_TZPC_DECPROT0STAT_gpio25_END           (13)
#define SOC_TZPC_DECPROT0STAT_gpio26_START         (14)
#define SOC_TZPC_DECPROT0STAT_gpio26_END           (14)
#define SOC_TZPC_DECPROT0STAT_gpio27_START         (15)
#define SOC_TZPC_DECPROT0STAT_gpio27_END           (15)
#define SOC_TZPC_DECPROT0STAT_ao_ioc_START         (16)
#define SOC_TZPC_DECPROT0STAT_ao_ioc_END           (16)
#define SOC_TZPC_DECPROT0STAT_bb_drx_START         (17)
#define SOC_TZPC_DECPROT0STAT_bb_drx_END           (17)
#define SOC_TZPC_DECPROT0STAT_time0_START          (18)
#define SOC_TZPC_DECPROT0STAT_time0_END            (18)
#define SOC_TZPC_DECPROT0STAT_time1_START          (19)
#define SOC_TZPC_DECPROT0STAT_time1_END            (19)
#define SOC_TZPC_DECPROT0STAT_time2_START          (20)
#define SOC_TZPC_DECPROT0STAT_time2_END            (20)
#define SOC_TZPC_DECPROT0STAT_time3_START          (21)
#define SOC_TZPC_DECPROT0STAT_time3_END            (21)
#define SOC_TZPC_DECPROT0STAT_time4_START          (22)
#define SOC_TZPC_DECPROT0STAT_time4_END            (22)
#define SOC_TZPC_DECPROT0STAT_time5_START          (23)
#define SOC_TZPC_DECPROT0STAT_time5_END            (23)
#define SOC_TZPC_DECPROT0STAT_time6_START          (24)
#define SOC_TZPC_DECPROT0STAT_time6_END            (24)
#define SOC_TZPC_DECPROT0STAT_time7_START          (25)
#define SOC_TZPC_DECPROT0STAT_time7_END            (25)
#define SOC_TZPC_DECPROT0STAT_time8_START          (26)
#define SOC_TZPC_DECPROT0STAT_time8_END            (26)
#define SOC_TZPC_DECPROT0STAT_mmbuf_START          (27)
#define SOC_TZPC_DECPROT0STAT_mmbuf_END            (27)
#define SOC_TZPC_DECPROT0STAT_asc_START            (28)
#define SOC_TZPC_DECPROT0STAT_asc_END              (28)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT0SET_UNION
 结构说明  : DECPROT0SET 寄存器结构定义。地址偏移量:0x804，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性置位寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec        : 1;  /* bit[0] : IP安全属性置位：
                                                      0：IP安全属性不变；
                                                      1：IP安全属性置“1”。 */
        unsigned int  rtc0          : 1;  /* bit[1] :  */
        unsigned int  rtc1          : 1;  /* bit[2] :  */
        unsigned int  sci0          : 1;  /* bit[3] :  */
        unsigned int  sci1          : 1;  /* bit[4] :  */
        unsigned int  syscnt        : 1;  /* bit[5] :  */
        unsigned int  sctrl_region1 : 1;  /* bit[6] :  */
        unsigned int  sctrl_region2 : 1;  /* bit[7] :  */
        unsigned int  sctrl_region3 : 1;  /* bit[8] :  */
        unsigned int  sctrl_region4 : 1;  /* bit[9] :  */
        unsigned int  gpio22        : 1;  /* bit[10]:  */
        unsigned int  gpio23        : 1;  /* bit[11]:  */
        unsigned int  gpio24        : 1;  /* bit[12]:  */
        unsigned int  gpio25        : 1;  /* bit[13]:  */
        unsigned int  gpio26        : 1;  /* bit[14]:  */
        unsigned int  gpio27        : 1;  /* bit[15]:  */
        unsigned int  ao_ioc        : 1;  /* bit[16]:  */
        unsigned int  bb_drx        : 1;  /* bit[17]:  */
        unsigned int  time0         : 1;  /* bit[18]:  */
        unsigned int  time1         : 1;  /* bit[19]:  */
        unsigned int  time2         : 1;  /* bit[20]:  */
        unsigned int  time3         : 1;  /* bit[21]:  */
        unsigned int  time4         : 1;  /* bit[22]:  */
        unsigned int  time5         : 1;  /* bit[23]:  */
        unsigned int  time6         : 1;  /* bit[24]:  */
        unsigned int  time7         : 1;  /* bit[25]:  */
        unsigned int  time8         : 1;  /* bit[26]:  */
        unsigned int  mmbuf         : 1;  /* bit[27]:  */
        unsigned int  asc           : 1;  /* bit[28]:  */
        unsigned int  reserved_0    : 1;  /* bit[29]:  */
        unsigned int  reserved_1    : 1;  /* bit[30]:  */
        unsigned int  reserved_2    : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT0SET_UNION;
#endif
#define SOC_TZPC_DECPROT0SET_efusec_START         (0)
#define SOC_TZPC_DECPROT0SET_efusec_END           (0)
#define SOC_TZPC_DECPROT0SET_rtc0_START           (1)
#define SOC_TZPC_DECPROT0SET_rtc0_END             (1)
#define SOC_TZPC_DECPROT0SET_rtc1_START           (2)
#define SOC_TZPC_DECPROT0SET_rtc1_END             (2)
#define SOC_TZPC_DECPROT0SET_sci0_START           (3)
#define SOC_TZPC_DECPROT0SET_sci0_END             (3)
#define SOC_TZPC_DECPROT0SET_sci1_START           (4)
#define SOC_TZPC_DECPROT0SET_sci1_END             (4)
#define SOC_TZPC_DECPROT0SET_syscnt_START         (5)
#define SOC_TZPC_DECPROT0SET_syscnt_END           (5)
#define SOC_TZPC_DECPROT0SET_sctrl_region1_START  (6)
#define SOC_TZPC_DECPROT0SET_sctrl_region1_END    (6)
#define SOC_TZPC_DECPROT0SET_sctrl_region2_START  (7)
#define SOC_TZPC_DECPROT0SET_sctrl_region2_END    (7)
#define SOC_TZPC_DECPROT0SET_sctrl_region3_START  (8)
#define SOC_TZPC_DECPROT0SET_sctrl_region3_END    (8)
#define SOC_TZPC_DECPROT0SET_sctrl_region4_START  (9)
#define SOC_TZPC_DECPROT0SET_sctrl_region4_END    (9)
#define SOC_TZPC_DECPROT0SET_gpio22_START         (10)
#define SOC_TZPC_DECPROT0SET_gpio22_END           (10)
#define SOC_TZPC_DECPROT0SET_gpio23_START         (11)
#define SOC_TZPC_DECPROT0SET_gpio23_END           (11)
#define SOC_TZPC_DECPROT0SET_gpio24_START         (12)
#define SOC_TZPC_DECPROT0SET_gpio24_END           (12)
#define SOC_TZPC_DECPROT0SET_gpio25_START         (13)
#define SOC_TZPC_DECPROT0SET_gpio25_END           (13)
#define SOC_TZPC_DECPROT0SET_gpio26_START         (14)
#define SOC_TZPC_DECPROT0SET_gpio26_END           (14)
#define SOC_TZPC_DECPROT0SET_gpio27_START         (15)
#define SOC_TZPC_DECPROT0SET_gpio27_END           (15)
#define SOC_TZPC_DECPROT0SET_ao_ioc_START         (16)
#define SOC_TZPC_DECPROT0SET_ao_ioc_END           (16)
#define SOC_TZPC_DECPROT0SET_bb_drx_START         (17)
#define SOC_TZPC_DECPROT0SET_bb_drx_END           (17)
#define SOC_TZPC_DECPROT0SET_time0_START          (18)
#define SOC_TZPC_DECPROT0SET_time0_END            (18)
#define SOC_TZPC_DECPROT0SET_time1_START          (19)
#define SOC_TZPC_DECPROT0SET_time1_END            (19)
#define SOC_TZPC_DECPROT0SET_time2_START          (20)
#define SOC_TZPC_DECPROT0SET_time2_END            (20)
#define SOC_TZPC_DECPROT0SET_time3_START          (21)
#define SOC_TZPC_DECPROT0SET_time3_END            (21)
#define SOC_TZPC_DECPROT0SET_time4_START          (22)
#define SOC_TZPC_DECPROT0SET_time4_END            (22)
#define SOC_TZPC_DECPROT0SET_time5_START          (23)
#define SOC_TZPC_DECPROT0SET_time5_END            (23)
#define SOC_TZPC_DECPROT0SET_time6_START          (24)
#define SOC_TZPC_DECPROT0SET_time6_END            (24)
#define SOC_TZPC_DECPROT0SET_time7_START          (25)
#define SOC_TZPC_DECPROT0SET_time7_END            (25)
#define SOC_TZPC_DECPROT0SET_time8_START          (26)
#define SOC_TZPC_DECPROT0SET_time8_END            (26)
#define SOC_TZPC_DECPROT0SET_mmbuf_START          (27)
#define SOC_TZPC_DECPROT0SET_mmbuf_END            (27)
#define SOC_TZPC_DECPROT0SET_asc_START            (28)
#define SOC_TZPC_DECPROT0SET_asc_END              (28)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT0CLR_UNION
 结构说明  : DECPROT0CLR 寄存器结构定义。地址偏移量:0x808，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性清零寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  efusec        : 1;  /* bit[0] : IP安全属性清零：
                                                      0：IP安全属性不变；
                                                      1：IP安全属性置“0”。 */
        unsigned int  rtc0          : 1;  /* bit[1] :  */
        unsigned int  rtc1          : 1;  /* bit[2] :  */
        unsigned int  sci0          : 1;  /* bit[3] :  */
        unsigned int  sci1          : 1;  /* bit[4] :  */
        unsigned int  syscnt        : 1;  /* bit[5] :  */
        unsigned int  sctrl_region1 : 1;  /* bit[6] :  */
        unsigned int  sctrl_region2 : 1;  /* bit[7] :  */
        unsigned int  sctrl_region3 : 1;  /* bit[8] :  */
        unsigned int  sctrl_region4 : 1;  /* bit[9] :  */
        unsigned int  gpio22        : 1;  /* bit[10]:  */
        unsigned int  gpio23        : 1;  /* bit[11]:  */
        unsigned int  gpio24        : 1;  /* bit[12]:  */
        unsigned int  gpio25        : 1;  /* bit[13]:  */
        unsigned int  gpio26        : 1;  /* bit[14]:  */
        unsigned int  gpio27        : 1;  /* bit[15]:  */
        unsigned int  ao_ioc        : 1;  /* bit[16]:  */
        unsigned int  bb_drx        : 1;  /* bit[17]:  */
        unsigned int  time0         : 1;  /* bit[18]:  */
        unsigned int  time1         : 1;  /* bit[19]:  */
        unsigned int  time2         : 1;  /* bit[20]:  */
        unsigned int  time3         : 1;  /* bit[21]:  */
        unsigned int  time4         : 1;  /* bit[22]:  */
        unsigned int  time5         : 1;  /* bit[23]:  */
        unsigned int  time6         : 1;  /* bit[24]:  */
        unsigned int  time7         : 1;  /* bit[25]:  */
        unsigned int  time8         : 1;  /* bit[26]:  */
        unsigned int  mmbuf         : 1;  /* bit[27]:  */
        unsigned int  asc           : 1;  /* bit[28]:  */
        unsigned int  reserved_0    : 1;  /* bit[29]:  */
        unsigned int  reserved_1    : 1;  /* bit[30]:  */
        unsigned int  reserved_2    : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT0CLR_UNION;
#endif
#define SOC_TZPC_DECPROT0CLR_efusec_START         (0)
#define SOC_TZPC_DECPROT0CLR_efusec_END           (0)
#define SOC_TZPC_DECPROT0CLR_rtc0_START           (1)
#define SOC_TZPC_DECPROT0CLR_rtc0_END             (1)
#define SOC_TZPC_DECPROT0CLR_rtc1_START           (2)
#define SOC_TZPC_DECPROT0CLR_rtc1_END             (2)
#define SOC_TZPC_DECPROT0CLR_sci0_START           (3)
#define SOC_TZPC_DECPROT0CLR_sci0_END             (3)
#define SOC_TZPC_DECPROT0CLR_sci1_START           (4)
#define SOC_TZPC_DECPROT0CLR_sci1_END             (4)
#define SOC_TZPC_DECPROT0CLR_syscnt_START         (5)
#define SOC_TZPC_DECPROT0CLR_syscnt_END           (5)
#define SOC_TZPC_DECPROT0CLR_sctrl_region1_START  (6)
#define SOC_TZPC_DECPROT0CLR_sctrl_region1_END    (6)
#define SOC_TZPC_DECPROT0CLR_sctrl_region2_START  (7)
#define SOC_TZPC_DECPROT0CLR_sctrl_region2_END    (7)
#define SOC_TZPC_DECPROT0CLR_sctrl_region3_START  (8)
#define SOC_TZPC_DECPROT0CLR_sctrl_region3_END    (8)
#define SOC_TZPC_DECPROT0CLR_sctrl_region4_START  (9)
#define SOC_TZPC_DECPROT0CLR_sctrl_region4_END    (9)
#define SOC_TZPC_DECPROT0CLR_gpio22_START         (10)
#define SOC_TZPC_DECPROT0CLR_gpio22_END           (10)
#define SOC_TZPC_DECPROT0CLR_gpio23_START         (11)
#define SOC_TZPC_DECPROT0CLR_gpio23_END           (11)
#define SOC_TZPC_DECPROT0CLR_gpio24_START         (12)
#define SOC_TZPC_DECPROT0CLR_gpio24_END           (12)
#define SOC_TZPC_DECPROT0CLR_gpio25_START         (13)
#define SOC_TZPC_DECPROT0CLR_gpio25_END           (13)
#define SOC_TZPC_DECPROT0CLR_gpio26_START         (14)
#define SOC_TZPC_DECPROT0CLR_gpio26_END           (14)
#define SOC_TZPC_DECPROT0CLR_gpio27_START         (15)
#define SOC_TZPC_DECPROT0CLR_gpio27_END           (15)
#define SOC_TZPC_DECPROT0CLR_ao_ioc_START         (16)
#define SOC_TZPC_DECPROT0CLR_ao_ioc_END           (16)
#define SOC_TZPC_DECPROT0CLR_bb_drx_START         (17)
#define SOC_TZPC_DECPROT0CLR_bb_drx_END           (17)
#define SOC_TZPC_DECPROT0CLR_time0_START          (18)
#define SOC_TZPC_DECPROT0CLR_time0_END            (18)
#define SOC_TZPC_DECPROT0CLR_time1_START          (19)
#define SOC_TZPC_DECPROT0CLR_time1_END            (19)
#define SOC_TZPC_DECPROT0CLR_time2_START          (20)
#define SOC_TZPC_DECPROT0CLR_time2_END            (20)
#define SOC_TZPC_DECPROT0CLR_time3_START          (21)
#define SOC_TZPC_DECPROT0CLR_time3_END            (21)
#define SOC_TZPC_DECPROT0CLR_time4_START          (22)
#define SOC_TZPC_DECPROT0CLR_time4_END            (22)
#define SOC_TZPC_DECPROT0CLR_time5_START          (23)
#define SOC_TZPC_DECPROT0CLR_time5_END            (23)
#define SOC_TZPC_DECPROT0CLR_time6_START          (24)
#define SOC_TZPC_DECPROT0CLR_time6_END            (24)
#define SOC_TZPC_DECPROT0CLR_time7_START          (25)
#define SOC_TZPC_DECPROT0CLR_time7_END            (25)
#define SOC_TZPC_DECPROT0CLR_time8_START          (26)
#define SOC_TZPC_DECPROT0CLR_time8_END            (26)
#define SOC_TZPC_DECPROT0CLR_mmbuf_START          (27)
#define SOC_TZPC_DECPROT0CLR_mmbuf_END            (27)
#define SOC_TZPC_DECPROT0CLR_asc_START            (28)
#define SOC_TZPC_DECPROT0CLR_asc_END              (28)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT1STAT_UNION
 结构说明  : DECPROT1STAT 寄存器结构定义。地址偏移量:0x80C，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 1;  /* bit[0] : 保留。 */
        unsigned int  reserved_1    : 1;  /* bit[1] : 保留。 */
        unsigned int  timer9        : 1;  /* bit[2] : timer9 slv上电默认为安全属性。 */
        unsigned int  timer10       : 1;  /* bit[3] : timer10 slv上电默认为安全属性。 */
        unsigned int  timer11       : 1;  /* bit[4] : timer11 slv上电默认为安全属性。 */
        unsigned int  timer12       : 1;  /* bit[5] : timer12 slv上电默认为安全属性。 */
        unsigned int  pctrl_region1 : 1;  /* bit[6] : PCTRL(0xA8A09000~0xA8A093FF)上电默认为安全属性。 */
        unsigned int  pctrl_region2 : 1;  /* bit[7] : PCTRL(0xA8A09400~0xA8A097FF)上电默认为安全属性。 */
        unsigned int  pctrl_region3 : 1;  /* bit[8] : PCTRL(0xA8A09800~0xA8A09BFF)上电默认为安全属性。 */
        unsigned int  pctrl_region4 : 1;  /* bit[9] : PCTRL(0xA8A09C00~0xA8A09FFF)上电默认为安全属性。 */
        unsigned int  pwm           : 1;  /* bit[10]: pwm slv上电默认为安全属性。 */
        unsigned int  reserved_2    : 1;  /* bit[11]: 保留。 */
        unsigned int  watchdog0     : 1;  /* bit[12]: watchdog0 slv上电默认为安全属性。 */
        unsigned int  watchdog1     : 1;  /* bit[13]: watchdog1 slv上电默认为安全属性。 */
        unsigned int  gpio0         : 1;  /* bit[14]: gpio0 slv上电默认为安全属性。 */
        unsigned int  gpio1         : 1;  /* bit[15]: gpio1 slv上电默认为安全属性。 */
        unsigned int  gpio2         : 1;  /* bit[16]: gpio2 slv上电默认为安全属性。 */
        unsigned int  gpio3         : 1;  /* bit[17]: gpio3 slv上电默认为安全属性。 */
        unsigned int  gpio4         : 1;  /* bit[18]: gpio4 slv上电默认为安全属性。 */
        unsigned int  gpio5         : 1;  /* bit[19]: gpio5 slv上电默认为安全属性。 */
        unsigned int  gpio6         : 1;  /* bit[20]: gpio6 slv上电默认为安全属性。 */
        unsigned int  gpio7         : 1;  /* bit[21]: gpio7 slv上电默认为安全属性。 */
        unsigned int  gpio8         : 1;  /* bit[22]: gpio8 slv上电默认为安全属性。 */
        unsigned int  gpio9         : 1;  /* bit[23]: gpio9 slv上电默认为安全属性。 */
        unsigned int  gpio10        : 1;  /* bit[24]: gpio10 slv上电默认为安全属性。 */
        unsigned int  gpio11        : 1;  /* bit[25]: gpio11 slv上电默认为安全属性。 */
        unsigned int  gpio12        : 1;  /* bit[26]: gpio12 slv上电默认为安全属性。 */
        unsigned int  gpio13        : 1;  /* bit[27]: gpio13 slv上电默认为安全属性。 */
        unsigned int  gpio14        : 1;  /* bit[28]: gpio14 slv上电默认为安全属性。 */
        unsigned int  gpio15        : 1;  /* bit[29]: gpio15 slv上电默认为安全属性。 */
        unsigned int  gpio16        : 1;  /* bit[30]: gpio16 slv上电默认为安全属性。 */
        unsigned int  gpio17        : 1;  /* bit[31]: gpio17 slv上电默认为安全属性。 */
    } reg;
} SOC_TZPC_DECPROT1STAT_UNION;
#endif
#define SOC_TZPC_DECPROT1STAT_timer9_START         (2)
#define SOC_TZPC_DECPROT1STAT_timer9_END           (2)
#define SOC_TZPC_DECPROT1STAT_timer10_START        (3)
#define SOC_TZPC_DECPROT1STAT_timer10_END          (3)
#define SOC_TZPC_DECPROT1STAT_timer11_START        (4)
#define SOC_TZPC_DECPROT1STAT_timer11_END          (4)
#define SOC_TZPC_DECPROT1STAT_timer12_START        (5)
#define SOC_TZPC_DECPROT1STAT_timer12_END          (5)
#define SOC_TZPC_DECPROT1STAT_pctrl_region1_START  (6)
#define SOC_TZPC_DECPROT1STAT_pctrl_region1_END    (6)
#define SOC_TZPC_DECPROT1STAT_pctrl_region2_START  (7)
#define SOC_TZPC_DECPROT1STAT_pctrl_region2_END    (7)
#define SOC_TZPC_DECPROT1STAT_pctrl_region3_START  (8)
#define SOC_TZPC_DECPROT1STAT_pctrl_region3_END    (8)
#define SOC_TZPC_DECPROT1STAT_pctrl_region4_START  (9)
#define SOC_TZPC_DECPROT1STAT_pctrl_region4_END    (9)
#define SOC_TZPC_DECPROT1STAT_pwm_START            (10)
#define SOC_TZPC_DECPROT1STAT_pwm_END              (10)
#define SOC_TZPC_DECPROT1STAT_watchdog0_START      (12)
#define SOC_TZPC_DECPROT1STAT_watchdog0_END        (12)
#define SOC_TZPC_DECPROT1STAT_watchdog1_START      (13)
#define SOC_TZPC_DECPROT1STAT_watchdog1_END        (13)
#define SOC_TZPC_DECPROT1STAT_gpio0_START          (14)
#define SOC_TZPC_DECPROT1STAT_gpio0_END            (14)
#define SOC_TZPC_DECPROT1STAT_gpio1_START          (15)
#define SOC_TZPC_DECPROT1STAT_gpio1_END            (15)
#define SOC_TZPC_DECPROT1STAT_gpio2_START          (16)
#define SOC_TZPC_DECPROT1STAT_gpio2_END            (16)
#define SOC_TZPC_DECPROT1STAT_gpio3_START          (17)
#define SOC_TZPC_DECPROT1STAT_gpio3_END            (17)
#define SOC_TZPC_DECPROT1STAT_gpio4_START          (18)
#define SOC_TZPC_DECPROT1STAT_gpio4_END            (18)
#define SOC_TZPC_DECPROT1STAT_gpio5_START          (19)
#define SOC_TZPC_DECPROT1STAT_gpio5_END            (19)
#define SOC_TZPC_DECPROT1STAT_gpio6_START          (20)
#define SOC_TZPC_DECPROT1STAT_gpio6_END            (20)
#define SOC_TZPC_DECPROT1STAT_gpio7_START          (21)
#define SOC_TZPC_DECPROT1STAT_gpio7_END            (21)
#define SOC_TZPC_DECPROT1STAT_gpio8_START          (22)
#define SOC_TZPC_DECPROT1STAT_gpio8_END            (22)
#define SOC_TZPC_DECPROT1STAT_gpio9_START          (23)
#define SOC_TZPC_DECPROT1STAT_gpio9_END            (23)
#define SOC_TZPC_DECPROT1STAT_gpio10_START         (24)
#define SOC_TZPC_DECPROT1STAT_gpio10_END           (24)
#define SOC_TZPC_DECPROT1STAT_gpio11_START         (25)
#define SOC_TZPC_DECPROT1STAT_gpio11_END           (25)
#define SOC_TZPC_DECPROT1STAT_gpio12_START         (26)
#define SOC_TZPC_DECPROT1STAT_gpio12_END           (26)
#define SOC_TZPC_DECPROT1STAT_gpio13_START         (27)
#define SOC_TZPC_DECPROT1STAT_gpio13_END           (27)
#define SOC_TZPC_DECPROT1STAT_gpio14_START         (28)
#define SOC_TZPC_DECPROT1STAT_gpio14_END           (28)
#define SOC_TZPC_DECPROT1STAT_gpio15_START         (29)
#define SOC_TZPC_DECPROT1STAT_gpio15_END           (29)
#define SOC_TZPC_DECPROT1STAT_gpio16_START         (30)
#define SOC_TZPC_DECPROT1STAT_gpio16_END           (30)
#define SOC_TZPC_DECPROT1STAT_gpio17_START         (31)
#define SOC_TZPC_DECPROT1STAT_gpio17_END           (31)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT1SET_UNION
 结构说明  : DECPROT1SET 寄存器结构定义。地址偏移量:0x810，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性置位寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 1;  /* bit[0] : IP安全属性置位：
                                                      0：IP安全属性不变；
                                                      1：IP安全属性置“1”。 */
        unsigned int  reserved_1    : 1;  /* bit[1] :  */
        unsigned int  timer9        : 1;  /* bit[2] :  */
        unsigned int  timer10       : 1;  /* bit[3] :  */
        unsigned int  timer11       : 1;  /* bit[4] :  */
        unsigned int  timer12       : 1;  /* bit[5] :  */
        unsigned int  pctrl_region1 : 1;  /* bit[6] :  */
        unsigned int  pctrl_region2 : 1;  /* bit[7] :  */
        unsigned int  pctrl_region3 : 1;  /* bit[8] :  */
        unsigned int  pctrl_region4 : 1;  /* bit[9] :  */
        unsigned int  pwm           : 1;  /* bit[10]:  */
        unsigned int  reserved_2    : 1;  /* bit[11]:  */
        unsigned int  watchdog0     : 1;  /* bit[12]:  */
        unsigned int  watchdog1     : 1;  /* bit[13]:  */
        unsigned int  gpio0         : 1;  /* bit[14]:  */
        unsigned int  gpio1         : 1;  /* bit[15]:  */
        unsigned int  gpio2         : 1;  /* bit[16]:  */
        unsigned int  gpio3         : 1;  /* bit[17]:  */
        unsigned int  gpio4         : 1;  /* bit[18]:  */
        unsigned int  gpio5         : 1;  /* bit[19]:  */
        unsigned int  gpio6         : 1;  /* bit[20]:  */
        unsigned int  gpio7         : 1;  /* bit[21]:  */
        unsigned int  gpio8         : 1;  /* bit[22]:  */
        unsigned int  gpio9         : 1;  /* bit[23]:  */
        unsigned int  gpio10        : 1;  /* bit[24]:  */
        unsigned int  gpio11        : 1;  /* bit[25]:  */
        unsigned int  gpio12        : 1;  /* bit[26]:  */
        unsigned int  gpio13        : 1;  /* bit[27]:  */
        unsigned int  gpio14        : 1;  /* bit[28]:  */
        unsigned int  gpio15        : 1;  /* bit[29]:  */
        unsigned int  gpio16        : 1;  /* bit[30]:  */
        unsigned int  gpio17        : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT1SET_UNION;
#endif
#define SOC_TZPC_DECPROT1SET_timer9_START         (2)
#define SOC_TZPC_DECPROT1SET_timer9_END           (2)
#define SOC_TZPC_DECPROT1SET_timer10_START        (3)
#define SOC_TZPC_DECPROT1SET_timer10_END          (3)
#define SOC_TZPC_DECPROT1SET_timer11_START        (4)
#define SOC_TZPC_DECPROT1SET_timer11_END          (4)
#define SOC_TZPC_DECPROT1SET_timer12_START        (5)
#define SOC_TZPC_DECPROT1SET_timer12_END          (5)
#define SOC_TZPC_DECPROT1SET_pctrl_region1_START  (6)
#define SOC_TZPC_DECPROT1SET_pctrl_region1_END    (6)
#define SOC_TZPC_DECPROT1SET_pctrl_region2_START  (7)
#define SOC_TZPC_DECPROT1SET_pctrl_region2_END    (7)
#define SOC_TZPC_DECPROT1SET_pctrl_region3_START  (8)
#define SOC_TZPC_DECPROT1SET_pctrl_region3_END    (8)
#define SOC_TZPC_DECPROT1SET_pctrl_region4_START  (9)
#define SOC_TZPC_DECPROT1SET_pctrl_region4_END    (9)
#define SOC_TZPC_DECPROT1SET_pwm_START            (10)
#define SOC_TZPC_DECPROT1SET_pwm_END              (10)
#define SOC_TZPC_DECPROT1SET_watchdog0_START      (12)
#define SOC_TZPC_DECPROT1SET_watchdog0_END        (12)
#define SOC_TZPC_DECPROT1SET_watchdog1_START      (13)
#define SOC_TZPC_DECPROT1SET_watchdog1_END        (13)
#define SOC_TZPC_DECPROT1SET_gpio0_START          (14)
#define SOC_TZPC_DECPROT1SET_gpio0_END            (14)
#define SOC_TZPC_DECPROT1SET_gpio1_START          (15)
#define SOC_TZPC_DECPROT1SET_gpio1_END            (15)
#define SOC_TZPC_DECPROT1SET_gpio2_START          (16)
#define SOC_TZPC_DECPROT1SET_gpio2_END            (16)
#define SOC_TZPC_DECPROT1SET_gpio3_START          (17)
#define SOC_TZPC_DECPROT1SET_gpio3_END            (17)
#define SOC_TZPC_DECPROT1SET_gpio4_START          (18)
#define SOC_TZPC_DECPROT1SET_gpio4_END            (18)
#define SOC_TZPC_DECPROT1SET_gpio5_START          (19)
#define SOC_TZPC_DECPROT1SET_gpio5_END            (19)
#define SOC_TZPC_DECPROT1SET_gpio6_START          (20)
#define SOC_TZPC_DECPROT1SET_gpio6_END            (20)
#define SOC_TZPC_DECPROT1SET_gpio7_START          (21)
#define SOC_TZPC_DECPROT1SET_gpio7_END            (21)
#define SOC_TZPC_DECPROT1SET_gpio8_START          (22)
#define SOC_TZPC_DECPROT1SET_gpio8_END            (22)
#define SOC_TZPC_DECPROT1SET_gpio9_START          (23)
#define SOC_TZPC_DECPROT1SET_gpio9_END            (23)
#define SOC_TZPC_DECPROT1SET_gpio10_START         (24)
#define SOC_TZPC_DECPROT1SET_gpio10_END           (24)
#define SOC_TZPC_DECPROT1SET_gpio11_START         (25)
#define SOC_TZPC_DECPROT1SET_gpio11_END           (25)
#define SOC_TZPC_DECPROT1SET_gpio12_START         (26)
#define SOC_TZPC_DECPROT1SET_gpio12_END           (26)
#define SOC_TZPC_DECPROT1SET_gpio13_START         (27)
#define SOC_TZPC_DECPROT1SET_gpio13_END           (27)
#define SOC_TZPC_DECPROT1SET_gpio14_START         (28)
#define SOC_TZPC_DECPROT1SET_gpio14_END           (28)
#define SOC_TZPC_DECPROT1SET_gpio15_START         (29)
#define SOC_TZPC_DECPROT1SET_gpio15_END           (29)
#define SOC_TZPC_DECPROT1SET_gpio16_START         (30)
#define SOC_TZPC_DECPROT1SET_gpio16_END           (30)
#define SOC_TZPC_DECPROT1SET_gpio17_START         (31)
#define SOC_TZPC_DECPROT1SET_gpio17_END           (31)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT1CLR_UNION
 结构说明  : DECPROT1CLR 寄存器结构定义。地址偏移量:0x814，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性清零寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 1;  /* bit[0] : IP安全属性清零：
                                                      0：IP安全属性不变；
                                                      1：IP安全属性置“0”。 */
        unsigned int  reserved_1    : 1;  /* bit[1] :  */
        unsigned int  timer9        : 1;  /* bit[2] :  */
        unsigned int  timer10       : 1;  /* bit[3] :  */
        unsigned int  timer11       : 1;  /* bit[4] :  */
        unsigned int  timer12       : 1;  /* bit[5] :  */
        unsigned int  pctrl_region1 : 1;  /* bit[6] :  */
        unsigned int  pctrl_region2 : 1;  /* bit[7] :  */
        unsigned int  pctrl_region3 : 1;  /* bit[8] :  */
        unsigned int  pctrl_region4 : 1;  /* bit[9] :  */
        unsigned int  pwm           : 1;  /* bit[10]:  */
        unsigned int  reserved_2    : 1;  /* bit[11]:  */
        unsigned int  watchdog0     : 1;  /* bit[12]:  */
        unsigned int  watchdog1     : 1;  /* bit[13]:  */
        unsigned int  gpio0         : 1;  /* bit[14]:  */
        unsigned int  gpio1         : 1;  /* bit[15]:  */
        unsigned int  gpio2         : 1;  /* bit[16]:  */
        unsigned int  gpio3         : 1;  /* bit[17]:  */
        unsigned int  gpio4         : 1;  /* bit[18]:  */
        unsigned int  gpio5         : 1;  /* bit[19]:  */
        unsigned int  gpio6         : 1;  /* bit[20]:  */
        unsigned int  gpio7         : 1;  /* bit[21]:  */
        unsigned int  gpio8         : 1;  /* bit[22]:  */
        unsigned int  gpio9         : 1;  /* bit[23]:  */
        unsigned int  gpio10        : 1;  /* bit[24]:  */
        unsigned int  gpio11        : 1;  /* bit[25]:  */
        unsigned int  gpio12        : 1;  /* bit[26]:  */
        unsigned int  gpio13        : 1;  /* bit[27]:  */
        unsigned int  gpio14        : 1;  /* bit[28]:  */
        unsigned int  gpio15        : 1;  /* bit[29]:  */
        unsigned int  gpio16        : 1;  /* bit[30]:  */
        unsigned int  gpio17        : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT1CLR_UNION;
#endif
#define SOC_TZPC_DECPROT1CLR_timer9_START         (2)
#define SOC_TZPC_DECPROT1CLR_timer9_END           (2)
#define SOC_TZPC_DECPROT1CLR_timer10_START        (3)
#define SOC_TZPC_DECPROT1CLR_timer10_END          (3)
#define SOC_TZPC_DECPROT1CLR_timer11_START        (4)
#define SOC_TZPC_DECPROT1CLR_timer11_END          (4)
#define SOC_TZPC_DECPROT1CLR_timer12_START        (5)
#define SOC_TZPC_DECPROT1CLR_timer12_END          (5)
#define SOC_TZPC_DECPROT1CLR_pctrl_region1_START  (6)
#define SOC_TZPC_DECPROT1CLR_pctrl_region1_END    (6)
#define SOC_TZPC_DECPROT1CLR_pctrl_region2_START  (7)
#define SOC_TZPC_DECPROT1CLR_pctrl_region2_END    (7)
#define SOC_TZPC_DECPROT1CLR_pctrl_region3_START  (8)
#define SOC_TZPC_DECPROT1CLR_pctrl_region3_END    (8)
#define SOC_TZPC_DECPROT1CLR_pctrl_region4_START  (9)
#define SOC_TZPC_DECPROT1CLR_pctrl_region4_END    (9)
#define SOC_TZPC_DECPROT1CLR_pwm_START            (10)
#define SOC_TZPC_DECPROT1CLR_pwm_END              (10)
#define SOC_TZPC_DECPROT1CLR_watchdog0_START      (12)
#define SOC_TZPC_DECPROT1CLR_watchdog0_END        (12)
#define SOC_TZPC_DECPROT1CLR_watchdog1_START      (13)
#define SOC_TZPC_DECPROT1CLR_watchdog1_END        (13)
#define SOC_TZPC_DECPROT1CLR_gpio0_START          (14)
#define SOC_TZPC_DECPROT1CLR_gpio0_END            (14)
#define SOC_TZPC_DECPROT1CLR_gpio1_START          (15)
#define SOC_TZPC_DECPROT1CLR_gpio1_END            (15)
#define SOC_TZPC_DECPROT1CLR_gpio2_START          (16)
#define SOC_TZPC_DECPROT1CLR_gpio2_END            (16)
#define SOC_TZPC_DECPROT1CLR_gpio3_START          (17)
#define SOC_TZPC_DECPROT1CLR_gpio3_END            (17)
#define SOC_TZPC_DECPROT1CLR_gpio4_START          (18)
#define SOC_TZPC_DECPROT1CLR_gpio4_END            (18)
#define SOC_TZPC_DECPROT1CLR_gpio5_START          (19)
#define SOC_TZPC_DECPROT1CLR_gpio5_END            (19)
#define SOC_TZPC_DECPROT1CLR_gpio6_START          (20)
#define SOC_TZPC_DECPROT1CLR_gpio6_END            (20)
#define SOC_TZPC_DECPROT1CLR_gpio7_START          (21)
#define SOC_TZPC_DECPROT1CLR_gpio7_END            (21)
#define SOC_TZPC_DECPROT1CLR_gpio8_START          (22)
#define SOC_TZPC_DECPROT1CLR_gpio8_END            (22)
#define SOC_TZPC_DECPROT1CLR_gpio9_START          (23)
#define SOC_TZPC_DECPROT1CLR_gpio9_END            (23)
#define SOC_TZPC_DECPROT1CLR_gpio10_START         (24)
#define SOC_TZPC_DECPROT1CLR_gpio10_END           (24)
#define SOC_TZPC_DECPROT1CLR_gpio11_START         (25)
#define SOC_TZPC_DECPROT1CLR_gpio11_END           (25)
#define SOC_TZPC_DECPROT1CLR_gpio12_START         (26)
#define SOC_TZPC_DECPROT1CLR_gpio12_END           (26)
#define SOC_TZPC_DECPROT1CLR_gpio13_START         (27)
#define SOC_TZPC_DECPROT1CLR_gpio13_END           (27)
#define SOC_TZPC_DECPROT1CLR_gpio14_START         (28)
#define SOC_TZPC_DECPROT1CLR_gpio14_END           (28)
#define SOC_TZPC_DECPROT1CLR_gpio15_START         (29)
#define SOC_TZPC_DECPROT1CLR_gpio15_END           (29)
#define SOC_TZPC_DECPROT1CLR_gpio16_START         (30)
#define SOC_TZPC_DECPROT1CLR_gpio16_END           (30)
#define SOC_TZPC_DECPROT1CLR_gpio17_START         (31)
#define SOC_TZPC_DECPROT1CLR_gpio17_END           (31)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT2STAT_UNION
 结构说明  : DECPROT2STAT 寄存器结构定义。地址偏移量:0x818，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio18   : 1;  /* bit[0] : gpio18 slv上电默认为安全属性。 */
        unsigned int  gpio19   : 1;  /* bit[1] : gpio19 slv上电默认为安全属性。 */
        unsigned int  gpio20   : 1;  /* bit[2] : gpio20 slv上电默认为安全属性。 */
        unsigned int  gpio21   : 1;  /* bit[3] : gpio21 slv上电默认为安全属性。 */
        unsigned int  reserved_0: 1;  /* bit[4] : 保留。 */
        unsigned int  reserved_1: 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_2: 1;  /* bit[6] : 保留。 */
        unsigned int  reserved_3: 1;  /* bit[7] : 保留。 */
        unsigned int  reserved_4: 1;  /* bit[8] : 保留。 */
        unsigned int  reserved_5: 1;  /* bit[9] : 保留。 */
        unsigned int  reserved_6: 1;  /* bit[10]: 保留。 */
        unsigned int  reserved_7: 1;  /* bit[11]: 保留。 */
        unsigned int  reserved_8: 1;  /* bit[12]: 保留。 */
        unsigned int  reserved_9: 1;  /* bit[13]: 保留。 */
        unsigned int  reserved_10: 1;  /* bit[14]: 保留。 */
        unsigned int  reserved_11: 1;  /* bit[15]: 保留。 */
        unsigned int  reserved_12: 1;  /* bit[16]: 保留。 */
        unsigned int  reserved_13: 1;  /* bit[17]: 保留。 */
        unsigned int  reserved_14: 1;  /* bit[18]: 保留。 */
        unsigned int  reserved_15: 1;  /* bit[19]: 保留。 */
        unsigned int  reserved_16: 1;  /* bit[20]: 保留。 */
        unsigned int  reserved_17: 1;  /* bit[21]: 保留。 */
        unsigned int  reserved_18: 1;  /* bit[22]: 保留。 */
        unsigned int  reserved_19: 1;  /* bit[23]: 保留。 */
        unsigned int  reserved_20: 1;  /* bit[24]: 保留。 */
        unsigned int  reserved_21: 1;  /* bit[25]: 保留。 */
        unsigned int  reserved_22: 1;  /* bit[26]: 保留。 */
        unsigned int  reserved_23: 1;  /* bit[27]: 保留。 */
        unsigned int  reserved_24: 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_25: 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_26: 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_27: 1;  /* bit[31]: 保留。 */
    } reg;
} SOC_TZPC_DECPROT2STAT_UNION;
#endif
#define SOC_TZPC_DECPROT2STAT_gpio18_START    (0)
#define SOC_TZPC_DECPROT2STAT_gpio18_END      (0)
#define SOC_TZPC_DECPROT2STAT_gpio19_START    (1)
#define SOC_TZPC_DECPROT2STAT_gpio19_END      (1)
#define SOC_TZPC_DECPROT2STAT_gpio20_START    (2)
#define SOC_TZPC_DECPROT2STAT_gpio20_END      (2)
#define SOC_TZPC_DECPROT2STAT_gpio21_START    (3)
#define SOC_TZPC_DECPROT2STAT_gpio21_END      (3)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT2SET_UNION
 结构说明  : DECPROT2SET 寄存器结构定义。地址偏移量:0x81C，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性置位寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio18   : 1;  /* bit[0] : IP安全属性置位：
                                                 0：IP安全属性不变；
                                                 1：IP安全属性置“1”。 */
        unsigned int  gpio19   : 1;  /* bit[1] :  */
        unsigned int  gpio20   : 1;  /* bit[2] :  */
        unsigned int  gpio21   : 1;  /* bit[3] :  */
        unsigned int  reserved_0: 1;  /* bit[4] :  */
        unsigned int  reserved_1: 1;  /* bit[5] :  */
        unsigned int  reserved_2: 1;  /* bit[6] :  */
        unsigned int  reserved_3: 1;  /* bit[7] :  */
        unsigned int  reserved_4: 1;  /* bit[8] :  */
        unsigned int  reserved_5: 1;  /* bit[9] :  */
        unsigned int  reserved_6: 1;  /* bit[10]:  */
        unsigned int  reserved_7: 1;  /* bit[11]:  */
        unsigned int  reserved_8: 1;  /* bit[12]:  */
        unsigned int  reserved_9: 1;  /* bit[13]:  */
        unsigned int  reserved_10: 1;  /* bit[14]:  */
        unsigned int  reserved_11: 1;  /* bit[15]:  */
        unsigned int  reserved_12: 1;  /* bit[16]:  */
        unsigned int  reserved_13: 1;  /* bit[17]:  */
        unsigned int  reserved_14: 1;  /* bit[18]:  */
        unsigned int  reserved_15: 1;  /* bit[19]:  */
        unsigned int  reserved_16: 1;  /* bit[20]:  */
        unsigned int  reserved_17: 1;  /* bit[21]:  */
        unsigned int  reserved_18: 1;  /* bit[22]:  */
        unsigned int  reserved_19: 1;  /* bit[23]:  */
        unsigned int  reserved_20: 1;  /* bit[24]:  */
        unsigned int  reserved_21: 1;  /* bit[25]:  */
        unsigned int  reserved_22: 1;  /* bit[26]:  */
        unsigned int  reserved_23: 1;  /* bit[27]:  */
        unsigned int  reserved_24: 1;  /* bit[28]:  */
        unsigned int  reserved_25: 1;  /* bit[29]:  */
        unsigned int  reserved_26: 1;  /* bit[30]:  */
        unsigned int  reserved_27: 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT2SET_UNION;
#endif
#define SOC_TZPC_DECPROT2SET_gpio18_START    (0)
#define SOC_TZPC_DECPROT2SET_gpio18_END      (0)
#define SOC_TZPC_DECPROT2SET_gpio19_START    (1)
#define SOC_TZPC_DECPROT2SET_gpio19_END      (1)
#define SOC_TZPC_DECPROT2SET_gpio20_START    (2)
#define SOC_TZPC_DECPROT2SET_gpio20_END      (2)
#define SOC_TZPC_DECPROT2SET_gpio21_START    (3)
#define SOC_TZPC_DECPROT2SET_gpio21_END      (3)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT2CLR_UNION
 结构说明  : DECPROT2CLR 寄存器结构定义。地址偏移量:0x820，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性清零寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio18   : 1;  /* bit[0] : IP安全属性清零：
                                                 0：IP安全属性不变；
                                                 1：IP安全属性置“0”。 */
        unsigned int  gpio19   : 1;  /* bit[1] :  */
        unsigned int  gpio20   : 1;  /* bit[2] :  */
        unsigned int  gpio21   : 1;  /* bit[3] :  */
        unsigned int  reserved_0: 1;  /* bit[4] :  */
        unsigned int  reserved_1: 1;  /* bit[5] :  */
        unsigned int  reserved_2: 1;  /* bit[6] :  */
        unsigned int  reserved_3: 1;  /* bit[7] :  */
        unsigned int  reserved_4: 1;  /* bit[8] :  */
        unsigned int  reserved_5: 1;  /* bit[9] :  */
        unsigned int  reserved_6: 1;  /* bit[10]:  */
        unsigned int  reserved_7: 1;  /* bit[11]:  */
        unsigned int  reserved_8: 1;  /* bit[12]:  */
        unsigned int  reserved_9: 1;  /* bit[13]:  */
        unsigned int  reserved_10: 1;  /* bit[14]:  */
        unsigned int  reserved_11: 1;  /* bit[15]:  */
        unsigned int  reserved_12: 1;  /* bit[16]:  */
        unsigned int  reserved_13: 1;  /* bit[17]:  */
        unsigned int  reserved_14: 1;  /* bit[18]:  */
        unsigned int  reserved_15: 1;  /* bit[19]:  */
        unsigned int  reserved_16: 1;  /* bit[20]:  */
        unsigned int  reserved_17: 1;  /* bit[21]:  */
        unsigned int  reserved_18: 1;  /* bit[22]:  */
        unsigned int  reserved_19: 1;  /* bit[23]:  */
        unsigned int  reserved_20: 1;  /* bit[24]:  */
        unsigned int  reserved_21: 1;  /* bit[25]:  */
        unsigned int  reserved_22: 1;  /* bit[26]:  */
        unsigned int  reserved_23: 1;  /* bit[27]:  */
        unsigned int  reserved_24: 1;  /* bit[28]:  */
        unsigned int  reserved_25: 1;  /* bit[29]:  */
        unsigned int  reserved_26: 1;  /* bit[30]:  */
        unsigned int  reserved_27: 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT2CLR_UNION;
#endif
#define SOC_TZPC_DECPROT2CLR_gpio18_START    (0)
#define SOC_TZPC_DECPROT2CLR_gpio18_END      (0)
#define SOC_TZPC_DECPROT2CLR_gpio19_START    (1)
#define SOC_TZPC_DECPROT2CLR_gpio19_END      (1)
#define SOC_TZPC_DECPROT2CLR_gpio20_START    (2)
#define SOC_TZPC_DECPROT2CLR_gpio20_END      (2)
#define SOC_TZPC_DECPROT2CLR_gpio21_START    (3)
#define SOC_TZPC_DECPROT2CLR_gpio21_END      (3)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT3STAT_UNION
 结构说明  : DECPROT3STAT 寄存器结构定义。地址偏移量:0x824，初值:0x00030303，宽度:32
 寄存器说明: IP安全属性状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vdec_firewall  : 8;  /* bit[0-7]  : bit0：firewall的使能控制，默认使能。
                                                          bit1：firewall发现越权是否上报error，默认上报。
                                                          bit2：vdec slv的安全属性，默认是安全属性。
                                                          bit[5:3]：保留。
                                                          bit6：默认为0。
                                                          0: VDEC处于安全态。当vdec处于安全态时，其内部关键寄存器不能够被非安全os访问。
                                                          1：VDEC处于非安全态。当vdec处于非安全态时，其内部所有寄存器能够被非安全os\安全os访问。
                                                          bit7：访问VDEC的命令强制转换为安全命令使能位，默认为0，打开使能（废弃该功能，初始化时需要配置为1）。 */
        unsigned int  venc_firewall  : 8;  /* bit[8-15] : bit0：firewall的使能控制，默认使能。
                                                          bit1：firewall发现越权是否上报error，默认上报。
                                                          bit2：venc slv的安全属性，默认是安全属性。
                                                          bit[7:3]：保留。 */
        unsigned int  hkmem_firewall : 8;  /* bit[16-23]: bit0：firewall的使能控制，默认使能。
                                                          bit1：firewall发现越权是否上报error，默认上报。
                                                          bit2：hkmem slv的安全属性，默认是安全属性。
                                                          bit[7:3]：保留。 */
        unsigned int  g3d            : 1;  /* bit[24]   : g3d slv上电默认为安全属性。 */
        unsigned int  reserved_0     : 1;  /* bit[25]   : 保留。 */
        unsigned int  emmc0          : 1;  /* bit[26]   : emmc0 slv上电默认为安全属性。 */
        unsigned int  emmc1          : 1;  /* bit[27]   : emmc1 slv上电默认为安全属性。 */
        unsigned int  sd30           : 1;  /* bit[28]   : sd30 slv上电默认为安全属性。 */
        unsigned int  sdio0          : 1;  /* bit[29]   : sdio0 slv上电默认为安全属性。 */
        unsigned int  sdio1          : 1;  /* bit[30]   : sdio1 slv上电默认为安全属性。 */
        unsigned int  reserved_1     : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_TZPC_DECPROT3STAT_UNION;
#endif
#define SOC_TZPC_DECPROT3STAT_vdec_firewall_START   (0)
#define SOC_TZPC_DECPROT3STAT_vdec_firewall_END     (7)
#define SOC_TZPC_DECPROT3STAT_venc_firewall_START   (8)
#define SOC_TZPC_DECPROT3STAT_venc_firewall_END     (15)
#define SOC_TZPC_DECPROT3STAT_hkmem_firewall_START  (16)
#define SOC_TZPC_DECPROT3STAT_hkmem_firewall_END    (23)
#define SOC_TZPC_DECPROT3STAT_g3d_START             (24)
#define SOC_TZPC_DECPROT3STAT_g3d_END               (24)
#define SOC_TZPC_DECPROT3STAT_emmc0_START           (26)
#define SOC_TZPC_DECPROT3STAT_emmc0_END             (26)
#define SOC_TZPC_DECPROT3STAT_emmc1_START           (27)
#define SOC_TZPC_DECPROT3STAT_emmc1_END             (27)
#define SOC_TZPC_DECPROT3STAT_sd30_START            (28)
#define SOC_TZPC_DECPROT3STAT_sd30_END              (28)
#define SOC_TZPC_DECPROT3STAT_sdio0_START           (29)
#define SOC_TZPC_DECPROT3STAT_sdio0_END             (29)
#define SOC_TZPC_DECPROT3STAT_sdio1_START           (30)
#define SOC_TZPC_DECPROT3STAT_sdio1_END             (30)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT3SET_UNION
 结构说明  : DECPROT3SET 寄存器结构定义。地址偏移量:0x828，初值:0x00030303，宽度:32
 寄存器说明: IP安全属性置位寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vdec_firewall  : 8;  /* bit[0-7]  : IP安全属性置位：
                                                          0：IP安全属性不变；
                                                          1：IP安全属性置“1”。 */
        unsigned int  venc_firewall  : 8;  /* bit[8-15] :  */
        unsigned int  hkmem_firewall : 8;  /* bit[16-23]:  */
        unsigned int  g3d            : 1;  /* bit[24]   :  */
        unsigned int  reserved_0     : 1;  /* bit[25]   :  */
        unsigned int  emmc0          : 1;  /* bit[26]   :  */
        unsigned int  emmc1          : 1;  /* bit[27]   :  */
        unsigned int  sd30           : 1;  /* bit[28]   :  */
        unsigned int  sdio0          : 1;  /* bit[29]   :  */
        unsigned int  sdio1          : 1;  /* bit[30]   :  */
        unsigned int  reserved_1     : 1;  /* bit[31]   :  */
    } reg;
} SOC_TZPC_DECPROT3SET_UNION;
#endif
#define SOC_TZPC_DECPROT3SET_vdec_firewall_START   (0)
#define SOC_TZPC_DECPROT3SET_vdec_firewall_END     (7)
#define SOC_TZPC_DECPROT3SET_venc_firewall_START   (8)
#define SOC_TZPC_DECPROT3SET_venc_firewall_END     (15)
#define SOC_TZPC_DECPROT3SET_hkmem_firewall_START  (16)
#define SOC_TZPC_DECPROT3SET_hkmem_firewall_END    (23)
#define SOC_TZPC_DECPROT3SET_g3d_START             (24)
#define SOC_TZPC_DECPROT3SET_g3d_END               (24)
#define SOC_TZPC_DECPROT3SET_emmc0_START           (26)
#define SOC_TZPC_DECPROT3SET_emmc0_END             (26)
#define SOC_TZPC_DECPROT3SET_emmc1_START           (27)
#define SOC_TZPC_DECPROT3SET_emmc1_END             (27)
#define SOC_TZPC_DECPROT3SET_sd30_START            (28)
#define SOC_TZPC_DECPROT3SET_sd30_END              (28)
#define SOC_TZPC_DECPROT3SET_sdio0_START           (29)
#define SOC_TZPC_DECPROT3SET_sdio0_END             (29)
#define SOC_TZPC_DECPROT3SET_sdio1_START           (30)
#define SOC_TZPC_DECPROT3SET_sdio1_END             (30)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT3CLR_UNION
 结构说明  : DECPROT3CLR 寄存器结构定义。地址偏移量:0x82C，初值:0x00030303，宽度:32
 寄存器说明: IP安全属性清零寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vdec_firewall  : 8;  /* bit[0-7]  : IP安全属性清零：
                                                          0：IP安全属性不变；
                                                          1：IP安全属性置“0”。 */
        unsigned int  venc_firewall  : 8;  /* bit[8-15] :  */
        unsigned int  hkmem_firewall : 8;  /* bit[16-23]:  */
        unsigned int  g3d            : 1;  /* bit[24]   :  */
        unsigned int  reserved_0     : 1;  /* bit[25]   :  */
        unsigned int  emmc0          : 1;  /* bit[26]   :  */
        unsigned int  emmc1          : 1;  /* bit[27]   :  */
        unsigned int  sd30           : 1;  /* bit[28]   :  */
        unsigned int  sdio0          : 1;  /* bit[29]   :  */
        unsigned int  sdio1          : 1;  /* bit[30]   :  */
        unsigned int  reserved_1     : 1;  /* bit[31]   :  */
    } reg;
} SOC_TZPC_DECPROT3CLR_UNION;
#endif
#define SOC_TZPC_DECPROT3CLR_vdec_firewall_START   (0)
#define SOC_TZPC_DECPROT3CLR_vdec_firewall_END     (7)
#define SOC_TZPC_DECPROT3CLR_venc_firewall_START   (8)
#define SOC_TZPC_DECPROT3CLR_venc_firewall_END     (15)
#define SOC_TZPC_DECPROT3CLR_hkmem_firewall_START  (16)
#define SOC_TZPC_DECPROT3CLR_hkmem_firewall_END    (23)
#define SOC_TZPC_DECPROT3CLR_g3d_START             (24)
#define SOC_TZPC_DECPROT3CLR_g3d_END               (24)
#define SOC_TZPC_DECPROT3CLR_emmc0_START           (26)
#define SOC_TZPC_DECPROT3CLR_emmc0_END             (26)
#define SOC_TZPC_DECPROT3CLR_emmc1_START           (27)
#define SOC_TZPC_DECPROT3CLR_emmc1_END             (27)
#define SOC_TZPC_DECPROT3CLR_sd30_START            (28)
#define SOC_TZPC_DECPROT3CLR_sd30_END              (28)
#define SOC_TZPC_DECPROT3CLR_sdio0_START           (29)
#define SOC_TZPC_DECPROT3CLR_sdio0_END             (29)
#define SOC_TZPC_DECPROT3CLR_sdio1_START           (30)
#define SOC_TZPC_DECPROT3CLR_sdio1_END             (30)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT4STAT_UNION
 结构说明  : DECPROT4STAT 寄存器结构定义。地址偏移量:0x830，初值:0x00000001，宽度:32
 寄存器说明: IP安全属性状态寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socp       : 1;  /* bit[0] : socp slv上电默认为非安全属性，socp ip本身具备了安全非安全特性，不需要tzpc进行安全非安全控制。 */
        unsigned int  usb3otg    : 1;  /* bit[1] : USB3OTG（内部寄存器） slv上电默认为安全属性。 */
        unsigned int  usb3otg_bc : 1;  /* bit[2] : USB3OTG （BC寄存器） slv上电默认为安全属性。 */
        unsigned int  perf_stat  : 1;  /* bit[3] : perf_stat slv上电默认为安全属性。 */
        unsigned int  reserved_0 : 1;  /* bit[4] : 保留。 */
        unsigned int  ipcns      : 1;  /* bit[5] : ipcns slv上电默认为安全属性。 */
        unsigned int  ipc        : 1;  /* bit[6] : ipc slv上电默认为安全属性。 */
        unsigned int  ioc        : 1;  /* bit[7] : ioc slv上电默认为安全属性。 */
        unsigned int  vcodecbus  : 1;  /* bit[8] : VCODECBUS(0xE8920000~0xE895FFFF) slv上电默认为安全属性。 */
        unsigned int  reserved_1 : 1;  /* bit[9] : 保留。 */
        unsigned int  hkadc_ssi  : 1;  /* bit[10]: hkadcssi slv上电默认为安全属性。 */
        unsigned int  codec_ssi  : 1;  /* bit[11]: codecssi slv上电默认为安全属性。 */
        unsigned int  reserved_2 : 1;  /* bit[12]: 保留。 */
        unsigned int  ipc_mdm    : 1;  /* bit[13]: ipc_mdm slv上电默认为安全属性。 */
        unsigned int  uart0      : 1;  /* bit[14]: uart0 slv上电默认为安全属性。 */
        unsigned int  uart1      : 1;  /* bit[15]: uart1 slv上电默认为安全属性。 */
        unsigned int  uart2      : 1;  /* bit[16]: uart2 slv上电默认为安全属性。 */
        unsigned int  uart4      : 1;  /* bit[17]: uart4 slv上电默认为安全属性。 */
        unsigned int  uart5      : 1;  /* bit[18]: uart5 slv上电默认为安全属性。 */
        unsigned int  spi1       : 1;  /* bit[19]: spi1 slv上电默认为安全属性。 */
        unsigned int  i2c3       : 1;  /* bit[20]: i2c3 slv上电默认为安全属性。 */
        unsigned int  i2c4       : 1;  /* bit[21]: i2c4 slv上电默认为安全属性。 */
        unsigned int  ddrc       : 1;  /* bit[22]: DDRC内部关键寄存器的锁使能控制，使能锁后将不可配置关键寄存器，默认为0，不使能锁。 */
        unsigned int  bisr       : 1;  /* bit[23]: bisr slv上电默认为安全属性。 */
        unsigned int  reserved_3 : 1;  /* bit[24]: 保留。 */
        unsigned int  reserved_4 : 1;  /* bit[25]: 保留。 */
        unsigned int  reserved_5 : 1;  /* bit[26]: 保留。 */
        unsigned int  reserved_6 : 1;  /* bit[27]: 保留。 */
        unsigned int  reserved_7 : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_8 : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_9 : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_10: 1;  /* bit[31]: 保留。 */
    } reg;
} SOC_TZPC_DECPROT4STAT_UNION;
#endif
#define SOC_TZPC_DECPROT4STAT_socp_START        (0)
#define SOC_TZPC_DECPROT4STAT_socp_END          (0)
#define SOC_TZPC_DECPROT4STAT_usb3otg_START     (1)
#define SOC_TZPC_DECPROT4STAT_usb3otg_END       (1)
#define SOC_TZPC_DECPROT4STAT_usb3otg_bc_START  (2)
#define SOC_TZPC_DECPROT4STAT_usb3otg_bc_END    (2)
#define SOC_TZPC_DECPROT4STAT_perf_stat_START   (3)
#define SOC_TZPC_DECPROT4STAT_perf_stat_END     (3)
#define SOC_TZPC_DECPROT4STAT_ipcns_START       (5)
#define SOC_TZPC_DECPROT4STAT_ipcns_END         (5)
#define SOC_TZPC_DECPROT4STAT_ipc_START         (6)
#define SOC_TZPC_DECPROT4STAT_ipc_END           (6)
#define SOC_TZPC_DECPROT4STAT_ioc_START         (7)
#define SOC_TZPC_DECPROT4STAT_ioc_END           (7)
#define SOC_TZPC_DECPROT4STAT_vcodecbus_START   (8)
#define SOC_TZPC_DECPROT4STAT_vcodecbus_END     (8)
#define SOC_TZPC_DECPROT4STAT_hkadc_ssi_START   (10)
#define SOC_TZPC_DECPROT4STAT_hkadc_ssi_END     (10)
#define SOC_TZPC_DECPROT4STAT_codec_ssi_START   (11)
#define SOC_TZPC_DECPROT4STAT_codec_ssi_END     (11)
#define SOC_TZPC_DECPROT4STAT_ipc_mdm_START     (13)
#define SOC_TZPC_DECPROT4STAT_ipc_mdm_END       (13)
#define SOC_TZPC_DECPROT4STAT_uart0_START       (14)
#define SOC_TZPC_DECPROT4STAT_uart0_END         (14)
#define SOC_TZPC_DECPROT4STAT_uart1_START       (15)
#define SOC_TZPC_DECPROT4STAT_uart1_END         (15)
#define SOC_TZPC_DECPROT4STAT_uart2_START       (16)
#define SOC_TZPC_DECPROT4STAT_uart2_END         (16)
#define SOC_TZPC_DECPROT4STAT_uart4_START       (17)
#define SOC_TZPC_DECPROT4STAT_uart4_END         (17)
#define SOC_TZPC_DECPROT4STAT_uart5_START       (18)
#define SOC_TZPC_DECPROT4STAT_uart5_END         (18)
#define SOC_TZPC_DECPROT4STAT_spi1_START        (19)
#define SOC_TZPC_DECPROT4STAT_spi1_END          (19)
#define SOC_TZPC_DECPROT4STAT_i2c3_START        (20)
#define SOC_TZPC_DECPROT4STAT_i2c3_END          (20)
#define SOC_TZPC_DECPROT4STAT_i2c4_START        (21)
#define SOC_TZPC_DECPROT4STAT_i2c4_END          (21)
#define SOC_TZPC_DECPROT4STAT_ddrc_START        (22)
#define SOC_TZPC_DECPROT4STAT_ddrc_END          (22)
#define SOC_TZPC_DECPROT4STAT_bisr_START        (23)
#define SOC_TZPC_DECPROT4STAT_bisr_END          (23)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT4SET_UNION
 结构说明  : DECPROT4SET 寄存器结构定义。地址偏移量:0x834，初值:0x00000001，宽度:32
 寄存器说明: IP安全属性置位寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socp       : 1;  /* bit[0] : IP安全属性置位：
                                                   0：IP安全属性不变；
                                                   1：IP安全属性置“1”。 */
        unsigned int  usb3otg    : 1;  /* bit[1] :  */
        unsigned int  usb3otg_bc : 1;  /* bit[2] :  */
        unsigned int  perf_stat  : 1;  /* bit[3] :  */
        unsigned int  reserved_0 : 1;  /* bit[4] :  */
        unsigned int  ipcns      : 1;  /* bit[5] :  */
        unsigned int  ipc        : 1;  /* bit[6] :  */
        unsigned int  ioc        : 1;  /* bit[7] :  */
        unsigned int  vcodecbus  : 1;  /* bit[8] :  */
        unsigned int  reserved_1 : 1;  /* bit[9] :  */
        unsigned int  hkadc_ssi  : 1;  /* bit[10]:  */
        unsigned int  codec_ssi  : 1;  /* bit[11]:  */
        unsigned int  reserved_2 : 1;  /* bit[12]:  */
        unsigned int  ipc_mdm    : 1;  /* bit[13]:  */
        unsigned int  uart0      : 1;  /* bit[14]:  */
        unsigned int  uart1      : 1;  /* bit[15]:  */
        unsigned int  uart2      : 1;  /* bit[16]:  */
        unsigned int  uart4      : 1;  /* bit[17]:  */
        unsigned int  uart5      : 1;  /* bit[18]:  */
        unsigned int  spi1       : 1;  /* bit[19]:  */
        unsigned int  i2c3       : 1;  /* bit[20]:  */
        unsigned int  i2c4       : 1;  /* bit[21]:  */
        unsigned int  ddrc       : 1;  /* bit[22]:  */
        unsigned int  bisr       : 1;  /* bit[23]:  */
        unsigned int  reserved_3 : 1;  /* bit[24]:  */
        unsigned int  reserved_4 : 1;  /* bit[25]:  */
        unsigned int  reserved_5 : 1;  /* bit[26]:  */
        unsigned int  reserved_6 : 1;  /* bit[27]:  */
        unsigned int  reserved_7 : 1;  /* bit[28]:  */
        unsigned int  reserved_8 : 1;  /* bit[29]:  */
        unsigned int  reserved_9 : 1;  /* bit[30]:  */
        unsigned int  reserved_10: 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT4SET_UNION;
#endif
#define SOC_TZPC_DECPROT4SET_socp_START        (0)
#define SOC_TZPC_DECPROT4SET_socp_END          (0)
#define SOC_TZPC_DECPROT4SET_usb3otg_START     (1)
#define SOC_TZPC_DECPROT4SET_usb3otg_END       (1)
#define SOC_TZPC_DECPROT4SET_usb3otg_bc_START  (2)
#define SOC_TZPC_DECPROT4SET_usb3otg_bc_END    (2)
#define SOC_TZPC_DECPROT4SET_perf_stat_START   (3)
#define SOC_TZPC_DECPROT4SET_perf_stat_END     (3)
#define SOC_TZPC_DECPROT4SET_ipcns_START       (5)
#define SOC_TZPC_DECPROT4SET_ipcns_END         (5)
#define SOC_TZPC_DECPROT4SET_ipc_START         (6)
#define SOC_TZPC_DECPROT4SET_ipc_END           (6)
#define SOC_TZPC_DECPROT4SET_ioc_START         (7)
#define SOC_TZPC_DECPROT4SET_ioc_END           (7)
#define SOC_TZPC_DECPROT4SET_vcodecbus_START   (8)
#define SOC_TZPC_DECPROT4SET_vcodecbus_END     (8)
#define SOC_TZPC_DECPROT4SET_hkadc_ssi_START   (10)
#define SOC_TZPC_DECPROT4SET_hkadc_ssi_END     (10)
#define SOC_TZPC_DECPROT4SET_codec_ssi_START   (11)
#define SOC_TZPC_DECPROT4SET_codec_ssi_END     (11)
#define SOC_TZPC_DECPROT4SET_ipc_mdm_START     (13)
#define SOC_TZPC_DECPROT4SET_ipc_mdm_END       (13)
#define SOC_TZPC_DECPROT4SET_uart0_START       (14)
#define SOC_TZPC_DECPROT4SET_uart0_END         (14)
#define SOC_TZPC_DECPROT4SET_uart1_START       (15)
#define SOC_TZPC_DECPROT4SET_uart1_END         (15)
#define SOC_TZPC_DECPROT4SET_uart2_START       (16)
#define SOC_TZPC_DECPROT4SET_uart2_END         (16)
#define SOC_TZPC_DECPROT4SET_uart4_START       (17)
#define SOC_TZPC_DECPROT4SET_uart4_END         (17)
#define SOC_TZPC_DECPROT4SET_uart5_START       (18)
#define SOC_TZPC_DECPROT4SET_uart5_END         (18)
#define SOC_TZPC_DECPROT4SET_spi1_START        (19)
#define SOC_TZPC_DECPROT4SET_spi1_END          (19)
#define SOC_TZPC_DECPROT4SET_i2c3_START        (20)
#define SOC_TZPC_DECPROT4SET_i2c3_END          (20)
#define SOC_TZPC_DECPROT4SET_i2c4_START        (21)
#define SOC_TZPC_DECPROT4SET_i2c4_END          (21)
#define SOC_TZPC_DECPROT4SET_ddrc_START        (22)
#define SOC_TZPC_DECPROT4SET_ddrc_END          (22)
#define SOC_TZPC_DECPROT4SET_bisr_START        (23)
#define SOC_TZPC_DECPROT4SET_bisr_END          (23)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT4CLR_UNION
 结构说明  : DECPROT4CLR 寄存器结构定义。地址偏移量:0x838，初值:0x00000001，宽度:32
 寄存器说明: IP安全属性清零寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socp       : 1;  /* bit[0] : IP安全属性清零：
                                                   0：IP安全属性不变；
                                                   1：IP安全属性置“0”。 */
        unsigned int  usb3otg    : 1;  /* bit[1] :  */
        unsigned int  usb3otg_bc : 1;  /* bit[2] :  */
        unsigned int  perf_stat  : 1;  /* bit[3] :  */
        unsigned int  reserved_0 : 1;  /* bit[4] :  */
        unsigned int  ipcns      : 1;  /* bit[5] :  */
        unsigned int  ipc        : 1;  /* bit[6] :  */
        unsigned int  ioc        : 1;  /* bit[7] :  */
        unsigned int  vcodecbus  : 1;  /* bit[8] :  */
        unsigned int  reserved_1 : 1;  /* bit[9] :  */
        unsigned int  hkadc_ssi  : 1;  /* bit[10]:  */
        unsigned int  codec_ssi  : 1;  /* bit[11]:  */
        unsigned int  reserved_2 : 1;  /* bit[12]:  */
        unsigned int  ipc_mdm    : 1;  /* bit[13]:  */
        unsigned int  uart0      : 1;  /* bit[14]:  */
        unsigned int  uart1      : 1;  /* bit[15]:  */
        unsigned int  uart2      : 1;  /* bit[16]:  */
        unsigned int  uart4      : 1;  /* bit[17]:  */
        unsigned int  uart5      : 1;  /* bit[18]:  */
        unsigned int  spi1       : 1;  /* bit[19]:  */
        unsigned int  i2c3       : 1;  /* bit[20]:  */
        unsigned int  i2c4       : 1;  /* bit[21]:  */
        unsigned int  ddrc       : 1;  /* bit[22]:  */
        unsigned int  bisr       : 1;  /* bit[23]:  */
        unsigned int  reserved_3 : 1;  /* bit[24]:  */
        unsigned int  reserved_4 : 1;  /* bit[25]:  */
        unsigned int  reserved_5 : 1;  /* bit[26]:  */
        unsigned int  reserved_6 : 1;  /* bit[27]:  */
        unsigned int  reserved_7 : 1;  /* bit[28]:  */
        unsigned int  reserved_8 : 1;  /* bit[29]:  */
        unsigned int  reserved_9 : 1;  /* bit[30]:  */
        unsigned int  reserved_10: 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT4CLR_UNION;
#endif
#define SOC_TZPC_DECPROT4CLR_socp_START        (0)
#define SOC_TZPC_DECPROT4CLR_socp_END          (0)
#define SOC_TZPC_DECPROT4CLR_usb3otg_START     (1)
#define SOC_TZPC_DECPROT4CLR_usb3otg_END       (1)
#define SOC_TZPC_DECPROT4CLR_usb3otg_bc_START  (2)
#define SOC_TZPC_DECPROT4CLR_usb3otg_bc_END    (2)
#define SOC_TZPC_DECPROT4CLR_perf_stat_START   (3)
#define SOC_TZPC_DECPROT4CLR_perf_stat_END     (3)
#define SOC_TZPC_DECPROT4CLR_ipcns_START       (5)
#define SOC_TZPC_DECPROT4CLR_ipcns_END         (5)
#define SOC_TZPC_DECPROT4CLR_ipc_START         (6)
#define SOC_TZPC_DECPROT4CLR_ipc_END           (6)
#define SOC_TZPC_DECPROT4CLR_ioc_START         (7)
#define SOC_TZPC_DECPROT4CLR_ioc_END           (7)
#define SOC_TZPC_DECPROT4CLR_vcodecbus_START   (8)
#define SOC_TZPC_DECPROT4CLR_vcodecbus_END     (8)
#define SOC_TZPC_DECPROT4CLR_hkadc_ssi_START   (10)
#define SOC_TZPC_DECPROT4CLR_hkadc_ssi_END     (10)
#define SOC_TZPC_DECPROT4CLR_codec_ssi_START   (11)
#define SOC_TZPC_DECPROT4CLR_codec_ssi_END     (11)
#define SOC_TZPC_DECPROT4CLR_ipc_mdm_START     (13)
#define SOC_TZPC_DECPROT4CLR_ipc_mdm_END       (13)
#define SOC_TZPC_DECPROT4CLR_uart0_START       (14)
#define SOC_TZPC_DECPROT4CLR_uart0_END         (14)
#define SOC_TZPC_DECPROT4CLR_uart1_START       (15)
#define SOC_TZPC_DECPROT4CLR_uart1_END         (15)
#define SOC_TZPC_DECPROT4CLR_uart2_START       (16)
#define SOC_TZPC_DECPROT4CLR_uart2_END         (16)
#define SOC_TZPC_DECPROT4CLR_uart4_START       (17)
#define SOC_TZPC_DECPROT4CLR_uart4_END         (17)
#define SOC_TZPC_DECPROT4CLR_uart5_START       (18)
#define SOC_TZPC_DECPROT4CLR_uart5_END         (18)
#define SOC_TZPC_DECPROT4CLR_spi1_START        (19)
#define SOC_TZPC_DECPROT4CLR_spi1_END          (19)
#define SOC_TZPC_DECPROT4CLR_i2c3_START        (20)
#define SOC_TZPC_DECPROT4CLR_i2c3_END          (20)
#define SOC_TZPC_DECPROT4CLR_i2c4_START        (21)
#define SOC_TZPC_DECPROT4CLR_i2c4_END          (21)
#define SOC_TZPC_DECPROT4CLR_ddrc_START        (22)
#define SOC_TZPC_DECPROT4CLR_ddrc_END          (22)
#define SOC_TZPC_DECPROT4CLR_bisr_START        (23)
#define SOC_TZPC_DECPROT4CLR_bisr_END          (23)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT5STAT_UNION
 结构说明  : DECPROT5STAT 寄存器结构定义。地址偏移量:0x83C，初值:0x00300000，宽度:32
 寄存器说明: IP安全属性状态寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3_pmussi1  : 1;  /* bit[0] : lpm3_pmussi1 slv上电默认为安全属性。 */
        unsigned int  ddrc          : 1;  /* bit[1] : ddrc slv上电默认为安全属性。 */
        unsigned int  lpm3_tsensorc : 1;  /* bit[2] : lpm3_tsensorc slv上电默认为安全属性。 */
        unsigned int  lpm3_pmc      : 1;  /* bit[3] : lpm3_pmc slv上电默认为安全属性。 */
        unsigned int  lpm3_uart     : 1;  /* bit[4] : lpm3_uart slv上电默认为安全属性。 */
        unsigned int  lpm3_pmui2c   : 1;  /* bit[5] : lpm3_pmui2c slv上电默认为安全属性。 */
        unsigned int  lpm3_pmussi0  : 1;  /* bit[6] : lpm3_pmussi0 slv上电默认为安全属性。 */
        unsigned int  crg_region1   : 1;  /* bit[7] : CRG(region1：0x000~0xBFF)上电默认为安全属性。 */
        unsigned int  crg_region2   : 1;  /* bit[8] : CRG(region2：0xC00~0xC7F)IVP子系统软复位控制，上电默认为安全属性。 */
        unsigned int  crg_region3   : 1;  /* bit[9] : CRG(region3：0xC80~0xCFF)ISP子系统软复位控制，上电默认为安全属性。 */
        unsigned int  crg_region4   : 1;  /* bit[10]: CRG(region4：0xD00~0xDFF)Modem子系统软复位控制，上电默认为安全属性。 */
        unsigned int  crg_region5   : 1;  /* bit[11]: CRG(region5：0xE00~0xFFF)，上电默认为安全属性。 */
        unsigned int  lpm3_wd       : 1;  /* bit[12]: lpm3_wd slv上电默认为安全属性。 */
        unsigned int  lpm3_timer    : 1;  /* bit[13]: lpm3_timer slv上电默认为安全属性。 */
        unsigned int  lpm3_config   : 1;  /* bit[14]: lpm3_config slv上电默认为安全属性。 */
        unsigned int  lpm3_nandc    : 1;  /* bit[15]: lpm3_nandc slv上电默认为安全属性。 */
        unsigned int  lpm3_gnspwm   : 1;  /* bit[16]: lpm3_gnspwm slv上电默认为安全属性。 */
        unsigned int  lpm3_ram      : 1;  /* bit[17]: lpm3_ram slv上电默认为安全属性。 */
        unsigned int  reserved_0    : 1;  /* bit[18]: 保留。 */
        unsigned int  reserved_1    : 1;  /* bit[19]: 保留。 */
        unsigned int  reserved_2    : 1;  /* bit[20]: 保留。 */
        unsigned int  reserved_3    : 1;  /* bit[21]: 保留。 */
        unsigned int  reserved_4    : 1;  /* bit[22]: 保留。 */
        unsigned int  reserved_5    : 1;  /* bit[23]: 保留。 */
        unsigned int  reserved_6    : 1;  /* bit[24]: 保留。 */
        unsigned int  reserved_7    : 1;  /* bit[25]: 保留。 */
        unsigned int  reserved_8    : 1;  /* bit[26]: 保留。 */
        unsigned int  reserved_9    : 1;  /* bit[27]: 保留。 */
        unsigned int  reserved_10   : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_11   : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_12   : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_13   : 1;  /* bit[31]: 保留。 */
    } reg;
} SOC_TZPC_DECPROT5STAT_UNION;
#endif
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi1_START   (0)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi1_END     (0)
#define SOC_TZPC_DECPROT5STAT_ddrc_START           (1)
#define SOC_TZPC_DECPROT5STAT_ddrc_END             (1)
#define SOC_TZPC_DECPROT5STAT_lpm3_tsensorc_START  (2)
#define SOC_TZPC_DECPROT5STAT_lpm3_tsensorc_END    (2)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmc_START       (3)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmc_END         (3)
#define SOC_TZPC_DECPROT5STAT_lpm3_uart_START      (4)
#define SOC_TZPC_DECPROT5STAT_lpm3_uart_END        (4)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmui2c_START    (5)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmui2c_END      (5)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi0_START   (6)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi0_END     (6)
#define SOC_TZPC_DECPROT5STAT_crg_region1_START    (7)
#define SOC_TZPC_DECPROT5STAT_crg_region1_END      (7)
#define SOC_TZPC_DECPROT5STAT_crg_region2_START    (8)
#define SOC_TZPC_DECPROT5STAT_crg_region2_END      (8)
#define SOC_TZPC_DECPROT5STAT_crg_region3_START    (9)
#define SOC_TZPC_DECPROT5STAT_crg_region3_END      (9)
#define SOC_TZPC_DECPROT5STAT_crg_region4_START    (10)
#define SOC_TZPC_DECPROT5STAT_crg_region4_END      (10)
#define SOC_TZPC_DECPROT5STAT_crg_region5_START    (11)
#define SOC_TZPC_DECPROT5STAT_crg_region5_END      (11)
#define SOC_TZPC_DECPROT5STAT_lpm3_wd_START        (12)
#define SOC_TZPC_DECPROT5STAT_lpm3_wd_END          (12)
#define SOC_TZPC_DECPROT5STAT_lpm3_timer_START     (13)
#define SOC_TZPC_DECPROT5STAT_lpm3_timer_END       (13)
#define SOC_TZPC_DECPROT5STAT_lpm3_config_START    (14)
#define SOC_TZPC_DECPROT5STAT_lpm3_config_END      (14)
#define SOC_TZPC_DECPROT5STAT_lpm3_nandc_START     (15)
#define SOC_TZPC_DECPROT5STAT_lpm3_nandc_END       (15)
#define SOC_TZPC_DECPROT5STAT_lpm3_gnspwm_START    (16)
#define SOC_TZPC_DECPROT5STAT_lpm3_gnspwm_END      (16)
#define SOC_TZPC_DECPROT5STAT_lpm3_ram_START       (17)
#define SOC_TZPC_DECPROT5STAT_lpm3_ram_END         (17)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT5SET_UNION
 结构说明  : DECPROT5SET 寄存器结构定义。地址偏移量:0x840，初值:0x00300000，宽度:32
 寄存器说明: IP安全属性置位寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3_pmussi1  : 1;  /* bit[0] : IP安全属性置位：
                                                      0：IP安全属性不变；
                                                      1：IP安全属性置“1”。 */
        unsigned int  ddrc          : 1;  /* bit[1] :  */
        unsigned int  lpm3_tsensorc : 1;  /* bit[2] :  */
        unsigned int  lpm3_pmc      : 1;  /* bit[3] :  */
        unsigned int  lpm3_uart     : 1;  /* bit[4] :  */
        unsigned int  lpm3_pmui2c   : 1;  /* bit[5] :  */
        unsigned int  lpm3_pmussi0  : 1;  /* bit[6] :  */
        unsigned int  crg_region1   : 1;  /* bit[7] :  */
        unsigned int  crg_region2   : 1;  /* bit[8] :  */
        unsigned int  crg_region3   : 1;  /* bit[9] :  */
        unsigned int  crg_region4   : 1;  /* bit[10]:  */
        unsigned int  crg_region5   : 1;  /* bit[11]:  */
        unsigned int  lpm3_wd       : 1;  /* bit[12]:  */
        unsigned int  lpm3_timer    : 1;  /* bit[13]:  */
        unsigned int  lpm3_config   : 1;  /* bit[14]:  */
        unsigned int  lpm3_nandc    : 1;  /* bit[15]:  */
        unsigned int  lpm3_gnspwm   : 1;  /* bit[16]:  */
        unsigned int  lpm3_ram      : 1;  /* bit[17]:  */
        unsigned int  reserved_0    : 1;  /* bit[18]:  */
        unsigned int  reserved_1    : 1;  /* bit[19]:  */
        unsigned int  reserved_2    : 1;  /* bit[20]:  */
        unsigned int  reserved_3    : 1;  /* bit[21]:  */
        unsigned int  reserved_4    : 1;  /* bit[22]:  */
        unsigned int  reserved_5    : 1;  /* bit[23]:  */
        unsigned int  reserved_6    : 1;  /* bit[24]:  */
        unsigned int  reserved_7    : 1;  /* bit[25]:  */
        unsigned int  reserved_8    : 1;  /* bit[26]:  */
        unsigned int  reserved_9    : 1;  /* bit[27]:  */
        unsigned int  reserved_10   : 1;  /* bit[28]:  */
        unsigned int  reserved_11   : 1;  /* bit[29]:  */
        unsigned int  reserved_12   : 1;  /* bit[30]:  */
        unsigned int  reserved_13   : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT5SET_UNION;
#endif
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi1_START   (0)
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi1_END     (0)
#define SOC_TZPC_DECPROT5SET_ddrc_START           (1)
#define SOC_TZPC_DECPROT5SET_ddrc_END             (1)
#define SOC_TZPC_DECPROT5SET_lpm3_tsensorc_START  (2)
#define SOC_TZPC_DECPROT5SET_lpm3_tsensorc_END    (2)
#define SOC_TZPC_DECPROT5SET_lpm3_pmc_START       (3)
#define SOC_TZPC_DECPROT5SET_lpm3_pmc_END         (3)
#define SOC_TZPC_DECPROT5SET_lpm3_uart_START      (4)
#define SOC_TZPC_DECPROT5SET_lpm3_uart_END        (4)
#define SOC_TZPC_DECPROT5SET_lpm3_pmui2c_START    (5)
#define SOC_TZPC_DECPROT5SET_lpm3_pmui2c_END      (5)
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi0_START   (6)
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi0_END     (6)
#define SOC_TZPC_DECPROT5SET_crg_region1_START    (7)
#define SOC_TZPC_DECPROT5SET_crg_region1_END      (7)
#define SOC_TZPC_DECPROT5SET_crg_region2_START    (8)
#define SOC_TZPC_DECPROT5SET_crg_region2_END      (8)
#define SOC_TZPC_DECPROT5SET_crg_region3_START    (9)
#define SOC_TZPC_DECPROT5SET_crg_region3_END      (9)
#define SOC_TZPC_DECPROT5SET_crg_region4_START    (10)
#define SOC_TZPC_DECPROT5SET_crg_region4_END      (10)
#define SOC_TZPC_DECPROT5SET_crg_region5_START    (11)
#define SOC_TZPC_DECPROT5SET_crg_region5_END      (11)
#define SOC_TZPC_DECPROT5SET_lpm3_wd_START        (12)
#define SOC_TZPC_DECPROT5SET_lpm3_wd_END          (12)
#define SOC_TZPC_DECPROT5SET_lpm3_timer_START     (13)
#define SOC_TZPC_DECPROT5SET_lpm3_timer_END       (13)
#define SOC_TZPC_DECPROT5SET_lpm3_config_START    (14)
#define SOC_TZPC_DECPROT5SET_lpm3_config_END      (14)
#define SOC_TZPC_DECPROT5SET_lpm3_nandc_START     (15)
#define SOC_TZPC_DECPROT5SET_lpm3_nandc_END       (15)
#define SOC_TZPC_DECPROT5SET_lpm3_gnspwm_START    (16)
#define SOC_TZPC_DECPROT5SET_lpm3_gnspwm_END      (16)
#define SOC_TZPC_DECPROT5SET_lpm3_ram_START       (17)
#define SOC_TZPC_DECPROT5SET_lpm3_ram_END         (17)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT5CLR_UNION
 结构说明  : DECPROT5CLR 寄存器结构定义。地址偏移量:0x844，初值:0x00300000，宽度:32
 寄存器说明: IP安全属性清零寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3_pmussi1  : 1;  /* bit[0] : IP安全属性清零：
                                                      0：IP安全属性不变；
                                                      1：IP安全属性置“0”。 */
        unsigned int  ddrc          : 1;  /* bit[1] :  */
        unsigned int  lpm3_tsensorc : 1;  /* bit[2] :  */
        unsigned int  lpm3_pmc      : 1;  /* bit[3] :  */
        unsigned int  lpm3_uart     : 1;  /* bit[4] :  */
        unsigned int  lpm3_pmui2c   : 1;  /* bit[5] :  */
        unsigned int  lpm3_pmussi0  : 1;  /* bit[6] :  */
        unsigned int  crg_region1   : 1;  /* bit[7] :  */
        unsigned int  crg_region2   : 1;  /* bit[8] :  */
        unsigned int  crg_region3   : 1;  /* bit[9] :  */
        unsigned int  crg_region4   : 1;  /* bit[10]:  */
        unsigned int  crg_region5   : 1;  /* bit[11]:  */
        unsigned int  lpm3_wd       : 1;  /* bit[12]:  */
        unsigned int  lpm3_timer    : 1;  /* bit[13]:  */
        unsigned int  lpm3_config   : 1;  /* bit[14]:  */
        unsigned int  lpm3_nandc    : 1;  /* bit[15]:  */
        unsigned int  lpm3_gnspwm   : 1;  /* bit[16]:  */
        unsigned int  lpm3_ram      : 1;  /* bit[17]:  */
        unsigned int  reserved_0    : 1;  /* bit[18]:  */
        unsigned int  reserved_1    : 1;  /* bit[19]:  */
        unsigned int  reserved_2    : 1;  /* bit[20]:  */
        unsigned int  reserved_3    : 1;  /* bit[21]:  */
        unsigned int  reserved_4    : 1;  /* bit[22]:  */
        unsigned int  reserved_5    : 1;  /* bit[23]:  */
        unsigned int  reserved_6    : 1;  /* bit[24]:  */
        unsigned int  reserved_7    : 1;  /* bit[25]:  */
        unsigned int  reserved_8    : 1;  /* bit[26]:  */
        unsigned int  reserved_9    : 1;  /* bit[27]:  */
        unsigned int  reserved_10   : 1;  /* bit[28]:  */
        unsigned int  reserved_11   : 1;  /* bit[29]:  */
        unsigned int  reserved_12   : 1;  /* bit[30]:  */
        unsigned int  reserved_13   : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT5CLR_UNION;
#endif
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi1_START   (0)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi1_END     (0)
#define SOC_TZPC_DECPROT5CLR_ddrc_START           (1)
#define SOC_TZPC_DECPROT5CLR_ddrc_END             (1)
#define SOC_TZPC_DECPROT5CLR_lpm3_tsensorc_START  (2)
#define SOC_TZPC_DECPROT5CLR_lpm3_tsensorc_END    (2)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmc_START       (3)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmc_END         (3)
#define SOC_TZPC_DECPROT5CLR_lpm3_uart_START      (4)
#define SOC_TZPC_DECPROT5CLR_lpm3_uart_END        (4)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmui2c_START    (5)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmui2c_END      (5)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi0_START   (6)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi0_END     (6)
#define SOC_TZPC_DECPROT5CLR_crg_region1_START    (7)
#define SOC_TZPC_DECPROT5CLR_crg_region1_END      (7)
#define SOC_TZPC_DECPROT5CLR_crg_region2_START    (8)
#define SOC_TZPC_DECPROT5CLR_crg_region2_END      (8)
#define SOC_TZPC_DECPROT5CLR_crg_region3_START    (9)
#define SOC_TZPC_DECPROT5CLR_crg_region3_END      (9)
#define SOC_TZPC_DECPROT5CLR_crg_region4_START    (10)
#define SOC_TZPC_DECPROT5CLR_crg_region4_END      (10)
#define SOC_TZPC_DECPROT5CLR_crg_region5_START    (11)
#define SOC_TZPC_DECPROT5CLR_crg_region5_END      (11)
#define SOC_TZPC_DECPROT5CLR_lpm3_wd_START        (12)
#define SOC_TZPC_DECPROT5CLR_lpm3_wd_END          (12)
#define SOC_TZPC_DECPROT5CLR_lpm3_timer_START     (13)
#define SOC_TZPC_DECPROT5CLR_lpm3_timer_END       (13)
#define SOC_TZPC_DECPROT5CLR_lpm3_config_START    (14)
#define SOC_TZPC_DECPROT5CLR_lpm3_config_END      (14)
#define SOC_TZPC_DECPROT5CLR_lpm3_nandc_START     (15)
#define SOC_TZPC_DECPROT5CLR_lpm3_nandc_END       (15)
#define SOC_TZPC_DECPROT5CLR_lpm3_gnspwm_START    (16)
#define SOC_TZPC_DECPROT5CLR_lpm3_gnspwm_END      (16)
#define SOC_TZPC_DECPROT5CLR_lpm3_ram_START       (17)
#define SOC_TZPC_DECPROT5CLR_lpm3_ram_END         (17)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT6STAT_UNION
 结构说明  : DECPROT6STAT 寄存器结构定义。地址偏移量:0x848，初值:0x0007FE60，宽度:32
 寄存器说明: IP安全属性状态寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3             : 1;  /* bit[0] : lpm3 mst上电默认为安全属性。 */
        unsigned int  reserved_0       : 1;  /* bit[1] : 保留。 */
        unsigned int  reserved_1       : 1;  /* bit[2] : 保留。 */
        unsigned int  emmc0            : 1;  /* bit[3] : emmc0 mst上电默认为安全属性。 */
        unsigned int  emmc1            : 1;  /* bit[4] : emmc1 mst上电默认为安全属性。 */
        unsigned int  sd30             : 1;  /* bit[5] : sd30 mst上电默认为非安全属性。 */
        unsigned int  sdio0            : 1;  /* bit[6] : sdio0 mst上电默认为非安全属性。 */
        unsigned int  sdio1            : 1;  /* bit[7] : sdio1 mst上电默认为安全属性。 */
        unsigned int  usb3otg          : 1;  /* bit[8] : usb3otg mst上电默认为安全属性。 */
        unsigned int  g3d              : 1;  /* bit[9] : g3d mst上电默认为非安全属性。 */
        unsigned int  reserved_2       : 1;  /* bit[10]: 保留。 */
        unsigned int  vdec             : 1;  /* bit[11]: vdec mst上电默认为非安全属性。 */
        unsigned int  venc             : 1;  /* bit[12]: venc mst上电默认为非安全属性。 */
        unsigned int  reserved_3       : 1;  /* bit[13]: 保留。 */
        unsigned int  reserved_4       : 1;  /* bit[14]: 保留。 */
        unsigned int  isp_a7tocfg      : 1;  /* bit[15]: isp_a7tocfg mst上电默认为非安全属性。 */
        unsigned int  isp_a7_axi_mst   : 1;  /* bit[16]: isp_a7_axi_mst mst上电默认为非安全属性。 */
        unsigned int  isp_core_axi_mst : 1;  /* bit[17]: isp_core_axi_mst mst上电默认为非安全属性。 */
        unsigned int  perf_stat        : 1;  /* bit[18]: perf_stat mst上电默认为非安全属性。 */
        unsigned int  reserved_5       : 1;  /* bit[19]: 保留。 */
        unsigned int  reserved_6       : 1;  /* bit[20]: 保留。 */
        unsigned int  reserved_7       : 1;  /* bit[21]: 保留。 */
        unsigned int  reserved_8       : 1;  /* bit[22]: 保留。 */
        unsigned int  reserved_9       : 1;  /* bit[23]: 保留。 */
        unsigned int  reserved_10      : 1;  /* bit[24]: 保留。 */
        unsigned int  reserved_11      : 1;  /* bit[25]: 保留。 */
        unsigned int  reserved_12      : 1;  /* bit[26]: 保留。 */
        unsigned int  reserved_13      : 1;  /* bit[27]: 保留。 */
        unsigned int  reserved_14      : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_15      : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_16      : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_17      : 1;  /* bit[31]: 保留。 */
    } reg;
} SOC_TZPC_DECPROT6STAT_UNION;
#endif
#define SOC_TZPC_DECPROT6STAT_lpm3_START              (0)
#define SOC_TZPC_DECPROT6STAT_lpm3_END                (0)
#define SOC_TZPC_DECPROT6STAT_emmc0_START             (3)
#define SOC_TZPC_DECPROT6STAT_emmc0_END               (3)
#define SOC_TZPC_DECPROT6STAT_emmc1_START             (4)
#define SOC_TZPC_DECPROT6STAT_emmc1_END               (4)
#define SOC_TZPC_DECPROT6STAT_sd30_START              (5)
#define SOC_TZPC_DECPROT6STAT_sd30_END                (5)
#define SOC_TZPC_DECPROT6STAT_sdio0_START             (6)
#define SOC_TZPC_DECPROT6STAT_sdio0_END               (6)
#define SOC_TZPC_DECPROT6STAT_sdio1_START             (7)
#define SOC_TZPC_DECPROT6STAT_sdio1_END               (7)
#define SOC_TZPC_DECPROT6STAT_usb3otg_START           (8)
#define SOC_TZPC_DECPROT6STAT_usb3otg_END             (8)
#define SOC_TZPC_DECPROT6STAT_g3d_START               (9)
#define SOC_TZPC_DECPROT6STAT_g3d_END                 (9)
#define SOC_TZPC_DECPROT6STAT_vdec_START              (11)
#define SOC_TZPC_DECPROT6STAT_vdec_END                (11)
#define SOC_TZPC_DECPROT6STAT_venc_START              (12)
#define SOC_TZPC_DECPROT6STAT_venc_END                (12)
#define SOC_TZPC_DECPROT6STAT_isp_a7tocfg_START       (15)
#define SOC_TZPC_DECPROT6STAT_isp_a7tocfg_END         (15)
#define SOC_TZPC_DECPROT6STAT_isp_a7_axi_mst_START    (16)
#define SOC_TZPC_DECPROT6STAT_isp_a7_axi_mst_END      (16)
#define SOC_TZPC_DECPROT6STAT_isp_core_axi_mst_START  (17)
#define SOC_TZPC_DECPROT6STAT_isp_core_axi_mst_END    (17)
#define SOC_TZPC_DECPROT6STAT_perf_stat_START         (18)
#define SOC_TZPC_DECPROT6STAT_perf_stat_END           (18)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT6SET_UNION
 结构说明  : DECPROT6SET 寄存器结构定义。地址偏移量:0x84C，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性置位寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3             : 1;  /* bit[0] : IP安全属性置位：
                                                         0：IP安全属性不变；
                                                         1：IP安全属性置“1”。 */
        unsigned int  reserved_0       : 1;  /* bit[1] :  */
        unsigned int  reserved_1       : 1;  /* bit[2] :  */
        unsigned int  emmc0            : 1;  /* bit[3] :  */
        unsigned int  emmc1            : 1;  /* bit[4] :  */
        unsigned int  sd30             : 1;  /* bit[5] :  */
        unsigned int  sdio0            : 1;  /* bit[6] :  */
        unsigned int  sdio1            : 1;  /* bit[7] :  */
        unsigned int  usb3otg          : 1;  /* bit[8] :  */
        unsigned int  g3d              : 1;  /* bit[9] :  */
        unsigned int  reserved_2       : 1;  /* bit[10]:  */
        unsigned int  vdec             : 1;  /* bit[11]:  */
        unsigned int  venc             : 1;  /* bit[12]:  */
        unsigned int  reserved_3       : 1;  /* bit[13]:  */
        unsigned int  reserved_4       : 1;  /* bit[14]:  */
        unsigned int  isp_a7tocfg      : 1;  /* bit[15]:  */
        unsigned int  isp_a7_axi_mst   : 1;  /* bit[16]:  */
        unsigned int  isp_core_axi_mst : 1;  /* bit[17]:  */
        unsigned int  perf_stat        : 1;  /* bit[18]:  */
        unsigned int  reserved_5       : 1;  /* bit[19]:  */
        unsigned int  reserved_6       : 1;  /* bit[20]:  */
        unsigned int  reserved_7       : 1;  /* bit[21]:  */
        unsigned int  reserved_8       : 1;  /* bit[22]:  */
        unsigned int  reserved_9       : 1;  /* bit[23]:  */
        unsigned int  reserved_10      : 1;  /* bit[24]:  */
        unsigned int  reserved_11      : 1;  /* bit[25]:  */
        unsigned int  reserved_12      : 1;  /* bit[26]:  */
        unsigned int  reserved_13      : 1;  /* bit[27]:  */
        unsigned int  reserved_14      : 1;  /* bit[28]:  */
        unsigned int  reserved_15      : 1;  /* bit[29]:  */
        unsigned int  reserved_16      : 1;  /* bit[30]:  */
        unsigned int  reserved_17      : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT6SET_UNION;
#endif
#define SOC_TZPC_DECPROT6SET_lpm3_START              (0)
#define SOC_TZPC_DECPROT6SET_lpm3_END                (0)
#define SOC_TZPC_DECPROT6SET_emmc0_START             (3)
#define SOC_TZPC_DECPROT6SET_emmc0_END               (3)
#define SOC_TZPC_DECPROT6SET_emmc1_START             (4)
#define SOC_TZPC_DECPROT6SET_emmc1_END               (4)
#define SOC_TZPC_DECPROT6SET_sd30_START              (5)
#define SOC_TZPC_DECPROT6SET_sd30_END                (5)
#define SOC_TZPC_DECPROT6SET_sdio0_START             (6)
#define SOC_TZPC_DECPROT6SET_sdio0_END               (6)
#define SOC_TZPC_DECPROT6SET_sdio1_START             (7)
#define SOC_TZPC_DECPROT6SET_sdio1_END               (7)
#define SOC_TZPC_DECPROT6SET_usb3otg_START           (8)
#define SOC_TZPC_DECPROT6SET_usb3otg_END             (8)
#define SOC_TZPC_DECPROT6SET_g3d_START               (9)
#define SOC_TZPC_DECPROT6SET_g3d_END                 (9)
#define SOC_TZPC_DECPROT6SET_vdec_START              (11)
#define SOC_TZPC_DECPROT6SET_vdec_END                (11)
#define SOC_TZPC_DECPROT6SET_venc_START              (12)
#define SOC_TZPC_DECPROT6SET_venc_END                (12)
#define SOC_TZPC_DECPROT6SET_isp_a7tocfg_START       (15)
#define SOC_TZPC_DECPROT6SET_isp_a7tocfg_END         (15)
#define SOC_TZPC_DECPROT6SET_isp_a7_axi_mst_START    (16)
#define SOC_TZPC_DECPROT6SET_isp_a7_axi_mst_END      (16)
#define SOC_TZPC_DECPROT6SET_isp_core_axi_mst_START  (17)
#define SOC_TZPC_DECPROT6SET_isp_core_axi_mst_END    (17)
#define SOC_TZPC_DECPROT6SET_perf_stat_START         (18)
#define SOC_TZPC_DECPROT6SET_perf_stat_END           (18)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT6CLR_UNION
 结构说明  : DECPROT6CLR 寄存器结构定义。地址偏移量:0x850，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性清零寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3             : 1;  /* bit[0] : IP安全属性清零：
                                                         0：IP安全属性不变；
                                                         1：IP安全属性置“0”。 */
        unsigned int  reserved_0       : 1;  /* bit[1] :  */
        unsigned int  reserved_1       : 1;  /* bit[2] :  */
        unsigned int  emmc0            : 1;  /* bit[3] :  */
        unsigned int  emmc1            : 1;  /* bit[4] :  */
        unsigned int  sd30             : 1;  /* bit[5] :  */
        unsigned int  sdio0            : 1;  /* bit[6] :  */
        unsigned int  sdio1            : 1;  /* bit[7] :  */
        unsigned int  usb3otg          : 1;  /* bit[8] :  */
        unsigned int  g3d              : 1;  /* bit[9] :  */
        unsigned int  reserved_2       : 1;  /* bit[10]:  */
        unsigned int  vdec             : 1;  /* bit[11]:  */
        unsigned int  venc             : 1;  /* bit[12]:  */
        unsigned int  reserved_3       : 1;  /* bit[13]:  */
        unsigned int  reserved_4       : 1;  /* bit[14]:  */
        unsigned int  isp_a7tocfg      : 1;  /* bit[15]:  */
        unsigned int  isp_a7_axi_mst   : 1;  /* bit[16]:  */
        unsigned int  isp_core_axi_mst : 1;  /* bit[17]:  */
        unsigned int  perf_stat        : 1;  /* bit[18]:  */
        unsigned int  reserved_5       : 1;  /* bit[19]:  */
        unsigned int  reserved_6       : 1;  /* bit[20]:  */
        unsigned int  reserved_7       : 1;  /* bit[21]:  */
        unsigned int  reserved_8       : 1;  /* bit[22]:  */
        unsigned int  reserved_9       : 1;  /* bit[23]:  */
        unsigned int  reserved_10      : 1;  /* bit[24]:  */
        unsigned int  reserved_11      : 1;  /* bit[25]:  */
        unsigned int  reserved_12      : 1;  /* bit[26]:  */
        unsigned int  reserved_13      : 1;  /* bit[27]:  */
        unsigned int  reserved_14      : 1;  /* bit[28]:  */
        unsigned int  reserved_15      : 1;  /* bit[29]:  */
        unsigned int  reserved_16      : 1;  /* bit[30]:  */
        unsigned int  reserved_17      : 1;  /* bit[31]:  */
    } reg;
} SOC_TZPC_DECPROT6CLR_UNION;
#endif
#define SOC_TZPC_DECPROT6CLR_lpm3_START              (0)
#define SOC_TZPC_DECPROT6CLR_lpm3_END                (0)
#define SOC_TZPC_DECPROT6CLR_emmc0_START             (3)
#define SOC_TZPC_DECPROT6CLR_emmc0_END               (3)
#define SOC_TZPC_DECPROT6CLR_emmc1_START             (4)
#define SOC_TZPC_DECPROT6CLR_emmc1_END               (4)
#define SOC_TZPC_DECPROT6CLR_sd30_START              (5)
#define SOC_TZPC_DECPROT6CLR_sd30_END                (5)
#define SOC_TZPC_DECPROT6CLR_sdio0_START             (6)
#define SOC_TZPC_DECPROT6CLR_sdio0_END               (6)
#define SOC_TZPC_DECPROT6CLR_sdio1_START             (7)
#define SOC_TZPC_DECPROT6CLR_sdio1_END               (7)
#define SOC_TZPC_DECPROT6CLR_usb3otg_START           (8)
#define SOC_TZPC_DECPROT6CLR_usb3otg_END             (8)
#define SOC_TZPC_DECPROT6CLR_g3d_START               (9)
#define SOC_TZPC_DECPROT6CLR_g3d_END                 (9)
#define SOC_TZPC_DECPROT6CLR_vdec_START              (11)
#define SOC_TZPC_DECPROT6CLR_vdec_END                (11)
#define SOC_TZPC_DECPROT6CLR_venc_START              (12)
#define SOC_TZPC_DECPROT6CLR_venc_END                (12)
#define SOC_TZPC_DECPROT6CLR_isp_a7tocfg_START       (15)
#define SOC_TZPC_DECPROT6CLR_isp_a7tocfg_END         (15)
#define SOC_TZPC_DECPROT6CLR_isp_a7_axi_mst_START    (16)
#define SOC_TZPC_DECPROT6CLR_isp_a7_axi_mst_END      (16)
#define SOC_TZPC_DECPROT6CLR_isp_core_axi_mst_START  (17)
#define SOC_TZPC_DECPROT6CLR_isp_core_axi_mst_END    (17)
#define SOC_TZPC_DECPROT6CLR_perf_stat_START         (18)
#define SOC_TZPC_DECPROT6CLR_perf_stat_END           (18)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT7STAT_UNION
 结构说明  : DECPROT7STAT 寄存器结构定义。地址偏移量:0x854，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性状态寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_TZPC_DECPROT7STAT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT7SET_UNION
 结构说明  : DECPROT7SET 寄存器结构定义。地址偏移量:0x858，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性置位寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_TZPC_DECPROT7SET_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT7CLR_UNION
 结构说明  : DECPROT7CLR 寄存器结构定义。地址偏移量:0x85C，初值:0x00000000，宽度:32
 寄存器说明: IP安全属性清零寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_TZPC_DECPROT7CLR_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT8STAT_UNION
 结构说明  : DECPROT8STAT 寄存器结构定义。地址偏移量:0x860，初值:0x00000007，宽度:32
 寄存器说明: IP安全属性状态寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vivobus_firewall : 8;  /* bit[0-7] : bit0：firewall的使能控制，默认使能。
                                                           bit1：firewall发现越权是否上报error，默认上报。
                                                           bit2：isp_subsys slv的安全属性，默认是非安全属性。
                                                           bit3：VIVOBUS(0xE86C0000~0xE8DFFFFF) slv的安全属性，默认是安全属性。
                                                           bit[7:4]：保留。 */
        unsigned int  reserved_0       : 23; /* bit[8-30]: 保留。 */
        unsigned int  reserved_1       : 1;  /* bit[31]  : 保留。 */
    } reg;
} SOC_TZPC_DECPROT8STAT_UNION;
#endif
#define SOC_TZPC_DECPROT8STAT_vivobus_firewall_START  (0)
#define SOC_TZPC_DECPROT8STAT_vivobus_firewall_END    (7)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT8SET_UNION
 结构说明  : DECPROT8SET 寄存器结构定义。地址偏移量:0x864，初值:0x00000007，宽度:32
 寄存器说明: IP安全属性置位寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vivobus_firewall : 8;  /* bit[0-7] : IP安全属性置位：
                                                           0：IP安全属性不变；
                                                           1：IP安全属性置“1”。 */
        unsigned int  reserved_0       : 23; /* bit[8-30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]  :  */
    } reg;
} SOC_TZPC_DECPROT8SET_UNION;
#endif
#define SOC_TZPC_DECPROT8SET_vivobus_firewall_START  (0)
#define SOC_TZPC_DECPROT8SET_vivobus_firewall_END    (7)


/*****************************************************************************
 结构名    : SOC_TZPC_DECPROT8CLR_UNION
 结构说明  : DECPROT8CLR 寄存器结构定义。地址偏移量:0x868，初值:0x00000007，宽度:32
 寄存器说明: IP安全属性清零寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vivobus_firewall : 8;  /* bit[0-7] : IP安全属性清零：
                                                           0：IP安全属性不变；
                                                           1：IP安全属性置“0”。 */
        unsigned int  reserved_0       : 23; /* bit[8-30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]  :  */
    } reg;
} SOC_TZPC_DECPROT8CLR_UNION;
#endif
#define SOC_TZPC_DECPROT8CLR_vivobus_firewall_START  (0)
#define SOC_TZPC_DECPROT8CLR_vivobus_firewall_END    (7)


/*****************************************************************************
 结构名    : SOC_TZPC_REG0_STAT_UNION
 结构说明  : REG0_STAT 寄存器结构定义。地址偏移量:0x86C，初值:0x00000000，宽度:32
 寄存器说明: 控制reg0寄存器的信息。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_TZPC_REG0_STAT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_TZPC_REG1_STAT_UNION
 结构说明  : REG1_STAT 寄存器结构定义。地址偏移量:0x870，初值:0x00000000，宽度:32
 寄存器说明: 控制reg1寄存器的信息。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_TZPC_REG1_STAT_UNION;
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

#endif /* end of soc_tzpc_interface.h */
