

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_USB3OTG_BC_INTERFACE_H__
#define __SOC_USB3OTG_BC_INTERFACE_H__

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
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_CTRL0_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_ADDR(base)       ((base) + (0x00))

/* 寄存器说明：USB控制器参数配置寄存器
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_CTRL1_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_ADDR(base)       ((base) + (0x04))

/* 寄存器说明：PHY低功耗控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_CTRL2_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_ADDR(base)       ((base) + (0x08))

/* 寄存器说明：选择控制寄存器3
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_CTRL3_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_ADDR(base)       ((base) + (0x0C))

/* 寄存器说明：legacy USB参数调整寄存器
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_CTRL4_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_ADDR(base)       ((base) + (0x10))

/* 寄存器说明：SS参数调整寄存器1
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_CTRL5_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_ADDR(base)       ((base) + (0x14))

/* 寄存器说明：SS参数调整寄存器2
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_CTRL6_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_ADDR(base)       ((base) + (0x18))

/* 寄存器说明：选择控制寄存器7
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_CTRL7_UNION */
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ADDR(base)       ((base) + (0x1C))

/* 寄存器说明：状态寄存器0
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_STS0_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS0_ADDR(base)        ((base) + (0x20))

/* 寄存器说明：状态寄存器1
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_STS1_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS1_ADDR(base)        ((base) + (0x24))

/* 寄存器说明：状态寄存器2
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_STS2_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS2_ADDR(base)        ((base) + (0x28))

/* 寄存器说明：状态寄存器3
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_STS3_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS3_ADDR(base)        ((base) + (0x2C))

/* 寄存器说明：BC控制器寄存器0
   位域定义UNION结构:  SOC_USB3OTG_BC_BC_CTRL0_UNION */
#define SOC_USB3OTG_BC_BC_CTRL0_ADDR(base)            ((base) + (0x30))

/* 寄存器说明：BC控制器寄存器1
   位域定义UNION结构:  SOC_USB3OTG_BC_BC_CTRL1_UNION */
#define SOC_USB3OTG_BC_BC_CTRL1_ADDR(base)            ((base) + (0x34))

/* 寄存器说明：BC控制器寄存器2
   位域定义UNION结构:  SOC_USB3OTG_BC_BC_CTRL2_UNION */
#define SOC_USB3OTG_BC_BC_CTRL2_ADDR(base)            ((base) + (0x38))

/* 寄存器说明：BC状态寄存器0
   位域定义UNION结构:  SOC_USB3OTG_BC_BC_STS0_UNION */
#define SOC_USB3OTG_BC_BC_STS0_ADDR(base)             ((base) + (0x3C))

/* 寄存器说明：RAM控制寄存器
   位域定义UNION结构:  SOC_USB3OTG_BC_RAM_CTRL_UNION */
#define SOC_USB3OTG_BC_RAM_CTRL_ADDR(base)            ((base) + (0x40))

/* 寄存器说明：状态寄存器4
   位域定义UNION结构:  SOC_USB3OTG_BC_USBOTG3_STS4_UNION */
