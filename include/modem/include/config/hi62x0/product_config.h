/* MD5: ae8a0450c191fa5d106ea1af30620677*/
#if !defined(__PRODUCT_CONFIG_H__)
#define __PRODUCT_CONFIG_H__

#ifndef BALONG_OBUILD_VERSION
#define BALONG_OBUILD_VERSION 10 
#endif 

#ifndef PRODUCT_NAME
#define PRODUCT_NAME "hi6250" 
#endif 

#ifndef PRODUCT_CFG_CHIP_SOLUTION_NAME
#define PRODUCT_CFG_CHIP_SOLUTION_NAME "Balong" 
#endif 

#ifndef BUILD_TYPE
#define BUILD_TYPE RELEASE 
#endif 

#ifndef PRODUCT_VERSION
#define PRODUCT_VERSION K300V300C00B000 
#endif 

#ifndef PRODUCT_VERSION_STR
#define PRODUCT_VERSION_STR "K300V300C00B000" 
#endif 

#ifndef PRODUCT_FULL_VERSION_STR
#define PRODUCT_FULL_VERSION_STR "Dallas V100R001C10B101" 
#endif 

#ifndef PRODUCT_FILE_VERSION_STR
#define PRODUCT_FILE_VERSION_STR "2.1.6.8" 
#endif 

#ifndef PRODUCT_DLOAD_SOFTWARE_VER		
#define PRODUCT_DLOAD_SOFTWARE_VER		 "21.150.00.00.031" 
#endif 

#ifndef PLATFORM
#define PLATFORM hi6250 
#endif 

#ifndef PLATFORM_CHIP_TYPE
#define PLATFORM_CHIP_TYPE hi6250 
#endif 

#ifndef CONFIG_DYNAMIC_LOAD
#define CONFIG_DYNAMIC_LOAD 
#endif 

#ifndef FEATURE_MULTIMODE_GUL
#define FEATURE_MULTIMODE_GUL 
#endif 

#ifndef OS_PATH
#define OS_PATH config/product/hi6250/os 
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
#define OS_LINUX_PRODUCT_NAME hisi_6250_defconfig 
#endif 

#ifndef OS_K3V3_USE_LPM3_API
#define OS_K3V3_USE_LPM3_API 
#endif 

#ifndef BSP_CONFIG_HI3650
#define BSP_CONFIG_HI3650 
#endif 

#ifndef BSP_CONFIG_HI6250
#define BSP_CONFIG_HI6250 
#endif 

#ifndef BSP_CONFIG_BOARD_SFT
#endif 

#ifndef BSP_CONFIG_EDA
#endif 

#ifndef BSP_CONFIG_EMU
#endif 

#ifndef BSP_CONFIG_NOT_DDR_BYPASSPLL
#endif 

#ifndef BSP_ENABLE_SEC_VERIFY
#endif 

#ifndef BSP_HAS_SEC_FEATURE
#endif 

#ifndef BSP_ICC_MCHANNEL_USE_LPM3TCM
#define BSP_ICC_MCHANNEL_USE_LPM3TCM 
#endif 

#ifndef BSP_MONITOR_DEBUG_UNSET
#define BSP_MONITOR_DEBUG_UNSET 
#endif 

#ifndef PLATFORM_HISI_BALONG
#define PLATFORM_HISI_BALONG hi6250 
#endif 

#ifndef FEATURE_ON
#define FEATURE_ON 1 
#endif 

#ifndef FEATURE_OFF
#define FEATURE_OFF 0 
#endif 

#ifndef PRODUCT_CONTROL_VERSION
#define PRODUCT_CONTROL_VERSION "121" 
#endif 

#ifndef PRODUCT_HISILICON_VERSION
#define PRODUCT_HISILICON_VERSION hi6250 
#endif 

#ifndef PRODUCT_NV_SPLITFILE
#define PRODUCT_NV_SPLITFILE binfilesplit "0" 
#endif 

#ifndef PRODUCT_NV_FILE_MAX_SIZE
#define PRODUCT_NV_FILE_MAX_SIZE binfileLimitSize "100" 
#endif 

#ifndef PRODUCT_NV_BIN_MODEM_NUNBER
#define PRODUCT_NV_BIN_MODEM_NUNBER bin_modem_number "2" 
#endif 

#ifndef PRODUCT_NV_XNV_MODEM_NUNBER
#define PRODUCT_NV_XNV_MODEM_NUNBER xnv_modem_number "2" 
#endif 

#ifndef PRODUCT_NV_XNV_SUPPORT_PRODUCT_CAT
#define PRODUCT_NV_XNV_SUPPORT_PRODUCT_CAT xnv_support_product_cat "1" 
#endif 

#ifndef PRODUCT_NV_XNV_PDT_VERSION
#define PRODUCT_NV_XNV_PDT_VERSION v8r5_udp 
#endif 

#ifndef MCORE_TEXT_START_ADDR
#define MCORE_TEXT_START_ADDR 0x38400000 
#endif 

#ifndef RTX_KERNEL_ENTRY
#define RTX_KERNEL_ENTRY 0x10000000 
#endif 

#ifndef HI_SRAM_MEM_ADDR
#define HI_SRAM_MEM_ADDR 0xE0800000 
#endif 

#ifndef HI_SRAM_SIZE
#define HI_SRAM_SIZE 0x4000 
#endif 

#ifndef DRV_SRAM_ADDR
#define DRV_SRAM_ADDR (HI_SRAM_MEM_ADDR) 
#endif 

#ifndef DRV_SRAM_SIZE				
#define DRV_SRAM_SIZE				 0x2000 
#endif 

#ifndef DDR_MEM_ADDR
#define DDR_MEM_ADDR 0x38000000 
#endif 

#ifndef DDR_MEM_SIZE
#define DDR_MEM_SIZE 0x09400000 
#endif 

#ifndef DDR_SECMEM_SIZE
#define DDR_SECMEM_SIZE 0x07C00000 
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
#define DDR_GU_SIZE 0x000C0000 
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

#ifndef DDR_MDM_GU_RESERVE_ADDR
#define DDR_MDM_GU_RESERVE_ADDR ((DDR_ECS_TEE_ADDR) + (DDR_ECS_TEE_SIZE)) 
#endif 

#ifndef DDR_MDM_GU_RESERVE_SIZE
#define DDR_MDM_GU_RESERVE_SIZE 0x00082800 
#endif 

#ifndef DDR_EVDO_ADDR
#define DDR_EVDO_ADDR DDR_MDM_GU_RESERVE_ADDR 
#endif 

#ifndef DDR_EVDO_SIZE
#define DDR_EVDO_SIZE 0x00003C00 
#endif 

#ifndef DDR_1X_ADDR
#define DDR_1X_ADDR ((DDR_EVDO_ADDR) + (DDR_EVDO_SIZE)) 
#endif 

