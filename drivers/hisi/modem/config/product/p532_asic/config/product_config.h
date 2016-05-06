/* MD5: 14877281bfe0765787b273bf586fb0d5*/
#if !defined(__PRODUCT_CONFIG_H__)
#define __PRODUCT_CONFIG_H__

#ifndef BALONG_OBUILD_VERSION
#define BALONG_OBUILD_VERSION 10 
#endif 

#ifndef BUILD_PTABLE
#define BUILD_PTABLE 
#endif 

#ifndef ARCH_TYPE	
#define ARCH_TYPE	 3339 
#endif 

#ifndef PRODUCT_NAME
#define PRODUCT_NAME "p532_asic" 
#endif 

#ifndef PRODUCT_CFG_CHIP_SOLUTION_NAME
#define PRODUCT_CFG_CHIP_SOLUTION_NAME "Balong" 
#endif 

#ifndef BUILD_TYPE
#define BUILD_TYPE RELEASE 
#endif 

#ifndef PRODUCT_VERSION
#define PRODUCT_VERSION V700R200C31B120 
#endif 

#ifndef PRODUCT_VERSION_STR
#define PRODUCT_VERSION_STR "V700R200C31B120" 
#endif 

#ifndef PRODUCT_FULL_VERSION_STR
#define PRODUCT_FULL_VERSION_STR "Balong V700R200C31B120" 
#endif 

#ifndef PRODUCT_FILE_VERSION_STR
#define PRODUCT_FILE_VERSION_STR "2.1.6.8" 
#endif 

#ifndef PRODUCT_DLOAD_SOFTWARE_VER		
#define PRODUCT_DLOAD_SOFTWARE_VER		 "21.120.00.00.031" 
#endif 

#ifndef CONFIG_VERSION_STUB
#define CONFIG_VERSION_STUB 
#endif 

#ifndef HW_VERSION_STUB
#define HW_VERSION_STUB 0XFF000000 
#endif 

#ifndef PXXX_BOARD_TYPE_ONLY_SOC
#define PXXX_BOARD_TYPE_ONLY_SOC 
#endif 

#ifndef FEATURE_OBJ_CMP 				
#endif 

#ifndef FEATURE_OBJ_DUMP				
#endif 

#ifndef USE_USBLOADER_MERGE 			
#define USE_USBLOADER_MERGE 			 
#endif 

#ifndef BSP_ENBALE_PACK_IMAGE			
#define BSP_ENBALE_PACK_IMAGE			 
#endif 

#ifndef BSP_USB_BURN					
#define BSP_USB_BURN					 
#endif 

#ifndef PLATFORM
#define PLATFORM p532 
#endif 

#ifndef OS_PATH
#define OS_PATH modem/config/product/p532_asic/os 
#endif 

#ifndef OS_IMG_FILE
#define OS_IMG_FILE VXWORKS.6.8.3.IMG.wpj 
#endif 

#ifndef OS_LIB
#define OS_LIB VXWORKS.6.8.3.LIB.RELEASE 
#endif 

#ifndef FTP_REPLY_TIME_OUT
#define FTP_REPLY_TIME_OUT 0 
#endif 

#ifndef OS_LINUX_PRODUCT_NAME
#define OS_LINUX_PRODUCT_NAME p532_defconfig 
#endif 

#ifndef TARGET_BALONG_PRODUCT
#define TARGET_BALONG_PRODUCT p532 
#endif 

#ifndef PRODUCT_CONTROL_VERSION
#define PRODUCT_CONTROL_VERSION "121" 
#endif 

#ifndef PRODUCT_HISILICON_VERSION
#define PRODUCT_HISILICON_VERSION hi6950 
#endif 

#ifndef PRODUCT_NV_SPLITFILE
#define PRODUCT_NV_SPLITFILE binfilesplit "0" 
#endif 

#ifndef PRODUCT_NV_FILE_MAX_SIZE
#define PRODUCT_NV_FILE_MAX_SIZE binfileLimitSize "100" 
#endif 

#ifndef PRODUCT_NV_BIN_MODEM_NUNBER
#define PRODUCT_NV_BIN_MODEM_NUNBER bin_modem_number "1" 
#endif 

#ifndef PRODUCT_NV_XNV_MODEM_NUNBER
#define PRODUCT_NV_XNV_MODEM_NUNBER xnv_modem_number "1" 
#endif 

#ifndef PRODUCT_NV_XNV_PDT_VERSION
#define PRODUCT_NV_XNV_PDT_VERSION hi6950_fpga_p532 
#endif 

#ifndef XTENSA_CORE				
#define XTENSA_CORE				 p532_bbe16_nocache 
#endif 

#ifndef XTENSA_SYSTEM			
#define XTENSA_SYSTEM			 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RE-2014.5-linux/p532_bbe16_nocache/config 
#endif 

#ifndef LPHY_PUB_DTCM_BASE	
#define LPHY_PUB_DTCM_BASE	 0x49000000 
#endif 

#ifndef LPHY_PUB_ITCM_BASE	
#define LPHY_PUB_ITCM_BASE	 0x49100000 
#endif 

#ifndef LPHY_PRV_DTCM_BASE	
#define LPHY_PRV_DTCM_BASE	 0x49080000 
#endif 