#define SOC_USB3OTG_BC_USBOTG3_STS4_ADDR(base)        ((base) + (0x44))





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
 结构名    : SOC_USB3OTG_BC_USBOTG3_CTRL0_UNION
 结构说明  : USBOTG3_CTRL0 寄存器结构定义。地址偏移量:0x00，初值:0x00000008，宽度:32
 寄存器说明: 选择控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  idpullup_sel  : 1;  /* bit[0]   : ID上拉电阻使能选择：
                                                        0：控制器；
                                                        1：寄存器 */
        unsigned int  idpullup      : 1;  /* bit[1]   : ID上拉电阻使能 */
        unsigned int  iddig_sel     : 1;  /* bit[2]   : ACA接口来源选择：
                                                        00：来自寄存器；
                                                        01：来自PHY的iddig；
                                                        10：来自PHY的ACA接口；
                                                        其他：保留 */
        unsigned int  iddig         : 1;  /* bit[3]   : 工作模式识别 */
        unsigned int  drvvbus_sel   : 1;  /* bit[4]   : 开启vbus电压选择：
                                                        0：来自控制器；
                                                        1：来自寄存器 */
        unsigned int  drvvbus       : 1;  /* bit[5]   : 使能vbus施加电压 */
        unsigned int  vbusvalid_sel : 1;  /* bit[6]   : 控制器的vbusvalid信号来源选择：
                                                        0：选择PHY输出的vbusvalid;
                                                        1：选择内部的drvvbus信号 */
        unsigned int  reserved      : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL0_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_idpullup_sel_START   (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_idpullup_sel_END     (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_idpullup_START       (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_idpullup_END         (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_iddig_sel_START      (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_iddig_sel_END        (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_iddig_START          (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_iddig_END            (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_drvvbus_sel_START    (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_drvvbus_sel_END      (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_drvvbus_START        (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_drvvbus_END          (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_vbusvalid_sel_START  (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL0_vbusvalid_sel_END    (6)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_CTRL1_UNION
 结构说明  : USBOTG3_CTRL1 寄存器结构定义。地址偏移量:0x04，初值:0x00020080，宽度:32
 寄存器说明: USB控制器参数配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  host_u2_port_disable            : 1;  /* bit[0]    : USB2.0端口去使能控制。
                                                                           0：端口使能
                                                                           1：端口去使能 */
        unsigned int  host_u3_port_disable            : 1;  /* bit[1]    : USB2 SS端口去使能控制。
                                                                           0：端口使能
                                                                           1：端口去使能 */
        unsigned int  hub_port_overcurrent            : 2;  /* bit[2-3]  : 根集线器过流指示。高位代表SS 端口，低位代表legacy端口。 */
        unsigned int  hub_port_perm_attach            : 2;  /* bit[4-5]  : 用于指示是否有设备永久链接在下行端口上。高位代表SS 端口，低位代表legacy端口
                                                                           1：永久链接
                                                                           0：非永久链接 */
        unsigned int  host_port_power_control_present : 1;  /* bit[6]    : 端口电源控制。
                                                                           1：指示端口有电源开关
                                                                           0：端口没有电源开关 */
        unsigned int  xhc_bme                         : 1;  /* bit[7]    : 使能总线master。固定为1。 */
        unsigned int  bus_filter_bypass               : 4;  /* bit[8-11] : 总线过滤旁路控制。
                                                                           [3]:旁路utmiotg_iddig的过滤
                                                                           [2]:旁路utmisrp_bvalid的过滤
                                                                           [1]:旁路pipe3_PowerPresent的过滤
                                                                           [0]:旁路utmiotg_vbusvalid的过滤 */
        unsigned int  fladj_30mhz_reg                 : 6;  /* bit[12-17]: HS jitter调整。校准micro-frame的准确度。 */
        unsigned int  reserved                        : 14; /* bit[18-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL1_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_u2_port_disable_START             (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_u2_port_disable_END               (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_u3_port_disable_START             (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_u3_port_disable_END               (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_hub_port_overcurrent_START             (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_hub_port_overcurrent_END               (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_hub_port_perm_attach_START             (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_hub_port_perm_attach_END               (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_port_power_control_present_START  (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_host_port_power_control_present_END    (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_xhc_bme_START                          (7)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_xhc_bme_END                            (7)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_bus_filter_bypass_START                (8)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_bus_filter_bypass_END                  (11)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_fladj_30mhz_reg_START                  (12)
#define SOC_USB3OTG_BC_USBOTG3_CTRL1_fladj_30mhz_reg_END                    (17)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_CTRL2_UNION
 结构说明  : USBOTG3_CTRL2 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: PHY低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  test_powerdown_hsp : 1;  /* bit[0]   : 超速电路下电控制 */
        unsigned int  test_powerdown_ssp : 1;  /* bit[1]   : 高速电路下电控制 */
        unsigned int  reserved           : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL2_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_test_powerdown_hsp_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_test_powerdown_hsp_END    (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_test_powerdown_ssp_START  (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL2_test_powerdown_ssp_END    (1)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_CTRL3_UNION
 结构说明  : USBOTG3_CTRL3 寄存器结构定义。地址偏移量:0x0C，初值:0x00000004，宽度:32
 寄存器说明: 选择控制寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  commononn     : 1;  /* bit[0]   : PHY的COMMON电路电源开关 */
        unsigned int  otgdisable    : 1;  /* bit[1]   : 关闭PHY的OTG特性。 */
        unsigned int  retenablen    : 1;  /* bit[2]   : 保留。缺省值为1。 */
        unsigned int  txbitstuffen  : 1;  /* bit[3]   : 在opmode=2'b11时，控制DATAIN[7:0]上的bit stuffing
                                                        1: Bit stuffing使能
                                                        0: Bit stuffing去使能. */
        unsigned int  txbitstuffehn : 1;  /* bit[4]   : 在opmode=2'b11时，控制DATAIN[15:8]上的bit stuffing
                                                        1: Bit stuffing使能
                                                        0: Bit stuffing去使能. */
        unsigned int  vbusvldextsel : 1;  /* bit[5]   : VBUS有效选择：
                                                        0：来自PHY内部比较器
                                                        1：来自寄存器 */
        unsigned int  vbusvldext    : 1;  /* bit[6]   : VBUS有效 */
        unsigned int  reserved      : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL3_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_commononn_START      (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_commononn_END        (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_otgdisable_START     (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_otgdisable_END       (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_retenablen_START     (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_retenablen_END       (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_txbitstuffen_START   (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_txbitstuffen_END     (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_txbitstuffehn_START  (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_txbitstuffehn_END    (4)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_vbusvldextsel_START  (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_vbusvldextsel_END    (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_vbusvldext_START     (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL3_vbusvldext_END       (6)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_CTRL4_UNION
 结构说明  : USBOTG3_CTRL4 寄存器结构定义。地址偏移量:0x10，初值:0x00E466DB，宽度:32
 寄存器说明: legacy USB参数调整寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  compdistune       : 3;  /* bit[0-2]  : Host模式下设备断连阈值调节。 */
        unsigned int  otgtune           : 3;  /* bit[3-5]  : 调节Vbus阈值。 */
        unsigned int  sqrxtune          : 3;  /* bit[6-8]  : HS模式下squelch电压阈值调节 */
        unsigned int  txfslstune        : 4;  /* bit[9-12] : FS/LS模式下，单端元阻抗调节。 */
        unsigned int  txhsxvtune        : 2;  /* bit[13-14]: HS模式下，眼图交叉点调节参数 */
        unsigned int  txpreempamptune   : 2;  /* bit[15-16]: 调整驱动电流的值。 */
        unsigned int  txpreemppulsetune : 1;  /* bit[17]   : 预加重电流持续时间调整参数。缺省值为0. */
        unsigned int  txrestune         : 2;  /* bit[18-19]: 调整驱动源端阻抗匹配。缺省值2'b01. */
        unsigned int  txrisetune        : 2;  /* bit[20-21]: HS模式上升/下降时间调整参数。缺省值为2'b10 */
        unsigned int  txvreftune        : 4;  /* bit[22-25]: 高 速 直 流 电 平 调 整 ， 缺 省 值 为4’b1000.正常的值为 400mv */
        unsigned int  reserved          : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL4_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_compdistune_START        (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_compdistune_END          (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_otgtune_START            (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_otgtune_END              (5)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_sqrxtune_START           (6)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_sqrxtune_END             (8)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txfslstune_START         (9)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txfslstune_END           (12)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txhsxvtune_START         (13)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txhsxvtune_END           (14)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txpreempamptune_START    (15)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txpreempamptune_END      (16)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txpreemppulsetune_START  (17)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txpreemppulsetune_END    (17)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txrestune_START          (18)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txrestune_END            (19)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txrisetune_START         (20)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txrisetune_END           (21)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txvreftune_START         (22)
#define SOC_USB3OTG_BC_USBOTG3_CTRL4_txvreftune_END           (25)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_CTRL5_UNION
 结构说明  : USBOTG3_CTRL5 寄存器结构定义。地址偏移量:0x14，初值:0xFEE38605，宽度:32
 寄存器说明: SS参数调整寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  los_bias        : 3;  /* bit[0-2]  : LoS检测器阈值控制。 */
        unsigned int  rx_los_mask_val : 10; /* bit[3-12] : 配置LoS掩膜宽度。主要功能是过滤不兼容LPPS的信号。 */
        unsigned int  tx_deemph_3p5db : 6;  /* bit[13-18]: 3.5DB去加重 */
        unsigned int  tx_deemph_6db   : 6;  /* bit[19-24]: 6DB去加重 */
        unsigned int  tx_swing_full   : 7;  /* bit[25-31]: TX强度调节 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL5_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_los_bias_START         (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_los_bias_END           (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_rx_los_mask_val_START  (3)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_rx_los_mask_val_END    (12)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_deemph_3p5db_START  (13)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_deemph_3p5db_END    (18)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_deemph_6db_START    (19)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_deemph_6db_END      (24)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_swing_full_START    (25)
#define SOC_USB3OTG_BC_USBOTG3_CTRL5_tx_swing_full_END      (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_CTRL6_UNION
 结构说明  : USBOTG3_CTRL6 寄存器结构定义。地址偏移量:0x18，初值:0x00000004，宽度:32
 寄存器说明: SS参数调整寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_vboost_lvl : 3;  /* bit[0-2] : TX电压Boost电平控制。 */
        unsigned int  reserved      : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL6_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_tx_vboost_lvl_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL6_tx_vboost_lvl_END    (2)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_CTRL7_UNION
 结构说明  : USBOTG3_CTRL7 寄存器结构定义。地址偏移量:0x1C，初值:0x000200E2，宽度:32
 寄存器说明: 选择控制寄存器7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  refclksel          : 2;  /* bit[0-1]  : 参考时钟选择。缺省为2'b10. */
        unsigned int  fsel               : 6;  /* bit[2-7]  : 参考时钟频率选择。
                                                              6'h38: 19.2MHz
                                                              6'h2A: 24MHz */
        unsigned int  mpll_multiplier    : 7;  /* bit[8-14] : MPLL频率乘数控制。默认为0，不需要调整。 */
        unsigned int  ref_clkdiv2        : 1;  /* bit[15]   : 输入参考时钟分频控制。
                                                              1：参考时钟大于100MHz
                                                              0：参考时钟低于100MHz */
        unsigned int  ref_ssp_en         : 1;  /* bit[16]   : SS功能参考时钟使能 */
        unsigned int  ssc_en             : 1;  /* bit[17]   : 扩频使能。
                                                              1：使能扩频
                                                              0：去使能 */
        unsigned int  ssc_range          : 3;  /* bit[18-20]: 扩频时钟范围。单位PPM。
                                                              3'b000:-4980
                                                              3'b001: -4492
                                                              3'b010:-4003
                                                              其它：保留 */
        unsigned int  ssc_ref_clk_sel    : 9;  /* bit[21-29]: 扩频参考时钟偏移。 */
        unsigned int  lane0_ext_pclk_req : 1;  /* bit[30]   : 外部PIPE时钟使能请求。 */
        unsigned int  lane0_tx2rx_loopbk : 1;  /* bit[31]   : Loopback使能控制 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_CTRL7_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_refclksel_START           (0)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_refclksel_END             (1)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_fsel_START                (2)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_fsel_END                  (7)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_mpll_multiplier_START     (8)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_mpll_multiplier_END       (14)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ref_clkdiv2_START         (15)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ref_clkdiv2_END           (15)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ref_ssp_en_START          (16)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ref_ssp_en_END            (16)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_en_START              (17)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_en_END                (17)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_range_START           (18)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_range_END             (20)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_ref_clk_sel_START     (21)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_ssc_ref_clk_sel_END       (29)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_lane0_ext_pclk_req_START  (30)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_lane0_ext_pclk_req_END    (30)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_lane0_tx2rx_loopbk_START  (31)
#define SOC_USB3OTG_BC_USBOTG3_CTRL7_lane0_tx2rx_loopbk_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_STS0_UNION
 结构说明  : USBOTG3_STS0 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: 状态寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS0_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS0_debug_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS0_debug_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_STS1_UNION
 结构说明  : USBOTG3_STS1 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: 状态寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debugh : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS1_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS1_debugh_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS1_debugh_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_STS2_UNION
 结构说明  : USBOTG3_STS2 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: 状态寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  logic_analyzer_trace : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS2_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS2_logic_analyzer_trace_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS2_logic_analyzer_trace_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_STS3_UNION
 结构说明  : USBOTG3_STS3 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: 状态寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  logic_analyzer_traceh : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS3_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS3_logic_analyzer_traceh_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS3_logic_analyzer_traceh_END    (31)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_BC_CTRL0_UNION
 结构说明  : BC_CTRL0 寄存器结构定义。地址偏移量:0x30，初值:0x00000205，宽度:32
 寄存器说明: BC控制器寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_opmode     : 2;  /* bit[0-1]  : 充电检测时，OPMODE的控制 */
        unsigned int  bc_xcvrselect : 2;  /* bit[2-3]  : 充电模式时，PHY的transmiter选择 */
        unsigned int  bc_termselect : 1;  /* bit[4]    : 充电模式时，PHY的阻抗选择 */
        unsigned int  bc_txvalid    : 1;  /* bit[5]    : 充电模式下TX有效使能控制 */
        unsigned int  bc_txvalidh   : 1;  /* bit[6]    : 充电模式下TX有效使能控制 */
        unsigned int  bc_dppulldown : 1;  /* bit[7]    : 充电模式下DP上下拉电阻控制 */
        unsigned int  bc_dmpulldown : 1;  /* bit[8]    : 充电模式下DM上下拉电阻控制 */
        unsigned int  bc_suspend_n  : 1;  /* bit[9]    : 充电模式下suspendn控制。缺省为1 */
        unsigned int  bc_idpullup   : 1;  /* bit[10]   : 充电模式下idpullup控制 */
        unsigned int  reserved      : 21; /* bit[11-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_BC_CTRL0_UNION;
#endif
#define SOC_USB3OTG_BC_BC_CTRL0_bc_opmode_START      (0)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_opmode_END        (1)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_xcvrselect_START  (2)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_xcvrselect_END    (3)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_termselect_START  (4)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_termselect_END    (4)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_txvalid_START     (5)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_txvalid_END       (5)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_txvalidh_START    (6)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_txvalidh_END      (6)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_dppulldown_START  (7)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_dppulldown_END    (7)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_dmpulldown_START  (8)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_dmpulldown_END    (8)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_suspend_n_START   (9)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_suspend_n_END     (9)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_idpullup_START    (10)
#define SOC_USB3OTG_BC_BC_CTRL0_bc_idpullup_END      (10)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_BC_CTRL1_UNION
 结构说明  : BC_CTRL1 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: BC控制器寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_mode  : 1;  /* bit[0]   : 充电检测模式使能。
                                                   1：使能充电检测
                                                   0：充电检测不使能 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_BC_CTRL1_UNION;
#endif
#define SOC_USB3OTG_BC_BC_CTRL1_bc_mode_START   (0)
#define SOC_USB3OTG_BC_BC_CTRL1_bc_mode_END     (0)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_BC_CTRL2_UNION
 结构说明  : BC_CTRL2 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: BC控制器寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_phy_acaenb     : 1;  /* bit[0]   : ACA接口使能 */
        unsigned int  bc_phy_dcdenb     : 1;  /* bit[1]   : DCD检测使能 */
        unsigned int  bc_phy_chrgsel    : 1;  /* bit[2]   : 充电源选择
                                                            1：源电压驱动DM，在DP端吸收
                                                            0：源电压驱动DP，在DM端吸收 */
        unsigned int  bc_phy_vdatarcenb : 1;  /* bit[3]   : 充电源使能控制。
                                                            1：源电压使能
                                                            0：源电压去使能 */
        unsigned int  bc_phy_vdatdetenb : 1;  /* bit[4]   : 充电连接检测使能。
                                                            1：DATA检测电压使能
                                                            0：DATA检测电压去使能 */
        unsigned int  reserved          : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_BC_CTRL2_UNION;
#endif
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_acaenb_START      (0)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_acaenb_END        (0)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_dcdenb_START      (1)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_dcdenb_END        (1)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_chrgsel_START     (2)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_chrgsel_END       (2)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_vdatarcenb_START  (3)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_vdatarcenb_END    (3)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_vdatdetenb_START  (4)
#define SOC_USB3OTG_BC_BC_CTRL2_bc_phy_vdatdetenb_END    (4)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_BC_STS0_UNION
 结构说明  : BC_STS0 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: BC状态寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_sessvld      : 1;  /* bit[0]    : session 有效 */
        unsigned int  bc_rid_a        : 1;  /* bit[1]    : ACA接口状态 */
        unsigned int  bc_rid_b        : 1;  /* bit[2]    : ACA接口状态 */
        unsigned int  bc_rid_c        : 1;  /* bit[3]    : ACA接口状态 */
        unsigned int  bc_rid_float    : 1;  /* bit[4]    : ACA接口状态 */
        unsigned int  bc_rid_gnd      : 1;  /* bit[5]    : ACA接口状态 */
        unsigned int  bc_phy_fsvplus  : 1;  /* bit[6]    : DP状态 */
        unsigned int  bc_phy_fsvminus : 1;  /* bit[7]    : DM状态 */
        unsigned int  bc_phy_chgdet   : 1;  /* bit[8]    : 充电器检测状态。
                                                           1：检测到充电器
                                                           0：未检测到 */
        unsigned int  bc_linestate    : 2;  /* bit[9-10] : 数据线缆状态 */
        unsigned int  reserved        : 21; /* bit[11-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_BC_STS0_UNION;
#endif
#define SOC_USB3OTG_BC_BC_STS0_bc_sessvld_START       (0)
#define SOC_USB3OTG_BC_BC_STS0_bc_sessvld_END         (0)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_a_START         (1)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_a_END           (1)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_b_START         (2)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_b_END           (2)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_c_START         (3)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_c_END           (3)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_float_START     (4)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_float_END       (4)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_gnd_START       (5)
#define SOC_USB3OTG_BC_BC_STS0_bc_rid_gnd_END         (5)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_fsvplus_START   (6)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_fsvplus_END     (6)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_fsvminus_START  (7)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_fsvminus_END    (7)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_chgdet_START    (8)
#define SOC_USB3OTG_BC_BC_STS0_bc_phy_chgdet_END      (8)
#define SOC_USB3OTG_BC_BC_STS0_bc_linestate_START     (9)
#define SOC_USB3OTG_BC_BC_STS0_bc_linestate_END       (10)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_RAM_CTRL_UNION
 结构说明  : RAM_CTRL 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: RAM控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ram0_slp : 1;  /* bit[0]   : ram0低功耗控制 */
        unsigned int  ram1_slp : 1;  /* bit[1]   : ram1低功耗控制 */
        unsigned int  ram2_slp : 1;  /* bit[2]   : ram2低功耗控制 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_RAM_CTRL_UNION;
#endif
#define SOC_USB3OTG_BC_RAM_CTRL_ram0_slp_START  (0)
#define SOC_USB3OTG_BC_RAM_CTRL_ram0_slp_END    (0)
#define SOC_USB3OTG_BC_RAM_CTRL_ram1_slp_START  (1)
#define SOC_USB3OTG_BC_RAM_CTRL_ram1_slp_END    (1)
#define SOC_USB3OTG_BC_RAM_CTRL_ram2_slp_START  (2)
#define SOC_USB3OTG_BC_RAM_CTRL_ram2_slp_END    (2)


/*****************************************************************************
 结构名    : SOC_USB3OTG_BC_USBOTG3_STS4_UNION
 结构说明  : USBOTG3_STS4 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: 状态寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_chirp_on : 1;  /* bit[0]   : 保留。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_USB3OTG_BC_USBOTG3_STS4_UNION;
#endif
#define SOC_USB3OTG_BC_USBOTG3_STS4_bc_chirp_on_START  (0)
#define SOC_USB3OTG_BC_USBOTG3_STS4_bc_chirp_on_END    (0)






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

#endif /* end of soc_usb3otg_bc_interface.h */
