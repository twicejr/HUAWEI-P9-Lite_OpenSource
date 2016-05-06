-include $(srctree)/drivers/hisi/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
ifeq ($(strip $(CFG_FEATURE_TDS_WCDMA_DYNAMIC_LOAD)),FEATURE_ON)
EXTRA_CFLAGS += -Idrivers/hisi/tzdriver
obj-y       += bsp_loadps.o
endif
