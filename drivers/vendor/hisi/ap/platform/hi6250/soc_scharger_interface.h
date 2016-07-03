

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_SCHARGER_INTERFACE_H__
#define __SOC_SCHARGER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/2) SHEET_NAME
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_SCHARGER_a_UNION */
#define SOC_SCHARGER_a_ADDR(base)                     ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_SCHARGER_b_UNION */
#define SOC_SCHARGER_b_ADDR(base)                     ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_SCHARGER_c_UNION */
#define SOC_SCHARGER_c_ADDR(base)                     ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_SCHARGER_d_UNION */
#define SOC_SCHARGER_d_ADDR(base)                     ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_SCHARGER_e_UNION */
#define SOC_SCHARGER_e_ADDR(base)                     ((base) + (0x0000))



/****************************************************************************
                     (2/2) register_define
 ****************************************************************************/
/* 寄存器说明：芯片版本寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHIP_VERSION_UNION */
#define SOC_SCHARGER_CHIP_VERSION_ADDR(base)          ((base) + (0x00))

/* 寄存器说明：状态0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUS0_UNION */
#define SOC_SCHARGER_STATUS0_ADDR(base)               ((base) + (0x01))

/* 寄存器说明：状态1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUS1_UNION */
#define SOC_SCHARGER_STATUS1_ADDR(base)               ((base) + (0x02))

/* 寄存器说明：状态2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUS2_UNION */
#define SOC_SCHARGER_STATUS2_ADDR(base)               ((base) + (0x03))

/* 寄存器说明：状态3寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUS3_UNION */
#define SOC_SCHARGER_STATUS3_ADDR(base)               ((base) + (0x04))

/* 寄存器说明：状态4寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUS4_UNION */
#define SOC_SCHARGER_STATUS4_ADDR(base)               ((base) + (0x05))

/* 寄存器说明：状态5寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUS5_UNION */
#define SOC_SCHARGER_STATUS5_ADDR(base)               ((base) + (0x06))

/* 寄存器说明：中断0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ0_UNION */
#define SOC_SCHARGER_IRQ0_ADDR(base)                  ((base) + (0x07))

/* 寄存器说明：中断1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ1_UNION */
#define SOC_SCHARGER_IRQ1_ADDR(base)                  ((base) + (0x08))

/* 寄存器说明：中断2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ2_UNION */
#define SOC_SCHARGER_IRQ2_ADDR(base)                  ((base) + (0x09))

/* 寄存器说明：中断3寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ3_UNION */
#define SOC_SCHARGER_IRQ3_ADDR(base)                  ((base) + (0x0A))

/* 寄存器说明：中断4寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ4_UNION */
#define SOC_SCHARGER_IRQ4_ADDR(base)                  ((base) + (0x0B))

/* 寄存器说明：中断屏蔽0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQM0_UNION */
#define SOC_SCHARGER_IRQM0_ADDR(base)                 ((base) + (0x0C))

/* 寄存器说明：中断屏蔽1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQM1_UNION */
#define SOC_SCHARGER_IRQM1_ADDR(base)                 ((base) + (0x0D))

/* 寄存器说明：中断屏蔽2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQM2_UNION */
#define SOC_SCHARGER_IRQM2_ADDR(base)                 ((base) + (0x0E))

/* 寄存器说明：中断屏蔽3寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQM3_UNION */
#define SOC_SCHARGER_IRQM3_ADDR(base)                 ((base) + (0x0F))

/* 寄存器说明：中断屏蔽4寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQM4_UNION */
#define SOC_SCHARGER_IRQM4_ADDR(base)                 ((base) + (0x10))

/* 寄存器说明：开关控制0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_ONFF0_UNION */
#define SOC_SCHARGER_ONFF0_ADDR(base)                 ((base) + (0x11))

/* 寄存器说明：开关控制1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_ONFF1_UNION */
#define SOC_SCHARGER_ONFF1_ADDR(base)                 ((base) + (0x12))

/* 寄存器说明：温度报警寄存器。
   位域定义UNION结构:  SOC_SCHARGER_REF_REG_UNION */
#define SOC_SCHARGER_REF_REG_ADDR(base)               ((base) + (0x13))

/* 寄存器说明：电池过压点选择寄存器。
   位域定义UNION结构:  SOC_SCHARGER_VBAT_OV_SEL_UNION */
#define SOC_SCHARGER_VBAT_OV_SEL_ADDR(base)           ((base) + (0x14))

/* 寄存器说明：WLED_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG0_UNION */
#define SOC_SCHARGER_WLED_REG0_ADDR(base)             ((base) + (0x15))

/* 寄存器说明：WLED_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG1_UNION */
#define SOC_SCHARGER_WLED_REG1_ADDR(base)             ((base) + (0x16))

/* 寄存器说明：WLED_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG2_UNION */
#define SOC_SCHARGER_WLED_REG2_ADDR(base)             ((base) + (0x17))

/* 寄存器说明：WLED_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG3_UNION */
#define SOC_SCHARGER_WLED_REG3_ADDR(base)             ((base) + (0x18))

/* 寄存器说明：WLED_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG4_UNION */
#define SOC_SCHARGER_WLED_REG4_ADDR(base)             ((base) + (0x19))

/* 寄存器说明：WLED_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG5_UNION */
#define SOC_SCHARGER_WLED_REG5_ADDR(base)             ((base) + (0x1A))

/* 寄存器说明：WLED_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG6_UNION */
#define SOC_SCHARGER_WLED_REG6_ADDR(base)             ((base) + (0x1B))

/* 寄存器说明：WLED_REG7调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG7_UNION */
#define SOC_SCHARGER_WLED_REG7_ADDR(base)             ((base) + (0x1C))

/* 寄存器说明：WLED_REG8调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG8_UNION */
#define SOC_SCHARGER_WLED_REG8_ADDR(base)             ((base) + (0x1D))

/* 寄存器说明：WLED_REG9调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WLED_REG9_UNION */
#define SOC_SCHARGER_WLED_REG9_ADDR(base)             ((base) + (0x1E))

/* 寄存器说明：LCD_BOOST_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG0_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG0_ADDR(base)        ((base) + (0x1F))

/* 寄存器说明：LCD_BOOST_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG1_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG1_ADDR(base)        ((base) + (0x20))

/* 寄存器说明：LCD_BOOST_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG2_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG2_ADDR(base)        ((base) + (0x21))

/* 寄存器说明：LCD_BOOST_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG3_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG3_ADDR(base)        ((base) + (0x22))

/* 寄存器说明：LCD_BOOST_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG4_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG4_ADDR(base)        ((base) + (0x23))

/* 寄存器说明：LCD_BOOST_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG5_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG5_ADDR(base)        ((base) + (0x24))

/* 寄存器说明：LCD_BOOST_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG6_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG6_ADDR(base)        ((base) + (0x25))

/* 寄存器说明：LCD_BOOST_REG7调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG7_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG7_ADDR(base)        ((base) + (0x26))

/* 寄存器说明：LCD_BOOST_REG8调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG8_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG8_ADDR(base)        ((base) + (0x27))

/* 寄存器说明：LCD_BOOST_REG9调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG9_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG9_ADDR(base)        ((base) + (0x28))

/* 寄存器说明：LCD_BOOST_REG10调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG10_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG10_ADDR(base)       ((base) + (0x29))

/* 寄存器说明：LCD_BOOST_REG11调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG11_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG11_ADDR(base)       ((base) + (0x2A))

/* 寄存器说明：LCD_BOOST_REG12调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG12_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG12_ADDR(base)       ((base) + (0x2B))

/* 寄存器说明：LCD_BOOST_REG13调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG13_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG13_ADDR(base)       ((base) + (0x2C))

/* 寄存器说明：LCD_BOOST_REG14调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_BOOST_REG14_UNION */
#define SOC_SCHARGER_LCD_BOOST_REG14_ADDR(base)       ((base) + (0x2D))

/* 寄存器说明：LCD_NCP_REG0调节寄存器。.
   位域定义UNION结构:  SOC_SCHARGER_LCD_NCP_REG0_UNION */
#define SOC_SCHARGER_LCD_NCP_REG0_ADDR(base)          ((base) + (0x2E))

/* 寄存器说明：LCD_NCP_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_NCP_REG1_UNION */
#define SOC_SCHARGER_LCD_NCP_REG1_ADDR(base)          ((base) + (0x2F))

/* 寄存器说明：LCD_NCP_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_NCP_REG2_UNION */
#define SOC_SCHARGER_LCD_NCP_REG2_ADDR(base)          ((base) + (0x30))

/* 寄存器说明：LCD_NCP_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_NCP_REG3_UNION */
#define SOC_SCHARGER_LCD_NCP_REG3_ADDR(base)          ((base) + (0x31))

/* 寄存器说明：LCD_NCP_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_NCP_REG4_UNION */
#define SOC_SCHARGER_LCD_NCP_REG4_ADDR(base)          ((base) + (0x32))

/* 寄存器说明：LCD_NCP_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_NCP_REG5_UNION */
#define SOC_SCHARGER_LCD_NCP_REG5_ADDR(base)          ((base) + (0x33))

/* 寄存器说明：LCD_LDO_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LCD_LDO_REG0_UNION */
#define SOC_SCHARGER_LCD_LDO_REG0_ADDR(base)          ((base) + (0x34))

/* 寄存器说明：LDO_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_LDO_REG0_UNION */
#define SOC_SCHARGER_LDO_REG0_ADDR(base)              ((base) + (0x35))

/* 寄存器说明：BUCK_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG0_UNION */
#define SOC_SCHARGER_BUCK_REG0_ADDR(base)             ((base) + (0x36))

/* 寄存器说明：BUCK_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG1_UNION */
#define SOC_SCHARGER_BUCK_REG1_ADDR(base)             ((base) + (0x37))

/* 寄存器说明：BUCK_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG2_UNION */
#define SOC_SCHARGER_BUCK_REG2_ADDR(base)             ((base) + (0x38))

/* 寄存器说明：BUCK_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG3_UNION */
#define SOC_SCHARGER_BUCK_REG3_ADDR(base)             ((base) + (0x39))

/* 寄存器说明：BUCK_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG4_UNION */
#define SOC_SCHARGER_BUCK_REG4_ADDR(base)             ((base) + (0x3A))

/* 寄存器说明：BUCK_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG5_UNION */
#define SOC_SCHARGER_BUCK_REG5_ADDR(base)             ((base) + (0x3B))

/* 寄存器说明：BUCK_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG6_UNION */
#define SOC_SCHARGER_BUCK_REG6_ADDR(base)             ((base) + (0x3C))

/* 寄存器说明：OTG_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG0_UNION */
#define SOC_SCHARGER_OTG_REG0_ADDR(base)              ((base) + (0x3D))

/* 寄存器说明：OTG_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG1_UNION */
#define SOC_SCHARGER_OTG_REG1_ADDR(base)              ((base) + (0x3E))

/* 寄存器说明：OTG_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG2_UNION */
#define SOC_SCHARGER_OTG_REG2_ADDR(base)              ((base) + (0x3F))

/* 寄存器说明：OTG_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG3_UNION */
#define SOC_SCHARGER_OTG_REG3_ADDR(base)              ((base) + (0x40))

/* 寄存器说明：OTG_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG4_UNION */
#define SOC_SCHARGER_OTG_REG4_ADDR(base)              ((base) + (0x41))

/* 寄存器说明：OTG_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG5_UNION */
#define SOC_SCHARGER_OTG_REG5_ADDR(base)              ((base) + (0x42))

/* 寄存器说明：OTG_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG6_UNION */
#define SOC_SCHARGER_OTG_REG6_ADDR(base)              ((base) + (0x43))

/* 寄存器说明：OTG_REG7调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG7_UNION */
#define SOC_SCHARGER_OTG_REG7_ADDR(base)              ((base) + (0x44))

/* 寄存器说明：OTG_REG8调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG8_UNION */
#define SOC_SCHARGER_OTG_REG8_ADDR(base)              ((base) + (0x45))

/* 寄存器说明：OTG_REG9调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG9_UNION */
#define SOC_SCHARGER_OTG_REG9_ADDR(base)              ((base) + (0x46))

/* 寄存器说明：OTG_REG10调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG10_UNION */
#define SOC_SCHARGER_OTG_REG10_ADDR(base)             ((base) + (0x47))

/* 寄存器说明：CHG_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG0_UNION */
#define SOC_SCHARGER_CHG_REG0_ADDR(base)              ((base) + (0x48))

/* 寄存器说明：CHG_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG1_UNION */
#define SOC_SCHARGER_CHG_REG1_ADDR(base)              ((base) + (0x49))

/* 寄存器说明：CHG_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG2_UNION */
#define SOC_SCHARGER_CHG_REG2_ADDR(base)              ((base) + (0x4A))

/* 寄存器说明：CHG_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG3_UNION */
#define SOC_SCHARGER_CHG_REG3_ADDR(base)              ((base) + (0x4B))

/* 寄存器说明：CHG_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG4_UNION */
#define SOC_SCHARGER_CHG_REG4_ADDR(base)              ((base) + (0x4C))

/* 寄存器说明：CHG_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG5_UNION */
#define SOC_SCHARGER_CHG_REG5_ADDR(base)              ((base) + (0x4D))

/* 寄存器说明：CHG_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG6_UNION */
#define SOC_SCHARGER_CHG_REG6_ADDR(base)              ((base) + (0x4E))

/* 寄存器说明：CHG_REG7调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG7_UNION */
#define SOC_SCHARGER_CHG_REG7_ADDR(base)              ((base) + (0x4F))

/* 寄存器说明：CHG_REG8调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG8_UNION */
#define SOC_SCHARGER_CHG_REG8_ADDR(base)              ((base) + (0x50))

/* 寄存器说明：CHG_REG9调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG9_UNION */
#define SOC_SCHARGER_CHG_REG9_ADDR(base)              ((base) + (0x51))

/* 寄存器说明：CHG_REG10调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG10_UNION */
#define SOC_SCHARGER_CHG_REG10_ADDR(base)             ((base) + (0x52))

/* 寄存器说明：CHG_REG11调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG11_UNION */
#define SOC_SCHARGER_CHG_REG11_ADDR(base)             ((base) + (0x53))

/* 寄存器说明：PSEL_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_PSEL_REG0_UNION */
#define SOC_SCHARGER_PSEL_REG0_ADDR(base)             ((base) + (0x54))

/* 寄存器说明：FLASH_BST_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG0_UNION */
#define SOC_SCHARGER_FLASH_BST_REG0_ADDR(base)        ((base) + (0x55))

/* 寄存器说明：FLASH_BST_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG1_UNION */
#define SOC_SCHARGER_FLASH_BST_REG1_ADDR(base)        ((base) + (0x56))

/* 寄存器说明：FLASH_BST_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG2_UNION */
#define SOC_SCHARGER_FLASH_BST_REG2_ADDR(base)        ((base) + (0x57))

/* 寄存器说明：FLASH_BST_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG3_UNION */
#define SOC_SCHARGER_FLASH_BST_REG3_ADDR(base)        ((base) + (0x58))

/* 寄存器说明：FLASH_BST_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG4_UNION */
#define SOC_SCHARGER_FLASH_BST_REG4_ADDR(base)        ((base) + (0x59))

/* 寄存器说明：FLASH_BST_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG5_UNION */
#define SOC_SCHARGER_FLASH_BST_REG5_ADDR(base)        ((base) + (0x5A))

/* 寄存器说明：FLASH_BST_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG6_UNION */
#define SOC_SCHARGER_FLASH_BST_REG6_ADDR(base)        ((base) + (0x5B))

/* 寄存器说明：FLASH_BST_REG7调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG7_UNION */
#define SOC_SCHARGER_FLASH_BST_REG7_ADDR(base)        ((base) + (0x5C))

/* 寄存器说明：FLASH_BST_REG8调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG8_UNION */
#define SOC_SCHARGER_FLASH_BST_REG8_ADDR(base)        ((base) + (0x5D))

/* 寄存器说明：FLASH_BST_REG9调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG9_UNION */
#define SOC_SCHARGER_FLASH_BST_REG9_ADDR(base)        ((base) + (0x5E))

/* 寄存器说明：FLASH_BST_REG10调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG10_UNION */
#define SOC_SCHARGER_FLASH_BST_REG10_ADDR(base)       ((base) + (0x5F))

/* 寄存器说明：FLASH_BST_REG11调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_BST_REG11_UNION */
#define SOC_SCHARGER_FLASH_BST_REG11_ADDR(base)       ((base) + (0x60))

/* 寄存器说明：FLASH_LED_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_LED_REG0_UNION */
#define SOC_SCHARGER_FLASH_LED_REG0_ADDR(base)        ((base) + (0x61))

/* 寄存器说明：FLASH_LED_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_LED_REG1_UNION */
#define SOC_SCHARGER_FLASH_LED_REG1_ADDR(base)        ((base) + (0x62))

/* 寄存器说明：SYS调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SYS_REG_UNION */
#define SOC_SCHARGER_SYS_REG_ADDR(base)               ((base) + (0x63))

/* 寄存器说明：FLASH_LED_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_LED_REG2_UNION */
#define SOC_SCHARGER_FLASH_LED_REG2_ADDR(base)        ((base) + (0x64))

/* 寄存器说明：FLASH_LED_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_LED_REG3_UNION */
#define SOC_SCHARGER_FLASH_LED_REG3_ADDR(base)        ((base) + (0x65))

/* 寄存器说明：FLASH_LED_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_LED_REG4_UNION */
#define SOC_SCHARGER_FLASH_LED_REG4_ADDR(base)        ((base) + (0x66))

/* 寄存器说明：FLASH_LED_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_LED_REG5_UNION */
#define SOC_SCHARGER_FLASH_LED_REG5_ADDR(base)        ((base) + (0x67))

/* 寄存器说明：FLASH_LED_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_LED_REG6_UNION */
#define SOC_SCHARGER_FLASH_LED_REG6_ADDR(base)        ((base) + (0x68))

/* 寄存器说明：FLASH_LED_REG7调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FLASH_LED_REG7_UNION */
#define SOC_SCHARGER_FLASH_LED_REG7_ADDR(base)        ((base) + (0x69))

/* 寄存器说明：CTRL_REG调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CTRL_REG_UNION */
#define SOC_SCHARGER_CTRL_REG_ADDR(base)              ((base) + (0x6A))

/* 寄存器说明：SYS_SET_REG调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SYS_SET_REG_UNION */
#define SOC_SCHARGER_SYS_SET_REG_ADDR(base)           ((base) + (0x6B))





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
                     (1/2) SHEET_NAME
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_SCHARGER_a_UNION
 结构说明  : a 寄存器结构定义。地址偏移量:0x0000，初值:0x0000，宽度:16
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  f_5 : 12; /* bit[0-11]:  */
        unsigned short  f_4 : 1;  /* bit[12]  :  */
        unsigned short  f_3 : 1;  /* bit[13]  :  */
        unsigned short  f_2 : 1;  /* bit[14]  :  */
        unsigned short  f_1 : 1;  /* bit[15]  :  */
    } reg;
} SOC_SCHARGER_a_UNION;
#endif
#define SOC_SCHARGER_a_f_5_START  (0)
#define SOC_SCHARGER_a_f_5_END    (11)
#define SOC_SCHARGER_a_f_4_START  (12)
#define SOC_SCHARGER_a_f_4_END    (12)
#define SOC_SCHARGER_a_f_3_START  (13)
#define SOC_SCHARGER_a_f_3_END    (13)
#define SOC_SCHARGER_a_f_2_START  (14)
#define SOC_SCHARGER_a_f_2_END    (14)
#define SOC_SCHARGER_a_f_1_START  (15)
#define SOC_SCHARGER_a_f_1_END    (15)


/*****************************************************************************
 结构名    : SOC_SCHARGER_b_UNION
 结构说明  : b 寄存器结构定义。地址偏移量:0x0000，初值:0x0000，宽度:16
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  f_10 : 12; /* bit[0-11]:  */
        unsigned short  f_9  : 1;  /* bit[12]  :  */
        unsigned short  f_8  : 1;  /* bit[13]  :  */
        unsigned short  f_7  : 1;  /* bit[14]  :  */
        unsigned short  f_6  : 1;  /* bit[15]  :  */
    } reg;
} SOC_SCHARGER_b_UNION;
#endif
#define SOC_SCHARGER_b_f_10_START  (0)
#define SOC_SCHARGER_b_f_10_END    (11)
#define SOC_SCHARGER_b_f_9_START   (12)
#define SOC_SCHARGER_b_f_9_END     (12)
#define SOC_SCHARGER_b_f_8_START   (13)
#define SOC_SCHARGER_b_f_8_END     (13)
#define SOC_SCHARGER_b_f_7_START   (14)
#define SOC_SCHARGER_b_f_7_END     (14)
#define SOC_SCHARGER_b_f_6_START   (15)
#define SOC_SCHARGER_b_f_6_END     (15)


/*****************************************************************************
 结构名    : SOC_SCHARGER_c_UNION
 结构说明  : c 寄存器结构定义。地址偏移量:0x0000，初值:0x0000，宽度:16
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  f_15 : 12; /* bit[0-11]:  */
        unsigned short  f_14 : 1;  /* bit[12]  :  */
        unsigned short  f_13 : 1;  /* bit[13]  :  */
        unsigned short  f_12 : 1;  /* bit[14]  :  */
        unsigned short  f_11 : 1;  /* bit[15]  :  */
    } reg;
} SOC_SCHARGER_c_UNION;
#endif
#define SOC_SCHARGER_c_f_15_START  (0)
#define SOC_SCHARGER_c_f_15_END    (11)
#define SOC_SCHARGER_c_f_14_START  (12)
#define SOC_SCHARGER_c_f_14_END    (12)
#define SOC_SCHARGER_c_f_13_START  (13)
#define SOC_SCHARGER_c_f_13_END    (13)
#define SOC_SCHARGER_c_f_12_START  (14)
#define SOC_SCHARGER_c_f_12_END    (14)
#define SOC_SCHARGER_c_f_11_START  (15)
#define SOC_SCHARGER_c_f_11_END    (15)


/*****************************************************************************
 结构名    : SOC_SCHARGER_d_UNION
 结构说明  : d 寄存器结构定义。地址偏移量:0x0000，初值:0x0000，宽度:16
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  f_20 : 12; /* bit[0-11]:  */
        unsigned short  f_19 : 1;  /* bit[12]  :  */
        unsigned short  f_18 : 1;  /* bit[13]  :  */
        unsigned short  f_17 : 1;  /* bit[14]  :  */
        unsigned short  f_16 : 1;  /* bit[15]  :  */
    } reg;
} SOC_SCHARGER_d_UNION;
#endif
#define SOC_SCHARGER_d_f_20_START  (0)
#define SOC_SCHARGER_d_f_20_END    (11)
#define SOC_SCHARGER_d_f_19_START  (12)
#define SOC_SCHARGER_d_f_19_END    (12)
#define SOC_SCHARGER_d_f_18_START  (13)
#define SOC_SCHARGER_d_f_18_END    (13)
#define SOC_SCHARGER_d_f_17_START  (14)
#define SOC_SCHARGER_d_f_17_END    (14)
#define SOC_SCHARGER_d_f_16_START  (15)
#define SOC_SCHARGER_d_f_16_END    (15)


/*****************************************************************************
 结构名    : SOC_SCHARGER_e_UNION
 结构说明  : e 寄存器结构定义。地址偏移量:0x0000，初值:0x0000，宽度:16
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  f_25 : 12; /* bit[0-11]:  */
        unsigned short  f_24 : 1;  /* bit[12]  :  */
        unsigned short  f_23 : 1;  /* bit[13]  :  */
        unsigned short  f_22 : 1;  /* bit[14]  :  */
        unsigned short  f_21 : 1;  /* bit[15]  :  */
    } reg;
} SOC_SCHARGER_e_UNION;
#endif
#define SOC_SCHARGER_e_f_25_START  (0)
#define SOC_SCHARGER_e_f_25_END    (11)
#define SOC_SCHARGER_e_f_24_START  (12)
#define SOC_SCHARGER_e_f_24_END    (12)
#define SOC_SCHARGER_e_f_23_START  (13)
#define SOC_SCHARGER_e_f_23_END    (13)
#define SOC_SCHARGER_e_f_22_START  (14)
#define SOC_SCHARGER_e_f_22_END    (14)
#define SOC_SCHARGER_e_f_21_START  (15)
#define SOC_SCHARGER_e_f_21_END    (15)




