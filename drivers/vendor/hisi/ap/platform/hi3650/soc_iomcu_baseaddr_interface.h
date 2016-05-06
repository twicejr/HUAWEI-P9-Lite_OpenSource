/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_iomcu_baseaddr_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-23 11:53:37
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月23日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_IOMCU_BaseAddr.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_IOMCU_BASEADDR_INTERFACE_H__
#define __SOC_IOMCU_BASEADDR_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 寄存器说明：4K */
#define SOC_IOMCU_M7_CS_PPB_ROM_TABLE_BASE_ADDR       (0xE00FF000)

/* 寄存器说明：4K */
#define SOC_IOMCU_M7_CS_Processor_ROM_TABLE_BASE_ADDR (0xE00FE000)

/* 寄存器说明：4K */
#define SOC_IOMCU_M7_CS_CTI_BASE_ADDR                 (0xE0042000)

/* 寄存器说明：4K */
#define SOC_IOMCU_M7_CS_ETM_BASE_ADDR                 (0xE0041000)

/* 寄存器说明：4K */
#define SOC_IOMCU_M7_CS_SCS_BASE_ADDR                 (0xE000E000)

/* 寄存器说明：4K */
#define SOC_IOMCU_M7_CS_FPB_BASE_ADDR                 (0xE0002000)

/* 寄存器说明：4K */
#define SOC_IOMCU_M7_CS_DWT_BASE_ADDR                 (0xE0001000)

/* 寄存器说明：400K */
#define SOC_IOMCU_MMBUF_BASE_ADDR                     (0x80200000)

/* 寄存器说明：2M */
#define SOC_IOMCU_HKMEM_BASE_ADDR                     (0x80000000)

/* 寄存器说明：512M */
#define SOC_IOMCU_DRAM_BASE_ADDR                      (0x60000000)

/* 寄存器说明：64K */
#define SOC_IOMCU_BOOTROM_NAND_REMAP_BASE_ADDR        (0x5FFF0000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRC_QOSB_0_BASE_ADDR               (0x5FFC8000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRC_DMC_0_0_BASE_ADDR              (0x5FFC9000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRC_DMC_0_1_BASE_ADDR              (0x5FFCA000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRC_QOSB_1_BASE_ADDR               (0x5FFCC000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRC_DMC_1_0_BASE_ADDR              (0x5FFCD000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRC_DMC_1_1_BASE_ADDR              (0x5FFCE000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PACK_A_BASE_ADDR                    (0x5FFD0000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRPHY_STATIC_A_BASE_ADDR           (0x5FFD1000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PACK_B_BASE_ADDR                    (0x5FFD2000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRPHY_STATIC_B_BASE_ADDR           (0x5FFD3000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PACK_C_BASE_ADDR                    (0x5FFD4000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRPHY_STATIC_C_BASE_ADDR           (0x5FFD5000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PACK_D_BASE_ADDR                    (0x5FFD6000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DDRPHY_STATIC_D_BASE_ADDR           (0x5FFD7000)

/* 寄存器说明：32K */
#define SOC_IOMCU_DMSS_BASE_ADDR                      (0x5FFC0000)

/* 寄存器说明：128K */
#define SOC_IOMCU_NANDC_CFG_BASE_ADDR                 (0x5FFA0000)

/* 寄存器说明：128K */
#define SOC_IOMCU_NANDC_BASE_ADDR                     (0x5FF80000)

/* 寄存器说明：64K */
#define SOC_IOMCU_BOOTROM_BASE_ADDR                   (0x5FF60000)

/* 寄存器说明：64K */
#define SOC_IOMCU_LPMCU_RAM_BASE_ADDR                 (0x5FF50000)

/* 寄存器说明：64K */
#define SOC_IOMCU_LP_RAM_BASE_ADDR                    (0x5FF40000)

/* 寄存器说明：4K */
#define SOC_IOMCU_LP_CONFIG_BASE_ADDR                 (0x5FF3F000)

/* 寄存器说明：4K */
#define SOC_IOMCU_LP_TIMER_BASE_ADDR                  (0x5FF3E000)

/* 寄存器说明：4K */
#define SOC_IOMCU_LP_Watchdog_BASE_ADDR               (0x5FF3D000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GNSPWM_BASE_ADDR                    (0x5FF37000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PMU_SSI1_BASE_ADDR                  (0x5FF36000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PERI_CRG_BASE_ADDR                  (0x5FF35000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PMU_SSI0_BASE_ADDR                  (0x5FF34000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PMU_I2C_BASE_ADDR                   (0x5FF33000)

