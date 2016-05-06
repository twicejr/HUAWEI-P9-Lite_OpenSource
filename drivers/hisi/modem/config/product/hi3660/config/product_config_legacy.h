/* MD5: cda86a05331e0d5552373f7af8c55ccf*/
#if !defined(__PRODUCT_CONFIG_LEGACY_H__)
#define __PRODUCT_CONFIG_LEGACY_H__

#ifndef BALONG_OBUILD_VERSION
#define BALONG_OBUILD_VERSION 10 
#endif 

#ifndef FEATURE_ON
#define FEATURE_ON 1 
#endif 

#ifndef FEATURE_OFF
#define FEATURE_OFF 0 
#endif 

#ifndef FEATURE_OBJ_CMP 				
#endif 

#ifndef FEATURE_OBJ_DUMP				
#endif 

#ifndef PLATFORM
#define PLATFORM hi3660 
#endif 

#ifndef PLATFORM_CHIP_TYPE
#define PLATFORM_CHIP_TYPE hi3660 
#endif 

#ifndef ENABLE_SHELL_SYM
#define ENABLE_SHELL_SYM 
#endif 

#ifndef ENABLE_DEBUG
#define ENABLE_DEBUG 
#endif 

#ifndef RTOSCK_CCORE_COMPONENTS
#define RTOSCK_CCORE_COMPONENTS bsp_ccore.o gumsp_mcore.o nas_ccore.o rabm_ccore.o gas_ccore.o was_ccore.o ttf_ccore.o ascomm_ccore.o pscomm_ccore.o encodix_ccore.o taf_ccore.o tlas_ccore.o tlnas_ccore.o lmsp_ccore.o gudsp_mcore.o gudsp_comm_RT.o gudsp_mcore_RT.o modemcore1_union.o 
#endif 

#ifndef CCORE_COMPONENTS
#define CCORE_COMPONENTS bsp_ccore.o gumsp_mcore.o nas_ccore.o rabm_ccore.o gas_ccore.o was_ccore.o ttf_ccore.o ascomm_ccore.o pscomm_ccore.o encodix_ccore.o taf_ccore.o tlas_ccore.o tlnas_ccore.o lmsp_ccore.o gudsp_mcore.o gudsp_comm_RT.o gudsp_mcore_RT.o os_ccore.o 
#endif 

#ifndef CCORE_MODEM1_COMPONENTS
#define CCORE_MODEM1_COMPONENTS bsp_ccore1.o nas1_ccore.o rabm1_ccore.o gas1_ccore.o taf1_ccore.o ascomm1_ccore.o pscomm1_ccore.o encodix1_ccore.o gumsp1_mcore.o gudsp1_mcore.o gudsp1_mcore_RT.o ttf1_ccore.o 
#endif 

#ifndef CCORE_MODEM2_COMPONENTS
#define CCORE_MODEM2_COMPONENTS bsp_ccore2.o nas2_ccore.o rabm2_ccore.o gas2_ccore.o taf2_ccore.o ascomm2_ccore.o pscomm2_ccore.o encodix2_ccore.o gumsp2_mcore.o gudsp2_mcore.o gudsp2_mcore_RT.o ttf2_ccore.o 
#endif 

#ifndef RTOSCK_CCORE2_COMPONENTS
#define RTOSCK_CCORE2_COMPONENTS modemcore2_union.o 
#endif 

#ifndef FEATURE_IMS
#define FEATURE_IMS FEATURE_ON 
#endif 

#ifndef FEATURE_DFS_SYNC							
#define FEATURE_DFS_SYNC							 FEATURE_OFF 
#endif 

#ifndef GU_INC_PATH
#define GU_INC_PATH COMM_CODE_GU/Balong_GU_Inc/GUL_CS 
#endif 

#ifndef GU_RAT_MODE
#define GU_RAT_MODE RAT_GUL 
#endif 

#ifndef TTF_SKB_EXP
#endif 

#ifndef GU_FEATURE_CONFIG_PATH
#define GU_FEATURE_CONFIG_PATH config/product/hi3660_udp/include_gu 
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

#ifndef FEATURE_PTABLE_UDP
#define FEATURE_PTABLE_UDP FEATURE_ON 
#endif 

#ifndef FEATURE_E5_UDP
#define FEATURE_E5_UDP FEATURE_OFF 
#endif 

#ifndef FEATURE_SEC_BOOT
#define FEATURE_SEC_BOOT FEATURE_OFF 
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

#ifndef FEATURE_OLED
#define FEATURE_OLED FEATURE_OFF 
#endif 

#ifndef FEATURE_TFT
#define FEATURE_TFT FEATURE_OFF 
#endif 

#ifndef FEATURE_MMI_TEST
#define FEATURE_MMI_TEST FEATURE_OFF 
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