/****************************************************************************
                     (2/2) register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_SCHARGER_CHIP_VERSION_UNION
 结构说明  : CHIP_VERSION 寄存器结构定义。地址偏移量:0x00，初值:0x20，宽度:8
 寄存器说明: 芯片版本寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  version_id_v : 8;  /* bit[0-7]: 版本寄存器，表示版本为V200。 */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_version_id_v_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_version_id_v_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUS0_UNION
 结构说明  : STATUS0 寄存器结构定义。地址偏移量:0x01，初值:0x10，宽度:8
 寄存器说明: 状态0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  to_happened       : 1;  /* bit[0]  : flash_led模块timeout功能触发指示信号：
                                                            0:timeout 功能没有触发
                                                            1:timeout 功能触发 */
        unsigned char  wt_happened       : 1;  /* bit[1]  : flash_led模块watchdog timer功能触发指示信号：
                                                            0:watchdog timer 功能没有触发
                                                            1:watchdog timer 功能触发 */
        unsigned char  buck_dpm_stat_2d  : 1;  /* bit[2]  : 上报buck是否进入DPM模式
                                                            0:no DPM
                                                            1:VINDPM */
        unsigned char  buck_vsys_stat_2d : 1;  /* bit[3]  : 表征buck输出是否是最小电压
                                                            0:Not in VSYSMIN regulation (BAT>VSYSMIN),
                                                            1:In VSYSMIN regulation (BAT<VSYSMIN) */
        unsigned char  wdt_time_out_n    : 1;  /* bit[4]  : 0: watchdog timer 溢出，SOC在规定时间内没有watchdog timer寄存器；
                                                            1: watchdog timer 功能没有触发 或watchdog timer正常； */
        unsigned char  chg_chgstate      : 2;  /* bit[5-6]: 充电状态记录寄存器
                                                            00: Not Charging
                                                            01: Pre-charge
                                                            10: Fast-charg
                                                            11: Charge Termination Done */
        unsigned char  otg_on            : 1;  /* bit[7]  : boost状态指示：
                                                            0：OTG关闭
                                                            1：OTG开启 */
    } reg;
} SOC_SCHARGER_STATUS0_UNION;
#endif
#define SOC_SCHARGER_STATUS0_to_happened_START        (0)
#define SOC_SCHARGER_STATUS0_to_happened_END          (0)
#define SOC_SCHARGER_STATUS0_wt_happened_START        (1)
#define SOC_SCHARGER_STATUS0_wt_happened_END          (1)
#define SOC_SCHARGER_STATUS0_buck_dpm_stat_2d_START   (2)
#define SOC_SCHARGER_STATUS0_buck_dpm_stat_2d_END     (2)
#define SOC_SCHARGER_STATUS0_buck_vsys_stat_2d_START  (3)
#define SOC_SCHARGER_STATUS0_buck_vsys_stat_2d_END    (3)
#define SOC_SCHARGER_STATUS0_wdt_time_out_n_START     (4)
#define SOC_SCHARGER_STATUS0_wdt_time_out_n_END       (4)
#define SOC_SCHARGER_STATUS0_chg_chgstate_START       (5)
#define SOC_SCHARGER_STATUS0_chg_chgstate_END         (6)
#define SOC_SCHARGER_STATUS0_otg_on_START             (7)
#define SOC_SCHARGER_STATUS0_otg_on_END               (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUS1_UNION
 结构说明  : STATUS1 寄存器结构定义。地址偏移量:0x02，初值:0x00，宽度:8
 寄存器说明: 状态1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otmp_150_r          : 1;  /* bit[0]: 0：温度没有超过150度
                                                            1：温度超过150度 */
        unsigned char  otmp_jstp_r         : 1;  /* bit[1]: 0：温度没超过thsd_tstp_set寄存器设置的温度
                                                            1:温度超过thsd_tstp_set寄存器设置的温度 */
        unsigned char  otmp_jreg_r         : 1;  /* bit[2]: 0：温度没超过thsd_treg_set寄存器设置的温度
                                                            1:温度超过thsd_treg_set寄存器设置的温度 */
        unsigned char  vbus_ovp_6p5v_r     : 1;  /* bit[3]: 0:vbus<6.5v
                                                            1:vbus>6.5v */
        unsigned char  vbus_uvp_3p5v_r     : 1;  /* bit[4]: 0:vbus>3.5v
                                                            1:vbus<3.5v */
        unsigned char  fast_chg_fault_r    : 1;  /* bit[5]: 电池快充电故障检测信号：（安全计时超时）
                                                            1：超时充未满故障
                                                            0：电池正常 */
        unsigned char  pre_chg_fault_r     : 1;  /* bit[6]: 弱电池充电故障检测信号：（VBAT低于2.8V/3.0V/3.1V/3.2V）
                                                            1：电池电压过低
                                                            0：电池正常 */
        unsigned char  trickle_chg_fault_r : 1;  /* bit[7]: 死电池充电故障检测信号：（VBAT低于2V）
                                                            1：电池电压过低
                                                            0：电池正常 */
    } reg;
} SOC_SCHARGER_STATUS1_UNION;
#endif
#define SOC_SCHARGER_STATUS1_otmp_150_r_START           (0)
#define SOC_SCHARGER_STATUS1_otmp_150_r_END             (0)
#define SOC_SCHARGER_STATUS1_otmp_jstp_r_START          (1)
#define SOC_SCHARGER_STATUS1_otmp_jstp_r_END            (1)
#define SOC_SCHARGER_STATUS1_otmp_jreg_r_START          (2)
#define SOC_SCHARGER_STATUS1_otmp_jreg_r_END            (2)
#define SOC_SCHARGER_STATUS1_vbus_ovp_6p5v_r_START      (3)
#define SOC_SCHARGER_STATUS1_vbus_ovp_6p5v_r_END        (3)
#define SOC_SCHARGER_STATUS1_vbus_uvp_3p5v_r_START      (4)
#define SOC_SCHARGER_STATUS1_vbus_uvp_3p5v_r_END        (4)
#define SOC_SCHARGER_STATUS1_fast_chg_fault_r_START     (5)
#define SOC_SCHARGER_STATUS1_fast_chg_fault_r_END       (5)
#define SOC_SCHARGER_STATUS1_pre_chg_fault_r_START      (6)
#define SOC_SCHARGER_STATUS1_pre_chg_fault_r_END        (6)
#define SOC_SCHARGER_STATUS1_trickle_chg_fault_r_START  (7)
#define SOC_SCHARGER_STATUS1_trickle_chg_fault_r_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUS2_UNION
 结构说明  : STATUS2 寄存器结构定义。地址偏移量:0x03，初值:0x00，宽度:8
 寄存器说明: 状态2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_scp_r      : 1;  /* bit[0]: 0:wled 没有发生短路
                                                        1:wled 发生短路 */
        unsigned char  wled_ocp_r      : 1;  /* bit[1]: 0:wled 没有发生过流
                                                        1:wled 发生过流 */
        unsigned char  wled_uvp_r      : 1;  /* bit[2]: 0:wled boost没有发生输出欠压
                                                        1:wled boost发生输出欠压 */
        unsigned char  wled_ovp_4p5v_r : 1;  /* bit[3]: 0:wled vifb没有发生过压4p5v
                                                        1:wled vifb 发生过压4p5v */
        unsigned char  wled_ovp_38v_r  : 1;  /* bit[4]: 0:wled vout没有发生过压38v
                                                        1:wled vout 发生过压38v */
        unsigned char  buck_scp_r      : 1;  /* bit[5]: 0:buck没有发生短路
                                                        1:buck发生短路 */
        unsigned char  chg_rechg_r     : 1;  /* bit[6]: 重新充电状态寄存器：
                                                        1：重新充电
                                                        0：无重新充电 */
        unsigned char  reserved        : 1;  /* bit[7]: 保留。 */
    } reg;
} SOC_SCHARGER_STATUS2_UNION;
#endif
#define SOC_SCHARGER_STATUS2_wled_scp_r_START       (0)
#define SOC_SCHARGER_STATUS2_wled_scp_r_END         (0)
#define SOC_SCHARGER_STATUS2_wled_ocp_r_START       (1)
#define SOC_SCHARGER_STATUS2_wled_ocp_r_END         (1)
#define SOC_SCHARGER_STATUS2_wled_uvp_r_START       (2)
#define SOC_SCHARGER_STATUS2_wled_uvp_r_END         (2)
#define SOC_SCHARGER_STATUS2_wled_ovp_4p5v_r_START  (3)
#define SOC_SCHARGER_STATUS2_wled_ovp_4p5v_r_END    (3)
#define SOC_SCHARGER_STATUS2_wled_ovp_38v_r_START   (4)
#define SOC_SCHARGER_STATUS2_wled_ovp_38v_r_END     (4)
#define SOC_SCHARGER_STATUS2_buck_scp_r_START       (5)
#define SOC_SCHARGER_STATUS2_buck_scp_r_END         (5)
#define SOC_SCHARGER_STATUS2_chg_rechg_r_START      (6)
#define SOC_SCHARGER_STATUS2_chg_rechg_r_END        (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUS3_UNION
 结构说明  : STATUS3 寄存器结构定义。地址偏移量:0x04，初值:0x00，宽度:8
 寄存器说明: 状态3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_uvp_r   : 1;  /* bit[0]  : 0：FLASH BOOST 没有发生欠压
                                                            1：FLASH BOOST 发生欠压 */
        unsigned char  flash_bst_ovp_r   : 1;  /* bit[1]  : 0：FLASH BOOST 没有发生过压
                                                            1：FLASH BOOST 发生过压 */
        unsigned char  flash_bst_scp_r   : 1;  /* bit[2]  : 0：FLASH BOOST 没有发生短路
                                                            1：FLASH BOOST 发生短路 */
        unsigned char  reserved_0        : 1;  /* bit[3]  : 保留，配置无用。 */
        unsigned char  flash_led_open_r  : 1;  /* bit[4]  : 0:LED灯没有开路
                                                            1:LED灯开路 */
        unsigned char  flash_led_short_r : 1;  /* bit[5]  : 0：LED灯没有短路
                                                            1：LED灯短路 */
        unsigned char  reserved_1        : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_STATUS3_UNION;
#endif
#define SOC_SCHARGER_STATUS3_flash_bst_uvp_r_START    (0)
#define SOC_SCHARGER_STATUS3_flash_bst_uvp_r_END      (0)
#define SOC_SCHARGER_STATUS3_flash_bst_ovp_r_START    (1)
#define SOC_SCHARGER_STATUS3_flash_bst_ovp_r_END      (1)
#define SOC_SCHARGER_STATUS3_flash_bst_scp_r_START    (2)
#define SOC_SCHARGER_STATUS3_flash_bst_scp_r_END      (2)
#define SOC_SCHARGER_STATUS3_flash_led_open_r_START   (4)
#define SOC_SCHARGER_STATUS3_flash_led_open_r_END     (4)
#define SOC_SCHARGER_STATUS3_flash_led_short_r_START  (5)
#define SOC_SCHARGER_STATUS3_flash_led_short_r_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUS4_UNION
 结构说明  : STATUS4 寄存器结构定义。地址偏移量:0x05，初值:0x00，宽度:8
 寄存器说明: 状态4寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_200ma_ocp_r : 1;  /* bit[0]: 0：ldo2_200ma 没有发生过流
                                                         1：ldo2_200ma 发生过流 */
        unsigned char  ldo1_200ma_ocp_r : 1;  /* bit[1]: 0：ldo1_200ma 没有发生过流
                                                         1：ldo1_200ma 发生过流 */
        unsigned char  lcd_ldo_ocp_r    : 1;  /* bit[2]: 0：lcd_ldo 没有发生过流
                                                         1：lcd_ldo 发生过流 */
        unsigned char  lcd_ncp_scp_r    : 1;  /* bit[3]: 0：lcd_ncp 没有发生短路
                                                         1：lcd_ncp 发生短路 */
        unsigned char  lcd_bst_uvp_r    : 1;  /* bit[4]: 0：lcd_bst 没有发生欠压
                                                         1：lcd_bst 发生欠压 */
        unsigned char  lcd_bst_ovp_r    : 1;  /* bit[5]: 0：lcd_bst 没有发生过压
                                                         1：lcd_bst 发生过压 */
        unsigned char  lcd_bst_scp_r    : 1;  /* bit[6]: 0：lcd_bst 没有发生短路
                                                         1：lcd_bst 发生短路 */
        unsigned char  lcd_bst_ocp_r    : 1;  /* bit[7]: 0：lcd_bst 没有发生过流
                                                         1：lcd_bst 发生过流 */
    } reg;
} SOC_SCHARGER_STATUS4_UNION;
#endif
#define SOC_SCHARGER_STATUS4_ldo2_200ma_ocp_r_START  (0)
#define SOC_SCHARGER_STATUS4_ldo2_200ma_ocp_r_END    (0)
#define SOC_SCHARGER_STATUS4_ldo1_200ma_ocp_r_START  (1)
#define SOC_SCHARGER_STATUS4_ldo1_200ma_ocp_r_END    (1)
#define SOC_SCHARGER_STATUS4_lcd_ldo_ocp_r_START     (2)
#define SOC_SCHARGER_STATUS4_lcd_ldo_ocp_r_END       (2)
#define SOC_SCHARGER_STATUS4_lcd_ncp_scp_r_START     (3)
#define SOC_SCHARGER_STATUS4_lcd_ncp_scp_r_END       (3)
#define SOC_SCHARGER_STATUS4_lcd_bst_uvp_r_START     (4)
#define SOC_SCHARGER_STATUS4_lcd_bst_uvp_r_END       (4)
#define SOC_SCHARGER_STATUS4_lcd_bst_ovp_r_START     (5)
#define SOC_SCHARGER_STATUS4_lcd_bst_ovp_r_END       (5)
#define SOC_SCHARGER_STATUS4_lcd_bst_scp_r_START     (6)
#define SOC_SCHARGER_STATUS4_lcd_bst_scp_r_END       (6)
#define SOC_SCHARGER_STATUS4_lcd_bst_ocp_r_START     (7)
#define SOC_SCHARGER_STATUS4_lcd_bst_ocp_r_END       (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUS5_UNION
 结构说明  : STATUS5 寄存器结构定义。地址偏移量:0x06，初值:0x00，宽度:8
 寄存器说明: 状态5寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_ovp_5p3v_r : 1;  /* bit[0]: 0:otg boost 没有发生过压5.3v
                                                       1:otg boost 发生过压5.3v */
        unsigned char  otg_uvp_r      : 1;  /* bit[1]: 0:otg boost 没有发生输出欠压
                                                       1:otg boost 发生输出欠压 */
        unsigned char  otg_ocp_r      : 1;  /* bit[2]: 0:otg 没有发生过流
                                                       1:otg 发生过流 */
        unsigned char  otg_scp_r      : 1;  /* bit[3]: 0:otg 没有发生短路
                                                       1:otg 发生短路 */
        unsigned char  bat_ltmp_r     : 1;  /* bit[4]: 0:电池没有发生低温过温
                                                       1:电池低温过温 */
        unsigned char  bat_htmp_r     : 1;  /* bit[5]: 0:电池没有发生高温过温
                                                       1:电池高温过温 */
        unsigned char  vbat_ovp_r     : 1;  /* bit[6]: 0:charger IC 电池没有发生过压
                                                       1:charger IC 电池发生过压 */
        unsigned char  otg_vbat_ok    : 1;  /* bit[7]: 0:VBAT电压过低
                                                       1：VBAT电压OK */
    } reg;
} SOC_SCHARGER_STATUS5_UNION;
#endif
#define SOC_SCHARGER_STATUS5_otg_ovp_5p3v_r_START  (0)
#define SOC_SCHARGER_STATUS5_otg_ovp_5p3v_r_END    (0)
#define SOC_SCHARGER_STATUS5_otg_uvp_r_START       (1)
#define SOC_SCHARGER_STATUS5_otg_uvp_r_END         (1)
#define SOC_SCHARGER_STATUS5_otg_ocp_r_START       (2)
#define SOC_SCHARGER_STATUS5_otg_ocp_r_END         (2)
#define SOC_SCHARGER_STATUS5_otg_scp_r_START       (3)
#define SOC_SCHARGER_STATUS5_otg_scp_r_END         (3)
#define SOC_SCHARGER_STATUS5_bat_ltmp_r_START      (4)
#define SOC_SCHARGER_STATUS5_bat_ltmp_r_END        (4)
#define SOC_SCHARGER_STATUS5_bat_htmp_r_START      (5)
#define SOC_SCHARGER_STATUS5_bat_htmp_r_END        (5)
#define SOC_SCHARGER_STATUS5_vbat_ovp_r_START      (6)
#define SOC_SCHARGER_STATUS5_vbat_ovp_r_END        (6)
#define SOC_SCHARGER_STATUS5_otg_vbat_ok_START     (7)
#define SOC_SCHARGER_STATUS5_otg_vbat_ok_END       (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ0_UNION
 结构说明  : IRQ0 寄存器结构定义。地址偏移量:0x07，初值:0x00，宽度:8
 寄存器说明: 中断0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otmp_150_r          : 1;  /* bit[0]: 0：温度没有超过150度
                                                            1：温度超过150度 */
        unsigned char  otmp_jstp_r         : 1;  /* bit[1]: 0：温度没超过thsd_tstp_set寄存器设置的温度
                                                            1:温度超过thsd_tstp_set寄存器设置的温度 */
        unsigned char  otmp_jreg_r         : 1;  /* bit[2]: 0：温度没超过thsd_treg_set寄存器设置的温度
                                                            1:温度超过thsd_treg_set寄存器设置的温度 */
        unsigned char  vbus_ovp_6p5v_r     : 1;  /* bit[3]: 0:vbus<6.5v
                                                            1:vbus>6.5v */
        unsigned char  vbus_uvp_3p5v_r     : 1;  /* bit[4]: 0:vbus>3.5v
                                                            1:vbus<3.5v */
        unsigned char  fast_chg_fault_r    : 1;  /* bit[5]: 电池快充电故障检测信号：（安全计时超时）
                                                            1：超时充未满故障
                                                            0：电池正常 */
        unsigned char  pre_chg_fault_r     : 1;  /* bit[6]: 弱电池充电故障检测信号：（VBAT低于2.8V/3.0V/3.1V/3.2V）
                                                            1：电池电压过低
                                                            0：电池正常 */
        unsigned char  trickle_chg_fault_r : 1;  /* bit[7]: 死电池充电故障检测信号：（VBAT低于2V）
                                                            1：电池电压过低
                                                            0：电池正常 */
    } reg;
} SOC_SCHARGER_IRQ0_UNION;
#endif
#define SOC_SCHARGER_IRQ0_otmp_150_r_START           (0)
#define SOC_SCHARGER_IRQ0_otmp_150_r_END             (0)
#define SOC_SCHARGER_IRQ0_otmp_jstp_r_START          (1)
#define SOC_SCHARGER_IRQ0_otmp_jstp_r_END            (1)
#define SOC_SCHARGER_IRQ0_otmp_jreg_r_START          (2)
#define SOC_SCHARGER_IRQ0_otmp_jreg_r_END            (2)
#define SOC_SCHARGER_IRQ0_vbus_ovp_6p5v_r_START      (3)
#define SOC_SCHARGER_IRQ0_vbus_ovp_6p5v_r_END        (3)
#define SOC_SCHARGER_IRQ0_vbus_uvp_3p5v_r_START      (4)
#define SOC_SCHARGER_IRQ0_vbus_uvp_3p5v_r_END        (4)
#define SOC_SCHARGER_IRQ0_fast_chg_fault_r_START     (5)
#define SOC_SCHARGER_IRQ0_fast_chg_fault_r_END       (5)
#define SOC_SCHARGER_IRQ0_pre_chg_fault_r_START      (6)
#define SOC_SCHARGER_IRQ0_pre_chg_fault_r_END        (6)
#define SOC_SCHARGER_IRQ0_trickle_chg_fault_r_START  (7)
#define SOC_SCHARGER_IRQ0_trickle_chg_fault_r_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ1_UNION
 结构说明  : IRQ1 寄存器结构定义。地址偏移量:0x08，初值:0x00，宽度:8
 寄存器说明: 中断1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_scp_r        : 1;  /* bit[0]: 0:wled 没有发生短路
                                                          1:wled 发生短路 */
        unsigned char  wled_ocp_r        : 1;  /* bit[1]: 0:wled 没有发生过流
                                                          1:wled 发生过流 */
        unsigned char  wled_uvp_r        : 1;  /* bit[2]: 0:wled boost没有发生输出欠压
                                                          1:wled boost发生输出欠压 */
        unsigned char  wled_ovp_4p5v_r   : 1;  /* bit[3]: 0:wled vifb没有发生过压4p5v
                                                          1:wled vifb 发生过压4p5v */
        unsigned char  wled_ovp_38v_r    : 1;  /* bit[4]: 0:wled vout没有发生过压38v
                                                          1:wled vout 发生过压38v */
        unsigned char  buck_scp_r        : 1;  /* bit[5]: 0:buck没有发生短路
                                                          1:buck发生短路 */
        unsigned char  chg_rechg_r       : 1;  /* bit[6]: 重新充电状态寄存器：
                                                          1：重新充电
                                                          0：无重新充电 */
        unsigned char  chg_charge_done_r : 1;  /* bit[7]: 0:充电状态记录寄存器中，没有 Charge Termination Done （充电终止）
                                                          1:充电状态记录寄存器中，发生 Charge Termination Done （充电终止） */
    } reg;
} SOC_SCHARGER_IRQ1_UNION;
#endif
#define SOC_SCHARGER_IRQ1_wled_scp_r_START         (0)
#define SOC_SCHARGER_IRQ1_wled_scp_r_END           (0)
#define SOC_SCHARGER_IRQ1_wled_ocp_r_START         (1)
#define SOC_SCHARGER_IRQ1_wled_ocp_r_END           (1)
#define SOC_SCHARGER_IRQ1_wled_uvp_r_START         (2)
#define SOC_SCHARGER_IRQ1_wled_uvp_r_END           (2)
#define SOC_SCHARGER_IRQ1_wled_ovp_4p5v_r_START    (3)
#define SOC_SCHARGER_IRQ1_wled_ovp_4p5v_r_END      (3)
#define SOC_SCHARGER_IRQ1_wled_ovp_38v_r_START     (4)
#define SOC_SCHARGER_IRQ1_wled_ovp_38v_r_END       (4)
#define SOC_SCHARGER_IRQ1_buck_scp_r_START         (5)
#define SOC_SCHARGER_IRQ1_buck_scp_r_END           (5)
#define SOC_SCHARGER_IRQ1_chg_rechg_r_START        (6)
#define SOC_SCHARGER_IRQ1_chg_rechg_r_END          (6)
#define SOC_SCHARGER_IRQ1_chg_charge_done_r_START  (7)
#define SOC_SCHARGER_IRQ1_chg_charge_done_r_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ2_UNION
 结构说明  : IRQ2 寄存器结构定义。地址偏移量:0x09，初值:0x00，宽度:8
 寄存器说明: 中断2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_uvp_r   : 1;  /* bit[0]  : 0：FLASH BOOST 没有发生欠压
                                                            1：FLASH BOOST 发生欠压 */
        unsigned char  flash_bst_ovp_r   : 1;  /* bit[1]  : 0：FLASH BOOST 没有发生过压
                                                            1：FLASH BOOST 发生过压 */
        unsigned char  flash_bst_scp_r   : 1;  /* bit[2]  : 0：FLASH BOOST 没有发生短路
                                                            1：FLASH BOOST 发生短路 */
        unsigned char  reserved_0        : 1;  /* bit[3]  : 保留，配置无用。 */
        unsigned char  flash_led_open_r  : 1;  /* bit[4]  : 0:LED灯没有开路
                                                            1:LED灯开路 */
        unsigned char  flash_led_short_r : 1;  /* bit[5]  : 0：LED灯没有短路
                                                            1：LED灯短路 */
        unsigned char  reserved_1        : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_IRQ2_UNION;