/* 寄存器说明：4K */
#define SOC_IOMCU_UART6_BASE_ADDR                     (0x5FF32000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PMC_BASE_ADDR                       (0x5FF31000)

/* 寄存器说明：4K */
#define SOC_IOMCU_TSENSORC_BASE_ADDR                  (0x5FF30000)

/* 寄存器说明：4K */
#define SOC_IOMCU_TIMER0_BASE_ADDR                    (0x5FF14000)

/* 寄存器说明：4k */
#define SOC_IOMCU_TIMER1_BASE_ADDR                    (0x5FF15000)

/* 寄存器说明：4k */
#define SOC_IOMCU_TIMER2_BASE_ADDR                    (0x5FF16000)

/* 寄存器说明：4k */
#define SOC_IOMCU_TIMER3_BASE_ADDR                    (0x5FF17000)

/* 寄存器说明：4k */
#define SOC_IOMCU_TIMER4_BASE_ADDR                    (0x5FF18000)

/* 寄存器说明：4k */
#define SOC_IOMCU_TIMER5_BASE_ADDR                    (0x5FF19000)

/* 寄存器说明：4k */
#define SOC_IOMCU_TIMER6_BASE_ADDR                    (0x5FF1A000)

/* 寄存器说明：4k */
#define SOC_IOMCU_TIMER7_BASE_ADDR                    (0x5FF1B000)

/* 寄存器说明：4k */
#define SOC_IOMCU_TIMER8_BASE_ADDR                    (0x5FF1C000)

/* 寄存器说明：4K */
#define SOC_IOMCU_AO_IOC_BASE_ADDR                    (0x5FF11000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO27_BASE_ADDR                    (0x5FF10000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO26_BASE_ADDR                    (0x5FF0F000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO25_BASE_ADDR                    (0x5FF0E000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO24_BASE_ADDR                    (0x5FF0D000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO23_BASE_ADDR                    (0x5FF0C000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO22_BASE_ADDR                    (0x5FF0B000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SCTRL_BASE_ADDR                     (0x5FF0A000)

/* 寄存器说明：8K */
#define SOC_IOMCU_SYS_CNT_BASE_ADDR                   (0x5FF08000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SCI1_BASE_ADDR                      (0x5FF07000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SCI0_BASE_ADDR                      (0x5FF06000)

/* 寄存器说明：4K */
#define SOC_IOMCU_RTC1_BASE_ADDR                      (0x5FF05000)

/* 寄存器说明：4K */
#define SOC_IOMCU_RTC0_BASE_ADDR                      (0x5FF04000)

/* 寄存器说明：4K */
#define SOC_IOMCU_EFUSEC_BASE_ADDR                    (0x5FF03000)

/* 寄存器说明：4K */
#define SOC_IOMCU_MMBUF_CFG_BASE_ADDR                 (0x5FF02000)

/* 寄存器说明：4K */
#define SOC_IOMCU_MMBUF_ASC1_BASE_ADDR                (0x5FF01000)

/* 寄存器说明：4K */
#define SOC_IOMCU_MMBUF_ASC0_BASE_ADDR                (0x5FF00000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_RTC_BASE_ADDR                 (0x5FD7F000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_CONFIG_BASE_ADDR              (0x5FD7E000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_TIMER_BASE_ADDR               (0x5FD7D000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_Watchdog_BASE_ADDR            (0x5FD7C000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_GPIO3_BASE_ADDR               (0x5FD7B000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_GPIO2_BASE_ADDR               (0x5FD7A000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_GPIO1_BASE_ADDR               (0x5FD79000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_GPIO0_BASE_ADDR               (0x5FD78000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_DMAC_BASE_ADDR                (0x5FD77000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_UART7_BASE_ADDR               (0x5FD76000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_BLPWM_BASE_ADDR               (0x5FD75000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_UART3_BASE_ADDR               (0x5FD74000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_I2C2_BASE_ADDR                (0x5FD73000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_I2C1_BASE_ADDR                (0x5FD72000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_I2C0_BASE_ADDR                (0x5FD71000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_SPI_BASE_ADDR                 (0x5FD70000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DTCM1Remap_BASE_ADDR                (0x5FD6F000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DTCM0Remap_BASE_ADDR                (0x5FD6E000)

