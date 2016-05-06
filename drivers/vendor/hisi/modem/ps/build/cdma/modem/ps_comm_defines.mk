#***********************************************************#
# compiler defines
#***********************************************************#
CC_USER_DEFINES :=

CC_USER_DEFINES += -DUSP_2_0 -D__LOG_RELEASE__  -DVOS_HARDWARE_PLATFORM=8 \
				-DVOS_CPU_TYPE=8 -DV2R1_USIM -DINET \
				-DVOS_OSA_CPU=OSA_CPU_CCPU -DBALONG_CHIP_V200=2 \
				-DBALONG_CHIP_V300=3 -DBALONG_CHIP_V500=4 -DBALONG_CHIP_VER=BALONG_CHIP_V500 -DDSP_A17_ENABLE \
				-DVERSION_V3R2_C00 -D$(CFG_GU_PRODUCT_VERSION) -D__LDF_FUNCTION__ -DBOARD_$(CFG_BOARD) \
				-DFEATURE_DSP2ARM -DBSP_CORE_MODEM