#endif
#define SOC_SCHARGER_IRQ2_flash_bst_uvp_r_START    (0)
#define SOC_SCHARGER_IRQ2_flash_bst_uvp_r_END      (0)
#define SOC_SCHARGER_IRQ2_flash_bst_ovp_r_START    (1)
#define SOC_SCHARGER_IRQ2_flash_bst_ovp_r_END      (1)
#define SOC_SCHARGER_IRQ2_flash_bst_scp_r_START    (2)
#define SOC_SCHARGER_IRQ2_flash_bst_scp_r_END      (2)
#define SOC_SCHARGER_IRQ2_flash_led_open_r_START   (4)
#define SOC_SCHARGER_IRQ2_flash_led_open_r_END     (4)
#define SOC_SCHARGER_IRQ2_flash_led_short_r_START  (5)
#define SOC_SCHARGER_IRQ2_flash_led_short_r_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ3_UNION
 结构说明  : IRQ3 寄存器结构定义。地址偏移量:0x0A，初值:0x00，宽度:8
 寄存器说明: 中断3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_200ma_ocp_r : 1;  /* bit[0]: 0：ldo2_200ma 没有发生过流
                                                         1：ldo2_200ma 发生过流 */
        unsigned char  ldo1_200ma_ocp_r : 1;  /* bit[1]: 0：ldo1_200ma 没有发生过流
                                                         1：ldo1_200ma 发生过流 */
        unsigned char  lcd_ldo_ocp_r    : 1;  /* bit[2]: 0：lcd_ldo 没有发生过流
                                                         1：lcd_ldo 发生过流 */
        unsigned char  lcd_ncp_scp_r    : 1;  /* bit[3]: 0：lcd_ncp 没有发生短路
                                                         1：lcd_ncp 发生短路 */
        unsigned char  lcd_bst_uvp_r    : 1;  /* bit[4]: 0：lcd_bst 没有发生欠压
                                                         1：lcd_bst 发生欠压 */
        unsigned char  lcd_bst_ovp_r    : 1;  /* bit[5]: 0：lcd_bst 没有发生过压
                                                         1：lcd_bst 发生过压 */
        unsigned char  lcd_bst_scp_r    : 1;  /* bit[6]: 0：lcd_bst 没有发生短路
                                                         1：lcd_bst 发生短路 */
        unsigned char  lcd_bst_ocp_r    : 1;  /* bit[7]: 0：lcd_bst 没有发生过流
                                                         1：lcd_bst 发生过流 */
    } reg;
} SOC_SCHARGER_IRQ3_UNION;
#endif
#define SOC_SCHARGER_IRQ3_ldo2_200ma_ocp_r_START  (0)
#define SOC_SCHARGER_IRQ3_ldo2_200ma_ocp_r_END    (0)
#define SOC_SCHARGER_IRQ3_ldo1_200ma_ocp_r_START  (1)
#define SOC_SCHARGER_IRQ3_ldo1_200ma_ocp_r_END    (1)
#define SOC_SCHARGER_IRQ3_lcd_ldo_ocp_r_START     (2)
#define SOC_SCHARGER_IRQ3_lcd_ldo_ocp_r_END       (2)
#define SOC_SCHARGER_IRQ3_lcd_ncp_scp_r_START     (3)
#define SOC_SCHARGER_IRQ3_lcd_ncp_scp_r_END       (3)
#define SOC_SCHARGER_IRQ3_lcd_bst_uvp_r_START     (4)
#define SOC_SCHARGER_IRQ3_lcd_bst_uvp_r_END       (4)
#define SOC_SCHARGER_IRQ3_lcd_bst_ovp_r_START     (5)
#define SOC_SCHARGER_IRQ3_lcd_bst_ovp_r_END       (5)
#define SOC_SCHARGER_IRQ3_lcd_bst_scp_r_START     (6)
#define SOC_SCHARGER_IRQ3_lcd_bst_scp_r_END       (6)
#define SOC_SCHARGER_IRQ3_lcd_bst_ocp_r_START     (7)
#define SOC_SCHARGER_IRQ3_lcd_bst_ocp_r_END       (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ4_UNION
 结构说明  : IRQ4 寄存器结构定义。地址偏移量:0x0B，初值:0x00，宽度:8
 寄存器说明: 中断4寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_ovp_5p3v_r : 1;  /* bit[0]: 0:otg boost 没有发生过压5.3v
                                                       1:otg boost 发生过压5.3v */
        unsigned char  otg_uvp_r      : 1;  /* bit[1]: 0:otg boost 没有发生输出欠压
                                                       1:otg boost 发生输出欠压 */
        unsigned char  otg_ocp_r      : 1;  /* bit[2]: 0:otg 没有发生过流
                                                       1:otg 发生过流 */
        unsigned char  otg_scp_r      : 1;  /* bit[3]: 0:otg 没有发生短路
                                                       1:otg 发生短路 */
        unsigned char  bat_ltmp_r     : 1;  /* bit[4]: 0:电池没有发生低温过温
                                                       1:电池低温过温 */
        unsigned char  bat_htmp_r     : 1;  /* bit[5]: 0:电池没有发生高温过温
                                                       1:电池高温过温 */
        unsigned char  vbat_ovp_r     : 1;  /* bit[6]: 0:charger IC 电池没有发生过压
                                                       1:charger IC 电池发生过压 */
        unsigned char  otg_vbat_ok_f  : 1;  /* bit[7]: 0：VBAT电压OK
                                                       1：VBAT电压过低 */
    } reg;
} SOC_SCHARGER_IRQ4_UNION;
#endif
#define SOC_SCHARGER_IRQ4_otg_ovp_5p3v_r_START  (0)
#define SOC_SCHARGER_IRQ4_otg_ovp_5p3v_r_END    (0)
#define SOC_SCHARGER_IRQ4_otg_uvp_r_START       (1)
#define SOC_SCHARGER_IRQ4_otg_uvp_r_END         (1)
#define SOC_SCHARGER_IRQ4_otg_ocp_r_START       (2)
#define SOC_SCHARGER_IRQ4_otg_ocp_r_END         (2)
#define SOC_SCHARGER_IRQ4_otg_scp_r_START       (3)
#define SOC_SCHARGER_IRQ4_otg_scp_r_END         (3)
#define SOC_SCHARGER_IRQ4_bat_ltmp_r_START      (4)
#define SOC_SCHARGER_IRQ4_bat_ltmp_r_END        (4)
#define SOC_SCHARGER_IRQ4_bat_htmp_r_START      (5)
#define SOC_SCHARGER_IRQ4_bat_htmp_r_END        (5)
#define SOC_SCHARGER_IRQ4_vbat_ovp_r_START      (6)
#define SOC_SCHARGER_IRQ4_vbat_ovp_r_END        (6)
#define SOC_SCHARGER_IRQ4_otg_vbat_ok_f_START   (7)
#define SOC_SCHARGER_IRQ4_otg_vbat_ok_f_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQM0_UNION
 结构说明  : IRQM0 寄存器结构定义。地址偏移量:0x0C，初值:0x00，宽度:8
 寄存器说明: 中断屏蔽0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otmp_150_rm          : 1;  /* bit[0]: 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  otmp_jstp_rm         : 1;  /* bit[1]: 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  otmp_jreg_rm         : 1;  /* bit[2]: 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  vbus_ovp_6p5v_rm     : 1;  /* bit[3]: 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  vbus_uvp_3p5v_rm     : 1;  /* bit[4]: 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  fast_chg_fault_rm    : 1;  /* bit[5]: 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  pre_chg_fault_rm     : 1;  /* bit[6]: 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  trickle_chg_fault_rm : 1;  /* bit[7]: 0:使能该中断；
                                                             1:屏蔽该中断； */
    } reg;
} SOC_SCHARGER_IRQM0_UNION;
#endif
#define SOC_SCHARGER_IRQM0_otmp_150_rm_START           (0)
#define SOC_SCHARGER_IRQM0_otmp_150_rm_END             (0)
#define SOC_SCHARGER_IRQM0_otmp_jstp_rm_START          (1)
#define SOC_SCHARGER_IRQM0_otmp_jstp_rm_END            (1)
#define SOC_SCHARGER_IRQM0_otmp_jreg_rm_START          (2)
#define SOC_SCHARGER_IRQM0_otmp_jreg_rm_END            (2)
#define SOC_SCHARGER_IRQM0_vbus_ovp_6p5v_rm_START      (3)
#define SOC_SCHARGER_IRQM0_vbus_ovp_6p5v_rm_END        (3)
#define SOC_SCHARGER_IRQM0_vbus_uvp_3p5v_rm_START      (4)
#define SOC_SCHARGER_IRQM0_vbus_uvp_3p5v_rm_END        (4)
#define SOC_SCHARGER_IRQM0_fast_chg_fault_rm_START     (5)
#define SOC_SCHARGER_IRQM0_fast_chg_fault_rm_END       (5)
#define SOC_SCHARGER_IRQM0_pre_chg_fault_rm_START      (6)
#define SOC_SCHARGER_IRQM0_pre_chg_fault_rm_END        (6)
#define SOC_SCHARGER_IRQM0_trickle_chg_fault_rm_START  (7)
#define SOC_SCHARGER_IRQM0_trickle_chg_fault_rm_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQM1_UNION
 结构说明  : IRQM1 寄存器结构定义。地址偏移量:0x0D，初值:0x00，宽度:8
 寄存器说明: 中断屏蔽1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_scp_rm        : 1;  /* bit[0]: 0:使能该中断；
                                                           1:屏蔽该中断； */
        unsigned char  wled_ocp_rm        : 1;  /* bit[1]: 0:使能该中断；
                                                           1:屏蔽该中断； */
        unsigned char  wled_uvp_rm        : 1;  /* bit[2]: 0:使能该中断；
                                                           1:屏蔽该中断； */
        unsigned char  wled_ovp_4p5v_rm   : 1;  /* bit[3]: 0:使能该中断；
                                                           1:屏蔽该中断； */
        unsigned char  wled_ovp_38v_rm    : 1;  /* bit[4]: 0:使能该中断；
                                                           1:屏蔽该中断； */
        unsigned char  buck_scp_rm        : 1;  /* bit[5]: 0:使能该中断；
                                                           1:屏蔽该中断； */
        unsigned char  chg_rechg_rm       : 1;  /* bit[6]: 0:使能该中断；
                                                           1:屏蔽该中断； */
        unsigned char  chg_charge_done_rm : 1;  /* bit[7]: 0:使能该中断；
                                                           1:屏蔽该中断； */
    } reg;
} SOC_SCHARGER_IRQM1_UNION;
#endif
#define SOC_SCHARGER_IRQM1_wled_scp_rm_START         (0)
#define SOC_SCHARGER_IRQM1_wled_scp_rm_END           (0)
#define SOC_SCHARGER_IRQM1_wled_ocp_rm_START         (1)
#define SOC_SCHARGER_IRQM1_wled_ocp_rm_END           (1)
#define SOC_SCHARGER_IRQM1_wled_uvp_rm_START         (2)
#define SOC_SCHARGER_IRQM1_wled_uvp_rm_END           (2)
#define SOC_SCHARGER_IRQM1_wled_ovp_4p5v_rm_START    (3)
#define SOC_SCHARGER_IRQM1_wled_ovp_4p5v_rm_END      (3)
#define SOC_SCHARGER_IRQM1_wled_ovp_38v_rm_START     (4)
#define SOC_SCHARGER_IRQM1_wled_ovp_38v_rm_END       (4)
#define SOC_SCHARGER_IRQM1_buck_scp_rm_START         (5)
#define SOC_SCHARGER_IRQM1_buck_scp_rm_END           (5)
#define SOC_SCHARGER_IRQM1_chg_rechg_rm_START        (6)
#define SOC_SCHARGER_IRQM1_chg_rechg_rm_END          (6)
#define SOC_SCHARGER_IRQM1_chg_charge_done_rm_START  (7)
#define SOC_SCHARGER_IRQM1_chg_charge_done_rm_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQM2_UNION
 结构说明  : IRQM2 寄存器结构定义。地址偏移量:0x0E，初值:0x00，宽度:8
 寄存器说明: 中断屏蔽2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_uvp_rm   : 1;  /* bit[0]  : 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  flash_bst_ovp_rm   : 1;  /* bit[1]  : 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  flash_bst_scp_rm   : 1;  /* bit[2]  : 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  reserved_0         : 1;  /* bit[3]  : 保留，配置无用。 */
        unsigned char  flash_led_open_rm  : 1;  /* bit[4]  : 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  flash_led_short_rm : 1;  /* bit[5]  : 0:使能该中断；
                                                             1:屏蔽该中断； */
        unsigned char  reserved_1         : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_IRQM2_UNION;
#endif
#define SOC_SCHARGER_IRQM2_flash_bst_uvp_rm_START    (0)
#define SOC_SCHARGER_IRQM2_flash_bst_uvp_rm_END      (0)
#define SOC_SCHARGER_IRQM2_flash_bst_ovp_rm_START    (1)
#define SOC_SCHARGER_IRQM2_flash_bst_ovp_rm_END      (1)
#define SOC_SCHARGER_IRQM2_flash_bst_scp_rm_START    (2)
#define SOC_SCHARGER_IRQM2_flash_bst_scp_rm_END      (2)
#define SOC_SCHARGER_IRQM2_flash_led_open_rm_START   (4)
#define SOC_SCHARGER_IRQM2_flash_led_open_rm_END     (4)
#define SOC_SCHARGER_IRQM2_flash_led_short_rm_START  (5)
#define SOC_SCHARGER_IRQM2_flash_led_short_rm_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQM3_UNION
 结构说明  : IRQM3 寄存器结构定义。地址偏移量:0x0F，初值:0x00，宽度:8
 寄存器说明: 中断屏蔽3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_200ma_ocp_rm : 1;  /* bit[0]: 0:使能该中断；
                                                          1:屏蔽该中断； */
        unsigned char  ldo1_200ma_ocp_rm : 1;  /* bit[1]: 0:使能该中断；
                                                          1:屏蔽该中断； */
        unsigned char  lcd_ldo_ocp_rm    : 1;  /* bit[2]: 0:使能该中断；
                                                          1:屏蔽该中断； */
        unsigned char  lcd_ncp_scp_rm    : 1;  /* bit[3]: 0:使能该中断；
                                                          1:屏蔽该中断； */
        unsigned char  lcd_bst_uvp_rm    : 1;  /* bit[4]: 0:使能该中断；
                                                          1:屏蔽该中断； */
        unsigned char  lcd_bst_ovp_rm    : 1;  /* bit[5]: 0:使能该中断；
                                                          1:屏蔽该中断； */
        unsigned char  lcd_bst_scp_rm    : 1;  /* bit[6]: 0:使能该中断；
                                                          1:屏蔽该中断； */
        unsigned char  lcd_bst_ocp_rm    : 1;  /* bit[7]: 0:使能该中断；
                                                          1:屏蔽该中断； */
    } reg;
} SOC_SCHARGER_IRQM3_UNION;
#endif
#define SOC_SCHARGER_IRQM3_ldo2_200ma_ocp_rm_START  (0)
#define SOC_SCHARGER_IRQM3_ldo2_200ma_ocp_rm_END    (0)
#define SOC_SCHARGER_IRQM3_ldo1_200ma_ocp_rm_START  (1)
#define SOC_SCHARGER_IRQM3_ldo1_200ma_ocp_rm_END    (1)
#define SOC_SCHARGER_IRQM3_lcd_ldo_ocp_rm_START     (2)
#define SOC_SCHARGER_IRQM3_lcd_ldo_ocp_rm_END       (2)
#define SOC_SCHARGER_IRQM3_lcd_ncp_scp_rm_START     (3)
#define SOC_SCHARGER_IRQM3_lcd_ncp_scp_rm_END       (3)
#define SOC_SCHARGER_IRQM3_lcd_bst_uvp_rm_START     (4)
#define SOC_SCHARGER_IRQM3_lcd_bst_uvp_rm_END       (4)
#define SOC_SCHARGER_IRQM3_lcd_bst_ovp_rm_START     (5)
#define SOC_SCHARGER_IRQM3_lcd_bst_ovp_rm_END       (5)
#define SOC_SCHARGER_IRQM3_lcd_bst_scp_rm_START     (6)
#define SOC_SCHARGER_IRQM3_lcd_bst_scp_rm_END       (6)
#define SOC_SCHARGER_IRQM3_lcd_bst_ocp_rm_START     (7)
#define SOC_SCHARGER_IRQM3_lcd_bst_ocp_rm_END       (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQM4_UNION
 结构说明  : IRQM4 寄存器结构定义。地址偏移量:0x10，初值:0x00，宽度:8
 寄存器说明: 中断屏蔽4寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_ovp_5p3v_rm : 1;  /* bit[0]: 0:使能该中断；
                                                        1:屏蔽该中断； */
        unsigned char  otg_uvp_rm      : 1;  /* bit[1]: 0:使能该中断；
                                                        1:屏蔽该中断； */
        unsigned char  otg_ocp_rm      : 1;  /* bit[2]: 0:使能该中断；
                                                        1:屏蔽该中断； */
        unsigned char  otg_scp_rm      : 1;  /* bit[3]: 0:使能该中断；
                                                        1:屏蔽该中断； */
        unsigned char  bat_ltmp_rm     : 1;  /* bit[4]: 0:使能该中断；
                                                        1:屏蔽该中断； */
        unsigned char  bat_htmp_rm     : 1;  /* bit[5]: 0:使能该中断；
                                                        1:屏蔽该中断； */
        unsigned char  vbat_ovp_rm     : 1;  /* bit[6]: 0:使能该中断；
                                                        1:屏蔽该中断； */
        unsigned char  otg_vbat_ok_fm  : 1;  /* bit[7]: 0：使能该中断；
                                                        1：屏蔽该中断； */
    } reg;
} SOC_SCHARGER_IRQM4_UNION;
#endif
#define SOC_SCHARGER_IRQM4_otg_ovp_5p3v_rm_START  (0)
#define SOC_SCHARGER_IRQM4_otg_ovp_5p3v_rm_END    (0)
#define SOC_SCHARGER_IRQM4_otg_uvp_rm_START       (1)
#define SOC_SCHARGER_IRQM4_otg_uvp_rm_END         (1)
#define SOC_SCHARGER_IRQM4_otg_ocp_rm_START       (2)
#define SOC_SCHARGER_IRQM4_otg_ocp_rm_END         (2)
#define SOC_SCHARGER_IRQM4_otg_scp_rm_START       (3)
#define SOC_SCHARGER_IRQM4_otg_scp_rm_END         (3)
#define SOC_SCHARGER_IRQM4_bat_ltmp_rm_START      (4)
#define SOC_SCHARGER_IRQM4_bat_ltmp_rm_END        (4)
#define SOC_SCHARGER_IRQM4_bat_htmp_rm_START      (5)
#define SOC_SCHARGER_IRQM4_bat_htmp_rm_END        (5)
#define SOC_SCHARGER_IRQM4_vbat_ovp_rm_START      (6)
#define SOC_SCHARGER_IRQM4_vbat_ovp_rm_END        (6)
#define SOC_SCHARGER_IRQM4_otg_vbat_ok_fm_START   (7)
#define SOC_SCHARGER_IRQM4_otg_vbat_ok_fm_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ONFF0_UNION
 结构说明  : ONFF0 寄存器结构定义。地址偏移量:0x11，初值:0x00，宽度:8
 寄存器说明: 开关控制0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_ncp_en_int     : 1;  /* bit[0]  : 0:关闭lcd_ncp
                                                             1:开启lcd_ncp */
        unsigned char  lcd_ldo_en_int     : 1;  /* bit[1]  : 0:关闭lcd_ldo
                                                             1:开启lcd_ldo */
        unsigned char  lcd_bst_en_int     : 1;  /* bit[2]  : 0:关闭lcd boost
                                                             1:开启lcd boost */
        unsigned char  flash_bst_en_int   : 1;  /* bit[3]  : 0:关闭flash boost
                                                             1:开启flash boost */
        unsigned char  flash_led_flash_en : 1;  /* bit[4]  : 0:关闭flash_led的flash模式
                                                             1:开启flash_led的flash模式 */
        unsigned char  flash_led_torch_en : 1;  /* bit[5]  : 0:关闭flash_led的torch模式
                                                             1:开启flash_led的torch模式 */
        unsigned char  reserved           : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_ONFF0_UNION;
#endif
#define SOC_SCHARGER_ONFF0_lcd_ncp_en_int_START      (0)
#define SOC_SCHARGER_ONFF0_lcd_ncp_en_int_END        (0)
#define SOC_SCHARGER_ONFF0_lcd_ldo_en_int_START      (1)
#define SOC_SCHARGER_ONFF0_lcd_ldo_en_int_END        (1)
#define SOC_SCHARGER_ONFF0_lcd_bst_en_int_START      (2)
#define SOC_SCHARGER_ONFF0_lcd_bst_en_int_END        (2)
#define SOC_SCHARGER_ONFF0_flash_bst_en_int_START    (3)
#define SOC_SCHARGER_ONFF0_flash_bst_en_int_END      (3)
#define SOC_SCHARGER_ONFF0_flash_led_flash_en_START  (4)
#define SOC_SCHARGER_ONFF0_flash_led_flash_en_END    (4)
#define SOC_SCHARGER_ONFF0_flash_led_torch_en_START  (5)
#define SOC_SCHARGER_ONFF0_flash_led_torch_en_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ONFF1_UNION
 结构说明  : ONFF1 寄存器结构定义。地址偏移量:0x12，初值:0x00，宽度:8
 寄存器说明: 开关控制1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_200ma_en_int : 1;  /* bit[0]  : 0:关闭ldo2_200ma(注：该寄存器仅受上电POR复位信号复位,不受软复位信号soft_rst_n和外部硬线RESET复位的控制)
                                                            1:开启ldo2_200ma */
        unsigned char  ldo1_200ma_en_int : 1;  /* bit[1]  : 0:关闭ldo1_200ma
                                                            1:开启ldo1_200ma */
        unsigned char  wled_en_int       : 1;  /* bit[2]  : 0:关闭wled
                                                            1:开启wled */
        unsigned char  otg_en_int        : 1;  /* bit[3]  : 0:关闭otg
                                                            1:开启otg  */
        unsigned char  chg_en_int        : 1;  /* bit[4]  : 0:关闭charge
                                                            1:开启charge  */
        unsigned char  reserved          : 3;  /* bit[5-7]: 保留 */
    } reg;
} SOC_SCHARGER_ONFF1_UNION;
#endif
#define SOC_SCHARGER_ONFF1_ldo2_200ma_en_int_START  (0)
#define SOC_SCHARGER_ONFF1_ldo2_200ma_en_int_END    (0)
#define SOC_SCHARGER_ONFF1_ldo1_200ma_en_int_START  (1)
#define SOC_SCHARGER_ONFF1_ldo1_200ma_en_int_END    (1)
#define SOC_SCHARGER_ONFF1_wled_en_int_START        (2)
#define SOC_SCHARGER_ONFF1_wled_en_int_END          (2)
#define SOC_SCHARGER_ONFF1_otg_en_int_START         (3)
#define SOC_SCHARGER_ONFF1_otg_en_int_END           (3)
#define SOC_SCHARGER_ONFF1_chg_en_int_START         (4)
#define SOC_SCHARGER_ONFF1_chg_en_int_END           (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_REF_REG_UNION
 结构说明  : REF_REG 寄存器结构定义。地址偏移量:0x13，初值:0x04，宽度:8
 寄存器说明: 温度报警寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  thsd_tstp_set : 1;  /* bit[0]  : 温度保护模块报警温度设置。
                                                        0：120℃；
                                                        1：140℃；
                                                        默认设置为120℃。 */
        unsigned char  thsd_treg_set : 2;  /* bit[1-2]: 温度保护模块报警温度设置。
                                                        00：60℃；
                                                        01：80℃；
                                                        10：100℃；
                                                        11：120℃；
                                                        默认设置为100℃。 */
        unsigned char  reserved      : 5;  /* bit[3-7]: 保留 */
    } reg;
} SOC_SCHARGER_REF_REG_UNION;
#endif
#define SOC_SCHARGER_REF_REG_thsd_tstp_set_START  (0)
#define SOC_SCHARGER_REF_REG_thsd_tstp_set_END    (0)
#define SOC_SCHARGER_REF_REG_thsd_treg_set_START  (1)
#define SOC_SCHARGER_REF_REG_thsd_treg_set_END    (2)