#ifndef LPHY_PRV_ITCM_BASE	
#define LPHY_PRV_ITCM_BASE	 0x49180000 
#endif 

#ifndef LPHY_PUB_DTCM_SIZE		
#define LPHY_PUB_DTCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_PUB_ITCM_SIZE		
#define LPHY_PUB_ITCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_PRV_DTCM_SIZE		
#define LPHY_PRV_DTCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_PRV_ITCM_SIZE		
#define LPHY_PRV_ITCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_LTE_DTCM_SIZE		
#define LPHY_LTE_DTCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_LTE_ITCM_SIZE		
#define LPHY_LTE_ITCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_TDS_DTCM_SIZE		
#define LPHY_TDS_DTCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_TDS_ITCM_SIZE		
#define LPHY_TDS_ITCM_SIZE		 0x80000 
#endif 

#ifndef LPHY_ALL_IMAG_SIZE		
#define LPHY_ALL_IMAG_SIZE		 0x300000 
#endif 

#ifndef LPHY_TOTAL_IMG_SIZE
#define LPHY_TOTAL_IMG_SIZE ((LPHY_PUB_DTCM_SIZE)+(LPHY_PUB_ITCM_SIZE)+(LPHY_LTE_DTCM_SIZE)*1+(LPHY_LTE_ITCM_SIZE)*1+(LPHY_TDS_DTCM_SIZE)+(LPHY_TDS_ITCM_SIZE)) 
#endif 

#ifndef TL_PHY_LALG_PATH    	
#define TL_PHY_LALG_PATH    	 modem/include/phy 
#endif 

#ifndef TL_PHY_FPGA_P532    	
#define TL_PHY_FPGA_P532    	 
#endif 

#ifndef TL_PHY_BBE16_CACHE
#endif 

#ifndef TL_PHY_6930         	
#define TL_PHY_6930         	 
#endif 

#ifndef TL_PHY_FEATURE_LTE_LCS  	
#define TL_PHY_FEATURE_LTE_LCS  	 
#endif 

#ifndef GU_INC_PATH
#define GU_INC_PATH COMM_CODE_GU/Balong_GU_Inc/GUL_CS 
#endif 

#ifndef GU_PRODUCT_VERSION
#define GU_PRODUCT_VERSION VERSION_V7R1 
#endif 

#ifndef RAT_GU
#define RAT_GU 0 
#endif 

#ifndef RAT_GUL
#define RAT_GUL 1 
#endif 

#ifndef RAT_MODE
#define RAT_MODE RAT_GUL 
#endif 

#ifndef GU_RAT_MODE
#define GU_RAT_MODE RAT_GUL 
#endif 

#ifndef PLATFORM_HISI_BALONG
#define PLATFORM_HISI_BALONG p532 
#endif 

#ifndef TTF_SKB_EXP
#endif 

#ifndef GU_FEATURE_CONFIG_PATH
#define GU_FEATURE_CONFIG_PATH modem/config/product/p532_asic/include_gu 
#endif 

#ifndef HIFI_INCLUDE
#define HIFI_INCLUDE 
#endif 

#ifndef HIFI_LINK_DIR_NAME
#define HIFI_LINK_DIR_NAME hifi_ld_V7R2_SFT 
#endif 

#ifndef XTENSA_CORE_HIFI
#define XTENSA_CORE_HIFI v7r2_hifi 
#endif 

#ifndef PLATFORM_CHIP_TYPE
#define PLATFORM_CHIP_TYPE p532 
#endif 

#ifndef CHIP_MODEM_ARM_ARCH
#define CHIP_MODEM_ARM_ARCH CORTEX_A9 
#endif 

#ifndef BSP_CONFIG_EDA
#endif 

#ifndef BSP_CONFIG_EMU
#endif 

#ifndef BSP_CONFIG_NOT_DDR_BYPASSPLL
#endif 

#ifndef BSP_CONFIG_P532_ASIC
#define BSP_CONFIG_P532_ASIC 
#endif 

#ifndef BSP_CONFIG_P532_FPGA
#endif 

#ifndef BSP_HAS_SEC_FEATURE
#endif 

#ifndef CONFIG_SMART_SYSTEM_MODEM
#endif 

#ifndef CONFIG_OF
#define CONFIG_OF 
#endif 

#ifndef CONFIG_FASTBOOT_DEBUG
#endif 

#ifndef CONFIG_FASTBOOT_UART_NUM
#define CONFIG_FASTBOOT_UART_NUM 1 
#endif 

#ifndef CONFIG_GPIO_SYNOPSYS
#define CONFIG_GPIO_SYNOPSYS 
#endif 

#ifndef CONFIG_COMPRESS_CCORE_IMAGE
#define CONFIG_COMPRESS_CCORE_IMAGE 
#endif 

#ifndef CONFIG_MODULE_VIC
#endif 

#ifndef CONFIG_PCIE_CFG
#define CONFIG_PCIE_CFG 
#endif 

#ifndef CONFIG_CIPHER
#define CONFIG_CIPHER 
#endif 

#ifndef CONFIG_AT_UART
#endif 

#ifndef CONFIG_CSHELL
#endif 

#ifndef CONFIG_IPF
#define CONFIG_IPF 
#endif 

#ifndef CONFIG_PSAM
#endif 