#ifndef DDR_1X_SIZE
#define DDR_1X_SIZE 0x00012C00 
#endif 

#ifndef DDR_RESERVE_ADDR
#define DDR_RESERVE_ADDR ((DDR_1X_ADDR) + (DDR_1X_SIZE)) 
#endif 

#ifndef DDR_RESERVE_SIZE
#define DDR_RESERVE_SIZE CFG_DDR_MDM_GU_RESERVE_SIZE 
#endif 

#ifndef CSDR_DDR_RAM_BASE
#define CSDR_DDR_RAM_BASE DDR_EVDO_ADDR 
#endif 

#ifndef DDR_TLPHY_IMAGE_ADDR     	
#define DDR_TLPHY_IMAGE_ADDR     	 ((DDR_MDM_GU_RESERVE_ADDR) + (DDR_MDM_GU_RESERVE_SIZE)) 
#endif 

#ifndef DDR_TLPHY_IMAGE_SIZE     	
#define DDR_TLPHY_IMAGE_SIZE     	 0x340000 
#endif 

#ifndef DDR_MCORE_ADDR
#define DDR_MCORE_ADDR (( DDR_TLPHY_IMAGE_ADDR ) + (DDR_TLPHY_IMAGE_SIZE)) 
#endif 

#ifndef DDR_MCORE_SIZE
#define DDR_MCORE_SIZE 0x7100000 
#endif 

#ifndef DDR_MCORE_DTS_ADDR
#define DDR_MCORE_DTS_ADDR ((DDR_MCORE_ADDR) + (DDR_MCORE_SIZE)) 
#endif 

#ifndef DDR_MCORE_DTS_SIZE
#define DDR_MCORE_DTS_SIZE 0x0100000 
#endif 

#ifndef DDR_CBBE_IMAGE_ADDR
#define DDR_CBBE_IMAGE_ADDR ((DDR_MCORE_DTS_ADDR) + (DDR_MCORE_DTS_SIZE)) 
#endif 

#ifndef DDR_CBBE_IMAGE_SIZE
#define DDR_CBBE_IMAGE_SIZE 0x100000 
#endif 

#ifndef DDR_LPHY_SDR_ADDR		
#define DDR_LPHY_SDR_ADDR		 ((DDR_CBBE_IMAGE_ADDR) + (DDR_CBBE_IMAGE_SIZE)) 
#endif 

#ifndef DDR_LPHY_SDR_SIZE     	
#define DDR_LPHY_SDR_SIZE     	 0x200000 
#endif 

#ifndef DDR_LCS_ADDR
#define DDR_LCS_ADDR ((DDR_LPHY_SDR_ADDR) + (DDR_LPHY_SDR_SIZE)) 
#endif 

#ifndef DDR_LCS_SIZE
#define DDR_LCS_SIZE 0x280000 
#endif 

#ifndef DDR_MDM_RESERVED_ADDR
#define DDR_MDM_RESERVED_ADDR ((DDR_LCS_ADDR) + (DDR_LCS_SIZE)) 
#endif 

#ifndef DDR_MDM_RESERVED_SIZE
#define DDR_MDM_RESERVED_SIZE 0x80000 
#endif 

#ifndef DDR_ACORE_ADDR
#define DDR_ACORE_ADDR ((DDR_MDM_RESERVED_ADDR) + (DDR_MDM_RESERVED_SIZE)) 
#endif 

#ifndef DDR_ACORE_SIZE
#define DDR_ACORE_SIZE 0x0 
#endif 

#ifndef DDR_ACORE_DTS_ADDR
#define DDR_ACORE_DTS_ADDR ((DDR_ACORE_ADDR) + (DDR_ACORE_SIZE)) 
#endif 

#ifndef DDR_ACORE_DTS_SIZE
#define DDR_ACORE_DTS_SIZE 0x0 
#endif 

#ifndef DDR_MDM_ACP_ADDR
#define DDR_MDM_ACP_ADDR ((DDR_ACORE_DTS_ADDR) + (DDR_ACORE_DTS_SIZE)) 
#endif 

#ifndef DDR_MDM_ACP_SIZE
#define DDR_MDM_ACP_SIZE 0x0 
#endif 

#ifndef DDR_SHARED_MEM_ADDR
#define DDR_SHARED_MEM_ADDR ((DDR_MEM_ADDR) + (DDR_SECMEM_SIZE)) 
#endif 

#ifndef DDR_SHARED_MEM_SIZE
#define DDR_SHARED_MEM_SIZE 0x00300000 
#endif 

#ifndef DDR_HIFI_MBX_ADDR			
#define DDR_HIFI_MBX_ADDR			 (DDR_SHARED_MEM_ADDR) 
#endif 

#ifndef DDR_HIFI_MBX_SIZE			
#define DDR_HIFI_MBX_SIZE			 (0X9800) 
#endif 

#ifndef DDR_MNTN_ADDR
#define DDR_MNTN_ADDR ((DDR_SHARED_MEM_ADDR) + (DDR_SHARED_MEM_SIZE)) 
#endif 

#ifndef DDR_MNTN_SIZE
#define DDR_MNTN_SIZE (0x00100000) 
#endif 

#ifndef DDR_SOCP_ADDR
#define DDR_SOCP_ADDR ((DDR_MNTN_ADDR) + (DDR_MNTN_SIZE)) 
#endif 

#ifndef DDR_SOCP_SIZE
#define DDR_SOCP_SIZE 0x01100000 
#endif 

#ifndef DDR_HIFI_ADDR
#define DDR_HIFI_ADDR ((DDR_SOCP_ADDR) + (DDR_SOCP_SIZE)) 
#endif 

#ifndef DDR_HIFI_SIZE
#define DDR_HIFI_SIZE 0x00900000 
#endif 

#ifndef CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE
#define CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE 0x8000 
#endif 

#ifndef CORESHARE_MEM_TENCILICA_MULT_BAND_ADDR
#define CORESHARE_MEM_TENCILICA_MULT_BAND_ADDR DDR_SHARED_MEM_ADDR 
#endif 

#ifndef CONFIG_VERSION_STUB
#endif 

#ifndef HW_VERSION_STUB
#define HW_VERSION_STUB 0x35FFFFFB 
#endif 

#ifndef CONFIG_VER_MASK
#define CONFIG_VER_MASK 0x35000000 
#endif 

#ifndef FEATURE_OBJ_CMP 				
#endif 

#ifndef FEATURE_OBJ_DUMP				
#endif 

#ifndef BSP_ENBALE_PACK_IMAGE			
#define BSP_ENBALE_PACK_IMAGE			 
#endif 

#ifndef CONFIG_SMART_SYSTEM_MODEM
#endif 