/*****************************************************************************
 结构名    : SOC_SCHARGER_VBAT_OV_SEL_UNION
 结构说明  : VBAT_OV_SEL 寄存器结构定义。地址偏移量:0x14，初值:0x01，宽度:8
 寄存器说明: 电池过压点选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vbat_ov_sel : 1;  /* bit[0]  : 电池过压点选择：
                                                      1：电池过压点为1.04*VBAT
                                                      0:电池过压点为1.06*VBAT */
        unsigned char  reserved    : 7;  /* bit[1-7]: 保留 */
    } reg;
} SOC_SCHARGER_VBAT_OV_SEL_UNION;
#endif
#define SOC_SCHARGER_VBAT_OV_SEL_vbat_ov_sel_START  (0)
#define SOC_SCHARGER_VBAT_OV_SEL_vbat_ov_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG0_UNION
 结构说明  : WLED_REG0 寄存器结构定义。地址偏移量:0x15，初值:0x7D，宽度:8
 寄存器说明: WLED_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_bst_ovp_en  : 1;  /* bit[0]  : boost ovp使能：
                                                           1: 使能
                                                           0: 关闭 */
        unsigned char  wled_bst_en_pfm  : 1;  /* bit[1]  : boost pfm使能： 
                                                           0: 关闭pfm
                                                           1: 使能pfm */
        unsigned char  wled_bst_en_clp  : 1;  /* bit[2]  : boost EA钳位电路（高低一起）使能：
                                                           0: 关闭钳位电路
                                                           1: 使能钳位电路 */
        unsigned char  wled_bst_slop    : 1;  /* bit[3]  : boost 斜坡补偿使能：
                                                           0: 关闭斜坡补偿
                                                           1: 使能斜坡补偿 */
        unsigned char  wled_bst_ocp_en  : 1;  /* bit[4]  : boost ocp使能：
                                                           0: 关闭
                                                           1: 使能 */
        unsigned char  wled_bst_scp     : 1;  /* bit[5]  : boost scp动作选择：
                                                           0: 短路后系统不自动关闭（仍上报）
                                                           1: 短路后系统自动关闭 */
        unsigned char  wled_ifb_uvp_sel : 2;  /* bit[6-7]: ifb端的uvp检测档位选择
                                                           00: 
                                                           01: 
                                                           10:
                                                           11:  */
    } reg;
} SOC_SCHARGER_WLED_REG0_UNION;
#endif
#define SOC_SCHARGER_WLED_REG0_wled_bst_ovp_en_START   (0)
#define SOC_SCHARGER_WLED_REG0_wled_bst_ovp_en_END     (0)
#define SOC_SCHARGER_WLED_REG0_wled_bst_en_pfm_START   (1)
#define SOC_SCHARGER_WLED_REG0_wled_bst_en_pfm_END     (1)
#define SOC_SCHARGER_WLED_REG0_wled_bst_en_clp_START   (2)
#define SOC_SCHARGER_WLED_REG0_wled_bst_en_clp_END     (2)
#define SOC_SCHARGER_WLED_REG0_wled_bst_slop_START     (3)
#define SOC_SCHARGER_WLED_REG0_wled_bst_slop_END       (3)
#define SOC_SCHARGER_WLED_REG0_wled_bst_ocp_en_START   (4)
#define SOC_SCHARGER_WLED_REG0_wled_bst_ocp_en_END     (4)
#define SOC_SCHARGER_WLED_REG0_wled_bst_scp_START      (5)
#define SOC_SCHARGER_WLED_REG0_wled_bst_scp_END        (5)
#define SOC_SCHARGER_WLED_REG0_wled_ifb_uvp_sel_START  (6)
#define SOC_SCHARGER_WLED_REG0_wled_ifb_uvp_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG1_UNION
 结构说明  : WLED_REG1 寄存器结构定义。地址偏移量:0x16，初值:0xD9，宽度:8
 寄存器说明: WLED_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_bst_clp_l    : 2;  /* bit[0-1]: boost EA输出钳位值和VRAMP直流电平值的失调
                                                            00: 1.4V
                                                            01: 1.6V
                                                            10: 1.8V
                                                            11: 2V */
        unsigned char  wled_bst_gm       : 3;  /* bit[2-4]: boost EA中gm电阻设定(gm=2/R)
                                                            000: 90kΩ
                                                            001: 80kΩ
                                                            010: 70kΩ
                                                            011: 60kΩ
                                                            100: 40kΩ
                                                            101: 30kΩ
                                                            110: 20kΩ
                                                            111: 10kΩ */
        unsigned char  wled_bst_lmos_ocp : 2;  /* bit[5-6]: boost 低端MOS管限流值(A)
                                                            00: 
                                                            01: 
                                                            10: 
                                                            11:  */
        unsigned char  wled_bst_ocp      : 1;  /* bit[7]  : boost OCP动作选择：
                                                            1: 过流后自动关闭boost
                                                            0: 过流后不自动关闭boost */
    } reg;
} SOC_SCHARGER_WLED_REG1_UNION;
#endif
#define SOC_SCHARGER_WLED_REG1_wled_bst_clp_l_START     (0)
#define SOC_SCHARGER_WLED_REG1_wled_bst_clp_l_END       (1)
#define SOC_SCHARGER_WLED_REG1_wled_bst_gm_START        (2)
#define SOC_SCHARGER_WLED_REG1_wled_bst_gm_END          (4)
#define SOC_SCHARGER_WLED_REG1_wled_bst_lmos_ocp_START  (5)
#define SOC_SCHARGER_WLED_REG1_wled_bst_lmos_ocp_END    (6)
#define SOC_SCHARGER_WLED_REG1_wled_bst_ocp_START       (7)
#define SOC_SCHARGER_WLED_REG1_wled_bst_ocp_END         (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG2_UNION
 结构说明  : WLED_REG2 寄存器结构定义。地址偏移量:0x17，初值:0x6A，宽度:8
 寄存器说明: WLED_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_bst_drv     : 6;  /* bit[0-5]: boost 下管驱动强度：
                                                           00: 10ns
                                                           01: 20ns
                                                           10: 30ns
                                                           11: 40ns */
        unsigned char  wled_bst_scp_sel : 2;  /* bit[6-7]: boost scp的检测档位选择
                                                           00：
                                                           01：
                                                           10：
                                                           11： */
    } reg;
} SOC_SCHARGER_WLED_REG2_UNION;
#endif
#define SOC_SCHARGER_WLED_REG2_wled_bst_drv_START      (0)
#define SOC_SCHARGER_WLED_REG2_wled_bst_drv_END        (5)
#define SOC_SCHARGER_WLED_REG2_wled_bst_scp_sel_START  (6)
#define SOC_SCHARGER_WLED_REG2_wled_bst_scp_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG3_UNION
 结构说明  : WLED_REG3 寄存器结构定义。地址偏移量:0x18，初值:0x9A，宽度:8
 寄存器说明: WLED_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_bst_osc : 8;  /* bit[0-7]: 开关频率（MHz）和斜坡量 */
    } reg;
} SOC_SCHARGER_WLED_REG3_UNION;
#endif
#define SOC_SCHARGER_WLED_REG3_wled_bst_osc_START  (0)
#define SOC_SCHARGER_WLED_REG3_wled_bst_osc_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG4_UNION
 结构说明  : WLED_REG4 寄存器结构定义。地址偏移量:0x19，初值:0x9F，宽度:8
 寄存器说明: WLED_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_ifb_prot_en : 4;  /* bit[0-3]: IFB的ovp和uvp检测的使能
                                                           wled_ifb_prot_en<0>：uvp使能
                                                           wled_ifb_prot_en<1>：ovp的低电压使能
                                                           wled_ifb_prot_en<2>：ovp的中电压使能
                                                           wled_ifb_prot_en<3>：ovp的高电压使能 */
        unsigned char  wled_bst_rf      : 2;  /* bit[4-5]: 电感电流转电压阻抗
                                                           00: 12.5kΩ）
                                                           01: 10kΩ）
                                                           10: 7.5kΩ）
                                                           11: 5kΩ） */
        unsigned char  wled_bst_ckmin   : 2;  /* bit[6-7]: NMOS最小导通时间
                                                           00: 160ns
                                                           01: 120ns
                                                           10: 80ns
                                                           11: 40ns */
    } reg;
} SOC_SCHARGER_WLED_REG4_UNION;
#endif
#define SOC_SCHARGER_WLED_REG4_wled_ifb_prot_en_START  (0)
#define SOC_SCHARGER_WLED_REG4_wled_ifb_prot_en_END    (3)
#define SOC_SCHARGER_WLED_REG4_wled_bst_rf_START       (4)
#define SOC_SCHARGER_WLED_REG4_wled_bst_rf_END         (5)
#define SOC_SCHARGER_WLED_REG4_wled_bst_ckmin_START    (6)
#define SOC_SCHARGER_WLED_REG4_wled_bst_ckmin_END      (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG5_UNION
 结构说明  : WLED_REG5 寄存器结构定义。地址偏移量:0x1A，初值:0x83，宽度:8
 寄存器说明: WLED_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_resv1 : 8;  /* bit[0-7]: wled_resv1<1:0>为wled_driver的en控制寄存器，若某路ifb不用，需要将该路的en信号置低。
                                                     wled_resv1<0>对应ifb1；wled_resv1<1>对应ifb2.
                                                     00：两路ifb1和ifb2都关闭。
                                                     01：ifb2关闭，ifb1开启
                                                     10：ifb2开启，ifb1关闭
                                                     11：两路都开启
                                                     wled_resv1<5:2>为current sense的档位选择 
                                                     wled_resv1<6>为osc_comp控制
                                                     wled_resv1<7>为boost 的scp的使能 */
    } reg;
} SOC_SCHARGER_WLED_REG5_UNION;
#endif
#define SOC_SCHARGER_WLED_REG5_wled_resv1_START  (0)
#define SOC_SCHARGER_WLED_REG5_wled_resv1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG6_UNION
 结构说明  : WLED_REG6 寄存器结构定义。地址偏移量:0x1B，初值:0x2B，宽度:8
 寄存器说明: WLED_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_resv2 : 8;  /* bit[0-7]: wled_resv2<3:0>为ICS的trim档位 wled_resv2<5:4>为IFB_OVPH的档位调节 */
    } reg;
} SOC_SCHARGER_WLED_REG6_UNION;
#endif
#define SOC_SCHARGER_WLED_REG6_wled_resv2_START  (0)
#define SOC_SCHARGER_WLED_REG6_wled_resv2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG7_UNION
 结构说明  : WLED_REG7 寄存器结构定义。地址偏移量:0x1C，初值:0x6C，宽度:8
 寄存器说明: WLED_REG7调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_resv3 : 8;  /* bit[0-7]: wled_resv3<7:0>为斜坡补偿的调节 */
    } reg;
} SOC_SCHARGER_WLED_REG7_UNION;
#endif
#define SOC_SCHARGER_WLED_REG7_wled_resv3_START  (0)
#define SOC_SCHARGER_WLED_REG7_wled_resv3_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG8_UNION
 结构说明  : WLED_REG8 寄存器结构定义。地址偏移量:0x1D，初值:0x6D，宽度:8
 寄存器说明: WLED_REG8调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_resv4 : 8;  /* bit[0-7]: wled_resv4<0>为IFB的UVP关闭屏蔽位，0为屏蔽；
                                                     wled_resv4<2>为boost的ovp关闭屏蔽位，0为屏蔽
                                                     wled_resv4<3>为boost的ovp去抖的屏蔽位，0为屏蔽；
                                                     wled_resv4<4>为IFB的ovp去抖时间调节位
                                                     wled_resv4<5>为IFB_OVP_LG的屏蔽位,0为屏蔽；
                                                     wled_resv4<6>为IFB的OVP去抖时间屏蔽位，0为屏蔽；
                                                     wled_resv4<7>为boost的ovp去抖时间调节位 */
    } reg;
} SOC_SCHARGER_WLED_REG8_UNION;
#endif
#define SOC_SCHARGER_WLED_REG8_wled_resv4_START  (0)
#define SOC_SCHARGER_WLED_REG8_wled_resv4_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WLED_REG9_UNION
 结构说明  : WLED_REG9 寄存器结构定义。地址偏移量:0x1E，初值:0x1F，宽度:8
 寄存器说明: WLED_REG9调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wled_driver_trim_test : 6;  /* bit[0-5]: 寄存器控制的精度修调，step：1mv */
        unsigned char  wled_ovp_sel          : 2;  /* bit[6-7]: wled过压点选择
                                                                00:38v
                                                                01:39v
                                                                10:40v
                                                                11:41v */
    } reg;
} SOC_SCHARGER_WLED_REG9_UNION;
#endif
#define SOC_SCHARGER_WLED_REG9_wled_driver_trim_test_START  (0)
#define SOC_SCHARGER_WLED_REG9_wled_driver_trim_test_END    (5)
#define SOC_SCHARGER_WLED_REG9_wled_ovp_sel_START           (6)
#define SOC_SCHARGER_WLED_REG9_wled_ovp_sel_END             (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG0_UNION
 结构说明  : LCD_BOOST_REG0 寄存器结构定义。地址偏移量:0x1F，初值:0x2F，宽度:8
 寄存器说明: LCD_BOOST_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_en_uvp : 1;  /* bit[0]  : en_uvp
                                                         1: 使能欠压电路
                                                         0: 关闭过压电路（不上报） */
        unsigned char  lcd_bst_en_scp : 1;  /* bit[1]  : 1: 使能短路系统自动关闭
                                                         0: 关闭短路系统自动关闭（仍上报） */
        unsigned char  lcd_bst_en_ovp : 1;  /* bit[2]  : 1: 使能过压电路
                                                         0: 关闭过压电路（不上报） */
        unsigned char  lcd_bst_en_ocp : 1;  /* bit[3]  : 1: 使能过流环路控制，并且上报
                                                         0: 使能过流环路控制，不上报 */
        unsigned char  lcd_bst_rcom   : 3;  /* bit[4-6]: 主环路补偿电阻
                                                         000: 520kΩ
                                                         001: 440kΩ
                                                         010: 360kΩ
                                                         011: 280kΩ
                                                         100:200kΩ
                                                         101:160kΩ
                                                         110:120kΩ
                                                         111:80kΩ */
        unsigned char  reserved       : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG0_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_en_uvp_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_en_uvp_END    (0)
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_en_scp_START  (1)
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_en_scp_END    (1)
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_en_ovp_START  (2)
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_en_ovp_END    (2)
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_en_ocp_START  (3)
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_en_ocp_END    (3)
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_rcom_START    (4)
#define SOC_SCHARGER_LCD_BOOST_REG0_lcd_bst_rcom_END      (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG1_UNION
 结构说明  : LCD_BOOST_REG1 寄存器结构定义。地址偏移量:0x20，初值:0x4E，宽度:8
 寄存器说明: LCD_BOOST_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_ckmin     : 2;  /* bit[0-1]: NMOS最小导通时间
                                                            00: 160ns
                                                            01: 120ns
                                                            10: 80ns
                                                            11: 40ns */
        unsigned char  lcd_bst_en_clp_os : 1;  /* bit[2]  : 1: 使能钳位电路失调电压
                                                            0: 关闭钳位电路失调电压 */
        unsigned char  lcd_bst_en_slop   : 1;  /* bit[3]  : 1: 使能斜坡补偿
                                                            0: 关闭斜坡补偿 */
        unsigned char  lcd_bst_en_pfm    : 1;  /* bit[4]  : 1: 使能输出电压方式的PFM模式
                                                            0: 关闭输出电压方式的PFM模式 */
        unsigned char  lcd_bst_en_nring  : 1;  /* bit[5]  : 保留 */
        unsigned char  lcd_bst_en_dmd    : 1;  /* bit[6]  : 1: 使能过零检测
                                                            0: 关闭过零检测 */
        unsigned char  reserved          : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG1_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_ckmin_START      (0)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_ckmin_END        (1)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_clp_os_START  (2)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_clp_os_END    (2)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_slop_START    (3)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_slop_END      (3)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_pfm_START     (4)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_pfm_END       (4)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_nring_START   (5)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_nring_END     (5)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_dmd_START     (6)
#define SOC_SCHARGER_LCD_BOOST_REG1_lcd_bst_en_dmd_END       (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG2_UNION
 结构说明  : LCD_BOOST_REG2 寄存器结构定义。地址偏移量:0x21，初值:0x1A，宽度:8
 寄存器说明: LCD_BOOST_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_ri : 2;  /* bit[0-1]: 电感电流转电压阻抗
                                                     00: 0.75Ω（实际120kΩ）
                                                     01: 0.625Ω（实际100kΩ）
                                                     10: 0.5Ω（实际80kΩ）
                                                     11: 0.375Ω（实际60kΩ） */
        unsigned char  lcd_bst_gm : 4;  /* bit[2-5]: EA中gm电阻设定(gm=2/R)
                                                     000: 90kΩ
                                                     001: 80kΩ
                                                     010: 70kΩ
                                                     011: 60kΩ
                                                     100: 40kΩ
                                                     101: 30kΩ
                                                     110: 20kΩ
                                                     111: 10kΩ
                                                     高位保留 */
        unsigned char  reserved   : 2;  /* bit[6-7]: 保留 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG2_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG2_lcd_bst_ri_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG2_lcd_bst_ri_END    (1)
#define SOC_SCHARGER_LCD_BOOST_REG2_lcd_bst_gm_START  (2)
#define SOC_SCHARGER_LCD_BOOST_REG2_lcd_bst_gm_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG3_UNION
 结构说明  : LCD_BOOST_REG3 寄存器结构定义。地址偏移量:0x22，初值:0x83，宽度:8
 寄存器说明: LCD_BOOST_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_clp     : 3;  /* bit[0-2]: EA输出钳位值和VRAMP直流电平值的失调
                                                          000: 8mV
                                                          001: 12mV
                                                          010: 16mV
                                                          011: 20mV
                                                          100: 24mV
                                                          101: 28mV
                                                          110: 32mV
                                                          111: 36mV */
        unsigned char  lcd_bst_sel_scp : 1;  /* bit[3]  : 1: 2ms内VOUT不足0.85BAT，上报短路
                                                          0: 1ms内VOUT不足0.85BAT，上报短路 */
        unsigned char  lcd_bst_ccom2   : 2;  /* bit[4-5]: EA输出滤波电容
                                                          00: 0.65pF；
                                                          01: 1.3pF；
                                                          10: 1.95pF；
                                                          11: 3.9pF。 */
        unsigned char  lcd_bst_ccom1   : 2;  /* bit[6-7]: 主环路补偿电容
                                                          00: 20pF
                                                          01: 40pF
                                                          10: 60pF
                                                          11: 80pF */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG3_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG3_lcd_bst_clp_START      (0)
#define SOC_SCHARGER_LCD_BOOST_REG3_lcd_bst_clp_END        (2)
#define SOC_SCHARGER_LCD_BOOST_REG3_lcd_bst_sel_scp_START  (3)
#define SOC_SCHARGER_LCD_BOOST_REG3_lcd_bst_sel_scp_END    (3)
#define SOC_SCHARGER_LCD_BOOST_REG3_lcd_bst_ccom2_START    (4)
#define SOC_SCHARGER_LCD_BOOST_REG3_lcd_bst_ccom2_END      (5)
#define SOC_SCHARGER_LCD_BOOST_REG3_lcd_bst_ccom1_START    (6)
#define SOC_SCHARGER_LCD_BOOST_REG3_lcd_bst_ccom1_END      (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG4_UNION
 结构说明  : LCD_BOOST_REG4 寄存器结构定义。地址偏移量:0x23，初值:0x95，宽度:8
 寄存器说明: LCD_BOOST_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_psn     : 2;  /* bit[0-1]: PMOS栅控电压下降斜率
                                                          保留 */
        unsigned char  lcd_bst_psp     : 2;  /* bit[2-3]: PMOS栅控电压上升斜率
                                                          保留 */
        unsigned char  lcd_bst_sel_ocp : 2;  /* bit[4-5]: NMOS限流值
                                                          00: 0.8A
                                                          01: 1.2A
                                                          10: 1.6A
                                                          11: 2.0A */
        unsigned char  lcd_bst_slop    : 2;  /* bit[6-7]: 斜坡补偿斜率调节（电容调节）
                                                          00: 1.2pF；
                                                          01: 1.6pF；
                                                          10: 2.4pF；
                                                          11: 5.1pF。 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG4_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG4_lcd_bst_psn_START      (0)
#define SOC_SCHARGER_LCD_BOOST_REG4_lcd_bst_psn_END        (1)
#define SOC_SCHARGER_LCD_BOOST_REG4_lcd_bst_psp_START      (2)
#define SOC_SCHARGER_LCD_BOOST_REG4_lcd_bst_psp_END        (3)
#define SOC_SCHARGER_LCD_BOOST_REG4_lcd_bst_sel_ocp_START  (4)
#define SOC_SCHARGER_LCD_BOOST_REG4_lcd_bst_sel_ocp_END    (5)
#define SOC_SCHARGER_LCD_BOOST_REG4_lcd_bst_slop_START     (6)
#define SOC_SCHARGER_LCD_BOOST_REG4_lcd_bst_slop_END       (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG5_UNION
 结构说明  : LCD_BOOST_REG5 寄存器结构定义。地址偏移量:0x24，初值:0x55，宽度:8
 寄存器说明: LCD_BOOST_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_dt_nm : 2;  /* bit[0-1]: NMOS关闭后开启PMOS的延时
                                                        00: 0
                                                        01: 2ns
                                                        10: 4ns
                                                        11: 6ns */
        unsigned char  lcd_bst_dt_pm : 2;  /* bit[2-3]: PMOS关闭后开启NMOS的延时
                                                        00: 0
                                                        01: 2ns
                                                        10: 4ns
                                                        11: 6ns */
        unsigned char  lcd_bst_nsn   : 2;  /* bit[4-5]: NMOS栅控电压下降斜率
                                                        00: 20ns
                                                        01: 10ns
                                                        10: 5ns
                                                        11: 3ns */
        unsigned char  lcd_bst_nsp   : 2;  /* bit[6-7]: NMOS栅控电压上升斜率
                                                        00: 20ns
                                                        01: 10ns
                                                        10: 5ns
                                                        11: 3ns */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG5_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG5_lcd_bst_dt_nm_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG5_lcd_bst_dt_nm_END    (1)
#define SOC_SCHARGER_LCD_BOOST_REG5_lcd_bst_dt_pm_START  (2)
#define SOC_SCHARGER_LCD_BOOST_REG5_lcd_bst_dt_pm_END    (3)
#define SOC_SCHARGER_LCD_BOOST_REG5_lcd_bst_nsn_START    (4)
#define SOC_SCHARGER_LCD_BOOST_REG5_lcd_bst_nsn_END      (5)
#define SOC_SCHARGER_LCD_BOOST_REG5_lcd_bst_nsp_START    (6)
#define SOC_SCHARGER_LCD_BOOST_REG5_lcd_bst_nsp_END      (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG6_UNION
 结构说明  : LCD_BOOST_REG6 寄存器结构定义。地址偏移量:0x25，初值:0x53，宽度:8
 寄存器说明: LCD_BOOST_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_vdrop : 3;  /* bit[0-2]: LCD_BST后级LDO和NCP Dropout电压
                                                        000：0
                                                        001：200mV
                                                        010：250mV
                                                        011：300mV
                                                        100：350mV
                                                        101：400mV
                                                        110：450mV
                                                        111：500mV
                                                        高位保留 */
        unsigned char  lcd_bst_osc   : 4;  /* bit[3-6]: 开关频率（MHz）
                                                        0000: 2.991
                                                        0001: 2.852
                                                        0010: 2.712
                                                        0011: 2.568
                                                        0100: 2.423
                                                        0101: 2.274
                                                        0110: 2.122
                                                        0111: 1.968
                                                        1000: 1.813
                                                        1001: 1.654
                                                        1010: 1.492
                                                        1011: 1.325
                                                        1100: 1.155
                                                        1101: 0.981
                                                        1110: 0.802
                                                        1111: 0.617 */
        unsigned char  reserved      : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG6_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG6_lcd_bst_vdrop_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG6_lcd_bst_vdrop_END    (2)
