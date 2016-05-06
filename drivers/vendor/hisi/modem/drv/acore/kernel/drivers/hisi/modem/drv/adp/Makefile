#
# created by y000184236 for k3v3 fpga
#
-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
KBUILD_CPPFLAGS += -Idrivers/hisi/modem/drv/icc
KBUILD_CPPFLAGS += -Idrivers/hisi/modem/drv/rtc
KBUILD_CPPFLAGS += -Idrivers/hisi/modem/drv/nvim
KBUILD_CPPFLAGS += -Idrivers/hisi/modem/drv/mem
KBUILD_CPPFLAGS += -Idrivers/hisi/modem/drv/om \
                   -Idrivers/hisi/modem/drv/om/common \
                   -Idrivers/hisi/modem/drv/om/dump \
                   -Idrivers/hisi/modem/drv/om/log 
KBUILD_CPPFLAGS += -Idrivers/hisi/modem/drv/udi
KBUILD_CPPFLAGS += -Idrivers/hisi/modem/drv/balong_timer
KBUILD_CPPFLAGS += -Idrivers/usb/gadget
ifneq ($(strip $(CFG_ATE_VECTOR)),YES)
obj-y           += adp_ipc.o
obj-y           += adp_icc.o
obj-y           += adp_pm_om.o
obj-y           += adp_version.o
obj-y           += adp_socp.o
obj-y           += adp_onoff.o
obj-y			+= adp_om.o
obj-y           += adp_usb.o
obj-$(CONFIG_RFILE_SUPPORT)  += adp_rfile.o
obj-y           += adp_nvim.o
obj-y           += adp_reset.o
obj-y           += adp_gpio.o
obj-y           += adp_efuse.o
obj-y 			+= adp_wdt.o
obj-y           += adp_timer.o
obj-y           += adp_wifi.o
obj-y           += adp_mailbox.o
obj-y           += adp_sec.o
obj-y           += adp_dpm.o
obj-y           += adp_mem_balong.o
obj-y           += adp_cpufreq_balong.o
ifeq ($(strip $(CFG_BSP_CONFIG_PHONE_TYPE)),YES)
obj-y			+= adp_nandc_k3.o
endif
obj-y           += adp_charger.o
obj-y           += adp_mmc.o
obj-y           += adp_dload.o
obj-y           += adp_misc.o
obj-y           += adp_vic.o
else
obj-y           += adp_pm_om.o
obj-y           += adp_reset.o
obj-y           += adp_timer.o
obj-y           += adp_vic.o
endif