#ifndef CONFIG_OF
#define CONFIG_OF 
#endif 

#ifndef CONFIG_BALONG_L2CACHE
#define CONFIG_BALONG_L2CACHE 
#endif 

#ifndef CONFIG_FASTBOOT_DEBUG
#endif 

#ifndef CONFIG_FASTBOOT_UART_NUM
#define CONFIG_FASTBOOT_UART_NUM 0 
#endif 

#ifndef CONFIG_UART_ARM
#define CONFIG_UART_ARM 
#endif 

#ifndef CONFIG_UART_SYNOPSYS
#endif 

#ifndef CONFIG_GPIO_PL061
#define CONFIG_GPIO_PL061 
#endif 

#ifndef CONFIG_GPIO_SYNOPSYS
#endif 

#ifndef ROM_COMPRESS
#endif 

#ifndef CONFIG_COMPRESS_CCORE_IMAGE
#endif 

#ifndef CONFIG_MODULE_VIC
#endif 

#ifndef CONFIG_PCIE_CFG
#endif 

#ifndef CONFIG_PASTAR_DSM
#endif 

#ifndef CONFIG_CIPHER
#define CONFIG_CIPHER 
#endif 

#ifndef CONFIG_AT_UART
#endif 

#ifndef CONFIG_CIPHER_ENABLE_BBPPLL
#define CONFIG_CIPHER_ENABLE_BBPPLL 
#endif 

#ifndef CONFIG_CSHELL
#define CONFIG_CSHELL 
#endif 

#ifndef CONFIG_IPF
#define CONFIG_IPF 
#endif 

#ifndef CONFIG_PSAM
#define CONFIG_PSAM 
#endif 

#ifndef CONFIG_MODULE_BUSSTRESS
#endif 

#ifndef CONFIG_ICC
#define CONFIG_ICC 
#endif 

#ifndef CONFIG_PM_OM
#define CONFIG_PM_OM 
#endif 

#ifndef CONFIG_MEM
#define CONFIG_MEM 
#endif 

#ifndef CONFIG_MDDR_WINBOND
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
#endif 

#ifndef CONFIG_PHONE_PLATFORM
#define CONFIG_PHONE_PLATFORM 
#endif 

#ifndef CONFIG_PMU_NEW
#define CONFIG_PMU_NEW 
#endif 

#ifndef CONFIG_COUL
#endif 

#ifndef CONFIG_SPI
#endif 

#ifndef CONFIG_SFLASH
#endif 

#ifndef CONFIG_AUDIO
#endif 

#ifndef CONFIG_SIO
#endif 

#ifndef CONFIG_ABB
#define CONFIG_ABB 
#endif 

#ifndef CONFIG_DSP
#define CONFIG_DSP 
#endif 

#ifndef CONFIG_CBBE
#define CONFIG_CBBE 
#endif 

#ifndef CONFIG_HIFI
#endif 

#ifndef CONFIG_HKADC
#define CONFIG_HKADC 
#endif 

#ifndef CONFIG_ONOFF
#define CONFIG_ONOFF 
#endif 

#ifndef CONFIG_TUNER
#endif 

#ifndef CONFIG_CROSS_MIPI
#endif 

#ifndef CONFIG_HW_SPINLOCK
#endif 

#ifndef CONFIG_BBP
#define CONFIG_BBP 
#endif 

#ifndef BSP_CONFIG_BBP_V3650
#endif 

#ifndef FEATURE_WIFI_ON
#endif 

#ifndef FEATURE_BCM_VERSION
#define FEATURE_BCM_VERSION 43241 
#endif 

#ifndef CONFIG_NVIM
#define CONFIG_NVIM 
#endif 

#ifndef CONFIG_SC
#define CONFIG_SC 
#endif 

#ifndef NV_DDR_SIZE       				
#define NV_DDR_SIZE       				 (0x180000) 
#endif 

#ifndef FEATURE_NV_FLASH_ON
#endif 

#ifndef FEATURE_NV_EMMC_ON
#define FEATURE_NV_EMMC_ON 
#endif 

#ifndef FEATURE_NV_LFILE_ON
#endif 

#ifndef FEATURE_NV_RFILE_ON
#endif 

#ifndef CONFIG_MULTI_CARRIER
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
#endif 

#ifndef CONFIG_PA_RF
#endif 

#ifndef FEATURE_CPHY_MAILBOX
#define FEATURE_CPHY_MAILBOX 
#endif 

#ifndef CONFIG_RFFE_MIPI
#endif 

#ifndef CONFIG_RFFE_ANTEN
#endif 

#ifndef CONFIG_RFFE_POWER
#define CONFIG_RFFE_POWER 
#endif 

#ifndef CONFIG_PASTAR
#endif 

#ifndef CONFIG_PASTAR_DPM_M3
#endif 

#ifndef CONFIG_MIPI
#define CONFIG_MIPI 
#endif 

#ifndef MODEM_MEM_REPAIR
#endif 

#ifndef ENABLE_SHELL_SYM
#define ENABLE_SHELL_SYM 
#endif 

#ifndef ENABLE_DEBUG
#define ENABLE_DEBUG 
#endif 

#ifndef RTOSCK_CCORE_COMPONENTS
#define RTOSCK_CCORE_COMPONENTS bsp_ccore.o gumsp_mcore.o nas_ccore.o rabm_ccore.o gas_ccore.o was_ccore.o ttf_ccore.o ascomm_ccore.o pscomm_ccore.o encodix_ccore.o taf_ccore.o tlas_ccore.o tlnas_ccore.o lmsp_ccore.o gudsp_mcore.o gudsp_comm_RT.o gudsp_mcore_RT.o 
#endif 

#ifndef CCORE_COMPONENTS
#define CCORE_COMPONENTS bsp_ccore.o gumsp_mcore.o nas_ccore.o rabm_ccore.o gas_ccore.o was_ccore.o ttf_ccore.o ascomm_ccore.o pscomm_ccore.o encodix_ccore.o taf_ccore.o tlas_ccore.o tlnas_ccore.o lmsp_ccore.o gudsp_mcore.o gudsp_comm_RT.o gudsp_mcore_RT.o os_ccore.o 
#endif 

#ifndef CCORE_MODEM1_COMPONENTS
#define CCORE_MODEM1_COMPONENTS bsp_ccore1.o nas1_ccore.o rabm1_ccore.o gas1_ccore.o taf1_ccore.o ascomm1_ccore.o pscomm1_ccore.o encodix1_ccore.o gumsp1_mcore.o gudsp1_mcore.o gudsp1_mcore_RT.o ttf1_ccore.o 
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

#ifndef ENABLE_BUILD_SYSVIEW
#endif 

#ifndef ENABLE_BUILD_CPUVIEW
#endif 

#ifndef ENABLE_BUILD_MEMVIEW
#endif 

