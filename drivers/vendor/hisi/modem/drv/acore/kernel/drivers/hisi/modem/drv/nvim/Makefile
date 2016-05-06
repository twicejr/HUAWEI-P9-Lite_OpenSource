-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk

KBUILD_CPPFLAGS += -Idrivers/hisi/modem/drv/om/dump

subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/nv/product/


ifeq ($(strip $(CFG_FEATURE_NV_FLASH_ON)),YES)
obj-$(CONFIG_NVIM)		    += nv_flash.o
endif
ifeq ($(strip $(CFG_FEATURE_NV_EMMC_ON)),YES)
obj-$(CONFIG_NVIM)		    += nv_emmc.o
endif
obj-$(CONFIG_NVIM)         += NVIM_ResumeId.o nv_ctrl.o nv_comm.o nv_base.o nv_xml_dec.o nvchar.o nv_debug.o 


subdir-ccflags-y := -Werror