/* 寄存器说明：8K */
#define SOC_IOMCU_ITCMRemap_BASE_ADDR                 (0x5FD6C000)

/* 寄存器说明：4K */
#define SOC_IOMCU_RemapCtrl_BASE_ADDR                 (0x5FD6B000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_I2C3_BASE_ADDR                (0x5FD6A000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_UART8_BASE_ADDR               (0x5FD69000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOMCU_SPI2_BASE_ADDR                (0x5FD68000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SDIO0_BASE_ADDR                     (0x5F3FF000)

/* 寄存器说明：4K */
#define SOC_IOMCU_EMMC1_BASE_ADDR                     (0x5F3FE000)

/* 寄存器说明：64K */
#define SOC_IOMCU_EMMC0_BASE_ADDR                     (0x5F390000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SD_BASE_ADDR                        (0x5F37F000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SDIO1_BASE_ADDR                     (0x5F37D000)

/* 寄存器说明：4K */
#define SOC_IOMCU_USB3OTG_BC_BASE_ADDR                (0x5F200000)

/* 寄存器说明：1M */
#define SOC_IOMCU_USB3OTG_BASE_ADDR                   (0x5F100000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SOCP_BASE_ADDR                      (0x5F030000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PERF_STAT_BASE_ADDR                 (0x5F012000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SECENG_S_BASE_ADDR                  (0x5F011000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SECENG_P_BASE_ADDR                  (0x5F010000)

/* 寄存器说明：16M */
#define SOC_IOMCU_CS_STM_BASE_ADDR                    (0x5E000000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PERI_DMAC_BASE_ADDR                 (0x5DF30000)

/* 寄存器说明：4K */
#define SOC_IOMCU_BISR_BASE_ADDR                      (0x5DF22000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IPC_MDM_BASE_ADDR                   (0x5DF21000)

/* 寄存器说明：4K */
#define SOC_IOMCU_I2C4_BASE_ADDR                      (0x5DF0D000)

/* 寄存器说明：4K */
#define SOC_IOMCU_I2C3_BASE_ADDR                      (0x5DF0C000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SPI1_BASE_ADDR                      (0x5DF08000)

/* 寄存器说明：4K */
#define SOC_IOMCU_UART5_BASE_ADDR                     (0x5DF05000)

/* 寄存器说明：4K */
#define SOC_IOMCU_UART2_BASE_ADDR                     (0x5DF03000)

/* 寄存器说明：4K */
#define SOC_IOMCU_UART0_BASE_ADDR                     (0x5DF02000)

/* 寄存器说明：4K */
#define SOC_IOMCU_UART4_BASE_ADDR                     (0x5DF01000)

/* 寄存器说明：4K */
#define SOC_IOMCU_UART1_BASE_ADDR                     (0x5DF00000)

/* 寄存器说明：4K */
#define SOC_IOMCU_A53_ROM_TABLE_BASE_ADDR             (0x4C800000)

/* 寄存器说明：4K */
#define SOC_IOMCU_A53_FUNNEL_BASE_ADDR                (0x4C801000)

/* 寄存器说明：4K */
#define SOC_IOMCU_A53_ETF_BASE_ADDR                   (0x4C802000)

/* 寄存器说明：4K */
#define SOC_IOMCU_A53_CTI_BASE_ADDR                   (0x4C803000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Maia_ROM_TABLE_BASE_ADDR            (0x4D000000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Maia_FUNNEL_BASE_ADDR               (0x4D001000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Maia_ETF_BASE_ADDR                  (0x4D002000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Maia_CTI_BASE_ADDR                  (0x4D003000)

/* 寄存器说明：24M */
#define SOC_IOMCU_CSSYS_APB_BASE_ADDR                 (0x4C000000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CSSYS_ROM_TABLE_BASE_ADDR           (0x4C030000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CSSYS_FUNNEL_BASE_ADDR              (0x4C031000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CSSYS_TPIU_BASE_ADDR                (0x4C032000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CSSYS_ETR_BASE_ADDR                 (0x4C033000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CSSYS_CTI_BASE_ADDR                 (0x4C034000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CSSYS_STM_BASE_ADDR                 (0x4C035000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CSSYS_ETF_BASE_ADDR                 (0x4C036000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CSSYS_Tsgen_BASE_ADDR               (0x4C037000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CSSYS_Tsgen_RO_BASE_ADDR            (0x4C038000)