#define SOC_SCHARGER_LCD_BOOST_REG6_lcd_bst_osc_START    (3)
#define SOC_SCHARGER_LCD_BOOST_REG6_lcd_bst_osc_END      (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG7_UNION
 结构说明  : LCD_BOOST_REG7 寄存器结构定义。地址偏移量:0x26，初值:0x0E，宽度:8
 寄存器说明: LCD_BOOST_REG7调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_vo : 5;  /* bit[0-4]: 输出电压（与LCD_LDO和LCD_NCP对应，再加上Dropout电压就是LCD_BST实际输出电压）
                                                     00000:4V
                                                     00001:4.1V
                                                     00010:4.2V
                                                     00011:4.3V
                                                     00100:4.4V
                                                     00101:4.5V
                                                     00110:4.6V
                                                     00111:4.7V
                                                     01000:4.8V
                                                     01001:4.9V
                                                     01010:5.0V
                                                     01011:5.1V
                                                     01100:5.2V
                                                     01101:5.3V
                                                     01110:5.4V
                                                     01111:5.5V
                                                     10000:5.6V
                                                     10001:5.7V
                                                     10010:5.8V
                                                     10011:5.9V
                                                     10100~11111:6V */
        unsigned char  reserved   : 3;  /* bit[5-7]: 保留 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG7_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG7_lcd_bst_vo_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG7_lcd_bst_vo_END    (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG8_UNION
 结构说明  : LCD_BOOST_REG8 寄存器结构定义。地址偏移量:0x27，初值:0x09，宽度:8
 寄存器说明: LCD_BOOST_REG8调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_dmd_ofs : 8;  /* bit[0-7]: DMD失调
                                                          0000: 234mA
                                                          0001: 208mA
                                                          0010: 182mA
                                                          0011: 156mA
                                                          0100: 130mA
                                                          0101: 104mA
                                                          0110: 78mA
                                                          0111: 52mA
                                                          1000: 26mA
                                                          1001:0
                                                          1010: -26mA
                                                          1011: -52mA
                                                          1100: -104mA
                                                          1101: -156mA
                                                          1110: -260mA
                                                          1111: -364mA
                                                          高4bit保留 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG8_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG8_lcd_bst_dmd_ofs_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG8_lcd_bst_dmd_ofs_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG9_UNION
 结构说明  : LCD_BOOST_REG9 寄存器结构定义。地址偏移量:0x28，初值:0x55，宽度:8
 寄存器说明: LCD_BOOST_REG9调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_rsv1 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG9_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG9_lcd_bst_rsv1_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG9_lcd_bst_rsv1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG10_UNION
 结构说明  : LCD_BOOST_REG10 寄存器结构定义。地址偏移量:0x29，初值:0x55，宽度:8
 寄存器说明: LCD_BOOST_REG10调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_rsv2 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG10_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG10_lcd_bst_rsv2_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG10_lcd_bst_rsv2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG11_UNION
 结构说明  : LCD_BOOST_REG11 寄存器结构定义。地址偏移量:0x2A，初值:0x00，宽度:8
 寄存器说明: LCD_BOOST_REG11调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_rsv3 : 8;  /* bit[0-7]: lcd_bst_rsv3<7:3>:预留寄存器;
                                                       lcd_bst_rsv3<2>:1：屏蔽lcd_bst_en配置
                                                        0：lcd_bst_en配置有效;
                                                       lcd_bst_rsv3<1>:1: PMOS强行关闭;
                                                        0: PMOS不被此寄存器控制;
                                                       lcd_bst_rsv3<0>:1: PMOS强行直通，所有内部电路关闭
                                                        0: PMOS不被此寄存器控制 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG11_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG11_lcd_bst_rsv3_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG11_lcd_bst_rsv3_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG12_UNION
 结构说明  : LCD_BOOST_REG12 寄存器结构定义。地址偏移量:0x2B，初值:0x00，宽度:8
 寄存器说明: LCD_BOOST_REG12调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_rsv4 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG12_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG12_lcd_bst_rsv4_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG12_lcd_bst_rsv4_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG13_UNION
 结构说明  : LCD_BOOST_REG13 寄存器结构定义。地址偏移量:0x2C，初值:0x00，宽度:8
 寄存器说明: LCD_BOOST_REG13调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_rsv5 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG13_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG13_lcd_bst_rsv5_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG13_lcd_bst_rsv5_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_BOOST_REG14_UNION
 结构说明  : LCD_BOOST_REG14 寄存器结构定义。地址偏移量:0x2D，初值:0x00，宽度:8
 寄存器说明: LCD_BOOST_REG14调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_bst_rsv6 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_LCD_BOOST_REG14_UNION;
#endif
#define SOC_SCHARGER_LCD_BOOST_REG14_lcd_bst_rsv6_START  (0)
#define SOC_SCHARGER_LCD_BOOST_REG14_lcd_bst_rsv6_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_NCP_REG0_UNION
 结构说明  : LCD_NCP_REG0 寄存器结构定义。地址偏移量:0x2E，初值:0x3A，宽度:8
 寄存器说明: LCD_NCP_REG0调节寄存器。.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_ncp_bwl_set : 2;  /* bit[0-1]: ncp中reglation的带宽调节信号：
                                                          00：带宽最小
                                                          11:带宽最大
                                                          其他次之 */
        unsigned char  lcd_ncp_vset    : 5;  /* bit[2-6]: LCD BIAS的ncp的输出电压控制信号
                                                          00000:-4V
                                                          00001:-4.1V
                                                          00010:-4.2V
                                                          00011:-4.3V
                                                          00100:-4.4V
                                                          00101:-4.5V
                                                          00110:-4.6V
                                                          00111:-4.7V
                                                          01000:-4.8V
                                                          01001:-4.9V
                                                          01010:-5.0V
                                                          01011:-5.1V
                                                          01100:-5.2V
                                                          01101:-5.3V
                                                          01110:-5.4V
                                                          01111:-5.5V
                                                          10000:-5.6V
                                                          10001:-5.7V
                                                          10010:-5.8V
                                                          10011:-5.9V
                                                          10100~11111:-6V */
        unsigned char  reserved        : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_LCD_NCP_REG0_UNION;
#endif
#define SOC_SCHARGER_LCD_NCP_REG0_lcd_ncp_bwl_set_START  (0)
#define SOC_SCHARGER_LCD_NCP_REG0_lcd_ncp_bwl_set_END    (1)
#define SOC_SCHARGER_LCD_NCP_REG0_lcd_ncp_vset_START     (2)
#define SOC_SCHARGER_LCD_NCP_REG0_lcd_ncp_vset_END       (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_NCP_REG1_UNION
 结构说明  : LCD_NCP_REG1 寄存器结构定义。地址偏移量:0x2F，初值:0xB8，宽度:8
 寄存器说明: LCD_NCP_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_ncp_regop_clamp : 1;  /* bit[0]  : reglation中EA内部输出电压是否箝位
                                                              0: 不箝位
                                                              1: 箝位 */
        unsigned char  lcd_ncp_regop_c     : 1;  /* bit[1]  : reglation中EA内部电容大小调节
                                                              0: 1.23pF
                                                              1: 0.615pF */
        unsigned char  lcd_ncp_trm_sel     : 1;  /* bit[2]  : 输出电压是选择寄存器微调或是otp trm
                                                              0：默认选择otp trm
                                                              1：选择寄存器微调 */
        unsigned char  lcd_ncp_dtset       : 2;  /* bit[3-4]: NCP死区时间调节信号
                                                              00: 最长
                                                              11：最短（3.3V 28n）
                                                              其他次之 */
        unsigned char  lcd_ncp_clk_ctr     : 3;  /* bit[5-7]: ncp中工作频率调节信号（fly电容最小充电时间和最长放电时间）
                                                              000: 0.932us
                                                              001：1.012us
                                                              010：1.109us
                                                              011：1.23us
                                                              100：1.385us
                                                              101: 1.591us
                                                              110：1.875us
                                                              111: 2.31us */
    } reg;
} SOC_SCHARGER_LCD_NCP_REG1_UNION;
#endif
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_regop_clamp_START  (0)
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_regop_clamp_END    (0)
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_regop_c_START      (1)
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_regop_c_END        (1)
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_trm_sel_START      (2)
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_trm_sel_END        (2)
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_dtset_START        (3)
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_dtset_END          (4)
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_clk_ctr_START      (5)
#define SOC_SCHARGER_LCD_NCP_REG1_lcd_ncp_clk_ctr_END        (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_NCP_REG2_UNION
 结构说明  : LCD_NCP_REG2 寄存器结构定义。地址偏移量:0x30，初值:0x00，宽度:8
 寄存器说明: LCD_NCP_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_ncp_trim_bak : 5;  /* bit[0-4]: 寄存器trim输出电压
                                                           00000：默认精确输出电压
                                                           00001：-0.26%
                                                           00010：-0.57%
                                                           00011：-0.86%
                                                           00100：-1.19%
                                                           00101：-1.48%
                                                           00110：-1.79%
                                                           00111：-2.08%
                                                           01000：-2.44%
                                                           01001：-2.73%
                                                           01010：-3.04%
                                                           01011: -3.33%
                                                           01100: -3.67%
                                                           01101: -3.96%
                                                           01110: -4.27%
                                                           01111: -4.56%
                                                           10000：0.4%
                                                           10001：0.7%
                                                           10010：1.0%
                                                           10011：1.3%
                                                           10100：1.6%
                                                           10101：1.9%
                                                           10110：2.2%
                                                           10111：2.5%
                                                           11000：2.9%
                                                           11001：3.2%
                                                           11010: 3.5%
                                                           11011: 3.8%
                                                           11100: 4.1%
                                                           11101: 4.4%
                                                           11110: 4.7%
                                                           11111: 5.0% */
        unsigned char  lcd_ncp_reg_p    : 2;  /* bit[5-6]: 增加reglation的下拉电流
                                                           00: 下拉电流为5u
                                                           01：下拉电流为6u
                                                           10：下拉电流为7u
                                                           11: 下拉电流为8u */
        unsigned char  lcd_ncp_reg_c    : 1;  /* bit[7]  : reglation中EA外部补偿电容调节
                                                           0：不增加补偿电容
                                                           1：增加补偿电容 */
    } reg;
} SOC_SCHARGER_LCD_NCP_REG2_UNION;
#endif
#define SOC_SCHARGER_LCD_NCP_REG2_lcd_ncp_trim_bak_START  (0)
#define SOC_SCHARGER_LCD_NCP_REG2_lcd_ncp_trim_bak_END    (4)
#define SOC_SCHARGER_LCD_NCP_REG2_lcd_ncp_reg_p_START     (5)
#define SOC_SCHARGER_LCD_NCP_REG2_lcd_ncp_reg_p_END       (6)
#define SOC_SCHARGER_LCD_NCP_REG2_lcd_ncp_reg_c_START     (7)
#define SOC_SCHARGER_LCD_NCP_REG2_lcd_ncp_reg_c_END       (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_NCP_REG3_UNION
 结构说明  : LCD_NCP_REG3 寄存器结构定义。地址偏移量:0x31，初值:0x04，宽度:8
 寄存器说明: LCD_NCP_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_ncp_rap_vx   : 1;  /* bit[0]  : 0: 利用VX方波产生斜坡信号
                                                           1: 只利用前馈电容产生斜坡量 */
        unsigned char  lcd_ncp_rap_set  : 2;  /* bit[1-2]: 调节VFB2上纹波的大小
                                                           00:纹波最大
                                                           11:纹波最小
                                                           其他次之 */
        unsigned char  lcd_ncp_reg_n    : 3;  /* bit[3-5]: 调节reglatiop输出上下电阻值的大小
                                                           000:5k
                                                           001:4k
                                                           010:3k
                                                           011:2k
                                                           100:6k
                                                           101:7k
                                                           111:8k */
        unsigned char  lcd_ncp_vcmp_sel : 1;  /* bit[6]  : reglation是否使用
                                                           0：默认使用
                                                           1：不使用 */
        unsigned char  reserved         : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_LCD_NCP_REG3_UNION;