#ifndef CONFIG_MODULE_BUSSTRESS
#endif 

#ifndef CONFIG_ICC
#define CONFIG_ICC 
#endif 

#ifndef CONFIG_RTC_BUILD_CTRL
#define CONFIG_RTC_BUILD_CTRL 
#endif 

#ifndef CONFIG_RTC_ON_SOC
#define CONFIG_RTC_ON_SOC 
#endif 

#ifndef CONFIG_RTC_DRV_PL031
#define CONFIG_RTC_DRV_PL031 
#endif 

#ifndef CONFIG_MEM
#define CONFIG_MEM 
#endif 

#ifndef CONFIG_CPUFREQ
#endif 

#ifndef CONFIG_CCORE_REGULATOR
#define CONFIG_CCORE_REGULATOR 
#endif 

#ifndef CONFIG_CCORE_WDT
#define CONFIG_CCORE_WDT 
#endif 

#ifndef CONFIG_ACORE_WDT
#define CONFIG_ACORE_WDT 
#endif 

#ifndef CONFIG_PMIC_HI6551
#define CONFIG_PMIC_HI6551 
#endif 

#ifndef CONFIG_COUL
#endif 

#ifndef CONFIG_USE_TIMER_STAMP
#define CONFIG_USE_TIMER_STAMP 
#endif 

#ifndef CONFIG_SPI
#endif 

#ifndef CONFIG_SFLASH
#endif 

#ifndef CONFIG_ABB
#endif 

#ifndef CONFIG_DSP
#endif 

#ifndef CONFIG_HIFI
#endif 

#ifndef CONFIG_HKADC
#endif 

#ifndef CONFIG_ONOFF
#define CONFIG_ONOFF 
#endif 

#ifndef CONFIG_BBP
#endif 

#ifndef CONFIG_NVIM
#define CONFIG_NVIM 
#endif 

#ifndef CONFIG_SC
#endif 

#ifndef FEATURE_NV_FLASH_ON
#define FEATURE_NV_FLASH_ON 
#endif 

#ifndef FEATURE_NV_EMMC_ON
#endif 

#ifndef FEATURE_NV_LFILE_ON
#endif 

#ifndef FEATURE_NV_RFILE_ON
#endif 

#ifndef FEATURE_UPGRADE_TL
#define FEATURE_UPGRADE_TL 
#endif 

#ifndef FEATURE_TLPHY_MAILBOX
#define FEATURE_TLPHY_MAILBOX 
#endif 

#ifndef CONFIG_MAILBOX_TYPE
#define CONFIG_MAILBOX_TYPE 
#endif 

#ifndef CONFIG_HIFI_MAILBOX
#define CONFIG_HIFI_MAILBOX 
#endif 

#ifndef CONFIG_PA_RF
#endif 

#ifndef CONFIG_PASTAR
#endif 

#ifndef CONFIG_MIPI
#endif 

#ifndef ENABLE_SHELL_SYM
#define ENABLE_SHELL_SYM 
#endif 

#ifndef ENABLE_DEBUG
#define ENABLE_DEBUG 
#endif 

#ifndef RTOSCK_CCORE_COMPONENTS
#define RTOSCK_CCORE_COMPONENTS bsp_ccore.o 
#endif 

#ifndef CCORE_COMPONENTS
#define CCORE_COMPONENTS bsp_ccore.o os_ccore.o 
#endif 

#ifndef CCORE_MODEM1_COMPONENTS
#define CCORE_MODEM1_COMPONENTS bsp_ccore1.o 
#endif 

#ifndef CCORE_MODEMUNION_COMPONENTS
#define CCORE_MODEMUNION_COMPONENTS modemcore1_union.o 
#endif 

#ifndef BUILD_DRV_ONLY
#endif 

#ifndef ENABLE_TEST_CODE
#endif 

#ifndef ENABLE_BUILD_VARS
#define ENABLE_BUILD_VARS 
#endif 

#ifndef ENABLE_BUILD_OM
#define ENABLE_BUILD_OM 
#endif 

#ifndef FEATURE_OM_PHONE
#endif 

#ifndef ENABLE_BUILD_SYSVIEW
#define ENABLE_BUILD_SYSVIEW 
#endif 

#ifndef ENABLE_BUILD_CPUVIEW
#define ENABLE_BUILD_CPUVIEW 
#endif 

#ifndef ENABLE_BUILD_MEMVIEW
#define ENABLE_BUILD_MEMVIEW 
#endif 

#ifndef ENABLE_BUILD_AMON
#define ENABLE_BUILD_AMON 
#endif 

#ifndef ENABLE_BUILD_UTRACE
#endif 

#ifndef ENABLE_BUILD_SOCP
#define ENABLE_BUILD_SOCP 
#endif 

#ifndef CONFIG_CCORE_CPU_IDLE
#define CONFIG_CCORE_CPU_IDLE 
#endif 

#ifndef CONFIG_BSP_TEST_CCORE
#endif 

#ifndef CONFIG_BALONG_CCLK
#endif 

#ifndef FEATURE_E5_ONOFF
#endif 

#ifndef CONFIG_CCORE_PM
#endif 

#ifndef CONFIG_MODULE_IPC
#define CONFIG_MODULE_IPC 
#endif 