/* 寄存器说明：64K */
#define SOC_IOMCU_MMC0_NOC_Service_Target_BASE_ADDR   (0x49890000)

/* 寄存器说明：64K */
#define SOC_IOMCU_MMC1_NOC_Service_Target_BASE_ADDR   (0x49880000)

/* 寄存器说明：64K */
#define SOC_IOMCU_DEBUG_SEC_NOC_Service_Target_BASE_ADDR (0x49870000)

/* 寄存器说明：64K */
#define SOC_IOMCU_DMA_NOC_Service_Target_BASE_ADDR    (0x49860000)

/* 寄存器说明：64K */
#define SOC_IOMCU_IVP32_Sevice_Target_BASE_ADDR       (0x49850000)

/* 寄存器说明：64K */
#define SOC_IOMCU_SYS_BUS_Service_Target_BASE_ADDR    (0x49840000)

/* 寄存器说明：64K */
#define SOC_IOMCU_ASP_Service_Target_BASE_ADDR        (0x49830000)

/* 寄存器说明：64K */
#define SOC_IOMCU_Modem_Service_Target_BASE_ADDR      (0x49820000)

/* 寄存器说明：64K */
#define SOC_IOMCU_CFGBUS_Service_Target_BASE_ADDR     (0x49800000)

/* 寄存器说明：128K */
#define SOC_IOMCU_IVP32_SMMU_BASE_ADDR                (0x48DC0000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IVP32_TIMER1_BASE_ADDR              (0x48D83000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IVP32_TIMER0_BASE_ADDR              (0x48D82000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IVP32_Watchdog_BASE_ADDR            (0x48D81000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IVP32_CFG_BASE_ADDR                 (0x48D80000)

/* 寄存器说明：64K */
#define SOC_IOMCU_IVP32_IRAM_BASE_ADDR                (0x48D00000)

/* 寄存器说明：64K */
#define SOC_IOMCU_IVP32_DRAM1_BASE_ADDR               (0x48C80000)

/* 寄存器说明：64K */
#define SOC_IOMCU_IVP32_DRAM0_BASE_ADDR               (0x48C00000)

/* 寄存器说明：4K */
#define SOC_IOMCU_TZPC_BASE_ADDR                      (0x48A21000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO0_BASE_ADDR                     (0x48A0B000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO1_BASE_ADDR                     (0x48A0C000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO2_BASE_ADDR                     (0x48A0D000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO3_BASE_ADDR                     (0x48A0E000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO4_BASE_ADDR                     (0x48A0F000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO5_BASE_ADDR                     (0x48A10000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO6_BASE_ADDR                     (0x48A11000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO7_BASE_ADDR                     (0x48A12000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO8_BASE_ADDR                     (0x48A13000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO9_BASE_ADDR                     (0x48A14000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO10_BASE_ADDR                    (0x48A15000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO11_BASE_ADDR                    (0x48A16000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO12_BASE_ADDR                    (0x48A17000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO13_BASE_ADDR                    (0x48A18000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO14_BASE_ADDR                    (0x48A19000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO15_BASE_ADDR                    (0x48A1A000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO16_BASE_ADDR                    (0x48A1B000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO17_BASE_ADDR                    (0x48A1C000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO18_BASE_ADDR                    (0x48A1D000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO19_BASE_ADDR                    (0x48A1E000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO20_BASE_ADDR                    (0x48A1F000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GPIO21_BASE_ADDR                    (0x48A20000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PCTRL_BASE_ADDR                     (0x48A09000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Watchdog1_BASE_ADDR                 (0x48A07000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Watchdog0_BASE_ADDR                 (0x48A06000)

/* 寄存器说明：4K */
#define SOC_IOMCU_PWM_BASE_ADDR                       (0x48A04000)

/* 寄存器说明：4K */
#define SOC_IOMCU_TIMER12_BASE_ADDR                   (0x48A03000)

/* 寄存器说明：4K */
#define SOC_IOMCU_TIMER11_BASE_ADDR                   (0x48A02000)

/* 寄存器说明：4K */
#define SOC_IOMCU_TIMER10_BASE_ADDR                   (0x48A01000)

/* 寄存器说明：4K */
#define SOC_IOMCU_TIMER9_BASE_ADDR                    (0x48A00000)