#endif
#define SOC_SCHARGER_LCD_NCP_REG3_lcd_ncp_rap_vx_START    (0)
#define SOC_SCHARGER_LCD_NCP_REG3_lcd_ncp_rap_vx_END      (0)
#define SOC_SCHARGER_LCD_NCP_REG3_lcd_ncp_rap_set_START   (1)
#define SOC_SCHARGER_LCD_NCP_REG3_lcd_ncp_rap_set_END     (2)
#define SOC_SCHARGER_LCD_NCP_REG3_lcd_ncp_reg_n_START     (3)
#define SOC_SCHARGER_LCD_NCP_REG3_lcd_ncp_reg_n_END       (5)
#define SOC_SCHARGER_LCD_NCP_REG3_lcd_ncp_vcmp_sel_START  (6)
#define SOC_SCHARGER_LCD_NCP_REG3_lcd_ncp_vcmp_sel_END    (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_NCP_REG4_UNION
 结构说明  : LCD_NCP_REG4 寄存器结构定义。地址偏移量:0x32，初值:0x00，宽度:8
 寄存器说明: LCD_NCP_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_ncp_vl1_disclamp : 1;  /* bit[0]  : 为0时，默认箝位；当输入电压低于5.4V时，设置为1，不箝位VL1 */
        unsigned char  lcd_ncp_vh1_disclamp : 1;  /* bit[1]  : 为0时，默认箝位；当输入电压低于5.4V时，设置为1，不箝位VH1 */
        unsigned char  lcd_ncp_g3dr_set     : 2;  /* bit[2-3]: 输出功率NMOS管的数量调节
                                                               00：默认m=70
                                                               01：m=50
                                                               10：m=35
                                                               11：m=20 */
        unsigned char  reserved             : 4;  /* bit[4-7]: 保留 */
    } reg;
} SOC_SCHARGER_LCD_NCP_REG4_UNION;
#endif
#define SOC_SCHARGER_LCD_NCP_REG4_lcd_ncp_vl1_disclamp_START  (0)
#define SOC_SCHARGER_LCD_NCP_REG4_lcd_ncp_vl1_disclamp_END    (0)
#define SOC_SCHARGER_LCD_NCP_REG4_lcd_ncp_vh1_disclamp_START  (1)
#define SOC_SCHARGER_LCD_NCP_REG4_lcd_ncp_vh1_disclamp_END    (1)
#define SOC_SCHARGER_LCD_NCP_REG4_lcd_ncp_g3dr_set_START      (2)
#define SOC_SCHARGER_LCD_NCP_REG4_lcd_ncp_g3dr_set_END        (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_NCP_REG5_UNION
 结构说明  : LCD_NCP_REG5 寄存器结构定义。地址偏移量:0x33，初值:0x00，宽度:8
 寄存器说明: LCD_NCP_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_ncp_resved : 8;  /* bit[0-7]: 7:1位为保留寄存器，低0位调节功率PMOS的个数，默认值为0。0：m=40；1：m=20。 */
    } reg;
} SOC_SCHARGER_LCD_NCP_REG5_UNION;
#endif
#define SOC_SCHARGER_LCD_NCP_REG5_lcd_ncp_resved_START  (0)
#define SOC_SCHARGER_LCD_NCP_REG5_lcd_ncp_resved_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LCD_LDO_REG0_UNION
 结构说明  : LCD_LDO_REG0 寄存器结构定义。地址偏移量:0x34，初值:0x0E，宽度:8
 寄存器说明: LCD_LDO_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  lcd_ldo_vset : 5;  /* bit[0-4]: LCD BIAS的LDO的输出电压控制信号
                                                       00000:4V
                                                       00001:4.1V
                                                       00010:4.2V
                                                       00011:4.3V
                                                       00100:4.4V
                                                       00101:4.5V
                                                       00110:4.6V
                                                       00111:4.7V
                                                       01000:4.8V
                                                       01001:4.9V
                                                       01010:5.0V
                                                       01011:5.1V
                                                       01100:5.2V
                                                       01101:5.3V
                                                       01110:5.4V
                                                       01111:5.5V
                                                       10000:5.6V
                                                       10001:5.7V
                                                       10010:5.8V
                                                       10011:5.9V
                                                       10100~11111:6V */
        unsigned char  reserved     : 3;  /* bit[5-7]: 保留 */
    } reg;
} SOC_SCHARGER_LCD_LDO_REG0_UNION;
#endif
#define SOC_SCHARGER_LCD_LDO_REG0_lcd_ldo_vset_START  (0)
#define SOC_SCHARGER_LCD_LDO_REG0_lcd_ldo_vset_END    (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_LDO_REG0_UNION
 结构说明  : LDO_REG0 寄存器结构定义。地址偏移量:0x35，初值:0x3D，宽度:8
 寄存器说明: LDO_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ldo2_200ma_vset : 4;  /* bit[0-3]: 200mA的LDO2的输出电压控制信号
                                                          0000:1.5V
                                                          0001:1.6V
                                                          0010:1.7V
                                                          0011:1.8V
                                                          0100:1.9V
                                                          0101:2.0V
                                                          0110:2.2V
                                                          0111:2.4V
                                                          1000:2.6V
                                                          1001:2.7V
                                                          1010:2.8V
                                                          1011:2.9V
                                                          1100:3.0V
                                                          1101:3.1V
                                                          1110:3.2V
                                                          1111:3.3V */
        unsigned char  ldo1_200ma_vset : 4;  /* bit[4-7]: 200mA的LDO1的输出电压控制信号
                                                          0000:1.5V
                                                          0001:1.6V
                                                          0010:1.7V
                                                          0011:1.8V
                                                          0100:1.9V
                                                          0101:2.0V
                                                          0110:2.2V
                                                          0111:2.4V
                                                          1000:2.6V
                                                          1001:2.7V
                                                          1010:2.8V
                                                          1011:2.9V
                                                          1100:3.0V
                                                          1101:3.1V
                                                          1110:3.2V
                                                          1111:3.3V */
    } reg;
} SOC_SCHARGER_LDO_REG0_UNION;
#endif
#define SOC_SCHARGER_LDO_REG0_ldo2_200ma_vset_START  (0)
#define SOC_SCHARGER_LDO_REG0_ldo2_200ma_vset_END    (3)
#define SOC_SCHARGER_LDO_REG0_ldo1_200ma_vset_START  (4)
#define SOC_SCHARGER_LDO_REG0_ldo1_200ma_vset_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG0_UNION
 结构说明  : BUCK_REG0 寄存器结构定义。地址偏移量:0x36，初值:0xFF，宽度:8
 寄存器说明: BUCK_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_max_ontime  : 2;  /* bit[0-1]: 最大导通时间选择
                                                           00:6.2us
                                                           01:5.4us
                                                           10:4.8us
                                                           11:4us */
        unsigned char  buck_c2_sel      : 2;  /* bit[2-3]: 迟滞电路RC电容值选择
                                                           00:5pF
                                                           01:10pF
                                                           10:15pF
                                                           11:20pF */
        unsigned char  buck_c1_sel      : 2;  /* bit[4-5]: 迟滞电路隔直电容选择
                                                           00:10pF
                                                           01:20pF
                                                           10:30pF
                                                           11:40pF */
        unsigned char  buck_max_offtime : 2;  /* bit[6-7]: 最大关断时间选择
                                                           00:6.2us
                                                           01:5.4us
                                                           10:4.8us
                                                           11:4us */
    } reg;
} SOC_SCHARGER_BUCK_REG0_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG0_buck_max_ontime_START   (0)
#define SOC_SCHARGER_BUCK_REG0_buck_max_ontime_END     (1)
#define SOC_SCHARGER_BUCK_REG0_buck_c2_sel_START       (2)
#define SOC_SCHARGER_BUCK_REG0_buck_c2_sel_END         (3)
#define SOC_SCHARGER_BUCK_REG0_buck_c1_sel_START       (4)
#define SOC_SCHARGER_BUCK_REG0_buck_c1_sel_END         (5)
#define SOC_SCHARGER_BUCK_REG0_buck_max_offtime_START  (6)
#define SOC_SCHARGER_BUCK_REG0_buck_max_offtime_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG1_UNION
 结构说明  : BUCK_REG1 寄存器结构定义。地址偏移量:0x37，初值:0xF7，宽度:8
 寄存器说明: BUCK_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_hmos_fall_ramp : 2;  /* bit[0-1]: 上管下降沿驱动能力选择
                                                              00：36ns
                                                              01:18ns
                                                              10:12ns
                                                              11:9ns */
        unsigned char  buck_hmos_rise_ramp : 2;  /* bit[2-3]: 上管上升沿驱动能力选择
                                                              00：50ns
                                                              01:25ns
                                                              10:17ns
                                                              11:12.5ns */
        unsigned char  buck_min_offtime    : 2;  /* bit[4-5]: 最小关断时间选择
                                                              00:180ns
                                                              01:160ns
                                                              10:140ns
                                                              11:120ns */
        unsigned char  buck_min_ontime     : 2;  /* bit[6-7]: 最小导通时间选择
                                                              00:155ns
                                                              01:120ns
                                                              10:110ns
                                                              11:75ns */
    } reg;
} SOC_SCHARGER_BUCK_REG1_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG1_buck_hmos_fall_ramp_START  (0)
#define SOC_SCHARGER_BUCK_REG1_buck_hmos_fall_ramp_END    (1)
#define SOC_SCHARGER_BUCK_REG1_buck_hmos_rise_ramp_START  (2)
#define SOC_SCHARGER_BUCK_REG1_buck_hmos_rise_ramp_END    (3)
#define SOC_SCHARGER_BUCK_REG1_buck_min_offtime_START     (4)
#define SOC_SCHARGER_BUCK_REG1_buck_min_offtime_END       (5)
#define SOC_SCHARGER_BUCK_REG1_buck_min_ontime_START      (6)
#define SOC_SCHARGER_BUCK_REG1_buck_min_ontime_END        (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG2_UNION
 结构说明  : BUCK_REG2 寄存器结构定义。地址偏移量:0x38，初值:0xF1，宽度:8
 寄存器说明: BUCK_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_en_dmd               : 1;  /* bit[0]  : 选择是否使能DMD功能
                                                                    0：不使能
                                                                    1：使能 */
        unsigned char  buck_dt_lx_rise_delay_sel : 1;  /* bit[1]  : lx上升沿死区额外延迟5ns
                                                                    0：不额外延迟
                                                                    1：额外延迟 */
        unsigned char  buck_dt_lx_fall_sel       : 1;  /* bit[2]  : lx下降沿死区产生方式选择
                                                                    0：老死区时间
                                                                    1：新死区时间 */
        unsigned char  buck_dt_lx_rise_sel       : 1;  /* bit[3]  : lx上升沿死区产生方式选择
                                                                    0：老死区时间
                                                                    1：新死区时间 */
        unsigned char  buck_lmos_fall_ramp       : 2;  /* bit[4-5]: 下管下降沿驱动能力选择
                                                                    00：40ns
                                                                    01:20ns
                                                                    10:10ns
                                                                    11:5ns */
        unsigned char  buck_lmos_rise_ramp       : 2;  /* bit[6-7]: 下管上升沿驱动能力选择
                                                                    00：40ns
                                                                    01:20ns
                                                                    10:10ns
                                                                    11:5ns */
    } reg;
} SOC_SCHARGER_BUCK_REG2_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG2_buck_en_dmd_START                (0)
#define SOC_SCHARGER_BUCK_REG2_buck_en_dmd_END                  (0)
#define SOC_SCHARGER_BUCK_REG2_buck_dt_lx_rise_delay_sel_START  (1)
#define SOC_SCHARGER_BUCK_REG2_buck_dt_lx_rise_delay_sel_END    (1)
#define SOC_SCHARGER_BUCK_REG2_buck_dt_lx_fall_sel_START        (2)
#define SOC_SCHARGER_BUCK_REG2_buck_dt_lx_fall_sel_END          (2)
#define SOC_SCHARGER_BUCK_REG2_buck_dt_lx_rise_sel_START        (3)
#define SOC_SCHARGER_BUCK_REG2_buck_dt_lx_rise_sel_END          (3)
#define SOC_SCHARGER_BUCK_REG2_buck_lmos_fall_ramp_START        (4)
#define SOC_SCHARGER_BUCK_REG2_buck_lmos_fall_ramp_END          (5)
#define SOC_SCHARGER_BUCK_REG2_buck_lmos_rise_ramp_START        (6)
#define SOC_SCHARGER_BUCK_REG2_buck_lmos_rise_ramp_END          (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG3_UNION
 结构说明  : BUCK_REG3 寄存器结构定义。地址偏移量:0x39，初值:0x11，宽度:8
 寄存器说明: BUCK_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_sysmin_sel : 2;  /* bit[0-1]: Vsys最小输出电压选择
                                                          00:3.55V
                                                          01:3.65V
                                                          10:3.75V
                                                          11:3.85V */
        unsigned char  buck_dmd_offset : 3;  /* bit[2-4]: DMD点选择
                                                          00：-250mA
                                                          01：-190mA
                                                          10:-130mA
                                                          11:-60mA
                                                          100：30mA
                                                          101:70mA
                                                          110:120mA
                                                          111:174mA */
        unsigned char  reserved        : 3;  /* bit[5-7]: 保留 */
    } reg;
} SOC_SCHARGER_BUCK_REG3_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG3_buck_sysmin_sel_START  (0)
#define SOC_SCHARGER_BUCK_REG3_buck_sysmin_sel_END    (1)
#define SOC_SCHARGER_BUCK_REG3_buck_dmd_offset_START  (2)
#define SOC_SCHARGER_BUCK_REG3_buck_dmd_offset_END    (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG4_UNION
 结构说明  : BUCK_REG4 寄存器结构定义。地址偏移量:0x3A，初值:0x26，宽度:8
 寄存器说明: BUCK_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_dpm_sel     : 4;  /* bit[0-3]: DPM输入电压设定
                                                           0000:3.88V
                                                           0001:3.96V
                                                           0010:4.04V
                                                           0011:4.12V
                                                           0100:4.20V
                                                           0101:4.28V
                                                           0110:4.36V
                                                           0111:4.44V
                                                           1000:4.52V
                                                           1001:4.60V
                                                           1010:4.68V
                                                           1011:4.76V
                                                           1100:4.84V
                                                           1101:4.92V
                                                           1110:5.00V
                                                           1111:5.08V */
        unsigned char  buck_int_lim_sel : 4;  /* bit[4-7]: 平均限流环设定电流
                                                           0000:100mA
                                                           0001:150mA
                                                           0010:500mA
                                                           0011:900mA
                                                           0100:1A
                                                           0101:1.2A
                                                           0110:1.5A
                                                           0111:1.6A
                                                           1000:1.8A
                                                           1001:2.0A
                                                           1010:2.2A
                                                           1011:2.5A */
    } reg;
} SOC_SCHARGER_BUCK_REG4_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG4_buck_dpm_sel_START      (0)
#define SOC_SCHARGER_BUCK_REG4_buck_dpm_sel_END        (3)
#define SOC_SCHARGER_BUCK_REG4_buck_int_lim_sel_START  (4)
#define SOC_SCHARGER_BUCK_REG4_buck_int_lim_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG5_UNION
 结构说明  : BUCK_REG5 寄存器结构定义。地址偏移量:0x3B，初值:0x00，宽度:8
 寄存器说明: BUCK_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve : 8;  /* bit[0-7]: buck_reserve<5:0>为预留寄存器
                                                       buck_reserve<6>:上电初始态屏蔽电路关闭信号
                                                       0：使能初始态屏蔽电路(default)
                                                       1:关闭初始态屏蔽电路.
                                                       Buck_reserve<7>:充电模式选择
                                                       0：IR模式（default)
                                                       1：GAP模式. */
    } reg;
} SOC_SCHARGER_BUCK_REG5_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG5_buck_reserve_START  (0)
#define SOC_SCHARGER_BUCK_REG5_buck_reserve_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG6_UNION
 结构说明  : BUCK_REG6 寄存器结构定义。地址偏移量:0x3C，初值:0x20，宽度:8
 寄存器说明: BUCK_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_ocp_off : 1;  /* bit[0]  : 关闭OCP功能
                                                       0：不关闭
                                                       1：关闭 */
        unsigned char  buck_ocp_sel : 2;  /* bit[1-2]: OCP点选择
                                                       00:2.8
                                                       01:3.4
                                                       10:4
                                                       11:4.6 */
        unsigned char  buck_gap_sel : 3;  /* bit[3-5]: buck 150mv gap 调整：
                                                       待补充。 */
        unsigned char  reserved     : 2;  /* bit[6-7]: 保留 */
    } reg;
} SOC_SCHARGER_BUCK_REG6_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG6_buck_ocp_off_START  (0)
#define SOC_SCHARGER_BUCK_REG6_buck_ocp_off_END    (0)
#define SOC_SCHARGER_BUCK_REG6_buck_ocp_sel_START  (1)
#define SOC_SCHARGER_BUCK_REG6_buck_ocp_sel_END    (2)
#define SOC_SCHARGER_BUCK_REG6_buck_gap_sel_START  (3)
#define SOC_SCHARGER_BUCK_REG6_buck_gap_sel_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG0_UNION
 结构说明  : OTG_REG0 寄存器结构定义。地址偏移量:0x3D，初值:0x75，宽度:8
 寄存器说明: OTG_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_uvp_en       : 1;  /* bit[0]: otg boost uvp使能：
                                                         0: 关闭欠压电路（不上报）
                                                         1: 使能欠压电路（上报） */
        unsigned char  otg_scp_time     : 1;  /* bit[1]: otg boost scp时间选择：
                                                         0: 1ms内VOUT不足0.85BAT，上报短路
                                                         1: 2ms内VOUT不足0.85BAT，上报短路 */
        unsigned char  otg_scp_en       : 1;  /* bit[2]: otg boost scp动作选择：
                                                         0: 短路后系统不自动关闭（仍上报）
                                                         1: 短路后系统自动关闭 */
        unsigned char  otg_ocp_sys      : 1;  /* bit[3]: boost OCP动作选择：
                                                         0: 过流后上报
                                                         1: 过流后不上报 */
        unsigned char  otg_ocp_en       : 1;  /* bit[4]: boost OCP动作选择：
                                                         0: 过流后不限流
                                                         1: 过流后限流 */
        unsigned char  otg_lim_set      : 1;  /* bit[5]: boost平均限流选择：
                                                         0:500mA
                                                         1:1A */
        unsigned char  otg_lim_en       : 1;  /* bit[6]: boost 平均限流模块使能：
                                                         0: 关闭平均限流模块
                                                         1: 使能平均限流模块 */
        unsigned char  otg_force_en_int : 1;  /* bit[7]: 0: 关闭otg_force_en
                                                         1: 开启otg_force_en */
    } reg;
} SOC_SCHARGER_OTG_REG0_UNION;
#endif
#define SOC_SCHARGER_OTG_REG0_otg_uvp_en_START        (0)
#define SOC_SCHARGER_OTG_REG0_otg_uvp_en_END          (0)
#define SOC_SCHARGER_OTG_REG0_otg_scp_time_START      (1)
#define SOC_SCHARGER_OTG_REG0_otg_scp_time_END        (1)
#define SOC_SCHARGER_OTG_REG0_otg_scp_en_START        (2)
#define SOC_SCHARGER_OTG_REG0_otg_scp_en_END          (2)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_sys_START       (3)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_sys_END         (3)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_en_START        (4)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_en_END          (4)
#define SOC_SCHARGER_OTG_REG0_otg_lim_set_START       (5)
#define SOC_SCHARGER_OTG_REG0_otg_lim_set_END         (5)
#define SOC_SCHARGER_OTG_REG0_otg_lim_en_START        (6)
#define SOC_SCHARGER_OTG_REG0_otg_lim_en_END          (6)
#define SOC_SCHARGER_OTG_REG0_otg_force_en_int_START  (7)
#define SOC_SCHARGER_OTG_REG0_otg_force_en_int_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG1_UNION
 结构说明  : OTG_REG1 寄存器结构定义。地址偏移量:0x3E，初值:0x19，宽度:8
 寄存器说明: OTG_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_ovp_set_t : 2;  /* bit[0-1]: boost ovp去抖时间选择：
                                                        00: 0
                                                        01: 1ms
                                                        10: 2ms
                                                        11: 4ms */
        unsigned char  otg_skip_set  : 1;  /* bit[2]  : skip周期内Pmos的开关状态：
                                                        0: PMOS关闭
                                                        1: PMOS开启 */
        unsigned char  otg_ovp_en    : 1;  /* bit[3]  : boost ovp使能：
                                                        0: 关闭过压电路（不上报）
                                                        1: 使能过压电路（上报） */
        unsigned char  otg_uvp_set_t : 2;  /* bit[4-5]: boost uvp去抖时间选择：
                                                        00: 0
                                                        01: 1ms
                                                        10: 2ms
                                                        11: 4ms */
        unsigned char  reserved      : 2;  /* bit[6-7]: 保留 */
    } reg;
} SOC_SCHARGER_OTG_REG1_UNION;
#endif
#define SOC_SCHARGER_OTG_REG1_otg_ovp_set_t_START  (0)
#define SOC_SCHARGER_OTG_REG1_otg_ovp_set_t_END    (1)
#define SOC_SCHARGER_OTG_REG1_otg_skip_set_START   (2)
#define SOC_SCHARGER_OTG_REG1_otg_skip_set_END     (2)
#define SOC_SCHARGER_OTG_REG1_otg_ovp_en_START     (3)
#define SOC_SCHARGER_OTG_REG1_otg_ovp_en_END       (3)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_set_t_START  (4)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_set_t_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG2_UNION
 结构说明  : OTG_REG2 寄存器结构定义。地址偏移量:0x3F，初值:0xE5，宽度:8
 寄存器说明: OTG_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_clp_l_iav_en : 1;  /* bit[0]  : boost EA_iav钳位电路（低）使能：
                                                           0: 关闭钳位电路
                                                           1: 使能钳位电路 */
        unsigned char  otg_clp_h_iav_en : 1;  /* bit[1]  : boost EA_iav钳位电路（高）使能：
                                                           0: 关闭钳位电路
                                                           1: 使能钳位电路 */
        unsigned char  otg_clp_l_en     : 1;  /* bit[2]  : boost EA钳位电路（低）使能：
                                                           0: 关闭钳位电路
                                                           1: 使能钳位电路 */
        unsigned char  otg_clp_h_en     : 1;  /* bit[3]  : boost EA钳位电路（高）使能：
                                                           0: 关闭钳位电路
                                                           1: 使能钳位电路 */
        unsigned char  otg_slop_set     : 2;  /* bit[4-5]: boost 斜坡补偿电容选择：
                                                           00: 1.5p
                                                           01: 2p
                                                           10: 2.5p
                                                           11: 3p */
        unsigned char  otg_slop_en      : 1;  /* bit[6]  : boost 斜坡补偿使能：
                                                           0: 关闭斜坡补偿
                                                           1: 使能斜坡补偿 */
        unsigned char  otg_dmd          : 1;  /* bit[7]  : boost dmd使能：
                                                           0: 关闭过零检测
                                                           1: 使能过零检测 */
    } reg;
} SOC_SCHARGER_OTG_REG2_UNION;
#endif
#define SOC_SCHARGER_OTG_REG2_otg_clp_l_iav_en_START  (0)
#define SOC_SCHARGER_OTG_REG2_otg_clp_l_iav_en_END    (0)
#define SOC_SCHARGER_OTG_REG2_otg_clp_h_iav_en_START  (1)
#define SOC_SCHARGER_OTG_REG2_otg_clp_h_iav_en_END    (1)
#define SOC_SCHARGER_OTG_REG2_otg_clp_l_en_START      (2)
#define SOC_SCHARGER_OTG_REG2_otg_clp_l_en_END        (2)
#define SOC_SCHARGER_OTG_REG2_otg_clp_h_en_START      (3)
#define SOC_SCHARGER_OTG_REG2_otg_clp_h_en_END        (3)
#define SOC_SCHARGER_OTG_REG2_otg_slop_set_START      (4)
#define SOC_SCHARGER_OTG_REG2_otg_slop_set_END        (5)
#define SOC_SCHARGER_OTG_REG2_otg_slop_en_START       (6)
#define SOC_SCHARGER_OTG_REG2_otg_slop_en_END         (6)
#define SOC_SCHARGER_OTG_REG2_otg_dmd_START           (7)
#define SOC_SCHARGER_OTG_REG2_otg_dmd_END             (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG3_UNION
 结构说明  : OTG_REG3 寄存器结构定义。地址偏移量:0x40，初值:0x8B，宽度:8
 寄存器说明: OTG_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_gm        : 3;  /* bit[0-2]: boost EA中gm电阻设定(gm=2/R)
                                                        000: 90kΩ
                                                        001: 80kΩ
                                                        010: 70kΩ
                                                        011: 60kΩ
                                                        100: 40kΩ
                                                        101: 30kΩ
                                                        110: 20kΩ
                                                        111: 10kΩ */
        unsigned char  otg_iav_t_set : 2;  /* bit[3-4]: boost iav脉冲宽度设置：
                                                        00: 40ns
                                                        01: 30ns
                                                        10: 20ns
                                                        11: 15ns */
        unsigned char  reseved       : 1;  /* bit[5]  : 保留,配置无用。 */
        unsigned char  reserved      : 1;  /* bit[6]  : 保留，配置无用。 */
        unsigned char  otg_pfm_v_en  : 1;  /* bit[7]  : boost pfm_v使能： 0: 关闭pfm
                                                        1: 使能pfm */
    } reg;
} SOC_SCHARGER_OTG_REG3_UNION;
#endif
#define SOC_SCHARGER_OTG_REG3_otg_gm_START         (0)
#define SOC_SCHARGER_OTG_REG3_otg_gm_END           (2)
#define SOC_SCHARGER_OTG_REG3_otg_iav_t_set_START  (3)
#define SOC_SCHARGER_OTG_REG3_otg_iav_t_set_END    (4)
#define SOC_SCHARGER_OTG_REG3_reseved_START        (5)
#define SOC_SCHARGER_OTG_REG3_reseved_END          (5)
#define SOC_SCHARGER_OTG_REG3_otg_pfm_v_en_START   (7)
#define SOC_SCHARGER_OTG_REG3_otg_pfm_v_en_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG4_UNION
 结构说明  : OTG_REG4 寄存器结构定义。地址偏移量:0x41，初值:0x65，宽度:8
 寄存器说明: OTG_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_ccom2_cmp : 2;  /* bit[0-1]: boost EA输出滤波电容（峰值电流模）
                                                        00: 0.8pF
                                                        01: 1.1pF
                                                        10: 1.4pF
                                                        11: 1.7pF */
        unsigned char  otg_ccom1_cmp : 2;  /* bit[2-3]: boost 主环路补偿电容（峰值电流模）
                                                        00: 35pF
                                                        01: 40pF
                                                        10: 45pF
                                                        11: 50pF */
        unsigned char  otg_rcom_cmp  : 2;  /* bit[4-5]: boost 主环路补偿电阻（峰值电流模）
                                                        00: 320kΩ
                                                        01: 280kΩ
                                                        10: 240kΩ
                                                        11: 200kΩ */
        unsigned char  otg_clp_l_set : 1;  /* bit[6]  : boost EA输出钳位值和VRAMP直流电平值的失调
                                                        0：27mv
                                                        1：40mv */
        unsigned char  reserved      : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_OTG_REG4_UNION;
#endif
#define SOC_SCHARGER_OTG_REG4_otg_ccom2_cmp_START  (0)
#define SOC_SCHARGER_OTG_REG4_otg_ccom2_cmp_END    (1)
#define SOC_SCHARGER_OTG_REG4_otg_ccom1_cmp_START  (2)
#define SOC_SCHARGER_OTG_REG4_otg_ccom1_cmp_END    (3)
#define SOC_SCHARGER_OTG_REG4_otg_rcom_cmp_START   (4)
#define SOC_SCHARGER_OTG_REG4_otg_rcom_cmp_END     (5)
#define SOC_SCHARGER_OTG_REG4_otg_clp_l_set_START  (6)
#define SOC_SCHARGER_OTG_REG4_otg_clp_l_set_END    (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG5_UNION
 结构说明  : OTG_REG5 寄存器结构定义。地址偏移量:0x42，初值:0x28，宽度:8
 寄存器说明: OTG_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_ccom_iav  : 2;  /* bit[0-1]: boost 限流环路电容补偿
                                                        00: 20p
                                                        01: 25p
                                                        10: 30p
                                                        11: 35p */
        unsigned char  otg_rcom2_iav : 2;  /* bit[2-3]: boost 限流环路电阻补偿
                                                        00: 620kΩ
                                                        01: 580kΩ
                                                        10: 440kΩ
                                                        11: 300kΩ */
        unsigned char  otg_rcom1_iav : 2;  /* bit[4-5]: boost 限流环路电阻补偿
                                                        00: 1.2MΩ
                                                        01: 1.6MΩ
                                                        10: 2.0MΩ
                                                        11: 2.4MΩ */
        unsigned char  reserved      : 2;  /* bit[6-7]: 保留 */
    } reg;
} SOC_SCHARGER_OTG_REG5_UNION;
#endif
#define SOC_SCHARGER_OTG_REG5_otg_ccom_iav_START   (0)
#define SOC_SCHARGER_OTG_REG5_otg_ccom_iav_END     (1)
#define SOC_SCHARGER_OTG_REG5_otg_rcom2_iav_START  (2)
#define SOC_SCHARGER_OTG_REG5_otg_rcom2_iav_END    (3)
#define SOC_SCHARGER_OTG_REG5_otg_rcom1_iav_START  (4)
#define SOC_SCHARGER_OTG_REG5_otg_rcom1_iav_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG6_UNION
 结构说明  : OTG_REG6 寄存器结构定义。地址偏移量:0x43，初值:0x86，宽度:8
 寄存器说明: OTG_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_lmos_ocp  : 2;  /* bit[0-1]: boost 低端MOS管限流值(A)
                                                        00: 1.5
                                                        01: 1.8
                                                        10: 2.5
                                                        11: 2.7 */
        unsigned char  otg_osc_ckmax : 2;  /* bit[2-3]: 振荡器放电电流（uA）
                                                        00: 13
                                                        01: 14
                                                        10: 15 
                                                        11: 16  */
        unsigned char  otg_osc       : 4;  /* bit[4-7]: 开关频率（MHz）
                                                        0000: 2.01
                                                        0001: 1.98
                                                        0010: 1.94
                                                        0011: 1.90
                                                        0100: 1.86
                                                        0101: 1.81
                                                        0110: 1.74
                                                        0111: 1.65
                                                        1000: 1.54
                                                        1001: 1.41
                                                        1010: 1.27
                                                        1011: 1.11
                                                        1100: 0.92
                                                        1101: 0.73
                                                        1110: 0.50
                                                        1111: 0.31 */
    } reg;
} SOC_SCHARGER_OTG_REG6_UNION;
#endif
#define SOC_SCHARGER_OTG_REG6_otg_lmos_ocp_START   (0)
#define SOC_SCHARGER_OTG_REG6_otg_lmos_ocp_END     (1)
#define SOC_SCHARGER_OTG_REG6_otg_osc_ckmax_START  (2)
#define SOC_SCHARGER_OTG_REG6_otg_osc_ckmax_END    (3)
#define SOC_SCHARGER_OTG_REG6_otg_osc_START        (4)
#define SOC_SCHARGER_OTG_REG6_otg_osc_END          (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG7_UNION
 结构说明  : OTG_REG7 寄存器结构定义。地址偏移量:0x44，初值:0xA9，宽度:8
 寄存器说明: OTG_REG7调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_dmd_ofs : 4;  /* bit[0-3]: boost DMD失调电压调节
                                                      0000: 20mV (300mA)
                                                      0001: 16mV (240mA)
                                                      0010: 14mV (210mA)
                                                      0011: 12mV (180mA)
                                                      0100: 10mV (150mA)
                                                      0101: 8mV (120mA)
                                                      0110: 6mV (90mA)
                                                      0111: 4mV (60mA)
                                                      1000: 2mV (30mA)
                                                      1001:0
                                                      1010: -16mV (-180mA).
                                                      1011: -32mV (-360mA).
                                                      1100: -48mV (-540mA).
                                                      1101: -64mV (-720mA)..
                                                      1110: -128mV (-900mA).
                                                      1111: -256mV (-1080mA) */
        unsigned char  otg_rf      : 2;  /* bit[4-5]: 电感电流转电压阻抗
                                                      00: 0.5Ω（实际100kΩ）
                                                      01: 0.4Ω（实际80kΩ）
                                                      10: 0.3Ω（实际60kΩ）
                                                      11: 0.2Ω（实际40kΩ） */
        unsigned char  otg_ckmin   : 2;  /* bit[6-7]: NMOS最小导通时间
                                                      00: 40ns
                                                      01: 30ns
                                                      10: 20ns
                                                      11: 15ns */
    } reg;
} SOC_SCHARGER_OTG_REG7_UNION;
#endif
#define SOC_SCHARGER_OTG_REG7_otg_dmd_ofs_START  (0)
#define SOC_SCHARGER_OTG_REG7_otg_dmd_ofs_END    (3)
#define SOC_SCHARGER_OTG_REG7_otg_rf_START       (4)
#define SOC_SCHARGER_OTG_REG7_otg_rf_END         (5)
#define SOC_SCHARGER_OTG_REG7_otg_ckmin_START    (6)
#define SOC_SCHARGER_OTG_REG7_otg_ckmin_END      (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG8_UNION
 结构说明  : OTG_REG8 寄存器结构定义。地址偏移量:0x45，初值:0x81，宽度:8
 寄存器说明: OTG_REG8调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_vo        : 2;  /* bit[0-1]: OTG输出电压微调
                                                        00: 
                                                        01: 
                                                        10: 
                                                        11:  */
        unsigned char  otg_vbat_time : 2;  /* bit[2-3]: OTG启动电池电压去抖时间（ms）
                                                        00: 16
                                                        01: 32
                                                        10: 64
                                                        11: 128 */
        unsigned char  otg_vbat      : 4;  /* bit[4-7]: OTG启动电池电压(V) 0000: 2.8
                                                        0001: 2.9
                                                        0010: 3.0
                                                        0011: 3.1
                                                        0100: 3.2
                                                        0101: 3.3
                                                        0110: 3.4
                                                        0111: 3.5
                                                        1000: 3.6
                                                        1001: 3.7
                                                        1010-1111: 3.8 */
    } reg;
} SOC_SCHARGER_OTG_REG8_UNION;
#endif
#define SOC_SCHARGER_OTG_REG8_otg_vo_START         (0)
#define SOC_SCHARGER_OTG_REG8_otg_vo_END           (1)
#define SOC_SCHARGER_OTG_REG8_otg_vbat_time_START  (2)
#define SOC_SCHARGER_OTG_REG8_otg_vbat_time_END    (3)
#define SOC_SCHARGER_OTG_REG8_otg_vbat_START       (4)
#define SOC_SCHARGER_OTG_REG8_otg_vbat_END         (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG9_UNION
 结构说明  : OTG_REG9 寄存器结构定义。地址偏移量:0x46，初值:0x05，宽度:8
 寄存器说明: OTG_REG9调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_delay2 : 2;  /* bit[0-1]: OTG内部延时调整
                                                     00: 
                                                     01: 
                                                     10: 
                                                     11:  */
        unsigned char  otg_delay1 : 2;  /* bit[2-3]: OTG内部延时调整
                                                     00: 
                                                     01: 
                                                     10: 
                                                     11:  */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留 */
    } reg;
} SOC_SCHARGER_OTG_REG9_UNION;
#endif
#define SOC_SCHARGER_OTG_REG9_otg_delay2_START  (0)
#define SOC_SCHARGER_OTG_REG9_otg_delay2_END    (1)
#define SOC_SCHARGER_OTG_REG9_otg_delay1_START  (2)
#define SOC_SCHARGER_OTG_REG9_otg_delay1_END    (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG10_UNION
 结构说明  : OTG_REG10 寄存器结构定义。地址偏移量:0x47，初值:0x00，宽度:8
 寄存器说明: OTG_REG10调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_resved : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_OTG_REG10_UNION;
