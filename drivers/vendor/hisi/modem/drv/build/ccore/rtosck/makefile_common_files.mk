# Created by Jeffery.zhai/199916 2012.03.25

include $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

DRV_DIR                  :=$(BALONG_TOPDIR)/modem/drv
BSP_DIR                  :=$(DRV_DIR)/ccore
OS_SRC_DIR               :=$(BALONG_TOPDIR)/build/delivery/$(OBB_PRODUCT_NAME)/os/$(OBC_LOCAL_CORE_NAME)
ASIC_DIR_NAME            :=$(CFG_BSP_ASIC_DIR_NAME)

CORE_INDEX_MODEM         :=1
CORE_INDEX_APP           :=2
CORE_INDEX_BOOTROM       :=3
CORE_INDEX_BOOTLOADER    :=4
#*******************************************************************
# src:OBC_LOCAL_SRC_FILE  以下放置小系统必须的组件
#*******************************************************************

#  head.s 必须放到第一个
ifeq ($(INSTANCE_ID),INSTANCE_0)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/rtosck/head.s \
	$(BALONG_TOPDIR)/modem/system/rtosck_a9/config/sre_config.c \
	$(BALONG_TOPDIR)/modem/system/rtosck_a9/config/sre_shellConfig.c \
	$(BSP_DIR)/rtosck/mmu.c \
	$(BSP_DIR)/rtosck/rtos_main.c \
	$(BSP_DIR)/sys/drv_entry.c

# systimer
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/systimer/systimer_rtosck.c
# serial
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/serial/synopsys_uart.c \
	$(BSP_DIR)/drivers/serial/arm_uart.c \
	$(BSP_DIR)/drivers/serial/serial_core.c \
	$(BSP_DIR)/drivers/serial/serial_balong.c

#*******************************************************************
# src:以下放置非小系统必须的组件
#*******************************************************************
ifneq ($(strip $(CFG_CONFIG_SMART_SYSTEM_MODEM)),YES)
#sys
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/sys/spinLockAmp.s \
	$(BSP_DIR)/rtosck/os_adapter.c \
	$(BSP_DIR)/rtosck/libPatch.c
#thermal
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/sys/thermal.c \
# osl
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/osl/osl_wait_rtosck.c \
	$(BSP_DIR)/drivers/osl/osl_ioremap.c
#gic
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/gic/gic_pm.c