/* 寄存器说明：16K */
#define SOC_IOMCU_G3D_BASE_ADDR                       (0x48970000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IOC_BASE_ADDR                       (0x4896C000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IPC_NS_BASE_ADDR                    (0x4896B000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IPC_BASE_ADDR                       (0x4896A000)

/* 寄存器说明：64K */
#define SOC_IOMCU_NOC_VENC_Service_Target_BASE_ADDR   (0x48940000)

/* 寄存器说明：64K */
#define SOC_IOMCU_NOC_VDEC_Service_Target_BASE_ADDR   (0x48930000)

/* 寄存器说明：64K */
#define SOC_IOMCU_NOC_VCODECBUS_Service_Target_BASE_ADDR (0x48920000)

/* 寄存器说明：64K */
#define SOC_IOMCU_VENC_BASE_ADDR                      (0x48900000)

/* 寄存器说明：1M */
#define SOC_IOMCU_VDEC_BASE_ADDR                      (0x48800000)

/* 寄存器说明：64K */
#define SOC_IOMCU_NOC_ISP_Service_Target_BASE_ADDR    (0x486D0000)

/* 寄存器说明：64K */
#define SOC_IOMCU_NOC_DSS_Service_Target_BASE_ADDR    (0x486C0000)

/* 寄存器说明：4K */
#define SOC_IOMCU_GLB0_BASE_ADDR                      (0x48600000)

/* 寄存器说明：512B */
#define SOC_IOMCU_DSI0_BASE_ADDR                      (0x48601000)

/* 寄存器说明：512B */
#define SOC_IOMCU_DSI1_BASE_ADDR                      (0x48601400)

/* 寄存器说明：4608B */
#define SOC_IOMCU_CMD_BASE_ADDR                       (0x48602000)

/* 寄存器说明：4K */
#define SOC_IOMCU_AIF0_BASE_ADDR                      (0x48607000)

/* 寄存器说明：4K */
#define SOC_IOMCU_AIF1_BASE_ADDR                      (0x48609000)

/* 寄存器说明：4K */
#define SOC_IOMCU_MIF_BASE_ADDR                       (0x4860A000)

/* 寄存器说明：2K */
#define SOC_IOMCU_MCTL_SYS_BASE_ADDR                  (0x48610000)

/* 寄存器说明：256B */
#define SOC_IOMCU_MCTL_MUTEX0_BASE_ADDR               (0x48610800)

/* 寄存器说明：256B */
#define SOC_IOMCU_MCTL_MUTEX1_BASE_ADDR               (0x48610900)

/* 寄存器说明：256B */
#define SOC_IOMCU_MCTL_MUTEX2_BASE_ADDR               (0x48610A00)

/* 寄存器说明：256B */
#define SOC_IOMCU_MCTL_MUTEX3_BASE_ADDR               (0x48610B00)

/* 寄存器说明：256B */
#define SOC_IOMCU_MCTL_MUTEX4_BASE_ADDR               (0x48610C00)

/* 寄存器说明：256B */
#define SOC_IOMCU_MCTL_MUTEX5_BASE_ADDR               (0x48610D00)

/* 寄存器说明：4K */
#define SOC_IOMCU_DBUG_BASE_ADDR                      (0x48611000)

/* 寄存器说明：32K */
#define SOC_IOMCU_RCH_V0_BASE_ADDR                    (0x48620000)

/* 寄存器说明：32K */
#define SOC_IOMCU_RCH_V1_BASE_ADDR                    (0x48628000)

/* 寄存器说明：32K */
#define SOC_IOMCU_RCH_G0_BASE_ADDR                    (0x48638000)

/* 寄存器说明：32K */
#define SOC_IOMCU_RCH_G1_BASE_ADDR                    (0x48640000)

/* 寄存器说明：4K */
#define SOC_IOMCU_RCH_D0_BASE_ADDR                    (0x48650000)

/* 寄存器说明：4K */
#define SOC_IOMCU_RCH_D1_BASE_ADDR                    (0x48651000)

/* 寄存器说明：4K */
#define SOC_IOMCU_RCH_D2_BASE_ADDR                    (0x48652000)

/* 寄存器说明：4K */
#define SOC_IOMCU_RCH_D3_BASE_ADDR                    (0x48653000)

/* 寄存器说明：4K */
#define SOC_IOMCU_WCH0_BASE_ADDR                      (0x4865A000)