#ifndef ENABLE_BUILD_AMON
#define ENABLE_BUILD_AMON 
#endif 

#ifndef ENABLE_BUILD_UTRACE
#endif 

#ifndef CONFIG_CORESIGHT
#define CONFIG_CORESIGHT 
#endif 

#ifndef CONFIG_ETB
#define CONFIG_ETB 
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
#define CONFIG_BALONG_CCLK 
#endif 

#ifndef FEATURE_E5_ONOFF
#endif 

#ifndef CONFIG_CCORE_PM
#define CONFIG_CCORE_PM 
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

#ifndef CONFIG_RSE
#endif 

#ifndef CONFIG_LEDS_CCORE
#endif 

#ifndef CONFIG_HAS_CCORE_WAKELOCK
#define CONFIG_HAS_CCORE_WAKELOCK 
#endif 

#ifndef CONFIG_CCORE_BALONG_PM
#define CONFIG_CCORE_BALONG_PM 
#endif 

#ifndef CONFIG_BALONG_EDMA
#define CONFIG_BALONG_EDMA 
#endif 

#ifndef CONFIG_BALONG_EDMA_TEST
#endif 

#ifndef CONFIG_DUAL_MODEM
#endif 

#ifndef CONFIG_I2C_TEST	
#endif 

#ifndef CONFIG_IPF_VESION
#define CONFIG_IPF_VESION 1 
#endif 

#ifndef CONFIG_IPF_ADQ_LEN
#define CONFIG_IPF_ADQ_LEN 3 
#endif 

#ifndef CONFIG_IPF_BACKUP_ON_LPM3
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
#define CONFIG_TEMPERATURE_PROTECT 
#endif 

#ifndef CONFIG_MODEM_PINTRL
#define CONFIG_MODEM_PINTRL 
#endif 

#ifndef CONFIG_EFUSE
#define CONFIG_EFUSE 
#endif 

#ifndef CONFIG_BURN_EFUSE_NANDC
#endif 

#ifndef CONFIG_DDM
#define CONFIG_DDM 
#endif 

#ifndef CONFIG_TSENSOR
#endif 

#ifndef CONFIG_DESIGNWARE_I2C
#endif 

#ifndef CONFIG_USB_DWC3_VBUS_DISCONNECT
#endif 

#ifndef USB3_SYNOPSYS_PHY
#endif 

#ifndef CONFIG_USB_FORCE_HIGHSPEED
#endif 

#ifndef CONFIG_PWC_MNTN_CCORE
#endif 

#ifndef CONFIG_TCXO_BALONG
#endif 

#ifndef FEATURE_SIM_NOTIFY
#endif 

#ifndef CONFIG_CCORE_I2C
#endif 

#ifndef CONFIG_BALONG_MODEM_RESET
#endif 

#ifndef CONFIG_LOAD_SEC_IMAGE
#define CONFIG_LOAD_SEC_IMAGE 
#endif 

#ifndef CONFIG_HIFI_RESET
#endif 

#ifndef CONFIG_BALONG_HPM_TEMP
#endif 

#ifndef CONFIG_ARM_ENABLE_DTS
#endif 

#ifndef DTS_NAME
#define DTS_NAME v711 
#endif 

#ifndef CONFIG_HWADP
#define CONFIG_HWADP 
#endif 

#ifndef CONFIG_SYSCTRL
#define CONFIG_SYSCTRL 
#endif 

#ifndef CONFIG_SYSCTRL_TEST
#endif 

#ifndef CONFIG_S_MEMORY
#define CONFIG_S_MEMORY 
#endif 

#ifndef CONFIG_S_MEMORY_TEST
#endif 

#ifndef CONFIG_M2M_HSUART
#endif 

#ifndef FEATURE_STICK								
#define FEATURE_STICK								 FEATURE_OFF 
#endif 

#ifndef FEATURE_HILINK
#define FEATURE_HILINK FEATURE_OFF 
#endif 

#ifndef FEATURE_SOCP_DECODE_INT_TIMEOUT
#define FEATURE_SOCP_DECODE_INT_TIMEOUT FEATURE_OFF 
#endif 

#ifndef FEATURE_SOCP_ON_DEMAND			
#define FEATURE_SOCP_ON_DEMAND			 FEATURE_OFF 
#endif 

#ifndef FEATURE_DELAY_MODEM_INIT
#define FEATURE_DELAY_MODEM_INIT FEATURE_ON 
#endif 

#ifndef FEATURE_MERGE_OM_CHAN						
#define FEATURE_MERGE_OM_CHAN						 FEATURE_ON 
#endif 

#ifndef FEATURE_SOCP_CHANNEL_REDUCE
#define FEATURE_SOCP_CHANNEL_REDUCE FEATURE_OFF 
#endif 

#ifndef FEATURE_SAMPLE_LTE_CHAN 			
#define FEATURE_SAMPLE_LTE_CHAN 			 FEATURE_OFF 
#endif 

#ifndef FEATURE_MULTI_CHANNEL			
#define FEATURE_MULTI_CHANNEL			 FEATURE_OFF 
#endif 

#ifndef FEATURE_BSP_LCH_OM
#define FEATURE_BSP_LCH_OM FEATURE_ON 
#endif 

#ifndef FEATURE_IMS
#define FEATURE_IMS FEATURE_OFF 
#endif 

#ifndef FEATURE_DFS_SYNC							
#define FEATURE_DFS_SYNC							 FEATURE_OFF 
#endif 

#ifndef FEATURE_TLPHY_SINGLE_XO								
#define FEATURE_TLPHY_SINGLE_XO								 
#endif 

#ifndef PRODUCT_HISILICON_VERSION
#define PRODUCT_HISILICON_VERSION hi6250 
#endif 

#ifndef XTENSA_CORE_X_CACHE             			
#define XTENSA_CORE_X_CACHE             			 v8r5_dallas_cbbe16 
#endif 

#ifndef XTENSA_CORE				
#define XTENSA_CORE				 v8r5_dallas_bbe16 
#endif 

#ifndef XTENSA_SYSTEM			
#define XTENSA_SYSTEM			 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RD-2012.5-linux/$(CFG_XTENSA_CORE)/config 
#endif 

#ifndef TENSILICA_BUILDS	
#define TENSILICA_BUILDS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RD-2012.5-linux 
#endif 

#ifndef TENSILICA_TOOLS	
#define TENSILICA_TOOLS	 $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RD-2012.5-linux 
#endif 

#ifndef TENSILICA_BUILDS_HIFI
#define TENSILICA_BUILDS_HIFI $(ROOT_XTENSA_PATH_W)/XtDevTools/install/builds/RD-2012.5-linux 
#endif 

