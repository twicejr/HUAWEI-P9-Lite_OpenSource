LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

-include $(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config/balong_product_config.mk
CFLAGS  += -I$(PRJ_TOP_DIR)/drivers/modem \
		   -I$(PRJ_TOP_DIR)/include \
		   -I$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/config \
           -I$(BALONG_TOPDIR)/modem/config/product/$(OBB_PRODUCT_NAME)/include_gu \
           -I$(BALONG_TOPDIR)/modem/config/nvim/include/gu \
           -I$(BALONG_TOPDIR)/modem/include/drv/acore \
           -I$(BALONG_TOPDIR)/modem/include/nv/tl/drv \
           -I$(BALONG_TOPDIR)/modem/include/nv/tl/oam \
           -I$(BALONG_TOPDIR)/modem/include/nv/tl/lps \
           -I$(BALONG_TOPDIR)/modem/include/phy/lphy \
           -I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM) \
           -I$(BALONG_TOPDIR)/modem/platform/$(CFG_PLATFORM)/soc \
           -I$(BALONG_TOPDIR)/modem/drv/common/include \
		   -I$(BALONG_TOPDIR)/modem/include/drv/common \
		   -I$(BALONG_TOPDIR)/modem/include/adrv
		   
LIB := lib_modem.a

COBJFILE	:= modem.o nv_boot.o nv_emmc.o nv_xml_dec.o version.o pintrl_balong.o temperature_balong.o param_cfg_to_sec.o
SOBJFILE	:=

ifeq ($(strip $(CFG_CONFIG_PM_OM)),YES)
COBJFILE += pm_om_smem.o
else
COBJFILE += adp_pm_om.o
endif

include $(BUILD_SUB_OBJ_LIBRARY)