/* 寄存器说明：4K */
#define SOC_IOMCU_WCH1_BASE_ADDR                      (0x4865C000)

/* 寄存器说明：1K */
#define SOC_IOMCU_OV6_0_BASE_ADDR                     (0x48660000)

/* 寄存器说明：1K */
#define SOC_IOMCU_OV2_0_BASE_ADDR                     (0x48660400)

/* 寄存器说明：1K */
#define SOC_IOMCU_OV6_1_BASE_ADDR                     (0x48660800)

/* 寄存器说明：1K */
#define SOC_IOMCU_OV2_1_BASE_ADDR                     (0x48660C00)

/* 寄存器说明：16K */
#define SOC_IOMCU_SCF_BASE_ADDR                       (0x48664000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DBUF0_BASE_ADDR                     (0x4866D000)

/* 寄存器说明：4K */
#define SOC_IOMCU_DBUF1_BASE_ADDR                     (0x4866E000)

/* 寄存器说明：48K */
#define SOC_IOMCU_DPP_BASE_ADDR                       (0x48670000)

/* 寄存器说明：4K */
#define SOC_IOMCU_SBL_BASE_ADDR                       (0x4867C000)

/* 寄存器说明：1K */
#define SOC_IOMCU_INTF0_BASE_ADDR                     (0x4867D000)

/* 寄存器说明：1K */
#define SOC_IOMCU_IFBC_BASE_ADDR                      (0x4867D400)

/* 寄存器说明：1K */
#define SOC_IOMCU_DSC_BASE_ADDR                       (0x4867D800)

/* 寄存器说明：4K */
#define SOC_IOMCU_INTF1_BASE_ADDR                     (0x4867E000)

/* 寄存器说明：1M */
#define SOC_IOMCU_ISP_CORE_CFG_BASE_ADDR              (0x48400000)

/* 寄存器说明：128K */
#define SOC_IOMCU_ISP_CORE_SRAM_BASE_ADDR             (0x48500000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ISP_Watchdog_BASE_ADDR              (0x48580000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ISP_TIMER_BASE_ADDR                 (0x48581000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ISP_IPC_BASE_ADDR                   (0x48582000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ISP_SUB_CTRL_BASE_ADDR              (0x48583000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CODEC_SSI_BASE_ADDR                 (0x482B9000)

/* 寄存器说明：4K */
#define SOC_IOMCU_HKADC_SSI_BASE_ADDR                 (0x482B8000)

/* 寄存器说明：32K */
#define SOC_IOMCU_GIC_BASE_ADDR                       (0x482B0000)

/* 寄存器说明：24K */
#define SOC_IOMCU_DSP_ITCM_BASE_ADDR                  (0x48070000)

/* 寄存器说明：96K */
#define SOC_IOMCU_DSP_DTCM_BASE_ADDR                  (0x48058000)

/* 寄存器说明：8K */
#define SOC_IOMCU_SLIMBUS_BASE_ADDR                   (0x48050000)

/* 寄存器说明：1K */
#define SOC_IOMCU_SIO_MODEM_BASE_ADDR                 (0x4804FC00)

/* 寄存器说明：1K */
#define SOC_IOMCU_SIO_BT_BASE_ADDR                    (0x4804F800)

/* 寄存器说明：1K */
#define SOC_IOMCU_SIO_VOICE_BASE_ADDR                 (0x4804F400)

/* 寄存器说明：1K */
#define SOC_IOMCU_SIO_AUDIO_BASE_ADDR                 (0x4804F000)

/* 寄存器说明：1K */
#define SOC_IOMCU_ASP_HDMI_SPDIF_BASE_ADDR            (0x4804EC00)

/* 寄存器说明：1K */
#define SOC_IOMCU_ASP_HDMI_SIO_BASE_ADDR              (0x4804E800)

/* 寄存器说明：1K */
#define SOC_IOMCU_ASP_HDMI_ASP_BASE_ADDR              (0x4804E400)

/* 寄存器说明：1K */
#define SOC_IOMCU_ASP_CFG_BASE_ADDR                   (0x4804E000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ASP_Watchdog_BASE_ADDR              (0x4804D000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ASP_IPC_BASE_ADDR                   (0x4804C000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ASP_DMAC_BASE_ADDR                  (0x4804B000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ASP_TIMER1_BASE_ADDR                (0x4804A000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ASP_TIMER0_BASE_ADDR                (0x48049000)

