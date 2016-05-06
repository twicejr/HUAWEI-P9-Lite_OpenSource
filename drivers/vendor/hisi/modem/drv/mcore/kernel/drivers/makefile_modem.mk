-include $(BALONG_TOPDIR)/build/scripts/make_base.mk
ifeq ($(strip $(CFG_OS_ANDROID_USE_K3V3_KERNEL)),YES)
DRIVER_SRCS += \
	$(DRIVER_DIR)/modem/ipf/ipf_balong_pm.c \
	$(DRIVER_DIR)/modem/ipc/ipc_lpm3_k3.c \
	$(DRIVER_DIR)/modem/icc/icc_balong.c \
	$(DRIVER_DIR)/modem/icc/icc_balong_debug.c \
	$(DRIVER_DIR)/modem/timer/softtimer_lpm3_k3.c \
	$(DRIVER_DIR)/modem/nvim/nv_base.c \
	$(DRIVER_DIR)/modem/nvim/nv_comm.c \
	$(DRIVER_DIR)/modem/modem/m3_modem.c \
	$(DRIVER_DIR)/modem/pm-k3/m3_pm_modem.c \
	$(DRIVER_DIR)/modem/pm-k3/m3_dpm_modem.c \
	$(DRIVER_DIR)/modem/pm-k3/m3_cpufreq_modem.c \
	$(DRIVER_DIR)/modem/watchdog/wdt_balong.c \
	$(DRIVER_DIR)/modem/regulator/regulator_balong.c \
	$(DRIVER_DIR)/modem/dpm/dpm_lpm3_k3.c \
	$(DRIVER_DIR)/modem/temperature/temperature.c \
	$(DRIVER_DIR)/modem/om/om_balong.c \
	$(DRIVER_DIR)/modem/socp/socp_balong.c \
	$(DRIVER_DIR)/modem/edma/edma_balong.c \
	$(DRIVER_DIR)/modem/hkadc/bsp_hkadc.c \
	$(DRIVER_DIR)/modem/start-k3/modem_start.c \
	$(DRIVER_DIR)/modem/reset/reset_balong.c \
	$(DRIVER_DIR)/modem/start/ccpu_start.c \
	$(DRIVER_DIR)/modem/pmu_new/pmu.c \
	$(DRIVER_DIR)/modem/dual_modem/dual_modem_wakeup.c
CFLAGS  += \
	-I$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config \
	-I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM) \
	-I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc \
	-I$(BALONG_TOPDIR)/modem/include/drv \
	-I$(BALONG_TOPDIR)/modem/include/nv/tl/drv \
	-I$(BALONG_TOPDIR)/modem/include/nv/tl/oam \
	-I$(BALONG_TOPDIR)/modem/drv/common/include \
	-I$(BALONG_TOPDIR)/modem/include/tools \
	-I$(SYS_DIR) \
	-I$(DRIVER_DIR)/modem/modem \
	-I$(DRIVER_DIR)/modem/pm-k3 \
	-I$(DRIVER_DIR)/modem/icc \
	-I$(DRIVER_DIR)/modem/ipc \
	-I$(DRIVER_DIR)/modem/dpm \
	-I$(DRIVER_DIR)/modem/watchdog \
	-I$(DRIVER_DIR)/modem/tsensor \
	-I$(DRIVER_DIR)/modem/edma \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/om \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/socp \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/regulator \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/temperature \
	-I$(DRIVER_DIR)/modem/start-k3 \
	-I$(DRIVER_DIR)/modem/start \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/reset \
	-I$(BALONG_TOPDIR)/modem/drv/mcore/kernel/drivers/pmu_new

CFLAGS  += -DK3V3_LPM3_HAS_MODEM_FEATURE

$(waring ******CFLAGS=$(CFLAGS))
endif
