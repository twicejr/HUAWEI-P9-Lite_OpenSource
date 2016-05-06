#
# Makefile for the memory technology device drivers.
#

# Core functionality.
-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

obj-y				+= log/
obj-$(CONFIG_BALONG_EASY_SHELL) += easy_shell/
ifeq ($(strip $(CFG_ENABLE_BUILD_OM)),YES)
obj-y				+= common/
obj-y				+= dump/
endif

KBUILD_CPPFLAGS += -Idrivers/hisi/modem/drv/om \
                   -Idrivers/hisi/modem/drv/om/common \
                   -Idrivers/hisi/modem/drv/om/dump \
                   -Idrivers/hisi/modem/drv/om/log 
                   
subdir-ccflags-y := -Werror