/* 寄存器说明：4K */
#define SOC_IOMCU_ASP_GPIO_BASE_ADDR                  (0x48048000)

/* 寄存器说明：192K */
#define SOC_IOMCU_SECRAM_BASE_ADDR                    (0x48000000)

/* 寄存器说明：512K */
#define SOC_IOMCU_TL_BBE16_ITCM1_BASE_ADDR            (0x42880000)

/* 寄存器说明：256K */
#define SOC_IOMCU_TL_BBE16_ITCM0_BASE_ADDR            (0x42840000)

/* 寄存器说明：512K */
#define SOC_IOMCU_TL_BBE16_DTCM1_BASE_ADDR            (0x42780000)

/* 寄存器说明：256K */
#define SOC_IOMCU_TL_BBE16_DTCM0_BASE_ADDR            (0x42740000)

/* 寄存器说明：96K */
#define SOC_IOMCU_ON_CHIP_MEMORY_BASE_ADDR            (0x40800000)

/* 寄存器说明：16K */
#define SOC_IOMCU_AXI_MON_BASE_ADDR                   (0x40476000)

/* 寄存器说明：4K */
#define SOC_IOMCU_IPCM_BASE_ADDR                      (0x40475000)

/* 寄存器说明：4K */
#define SOC_IOMCU_VIC_BBE16_BASE_ADDR                 (0x40474000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Modem_HS_UART_BASE_ADDR             (0x40473000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Modem_IPF_BASE_ADDR                 (0x40472000)

/* 寄存器说明：4K */
#define SOC_IOMCU_UPACC_BASE_ADDR                     (0x40471000)

/* 寄存器说明：4K */
#define SOC_IOMCU_CIPHER_BASE_ADDR                    (0x40470000)

/* 寄存器说明：64K */
#define SOC_IOMCU_CICOM1_BASE_ADDR                    (0x40450000)

/* 寄存器说明：64K */
#define SOC_IOMCU_CICOM0_BASE_ADDR                    (0x40440000)

/* 寄存器说明：256K */
#define SOC_IOMCU_UICC_BASE_ADDR                      (0x40400000)

/* 寄存器说明：4k */
#define SOC_IOMCU_Modem_TIMER0_BASE_ADDR              (0x40300000)

/* 寄存器说明：4k */
#define SOC_IOMCU_Modem_TIMER1_BASE_ADDR              (0x40301000)

/* 寄存器说明：4k */
#define SOC_IOMCU_Modem_TIMER2_BASE_ADDR              (0x40302000)

/* 寄存器说明：4k */
#define SOC_IOMCU_Modem_TIMER3_BASE_ADDR              (0x40303000)

/* 寄存器说明：4k */
#define SOC_IOMCU_Modem_TIMER4_BASE_ADDR              (0x40304000)

/* 寄存器说明：4k */
#define SOC_IOMCU_Modem_TIMER5_BASE_ADDR              (0x40305000)

/* 寄存器说明：4k */
#define SOC_IOMCU_Modem_TIMER6_BASE_ADDR              (0x40306000)

/* 寄存器说明：4k */
#define SOC_IOMCU_Modem_TIMER7_BASE_ADDR              (0x40307000)

/* 寄存器说明：4k */
#define SOC_IOMCU_Modem_TIMER8_BASE_ADDR              (0x40308000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Modem_TIMER9_BASE_ADDR              (0x40309000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Modem_ASHB_Bridge_BASE_ADDR         (0x40205000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Modem_EDMAC_BASE_ADDR               (0x40204000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Modem_UART_BASE_ADDR                (0x40203000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Modem_WatchDog_BASE_ADDR            (0x40201000)

/* 寄存器说明：4K */
#define SOC_IOMCU_Modem_Sysctrl_BASE_ADDR             (0x40200000)

/* 寄存器说明：1M */
#define SOC_IOMCU_MCPU_Private_Space_BASE_ADDR        (0x40100000)

/* 寄存器说明：1M */
#define SOC_IOMCU_MCPU_L2Cache_BASE_ADDR              (0x40000000)

/* 寄存器说明：1M */
#define SOC_IOMCU_LTE_RFIN_BASE_ADDR                  (0x41000000)

/* 寄存器说明：1M */
#define SOC_IOMCU_LTE_FPU_BASE_ADDR                   (0x41100000)