#ifndef TENSILICA_TOOLS_HIFI
#define TENSILICA_TOOLS_HIFI $(ROOT_XTENSA_PATH_W)/XtDevTools/install/tools/RD-2012.5-linux 
#endif 

#ifndef LPHY_PUB_DTCM_BASE	
#define LPHY_PUB_DTCM_BASE	 0x72700000 
#endif 

#ifndef LPHY_PUB_ITCM_BASE	
#define LPHY_PUB_ITCM_BASE	 0x72800000 
#endif 

#ifndef LPHY_PRV_DTCM_BASE	
#define LPHY_PRV_DTCM_BASE	 0x72758000 
#endif 

#ifndef LPHY_PRV_ITCM_BASE	
#define LPHY_PRV_ITCM_BASE	 0x72858000 
#endif 

#ifndef LPHY_PUB_DTCM_SIZE		
#define LPHY_PUB_DTCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PUB_ITCM_SIZE		
#define LPHY_PUB_ITCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PRV_DTCM_SIZE		
#define LPHY_PRV_DTCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_PRV_ITCM_SIZE		
#define LPHY_PRV_ITCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_LTE_DTCM_SIZE		
#define LPHY_LTE_DTCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_LTE_ITCM_SIZE		
#define LPHY_LTE_ITCM_SIZE		 0x58000 
#endif 

#ifndef LPHY_TDS_DTCM_SIZE		
#define LPHY_TDS_DTCM_SIZE		 0x30000 
#endif 

#ifndef LPHY_TDS_ITCM_SIZE		
#define LPHY_TDS_ITCM_SIZE		 0x38000 
#endif 

#ifndef LPHY_TOTAL_IMG_SIZE
#define LPHY_TOTAL_IMG_SIZE ((LPHY_PUB_DTCM_SIZE)+(LPHY_PUB_ITCM_SIZE)+(LPHY_LTE_DTCM_SIZE)*2+(LPHY_LTE_ITCM_SIZE)*2+(LPHY_TDS_DTCM_SIZE)+(LPHY_TDS_DTCM_SIZE)) 
#endif 

#ifndef CPHY_PUB_DTCM_BASE	
#define CPHY_PUB_DTCM_BASE	 0x72900000 
#endif 

#ifndef CPHY_PUB_ITCM_BASE	
#define CPHY_PUB_ITCM_BASE	 0x72980000 
#endif 

#ifndef CPHY_PRV_DTCM_BASE	
#define CPHY_PRV_DTCM_BASE	 0x72900000 
#endif 

#ifndef CPHY_PRV_ITCM_BASE	
#define CPHY_PRV_ITCM_BASE	 0x72980000 
#endif 

#ifndef CPHY_PUB_DTCM_SIZE		
#define CPHY_PUB_DTCM_SIZE		 0x60000 
#endif 

#ifndef CPHY_PUB_ITCM_SIZE		
#define CPHY_PUB_ITCM_SIZE		 0x60000 
#endif 

#ifndef CPHY_PRV_DTCM_SIZE		
#define CPHY_PRV_DTCM_SIZE		 0x60000 
#endif 

#ifndef CPHY_PRV_ITCM_SIZE		
#define CPHY_PRV_ITCM_SIZE		 0x60000 
#endif 

#ifndef CPHY_PUB_DTCM_GLB_MINUS_LOCAL	
#define CPHY_PUB_DTCM_GLB_MINUS_LOCAL	 (0xE2900000 - 0x72900000) 
#endif 

#ifndef TL_PHY_ASIC_V850    	
#define TL_PHY_ASIC_V850    	 
#endif 

#ifndef TL_PHY_BBE16_CACHE
#endif 

#ifndef TL_PHY_FEATURE_LTE_LCS
#endif 

#ifndef LPHY_SFT
#endif 

#ifndef FEATURE_LPHY_RFIC_HI6362
#define FEATURE_LPHY_RFIC_HI6362 FEATURE_ON 
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
#define PLATFORM_HISI_BALONG hi6250 
#endif 

#ifndef TTF_SKB_EXP
#endif 

#ifndef GU_FEATURE_CONFIG_PATH
#define GU_FEATURE_CONFIG_PATH config/product/hi6250_udp/include_gu 
#endif 

#ifndef TL_PS_MAX_TRCH_NUM_8
#define TL_PS_MAX_TRCH_NUM_8 
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

#ifndef PS_PTL_VER_DANAMIC
#define PS_PTL_VER_DANAMIC 20 
#endif 

#ifndef PS_PTL_VER_PRE_R99
#define PS_PTL_VER_PRE_R99 (-2) 
#endif 

#ifndef PS_PTL_VER_R99
#define PS_PTL_VER_R99 (-1) 
#endif 

#ifndef PS_PTL_VER_R3
#define PS_PTL_VER_R3 0 
#endif 

#ifndef PS_PTL_VER_R4
#define PS_PTL_VER_R4 1 
#endif 

#ifndef PS_PTL_VER_R5
#define PS_PTL_VER_R5 2 
#endif 

#ifndef PS_PTL_VER_R6
#define PS_PTL_VER_R6 3 
#endif 

#ifndef PS_PTL_VER_R7
#define PS_PTL_VER_R7 4 
#endif 

#ifndef PS_PTL_VER_R8
#define PS_PTL_VER_R8 5 
#endif 

#ifndef PS_PTL_VER_R9
#define PS_PTL_VER_R9 6 
#endif 

#ifndef PS_UE_REL_VER
#define PS_UE_REL_VER PS_PTL_VER_R9 
#endif 

#ifndef FEATURE_UE_MODE_G
#define FEATURE_UE_MODE_G FEATURE_ON 
#endif 

#ifndef FEATURE_UE_MODE_W
#define FEATURE_UE_MODE_W FEATURE_ON 
#endif 

#ifndef FEATURE_GCBS
#define FEATURE_GCBS FEATURE_ON 
#endif 

#ifndef FEATURE_WCBS
#define FEATURE_WCBS FEATURE_ON 
#endif 

#ifndef FEATURE_AP
#define FEATURE_AP FEATURE_OFF 
#endif 

#ifndef FEATURE_PTABLE_UDP
#define FEATURE_PTABLE_UDP FEATURE_ON 
#endif 

#ifndef FEATURE_E5
#define FEATURE_E5 FEATURE_OFF 
#endif 

#ifndef FEATURE_E5_UDP
#define FEATURE_E5_UDP FEATURE_OFF 
#endif 

#ifndef FEATURE_SEC_BOOT
#define FEATURE_SEC_BOOT FEATURE_OFF 
#endif 

#ifndef FEATURE_CSD
#define FEATURE_CSD FEATURE_OFF 
#endif 

#ifndef FEATURE_PPP
#define FEATURE_PPP FEATURE_ON 
#endif 