#ifndef FEATURE_RECONFIG
#define FEATURE_RECONFIG FEATURE_ON 
#endif 

#ifndef FEATURE_HWENCRY_REWORK
#define FEATURE_HWENCRY_REWORK FEATURE_OFF 
#endif 

#ifndef FEATURE_MMU_BIG
#define FEATURE_MMU_BIG FEATURE_OFF 
#endif 

#ifndef FEATURE_TTFMEM_CACHE
#define FEATURE_TTFMEM_CACHE FEATURE_OFF 
#endif 

#ifndef FEATURE_SDUPDATE
#define FEATURE_SDUPDATE FEATURE_OFF 
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

#ifndef FEATURE_UE_MODE_G
#define FEATURE_UE_MODE_G FEATURE_ON 
#endif 

#ifndef FEATURE_UE_MODE_W
#define FEATURE_UE_MODE_W FEATURE_ON 
#endif 

#ifndef FEATURE_PTM
#define FEATURE_PTM FEATURE_ON 
#endif 

#ifndef FEATURE_UE_UICC_MULTI_APP_SUPPORT
#define FEATURE_UE_UICC_MULTI_APP_SUPPORT FEATURE_ON 
#endif 

#ifndef FEATURE_LPP
#define FEATURE_LPP FEATURE_OFF 
#endif 

#ifndef ZSP_DSP_CHIP_BB_TYPE		
#define ZSP_DSP_CHIP_BB_TYPE		 8 
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
#define FEATURE_RFIC_RESET_GPIO_ON			 FEATURE_OFF 
#endif 

#ifndef FEATURE_EXTERNAL_32K_CLK			
#define FEATURE_EXTERNAL_32K_CLK			 FEATURE_OFF 
#endif 

#ifndef FEATURE_UPHY_SIO_WPLL_ELUSION_ON
#define FEATURE_UPHY_SIO_WPLL_ELUSION_ON FEATURE_OFF 
#endif 

#ifndef FEATURE_MULTI_RFIC_MEAS			
#define FEATURE_MULTI_RFIC_MEAS			 FEATURE_ON 
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
#define FEATURE_TUNER				 FEATURE_OFF 
#endif 

#ifndef FEATURE_ANT_SHARE				
#define FEATURE_ANT_SHARE				 FEATURE_ON 
#endif 

#ifndef FEATURE_VIRTUAL_BAND			
#define FEATURE_VIRTUAL_BAND			 FEATURE_ON 
#endif 

#ifndef FEATURE_GU_DSP_SPLIT
#define FEATURE_GU_DSP_SPLIT FEATURE_ON 
#endif 

#ifndef FEATURE_TAS
#define FEATURE_TAS FEATURE_OFF 
#endif 

#ifndef FEATURE_MODE_FEM_CHAN_EXT
#define FEATURE_MODE_FEM_CHAN_EXT FEATURE_ON 
#endif 

#ifndef FEATURE_SOCP_SYNC_ENABLE
#define FEATURE_SOCP_SYNC_ENABLE FEATURE_OFF 
#endif 

#ifndef FEATURE_VOICE_UP
#define FEATURE_VOICE_UP FEATURE_OFF 
#endif 

#ifndef FEATURE_MANUFACTURE_LOG
#define FEATURE_MANUFACTURE_LOG FEATURE_OFF 
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

#ifndef FEATURE_DCX0_TLHPA_WRITE_PHY_NV
#define FEATURE_DCX0_TLHPA_WRITE_PHY_NV FEATURE_ON 
#endif 

#ifndef FEATURE_VERSION_V8
#define FEATURE_VERSION_V8 FEATURE_OFF 
#endif 

#ifndef FEATURE_CIPHER_OPTIMIZE
#define FEATURE_CIPHER_OPTIMIZE FEATURE_OFF 
#endif 

#ifndef FEATURE_BALONG_CL
#define FEATURE_BALONG_CL FEATURE_OFF 
#endif 

#ifndef FEATURE_TDS_WCDMA_DYNAMIC_LOAD
#define FEATURE_TDS_WCDMA_DYNAMIC_LOAD FEATURE_OFF 
#endif 

#ifndef FEATURE_UE_MODE_CDMA
#define FEATURE_UE_MODE_CDMA FEATURE_ON 
#endif 

#ifndef FEATURE_CHINA_TELECOM_VOICE_ENCRYPT
#define FEATURE_CHINA_TELECOM_VOICE_ENCRYPT FEATURE_OFF 
#endif 

#ifndef FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE
#define FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE FEATURE_OFF 
#endif 

#ifndef FEATURE_CSG
#define FEATURE_CSG FEATURE_OFF 
#endif 

#ifndef TL_PS_MAX_TRCH_NUM_8
#define TL_PS_MAX_TRCH_NUM_8 FEATURE_ON 
#endif 

#endif /*__PRODUCT_CONFIG_H__*/ 