/* 寄存器说明：1M */
#define SOC_IOMCU_BBP_DMA_BASE_ADDR                   (0x41200000)

/* 寄存器说明：1M */
#define SOC_IOMCU_DBG_BASE_ADDR                       (0x41300000)

/* 寄存器说明：1M */
#define SOC_IOMCU_LTE_PB_BASE_ADDR                    (0x41400000)

/* 寄存器说明：1M */
#define SOC_IOMCU_LTE_VDL_BASE_ADDR                   (0x41500000)

/* 寄存器说明：1M */
#define SOC_IOMCU_LTE_UL_BASE_ADDR                    (0x41600000)

/* 寄存器说明：1M */
#define SOC_IOMCU_LTE_INT_BASE_ADDR                   (0x41700000)

/* 寄存器说明：512KB */
#define SOC_IOMCU_GSM0_BASE_ADDR                      (0x41800000)

/* 寄存器说明：512KB */
#define SOC_IOMCU_GSM1_BASE_ADDR                      (0x41880000)

/* 寄存器说明：1M */
#define SOC_IOMCU_LTE_CQI_BASE_ADDR                   (0x41A00000)

/* 寄存器说明：1M */
#define SOC_IOMCU_LTE_PDU_BASE_ADDR                   (0x41B00000)

/* 寄存器说明：1M */
#define SOC_IOMCU_LTE_TDL_BASE_ADDR                   (0x41C00000)

/* 寄存器说明：64K */
#define SOC_IOMCU_TW_Share_BASE_ADDR                  (0x41900000)

/* 寄存器说明：256K */
#define SOC_IOMCU_WBBP_TOP1_BASE_ADDR                 (0x41900000)

/* 寄存器说明：64K */
#define SOC_IOMCU_XBBP_BASE_ADDR                      (0x419E0000)

/* 寄存器说明：1M */
#define SOC_IOMCU_TDS122_BASE_ADDR                    (0x41D00000)

/* 寄存器说明：1M */
#define SOC_IOMCU_TDS245_BASE_ADDR                    (0x41E00000)

/* 寄存器说明：32K */
#define SOC_IOMCU_CTU_BASE_ADDR                       (0x41F80000)

/* 寄存器说明：8K */
#define SOC_IOMCU_ET_BASE_ADDR                        (0x41F88000)

/* 寄存器说明：2K */
#define SOC_IOMCU_GU_BBP_MASTER_BASE_ADDR             (0x41F8A800)

/* 寄存器说明：4K */
#define SOC_IOMCU_IRM_PS_CFG_BASE_ADDR                (0x41F8B000)

/* 寄存器说明：8K */
#define SOC_IOMCU_ABB_BASE_ADDR                       (0x41F8C000)

/* 寄存器说明：8K */
#define SOC_IOMCU_ABB_CFG_BASE_ADDR                   (0x41F8E000)

/* 寄存器说明：2KB */
#define SOC_IOMCU_LTE_ON_BASE_ADDR                    (0x5FF12000)

/* 寄存器说明：1KB */
#define SOC_IOMCU_BBP_COMM_ON_BASE_ADDR               (0x5FF12000)

/* 寄存器说明：1KB */
#define SOC_IOMCU_GSM0_ON_BASE_ADDR                   (0x5FF12800)

/* 寄存器说明：1KB */
#define SOC_IOMCU_GSM1_ON_BASE_ADDR                   (0x5FF12C00)

/* 寄存器说明：512B */
#define SOC_IOMCU_AFC_CH0_BASE_ADDR                   (0x5FF13000)

/* 寄存器说明：512B */
#define SOC_IOMCU_AFC_CH1_BASE_ADDR                   (0x5FF13200)

/* 寄存器说明：1KB */
#define SOC_IOMCU_TDS_ON_BASE_ADDR                    (0x5FF13400)

/* 寄存器说明：512B */
#define SOC_IOMCU_BBP_GLB_ON_BASE_ADDR                (0x5FF12000)

/* 寄存器说明：512B */
#define SOC_IOMCU_WCDMA_ON_BASE_ADDR                  (0x5FF12000)

/* 寄存器说明：512B */
#define SOC_IOMCU_CDMA_ON_BASE_ADDR                   (0x5FF12000)

/* 寄存器说明：12M */
#define SOC_IOMCU_IOMCU_TCM_BASE_ADDR                 (0x00000000)





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

#endif /* end of soc_iomcu_baseaddr_interface.h */