#ifndef CONFIG_MODULE_TIMER
#define CONFIG_MODULE_TIMER 
#endif 

#ifndef CONFIG_MODULE_SYNC
#define CONFIG_MODULE_SYNC 
#endif 

#ifndef CONFIG_LEDS_CCORE
#endif 

#ifndef CONFIG_HAS_CCORE_WAKELOCK
#endif 

#ifndef CONFIG_CCORE_BALONG_PM
#endif 

#ifndef CONFIG_BALONG_EDMA
#define CONFIG_BALONG_EDMA 
#endif 

#ifndef CONFIG_BALONG_EDMA_TEST
#define CONFIG_BALONG_EDMA_TEST 
#endif 

#ifndef CONFIG_IPF_VESION
#define CONFIG_IPF_VESION 2 
#endif 

#ifndef CONFIG_IPF_ADQ_LEN
#define CONFIG_IPF_ADQ_LEN 3 
#endif 

#ifndef CONFIG_IPF_PROPERTY_MBB
#define CONFIG_IPF_PROPERTY_MBB 
#endif 

#ifndef CONFIG_FB_SPI_BALONG
#endif 

#ifndef CONFIG_FB_EMI_BALONG
#endif 

#ifndef CONFIG_FB_1_4_5_INCH_BALONG
#endif 

#ifndef CONFIG_FB_2_4_INCH_BALONG
#endif 

#ifndef CONFIG_SLIC
#define CONFIG_SLIC n 
#endif 

#ifndef CONFIG_WM8990
#endif 

#ifndef CONFIG_GPIO_EXPANDER
#endif 

#ifndef CONFIG_TEMPERATURE_PROTECT
#endif 

#ifndef CONFIG_ANTEN
#endif 

#ifndef CONFIG_EFUSE
#endif 

#ifndef CONFIG_BURN_EFUSE_NANDC
#endif 

#ifndef CONFIG_DDM
#define CONFIG_DDM 
#endif 

#ifndef CONFIG_TSENSOR
#endif 

#ifndef CONFIG_DESIGNWARE_I2C
#define CONFIG_DESIGNWARE_I2C 
#endif 

#ifndef CONFIG_USB_DWC3_VBUS_DISCONNECT
#define CONFIG_USB_DWC3_VBUS_DISCONNECT 
#endif 

#ifndef USB3_SYNOPSYS_PHY
#define USB3_SYNOPSYS_PHY 
#endif 

#ifndef CONFIG_USB_FORCE_HIGHSPEED
#endif 

#ifndef CONFIG_TCXO_BALONG
#endif 

#ifndef FEATURE_SIM_NOTIFY
#endif 

#ifndef CONFIG_CCORE_I2C
#endif 

#ifndef CONFIG_BALONG_DPM
#endif 

#ifndef CONFIG_BALONG_HPM_TEMP
#endif 

#ifndef CONFIG_HWADP
#define CONFIG_HWADP 
#endif 

#ifndef PRODUCT_CFG_PTABLE_VER_NAME
#define PRODUCT_CFG_PTABLE_VER_NAME "HI6930_V7R2_UDP" 
#endif 

#ifndef PRODUCT_CFG_PTABLE_VER_ID			
#define PRODUCT_CFG_PTABLE_VER_ID			 "ptable 1.00" 
#endif 

#ifndef PRODUCT_CFG_FLASH_TOTAL_SIZE
#define PRODUCT_CFG_FLASH_TOTAL_SIZE 0x10000000 
#endif 

#ifndef PRODUCT_CFG_FLASH_M3BOOT_LEN     	
#define PRODUCT_CFG_FLASH_M3BOOT_LEN     	 0x40000 
#endif 

#ifndef PRODUCT_CFG_FLASH_FASTBOOT_LEN
#define PRODUCT_CFG_FLASH_FASTBOOT_LEN 0xC0000 
#endif 

#ifndef PRODUCT_CFG_FLASH_NV_LTE_LEN
#define PRODUCT_CFG_FLASH_NV_LTE_LEN 0x400000 
#endif 

#ifndef PRODUCT_CFG_FLASH_NV_IMG_LEN
#define PRODUCT_CFG_FLASH_NV_IMG_LEN 0x400000 
#endif 

#ifndef PRODUCT_CFG_FLASH_NV_DLD_LEN      	
#define PRODUCT_CFG_FLASH_NV_DLD_LEN      	 0x300000 
#endif 

#ifndef PRODUCT_CFG_FLASH_SEC_STORAGE_LEN
#define PRODUCT_CFG_FLASH_SEC_STORAGE_LEN 0 
#endif 

#ifndef PRODUCT_CFG_FLASH_NV_FACTORY_LEN   	
#define PRODUCT_CFG_FLASH_NV_FACTORY_LEN   	 0x300000 
#endif 

#ifndef PRODUCT_CFG_FLASH_OEMINFO_LEN
#define PRODUCT_CFG_FLASH_OEMINFO_LEN 0x200000 
#endif 

#ifndef PRODUCT_CFG_FLASH_YAFFS_USERDATA_LEN
#define PRODUCT_CFG_FLASH_YAFFS_USERDATA_LEN 0x600000 
#endif 

#ifndef PRODUCT_CFG_FLASH_YAFFS_ONLINE_LEN
#define PRODUCT_CFG_FLASH_YAFFS_ONLINE_LEN 0x5A00000 
#endif 