#ifndef FEATURE_HARDWARE_HDLC_FUNC
#define FEATURE_HARDWARE_HDLC_FUNC FEATURE_OFF 
#endif 

#ifndef FEATURE_HARDWARE_HDLC_ON_CCPU
#define FEATURE_HARDWARE_HDLC_ON_CCPU FEATURE_OFF 
#endif 

#ifndef FEATURE_PPPOE
#define FEATURE_PPPOE FEATURE_OFF 
#endif 

#ifndef FEATURE_UPDATEONLINE
#define FEATURE_UPDATEONLINE FEATURE_OFF 
#endif 

#ifndef FEATURE_WIFI
#define FEATURE_WIFI FEATURE_OFF 
#endif 

#ifndef FEATURE_HIFI
#define FEATURE_HIFI FEATURE_ON 
#endif 

#ifndef FEATURE_HIFI_USE_ICC
#define FEATURE_HIFI_USE_ICC FEATURE_ON 
#endif 

#ifndef FEATURE_MBB_MODULE_AUDIO
#define FEATURE_MBB_MODULE_AUDIO FEATURE_OFF 
#endif 

#ifndef FEATURE_SDIO
#define FEATURE_SDIO FEATURE_OFF 
#endif 

#ifndef FEATURE_KEYBOARD
#define FEATURE_KEYBOARD FEATURE_OFF 
#endif 

#ifndef FEATURE_CHARGE
#define FEATURE_CHARGE FEATURE_OFF 
#endif 

#ifndef FEATURE_ICC_DEBUG
#define FEATURE_ICC_DEBUG FEATURE_ON 
#endif 

#ifndef FEATURE_POWER_ON_OFF
#define FEATURE_POWER_ON_OFF FEATURE_OFF 
#endif 

#ifndef FEATURE_OLED
#define FEATURE_OLED FEATURE_OFF 
#endif 

#ifndef FEATURE_TFT
#define FEATURE_TFT FEATURE_OFF 
#endif 

#ifndef FEATURE_MMI_TEST
#define FEATURE_MMI_TEST FEATURE_OFF 
#endif 

#ifndef FEATURE_DL_E_CELL_FACH
#define FEATURE_DL_E_CELL_FACH FEATURE_ON 
#endif 

#ifndef FEATURE_INTERPEAK
#define FEATURE_INTERPEAK FEATURE_OFF 
#endif 

#ifndef FEATURE_INTERPEAK_MINI
#define FEATURE_INTERPEAK_MINI FEATURE_OFF 
#endif 

#ifndef IPWEBS_FEATURE_E5
#define IPWEBS_FEATURE_E5 FEATURE_OFF 
#endif 

#ifndef IPWEBS_FEATURE_WIRELESS_DONGLE
#define IPWEBS_FEATURE_WIRELESS_DONGLE FEATURE_OFF 
#endif 

#ifndef IPWEBS_FEATURE_LIGHTNING_CARD
#define IPWEBS_FEATURE_LIGHTNING_CARD FEATURE_OFF 
#endif 

#ifndef FEATURE_WEBNAS
#define FEATURE_WEBNAS FEATURE_OFF 
#endif 

#ifndef FEATURE_WIRELESS_DONGLE
#define FEATURE_WIRELESS_DONGLE FEATURE_OFF 
#endif 

#ifndef FEATURE_PMU_PROTECT
#define FEATURE_PMU_PROTECT FEATURE_OFF 
#endif 

#ifndef FEATURE_VXWORKS_TCPIP
#define FEATURE_VXWORKS_TCPIP FEATURE_OFF 
#endif 

#ifndef FEATURE_MEMORY_SIZE
#define FEATURE_MEMORY_SIZE MEMORY_SIZE_64M 
#endif 

#ifndef FEATURE_ECM_RNDIS
#define FEATURE_ECM_RNDIS FEATURE_OFF 
#endif 

#ifndef FEATURE_RNIC
#define FEATURE_RNIC FEATURE_OFF 
#endif 

#ifndef FEATURE_NFEXT
#define FEATURE_NFEXT FEATURE_ON 
#endif 

#ifndef FEATURE_UL_E_CELL_FACH
#define FEATURE_UL_E_CELL_FACH FEATURE_OFF 
#endif 

#ifndef FEATURE_BREATH_LIGHT
#define FEATURE_BREATH_LIGHT FEATURE_OFF 
#endif 

#ifndef FEATURE_LEDSTATUS
#define FEATURE_LEDSTATUS FEATURE_OFF 
#endif 

#ifndef FEATURE_E5_LED
#define FEATURE_E5_LED FEATURE_OFF 
#endif 

#ifndef FEATURE_RTC
#define FEATURE_RTC FEATURE_OFF 
#endif 

#ifndef FEATURE_SMALL_MAILBOX
#define FEATURE_SMALL_MAILBOX FEATURE_OFF 
#endif 

#ifndef FEATURE_RECONFIG
#define FEATURE_RECONFIG FEATURE_ON 
#endif 

#ifndef FEATURE_HWENCRY_REWORK
#define FEATURE_HWENCRY_REWORK FEATURE_OFF 
#endif 

#ifndef FEATURE_MMU_BIG
#define FEATURE_MMU_BIG FEATURE_OFF 
#endif 

#ifndef FEATURE_MMU_MEDIUM
#define FEATURE_MMU_MEDIUM FEATURE_ON 
#endif 

#ifndef FEATURE_MMU_SMALL
#define FEATURE_MMU_SMALL FEATURE_OFF 
#endif 

#ifndef FEATURE_TTFMEM_CACHE
#define FEATURE_TTFMEM_CACHE FEATURE_OFF 
#endif 

#ifndef FEATURE_SDUPDATE
#define FEATURE_SDUPDATE FEATURE_OFF 
#endif 

#ifndef FEATURE_SECURITY_SHELL          			
#define FEATURE_SECURITY_SHELL          			 FEATURE_ON 
#endif 

#ifndef FEATURE_EPAD
#define FEATURE_EPAD FEATURE_OFF 
#endif 

#ifndef FEATURE_HSIC_SLAVE
#define FEATURE_HSIC_SLAVE FEATURE_OFF 
#endif 

#ifndef FEATURE_MEM_MONITOR
#define FEATURE_MEM_MONITOR FEATURE_ON 
#endif 

#ifndef FEATURE_DRV_REPLAY_DUMP						
#define FEATURE_DRV_REPLAY_DUMP						 FEATURE_OFF 
#endif 

#ifndef FEATURE_SKB_EXP
#define FEATURE_SKB_EXP FEATURE_OFF 
#endif 

#ifndef FEATURE_MULTI_FS_PARTITION
#define FEATURE_MULTI_FS_PARTITION FEATURE_ON 
#endif 

#ifndef CONFIG_HISI_PTM
#define CONFIG_HISI_PTM FEATURE_OFF 
#endif 

