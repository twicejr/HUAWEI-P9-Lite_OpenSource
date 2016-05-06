ifneq ($(KERNEL_MODEM_IDL_SPLIT),true)
-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/winterface/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/adrv/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/drv/acore/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/drv/common/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/drv/common/include/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/nv/tl/drv/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/nv/product/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/nv/tl/oam/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/nv/tl/lps/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/phy/lphy/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/config/nvim/include/gu/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/taf/common/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/include/taf/acore/
subdir-ccflags-y += -I$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config

obj-$(CONFIG_HISI_BALONG_MODEM) +=drv/

ifneq ($(OBB_SEPARATE),true)
obj-$(CONFIG_BALONG_OAM_PS) +=oam/ ps/ taf/ 

#ifeq ($(CFG_FEATURE_IMS),FEATURE_ON)
obj-$(CONFIG_HISI_BALONG_MODEM) +=ims/
#endif

endif
else
obj-y += kernel_modem.o
endif