#ifndef PRODUCT_CFG_FLASH_BOOTIMG_LEN	
#define PRODUCT_CFG_FLASH_BOOTIMG_LEN	 0x600000 
#endif 

#ifndef PRODUCT_CFG_FLASH_BOOTIMGBAK_LEN	
#define PRODUCT_CFG_FLASH_BOOTIMGBAK_LEN	 0 
#endif 

#ifndef PRODUCT_CFG_FLASH_LOGO_LEN
#define PRODUCT_CFG_FLASH_LOGO_LEN 0x200000 
#endif 

#ifndef PRODUCT_CFG_FLASH_HIFI_LEN  	
#define PRODUCT_CFG_FLASH_HIFI_LEN  	 0x300000 
#endif 

#ifndef PRODUCT_CFG_FLASH_MISC_LEN
#define PRODUCT_CFG_FLASH_MISC_LEN 0x100000 
#endif 

#ifndef PRODUCT_CFG_FLASH_M3IMAGE_LEN 	
#define PRODUCT_CFG_FLASH_M3IMAGE_LEN 	 0x100000 
#endif 

#ifndef PRODUCT_CFG_FLASH_RESERVE1_LEN
#define PRODUCT_CFG_FLASH_RESERVE1_LEN 0 
#endif 

#ifndef PRODUCT_CFG_FLASH_RESERVE2_LEN
#define PRODUCT_CFG_FLASH_RESERVE2_LEN 0 
#endif 

#ifndef PRODUCT_CFG_FLASH_RESERVE3_LEN
#define PRODUCT_CFG_FLASH_RESERVE3_LEN 0 
#endif 

#ifndef PRODUCT_CFG_FLASH_OM_LEN
#define PRODUCT_CFG_FLASH_OM_LEN 0xC00000 
#endif 

#ifndef PRODUCT_CFG_FLASH_YAFFS_APP_LEN
#define PRODUCT_CFG_FLASH_YAFFS_APP_LEN 0x1000000 
#endif 

#ifndef PRODUCT_CFG_FLASH_YAFFS_WEBUI_LEN 	
#define PRODUCT_CFG_FLASH_YAFFS_WEBUI_LEN 	 0x0 
#endif 

#ifndef PRODUCT_CFG_FLASH_SYSIMG_LEN
#define PRODUCT_CFG_FLASH_SYSIMG_LEN 0x4000000 
#endif 

#ifndef PRODUCT_CFG_FLASH_DTIMG_LEN
#define PRODUCT_CFG_FLASH_DTIMG_LEN 0x00800000 
#endif 

#ifndef PRODUCT_CFG_FLASH_ISO_LEN
#define PRODUCT_CFG_FLASH_ISO_LEN 0x1000000 
#endif 

#ifndef PRODUCT_CFG_FLASH_CACHE_LEN   	
#define PRODUCT_CFG_FLASH_CACHE_LEN   	 0x400000 
#endif 

#ifndef PRODUCT_CFG_FLASH_RECOVERY_LEN
#define PRODUCT_CFG_FLASH_RECOVERY_LEN 0x400000 
#endif 

#ifndef PRODUCT_CFG_FLASH_MULTI_CARRIER_LEN
#define PRODUCT_CFG_FLASH_MULTI_CARRIER_LEN 0x00000 
#endif 

#ifndef FLASH_PTABLE_OFFSET						
#define FLASH_PTABLE_OFFSET						 0x1F800 
#endif 

#ifndef PRODUCT_CFG_FLASH_MODEM_FW_LEN
#define PRODUCT_CFG_FLASH_MODEM_FW_LEN 0x01400000 
#endif 

#ifndef MCORE_TEXT_START_ADDR
#define MCORE_TEXT_START_ADDR 0x50400000 
#endif 

#ifndef FASTBOOT_ENTRY
#define FASTBOOT_ENTRY 0x4fe00000 
#endif 

#ifndef FASTBOOT_DDR_ENTRY
#define FASTBOOT_DDR_ENTRY 0x5FD00000 
#endif 

#ifndef PRODUCT_CFG_KERNEL_ENTRY 		
#define PRODUCT_CFG_KERNEL_ENTRY 		 0x56E08000 
#endif 

#ifndef PRODUCT_KERNEL_PARAMS_PHYS		
#define PRODUCT_KERNEL_PARAMS_PHYS		 0x56E00100 
#endif 

#ifndef ONCHIP_FASTBOOT_ADDR
#define ONCHIP_FASTBOOT_ADDR 0x5F900000 
#endif 

#ifndef RTX_KERNEL_ENTRY
#define RTX_KERNEL_ENTRY 0x10000000 
#endif 

#ifndef HI_SRAM_MEM_ADDR
#define HI_SRAM_MEM_ADDR 0x4fe00000 
#endif 

#ifndef HI_SRAM_SIZE                		
#define HI_SRAM_SIZE                		 0x100000 
#endif 

#ifndef DRV_SRAM_ADDR               		
#define DRV_SRAM_ADDR               		 (HI_SRAM_MEM_ADDR) 
#endif 

#ifndef DRV_SRAM_SIZE						
#define DRV_SRAM_SIZE						 0x100000 
#endif 