#ifndef NAS_FEATURE_SMS_NVIM_SMSEXIST
#define NAS_FEATURE_SMS_NVIM_SMSEXIST FEATURE_ON 
#endif 

#ifndef NAS_FEATURE_SMS_FLASH_SMSEXIST
#define NAS_FEATURE_SMS_FLASH_SMSEXIST FEATURE_ON 
#endif 

#ifndef FEATURE_UE_MODE_G
#define FEATURE_UE_MODE_G FEATURE_ON 
#endif 

#ifndef FEATURE_UE_MODE_W
#define FEATURE_UE_MODE_W FEATURE_ON 
#endif 

#ifndef FEATURE_LTE
#define FEATURE_LTE FEATURE_ON 
#endif 

#ifndef FEATURE_UE_MODE_TDS
#define FEATURE_UE_MODE_TDS FEATURE_ON 
#endif 

#ifndef FEATURE_ETWS
#define FEATURE_ETWS FEATURE_ON 
#endif 

#ifndef FEATURE_AGPS
#define FEATURE_AGPS FEATURE_ON 
#endif 

#ifndef FEATRUE_XML_PARSER
#define FEATRUE_XML_PARSER FEATURE_ON 
#endif 

#ifndef FEATURE_PTM
#define FEATURE_PTM FEATURE_ON 
#endif 

#ifndef FEATURE_UE_UICC_MULTI_APP_SUPPORT
#define FEATURE_UE_UICC_MULTI_APP_SUPPORT FEATURE_ON 
#endif 

#ifndef FEATURE_VCOM_EXT
#define FEATURE_VCOM_EXT FEATURE_ON 
#endif 

#ifndef FEATURE_IPV6
#define FEATURE_IPV6 FEATURE_ON 
#endif 

#ifndef FEATURE_RMNET_CUSTOM
#define FEATURE_RMNET_CUSTOM FEATURE_OFF 
#endif 

#ifndef FEATURE_AT_HSIC
#define FEATURE_AT_HSIC FEATURE_OFF 
#endif 

#ifndef FEATURE_AT_HSUART
#define FEATURE_AT_HSUART FEATURE_OFF 
#endif 

#ifndef FEATURE_HUAWEI_VP
#define FEATURE_HUAWEI_VP FEATURE_OFF 
#endif 

#ifndef FEATURE_CL_INTERWORK
#define FEATURE_CL_INTERWORK FEATURE_OFF 
#endif 

#ifndef FEATURE_MULTI_MODEM
#define FEATURE_MULTI_MODEM FEATURE_ON 
#endif 

#ifndef MULTI_MODEM_NUMBER
#define MULTI_MODEM_NUMBER 2 
#endif 

#ifndef FEATURE_ECALL
#define FEATURE_ECALL FEATURE_OFF 
#endif 

#ifndef GAS_PTL_VER_PRE_R99
#define GAS_PTL_VER_PRE_R99 (PS_PTL_VER_PRE_R99) 
#endif 

#ifndef GAS_PTL_VER_R99
#define GAS_PTL_VER_R99 (PS_PTL_VER_R99) 
#endif 

#ifndef GAS_PTL_VER_R3
#define GAS_PTL_VER_R3 (PS_PTL_VER_R3) 
#endif 

#ifndef GAS_PTL_VER_R4
#define GAS_PTL_VER_R4 (PS_PTL_VER_R4) 
#endif 

#ifndef GAS_PTL_VER_R5
#define GAS_PTL_VER_R5 (PS_PTL_VER_R5) 
#endif 

#ifndef GAS_PTL_VER_R6
#define GAS_PTL_VER_R6 (PS_PTL_VER_R6) 
#endif 

#ifndef GAS_PTL_VER_R7
#define GAS_PTL_VER_R7 (PS_PTL_VER_R7) 
#endif 

#ifndef GAS_PTL_VER_R8
#define GAS_PTL_VER_R8 (PS_PTL_VER_R8) 
#endif 

#ifndef GAS_PTL_VER_R9
#define GAS_PTL_VER_R9 (PS_PTL_VER_R9) 
#endif 

#ifndef GAS_UE_REL_VER
#define GAS_UE_REL_VER (GAS_PTL_VER_R9) 
#endif 

#ifndef FEATURE_DC_MIMO
#define FEATURE_DC_MIMO FEATURE_OFF 
#endif 

#ifndef FEATURE_DC_UPA
#define FEATURE_DC_UPA FEATURE_OFF 
#endif 

#ifndef FEATURE_VISP_VPP
#define FEATURE_VISP_VPP FEATURE_OFF 
#endif 

#ifndef FEATURE_BBPMST_FREQUENCY_REDUCE
#define FEATURE_BBPMST_FREQUENCY_REDUCE FEATURE_OFF 
#endif 

#ifndef TTF_CF_FEATURE
#define TTF_CF_FEATURE FEATURE_OFF 
#endif 

#ifndef FEATURE_TTF_MEM_DEBUG
#define FEATURE_TTF_MEM_DEBUG FEATURE_ON 
#endif 

#ifndef FEATURE_W_R99_DL_DUAL_MAILBOX
#define FEATURE_W_R99_DL_DUAL_MAILBOX FEATURE_ON 
#endif 

#ifndef FEATURE_ASSEMBLY_MEM_CPY
#define FEATURE_ASSEMBLY_MEM_CPY FEATURE_ON 
#endif 

#ifndef FEATURE_HSPA_PERF_IMP
#define FEATURE_HSPA_PERF_IMP FEATURE_ON 
#endif 

#ifndef FEATURE_RACH_NO_ACK_DEBUG
#define FEATURE_RACH_NO_ACK_DEBUG FEATURE_OFF 
#endif 

#ifndef FEATURE_TCP_ACK_IN_FRONT
#define FEATURE_TCP_ACK_IN_FRONT FEATURE_ON 
#endif 

#ifndef FEATURE_CST_ASYN_OR_NOT_TRANS
#define FEATURE_CST_ASYN_OR_NOT_TRANS FEATURE_OFF 
#endif 

#ifndef FEATURE_ACPU_STAT
#define FEATURE_ACPU_STAT FEATURE_OFF 
#endif 

#ifndef FEATURE_ACPU_FC_POINT_REG
#define FEATURE_ACPU_FC_POINT_REG FEATURE_ON 
#endif 

#ifndef SC_CTRL_MOD_6620_FPGA
#define SC_CTRL_MOD_6620_FPGA 1 
#endif 

#ifndef SC_CTRL_MOD_6620_SFT
#define SC_CTRL_MOD_6620_SFT 2 
#endif 

#ifndef SC_CTRL_MOD_6758_FPGA
#define SC_CTRL_MOD_6758_FPGA 3 
#endif 