# watchdog
ifeq ($(strip $(CFG_CONFIG_CCORE_WDT)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/watchdog/wdt_balong.c \
	$(BSP_DIR)/drivers/watchdog/watchdog_timer.c \
	$(BSP_DIR)/drivers/watchdog/watchdog_hard.c

OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/watchdog/wdt_balong_test.c
endif

# busstress
ifeq ($(strip $(CFG_CONFIG_MODULE_BUSSTRESS)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/a9_balong_busstress.c \
    $(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/acc_bus_stress.c \
    $(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/bsp_dsp_test.c \
    $(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/cipher_stress_test.c \
    $(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/edma_balong_busstress.c \
    $(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/socp_balong_test.c \
    $(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/ipf_stress_test.c \
    $(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/bbp_balong_test.c \
    $(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/k3_busstress_balong.c \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_comm/BasicFunc.c \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_comm/common.c \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_comm/dmac1.c \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_comm/mem_fun.c \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_hdlc/master.c \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_hdlc/hdlcv200_frm_def_test_bbit.c \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_cicom/cicom.c \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_upacc/upacc.c
endif

#dual_modem
ifeq ($(strip $(CFG_CONFIG_DUAL_MODEM)),YES)
OBC_LOCAL_SRC_FILE +=  \
	$(BSP_DIR)/drivers/dual_modem/dual_modem.c
else
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/adp/adp_dual_modem_uart.c
endif
#ipc
ifeq ($(strip $(CFG_CONFIG_MODULE_IPC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/ipc/ipc_balong.c

OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/ipc/ipc_balong_test.c

endif
# icc
ifeq ($(strip $(CFG_CONFIG_ICC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/icc/icc_core.c \
	$(BSP_DIR)/drivers/icc/icc_rtosck.c \
	$(BSP_DIR)/drivers/icc/icc_debug.c

OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/icc/icc_test.c
endif

# of
ifeq ($(strip $(CFG_CONFIG_OF)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/of/dts.c \
	$(BSP_DIR)/drivers/of/dts_balong.c \
	$(BSP_DIR)/drivers/of/dts_balong_dump.c
OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/of/selftest.c
endif

# pm om(modem log)
ifeq ($(strip $(CFG_CONFIG_PM_OM)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/pm_om/pm_om.c \
	$(BSP_DIR)/drivers/pm_om/pm_om_platform.c \
	$(BSP_DIR)/drivers/pm_om/pm_om_debug.c \
	$(BSP_DIR)/drivers/pm_om/pm_om_test.c \
	$(BSP_DIR)/drivers/pm_om/m3pm_m3dpm_log.c \
	$(BSP_DIR)/drivers/pm_om/pm_wakeup_debug.c \
	$(BSP_DIR)/drivers/pm_om/modem_log_rtosck.c \
	$(BSP_DIR)/drivers/pm_om/bsp_ring_buffer.c
endif

# sysctrl
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/sysctrl/dt_sysctrl.c
OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/sysctrl/sysctrl_test.c

# s_memory
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/s_memory/s_memory.c
OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/s_memory/s_memory_test.c

#softtimer hardtimer
ifeq ($(strip $(CFG_CONFIG_MODULE_TIMER)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/balong_timer/timer_slice.c \
	$(BSP_DIR)/drivers/balong_timer/hardtimer_arm.c \
	$(BSP_DIR)/drivers/balong_timer/hardtimer_synopsis.c \
	$(BSP_DIR)/drivers/balong_timer/hardtimer_core.c \
	$(BSP_DIR)/drivers/balong_timer/softtimer_balong.c 

OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/balong_timer/hardtimer_balong_test.c 

endif
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/balong_timer/timer_init.c 
#borad
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/board/board_fpga.c
#cipher
ifeq ($(strip $(CFG_CONFIG_CIPHER)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/cipher/cipher_balong.c \
	$(BSP_DIR)/drivers/cipher/acc_balong.c \
	$(BSP_DIR)/drivers/cipher/kdf_balong.c 
	
OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/cipher/acc_balong_test.c \
	$(BSP_DIR)/drivers/cipher/cipher_balong_test.c \
	$(BSP_DIR)/drivers/cipher/kdf_test.c
endif


#security
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/security/aes_alg.c \
	$(BSP_DIR)/drivers/security/rsann.c \
	$(BSP_DIR)/drivers/security/rsa_cipher.c \
	$(BSP_DIR)/drivers/security/aes.c \
	$(BSP_DIR)/drivers/security/ran.c \
	$(BSP_DIR)/drivers/security/sha_alg.c \
	$(BSP_DIR)/drivers/security/security2.c

#vic
ifeq ($(strip $(CFG_CONFIG_MODULE_VIC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/vic/vic_balong.c
endif

#console
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/console/ringbuffer.c \
	$(BSP_DIR)/drivers/console/virtshell.c \
	$(BSP_DIR)/drivers/console/console.c \
	$(BSP_DIR)/drivers/console/con_platform.c

# regulator
ifeq ($(strip $(CFG_CONFIG_CCORE_REGULATOR)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/regulator/regulator_balong.c \
	$(BSP_DIR)/drivers/regulator/regulator_balong_pmic.c \
	$(BSP_DIR)/drivers/regulator/regulator_hi3600_pmic.c

endif

ifeq ($(strip $(CFG_CONFIG_CCORE_REGULATOR)),NO)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/regulator/regulator.c
endif

# cpufreq
ifeq ($(strip $(CFG_CONFIG_CPUFREQ)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/cpufreq/cpufreq_core.c \
	$(BSP_DIR)/drivers/cpufreq/cpufreq_balong_api.c \
	$(BSP_DIR)/drivers/cpufreq/cpufreq_governor.c \
	$(BSP_DIR)/drivers/cpufreq/cpufreq_ondemand_governor.c \
	$(BSP_DIR)/drivers/cpufreq/cpufreq_driver_mbb.c \
	$(BSP_DIR)/drivers/cpufreq/cpufreq_driver_phone.c \
	$(BSP_DIR)/drivers/cpufreq/cpufreq_driver_phone_hi6250.c \
	$(BSP_DIR)/drivers/cpufreq/cpufreq_balong_debug.c
endif
ifeq ($(strip $(CFG_CONFIG_CPUFREQ)),NO)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/cpufreq/cpufreq.c
endif

#l2cache
ifeq ($(strip $(CFG_CONFIG_BALONG_L2CACHE)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/l2cache/l2cache_balong.c
endif

#edma
ifeq ($(strip $(CFG_CONFIG_BALONG_EDMA)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/edma/edma_interface.c \
	$(BSP_DIR)/drivers/edma/edma_core.c \
	$(BSP_DIR)/drivers/edma/edma_driver.c \
	$(BSP_DIR)/drivers/edma/edma_device.c
endif

#ddr test
ifeq ($(strip $(CFG_CONFIG_DDR_TEST_KERNEL)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/ddr/ddr_test.c
endif

ifneq ($(strip $(CFG_CONFIG_MODULE_BUSSTRESS)),YES)
OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/edma/edma_balong_test.c
endif
# pm
ifeq ($(strip $(CFG_CONFIG_CCORE_BALONG_PM)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/pm/pm.c  \
	$(BSP_DIR)/drivers/pm/pm_asm_deepsleep.s \
	$(BSP_DIR)/drivers/pm/pm_debug.c  

endif
# dpm
ifeq ($(strip $(CFG_CONFIG_CCORE_PM)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/dpm/dpm_balong.c \
	$(BSP_DIR)/drivers/dpm/dpm_balong_debug.c

OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/dpm/dpm_balong_test.c
endif
ifeq ($(strip $(CFG_CONFIG_RSR_ACC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/rsr_acc/rsr_acc.c 
endif
#clk
ifeq ($(strip $(CFG_CONFIG_BALONG_CCLK)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/clk/clk_balong.c \
	$(BSP_DIR)/drivers/clk/clk_balong_core.c \
	$(BSP_DIR)/drivers/clk/clk_balong_debug.c


OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/clk/clk_balong_test.c
endif

# get_ip_base_addr
ifeq ($(strip $(CFG_CONFIG_HWADP)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/hwadp/hwadp_balong.c \
	$(BSP_DIR)/drivers/hwadp/hwadp_core.c \
	$(BSP_DIR)/drivers/hwadp/hwadp_debug.c
endif

#sync
ifeq ($(strip $(CFG_CONFIG_MODULE_SYNC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/sync/sync_balong.c

OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/sync/sync_balong_test.c
endif
#wakelock
ifeq ($(strip $(CFG_CONFIG_HAS_CCORE_WAKELOCK)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/wakelock/wakelock_balong.c
endif

#cpuidle
ifeq ($(strip $(CFG_CONFIG_CCORE_CPU_IDLE)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/cpuidle/cpuidle_balong.c \
	$(BSP_DIR)/drivers/cpuidle/sleep_balong.s
endif

#HW_SPINLOCK
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/hwspinlock/bsp_hw_spinlock.c

#dsp
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/adp/adp_dsp.c
ifeq ($(strip $(CFG_CONFIG_DSP)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/dsp/bsp_dsp.c 
endif

#cdsp
ifeq ($(strip $(CFG_CONFIG_CBBE)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/dsp/dsp_balong.c
endif

#tuner
ifeq ($(strip $(CFG_CONFIG_TUNER)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/tuner/bsp_tuner.c
endif

#cross mipi
ifeq ($(strip $(CFG_CONFIG_CROSS_MIPI)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/cross_mipi/bsp_cross_mipi.c
endif

#abb
ifeq ($(strip $(CFG_CONFIG_ABB)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/abb/bsp_abb.c \
	$(BSP_DIR)/drivers/abb/bsp_abb_tv201.c \
	$(BSP_DIR)/drivers/abb/bsp_abb_tv210.c \
	$(BSP_DIR)/drivers/abb/bsp_abb_tv220.c \
	$(BSP_DIR)/drivers/abb/bsp_abb_tv230.c \
	$(BSP_DIR)/drivers/abb/bsp_abb_tv260.c \
	$(BSP_DIR)/drivers/abb/bsp_abb_tv300.c \
	$(BSP_DIR)/drivers/abb/bsp_abb_tv310.c
endif

#hkadc
ifeq ($(strip $(CFG_CONFIG_HKADC)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/hkadc/bsp_hkadc.c \
	$(BSP_DIR)/drivers/hkadc/hkadc_debug.c
endif

#onoff
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/adp/adp_onoff.c
ifeq ($(strip $(CFG_CONFIG_ONOFF)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/onoff/bsp_onoff.c
endif

#bbp
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/adp/adp_bbp.c\
    $(BSP_DIR)/drivers/bbp/bbp.c
ifeq ($(strip $(CFG_CONFIG_BBP)),YES)
ifeq ($(strip $(CFG_BSP_CONFIG_BBP_V1)),YES)
OBC_LOCAL_SRC_FILE += \
    $(BSP_DIR)/drivers/bbp/hi_bbp_reg_hi6921.c 
endif
ifeq ($(strip $(CFG_BSP_CONFIG_BBP_V3650)),YES)
OBC_LOCAL_SRC_FILE += \
    $(BSP_DIR)/drivers/bbp/hi_bbp_reg_hi3650.c 
endif
ifneq ($(strip $(CFG_BSP_CONFIG_BBP_V1)),YES)
ifneq ($(strip $(CFG_BSP_CONFIG_BBP_V3650)),YES)
OBC_LOCAL_SRC_FILE += \
    $(BSP_DIR)/drivers/bbp/hi_bbp_reg.c 
endif
endif
OBC_LOCAL_SRC_FILE += \
    $(BSP_DIR)/drivers/bbp/bbp_dts.c \
    $(BSP_DIR)/drivers/bbp/bbp_pwrctrl.c \
	$(BSP_DIR)/drivers/bbp/bbp_balong.c \
	$(BSP_DIR)/drivers/bbp/bbp_balong_debug.c

OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/bbp/bbp_balong_test.c \
    $(BSP_DIR)/drivers/bbp/bbp_api_test.c 
endif
OBC_LOCAL_SRC_TEST_FILE += \
    $(BSP_DIR)/drivers/power/adp_power_api_test.c

# version
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/adp/adp_version.c \
	$(BSP_DIR)/drivers/version/version_balong.c

#i2c
#当前不编，若需要编译，必须在product_config.define填加此项
ifeq ($(strip $(CFG_CONFIG_CCORE_I2C)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/i2c/i2c_balong.c

OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/i2c/i2c_balong_test.c
endif

#modem memrepair
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/memrepair/memrepair_balong.c\
    $(BSP_DIR)/drivers/memrepair/memrepair_debug.c

# gpio
ifeq ($(strip $(CFG_CONFIG_GPIO_SYNOPSYS)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/gpio/gpio_balong.c
endif

ifeq ($(strip $(CFG_CONFIG_GPIO_PL061)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/gpio/gpio_pl061.c
endif

ifeq ($(CFG_CONFIG_MODEM_PINTRL),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/pintrl/pintrl_balong.c

endif

# anten
ifeq ($(strip $(CFG_CONFIG_ANTEN)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/anten/anten_balong.c
OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/anten/anten_balong_test.c
endif

# ddm
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/om/ddm/ddm_phase.c

# efuse
ifeq ($(strip $(CFG_CONFIG_EFUSE)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/efuse/efuse_balong.c
endif

#ipf
ifeq ($(strip $(CFG_CONFIG_IPF)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/ipf/ipf_balong.c

OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/ipf/ipf_balong_test.c

endif

#psam
ifeq ($(strip $(CFG_CONFIG_PSAM)),YES) 
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/psam/psam_balong.c

ifneq ($(strip $(CFG_CONFIG_MODULE_BUSSTRESS)),YES)
OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/psam/psam_balong_test.c \
	$(BSP_DIR)/drivers/psam/psam_cipher_test.c \
	$(BSP_DIR)/drivers/psam/psam_test.c
endif
endif


# pmu
ifeq ($(strip $(CFG_CONFIG_PMU_NEW)),YES)
OBC_LOCAL_SRC_FILE += \
    $(BSP_DIR)/drivers/pmu_new/pmic_volt.c \
    $(BSP_DIR)/drivers/pmu_new/pmic_ocp.c \
    $(BSP_DIR)/drivers/pmu_new/pmic_init.c \
    $(BSP_DIR)/drivers/pmu_new/pmic_dts.c \
    $(BSP_DIR)/drivers/pmu_new/dcdc_volt.c \
    $(BSP_DIR)/drivers/pmu_new/pmu_debug.c \
	$(BSP_DIR)/drivers/pmu_new/pmic_clk.c
    
endif
ifeq ($(strip $(CFG_CONFIG_PMIC_FPGA)),YES)
OBC_LOCAL_SRC_FILE += \
    $(BSP_DIR)/drivers/pmu_new/pmu_fpga.c 
endif
OBC_LOCAL_SRC_FILE += \
    $(BSP_DIR)/drivers/pmu_new/pmu_balong.c
OBC_LOCAL_SRC_FILE += \
    $(BSP_DIR)/drivers/adp/adp_pmu.c


#mipi
ifeq ($(strip $(CFG_CONFIG_MIPI)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/mipi/mipi_balong.c 
endif

#rffe interface
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/rffe/rf_balong.c
#rffe power
ifeq ($(strip $(CFG_CONFIG_RFFE_POWER)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/rffe/rf_power.c
endif
#rffe mipi
ifeq ($(strip $(CFG_CONFIG_RFFE_MIPI)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/rffe/rf_mipi_cfg.c
endif
#rffe ant
ifeq ($(strip $(CFG_CONFIG_RFFE_ANTEN)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/rffe/rf_anten_cfg.c
endif



# modem reset
ifeq ($(strip $(CFG_CONFIG_BALONG_MODEM_RESET)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/reset/reset_balong.c
endif

#adp
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/adp/adp_wdt.c \
	$(BSP_DIR)/drivers/adp/adp_ipc.c  \
	$(BSP_DIR)/drivers/adp/adp_icc.c \
	$(BSP_DIR)/drivers/adp/adp_pm_om.c \
	$(BSP_DIR)/drivers/adp/adp_timer.c \
	$(BSP_DIR)/drivers/adp/adp_sysctrl.c \
	$(BSP_DIR)/drivers/adp/adp_edma.c \
	$(BSP_DIR)/drivers/adp/adp_wakelock.c \
	$(BSP_DIR)/drivers/adp/adp_power.c\
	$(BSP_DIR)/drivers/adp/adp_cipher.c\
	$(BSP_DIR)/drivers/adp/adp_nvim.c\
	$(BSP_DIR)/drivers/adp/adp_sci.c \
	$(BSP_DIR)/drivers/adp/adp_om.c \
	$(BSP_DIR)/drivers/adp/adp_socp.c\
	$(BSP_DIR)/drivers/adp/adp_sec.c\
	$(BSP_DIR)/drivers/adp/adp_gpio.c\
	$(BSP_DIR)/drivers/adp/adp_anten.c\
	$(BSP_DIR)/drivers/adp/adp_efuse.c\
	$(BSP_DIR)/drivers/adp/adp_temperature.c\
	$(BSP_DIR)/drivers/adp/adp_pm.c\
	$(BSP_DIR)/drivers/adp/adp_usb.c \
	$(BSP_DIR)/drivers/adp/adp_reset.c \
	$(BSP_DIR)/drivers/adp/adp_amon.c\
	$(BSP_DIR)/drivers/adp/adp_mem_balong.c \
	$(BSP_DIR)/drivers/adp/adp_abb.c \
	$(BSP_DIR)/drivers/adp/adp_vic.c \
	$(BSP_DIR)/drivers/adp/adp_mipi.c 



#tcxo
ifeq ($(strip $(CFG_CONFIG_TCXO_BALONG)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/tcxo/tcxo_balong.c
endif
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/tcxo/tcxo.c

#leds --start
ifeq ($(strip $(CFG_CONFIG_LEDS_CCORE)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/leds/leds_balong.c 
endif
#leds --end

#rtc
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/rtc/rtc_balong.c
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/rtc/rtc_platform.c

#mem
ifeq ($(strip $(CFG_CONFIG_MEM)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/mem/mem_balong.c

OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/mem/mem_balong_test.c
endif

# nvim
ifeq ($(strip $(CFG_CONFIG_NVIM)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/nvim/nv_comm.c \
    $(BSP_DIR)/drivers/nvim/nv_base.c  \
	$(BSP_DIR)/drivers/nvim/NVIM_ResumeId.c \
	$(BSP_DIR)/drivers/nvim/nv_debug.c

#OBC_LOCAL_SRC_TEST_FILE += \
#	$(BSP_DIR)/drivers/nvim/nv_test.c \
#    $(BSP_DIR)/drivers/nvim/nv_api_test.c
endif


# sci
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/sci/sci_balong.c \
	$(BSP_DIR)/drivers/sci/sci_pl131.c  \
	$(BSP_DIR)/drivers/sci/sci_debug.c  \
	$(BSP_DIR)/drivers/sci/sci_cfg.c  \
	

# dsda add sci_cfg.c
#OBC_LOCAL_SRC_TEST_FILE += \
#	$(BSP_DIR)/drivers/sci/sci_balong_test.c \
#	$(BSP_DIR)/drivers/sci/sci_api_test.c
	
	
#aximonitor
ifeq ($(strip $(CFG_ENABLE_BUILD_AMON)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/om/aximonitor/amon_balong.c \
	$(BSP_DIR)/drivers/om/aximonitor/amon_addr_balong.c 
endif


# om
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/om/log/bsp_om_log.c
	
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/om/common/regcpy.s

ifeq ($(strip $(CFG_ENABLE_BUILD_OM)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/om/common/bsp_om_comm.c \
	$(BSP_DIR)/drivers/om/common/bsp_dmesg.c \
	$(BSP_DIR)/drivers/om/common/bsp_om_save.c 

OBC_LOCAL_SRC_FILE += $(BSP_DIR)/drivers/om/dump/bsp_dump_rtosck.c
OBC_LOCAL_SRC_FILE += $(BSP_DIR)/drivers/om/dump/bsp_dump_mem.c



# amon
#ifeq ($(strip $(CFG_ENABLE_BUILD_AMON)),YES)
#OBC_LOCAL_SRC_FILE += \
#	$(BSP_DIR)/drivers/om/aximonitor/amon_balong.c \
#	$(BSP_DIR)/drivers/om/aximonitor/amon_addr_balong.c
#endif



#OBC_LOCAL_SRC_FILE += \
#	$(BSP_DIR)/drivers/om/test/bsp_dump_test.c
#OBC_LOCAL_SRC_TEST_FILE += \
#	$(BSP_DIR)/drivers/om/test/bsp_om_test.c \
#	$(BSP_DIR)/drivers/om/test/bsp_dump_test.c

#ifeq ($(strip $(CFG_ENABLE_BUILD_AMON)),YES)
#OBC_LOCAL_SRC_TEST_FILE += \
#	$(BSP_DIR)/drivers/om/test/amon_balong_test.c
#endif
endif

#watchpoint
ifeq ($(strip $(CFG_CONFIG_WATCHPOINT)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/watchpoint/watchpoint.c
endif

#pdlock
ifeq ($(strip $(CFG_CONFIG_PDLOCK)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/pdlock/pdlock_balong.c
endif

#dsp_dvs
ifeq ($(strip $(CFG_CONFIG_DSPDVS)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/dspdvs/dsp_dvs.c
endif

#coresight
ifeq ($(strip $(CFG_CONFIG_CORESIGHT)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/coresight/coresight-platform.c \
	$(BSP_DIR)/drivers/coresight/coresight-dts.c \
	$(BSP_DIR)/drivers/coresight/coresight-etm.c \
	$(BSP_DIR)/drivers/coresight/coresight-funnel.c \
	$(BSP_DIR)/drivers/coresight/coresight-tmc.c \
	$(BSP_DIR)/drivers/coresight/coresight-mgr.c \
	$(BSP_DIR)/drivers/coresight/coresight-dep.c
endif

# socp
ifeq ($(strip $(CFG_ENABLE_BUILD_SOCP)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/socp/socp_balong.c \
	$(BSP_DIR)/drivers/socp/socp_debug.c
ifneq ($(strip $(CFG_CONFIG_MODULE_BUSSTRESS)),YES)
OBC_LOCAL_SRC_TEST_FILE += \
	$(BSP_DIR)/drivers/socp/socp_balong_test.c \
	$(BSP_DIR)/drivers/socp/socp_st_test.c \
	$(BSP_DIR)/drivers/socp/socp_api_test.c 
endif

endif
# rfile
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/rfile/rfile_balong.c \
	$(BSP_DIR)/drivers/adp/adp_rfile.c
#loadps
ifeq ($(strip $(CFG_FEATURE_TDS_WCDMA_DYNAMIC_LOAD)),FEATURE_ON)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/load_ps/bsp_loadps.c
endif

	# mailbox
ifeq ($(strip $(CFG_FEATURE_TLPHY_MAILBOX)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/mailbox/mailbox_commom.c \
	$(BSP_DIR)/drivers/mailbox/mailbox_commsg.c \
	$(BSP_DIR)/drivers/mailbox/mailbox_spmsg.c
else
OBC_LOCAL_SRC_FILE +=$(BSP_DIR)/drivers/adp/adp_mbxtlphy.c
endif

# tsensor
ifeq ($(strip $(CFG_CONFIG_TSENSOR)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/tsensor/tsensor_balong.c \
	$(BSP_DIR)/drivers/tsensor/tsensor_debug.c 
endif

# dynamic load
ifeq ($(strip $(CFG_CONFIG_DYNAMIC_LOAD)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/dynamic_load/dynamic_load.c 
ifeq ($(strip $(OBB_SEPARATE)),true)
OBC_LOCAL_SRC_FILE += \
        $(BSP_DIR)/drivers/dynamic_load/dynamic_load_stub.c
endif
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/dynamic_load
endif

ifeq ($(strip $(llt_gcov)),y)
OBC_LOCAL_SRC_FILE += \
	$(BALONG_TOPDIR)/llt/mdrv/tools/gcov/libgcov.c \
	$(BALONG_TOPDIR)/llt/mdrv/tools/gcov/mygcov.c
endif

# mbxhifi
OBC_LOCAL_SRC_FILE +=$(BSP_DIR)/drivers/adp/adp_mbxhifi.c

#	$(BSP_DIR)/drivers/mbxhifi/drv_mailbox_test_vxworks.c \

#sys_bus
ifeq ($(strip $(CFG_CONFIG_SYSBUS)),YES)
OBC_LOCAL_SRC_FILE +=  \
	$(BSP_DIR)/drivers/sys_bus/c_sys_bus_core.c \
	$(BSP_DIR)/drivers/sys_bus/c_sys_bus_single.c \
	$(BSP_DIR)/drivers/sys_bus/c_sys_bus_pressure.c \
	$(BSP_DIR)/drivers/sys_bus/c_sys_monitor.c \
	$(BSP_DIR)/drivers/sys_bus/c_sys_edma.c\
	$(BSP_DIR)/drivers/sys_bus/c_sys_ipf.c\
	$(BSP_DIR)/drivers/sys_bus/c_sys_acc.c\
	$(BSP_DIR)/drivers/sys_bus/c_sys_dsp.c \
	$(BSP_DIR)/drivers/sys_bus/c_sys_cpufreq.c\
	$(BSP_DIR)/drivers/sys_bus/gu/uft_comm/BasicFunc.c \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_comm/common.c \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_comm/dmac1.c \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_comm/mem_fun.c \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_hdlc/c_sys_gu.c \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_hdlc/hdlcv200_frm_def_test_bbit.c \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_cicom/cicom.c \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_upacc/upacc.c \
	$(BSP_DIR)/drivers/sys_bus/c_sys_ddr.c \
	$(BSP_DIR)/drivers/sys_bus/c_sys_os.c \
	$(BSP_DIR)/drivers/sys_bus/c_sys_pmu.c
endif
#for end CFG_CONFIG_SMART_SYSTEM_MODEM
endif

endif


MULTI_INSTANCE :=FALSE
ifeq ($(INSTANCE_ID),INSTANCE_1)
MULTI_INSTANCE :=TRUE
endif
ifeq ($(INSTANCE_ID),INSTANCE_2)
MULTI_INSTANCE :=TRUE
endif

ifeq ($(MULTI_INSTANCE),TRUE)
OBC_LOCAL_SRC_FILE += \
        $(BSP_DIR)/drivers/sci/sci_balong.c \
        $(BSP_DIR)/drivers/sci/sci_pl131.c  \
        $(BSP_DIR)/drivers/sci/sci_debug.c  \
    $(BSP_DIR)/drivers/adp/adp_sci.c

OBC_LOCAL_SRC_TEST_FILE += \
        $(BSP_DIR)/drivers/sci/sci_balong_test.c
endif



#*******************************************************************
# inc:OBC_LOCAL_INC_DIR
#*******************************************************************
# include
OBC_LOCAL_INC_DIR += \
	$(BALONG_TOPDIR)/modem/include/drv \
	$(BALONG_TOPDIR)/modem/include/drv/ccore \
	$(BALONG_TOPDIR)/modem/include/drv/common \
	$(BALONG_TOPDIR)/modem/include/ps/gups \
	$(BALONG_TOPDIR)/modem/include/nv/tl/drv \
	$(BALONG_TOPDIR)/modem/include/nv/gu/drv \
	$(BALONG_TOPDIR)/modem/include/nv/comm \
	$(BALONG_TOPDIR)/modem/include/nv/tl/oam \
	$(BALONG_TOPDIR)/modem/include/nv/product \
	$(BALONG_TOPDIR)/modem/include/phy/lphy \
	$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/os/ccore \
	$(BALONG_TOPDIR)/modem/config/product/nvim/include/gu


# sys
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/sys

#ccore include
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/modem/include \
	$(BALONG_TOPDIR)/modem/include/nv/tl/drv \
	$(BALONG_TOPDIR)/modem/include/nv/tl/oam \
	$(BALONG_TOPDIR)/modem/include/nv/tl/lps \
    $(BALONG_TOPDIR)/modem/include/nv/tl/phy \
	$(BALONG_TOPDIR)/modem/config/nvim/include/gu

# driver
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/sys \
	$(BSP_DIR)/drivers/gic \
	$(BSP_DIR)/drivers/serial \
	$(BSP_DIR)/drivers/systimer \
	$(BSP_DIR)/drivers/ipc \
	$(BSP_DIR)/drivers/icc \
	$(BSP_DIR)/drivers/pmu/hi6551 \
	$(BSP_DIR)/drivers/pmu/hi6552 \
	$(BSP_DIR)/drivers/pmu/hi6559 \
	$(BSP_DIR)/drivers/regulator \
	$(BSP_DIR)/drivers/clk \
	$(BSP_DIR)/drivers/nvim \
	$(BSP_DIR)/drivers/om \
	$(BSP_DIR)/drivers/om/dump \
	$(BSP_DIR)/drivers/om/log \
	$(BSP_DIR)/drivers/om/common \
	$(BSP_DIR)/drivers/om/aximonitor \
	$(BSP_DIR)/drivers/dpm \
	$(BSP_DIR)/drivers/socp \
	$(BSP_DIR)/drivers/i2c \
	$(BSP_DIR)/drivers/wakelock\
	$(BSP_DIR)/drivers/rfile\
	$(BSP_DIR)/drivers/sec\
	$(BSP_DIR)/drivers/tcxo\
	$(BSP_DIR)/drivers/bbp\
	$(BSP_DIR)/drivers/gpio\
	$(BSP_DIR)/drivers/ios\
	$(BSP_DIR)/drivers/mem\
	$(BSP_DIR)/drivers/balong_timer\
	$(BSP_DIR)/drivers/mipi \
	$(BSP_DIR)/drivers/rffe \
    $(BSP_DIR)/drivers/memrepair
	
ifeq ($(strip $(CFG_CONFIG_PMU_NEW)),YES)
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/pmu_new 
else
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/pmu 
endif

OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/rtc

ifeq ($(strip $(CFG_CONFIG_IPF)),YES)
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/ipf
endif

ifeq ($(strip $(CFG_CONFIG_MODULE_VIC)),YES)
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/vic
endif

ifeq ($(strip $(CFG_CONFIG_IPF)),YES)
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/ipf
endif
# busstress
ifeq ($(strip $(CFG_CONFIG_MODULE_BUSSTRESS)),YES)
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/busstress \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_comm \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_hdlc \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_cicom \
	$(BSP_DIR)/drivers/busstress/$(OBB_PRODUCT_NAME)/gu/uft_upacc
endif

OBC_LOCAL_INC_DIR += \
         $(BSP_DIR)/drivers/busstress/gu

OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/board

# osl
OBC_LOCAL_INC_DIR += \
	$(DRV_DIR)/common/include \
    $(DRV_DIR)/ccore/include

# ddm
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/om/ddm

# anten
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/anten

# efuse
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/efuse

# gpio
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/gpio

# rse
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/rse

# ios
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/ios
# pintrl
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/pintrl
		

#cipher
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/cipher

# temperature
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/temperature

#cpuidle
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/cpuidle

#lowpower mntn
ifeq ($(strip $(CFG_CONFIG_PWC_MNTN_CCORE)),YES)
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/lowpower_mntn
endif

#leds
ifeq ($(strip $(CFG_CONFIG_LEDS_CCORE)),YES)
OBC_LOCAL_INC_DIR += \
	$(BSP_DIR)/drivers/leds
endif

#dual_modem
ifeq ($(strip $(CFG_CONFIG_DUAL_MODEM)),YES)
OBC_LOCAL_INC_DIR +=  \
	$(BSP_DIR)/drivers/dual_modem
endif

# CPHY mailbox
ifeq ($(strip $(CFG_FEATURE_CPHY_MAILBOX)),YES)
OBC_LOCAL_SRC_FILE += \
	$(BSP_DIR)/drivers/mbxcphy/xmailbox_common.c \
	$(BSP_DIR)/drivers/mbxcphy/xmailbox_commsg.c
endif

#sys_bus

OBC_LOCAL_INC_DIR +=  \
	$(BSP_DIR)/drivers/sys_bus\
	$(BSP_DIR)/drivers/sys_bus/gu/uft_comm \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_hdlc \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_cicom \
	$(BSP_DIR)/drivers/sys_bus/gu/uft_upacc
