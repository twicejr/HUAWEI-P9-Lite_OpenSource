

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_OTG_USB_AHBIF_INTERFACE_H__
#define __SOC_OTG_USB_AHBIF_INTERFACE_H__

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
/* 寄存器说明：选择控制寄存器0
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_ADDR(base)    ((base) + (0x00))

/* 寄存器说明：选择控制寄存器1
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_ADDR(base)    ((base) + (0x04))

/* 寄存器说明：选择控制寄存器2
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_ADDR(base)    ((base) + (0x08))

/* 寄存器说明：参数配置寄存器
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_ADDR(base)    ((base) + (0x0C))

/* 寄存器说明：选择控制寄存器4
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_ADDR(base)    ((base) + (0x10))

/* 寄存器说明：参考时钟控制寄存器
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_ADDR(base)    ((base) + (0x14))

/* 寄存器说明：BC控制器寄存器0
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_CTRL0_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL0_ADDR(base)         ((base) + (0x18))

/* 寄存器说明：BC控制器寄存器1
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_CTRL1_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL1_ADDR(base)         ((base) + (0x1C))

/* 寄存器说明：BC控制器寄存器2
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_CTRL2_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL2_ADDR(base)         ((base) + (0x20))

/* 寄存器说明：BC控制器寄存器3
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_CTRL3_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL3_ADDR(base)         ((base) + (0x24))

/* 寄存器说明：BC控制器寄存器4
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_CTRL4_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL4_ADDR(base)         ((base) + (0x28))

/* 寄存器说明：BC控制器寄存器5
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_CTRL5_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL5_ADDR(base)         ((base) + (0x2C))

/* 寄存器说明：BC控制器寄存器6
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_CTRL6_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL6_ADDR(base)         ((base) + (0x30))

/* 寄存器说明：BC控制器寄存器7
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_CTRL7_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL7_ADDR(base)         ((base) + (0x34))

/* 寄存器说明：BC控制器寄存器8
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_CTRL8_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL8_ADDR(base)         ((base) + (0x38))

/* 寄存器说明：BC状态寄存器0
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_STS0_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS0_ADDR(base)          ((base) + (0x3C))

/* 寄存器说明：BC状态寄存器1
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_STS1_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS1_ADDR(base)          ((base) + (0x40))

/* 寄存器说明：BC状态寄存器2
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_STS2_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS2_ADDR(base)          ((base) + (0x44))

/* 寄存器说明：BC状态寄存器3
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_STS3_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS3_ADDR(base)          ((base) + (0x48))

/* 寄存器说明：BC状态寄存器4
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_BC_STS4_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS4_ADDR(base)          ((base) + (0x4C))

/* 寄存器说明：测试接口控制寄存器
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_ADDR(base)    ((base) + (0x50))

/* 寄存器说明：USB状态寄存器
   位域定义UNION结构:  SOC_OTG_USB_AHBIF_USBOTG2_STS_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_ADDR(base)      ((base) + (0x54))





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
 结构名    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_UNION
 结构说明  : USBOTG2_CTRL0 寄存器结构定义。地址偏移量:0x00，初值:0x00000040，宽度:32
 寄存器说明: 选择控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  idpullup_sel      : 1;  /* bit[0]    : ID上拉电阻使能选择：
                                                             0：控制器；
                                                             1：寄存器 */
        unsigned int  idpullup          : 1;  /* bit[1]    : ID上拉电阻使能 */
        unsigned int  acaenb_sel        : 1;  /* bit[2]    : ACA接口使能选择来源：
                                                             0：控制器
                                                             1：寄存器 */
        unsigned int  acaenb            : 1;  /* bit[3]    : ACA接口使能 */
        unsigned int  id_sel            : 2;  /* bit[4-5]  : ACA接口来源选择：
                                                             00：来自寄存器；
                                                             01：来自PHY的iddig；
                                                             10：来自PHY的ACA接口；
                                                             其他：保留 */
        unsigned int  id                : 1;  /* bit[6]    : 工作模式识别 */
        unsigned int  drvvbus_sel       : 1;  /* bit[7]    : 开启vbus电压选择：
                                                             0：来自控制器；
                                                             1：来自寄存器 */
        unsigned int  drvvbus           : 1;  /* bit[8]    : 使能vbus施加电压 */
        unsigned int  vbusvalid_sel     : 1;  /* bit[9]    : 控制器的vbusvalid信号来源选择：
                                                             0：选择PHY输出的vbusvalid;
                                                             1：选择内部的drvvbus信号 */
        unsigned int  sessvld_sel       : 1;  /* bit[10]   : 控制器的sessvld信号来源选择：
                                                             0：选择PHY输出的sessvld;
                                                             1：选择寄存器的sessvld */
        unsigned int  sessvld           : 1;  /* bit[11]   : session有效指示 */
        unsigned int  dpdmpulldown_sel  : 1;  /* bit[12]   : PHY的DP/DM下拉电阻使能选择：
                                                             0：选择控制器的dp/mpulldown；
                                                             1：选择寄存器的dp/mpulldown */
        unsigned int  dppulldown        : 1;  /* bit[13]   : 使能DP信号的下拉电阻 */
        unsigned int  dmpulldown        : 1;  /* bit[14]   : 使能DM信号的下拉电阻 */
        unsigned int  dbnce_fltr_bypass : 1;  /* bit[15]   : 去除vbusvalid,avalid,bvalid,sessend和iddig信号的滤波器 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_idpullup_sel_START       (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_idpullup_sel_END         (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_idpullup_START           (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_idpullup_END             (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_acaenb_sel_START         (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_acaenb_sel_END           (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_acaenb_START             (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_acaenb_END               (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_id_sel_START             (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_id_sel_END               (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_id_START                 (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_id_END                   (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_drvvbus_sel_START        (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_drvvbus_sel_END          (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_drvvbus_START            (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_drvvbus_END              (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_vbusvalid_sel_START      (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_vbusvalid_sel_END        (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_sessvld_sel_START        (10)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_sessvld_sel_END          (10)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_sessvld_START            (11)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_sessvld_END              (11)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dpdmpulldown_sel_START   (12)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dpdmpulldown_sel_END     (12)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dppulldown_START         (13)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dppulldown_END           (13)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dmpulldown_START         (14)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dmpulldown_END           (14)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dbnce_fltr_bypass_START  (15)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dbnce_fltr_bypass_END    (15)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_UNION
 结构说明  : USBOTG2_CTRL1 寄存器结构定义。地址偏移量:0x04，初值:0x00000000，宽度:32
 寄存器说明: 选择控制寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scaledown_mode : 2;  /* bit[0-1] : 控制器仿真模式：
                                                         00：正常模式；
                                                         01：仿真加快，除了device模式的suspend和resume，还包含速度枚举过程，HNP/SRP,host模式suspend和resume过程
                                                         10：只加快device模式的suspend和resume过程
                                                         11：所有过程加快 */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_scaledown_mode_START  (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_scaledown_mode_END    (1)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_UNION
 结构说明  : USBOTG2_CTRL2 寄存器结构定义。地址偏移量:0x08，初值:0x000000B1，宽度:32
 寄存器说明: 选择控制寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  commononn     : 1;  /* bit[0]    : PHY的COMMON电路电源开关 */
        unsigned int  otgdisable    : 1;  /* bit[1]    : 关闭PHY的OTG特性 */
        unsigned int  vbusvldsel    : 1;  /* bit[2]    : VBUS有效选择：
                                                         0：来自PHY内部比较器
                                                         1：来自寄存器 */
        unsigned int  vbusvldext    : 1;  /* bit[3]    : VBUS有效 */
        unsigned int  txbitstuffen  : 1;  /* bit[4]    : Function: This controller signal controls bit stuffing on DATAIN<#>[7:0] when 
                                                         OPMODE<#>[1:0] = 2’b11.
                                                         1: Bit stuffing is enabled.
                                                         0: Bit stuffing is disabled. */
        unsigned int  txbitstuffenh : 1;  /* bit[5]    : Function: This controller signal controls bit stuffing on DATAIN<#>[15:8] when 
                                                         OPMODE<#>[1:0] = 2’b11.
                                                         1: Bit stuffing is enabled.
                                                         0: Bit stuffing is disabled. */
        unsigned int  fsxcvrowner   : 1;  /* bit[6]    : Function: This controller signal enables the UTMI+ or serial interface.
                                                         1: The TXENABLEN<#>, FSDATAEXT<#>, and FSSE0EXT<#> inputs drive 
                                                         USB 2.0 picoPHY data output onto the D+ and D– lines. Data that the USB 2.0 
                                                         picoPHY receives from the D+ and D– lines appears on the FSVMINUS<#> and 
                                                         FSVPLUS<#> outputs.
                                                         0: Data on the D+ and D– lines is transmitted and received through the UTMI+.
                                                         If FSXCVROWNER<#> is not used, set it to 1'b0. */
        unsigned int  txenablen     : 1;  /* bit[7]    : Function: This controller signal enables the FSDATAEXT<#> and FSSE0EXT<#> 
                                                         inputs. TXENABLEN<#> is valid only when the FSXCVROWNER<#> signal is set to 1’b1.
                                                         1: FSDATAEXT<#> and FSSE0EXT<#> are disabled.
                                                         0: FSDATAEXT<#> and FSSE0EXT<#> are enabled.
                                                         If TXENABLEN<#> is not used, set it to 1'b1. */
        unsigned int  fsdataext     : 1;  /* bit[8]    : 串行接口数据输出 */
        unsigned int  fsse0ext      : 1;  /* bit[9]    : 串行接口输出SE0 */
        unsigned int  vatestenb     : 2;  /* bit[10-11]: Function: Enables analog test voltages to be placed on either the ANALOGTEST or ID0 pin.
                                                         11: Reserved. Invalid setting.
                                                         10: Analog test voltages can be viewed or applied on ANALOGTEST.
                                                         01: Analog test voltages can be viewed or applied on ID0.
                                                         00: Analog test voltages cannot be viewed or applied on either ANALOGTEST or ID0. */
        unsigned int  reserved      : 20; /* bit[12-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_commononn_START      (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_commononn_END        (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_otgdisable_START     (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_otgdisable_END       (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vbusvldsel_START     (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vbusvldsel_END       (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vbusvldext_START     (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vbusvldext_END       (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txbitstuffen_START   (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txbitstuffen_END     (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txbitstuffenh_START  (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txbitstuffenh_END    (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsxcvrowner_START    (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsxcvrowner_END      (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txenablen_START      (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txenablen_END        (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsdataext_START      (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsdataext_END        (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsse0ext_START       (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsse0ext_END         (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vatestenb_START      (10)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vatestenb_END        (11)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_UNION
 结构说明  : USBOTG2_CTRL3 寄存器结构定义。地址偏移量:0x0C，初值:0x05CD06DB，宽度:32
 寄存器说明: 参数配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  comdistune        : 3;  /* bit[0-2]  : Function: This bus adjusts the voltage level for the threshold used to detect a disconnect event at the host.
                                                             111: + 12%
                                                             110: + 10%
                                                             101: + 7%
                                                             100: + 3%
                                                             011: Design default
                                                             010: – 4%
                                                             001: – 6%
                                                             000: – 9% */
        unsigned int  otgtune           : 3;  /* bit[3-5]  : Function: This bus adjusts the voltage level for the VBUS Valid threshold.
                                                             111: + 12%
                                                             110: + 9%
                                                             101: + 6%
                                                             100: + 3%
                                                             011: Design default
                                                             010: – 3%
                                                             001: – 6%
                                                             000: – 9% */
        unsigned int  sqrxtune          : 3;  /* bit[6-8]  : Function: This bus adjusts the voltage level for the threshold used to detect valid high-speed data.
                                                             111: – 20%
                                                             110: – 15%
                                                             101: – 10%
                                                             100: – 5%
                                                             011: Design default
                                                             010: + 5%
                                                             001: + 10%
                                                             000: + 15% */
        unsigned int  txfslstune        : 4;  /* bit[9-12] : Function: This bus adjusts the low- and full-speed single-ended source impedance while driving high. The following adjustment values are based on nominal process, voltage, and temperature.
                                                             1111: – 10.7%
                                                             0111: – 5.6%
                                                             0011: Design default
                                                             0001: + 6.5%
                                                             0000: + 14%
                                                             All other bit settings are reserved. */
        unsigned int  txpreempamptune   : 2;  /* bit[13-14]: Function: This signal controls the amount of current sourced to DP<#> and DM<#> after a J-to-K or K-to-J transition. The HS Transmitter pre-emphasis current is defined in terms of unit amounts. One unit amount is 
                                                             approximately 600 μA and is defined as 1X pre-emphasis current.
                                                             11: HS Transmitter pre-emphasis circuit sources 3X pre-emphasis 
                                                             current.
                                                             10: HS Transmitter pre-emphasis circuit sources 2X pre-emphasis 
                                                             current.
                                                             01: HS Transmitter pre-emphasis circuit sources 1X pre-emphasis 
                                                             current.
                                                             00 (design default): HS Transmitter pre-emphasis is disabled. */
        unsigned int  txpreemppulsetune : 1;  /* bit[15]   : 使能欲加重。控制驱动DP或DM上的预加重电流的时间。预加重以580ps为一个单位，定义为1X预加重。该值仅当txpreempamptune[1]或者txpreempamptune[0]为1时有效。
                                                             1:1X，短的预加重时间
                                                             0:2X，长的预加重时间。缺省值 */
        unsigned int  txrisetune        : 2;  /* bit[16-17]: 调整眼图斜率。
                                                             11：-8.1%
                                                             10：-7.2%
                                                             01：缺省值
                                                             00：+5.4% */
        unsigned int  txvreftune        : 4;  /* bit[18-21]: 调整眼图上下电压。
                                                             1111: + 24%
                                                             1110: + 22%
                                                             1101: + 20%
                                                             1100: + 18%
                                                             1011: + 16%
                                                             1010: + 14%
                                                             1001: + 12%
                                                             1000: + 10%
                                                             0111: + 8%
                                                             0110: + 6%
                                                             0101: + 4%
                                                             0100: + 2%
                                                             0011: Design default
                                                             0010: – 2%
                                                             0001: – 4%
                                                             0000: – 6% */
        unsigned int  txhsxvtune        : 2;  /* bit[22-23]: 调整眼图0交叉点的位置。
                                                             11: 缺省值
                                                             10: + 15 mV
                                                             01: –15 mV
                                                             00: 保留 */
        unsigned int  txrestune         : 2;  /* bit[24-25]: 调整阻抗匹配。在有些应用中，在PHY和线缆之间可能有很大的串行电阻。该参数就是用来抵消掉附加电阻的影响。
                                                             11: 源阻抗减少 5.6 Ω
                                                             10: 源阻抗减少 3.6 Ω
                                                             01: 缺省值
                                                             00: 源阻抗增加1.3 Ω */
        unsigned int  vdatreftune       : 2;  /* bit[26-27]: 数据管脚检测电压调整。该参数调整Vdat_ref的值。
                                                             11: – 20%
                                                             10: – 10%
                                                             01: 缺省值
                                                             00: +10% */
        unsigned int  reserved          : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_comdistune_START         (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_comdistune_END           (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_otgtune_START            (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_otgtune_END              (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_sqrxtune_START           (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_sqrxtune_END             (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txfslstune_START         (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txfslstune_END           (12)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txpreempamptune_START    (13)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txpreempamptune_END      (14)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txpreemppulsetune_START  (15)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txpreemppulsetune_END    (15)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txrisetune_START         (16)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txrisetune_END           (17)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txvreftune_START         (18)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txvreftune_END           (21)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txhsxvtune_START         (22)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txhsxvtune_END           (23)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txrestune_START          (24)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txrestune_END            (25)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_vdatreftune_START        (26)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_vdatreftune_END          (27)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_UNION
 结构说明  : USBOTG2_CTRL4 寄存器结构定义。地址偏移量:0x10，初值:0x00000202，宽度:32
 寄存器说明: 选择控制寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  siddq         : 1;  /* bit[0]    : IDDQ模式 */
        unsigned int  vregbypass    : 1;  /* bit[1]    : Vreg18选择控制。Scan模式下不能改变其值。
                                                         1：VDDH需要外供1.8V电压
                                                         0：VDDH要外供3.3V电压 */
        unsigned int  loopbackenb   : 1;  /* bit[2]    : 环回测试使能控制。仅在测试模式下使用。 */
        unsigned int  bypasssel     : 1;  /* bit[3]    : 控制收发器的bypass模式。 */
        unsigned int  bypassdmen    : 1;  /* bit[4]    : DM bypass使能 */
        unsigned int  bypassdpen    : 1;  /* bit[5]    : DP bypass使能 */
        unsigned int  bypassdmdata  : 1;  /* bit[6]    : DM bypass数据 */
        unsigned int  bypassdpdata  : 1;  /* bit[7]    : DP bypass数据 */
        unsigned int  hsxcvrrextctl : 1;  /* bit[8]    : HS收发器异步控制。仅在高速模式下起作用。 */
        unsigned int  retenablen    : 1;  /* bit[9]    : retion使能，缺省为1 */
        unsigned int  autorsmenb    : 1;  /* bit[10]   : 自动唤醒。 */
        unsigned int  reserved      : 21; /* bit[11-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_siddq_START          (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_siddq_END            (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_vregbypass_START     (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_vregbypass_END       (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_loopbackenb_START    (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_loopbackenb_END      (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypasssel_START      (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypasssel_END        (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdmen_START     (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdmen_END       (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdpen_START     (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdpen_END       (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdmdata_START   (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdmdata_END     (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdpdata_START   (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdpdata_END     (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_hsxcvrrextctl_START  (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_hsxcvrrextctl_END    (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_retenablen_START     (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_retenablen_END       (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_autorsmenb_START     (10)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_autorsmenb_END       (10)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_UNION
 结构说明  : USBOTG2_CTRL5 寄存器结构定义。地址偏移量:0x14，初值:0x00003106，宽度:32
 寄存器说明: 参考时钟控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  refclksel : 2;  /* bit[0-1]  : This signal selects the reference clock source for the PLL block.
                                                     11: Reserved
                                                     10: The PLL uses CLKCORE as reference.
                                                     01: The XO block uses an external, 1.8-V clock supplied on the XO pin.
                                                     00: The XO block uses the clock from a crystal */
        unsigned int  fsel      : 3;  /* bit[2-4]  : Function: Selects the USB 2.0 picoPHY reference clock requency. 
                                                     It's value depends on the pllbtune's value.The detail usage refers to the databook description */
        unsigned int  pllbtune  : 1;  /* bit[5]    : PLL Bandwidth adjustment
                                                     This adjustment doubles the bandwidth of the PLL as needed
                                                     for some input reference clock frequencies.
                                                     1: 2x bandwidth 
                                                     0: Design default */
        unsigned int  pllitune  : 2;  /* bit[6-7]  : PLL Integral Path Tune.Reserved */
        unsigned int  pllptune  : 4;  /* bit[8-11] : PLL Proportional Path Tune.Reserved */
        unsigned int  reserved  : 20; /* bit[12-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_refclksel_START  (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_refclksel_END    (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_fsel_START       (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_fsel_END         (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllbtune_START   (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllbtune_END     (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllitune_START   (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllitune_END     (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllptune_START   (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllptune_END     (11)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_CTRL0_UNION
 结构说明  : BC_CTRL0 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: BC控制器寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_en : 1;  /* bit[0]   : 原始充电使能 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL0_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL0_chrg_det_en_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL0_chrg_det_en_END    (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_CTRL1_UNION
 结构说明  : BC_CTRL1 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: BC控制器寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_int_clr : 1;  /* bit[0]   : 原始充电中断清除 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL1_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL1_chrg_det_int_clr_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL1_chrg_det_int_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_CTRL2_UNION
 结构说明  : BC_CTRL2 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: BC控制器寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_int_msk : 1;  /* bit[0]   : 原始充电中断屏蔽 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL2_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL2_chrg_det_int_msk_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL2_chrg_det_int_msk_END    (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_CTRL3_UNION
 结构说明  : BC_CTRL3 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: BC控制器寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_mode  : 1;  /* bit[0]   : BC模式使能 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL3_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL3_bc_mode_START   (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL3_bc_mode_END     (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_CTRL4_UNION
 结构说明  : BC_CTRL4 寄存器结构定义。地址偏移量:0x28，初值:0x00000C01，宽度:32
 寄存器说明: BC控制器寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_opmode     : 2;  /* bit[0-1]  : This controller bus selects the UTMI+ operational mode.
                                                         11: Normal operation without SYNC or EOP generation. If the 
                                                         XCVRSEL<#>[1:0] bus is not set to 2’b00 while OPMODE<#>[1:0] is set to 2’b11, USB 2.0 picoPHY behavior is undefined.
                                                         10: Disable bit stuffing and NRZI encoding
                                                         01: Non-Driving
                                                         00: Normal */
        unsigned int  bc_xcvrselect : 2;  /* bit[2-3]  : 收发器选择 */
        unsigned int  bc_termselect : 1;  /* bit[4]    : 终端选择 */
        unsigned int  bc_txvalid    : 1;  /* bit[5]    : UTMI+低8bit数据发送使能 */
        unsigned int  bc_txvalidh   : 1;  /* bit[6]    : UTMI+高8bit数据发送使能 */
        unsigned int  bc_idpullup   : 1;  /* bit[7]    : ID上拉电阻使能 */
        unsigned int  bc_dppulldown : 1;  /* bit[8]    : DP下拉电阻使能 */
        unsigned int  bc_dmpulldown : 1;  /* bit[9]    : DM下拉电阻使能 */
        unsigned int  bc_suspendm   : 1;  /* bit[10]   : suspend模式 */
        unsigned int  bc_sleepm     : 1;  /* bit[11]   : sleep模式 */
        unsigned int  reserved      : 20; /* bit[12-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL4_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_opmode_START      (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_opmode_END        (1)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_xcvrselect_START  (2)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_xcvrselect_END    (3)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_termselect_START  (4)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_termselect_END    (4)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_txvalid_START     (5)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_txvalid_END       (5)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_txvalidh_START    (6)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_txvalidh_END      (6)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_idpullup_START    (7)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_idpullup_END      (7)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_dppulldown_START  (8)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_dppulldown_END    (8)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_dmpulldown_START  (9)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_dmpulldown_END    (9)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_suspendm_START    (10)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_suspendm_END      (10)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_sleepm_START      (11)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_sleepm_END        (11)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_CTRL5_UNION
 结构说明  : BC_CTRL5 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: BC控制器寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_aca_en      : 1;  /* bit[0]   : ACA接口使能 */
        unsigned int  bc_chrg_sel    : 1;  /* bit[1]   : 选择施加电平数据线 */
        unsigned int  bc_vdat_src_en : 1;  /* bit[2]   : 数据端口施加电平使能 */
        unsigned int  bc_vdat_det_en : 1;  /* bit[3]   : 数据端口电平检测使能 */
        unsigned int  bc_dcd_en      : 1;  /* bit[4]   : DCD检测使能 */
        unsigned int  reserved       : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL5_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_aca_en_START       (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_aca_en_END         (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_chrg_sel_START     (1)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_chrg_sel_END       (1)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_vdat_src_en_START  (2)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_vdat_src_en_END    (2)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_vdat_det_en_START  (3)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_vdat_det_en_END    (3)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_dcd_en_START       (4)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_dcd_en_END         (4)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_CTRL6_UNION
 结构说明  : BC_CTRL6 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: BC控制器寄存器6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_chirp_int_clr : 1;  /* bit[0]   : 充电接口中断清除 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL6_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL6_bc_chirp_int_clr_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL6_bc_chirp_int_clr_END    (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_CTRL7_UNION
 结构说明  : BC_CTRL7 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: BC控制器寄存器7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_chirp_int_msk : 1;  /* bit[0]   : 充电接口中断屏蔽 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL7_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL7_bc_chirp_int_msk_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL7_bc_chirp_int_msk_END    (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_CTRL8_UNION
 结构说明  : BC_CTRL8 寄存器结构定义。地址偏移量:0x38，初值:0xFFFFFFFF，宽度:32
 寄存器说明: BC控制器寄存器8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_len : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL8_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL8_filter_len_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL8_filter_len_END    (31)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_STS0_UNION
 结构说明  : BC_STS0 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: BC状态寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_rawint : 1;  /* bit[0]   : 原始充电检测中断(DP/DM同时高时间为filter_len) */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS0_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS0_chrg_det_rawint_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS0_chrg_det_rawint_END    (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_STS1_UNION
 结构说明  : BC_STS1 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: BC状态寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_mskint : 1;  /* bit[0]   : 经过屏蔽后中断 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS1_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS1_chrg_det_mskint_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS1_chrg_det_mskint_END    (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_STS2_UNION
 结构说明  : BC_STS2 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: BC状态寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_vbus_valid : 1;  /* bit[0]    : vbus 有效 */
        unsigned int  bc_sess_valid : 1;  /* bit[1]    : session 有效 */
        unsigned int  bc_fs_vplus   : 1;  /* bit[2]    : DP状态 */
        unsigned int  bc_fs_vminus  : 1;  /* bit[3]    : DM状态 */
        unsigned int  bc_chg_det    : 1;  /* bit[4]    : 充电口检测 */
        unsigned int  bc_iddig      : 1;  /* bit[5]    : ID电平 */
        unsigned int  bc_rid_float  : 1;  /* bit[6]    : ACA接口状态 */
        unsigned int  bc_rid_gnd    : 1;  /* bit[7]    : ACA接口状态 */
        unsigned int  bc_rid_a      : 1;  /* bit[8]    : ACA接口状态 */
        unsigned int  bc_rid_b      : 1;  /* bit[9]    : ACA接口状态 */
        unsigned int  bc_rid_c      : 1;  /* bit[10]   : ACA接口状态 */
        unsigned int  bc_chirp_on   : 1;  /* bit[11]   : chirp状态 */
        unsigned int  bc_linestate  : 2;  /* bit[12-13]: 数据线缆状态 */
        unsigned int  reserved      : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS2_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_vbus_valid_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_vbus_valid_END    (0)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_sess_valid_START  (1)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_sess_valid_END    (1)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_fs_vplus_START    (2)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_fs_vplus_END      (2)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_fs_vminus_START   (3)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_fs_vminus_END     (3)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_chg_det_START     (4)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_chg_det_END       (4)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_iddig_START       (5)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_iddig_END         (5)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_float_START   (6)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_float_END     (6)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_gnd_START     (7)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_gnd_END       (7)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_a_START       (8)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_a_END         (8)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_b_START       (9)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_b_END         (9)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_c_START       (10)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_c_END         (10)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_chirp_on_START    (11)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_chirp_on_END      (11)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_linestate_START   (12)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_linestate_END     (13)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_STS3_UNION
 结构说明  : BC_STS3 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: BC状态寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_rawint : 1;  /* bit[0]   : 控制器chirp_on有效产生中断 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS3_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS3_bc_rawint_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS3_bc_rawint_END    (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_BC_STS4_UNION
 结构说明  : BC_STS4 寄存器结构定义。地址偏移量:0x4C，初值:0x00000000，宽度:32
 寄存器说明: BC状态寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_mskint : 1;  /* bit[0]   : bc_rawint经过屏蔽后中断 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS4_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS4_bc_mskint_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS4_bc_mskint_END    (0)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_UNION
 结构说明  : USBOTG2_CTRL6 寄存器结构定义。地址偏移量:0x50，初值:0x00000000，宽度:32
 寄存器说明: 测试接口控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  testclk        : 1;  /* bit[0]    : 测试时钟。不需要一个连续的时钟，仅上升沿有效 */
        unsigned int  testdataoutsel : 1;  /* bit[1]    : 输出总线数据选择。
                                                          1：模式定义的测试寄存器输出
                                                          0：模式定义的内部产生信号的输出 */
        unsigned int  test_sel       : 1;  /* bit[2]    : 测试接口选择。
                                                          1：选择由SOC test管脚驱动
                                                          0：由内部寄存器控制 */
        unsigned int  reserved_0     : 1;  /* bit[3]    : 保留 */
        unsigned int  testaddr       : 4;  /* bit[4-7]  : 测试寄存器地址 */
        unsigned int  testdatain     : 8;  /* bit[8-15] : 测试总线写数据 */
        unsigned int  test_mux       : 4;  /* bit[16-19]: 测试管脚选择。 */
        unsigned int  reserved_1     : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testclk_START         (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testclk_END           (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testdataoutsel_START  (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testdataoutsel_END    (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_test_sel_START        (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_test_sel_END          (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testaddr_START        (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testaddr_END          (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testdatain_START      (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testdatain_END        (15)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_test_mux_START        (16)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_test_mux_END          (19)


/*****************************************************************************
 结构名    : SOC_OTG_USB_AHBIF_USBOTG2_STS_UNION
 结构说明  : USBOTG2_STS 寄存器结构定义。地址偏移量:0x54，初值:0x00000000，宽度:32
 寄存器说明: USB状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  testdataout : 4;  /* bit[0-3] : 测试总线读数据 */
        unsigned int  hssqyelch   : 1;  /* bit[4]   : HS squelch检测器输出 */
        unsigned int  hsrxdat     : 1;  /* bit[5]   : HS异步数据 */
        unsigned int  fslsrcv     : 1;  /* bit[6]   : 差分数值指示。
                                                      1：D+上的电压值大于D-
                                                      0：D-上的电压值大于D+ */
        unsigned int  reserved    : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_STS_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_testdataout_START  (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_testdataout_END    (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_hssqyelch_START    (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_hssqyelch_END      (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_hsrxdat_START      (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_hsrxdat_END        (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_fslsrcv_START      (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_fslsrcv_END        (6)






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

#endif /* end of soc_otg_usb_ahbif_interface.h */
