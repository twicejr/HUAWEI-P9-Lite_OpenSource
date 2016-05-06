#
# Makefile for the linux kernel.
#
-include $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
ccflags-y := -Werror
ccflags-y += -Idrivers/hisi/modem/drv/ipf -Iinclude/linux  -Idrivers/hisi/modem/drv/sys_bus/sys_hdlc
obj-y += sys_bus_core.o
obj-y += sys_bus_single.o
obj-y += sys_bus_pressure.o
obj-y += sys_edma.o
obj-y += sys_ipf.o
obj-y += sys_hdlc/
obj-y += sys_acore.o
obj-y += sys_netlink.o
obj-y += sys_monitor.o
ifeq ($(strip $(CFG_CONFIG_FB_EMI_BALONG)),YES)
	obj-y += sys_lcd.o
endif
obj-y += sys_socp.o