#ifndef DDR_MEM_ADDR       		
#define DDR_MEM_ADDR       		 0x50000000 
#endif 

#ifndef DDR_MEM_SIZE       		
#define DDR_MEM_SIZE       		 0x10000000 
#endif 

#ifndef DDR_APP_ACP_ADDR
#define DDR_APP_ACP_ADDR (DDR_MEM_ADDR) 
#endif 

#ifndef DDR_APP_ACP_SIZE
#define DDR_APP_ACP_SIZE 0x000000 
#endif 

#ifndef DDR_GU_ADDR
#define DDR_GU_ADDR ((DDR_APP_ACP_ADDR) + (DDR_APP_ACP_SIZE)) 
#endif 

#ifndef DDR_GU_SIZE
#define DDR_GU_SIZE 0x00C0000 
#endif 

#ifndef DDR_UPA_ADDR
#define DDR_UPA_ADDR DDR_GU_ADDR 
#endif 

#ifndef DDR_UPA_SIZE
#define DDR_UPA_SIZE 0x00024000 
#endif 

#ifndef DDR_CQI_ADDR
#define DDR_CQI_ADDR ((DDR_UPA_ADDR) + (DDR_UPA_SIZE)) 
#endif 

#ifndef DDR_CQI_SIZE
#define DDR_CQI_SIZE 0x00003400 
#endif 

#ifndef DDR_APT_ADDR
#define DDR_APT_ADDR ((DDR_CQI_ADDR) + (DDR_CQI_SIZE)) 
#endif 

#ifndef DDR_APT_SIZE
#define DDR_APT_SIZE 0x00008400 
#endif 

#ifndef DDR_ET_ADDR
#define DDR_ET_ADDR ((DDR_APT_ADDR) + (DDR_APT_SIZE)) 
#endif 

#ifndef DDR_ET_SIZE
#define DDR_ET_SIZE 0x00004800 
#endif 

#ifndef DDR_NV_ADDR
#define DDR_NV_ADDR ((DDR_ET_ADDR) + (DDR_ET_SIZE)) 
#endif 

#ifndef DDR_NV_SIZE
#define DDR_NV_SIZE 0x00000000 
#endif 

#ifndef DDR_ZSP_UP_ADDR
#define DDR_ZSP_UP_ADDR ((DDR_NV_ADDR) + (DDR_NV_SIZE)) 
#endif 

#ifndef DDR_ZSP_UP_SIZE
#define DDR_ZSP_UP_SIZE 0x00008000 
#endif 

#ifndef DDR_ECS_TEE_ADDR
#define DDR_ECS_TEE_ADDR ((DDR_ZSP_UP_ADDR) + (DDR_ZSP_UP_SIZE)) 
#endif 

#ifndef DDR_ECS_TEE_SIZE
#define DDR_ECS_TEE_SIZE 0x00001800 
#endif 

#ifndef DDR_RESERVE_ADDR
#define DDR_RESERVE_ADDR ((DDR_ECS_TEE_ADDR) + (DDR_ECS_TEE_SIZE)) 
#endif 

#ifndef DDR_RESERVE_SIZE
#define DDR_RESERVE_SIZE 0x00082800 
#endif 

#ifndef DDR_TLPHY_IMAGE_ADDR     	
#define DDR_TLPHY_IMAGE_ADDR     	 ((DDR_RESERVE_ADDR) + (DDR_RESERVE_SIZE)) 
#endif 

#ifndef DDR_TLPHY_IMAGE_SIZE     	
#define DDR_TLPHY_IMAGE_SIZE     	 0x340000 
#endif 

#ifndef DDR_MCORE_ADDR
#define DDR_MCORE_ADDR (( DDR_TLPHY_IMAGE_ADDR ) + (DDR_TLPHY_IMAGE_SIZE)) 
#endif 

#ifndef DDR_MCORE_SIZE
#define DDR_MCORE_SIZE 0x5D00000 
#endif 

#ifndef DDR_MCORE_DTS_ADDR
#define DDR_MCORE_DTS_ADDR ((DDR_MCORE_ADDR) + (DDR_MCORE_SIZE)) 
#endif 

#ifndef DDR_MCORE_DTS_SIZE
#define DDR_MCORE_DTS_SIZE 0x0100000 
#endif 

#ifndef DDR_SHARED_MEM_ADDR
#define DDR_SHARED_MEM_ADDR ((DDR_MCORE_DTS_ADDR) + (DDR_MCORE_DTS_SIZE)) 
#endif 

#ifndef DDR_SHARED_MEM_SIZE
#define DDR_SHARED_MEM_SIZE 0x400000 
#endif 

#ifndef DDR_MNTN_ADDR
#define DDR_MNTN_ADDR ((DDR_SHARED_MEM_ADDR) + (DDR_SHARED_MEM_SIZE)) 
#endif 

#ifndef DDR_MNTN_SIZE
#define DDR_MNTN_SIZE 0x100000 
#endif 

#ifndef DDR_LPHY_SDR_ADDR
#define DDR_LPHY_SDR_ADDR ((DDR_MNTN_ADDR) + (DDR_MNTN_SIZE)) 
#endif 

#ifndef DDR_LPHY_SDR_SIZE
#define DDR_LPHY_SDR_SIZE 0x280000 
#endif 