#endif
#define SOC_SCHARGER_OTG_REG10_otg_resved_START  (0)
#define SOC_SCHARGER_OTG_REG10_otg_resved_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG0_UNION
 结构说明  : CHG_REG0 寄存器结构定义。地址偏移量:0x48，初值:0x14，宽度:8
 寄存器说明: CHG_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_pre_vchg : 2;  /* bit[0-1]: 预充电电压阈值大小调节位
                                                       00: 2.8V
                                                       01: 3.0V
                                                       10: 3.1V
                                                       11: 3.2V */
        unsigned char  chg_pre_ichg : 2;  /* bit[2-3]: 预充电电流大小调节位
                                                       00: 100mA
                                                       01: 200mA
                                                       10: 300mA
                                                       11: 400mA */
        unsigned char  batfet_ctrl  : 1;  /* bit[4]  : 充电管控制寄存器
                                                       该寄存器除了受到pwr_rst_n复位，soft_rst_n复位，en_bst_in复位外，还受到模拟送给数字另外一个信号dc_rst_n复位：
                                                       0：关闭batfet;
                                                       1：打开batfet; */
        unsigned char  reserved     : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG0_UNION;
#endif
#define SOC_SCHARGER_CHG_REG0_chg_pre_vchg_START  (0)
#define SOC_SCHARGER_CHG_REG0_chg_pre_vchg_END    (1)
#define SOC_SCHARGER_CHG_REG0_chg_pre_ichg_START  (2)
#define SOC_SCHARGER_CHG_REG0_chg_pre_ichg_END    (3)
#define SOC_SCHARGER_CHG_REG0_batfet_ctrl_START   (4)
#define SOC_SCHARGER_CHG_REG0_batfet_ctrl_END     (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG1_UNION
 结构说明  : CHG_REG1 寄存器结构定义。地址偏移量:0x49，初值:0x13，宽度:8
 寄存器说明: CHG_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_fast_ichg : 5;  /* bit[0-4]: 快充电电流大小调节位
                                                        00000: 100mA
                                                        00001: 200mA
                                                        00010: 300mA
                                                        00011: 400mA
                                                        00100: 500mA
                                                        00101: 600mA
                                                        00110: 700mA
                                                        00111: 800mA
                                                        01000: 900mA
                                                        01001: 1000mA
                                                        01010: 1100mA
                                                        01011: 1200mA
                                                        01100: 1300mA
                                                        01101: 1400mA
                                                        01110: 1500mA
                                                        01111: 1600mA
                                                        10000: 1700mA
                                                        10001: 1800mA
                                                        10010: 1900mA
                                                        10011: 2000mA
                                                        10100: 2000mA
                                                         ～ ～
                                                        11111: 2000mA */
        unsigned char  reserved      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG1_UNION;
#endif
#define SOC_SCHARGER_CHG_REG1_chg_fast_ichg_START  (0)
#define SOC_SCHARGER_CHG_REG1_chg_fast_ichg_END    (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG2_UNION
 结构说明  : CHG_REG2 寄存器结构定义。地址偏移量:0x4A，初值:0x22，宽度:8
 寄存器说明: CHG_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_term_ichg : 2;  /* bit[0-1]: 终止充电电流阈值调节位
                                                        00: 50mA
                                                        01: 100mA
                                                        10: 150mA
                                                        11: 200mA */
        unsigned char  chg_fast_vchg : 4;  /* bit[2-5]: 快充电完成电压阈值大小调节位
                                                        0000: 3.8V
                                                        0001: 3.85V
                                                        0010: 3.9V
                                                        0011: 3.95V
                                                        0100: 4V
                                                        0101: 4.05V
                                                        0110: 4.1V
                                                        0111: 4.15V
                                                        1000：4.2
                                                        1001: 4.25
                                                        1010: 4.3
                                                        1011:4.35
                                                        1100:4.4
                                                        1101:4.45
                                                        1110:4.5
                                                        1111:4.55 */
        unsigned char  reserved      : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG2_UNION;
#endif
#define SOC_SCHARGER_CHG_REG2_chg_term_ichg_START  (0)
#define SOC_SCHARGER_CHG_REG2_chg_term_ichg_END    (1)
#define SOC_SCHARGER_CHG_REG2_chg_fast_vchg_START  (2)
#define SOC_SCHARGER_CHG_REG2_chg_fast_vchg_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG3_UNION
 结构说明  : CHG_REG3 寄存器结构定义。地址偏移量:0x4B，初值:0x18，宽度:8
 寄存器说明: CHG_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_prechg_timer : 2;  /* bit[0-1]: 预充电计时器（分钟）
                                                           00: 30min
                                                           01: 45min
                                                           10: 60min
                                                           11: 75min */
        unsigned char  chg_rechg_time   : 2;  /* bit[2-3]: 重新充电模式去抖时间设置位
                                                           00: 0.1s
                                                           01: 1s
                                                           10: 2s
                                                           11: 4s */
        unsigned char  chg_vrechg_hys   : 3;  /* bit[4-6]: 重新充电回滞电压调节位
                                                           000: 50mV
                                                           001: 100mV
                                                           010: 150mV
                                                           011: 200mV
                                                           100: 250mV
                                                           101: 300mV
                                                           110: 350mV
                                                           111: 400mV */
        unsigned char  reserved         : 1;  /* bit[7]  :  */
    } reg;
} SOC_SCHARGER_CHG_REG3_UNION;
#endif
#define SOC_SCHARGER_CHG_REG3_chg_prechg_timer_START  (0)
#define SOC_SCHARGER_CHG_REG3_chg_prechg_timer_END    (1)
#define SOC_SCHARGER_CHG_REG3_chg_rechg_time_START    (2)
#define SOC_SCHARGER_CHG_REG3_chg_rechg_time_END      (3)
#define SOC_SCHARGER_CHG_REG3_chg_vrechg_hys_START    (4)
#define SOC_SCHARGER_CHG_REG3_chg_vrechg_hys_END      (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG4_UNION
 结构说明  : CHG_REG4 寄存器结构定义。地址偏移量:0x4C，初值:0x47，宽度:8
 寄存器说明: CHG_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_vbatir_adj         : 4;  /* bit[0-3]: IR跟随电压调节位
                                                                 0000: 10mV
                                                                 0001: 20mV
                                                                 0010: 30mV
                                                                 0011: 40mV
                                                                 0100: 50mV
                                                                 0101: 60mV
                                                                 0110: 70mV
                                                                 0111: 80mV
                                                                 1000: 90mV
                                                                 1001: 100mV
                                                                 1010: 110mV
                                                                 1011: 120mV
                                                                 1100: 130mV
                                                                 1101: 140mV
                                                                 1110: 150mV
                                                                 1111: 160mV */
        unsigned char  chg_fastchg_safe_timer : 2;  /* bit[4-5]: 快充安全计时器（小时）
                                                                 00: 5 h
                                                                 01: 8 h
                                                                 10: 12 h
                                                                 11: 20 h */
        unsigned char  chg_termination_ctrl   : 1;  /* bit[6]  : 终止充电控制位
                                                                 0: Disabled
                                                                 1: Enabled */
        unsigned char  reserved               : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_CHG_REG4_UNION;
#endif
#define SOC_SCHARGER_CHG_REG4_chg_vbatir_adj_START          (0)
#define SOC_SCHARGER_CHG_REG4_chg_vbatir_adj_END            (3)
#define SOC_SCHARGER_CHG_REG4_chg_fastchg_safe_timer_START  (4)
#define SOC_SCHARGER_CHG_REG4_chg_fastchg_safe_timer_END    (5)
#define SOC_SCHARGER_CHG_REG4_chg_termination_ctrl_START    (6)
#define SOC_SCHARGER_CHG_REG4_chg_termination_ctrl_END      (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG5_UNION
 结构说明  : CHG_REG5 寄存器结构定义。地址偏移量:0x4D，初值:0x2A，宽度:8
 寄存器说明: CHG_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_hot_hsys  : 2;  /* bit[0-1]: 电池过热检测的回滞温度调整
                                                        00：1%
                                                        01：2%
                                                        10：3%
                                                        11：4% */
        unsigned char  chg_cold_hsys : 2;  /* bit[2-3]: 电池过冷检测的回滞温度调整
                                                        00：1%
                                                        01：2%
                                                        10：3%
                                                        11：4% */
        unsigned char  chg_smhys_adj : 3;  /* bit[4-6]: BATFET forward voltage调节位
                                                        000: 11.35mV
                                                        001: 22.7mV
                                                        010: 34.05mV
                                                        011: 45.4mV
                                                        100: 56.75mV
                                                        101: 68.1mV
                                                        110: 79.45mV
                                                        111: 90.8mV */
        unsigned char  reserved      : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG5_UNION;
#endif
#define SOC_SCHARGER_CHG_REG5_chg_hot_hsys_START   (0)
#define SOC_SCHARGER_CHG_REG5_chg_hot_hsys_END     (1)
#define SOC_SCHARGER_CHG_REG5_chg_cold_hsys_START  (2)
#define SOC_SCHARGER_CHG_REG5_chg_cold_hsys_END    (3)
#define SOC_SCHARGER_CHG_REG5_chg_smhys_adj_START  (4)
#define SOC_SCHARGER_CHG_REG5_chg_smhys_adj_END    (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG6_UNION
 结构说明  : CHG_REG6 寄存器结构定义。地址偏移量:0x4E，初值:0x00，宽度:8
 寄存器说明: CHG_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  therm_state        : 1;  /* bit[0]  : 系统热调整状态记录寄存器
                                                             0：Normal 
                                                             1：In Thermal Regulation */
        unsigned char  wled_ovp_ifb_state : 2;  /* bit[1-2]: 当Vifb>4.5V,上报过压时，可以查询IFB1和IFB2具体是哪一路
                                                             过压。
                                                             00: 正常
                                                             01: IFB1过压 
                                                             10:IFB2过压 
                                                             11：两路都过压 */
        unsigned char  buck_ok            : 1;  /* bit[3]  : 表征buck是否启动
                                                             0:没有启动
                                                             1:启动 */
        unsigned char  reserved           : 4;  /* bit[4-7]: 保留 */
    } reg;
} SOC_SCHARGER_CHG_REG6_UNION;
#endif
#define SOC_SCHARGER_CHG_REG6_therm_state_START         (0)
#define SOC_SCHARGER_CHG_REG6_therm_state_END           (0)
#define SOC_SCHARGER_CHG_REG6_wled_ovp_ifb_state_START  (1)
#define SOC_SCHARGER_CHG_REG6_wled_ovp_ifb_state_END    (2)
#define SOC_SCHARGER_CHG_REG6_buck_ok_START             (3)
#define SOC_SCHARGER_CHG_REG6_buck_ok_END               (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG7_UNION
 结构说明  : CHG_REG7 寄存器结构定义。地址偏移量:0x4F，初值:0x03，宽度:8
 寄存器说明: CHG_REG7调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_clk_ctl1 : 1;  /* bit[0]  : 充电计时器使能
                                                       0：关断计时器
                                                       1：计时器工作 */
        unsigned char  ts_ctrl      : 1;  /* bit[1]  : 控制电池温度检测模块：
                                                       1：开启
                                                       0：关闭 */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留 */
    } reg;
} SOC_SCHARGER_CHG_REG7_UNION;
#endif
#define SOC_SCHARGER_CHG_REG7_chg_clk_ctl1_START  (0)
#define SOC_SCHARGER_CHG_REG7_chg_clk_ctl1_END    (0)
#define SOC_SCHARGER_CHG_REG7_ts_ctrl_START       (1)
#define SOC_SCHARGER_CHG_REG7_ts_ctrl_END         (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG8_UNION
 结构说明  : CHG_REG8 寄存器结构定义。地址偏移量:0x50，初值:0x00，宽度:8
 寄存器说明: CHG_REG8调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvi1_2d : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_CHG_REG8_UNION;
#endif
#define SOC_SCHARGER_CHG_REG8_chg_resvi1_2d_START  (0)
#define SOC_SCHARGER_CHG_REG8_chg_resvi1_2d_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG9_UNION
 结构说明  : CHG_REG9 寄存器结构定义。地址偏移量:0x51，初值:0x00，宽度:8
 寄存器说明: CHG_REG9调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvi2_2d : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_CHG_REG9_UNION;
#endif
#define SOC_SCHARGER_CHG_REG9_chg_resvi2_2d_START  (0)
#define SOC_SCHARGER_CHG_REG9_chg_resvi2_2d_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG10_UNION
 结构说明  : CHG_REG10 寄存器结构定义。地址偏移量:0x52，初值:0x00，宽度:8
 寄存器说明: CHG_REG10调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvo1 : 8;  /* bit[0-7]: 预留寄存器
                                                     chg_resvo1<0>为系统电池不在位检测控制寄存器，若SOC检测到电池不在位则SOC把chg_resvo1<0>写“1”，否则为“0”。
                                                     chg_resvo1<0>=“1”电池不在位；
                                                     chg_resvo1<0>=“0”电池在位； */
    } reg;
} SOC_SCHARGER_CHG_REG10_UNION;
#endif
#define SOC_SCHARGER_CHG_REG10_chg_resvo1_START  (0)
#define SOC_SCHARGER_CHG_REG10_chg_resvo1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG11_UNION
 结构说明  : CHG_REG11 寄存器结构定义。地址偏移量:0x53，初值:0x00，宽度:8
 寄存器说明: CHG_REG11调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvo2 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_CHG_REG11_UNION;
#endif
#define SOC_SCHARGER_CHG_REG11_chg_resvo2_START  (0)
#define SOC_SCHARGER_CHG_REG11_chg_resvo2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_PSEL_REG0_UNION
 结构说明  : PSEL_REG0 寄存器结构定义。地址偏移量:0x54，初值:0x09，宽度:8
 寄存器说明: PSEL_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  vbus_ovp_uptime : 2;  /* bit[0-1]: vbus过压上升沿去抖时间配置位
                                                          00: 0ms
                                                          01: 1ms
                                                          10: 2ms
                                                          11: 4ms */
        unsigned char  regn_lv_sel     : 2;  /* bit[2-3]: 低压REGN输出电压选择位
                                                          00:3.1V
                                                          01:3.2V
                                                          10:3.3V
                                                          11:3.4V */
        unsigned char  reserved        : 4;  /* bit[4-7]: 保留 */
    } reg;
} SOC_SCHARGER_PSEL_REG0_UNION;
#endif
#define SOC_SCHARGER_PSEL_REG0_vbus_ovp_uptime_START  (0)
#define SOC_SCHARGER_PSEL_REG0_vbus_ovp_uptime_END    (1)
#define SOC_SCHARGER_PSEL_REG0_regn_lv_sel_START      (2)
#define SOC_SCHARGER_PSEL_REG0_regn_lv_sel_END        (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG0_UNION
 结构说明  : FLASH_BST_REG0 寄存器结构定义。地址偏移量:0x55，初值:0x00，宽度:8
 寄存器说明: FLASH_BST_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0       : 5;  /* bit[0-4]: 保留，配置无用。 */
        unsigned char  flash_bst_pm_cut : 1;  /* bit[5]  : 1: PMOS强行关闭
                                                           0: PMOS不被此寄存器控制 */
        unsigned char  flash_bst_pm_th  : 1;  /* bit[6]  : 1: PMOS强行直通，所有内部电路关闭
                                                           0: PMOS不被此寄存器控制 */
        unsigned char  reserved_1       : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG0_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG0_flash_bst_pm_cut_START  (5)
#define SOC_SCHARGER_FLASH_BST_REG0_flash_bst_pm_cut_END    (5)
#define SOC_SCHARGER_FLASH_BST_REG0_flash_bst_pm_th_START   (6)
#define SOC_SCHARGER_FLASH_BST_REG0_flash_bst_pm_th_END     (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG1_UNION
 结构说明  : FLASH_BST_REG1 寄存器结构定义。地址偏移量:0x56，初值:0x1E，宽度:8
 寄存器说明: FLASH_BST_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_sel_scp : 1;  /* bit[0]  : 1: 2ms内VOUT不足0.85BAT，上报短路
                                                            0: 1ms内VOUT不足0.85BAT，上报短路 */
        unsigned char  flash_bst_en_uvp  : 1;  /* bit[1]  : en_uvp 
                                                            1: 使能欠压电路
                                                            0: 关闭过压电路（不上报） */
        unsigned char  flash_bst_en_scp  : 1;  /* bit[2]  : 1: 使能短路系统自动关闭
                                                            0: 关闭短路系统自动关闭（仍上报） */
        unsigned char  flash_bst_en_ovp  : 1;  /* bit[3]  : 1: 使能过压电路
                                                            0: 关闭过压电路（不上报） */
        unsigned char  flash_bst_en_ocp  : 1;  /* bit[4]  : 1: 使能过流环路控制，并且上报
                                                            0: 使能过流环路控制，不上报 */
        unsigned char  reserved_0        : 1;  /* bit[5]  : 保留，配置无用。 */
        unsigned char  reserved_1        : 2;  /* bit[6-7]: 保留 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG1_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_sel_scp_START  (0)
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_sel_scp_END    (0)
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_en_uvp_START   (1)
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_en_uvp_END     (1)
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_en_scp_START   (2)
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_en_scp_END     (2)
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_en_ovp_START   (3)
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_en_ovp_END     (3)
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_en_ocp_START   (4)
#define SOC_SCHARGER_FLASH_BST_REG1_flash_bst_en_ocp_END     (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG2_UNION
 结构说明  : FLASH_BST_REG2 寄存器结构定义。地址偏移量:0x57，初值:0x07，宽度:8
 寄存器说明: FLASH_BST_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_en_dmd    : 1;  /* bit[0]  : 1: 使能过零检测
                                                              0: 关闭过零检测 */
        unsigned char  flash_bst_en_slop   : 1;  /* bit[1]  : 1: 使能斜坡补偿
                                                              0: 关闭斜坡补偿 */
        unsigned char  flash_bst_en_clp_os : 1;  /* bit[2]  : 1: 使能钳位电路失调电压
                                                              0: 关闭钳位电路失调电压 */
        unsigned char  flash_bst_en_nring  : 1;  /* bit[3]  : 1: 使能防振铃
                                                              0: 关闭短振铃 */
        unsigned char  flash_bst_en_pfm    : 1;  /* bit[4]  : 1: 使能输出电压方式的PFM模式
                                                              0: 关闭输出电压方式的PFM模式 */
        unsigned char  flash_bst_drv_mode  : 1;  /* bit[5]  : 1: 传统死区检测模式
                                                              0: 最小死区模式 */
        unsigned char  reserved            : 2;  /* bit[6-7]: 保留 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG2_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_dmd_START     (0)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_dmd_END       (0)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_slop_START    (1)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_slop_END      (1)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_clp_os_START  (2)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_clp_os_END    (2)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_nring_START   (3)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_nring_END     (3)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_pfm_START     (4)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_en_pfm_END       (4)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_drv_mode_START   (5)
#define SOC_SCHARGER_FLASH_BST_REG2_flash_bst_drv_mode_END     (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG3_UNION
 结构说明  : FLASH_BST_REG3 寄存器结构定义。地址偏移量:0x58，初值:0x6B，宽度:8
 寄存器说明: FLASH_BST_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_clp   : 3;  /* bit[0-2]: EA输出钳位值和VRAMP直流电平值的失调
                                                          000: 8mV
                                                          001: 12mV
                                                          010: 16mV
                                                          011: 20mV
                                                          100: 24mV
                                                          101: 28mV
                                                          110: 32mV
                                                          111: 36mV */
        unsigned char  flash_bst_itail : 1;  /* bit[3]  : EA输出级静态电流控制
                                                          1:5.5uA
                                                          0:2.5uA */
        unsigned char  flash_bst_gm    : 3;  /* bit[4-6]: EA中gm电阻设定(gm=2/R)。
                                                          000: 90kΩ；
                                                          001: 80kΩ；
                                                          010: 70kΩ；
                                                          011: 60kΩ；
                                                          100: 40kΩ；
                                                          101: 30kΩ；
                                                          110: 20kΩ；
                                                          111: 10kΩ。 */
        unsigned char  reserved        : 1;  /* bit[7]  : 保留，配置无用。 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG3_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG3_flash_bst_clp_START    (0)
#define SOC_SCHARGER_FLASH_BST_REG3_flash_bst_clp_END      (2)
#define SOC_SCHARGER_FLASH_BST_REG3_flash_bst_itail_START  (3)
#define SOC_SCHARGER_FLASH_BST_REG3_flash_bst_itail_END    (3)
#define SOC_SCHARGER_FLASH_BST_REG3_flash_bst_gm_START     (4)
#define SOC_SCHARGER_FLASH_BST_REG3_flash_bst_gm_END       (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG4_UNION
 结构说明  : FLASH_BST_REG4 寄存器结构定义。地址偏移量:0x59，初值:0x28，宽度:8
 寄存器说明: FLASH_BST_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_ccom2 : 2;  /* bit[0-1]: EA输出滤波电容。
                                                          00: 0.65pF；
                                                          01: 1.3pF；
                                                          10: 1.95pF；
                                                          11: 3.9pF。 */
        unsigned char  flash_bst_ccom1 : 2;  /* bit[2-3]: 主环路补偿电容。
                                                          00: 20pF；
                                                          01: 40pF；
                                                          10: 60pF；
                                                          11: 80pF。 */
        unsigned char  flash_bst_rcom  : 3;  /* bit[4-6]: 主环路补偿电阻
                                                          000: 520kΩ
                                                          001: 440kΩ
                                                          010: 360kΩ
                                                          011: 280kΩ
                                                          100:200kΩ
                                                          101:160kΩ
                                                          110:120kΩ
                                                          111:80kΩ */
        unsigned char  reserved        : 1;  /* bit[7]  : 保留，配置无用。 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG4_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG4_flash_bst_ccom2_START  (0)
#define SOC_SCHARGER_FLASH_BST_REG4_flash_bst_ccom2_END    (1)
#define SOC_SCHARGER_FLASH_BST_REG4_flash_bst_ccom1_START  (2)
#define SOC_SCHARGER_FLASH_BST_REG4_flash_bst_ccom1_END    (3)
#define SOC_SCHARGER_FLASH_BST_REG4_flash_bst_rcom_START   (4)
#define SOC_SCHARGER_FLASH_BST_REG4_flash_bst_rcom_END     (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG5_UNION
 结构说明  : FLASH_BST_REG5 寄存器结构定义。地址偏移量:0x5A，初值:0x0A，宽度:8
 寄存器说明: FLASH_BST_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_slop : 2;  /* bit[0-1]: 斜坡补偿斜率调节（电容调节）。
                                                         00: 1.2pF；
                                                         01: 1.6pF；
                                                         10: 2.4pF；
                                                         11: 5.1pF。 */
        unsigned char  flash_bst_ri   : 2;  /* bit[2-3]: 电感电流转电压阻抗
                                                         00: 0.75Ω（实际120kΩ）
                                                         01: 0.625Ω（实际100kΩ）
                                                         10: 0.5Ω（实际80kΩ）
                                                         11: 0.375Ω（实际60kΩ） */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留，配置无用。 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG5_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG5_flash_bst_slop_START  (0)
#define SOC_SCHARGER_FLASH_BST_REG5_flash_bst_slop_END    (1)
#define SOC_SCHARGER_FLASH_BST_REG5_flash_bst_ri_START    (2)
#define SOC_SCHARGER_FLASH_BST_REG5_flash_bst_ri_END      (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG6_UNION
 结构说明  : FLASH_BST_REG6 寄存器结构定义。地址偏移量:0x5B，初值:0x55，宽度:8
 寄存器说明: FLASH_BST_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_nsn : 2;  /* bit[0-1]: NMOS栅控电压下降斜率
                                                        00: 67ns
                                                        01: 35ns
                                                        10: 25ns
                                                        11: 11ns */
        unsigned char  flash_bst_nsp : 2;  /* bit[2-3]: NMOS栅控电压上升斜率
                                                        00: 50ns
                                                        01: 33ns
                                                        10: 23ns
                                                        11: 11ns */
        unsigned char  flash_bst_psn : 2;  /* bit[4-5]: PMOS栅控电压下降斜率
                                                        00:10ns
                                                        01: 6ns
                                                        10: 4ns
                                                        11:3ns */
        unsigned char  flash_bst_psp : 2;  /* bit[6-7]: PMOS栅控电压上升斜率
                                                        00: 10ns
                                                        01: 6ns
                                                        10: 4ns
                                                        11: 2ns */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG6_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG6_flash_bst_nsn_START  (0)