#ifndef SC_CTRL_MOD_6758_SFT
#define SC_CTRL_MOD_6758_SFT 4 
#endif 

#ifndef SC_CTRL_MOD_6930_FPGA
#define SC_CTRL_MOD_6930_FPGA 5 
#endif 

#ifndef SC_CTRL_MOD_6930_SFT
#define SC_CTRL_MOD_6930_SFT 6 
#endif 

#ifndef SC_CTRL_MOD_3630_UDP
#define SC_CTRL_MOD_3630_UDP 7 
#endif 

#ifndef SC_CTRL_MOD_6210_FPGA
#define SC_CTRL_MOD_6210_FPGA 8 
#endif 

#ifndef SC_CTRL_MOD_6210_SFT
#define SC_CTRL_MOD_6210_SFT 9 
#endif 

#ifndef SC_CTRL_MOD_P532
#define SC_CTRL_MOD_P532 10 
#endif 

#ifndef SC_CTRL_MOD_6950_SFT
#define SC_CTRL_MOD_6950_SFT 11 
#endif 

#ifndef SC_CTRL_MOD_3650_SFT
#define SC_CTRL_MOD_3650_SFT 12 
#endif 

#ifndef SC_CTRL_MOD
#define SC_CTRL_MOD (SC_CTRL_MOD_3650_SFT) 
#endif 

#ifndef ZSP_DSP_CHIP_BB_TYPE		
#define ZSP_DSP_CHIP_BB_TYPE		 10 
#endif 

#ifndef ZSP_DSP_PRODUCT_FORM		
#define ZSP_DSP_PRODUCT_FORM		 4 
#endif 

#ifndef BOARD
#define BOARD ASIC 
#endif 

#ifndef FEATURE_DC_DPA			
#define FEATURE_DC_DPA			 FEATURE_ON 
#endif 

#ifndef FEATURE_DC_UPA
#define FEATURE_DC_UPA FEATURE_OFF 
#endif 

#ifndef FEATURE_DC_MIMO
#define FEATURE_DC_MIMO FEATURE_OFF 
#endif 

#ifndef FEATURE_HARQ_OUT
#define FEATURE_HARQ_OUT FEATURE_ON 
#endif 

#ifndef FEATURE_RFIC_RESET_GPIO_ON	
#define FEATURE_RFIC_RESET_GPIO_ON	 FEATURE_OFF 
#endif 

#ifndef FEATURE_EXTERNAL_32K_CLK		
#define FEATURE_EXTERNAL_32K_CLK		 FEATURE_OFF 
#endif 

#ifndef FEATURE_UPHY_SIO_WPLL_ELUSION_ON
#define FEATURE_UPHY_SIO_WPLL_ELUSION_ON FEATURE_OFF 
#endif 

#ifndef FEATURE_MULTI_RFIC_MEAS	
#define FEATURE_MULTI_RFIC_MEAS	 FEATURE_ON 
#endif 

#ifndef FEATURE_SRAM_400K
#define FEATURE_SRAM_400K FEATURE_OFF 
#endif 

#ifndef FEATURE_TEMP_DSP_CORE_POWER_DOWN
#define FEATURE_TEMP_DSP_CORE_POWER_DOWN FEATURE_OFF 
#endif 

#ifndef FEATURE_TEMP_MULTI_MODE_LP
#define FEATURE_TEMP_MULTI_MODE_LP FEATURE_ON 
#endif 

#ifndef FEATURE_TUNER
#define FEATURE_TUNER FEATURE_OFF 
#endif 

#ifndef FEATURE_ANT_SHARE
#define FEATURE_ANT_SHARE FEATURE_ON 
#endif 

#ifndef FEATURE_VIRTUAL_BAND
#define FEATURE_VIRTUAL_BAND FEATURE_ON 
#endif 

#ifndef FEATURE_GU_DSP_SPLIT
#define FEATURE_GU_DSP_SPLIT FEATURE_ON 
#endif 

#ifndef FEATURE_TAS
#define FEATURE_TAS FEATURE_OFF 
#endif 

#ifndef FEATURE_DSDS
#define FEATURE_DSDS FEATURE_ON 
#endif 

#ifndef FEATURE_S_SKU_M_OPERATORS
#define FEATURE_S_SKU_M_OPERATORS FEATURE_OFF 
#endif 

#ifndef FEATURE_BROWSER_NV_FILE_IMEI_PROTECT
#define FEATURE_BROWSER_NV_FILE_IMEI_PROTECT FEATURE_OFF 
#endif 

#ifndef FEATURE_COMPRESS_WRITE_LOG_FILE
#define FEATURE_COMPRESS_WRITE_LOG_FILE FEATURE_OFF 
#endif 

#ifndef FEATURE_CBT_LOG
#define FEATURE_CBT_LOG FEATURE_OFF 
#endif 

#ifndef FEATURE_BBP_MASTER
#define FEATURE_BBP_MASTER FEATURE_ON 
#endif 

#ifndef BBP_MASTER_INT_MODE		 		
#define BBP_MASTER_INT_MODE		 		 FEATURE_ON 
#endif 

#ifndef FEATURE_BBP_MASTER_CHAN_EXTEND		
#define FEATURE_BBP_MASTER_CHAN_EXTEND		 FEATURE_ON 
#endif 

#ifndef FEATURE_VOICE_UP 					
#define FEATURE_VOICE_UP 					 FEATURE_OFF 
#endif 

#ifndef FEATURE_GUC_BBP_TRIG
#define FEATURE_GUC_BBP_TRIG FEATURE_ON 
#endif 

#ifndef FEATURE_LTE_R11
#define FEATURE_LTE_R11 FEATURE_ON 
#endif 

#ifndef FEATURE_LPP
#define FEATURE_LPP FEATURE_OFF 
#endif 

#ifndef FEATURE_POWER_TIMER
#define FEATURE_POWER_TIMER FEATURE_OFF 
#endif 

#ifndef FEATURE_VSIM
#define FEATURE_VSIM FEATURE_OFF 
#endif 

#ifndef FEATURE_MANUFACTURE_LOG
#define FEATURE_MANUFACTURE_LOG FEATURE_OFF 
#endif 

#ifndef FEATURE_BALONG_CL
#define FEATURE_BALONG_CL FEATURE_UE_MODE_CDMA 
#endif 

#ifndef FEATURE_UE_MODE_CDMA
#define FEATURE_UE_MODE_CDMA FEATURE_ON 
#endif 

#ifdef OBC_IMAGE_MODEM
#endif 

#ifdef OBC_IMAGE_APP
#endif 

#ifdef OBC_IMAGE_BOOTROM
#endif 

#ifdef OBC_IMAGE_BOOTLOADER
#endif 

#endif /*__PRODUCT_CONFIG_H__*/ 