#ifndef DDR_LCS_ADDR
#define DDR_LCS_ADDR ((DDR_LPHY_SDR_ADDR) + (DDR_LPHY_SDR_SIZE)) 
#endif 

#ifndef DDR_LCS_SIZE
#define DDR_LCS_SIZE 0x280000 
#endif 

#ifndef DDR_HIFI_ADDR
#define DDR_HIFI_ADDR ((DDR_LCS_ADDR) + (DDR_LCS_SIZE)) 
#endif 

#ifndef DDR_HIFI_SIZE
#define DDR_HIFI_SIZE 0x200000 
#endif 

#ifndef DDR_ACORE_ADDR
#define DDR_ACORE_ADDR ((DDR_HIFI_ADDR) + (DDR_HIFI_SIZE)) 
#endif 

#ifndef DDR_ACORE_SIZE
#define DDR_ACORE_SIZE 0x2E00000 
#endif 

#ifndef DDR_ACORE_DTS_ADDR
#define DDR_ACORE_DTS_ADDR ((DDR_ACORE_ADDR) + (DDR_ACORE_SIZE)) 
#endif 

#ifndef DDR_ACORE_DTS_SIZE
#define DDR_ACORE_DTS_SIZE 0x0100000 
#endif 

#ifndef DDR_SOCP_ADDR
#define DDR_SOCP_ADDR ((DDR_ACORE_DTS_ADDR) + (DDR_ACORE_DTS_SIZE)) 
#endif 

#ifndef DDR_SOCP_SIZE
#define DDR_SOCP_SIZE 0x300000 
#endif 

#ifndef DDR_MDM_ACP_ADDR
#define DDR_MDM_ACP_ADDR ((DDR_SOCP_ADDR) + (DDR_SOCP_SIZE)) 
#endif 

#ifndef DDR_MDM_ACP_SIZE
#define DDR_MDM_ACP_SIZE 0x0 
#endif 

#ifndef GLOBAL_AXI_TEMP_PROTECT_ADDR
#define GLOBAL_AXI_TEMP_PROTECT_ADDR 0x4FE1FF1C 
#endif 

#ifndef GLOBAL_AXI_TEMP_PROTECT_SIZE
#define GLOBAL_AXI_TEMP_PROTECT_SIZE (128) 
#endif 

#ifndef DDR_HIFI_MBX_ADDR
#define DDR_HIFI_MBX_ADDR (DDR_SHARED_MEM_ADDR) 
#endif 

#ifndef DDR_HIFI_MBX_SIZE
#define DDR_HIFI_MBX_SIZE (0X9800) 
#endif 

#ifndef NV_DDR_SIZE
#define NV_DDR_SIZE 0x200000 
#endif 

#ifndef SHM_SIZE_HIFI_MBX
#define SHM_SIZE_HIFI_MBX (DDR_HIFI_MBX_SIZE) 
#endif 

#ifndef SHM_SIZE_HIFI
#define SHM_SIZE_HIFI (10*1024) 
#endif 

#ifndef SHM_SIZE_TLPHY
#define SHM_SIZE_TLPHY (12*1024) 
#endif 

#ifndef SHM_SIZE_TEMPERATURE
#define SHM_SIZE_TEMPERATURE (3*1024) 
#endif 

#ifndef SHM_SIZE_DDM_LOAD
#define SHM_SIZE_DDM_LOAD (1*1024) 
#endif 

#ifndef SHM_SIZE_MEM_APPA9_PM_BOOT
#define SHM_SIZE_MEM_APPA9_PM_BOOT (0x10000) 
#endif 

#ifndef SHM_SIZE_MEM_MDMA9_PM_BOOT
#define SHM_SIZE_MEM_MDMA9_PM_BOOT (0x2000) 
#endif 

#ifndef SHM_SIZE_TENCILICA_MULT_BAND
#define SHM_SIZE_TENCILICA_MULT_BAND (0x8000) 
#endif 

#ifndef SHM_SIZE_ICC
#define SHM_SIZE_ICC (0x61800) 
#endif 

#ifndef SHM_SIZE_IPF
#define SHM_SIZE_IPF (0x10000) 
#endif 

#ifndef SHM_SIZE_PSAM
#define SHM_SIZE_PSAM (0) 
#endif 

#ifndef SHM_SIZE_WAN
#define SHM_SIZE_WAN (0x8000) 
#endif 

#ifndef SHM_SIZE_NV
#define SHM_SIZE_NV (NV_DDR_SIZE) 
#endif 

#ifndef SHM_SIZE_M3_MNTN
#define SHM_SIZE_M3_MNTN (0x20000) 
#endif 

#ifndef SHM_SIZE_TIMESTAMP
#define SHM_SIZE_TIMESTAMP (1*1024) 
#endif 

#ifndef SHM_SIZE_IOS
#define SHM_SIZE_IOS (6*1024) 
#endif 

#ifndef SHM_SIZE_RESTORE_AXI
#define SHM_SIZE_RESTORE_AXI (96*1024) 
#endif 

#ifndef SHM_SIZE_PMU
#define SHM_SIZE_PMU (3*1024) 
#endif 

#ifndef SHM_SIZE_PTABLE
#define SHM_SIZE_PTABLE (2*1024) 
#endif 