#define SOC_SCHARGER_FLASH_BST_REG6_flash_bst_nsn_END    (1)
#define SOC_SCHARGER_FLASH_BST_REG6_flash_bst_nsp_START  (2)
#define SOC_SCHARGER_FLASH_BST_REG6_flash_bst_nsp_END    (3)
#define SOC_SCHARGER_FLASH_BST_REG6_flash_bst_psn_START  (4)
#define SOC_SCHARGER_FLASH_BST_REG6_flash_bst_psn_END    (5)
#define SOC_SCHARGER_FLASH_BST_REG6_flash_bst_psp_START  (6)
#define SOC_SCHARGER_FLASH_BST_REG6_flash_bst_psp_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG7_UNION
 结构说明  : FLASH_BST_REG7 寄存器结构定义。地址偏移量:0x5C，初值:0x10，宽度:8
 寄存器说明: FLASH_BST_REG7调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_dt_nm : 2;  /* bit[0-1]: NMOS关闭后开启PMOS的延时
                                                          00: 0
                                                          01: 2ns
                                                          10: 4ns
                                                          11: 6ns */
        unsigned char  flash_bst_dt_pm : 2;  /* bit[2-3]: PMOS关闭后开启NMOS的延时
                                                          00: 0
                                                          01: 2ns
                                                          10: 4ns
                                                          11: 6ns */
        unsigned char  flash_bst_lxde  : 2;  /* bit[4-5]: 判定开启PMOS，LX判断电路保留寄存器
                                                          LXDE<1>：保留
                                                          LXDE<0>
                                                          1：开启DMD关断逻辑
                                                          0：关闭DMD关断逻辑（即DMD之后有漏电） */
        unsigned char  reserved        : 2;  /* bit[6-7]: 保留，配置无用。 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG7_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG7_flash_bst_dt_nm_START  (0)
#define SOC_SCHARGER_FLASH_BST_REG7_flash_bst_dt_nm_END    (1)
#define SOC_SCHARGER_FLASH_BST_REG7_flash_bst_dt_pm_START  (2)
#define SOC_SCHARGER_FLASH_BST_REG7_flash_bst_dt_pm_END    (3)
#define SOC_SCHARGER_FLASH_BST_REG7_flash_bst_lxde_START   (4)
#define SOC_SCHARGER_FLASH_BST_REG7_flash_bst_lxde_END     (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG8_UNION
 结构说明  : FLASH_BST_REG8 寄存器结构定义。地址偏移量:0x5D，初值:0x16，宽度:8
 寄存器说明: FLASH_BST_REG8调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_ckmin : 2;  /* bit[0-1]: NMOS最小导通时间
                                                          00: 160ns
                                                          01: 120ns
                                                          10: 80ns
                                                          11: 40ns */
        unsigned char  flash_bst_osc   : 4;  /* bit[2-5]: 开关频率（MHz）
                                                          0000: 2.991
                                                          0001: 2.852
                                                          0010: 2.712
                                                          0011: 2.568
                                                          0100: 2.423
                                                          0101: 2.274
                                                          0110: 2.122
                                                          0111: 1.968
                                                          1000: 1.813
                                                          1001: 1.654
                                                          1010: 1.492
                                                          1011: 1.325
                                                          1100: 1.155
                                                          1101: 0.981
                                                          1110: 0.802
                                                          1111: 0.617 */
        unsigned char  reserved        : 2;  /* bit[6-7]: 保留，配置无用。 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG8_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG8_flash_bst_ckmin_START  (0)
#define SOC_SCHARGER_FLASH_BST_REG8_flash_bst_ckmin_END    (1)
#define SOC_SCHARGER_FLASH_BST_REG8_flash_bst_osc_START    (2)
#define SOC_SCHARGER_FLASH_BST_REG8_flash_bst_osc_END      (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG9_UNION
 结构说明  : FLASH_BST_REG9 寄存器结构定义。地址偏移量:0x5E，初值:0x0D，宽度:8
 寄存器说明: FLASH_BST_REG9调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_sel_ocp : 2;  /* bit[0-1]: NMOS限流值。
                                                            00: 3.4A；
                                                            01: 4.4A；
                                                            10: 5.4A；
                                                            11: 6.4A。 */
        unsigned char  flash_bst_start   : 3;  /* bit[2-4]: PMOS直通时栅电流控制（影响启动时间和短路电流）。
                                                            000: 0.5uA；
                                                            001: 0.75uA；
                                                            010: 1uA；
                                                            011: 1.25uA；
                                                            100: 1.5uA；
                                                            101: 1.75uA；
                                                            110: 2uA；
                                                            111: 2.5uA。 */
        unsigned char  reserved          : 3;  /* bit[5-7]: 保留，配置无用。 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG9_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG9_flash_bst_sel_ocp_START  (0)
#define SOC_SCHARGER_FLASH_BST_REG9_flash_bst_sel_ocp_END    (1)
#define SOC_SCHARGER_FLASH_BST_REG9_flash_bst_start_START    (2)
#define SOC_SCHARGER_FLASH_BST_REG9_flash_bst_start_END      (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG10_UNION
 结构说明  : FLASH_BST_REG10 寄存器结构定义。地址偏移量:0x5F，初值:0x05，宽度:8
 寄存器说明: FLASH_BST_REG10调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_vo       : 5;  /* bit[0-4]: 输出电压
                                                             00000: 5.5V
                                                             00001: 5.4V
                                                             00010: 5.3V
                                                             00011: 5.2V
                                                             00100: 5.1V
                                                             00101：5V
                                                             00110：4.9V
                                                             00111：4.8V
                                                             01000：4.7V
                                                             01001：4.6V
                                                             01010：4.5V
                                                             01011：4.4V
                                                             01100：4.3V
                                                             01101：4.2V
                                                             01110：4.1V
                                                             01111：4.0V
                                                             10000：3.9V
                                                             10001：3.8V
                                                             10010：3.7V
                                                             10011：3.6V
                                                             10100：3.5V
                                                             10101：3.4V
                                                             10110：3.3V
                                                             10111：3.2V
                                                             剩余编码不使用，若不慎配置，则保持当前电压档位 */
        unsigned char  flash_bst_dmd_isel : 1;  /* bit[5]  : DMD偏置电流选择。0：2uA固定电流；1：(vout-vin)/r采样电流 */
        unsigned char  reserved           : 2;  /* bit[6-7]: 保留，配置无用 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG10_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG10_flash_bst_vo_START        (0)
#define SOC_SCHARGER_FLASH_BST_REG10_flash_bst_vo_END          (4)
#define SOC_SCHARGER_FLASH_BST_REG10_flash_bst_dmd_isel_START  (5)
#define SOC_SCHARGER_FLASH_BST_REG10_flash_bst_dmd_isel_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_BST_REG11_UNION
 结构说明  : FLASH_BST_REG11 寄存器结构定义。地址偏移量:0x60，初值:0x09，宽度:8
 寄存器说明: FLASH_BST_REG11调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_bst_dmd_ofs : 4;  /* bit[0-3]: DMD失调
                                                            0000: 20mV (300mA)
                                                            0001: 16mV (240mA)
                                                            0010: 14mV (210mA)
                                                            0011: 12mV (180mA)
                                                            0100: 10mV (150mA)
                                                            0101: 8mV (120mA)
                                                            0110: 6mV (90mA)
                                                            0111: 4mV (60mA)
                                                            1000: 2mV (30mA)
                                                            1001:0
                                                            1010: -16mV (-180mA).
                                                            1011: -32mV (-360mA).
                                                            1100: -48mV (-540mA).
                                                            1101: -64mV (-720mA)..
                                                            1110: -128mV (-900mA).
                                                            1111: -256mV (-1080mA). */
        unsigned char  reserved          : 4;  /* bit[4-7]: 保留 */
    } reg;
} SOC_SCHARGER_FLASH_BST_REG11_UNION;
#endif
#define SOC_SCHARGER_FLASH_BST_REG11_flash_bst_dmd_ofs_START  (0)
#define SOC_SCHARGER_FLASH_BST_REG11_flash_bst_dmd_ofs_END    (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_LED_REG0_UNION
 结构说明  : FLASH_LED_REG0 寄存器结构定义。地址偏移量:0x61，初值:0x00，宽度:8
 寄存器说明: FLASH_LED_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_led_trimstep_sel  : 2;  /* bit[0-1]: led电流trim步长档位选择。
                                                                  00:0.5mV/step（default）
                                                                  01/10:1mV/step
                                                                  11:2mV/step */
        unsigned char  flash_led_ledfault_vsel : 2;  /* bit[2-3]: led open检测电压档位选择。
                                                                  00:3.8V（default）
                                                                  01:3.7V
                                                                  10:3.6V
                                                                  11:3.5V */
        unsigned char  flash_led_ledfault_en   : 1;  /* bit[4]  : led open/short功能使能控制：0：开启LED开短路检测。1：关闭LED开短路检测。 */
        unsigned char  reserved                : 3;  /* bit[5-7]: 保留 */
    } reg;
} SOC_SCHARGER_FLASH_LED_REG0_UNION;
#endif
#define SOC_SCHARGER_FLASH_LED_REG0_flash_led_trimstep_sel_START   (0)
#define SOC_SCHARGER_FLASH_LED_REG0_flash_led_trimstep_sel_END     (1)
#define SOC_SCHARGER_FLASH_LED_REG0_flash_led_ledfault_vsel_START  (2)
#define SOC_SCHARGER_FLASH_LED_REG0_flash_led_ledfault_vsel_END    (3)
#define SOC_SCHARGER_FLASH_LED_REG0_flash_led_ledfault_en_START    (4)
#define SOC_SCHARGER_FLASH_LED_REG0_flash_led_ledfault_en_END      (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_LED_REG1_UNION
 结构说明  : FLASH_LED_REG1 寄存器结构定义。地址偏移量:0x62，初值:0x38，宽度:8
 寄存器说明: FLASH_LED_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_led_vbatdroop : 3;  /* bit[0-2]: 设置电池电压droop检测档位
                                                              000 3.5
                                                              001 3.4
                                                              010 3.3
                                                              011 3.2
                                                              100 3.1
                                                              101 3.0
                                                              110 2.9
                                                              111 2.8 */
        unsigned char  flash_led_vbattorch : 4;  /* bit[3-6]: 设定vbat_torch门槛值电压，从3.2V~4.2V可调
                                                              0000 4.2
                                                              0001 4.1
                                                              0010 4.0
                                                              0011 3.9
                                                              0100 3.8
                                                              0101 3.7
                                                              0110 3.6
                                                              0111 3.5
                                                              1000 3.4
                                                              1001 3.3
                                                              1010 3.2
                                                              余下编码不使用，若不慎配置，则电压档位保持当前档位不变。 */
        unsigned char  reserved            : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_FLASH_LED_REG1_UNION;
#endif
#define SOC_SCHARGER_FLASH_LED_REG1_flash_led_vbatdroop_START  (0)
#define SOC_SCHARGER_FLASH_LED_REG1_flash_led_vbatdroop_END    (2)
#define SOC_SCHARGER_FLASH_LED_REG1_flash_led_vbattorch_START  (3)
#define SOC_SCHARGER_FLASH_LED_REG1_flash_led_vbattorch_END    (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SYS_REG_UNION
 结构说明  : SYS_REG 寄存器结构定义。地址偏移量:0x63，初值:0x00，宽度:8
 寄存器说明: SYS调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resv : 8;  /* bit[0-7]: 寄存器预留 */
    } reg;
} SOC_SCHARGER_SYS_REG_UNION;
#endif
#define SOC_SCHARGER_SYS_REG_sys_resv_START  (0)
#define SOC_SCHARGER_SYS_REG_sys_resv_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_LED_REG2_UNION
 结构说明  : FLASH_LED_REG2 寄存器结构定义。地址偏移量:0x64，初值:0x04，宽度:8
 寄存器说明: FLASH_LED_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_led_tbatdroop : 4;  /* bit[0-3]: 设置batdroop滤波时间档位
                                                              0000:2.5us
                                                              0001:5us
                                                              0010:10us
                                                              0011:20us
                                                              0100:40us
                                                              0101:80us
                                                              0110:160us
                                                              0111:320us
                                                              1000:640us
                                                              1001:800us
                                                              1010:1ms
                                                              1011:2ms
                                                              1100:4ms
                                                              1101:10ms
                                                              1110:20ms
                                                              1111:40ms */
        unsigned char  flash_led_tfault    : 3;  /* bit[4-6]: 设定flash_led open/short检测滤波时间
                                                              000:90us
                                                              001:360us
                                                              010:1ms
                                                              011:2ms
                                                              100:4ms
                                                              101:10ms
                                                              110:20ms
                                                              111:40ms */
        unsigned char  reserved            : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_FLASH_LED_REG2_UNION;
#endif
#define SOC_SCHARGER_FLASH_LED_REG2_flash_led_tbatdroop_START  (0)
#define SOC_SCHARGER_FLASH_LED_REG2_flash_led_tbatdroop_END    (3)
#define SOC_SCHARGER_FLASH_LED_REG2_flash_led_tfault_START     (4)
#define SOC_SCHARGER_FLASH_LED_REG2_flash_led_tfault_END       (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_LED_REG3_UNION
 结构说明  : FLASH_LED_REG3 寄存器结构定义。地址偏移量:0x65，初值:0x27，宽度:8
 寄存器说明: FLASH_LED_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_led_tf             : 3;  /* bit[0-2]: 设置ramp down单位步长时间
                                                                   000:10us 
                                                                   001:8us
                                                                   010:6us
                                                                   011:4us
                                                                   100:2us
                                                                   101:1.5us
                                                                   110:1us
                                                                   111:0.5us */
        unsigned char  flash_led_tr             : 3;  /* bit[3-5]: 设置ramp up单位步长时间
                                                                   000:80us 
                                                                   001:50us
                                                                   010:40us
                                                                   011:20us
                                                                   100:10us
                                                                   101:5us
                                                                   110:2.5us
                                                                   111:1.5us */
        unsigned char  flash_led_mask_mask      : 1;  /* bit[6]  : 1：屏蔽外部硬线TX_MASK信号；
                                                                   0：不屏蔽外部硬线TX_MASK信号  */
        unsigned char  flash_led_mask_once_down : 1;  /* bit[7]  : 1：发生vbatdrooph或TX_MASK时，电流立刻下降到目标值；
                                                                   0：发生vbatdrooph或TX_MASK时，电流用ramp down模式下降到目标值 */
    } reg;
} SOC_SCHARGER_FLASH_LED_REG3_UNION;
#endif
#define SOC_SCHARGER_FLASH_LED_REG3_flash_led_tf_START              (0)
#define SOC_SCHARGER_FLASH_LED_REG3_flash_led_tf_END                (2)
#define SOC_SCHARGER_FLASH_LED_REG3_flash_led_tr_START              (3)
#define SOC_SCHARGER_FLASH_LED_REG3_flash_led_tr_END                (5)
#define SOC_SCHARGER_FLASH_LED_REG3_flash_led_mask_mask_START       (6)
#define SOC_SCHARGER_FLASH_LED_REG3_flash_led_mask_mask_END         (6)
#define SOC_SCHARGER_FLASH_LED_REG3_flash_led_mask_once_down_START  (7)
#define SOC_SCHARGER_FLASH_LED_REG3_flash_led_mask_once_down_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_LED_REG4_UNION
 结构说明  : FLASH_LED_REG4 寄存器结构定义。地址偏移量:0x66，初值:0x3D，宽度:8
 寄存器说明: FLASH_LED_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_led_itorch_set : 3;  /* bit[0-2]: 设置torch mode电流档位
                                                               000:50mA
                                                               001:100mA
                                                               010:150mA
                                                               011:200mA
                                                               100：250mA
                                                               101：300mA
                                                               110:350mA
                                                               111:400mA */
        unsigned char  flash_led_iflash_set : 4;  /* bit[3-6]: 设置flash mode电流档位
                                                               0000:125mA
                                                               0001:250mA
                                                               0010:375mA
                                                               0011:500mA
                                                               0100:625mA
                                                               0101:750mA
                                                               0110:875mA
                                                               0111:1000mA
                                                               1000:1125mA
                                                               1001:1250mA
                                                               1010:1375mA
                                                               1011:1500mA
                                                               1100~1111:1500mA */
        unsigned char  reserved             : 1;  /* bit[7]  : 保留 */
    } reg;
} SOC_SCHARGER_FLASH_LED_REG4_UNION;
#endif
#define SOC_SCHARGER_FLASH_LED_REG4_flash_led_itorch_set_START  (0)
#define SOC_SCHARGER_FLASH_LED_REG4_flash_led_itorch_set_END    (2)
#define SOC_SCHARGER_FLASH_LED_REG4_flash_led_iflash_set_START  (3)
#define SOC_SCHARGER_FLASH_LED_REG4_flash_led_iflash_set_END    (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_LED_REG5_UNION
 结构说明  : FLASH_LED_REG5 寄存器结构定义。地址偏移量:0x67，初值:0x03，宽度:8
 寄存器说明: FLASH_LED_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_led_isafe_set : 3;  /* bit[0-2]: 设置安全电流档位
                                                              000:50mA
                                                              001:100mA
                                                              010:150mA
                                                              011:200mA
                                                              100:250mA
                                                              101:300mA
                                                              110:350mA
                                                              111:400mA */
        unsigned char  reserved            : 5;  /* bit[3-7]: 保留 */
    } reg;
} SOC_SCHARGER_FLASH_LED_REG5_UNION;
#endif
#define SOC_SCHARGER_FLASH_LED_REG5_flash_led_isafe_set_START  (0)
#define SOC_SCHARGER_FLASH_LED_REG5_flash_led_isafe_set_END    (2)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_LED_REG6_UNION
 结构说明  : FLASH_LED_REG6 寄存器结构定义。地址偏移量:0x68，初值:0x40，宽度:8
 寄存器说明: FLASH_LED_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_led_watchdog_timer : 4;  /* bit[0-3]: torch模式开启时间设置
                                                                   0000:flash_led_watchdog_timer功能关闭
                                                                   0001:2s
                                                                   0010:4s
                                                                   0011:6s
                                                                   …
                                                                   1111:30s
                                                                   每个step为2s */
        unsigned char  flash_led_timeout        : 2;  /* bit[4-5]: flash模式开启时间设置
                                                                   00:400ms
                                                                   01:600ms
                                                                   10:800ms
                                                                   11:1000ms */
        unsigned char  flash_led_tpwrsel        : 2;  /* bit[6-7]: 设定数字内部信号pwrsel_pre双沿滤波时间
                                                                   00:4ms
                                                                   01:10ms
                                                                   10:20ms
                                                                   11:40ms */
    } reg;
} SOC_SCHARGER_FLASH_LED_REG6_UNION;
#endif
#define SOC_SCHARGER_FLASH_LED_REG6_flash_led_watchdog_timer_START  (0)
#define SOC_SCHARGER_FLASH_LED_REG6_flash_led_watchdog_timer_END    (3)
#define SOC_SCHARGER_FLASH_LED_REG6_flash_led_timeout_START         (4)
#define SOC_SCHARGER_FLASH_LED_REG6_flash_led_timeout_END           (5)
#define SOC_SCHARGER_FLASH_LED_REG6_flash_led_tpwrsel_START         (6)
#define SOC_SCHARGER_FLASH_LED_REG6_flash_led_tpwrsel_END           (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FLASH_LED_REG7_UNION
 结构说明  : FLASH_LED_REG7 寄存器结构定义。地址偏移量:0x69，初值:0x0E，宽度:8
 寄存器说明: FLASH_LED_REG7调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  flash_led_timeout_en     : 1;  /* bit[0]  : Flash_led开启时间设置功能使能
                                                                   0：关闭timeout
                                                                   1：开启timeout */
        unsigned char  flash_led_open_autostop  : 1;  /* bit[1]  : 1：不屏蔽flash_led_open_r信号
                                                                   0：屏蔽flash_led_open_r信号 */
        unsigned char  flash_led_short_autostop : 1;  /* bit[2]  : 1：不屏蔽flash_led_short_r信号
                                                                   0：屏蔽flash_led_short_r信号 */
        unsigned char  flash_strobe_mask        : 1;  /* bit[3]  : 1：不屏蔽外部硬线STROBE信号
                                                                   0：屏蔽外部硬线STROBE信号 */
        unsigned char  reserved                 : 4;  /* bit[4-7]: 保留 */
    } reg;
} SOC_SCHARGER_FLASH_LED_REG7_UNION;
#endif
#define SOC_SCHARGER_FLASH_LED_REG7_flash_led_timeout_en_START      (0)
#define SOC_SCHARGER_FLASH_LED_REG7_flash_led_timeout_en_END        (0)
#define SOC_SCHARGER_FLASH_LED_REG7_flash_led_open_autostop_START   (1)
#define SOC_SCHARGER_FLASH_LED_REG7_flash_led_open_autostop_END     (1)
#define SOC_SCHARGER_FLASH_LED_REG7_flash_led_short_autostop_START  (2)
#define SOC_SCHARGER_FLASH_LED_REG7_flash_led_short_autostop_END    (2)
#define SOC_SCHARGER_FLASH_LED_REG7_flash_strobe_mask_START         (3)
#define SOC_SCHARGER_FLASH_LED_REG7_flash_strobe_mask_END           (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CTRL_REG_UNION
 结构说明  : CTRL_REG 寄存器结构定义。地址偏移量:0x6A，初值:0x00，宽度:8
 寄存器说明: CTRL_REG调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_rst_n       : 1;  /* bit[0]  : 控制对所有寄存器的复位(写1后，自动清零)
                                                           0：正常
                                                           1：所有寄存器复位 */
        unsigned char  wd_rst_n         : 1;  /* bit[1]  : 写1该寄存器，系统watchdog timer计数重新计时(写1后，自动清零)
                                                           如果SoC在设置时间内不对该寄存器写‘1’操作，则复位chg_en_int和watchdog_timer寄存器 */
        unsigned char  flash_led_wd_rst : 1;  /* bit[2]  : torch watchdog timer计时清0使能信号(写1后，自动清零)
                                                           0：normal计时
                                                           1：torch watchdog timer 计时清零 */
        unsigned char  reserved         : 5;  /* bit[3-7]: 保留 */
    } reg;
} SOC_SCHARGER_CTRL_REG_UNION;
#endif
#define SOC_SCHARGER_CTRL_REG_soft_rst_n_START        (0)
#define SOC_SCHARGER_CTRL_REG_soft_rst_n_END          (0)
#define SOC_SCHARGER_CTRL_REG_wd_rst_n_START          (1)
#define SOC_SCHARGER_CTRL_REG_wd_rst_n_END            (1)
#define SOC_SCHARGER_CTRL_REG_flash_led_wd_rst_START  (2)
#define SOC_SCHARGER_CTRL_REG_flash_led_wd_rst_END    (2)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SYS_SET_REG_UNION
 结构说明  : SYS_SET_REG 寄存器结构定义。地址偏移量:0x6B，初值:0x00，宽度:8
 寄存器说明: SYS_SET_REG调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  watchdog_timer : 2;  /* bit[0-1]: SOC每隔一定时间对V200进行一次寄存器写操作；如果没有写操作事件发生，则进入Default模式，复位chg_en_int和watchdog_timer寄存器；否则是正常的Host模式。
                                                         系统watchdog_timer时间设置：
                                                         00：系统watchdog_timer功能屏蔽
                                                         01：10s
                                                         10:20s
                                                         11:40s  */
        unsigned char  reserved       : 6;  /* bit[2-7]: 保留 */
    } reg;
} SOC_SCHARGER_SYS_SET_REG_UNION;
#endif
#define SOC_SCHARGER_SYS_SET_REG_watchdog_timer_START  (0)
#define SOC_SCHARGER_SYS_SET_REG_watchdog_timer_END    (1)






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

#endif /* end of soc_scharger_interface.h */
