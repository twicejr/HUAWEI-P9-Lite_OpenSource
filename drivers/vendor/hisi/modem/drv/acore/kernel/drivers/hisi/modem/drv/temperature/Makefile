#
# Makefile for the input core drivers.
#

# Each configuration option enables a list of files.
-include $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

ifeq ($(strip $(CFG_CONFIG_TEMPERATURE_PROTECT)),YES)
obj-y		+= temperature_balong.o adp_temperature.o temperature_debug.o
obj-$(CONFIG_TEMPERATURE_SYS_BALONG)	+= tempsys_device.o
else
obj-y		+= temperature_stub.o
endif