#ifndef SHM_SIZE_CCORE_RESET
#define SHM_SIZE_CCORE_RESET (0x400) 
#endif 

#ifndef SHM_SIZE_PM_OM
#define SHM_SIZE_PM_OM (256*1024) 
#endif 

#ifndef SHM_SIZE_M3PM
#define SHM_SIZE_M3PM (0x1000) 
#endif 

#ifndef SHM_SIZE_SLICE_MEM
#define SHM_SIZE_SLICE_MEM (0x1000) 
#endif 

#ifndef SHM_SIZE_OSA_LOG
#define SHM_SIZE_OSA_LOG (1024) 
#endif 

#ifndef SHM_SIZE_WAS_LOG
#define SHM_SIZE_WAS_LOG (1024) 
#endif 

#ifndef SHM_SIZE_SRAM_BAK
#define SHM_SIZE_SRAM_BAK (HI_SRAM_SIZE) 
#endif 

#ifndef SHM_SIZE_SRAM_TO_DDR
#define SHM_SIZE_SRAM_TO_DDR (0) 
#endif 

#ifndef SHM_SIZE_M3RSRACC_BD
#define SHM_SIZE_M3RSRACC_BD (0) 
#endif 

#ifndef FEATURE_ON
#define FEATURE_ON 1 
#endif 

#ifndef FEATURE_OFF
#define FEATURE_OFF 0 
#endif 

#ifndef MEMORY_SIZE_32M
#define MEMORY_SIZE_32M 1 
#endif 

#ifndef MEMORY_SIZE_64M
#define MEMORY_SIZE_64M 2 
#endif 

#ifndef MEMORY_SIZE_128M
#define MEMORY_SIZE_128M 3 
#endif 

#ifndef MEMORY_SIZE_256M
#define MEMORY_SIZE_256M 4 
#endif 

#ifndef MEMORY_SIZE_512M
#define MEMORY_SIZE_512M 5 
#endif 

#ifndef FEATURE_HIFI_USE_ICC
#define FEATURE_HIFI_USE_ICC FEATURE_OFF 
#endif 

#ifndef FEATURE_MULTI_MODEM
#define FEATURE_MULTI_MODEM FEATURE_OFF 
#endif 

#ifndef FEATURE_SOCP_ON_DEMAND
#define FEATURE_SOCP_ON_DEMAND FEATURE_OFF 
#endif 

#ifndef FEATURE_SOCP_DECODE_INT_TIMEOUT
#define FEATURE_SOCP_DECODE_INT_TIMEOUT FEATURE_OFF 
#endif 

#ifndef FEATURE_RTOSCK
#define FEATURE_RTOSCK FEATURE_ON 
#endif 

#ifndef FEATURE_VISP_VPP				
#define FEATURE_VISP_VPP				 FEATURE_ON 
#endif 

#ifndef FEATURE_GU_DSP_SPLIT
#define FEATURE_GU_DSP_SPLIT FEATURE_OFF 
#endif 

#ifndef FEATURE_UE_MODE_CDMA
#define FEATURE_UE_MODE_CDMA FEATURE_OFF 
#endif 

#ifndef FEATURE_CHINA_TELECOM_VOICE_ENCRYPT
#define FEATURE_CHINA_TELECOM_VOICE_ENCRYPT FEATURE_OFF 
#endif 

#ifndef FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE
#define FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE FEATURE_OFF 
#endif 

#ifndef FEATURE_BASTET
#define FEATURE_BASTET FEATURE_OFF 
#endif 

#ifndef FEATURE_NV_PARTRION_MULTIPLEX
#define FEATURE_NV_PARTRION_MULTIPLEX FEATURE_ON 
#endif 

#ifndef BBP_MASTER_INT_MODE
#define BBP_MASTER_INT_MODE FEATURE_ON 
#endif 

#ifndef FEATURE_HUAWEI_VP
#define FEATURE_HUAWEI_VP FEATURE_OFF 
#endif 

#ifndef FEATURE_LTE_R11
#define FEATURE_LTE_R11 FEATURE_ON 
#endif 

#ifndef FEATURE_LTE_MBMS
#define FEATURE_LTE_MBMS FEATURE_OFF 
#endif 

#ifndef FEATURE_LTE_NAS_R11
#define FEATURE_LTE_NAS_R11 FEATURE_OFF 
#endif 

#ifndef FEATURE_LPP
#define FEATURE_LPP FEATURE_OFF 
#endif 

#ifndef FEATURE_LTE_CDMA_R11
#define FEATURE_LTE_CDMA_R11 FEATURE_OFF 
#endif 

#ifndef FEATURE_BALONG_CL
#define FEATURE_BALONG_CL FEATURE_UE_MODE_CDMA 
#endif 

#ifndef FEATURE_TDS_WCDMA_DYNAMIC_LOAD
#define FEATURE_TDS_WCDMA_DYNAMIC_LOAD FEATURE_OFF 
#endif 

#ifndef FEATURE_CSG
#define FEATURE_CSG FEATURE_OFF 
#endif 

#ifndef FEATURE_CSS_CLOUD_MEMORY_IMPROVE
#define FEATURE_CSS_CLOUD_MEMORY_IMPROVE FEATURE_OFF 
#endif 

#endif /*__PRODUCT_CONFIG_H__*/ 
